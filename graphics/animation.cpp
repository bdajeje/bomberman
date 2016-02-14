#include "animation.hpp"

#include <iostream>

#include "managers/texturemanager.hpp"

namespace graphics {

Animation::Animation(const std::string& textures_filename, const Position<float>& position,
                     unsigned int wanted_width, unsigned int wanted_height,
                     unsigned int texture_width, unsigned int texture_height)
  : _texture_width{texture_width}
  , _texture_height{texture_height}
{
  _sprite.setTexture( texture::TextureManager::get(textures_filename + ".png") );
  _sprite.setScale( static_cast<float>(wanted_width) / _texture_width,
                    static_cast<float>(wanted_height) / _texture_height );
//  std::cout << position.x << " / " << position.y << std::endl;
  _sprite.setPosition( position.x, position.y );
}

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(_sprite, states);
}

void Animation::update(const sf::Time& elapsed_time)
{
  if(finished())
    return;

  // Do we need a sprite update
  bool need_update = false;
  if( elapsed_time.asMilliseconds() - _elapsed_time >= _time_between_textures )
    need_update = true;

  _elapsed_time += elapsed_time.asMilliseconds();

  if(need_update)
    updateSprite();
}

void Animation::start(unsigned int sprite_time, bool loop)
{
  _finished = false;
  _elapsed_time = 0;
  _loop = loop;
  _time_between_textures = sprite_time;
  updateSprite();
}

void Animation::updateSprite()
{
  int texture_nbr = _elapsed_time / _time_between_textures;
  int x_offset = (texture_nbr * _texture_width) + (1 * texture_nbr);

  if(x_offset >= _sprite.getTexture()->getSize().x)
  {
    if(_loop)
    {
      _elapsed_time = 0;
      x_offset = 0;
    }
    else
      _finished = true;
  }

  _sprite.setTextureRect(sf::IntRect(x_offset, 0, _texture_width, _texture_height));
}

}
