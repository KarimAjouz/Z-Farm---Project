#include "TilePicker.h"

#include "Definitions.h"

TilePicker::TilePicker(ZEngine::GameDataRef data) :
	_data(data),
	active(false)
{
	_data->assetManager.LoadTexture("Tiles", TILE_PATH);
	_data->assetManager.LoadTexture("Units", UNITS_PATH);
	_selector.setTexture(_data->assetManager.GetTexture("Tiles"));
	_selector.setPosition(sf::Vector2f(SCREEN_WIDTH - _selector.getTexture()->getSize().x, SCREEN_HEIGHT - _selector.getTexture()->getSize().y));

	_selectorWindow.setFillColor(sf::Color::Transparent);
	_selectorWindow.setOutlineColor(sf::Color::Black);
	_selectorWindow.setOutlineThickness(4.0f);
	_selectorWindow.setPosition(sf::Vector2f(SCREEN_WIDTH - _selector.getTexture()->getSize().x, SCREEN_HEIGHT - _selector.getTexture()->getSize().y ));
	_selectorWindow.setSize(sf::Vector2f(_selector.getTexture()->getSize().x , _selector.getTexture()->getSize().y ));

	_hoveredTile.setFillColor(sf::Color::Transparent);
	_hoveredTile.setOutlineColor(sf::Color::Magenta);
	_hoveredTile.setOutlineThickness(2.0f);
	_hoveredTile.setSize(sf::Vector2f(32, 32));

	_activeTile.setFillColor(sf::Color::Transparent);
	_activeTile.setOutlineColor(sf::Color::Yellow);
	_activeTile.setOutlineThickness(2.0f);
	_activeTile.setSize(sf::Vector2f(32, 32));
}

TilePicker::~TilePicker()
{

}

void TilePicker::Update(float dT)
{
	if (active)
	{
		//Get the mouse position relative to the sf::view (Mouse position in world space)
		sf::Vector2f mousePosRelativeToView = _data->window.mapPixelToCoords(sf::Mouse::getPosition(_data->window));
		if (_selector.getGlobalBounds().contains(mousePosRelativeToView))
		{
			sf::Vector2f newPos = mousePosRelativeToView;

			//Offsets based on the mouse position 
			newPos.x -= std::fmodf(mousePosRelativeToView.x - (std::fmodf(_selector.getPosition().x, 32.0f)), 32);
			newPos.y -= std::fmodf(mousePosRelativeToView.y - (std::fmodf(_selector.getPosition().y, 32.0f)), 32);

			if (newPos.x < 0)
				newPos.x -= 32.0f;

			if (newPos.y < 0)
				newPos.y -= 32.0f;

			_hoveredTile.setPosition(newPos);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
			state = State::shipTiles;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
			state = State::units;
		

	}

	UpdateState();
}

void TilePicker::Draw()
{
	if (active)
	{
		_data->window.draw(_selector);
		_data->window.draw(_selectorWindow);

		_data->window.draw(_hoveredTile);
		_data->window.draw(_activeTile);
	
	}
}

sf::IntRect TilePicker::GetTileRect()
{
	sf::IntRect texRect = sf::IntRect(320, 0, 32, 32);

	if (_selector.getGlobalBounds().contains(_data->window.mapPixelToCoords(sf::Mouse::getPosition(_data->window))))
	{
		sf::Vector2f tilePos = _hoveredTile.getPosition();

		tilePos -= _selector.getPosition();

		texRect.left = tilePos.x;
		texRect.top = tilePos.y;
		texRect.width = 32;
		texRect.height = 32;

		_activeTile.setPosition(tilePos);

		active = false;
	}

	return texRect;
}

Agent* TilePicker::InstantiateAgent()
{
	Agent* newAgent = nullptr;

	if (_selector.getGlobalBounds().contains(_data->window.mapPixelToCoords(sf::Mouse::getPosition(_data->window))))
	{
		sf::Vector2f tilePos = _hoveredTile.getPosition();

		

		_activeTile.setPosition(tilePos);

		active = false;
	}

	return newAgent;
}

void TilePicker::Activate()
{
	active = true;
	_selector.setPosition(sf::Vector2f(_data->window.mapPixelToCoords(sf::Mouse::getPosition(_data->window))));
	_selectorWindow.setPosition(sf::Vector2f(_data->window.mapPixelToCoords(sf::Mouse::getPosition(_data->window))));
	_activeTile.setPosition(_activeTile.getPosition() + _selector.getPosition());
}

void TilePicker::UpdateState()
{
	switch (state)
	{
		case State::shipTiles:
			_selector.setTexture(_data->assetManager.GetTexture("Tiles"));
			_selectorWindow.setSize(static_cast<sf::Vector2f>(_selector.getTexture()->getSize()));
			break;
		case State::units:
			_selector.setTexture(_data->assetManager.GetTexture("Units"));
			_selectorWindow.setSize(static_cast<sf::Vector2f>(_selector.getTexture()->getSize()));
			break;

	}
}