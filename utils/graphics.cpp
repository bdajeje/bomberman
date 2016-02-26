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

void honrizontalCenter(sf::Text& text, uint total_width)
{
  text.setPosition( (total_width - text.getGlobalBounds().width) / 2, text.getPosition().y );
}

void verticalCenter( const std::vector<sf::Text*>& texts, uint total_height, uint y_offset)
{
  if(texts.empty())
    return;

  const uint section_height = total_height / texts.size();
  uint y = y_offset + (section_height / 2);
  for( sf::Text* text : texts )
  {
    text->setPosition( text->getPosition().x, y );
    y += section_height;
  }
}

void positionBottomRight(sf::Sprite& sprite, uint width, uint height)
{
  const sf::FloatRect& bounds = sprite.getGlobalBounds();
  sprite.setPosition( width - bounds.width, height - bounds.height );
}

}
}
