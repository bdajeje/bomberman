#include "utils/graphics.hpp"

namespace utils {
namespace graphics{

void resize(sf::Sprite& sprite, float x, float y)
{
  sprite.setScale( x / sprite.getGlobalBounds().width,
                   y / sprite.getGlobalBounds().height );
}

float findDistance(const sf::Time& elapsed_time, float speed)
{
  return speed * elapsed_time.asMilliseconds();
}

}
}
