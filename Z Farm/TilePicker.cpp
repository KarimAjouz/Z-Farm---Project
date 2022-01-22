#include "TilePicker.h"

#include "Definitions.h"

TilePicker::TilePicker(ZEngine::GameDataRef data) :
	_data(data),
	active(false)
{
	_data->assetManager.LoadTexture("Tiles", TILE_PATH);
	_data->assetManager.LoadTexture("AlarmPig", UNITS_PATH);
	_data->assetManager.LoadTexture("Spike", SPIKE_TRAP);
	_data->assetManager.LoadTexture("Box", BOX_OBSTACLE);
	_data->assetManager.LoadTexture("Sword", SWORD_ITEM);


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

	InitEntities();
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
		{
			state = State::shipTiles;
			RepositionWindows();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
		{
			state = State::units;
			RepositionWindows();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
		{
			state = State::obstacles;
			RepositionWindows();
		}
		//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4))
		//{
		//	state = State::props;
		//	RepositionWindows();
		//}

	}

	UpdateState();
}

void TilePicker::Draw()
{
	switch (state)
	{
	case State::shipTiles:		
		_data->window.draw(_selector);
		break;
	case State::units:
		for (int i = 0; i < _unitList.size(); i++)
			_data->window.draw(_unitList[i].rect);
		break;
	case State::obstacles:
		for (int i = 0; i < _obstacleList.size(); i++)
			_data->window.draw(_obstacleList[i].rect);
		break;
	case State::props:
		_selector.setTexture(_data->assetManager.GetTexture("Props"));
		break;

	}

	_data->window.draw(_selectorWindow);
	_data->window.draw(_hoveredTile);
	_data->window.draw(_activeTile);
}

sf::IntRect TilePicker::GetTileRect()
{
	sf::IntRect texRect = sf::IntRect(320, 0, 32, 32);

	if (_selector.getGlobalBounds().contains(_data->window.mapPixelToCoords(sf::Mouse::getPosition(_data->window))))
	{
		sf::Vector2f tilePos = _hoveredTile.getPosition();

		//tilePos -= _selector.getPosition();

		texRect.left = tilePos.x;
		texRect.top = tilePos.y;
		texRect.width = 32;
		texRect.height = 32;

		_activeTile.setPosition(tilePos);
	}

	return texRect;
}

void TilePicker::Activate()
{
	active = true;
	_activeTile.setPosition(_activeTile.getPosition() + _selector.getPosition());

	RepositionWindows();
}

void TilePicker::Deactivate()
{
	active = false;
}

bool TilePicker::isMouseInPicker()
{
	bool out = _selector.getGlobalBounds().contains(_data->window.mapPixelToCoords(sf::Mouse::getPosition(_data->window)));
	return out;
}

void TilePicker::UpdateState()
{

	


}

void TilePicker::InitEntities()
{
	SelectorItem box;
	box.rect.setTexture(&_data->assetManager.GetTexture("Box"));
	box.rect.setSize(sf::Vector2f(32, 32));
	box.type = static_cast<int>(Obstacle::Type::box);

	box.texture = &_data->assetManager.GetTexture("Box");
	box.rect.setFillColor(sf::Color::White);
	box.rect.setOutlineColor(sf::Color::Black);
	box.rect.setOutlineThickness(1.0f);


	SelectorItem spike;
	spike.rect.setTexture(&_data->assetManager.GetTexture("Spike"));
	spike.rect.setSize(sf::Vector2f(32, 32));
	spike.type = static_cast<int>(Obstacle::Type::spike);
	
	spike.texture = &_data->assetManager.GetTexture("Spike");

	spike.rect.setFillColor(sf::Color::White);
	spike.rect.setOutlineColor(sf::Color::Black);
	spike.rect.setOutlineThickness(1.0f);

	SelectorItem alarmPig;
	alarmPig.rect.setTexture(&_data->assetManager.GetTexture("AlarmPig"));
	alarmPig.rect.setSize(sf::Vector2f(32, 32));
	alarmPig.type = static_cast<int>(Agent::Type::alarmPig);

	alarmPig.texture = &_data->assetManager.GetTexture("AlarmPig");
	alarmPig.rect.setFillColor(sf::Color::White);
	alarmPig.rect.setOutlineColor(sf::Color::Black);
	alarmPig.rect.setOutlineThickness(1.0f);

	_obstacleList.push_back(box);
	_obstacleList.push_back(spike);

	_unitList.push_back(alarmPig);
}

TilePicker::SelectorItem TilePicker::GetSelectorItem()
{
	TilePicker::SelectorItem selectorItem;
	sf::Vector2f mousePosRelativeToView = _data->window.mapPixelToCoords(sf::Mouse::getPosition(_data->window));

	switch (state)
	{
		case State::units:
			if (_selectorWindow.getGlobalBounds().contains(mousePosRelativeToView))
				for (int i = 0; i < _unitList.size(); i++)
					if (_unitList[i].rect.getGlobalBounds().contains(mousePosRelativeToView))
					{

						selectorItem = _unitList[i];
					}
			break;
		case State::obstacles:
			if (_selectorWindow.getGlobalBounds().contains(mousePosRelativeToView))
				for (int i = 0; i < _obstacleList.size(); i++)
					if (_obstacleList[i].rect.getGlobalBounds().contains(mousePosRelativeToView))
						selectorItem = _obstacleList[i];
			break;
	}

	return selectorItem;
}

void TilePicker::RepositionWindows()
{
	switch (state)
	{
		case State::shipTiles:
			_selectorWindow.setSize(sf::Vector2f(_data->assetManager.GetTexture("Tiles").getSize()));
			break;
		case State::units:
			for (int i = 0; i < _unitList.size(); i++)
				_unitList[i].rect.setPosition(_selector.getPosition().x + (i * 32), _selector.getPosition().y + ((i / 10) * 32));
			_selectorWindow.setSize(sf::Vector2f(std::min(static_cast<int>(_unitList.size()), 10) * 32, ((static_cast<int>(_unitList.size()) / 10) + 1) * 32));
			break;
		case State::obstacles:
			for (int i = 0; i < _obstacleList.size(); i++)
				_obstacleList[i].rect.setPosition(_selector.getPosition().x + (i * 32), _selector.getPosition().y + ((i / 10) * 32));
			_selectorWindow.setSize(sf::Vector2f(std::min(static_cast<int>(_obstacleList.size()), 10) * 32, (static_cast<int>((_obstacleList.size()) / 10) + 1) * 32));
			break;
	}

	_selector.setTextureRect(sf::IntRect(0, 0, _selectorWindow.getSize().x, _selectorWindow.getSize().y));
}