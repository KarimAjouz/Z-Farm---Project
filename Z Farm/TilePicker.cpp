#include "TilePicker.h"

#include "Definitions.h"
#include <stdio.h>
#include <iostream>

TilePicker::TilePicker(ZEngine::GameDataRef data) :
	_data(data),
	active(false)
{
	_data->assetManager.LoadTexture("bgTiles", TILE_BG_PATH);
	_data->assetManager.LoadTexture("colTiles", TILE_COL_PATH);
	_data->assetManager.LoadTexture("AlarmPig", PIG_ICON);
	_data->assetManager.LoadTexture("Baldy", BALDY_ICON);
	_data->assetManager.LoadTexture("Spike", SPIKE_TRAP);
	_data->assetManager.LoadTexture("Box", BOX_OBSTACLE);
	_data->assetManager.LoadTexture("Sword", SWORD_ITEM);


	InitSheet("bgTiles", false);
	InitSheet("colTiles", true);

	_selectorWindow.setFillColor(sf::Color::Black);
	_selectorWindow.setOutlineColor(sf::Color::Black);
	_selectorWindow.setOutlineThickness(2.0f);
	_selectorWindow.setPosition(0.0f, 0.0f);
	_selectorWindow.setSize(sf::Vector2f(96.0f, SCREEN_HEIGHT));

	_hoveredTile.setFillColor(sf::Color::Transparent);
	_hoveredTile.setOutlineColor(sf::Color::Magenta);
	_hoveredTile.setOutlineThickness(2.0f);
	_hoveredTile.setSize(sf::Vector2f(TILE_SCALE * TILE_SIZE, TILE_SCALE * TILE_SIZE));

	_activeTile.setFillColor(sf::Color::Transparent);
	_activeTile.setOutlineColor(sf::Color::Yellow);
	_activeTile.setOutlineThickness(2.0f);
	_activeTile.setSize(sf::Vector2f(TILE_SCALE * TILE_SIZE, TILE_SCALE * TILE_SIZE));
	state = State::backgroundTiles;

	_curSelector = _backgroundSpritesheetList[0];

	InitEntities();
}

TilePicker::~TilePicker()
{
}

