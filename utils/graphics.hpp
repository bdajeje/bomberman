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

/*! Horizontally center a text */
void honrizontalCenter(sf::Text& text, uint total_width);

/*! Vertically center texts */
void verticalCenter(const std::vector<sf::Text*>& texts, uint total_height, uint y_offset = 0);

/*! Position a spriteat the bottom right corner */
void positionBottomRight(sf::Sprite& sprite, uint width, uint height);

}
}

#endif // UTILS_GRAPHICS_HPP

