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
#include "graphics/intro_screen.hpp"
#include "graphics/options_menu.hpp"

std::set<std::string> parseArgs(int argc, char** argv)
{
  std::set<std::string> args;
  for(int i = 0; i < argc; ++i)
    args.insert(argv[i]);

  return std::move(args);
}

int main(int argc, char** argv)
{
  // Parse args
  std::set<std::string> args = parseArgs(argc, argv);

  // Create window
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

  // Run intro screens
  if(args.find("--skip-intro") == args.end())
  {
    std::array<std::string, 3> intros = {"bomberman_intro_screen", "sfml_intro_screen", "developer_intro_screen"};
    for( const std::string& intro : intros )
    {
      graphics::IntroScreen bomberman_intro_screen {window, intro, 3000};
      bomberman_intro_screen.run();
    }
  }

graphics::OptionsMenu options_menu {window};
options_menu.run();

  // Create menu
  bool quit = false;
  graphics::MainMenu main_menu {window};
  while( !quit )
  {
    graphics::MainMenu::Action next_action = main_menu.run();

    switch(next_action)
    {
      case graphics::MainMenu::Action::NewGame:
      {
        // Start game
        std::unique_ptr<model::Game>& game = model::Game::reset(window, "1");
        game->start();
      }
      case graphics::MainMenu::Action::Options:
      {
        // Show options menu
        graphics::OptionsMenu options_menu {window};
        options_menu.run();
      }
      default:
      {
        quit = true;
      }
    }
  }

  return EXIT_SUCCESS;
}
