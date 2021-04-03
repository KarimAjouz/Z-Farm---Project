#include "TilePicker.h"

#include "Definitions.h"

TilePicker::TilePicker(ZEngine::GameDataRef data) :
	_data(data),
	active(false)
{
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
		if (_selector.getGlobalBounds().contains(_data->window.mapPixelToCoords(sf::Mouse::getPosition(_data->window))))
		{
			sf::Vector2f mousePosRelativeToView = _data->window.mapPixelToCoords(sf::Mouse::getPosition(_data->window));
			sf::Vector2f newPos = mousePosRelativeToView;

			newPos.x -= std::fmodf(mousePosRelativeToView.x, 32);
			newPos.y -= std::fmodf(mousePosRelativeToView.y, 32);

			_hoveredTile.setPosition(newPos);
		}
	}
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
		tilePos.x -= SCREEN_WIDTH - _selector.getTexture()->getSize().x;
		tilePos.y -= SCREEN_HEIGHT - _selector.getTexture()->getSize().y;

		texRect.left = tilePos.x;
		texRect.top = tilePos.y;
		texRect.width = 32;
		texRect.height = 32;

		_activeTile.setPosition(_hoveredTile.getPosition());

		active = false;
	}

	return texRect;
}