#include "options_menu.hpp"

#include "utils/timer.hpp"
#include "managers/fontmanager.hpp"
#include "utils/graphics.hpp"

namespace graphics {

OptionsMenu::OptionsMenu(sf::RenderWindow& window)
  : _window {window}
{
  const sf::Font& font = font::FontManager::get("consolas.ttf");
  _title.setFont( font );
  _title.setCharacterSize(26);
  _title.setString("OPTIONS");
  _title.setPosition( 0, 50 );
  _title.setColor(sf::Color::White);
  utils::graphics::honrizontalCenter(_title, window.getSize().y);
}

void OptionsMenu::run()
{
//  utils::time::Timer timer;
//  timer.start();

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
//          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
//            return;
        }
      }
      #pragma GCC diagnostic pop
    }

//    update( timer.getElapsedTime() );
    draw();
  }
}

void OptionsMenu::draw() const
{
  _window.clear();
  _window.draw(_title);
  _window.display();
}

}
