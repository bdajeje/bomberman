#include "intro_screen.hpp"

#include "managers/texturemanager.hpp"
#include "utils/graphics.hpp"

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
  while(_window.isOpen())
  {
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
          return;
        }
      }
      #pragma GCC diagnostic pop
    }

    _window.clear();
    _window.draw( _background );
    _window.display();
  }
}

}
