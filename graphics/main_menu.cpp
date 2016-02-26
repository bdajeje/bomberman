#include "main_menu.hpp"

#include <iostream>

#include <SFML/Audio/Sound.hpp>

#include "managers/fontmanager.hpp"
#include "managers/texturemanager.hpp"
#include "managers/soundmanager.hpp"
#include "utils/graphics.hpp"

namespace graphics {

MainMenu::MainMenu(sf::RenderWindow& window)
  : _window {window}
  , _key_limitor { 250 }
{
  const sf::Font& font = font::FontManager::get("consolas.ttf");

  _play_text.setString("Play");
  _options_text.setString("Options");
  _quit_text.setString("Quit");

  std::vector<sf::Text*> texts = {&_play_text, &_options_text, &_quit_text};
  for( sf::Text* text : texts )
  {
    text->setFont(font);
    text->setCharacterSize(25);
    utils::graphics::honrizontalCenter( *text, _window.getSize().x );
    text->setPosition( text->getPosition().x, text->getPosition().y );
  }

  utils::graphics::verticalCenter(texts, _window.getSize().y / 2, _window.getSize().y / 4);

  _background.setTexture( texture::TextureManager::get("main_menu_background.png") );
  utils::graphics::positionBottomRight( _background, _window.getSize().x, _window.getSize().y );

  _bomb_icon.setTexture( texture::TextureManager::get("main_menu_bomb_icon.png") );
  utils::graphics::resize(_bomb_icon, 20, 20);

  _menu_items.reserve(3);
  _menu_items.push_back( &_play_text );
  _menu_items.push_back( &_options_text );
  _menu_items.push_back( &_quit_text );

  setSelectedMenuItem( 0, false );
}

MainMenu::Action MainMenu::run()
{
  while(_window.isOpen())
  {
    Action action = handleEvents();
    if( action != Action::None )
      return action;

    draw();
  }

  return Action::Quit;
}

MainMenu::Action MainMenu::handleEvents()
{
  sf::Event event;
  while(_window.pollEvent(event))
  {
    // Remove compiler warnings about enumeration value not handled in switch
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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && _key_limitor.isAllow(sf::Keyboard::Up))
          setSelectedMenuItem(--_selected_menu_item, true);
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && _key_limitor.isAllow(sf::Keyboard::Down))
          setSelectedMenuItem(++_selected_menu_item, true);
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
          return selectCurrentMenuItem();

        break;
      }
    }
    #pragma GCC diagnostic pop
  }

  return Action::None;
}

void MainMenu::draw()
{
  _window.clear(sf::Color{167, 194, 153});

  _window.draw( _background );
  _window.draw( _play_text );
  _window.draw( _options_text );
  _window.draw( _quit_text );
  _window.draw( _bomb_icon );

  _window.display();
}

void MainMenu::setSelectedMenuItem( int offset, bool play_sound )
{
  if(offset >= static_cast<int>(_menu_items.size()))
    offset = 0;
  else if(offset < 0)
    offset = _menu_items.size() - 1;

  _selected_menu_item = offset;

  for( size_t i = 0; i < _menu_items.size(); ++i )
  {
    sf::Text* menu_item = _menu_items[i];

    if( static_cast<int>(i) == _selected_menu_item )
    {
      menu_item->setColor( _selected_menu_item_color );
      _bomb_icon.setPosition( menu_item->getPosition().x - _bomb_icon.getGlobalBounds().width - 15, menu_item->getPosition().y + ( menu_item->getGlobalBounds().height - _bomb_icon.getGlobalBounds().height) );
    }
    else
      menu_item->setColor( _menu_item_color );
  }

  if(play_sound)
  {
    static sf::Sound sound {sound::SoundManager::get("change_menu_item.wav")};
    sound.play();
  }
}

MainMenu::Action MainMenu::selectCurrentMenuItem()
{
  switch( _selected_menu_item )
  {
    case 0: return Action::NewGame;
    case 1: return Action::Options;
    case 2: return Action::Quit;
  }

  return Action::None;
}

}
