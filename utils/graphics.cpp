#include "utils/graphics.hpp"

#include <iostream>

namespace utils {
namespace graphics{

void resize(sf::Sprite& sprite, float x, float y)
{
  sprite.setScale( x / sprite.getGlobalBounds().width,
                   y / sprite.getGlobalBounds().height );
}

void setCenterOrigin(sf::Sprite& sprite)
{
  const sf::FloatRect& bounds = sprite.getGlobalBounds();
  sprite.setOrigin( bounds.width / 2, bounds.height / 2 );
}

float findDistance(const sf::Time& elapsed_time, float speed)
{
  return speed * elapsed_time.asMilliseconds();
}

}
}
