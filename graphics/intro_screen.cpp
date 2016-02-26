#include "intro_screen.hpp"

#include <iostream>

#include "managers/texturemanager.hpp"
#include "utils/graphics.hpp"
#include "utils/timer.hpp"

namespace graphics {

IntroScreen::IntroScreen(sf::RenderWindow& window, const std::string& texture_filename, uint display_time)
  :_window {window}
  , _display_time {display_time}
{
  _background.setTexture( texture::TextureManager::get(texture_filename + ".png") );
  utils::graphics::resize(_background, _window.getSize().x, _window.getSize().y);
}

void IntroScreen::run()
{
  utils::time::Timer timer;
  timer.start();

  while(_window.isOpen())
  {
    // Quit when no more time
    if( timer.getElapsedTime().asMilliseconds() >= _display_time )
      return;

    sf::Event event;
    while(_window.pollEvent(event))
    {
      #pragma GCC diagnostic push
      #pragma GCC diagnostic ignored "-Wswitch"
      switch(event.type)
      {
        case sf::Event::Closed:
        {
          _window.close();
          break;
        }
        case sf::Event::KeyPressed:
        {
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            return;
        }
      }
      #pragma GCC diagnostic pop
    }

    update( timer.getElapsedTime() );

    _window.clear();
    _window.draw( _background );
    _window.display();
  }
}

void IntroScreen::update(const sf::Time& elapsed_time)
{
  // Cut total time in three equal sections
  const int effect_time = _display_time / 3;

  if( elapsed_time.asMilliseconds() <= effect_time ||
      elapsed_time.asMilliseconds() > effect_time * 2 )
  {
    const float effect_ratio = static_cast<float>(elapsed_time.asMilliseconds()) / effect_time;
    sf::Uint8 transparency = effect_ratio * 255;

    // When fade in
    if( elapsed_time.asMilliseconds() <= effect_time )
      _background.setColor( sf::Color{255, 255, 255, transparency} );
    // When fade out
    else if( elapsed_time.asMilliseconds() > effect_time * 2 )
      _background.setColor( sf::Color{255, 255, 255, 255 - transparency} );
  }
}

}
