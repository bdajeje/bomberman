#include <iostream>
#include <stdlib.h>

#include <SFML/Graphics.hpp>

#include "defines.hpp"
#include "utils/graphics.hpp"
#include "managers/texturemanager.hpp"
#include "managers/fontmanager.hpp"
#include "managers/soundmanager.hpp"
#include "models/game.hpp"
#include "graphics/main_menu.hpp"

int main()
{
  // Creat window
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Bomber Man");
  window.setFramerateLimit(60);  

  // Set window icon (not working I don't know why...)
  {
    sf::Image icon;
    if(!icon.loadFromFile("resources/icon.png"))
    {
      std::cerr << "Error while loading application icon" << std::endl;
      return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
  }

  texture::TextureManager::init("resources/textures/");
  font::FontManager::init("resources/fonts/");
  sound::SoundManager::init("resources/sounds/");

  srand(time(NULL));

  // Create menu
  graphics::MainMenu main_menu {window};
  switch( main_menu.run() )
  {
    case graphics::MainMenu::Action::NewGame:
    {
      // Start game
      std::unique_ptr<model::Game>& game = model::Game::reset(window, "1");
      game->start();
      break;
    }
    case graphics::MainMenu::Action::Quit: break;
  }

  return EXIT_SUCCESS;
}