void TilePicker::Update(float dT)
{
	if (active)
	{
		_selectorWindow.setPosition(_zeroPixel);
		_curSelector.setPosition(_zeroPixel);
		//Get the mouse position relative to the sf::view (Mouse position in world space)
		sf::Vector2f mousePosRelativeToView = _data->GameWindow.mapPixelToCoords(sf::Mouse::getPosition(_data->GameWindow));

		if (state == TilePicker::State::backgroundTiles || state == TilePicker::State::collidableTiles)
		{
			UpdateHoveredTilePos(mousePosRelativeToView);
		}
		


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
		{
			state = State::backgroundTiles;
			_curSelector = _backgroundSpritesheetList[0];

			//RepositionWindows();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
		{
			state = State::collidableTiles;
			_curSelector = _collidablesSpritesheetList[0];

			//RepositionWindows();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
		{
			state = State::units;
			//RepositionWindows();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4))
		{
			state = State::obstacles;
			//RepositionWindows();
		}
		//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4))
		//{
		//	state = State::props;
		//	RepositionWindows();
		//}

		SelectorItem curItem = GetSelectorItem();

		switch (state)
		{
			case State::backgroundTiles:
				break;
			case State::collidableTiles:
				break;
			case State::units:
				_hoveredTile.setSize(curItem.rect.getSize());
				_hoveredTile.setPosition(curItem.rect.getPosition() + _zeroPixel);
				break;
			case State::obstacles:
				break;
			case State::props:
				break;
			default:
				std::cout << "CURRENT TILEPICKER STATE UNASSIGNED" << std::endl;
		}


	}

	UpdateState();
}

void TilePicker::Draw()
{

	_data->GameWindow.draw(_selectorWindow);

	switch (state)
	{
	case State::backgroundTiles:		
		_data->GameWindow.draw(_curSelector);
		break;
	case State::collidableTiles:
		_data->GameWindow.draw(_curSelector);
		break;
	case State::units:
		for (int i = 0; i < _unitList.size(); i++)
		{
			_data->GameWindow.draw(_unitList[i].rect);
		}
		break;
	case State::obstacles:
		for (int i = 0; i < _obstacleList.size(); i++)
		{
			_data->GameWindow.draw(_obstacleList[i].rect);
		}
		break;
	//case State::props:
	//	_selector.setTexture(_data->assetManager.GetTexture("Props"));
	//	break;

	}

	_data->GameWindow.draw(_hoveredTile);
	_data->GameWindow.draw(_activeTile);
}

sf::IntRect TilePicker::GetTileRect()
{
	sf::IntRect texRect = sf::IntRect(320, 0, TILE_SCALE * TILE_SIZE, TILE_SCALE * TILE_SIZE);

	if (_curSelector.getGlobalBounds().contains(_data->GameWindow.mapPixelToCoords(sf::Mouse::getPosition(_data->GameWindow))))
	{
		//sf::Vector2i tilePosI = _data->GameWindow.mapCoordsToPixel(_hoveredTile.getPosition());
		sf::Vector2i tilePosI = sf::Vector2i(_hoveredTile.getPosition());
		

		sf::Vector2f tilePos = sf::Vector2f(tilePosI.x, tilePosI.y);

		tilePos -= _curSelector.getPosition();

		texRect.left = tilePos.x;
		texRect.top = tilePos.y;
		texRect.width = TILE_SCALE * TILE_SIZE;
		texRect.height = TILE_SCALE * TILE_SIZE;

		_activeTile.setPosition(tilePos + _zeroPixel);
	}

	return texRect;
}

void TilePicker::Activate()
{
	active = true;
	_activeTile.setPosition(_activeTile.getPosition() + _curSelector.getPosition());

	//RepositionWindows();
}

void TilePicker::Deactivate()
{
	active = false;
}

bool TilePicker::isMouseInPicker()
{
	sf::Sprite curSelector;

	bool out = _curSelector.getGlobalBounds().contains(_data->GameWindow.mapPixelToCoords(sf::Mouse::getPosition(_data->GameWindow)));
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
	alarmPig.rect.setPosition(sf::Vector2f(0, 0));

	alarmPig.texture = &_data->assetManager.GetTexture("AlarmPig");
	alarmPig.rect.setFillColor(sf::Color::White);
	alarmPig.rect.setOutlineColor(sf::Color::Black);
	alarmPig.rect.setOutlineThickness(1.0f);

	SelectorItem baldy;
	baldy.rect.setTexture(&_data->assetManager.GetTexture("Baldy"));
	baldy.rect.setSize(sf::Vector2f(32, 64));
	baldy.type = static_cast<int>(Agent::Type::baldy);
	baldy.rect.setPosition(sf::Vector2f(32, 0));

	baldy.texture = &_data->assetManager.GetTexture("Baldy");
	baldy.rect.setFillColor(sf::Color::White);
	baldy.rect.setOutlineColor(sf::Color::Black);
	baldy.rect.setOutlineThickness(1.0f);

	_obstacleList.push_back(box);
	_obstacleList.push_back(spike);

	_unitList.push_back(alarmPig);
	_unitList.push_back(baldy);
}

TilePicker::SelectorItem TilePicker::GetSelectorItem()
{
	TilePicker::SelectorItem selectorItem;
	sf::Vector2f mousePosRelativeToView = _data->GameWindow.mapPixelToCoords(sf::Mouse::getPosition(_data->GameWindow));

	switch (state)
	{
		case State::units:
			if (_selectorWindow.getGlobalBounds().contains(mousePosRelativeToView))
				for (int i = 0; i < _unitList.size(); i++)
					if (_unitList[i].rect.getGlobalBounds().contains(mousePosRelativeToView))
					{
						selectorItem = _unitList[i];
						std::cout << "Item = " << selectorItem.type << std::endl;
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

void TilePicker::SetActiveTileSizePos(sf::Vector2f pos, sf::Vector2f size)
{
	_activeTile.setPosition(pos + _zeroPixel);
	_activeTile.setSize(size);
}

void TilePicker::RepositionToCorner()
{
	_zeroPixel = _data->GameWindow.mapPixelToCoords(sf::Vector2i(0, 0));

	//SetActiveTileSizePos(GetSelectorItem().rect.getPosition(), GetSelectorItem().rect.getSize());
}

//void TilePicker::RepositionWindows()
//{
//	switch (state)
//	{
//		case State::shipTiles:
//			_selectorWindow.setSize(sf::Vector2f(_data->assetManager.GetTexture("Tiles").getSize()));
//			break;
//		case State::units:
//			for (int i = 0; i < _unitList.size(); i++)
//				_unitList[i].rect.setPosition(_selector.getPosition().x + (i * 32), _selector.getPosition().y + ((i / 10) * 32));
//			_selectorWindow.setSize(sf::Vector2f(std::min(static_cast<int>(_unitList.size()), 10) * 32, ((static_cast<int>(_unitList.size()) / 10) + 1) * 32));
//			break;
//		case State::obstacles:
//			for (int i = 0; i < _obstacleList.size(); i++)
//				_obstacleList[i].rect.setPosition(_selector.getPosition().x + (i * 32), _selector.getPosition().y + ((i / 10) * 32));
//			_selectorWindow.setSize(sf::Vector2f(std::min(static_cast<int>(_obstacleList.size()), 10) * 32, (static_cast<int>((_obstacleList.size()) / 10) + 1) * 32));
//			break;
//	}
//
//	_selector.setTextureRect(sf::IntRect(0, 0, _selectorWindow.getSize().x, _selectorWindow.getSize().y));
//}

void TilePicker::UpdateHoveredTilePos(sf::Vector2f mousePos)
{
	if (_curSelector.getGlobalBounds().contains(mousePos))
	{
		sf::Vector2f newPos = mousePos;

		////Offsets based on the mouse position 
		if (mousePos.x > 0)
		{
			if(_curSelector.getPosition().x > 0)
				newPos.x -= std::fmodf(mousePos.x - std::fmodf(_curSelector.getPosition().x, TILE_SIZE), TILE_SIZE);
			else
				newPos.x -= std::fmodf(mousePos.x - std::fmodf(_curSelector.getPosition().x, -TILE_SIZE), TILE_SIZE);
		}
		else
		{
			if (_curSelector.getPosition().x > 0)
				newPos.x -= std::fmodf(mousePos.x - std::fmodf(_curSelector.getPosition().x, TILE_SIZE), -TILE_SIZE) + TILE_SIZE;
			else
				newPos.x -= std::fmodf(mousePos.x - std::fmodf(_curSelector.getPosition().x, -TILE_SIZE), -TILE_SIZE) + TILE_SIZE;
		}

		if (mousePos.y > 0)
		{
			if (_curSelector.getPosition().y > 0)
				newPos.y -= std::fmodf(mousePos.y - std::fmodf(_curSelector.getPosition().y, TILE_SIZE), TILE_SIZE);
			else
				newPos.y -= std::fmodf(mousePos.y - std::fmodf(_curSelector.getPosition().y, -TILE_SIZE), TILE_SIZE);
		}
		else
		{
			if (_curSelector.getPosition().y > 0)
				newPos.y -= std::fmodf(mousePos.y - std::fmodf(_curSelector.getPosition().y, TILE_SIZE), -TILE_SIZE) + TILE_SIZE;
			else
				newPos.y -= std::fmodf(mousePos.y - std::fmodf(_curSelector.getPosition().y, -TILE_SIZE), -TILE_SIZE) + TILE_SIZE;
		}

		_hoveredTile.setPosition(newPos);
	}
}

void TilePicker::InitSheet(std::string texName, bool isCol)
{
	sf::Sprite sheet;
	sheet.setTexture(_data->assetManager.GetTexture(texName));
	sheet.setPosition(sf::Vector2f(0.0f, 0.0f) + _zeroPixel);

	if (isCol)
	{
		_collidablesSpritesheetList.push_back(sheet);
	}
	else if (!isCol)
	{
		_backgroundSpritesheetList.push_back(sheet);
	}

}