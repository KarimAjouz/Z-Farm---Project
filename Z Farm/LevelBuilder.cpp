#include "LevelBuilder.h"
#include "Definitions.h"

LevelBuilder::LevelBuilder(ZEngine::GameDataRef data) :
	_data(data),
	_curSelectedTexture()
{
	_data->assetManager.LoadTexture("Tiles", TILE_PATH);
	_curSelectedTexture.setTexture(_data->assetManager.GetTexture("Tiles"));
	_curSelectedTexture.setTextureRect(_texRect);

	_curTextureOutline.setSize(sf::Vector2f(_texRect.width + 2, _texRect.height + 2));
	_curTextureOutline.setOutlineColor(sf::Color::Magenta);
	_curTextureOutline.setOutlineThickness(1);

	_hoveredTile.setSize(sf::Vector2f(_texRect.width + 2, _texRect.height + 2));
	_hoveredTile.setOutlineThickness(1);
	_hoveredTile.setOrigin(16, 16);
	_hoveredTile.setOutlineColor(sf::Color::Green);
	_hoveredTile.setFillColor(sf::Color::Transparent);
	_hoveredTile.setScale(2.0f, 2.0f);

}

LevelBuilder::~LevelBuilder()
{
}

void LevelBuilder::Update(float dT)
{
	sf::Vector2i mousePos = sf::Vector2i(sf::Mouse::getPosition(_data->window));
	_curTextureOutline.setPosition(sf::Vector2f(mousePos.x, mousePos.y - 34.0f));
	_curSelectedTexture.setPosition(sf::Vector2f(mousePos.x, mousePos.y - 33.0f));
	_hoveredTile.setPosition(sf::Vector2f((mousePos.x / 64 * 64 + 30), (mousePos.y / 64 * 64) + 30));

}

void LevelBuilder::Draw()
{
	_data->window.draw(_hoveredTile);
	_data->window.draw(_curSelectedTexture);
	_data->window.draw(_curTextureOutline);
}
