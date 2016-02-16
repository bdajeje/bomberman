#include "bomberman.hpp"

#include <iostream>

#include "managers/texturemanager.hpp"

namespace model {

BomberMan::BomberMan(const std::string& name, const std::string& logo, Position<float> position, std::shared_ptr<Map>& map)
  : _name{name}
  , _logo_name{logo}
  , _map{map}
{
  _textures.emplace(Texture::Left, texture::TextureManager::get("player_left.png"));
  _textures.emplace(Texture::Right, texture::TextureManager::get("player_right.png"));
  _textures.emplace(Texture::Top, texture::TextureManager::get("player_top.png"));
  _textures.emplace(Texture::Bottom, texture::TextureManager::get("player.png"));

  setCurrentTexture(Texture::Bottom);
  utils::graphics::resize(_sprite, Map::_tile_size, Map::_tile_size);

  updatePosition(position);
}

BomberMan::~BomberMan()
{

}

void BomberMan::setCurrentTexture(Texture texture)
{
   _sprite.setTexture( _textures.at(texture) );
}

void BomberMan::updatePosition(const Position<float>& position)
{
  _position = position;
  _sprite.setPosition(_position.x - Map::_tile_size / 2, _position.y - Map::_tile_size / 2);
}

void BomberMan::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(_sprite, states);
}

void BomberMan::setDirection(utils::graphics::Direction direction)
{
  _direction = direction;
  setCurrentTexture( directionToTexture(direction) );
}

BomberMan::Texture BomberMan::directionToTexture(utils::graphics::Direction direction)
{
  switch(direction)
  {
    case utils::graphics::Direction::Left: return Texture::Left;
    case utils::graphics::Direction::Right: return Texture::Right;
    case utils::graphics::Direction::Top: return Texture::Top;
    case utils::graphics::Direction::Bottom: return Texture::Bottom;
    default: return Texture::Bottom;
  }
}

void BomberMan::update(const sf::Time& elapsed_time)
{
  // Update position
  movementUpdate(elapsed_time);
}

void BomberMan::movementUpdate(const sf::Time& elapsed_time)
{
  if(_is_moving)
  {
    Position<float> future_position = findFuturePosition(elapsed_time);

    if( _map->isAllowedPosition(future_position, _sprite_size) )
    {
      updatePosition(future_position);
      Tile& tile = _map->getTile(future_position);
      const std::unique_ptr<Bonus>& bonus = tile.getBonus();
      if( bonus )
      {
        bonus->playerPickUp(*this);
        tile.removeBonus();
      }
    }
  }
}

Position<float> BomberMan::findFuturePosition(const sf::Time& elapsed_time) const
{
  using namespace utils::graphics;

  short factor_x = 0;
  short factor_y = 0;
  switch(_direction)
  {
    case Direction::Left: factor_x = -1; break;
    case Direction::Right: factor_x = 1; break;
    case Direction::Top: factor_y = -1; break;
    case Direction::Bottom: factor_y = 1; break;
  }

  float x_movement = findDistance(elapsed_time, _movement_speed) * factor_x;
  float y_movement = findDistance(elapsed_time, _movement_speed) * factor_y;
  return { _position.x + x_movement, _position.y + y_movement };
}

void BomberMan::raiseSpeed()
{
  _movement_speed += 0.05;
}

void BomberMan::raisePower()
{
  _bomb_power++;
}

void BomberMan::raiseAvailableBombs()
{
  _available_bombs++;
}

void BomberMan::raiseNbrBombs()
{
  if( _available_bombs < 4 )
    _available_bombs++;
}

std::shared_ptr<Bomb> BomberMan::dropBomb()
{
  if( _available_bombs == 0 )
    return nullptr;

  _available_bombs--;
  Position<float> position = _map->getTileCenterPosition(_position);
  return std::make_shared<Bomb>( shared_from_this(), _bomb_power, position );
}

}
