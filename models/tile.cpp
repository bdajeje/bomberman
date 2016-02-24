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

Tile::Tile(const std::string& texture_name, bool blockable, bool breakable, const Position<float>& position)
  : _blockable{blockable}
  , _breakable{breakable}
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

  if(_incoming_block_of_death_shadow_animation)
    target.draw(*_incoming_block_of_death_shadow_animation, states);
}

void Tile::update(const sf::Time& elapsed_time)
{
  if(_explosion_animation)
  {
    _explosion_animation->update(elapsed_time);
    if(_explosion_animation->finished())
      _explosion_animation.release();
  }

  // Block of death animations
  if(_incoming_block_of_death_shadow_animation)
  {
    _incoming_block_of_death_shadow_animation->update(elapsed_time);

    if(_incoming_block_of_death_shadow_animation->finished())
    {
      _incoming_block_of_death_shadow_animation.release();

      // \todo then start incoming block animation, but I guess this should be an effect runned an a sprite to make the move from air to ground
      // for now simply put a unbreackable block instead
      _blockable = true;
      _breakable = false;
      _sprite.setTexture( texture::TextureManager::get("block_border.png") );
    }
  }
}

void Tile::exploses(const std::string& animation)
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

bool Tile::isBlockOfDeathIncoming() const
{
  return _incoming_block_of_death_shadow_animation != nullptr ||
         _incoming_block_of_death_animation != nullptr;
}

void Tile::blockOfDeathIncoming()
{
  _incoming_block_of_death_shadow_animation.reset( new graphics::Animation("block_of_death_shadow", _position, Map::_tile_size, Map::_tile_size, 16, 16) );
  _incoming_block_of_death_shadow_animation->start(200, false);
}

}
