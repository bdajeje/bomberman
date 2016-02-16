#include "tile.hpp"

#include <iostream>

#include "managers/texturemanager.hpp"
#include "utils/graphics.hpp"
#include "models/map.hpp"
#include "models/bonuskick.hpp"
#include "models/bonuspower.hpp"
#include "models/bonusspeed.hpp"
#include "models/bonusthrow.hpp"
#include "models/bonusbomb.hpp"

namespace model {

Tile::Tile(const std::string& texture_name, bool blockable, const Position<float>& position)
  : _blockable{blockable}
  , _position{position}
{
  _sprite.setPosition(position.x, position.y);
  _sprite.setTexture( texture::TextureManager::get(texture_name + ".png") );
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(_sprite, states);

  if( _bonus )
    target.draw(*_bonus, states);

  if(_explosion_animation)
    target.draw(*_explosion_animation, states);
}

void Tile::update(const sf::Time& elapsed_time)
{
  if(_explosion_animation)
  {
    _explosion_animation->update(elapsed_time);
    if(_explosion_animation->finished())
      _explosion_animation.release();
  }
}

void Tile::exploses(const std::__cxx11::string& animation)
{
  // Tile was blockable? Well no more now
  if(_blockable)
  {
    createBonus();
    _sprite.setTexture( texture::TextureManager::get("path.png") );
    _blockable = false;
  }

  _explosion_animation.reset( new graphics::Animation(animation, _position, Map::_tile_size, Map::_tile_size, 16, 16) );

  // Start explosion animation
  _explosion_animation->start(70, false);  
}

void Tile::createBonus()
{
  if(hasBonus())
    return;

  int random = rand() % 100 + 0;
  if( _bonus_chance < random )
    return;

  const static std::vector<bonus::Type> bonuses = {
    bonus::Type::Power,
    bonus::Type::Kick,
    bonus::Type::Speed,
    bonus::Type::Throw,
    bonus::Type::Bomb
  };

  // Randomly choose a bonus
  bonus::Type type = bonuses[rand() % bonuses.size()];

  // Create bonus
  switch(type)
  {
    case bonus::Type::Power: _bonus.reset( new BonusPower(_position) ); break;
    case bonus::Type::Kick:  _bonus.reset( new BonusKick(_position) ); break;
    case bonus::Type::Speed: _bonus.reset( new BonusSpeed(_position) ); break;
    case bonus::Type::Throw: _bonus.reset( new BonusThrow(_position) ); break;
    case bonus::Type::Bomb:  _bonus.reset( new BonusBomb(_position) ); break;
  }
}

}
