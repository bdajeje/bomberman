#ifndef UTILS_GRAPHICS_HPP
#define UTILS_GRAPHICS_HPP

#include <SFML/Graphics.hpp>

namespace utils {
namespace graphics{

enum class Direction
{
  Top, Bottom, Left, Right
};

void resize(sf::Sprite& sprite, float x, float y);

/*! Set origin of sprite in the center of it */
void setCenterOrigin(sf::Sprite& sprite);

// Speed in pixels/millisecond
float findDistance(const sf::Time& elapsed_time, float speed);

}
}

#endif // UTILS_GRAPHICS_HPP

