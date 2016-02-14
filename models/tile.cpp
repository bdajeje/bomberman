#include "tile.hpp"

#include "managers/texturemanager.hpp"
#include "utils/graphics.hpp"
#include "models/map.hpp"

namespace model {

Tile::Tile(const std::string& texture_name, bool blockable, const Position<float>& position)
  : _blockable{blockable}
  , _position{position}
{
  _sprite.setPosition(position.x, position.y);
  _sprite.setTexture( texture::TextureManager::get(texture_name + ".png") );
}

Tile::~Tile()
{
  cleanExplosionAnimation();
}

void Tile::cleanExplosionAnimation()
{
  delete _explosion_animation;
  _explosion_animation = nullptr;
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(_sprite, states);

  if(_explosion_animation)
    target.draw(*_explosion_animation, states);
}

void Tile::update(const sf::Time& elapsed_time)
{
  if(_explosion_animation)
  {
    _explosion_animation->update(elapsed_time);
    if(_explosion_animation->finished())
      cleanExplosionAnimation();
  }
}

void Tile::exploses(const std::__cxx11::string& animation)
{
  // Tile was blockable? Well no more now
  if(_blockable)
  {
    _sprite.setTexture( texture::TextureManager::get("path.png") );
    _blockable = false;
  }

  cleanExplosionAnimation();
  _explosion_animation = new graphics::Animation(animation, _position, Map::_tile_size, Map::_tile_size, 16, 16);

  // Start explosion animation
  _explosion_animation->start(150, false);
}

}
