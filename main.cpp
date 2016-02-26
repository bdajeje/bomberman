#include <iostream>
#include <stdlib.h>

#include <SFML/Graphics.hpp>
#include <SFML/Audio/Sound.hpp>

#include "defines.hpp"
#include "utils/graphics.hpp"
#include "managers/texturemanager.hpp"
#include "managers/fontmanager.hpp"
#include "managers/soundmanager.hpp"
#include "models/game.hpp"
#include "models/map.hpp"
#include "models/player.hpp"
#include "models/ia.hpp"
#include "models/bomb.hpp"
#include "graphics/hud.hpp"

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

  std::shared_ptr<sf::Time> game_remaining_time = std::make_shared<sf::Time>(sf::seconds(120));
  std::vector<std::shared_ptr<model::BomberMan>> players;
  std::shared_ptr<model::Map> map = std::make_shared<model::Map>("1", game_remaining_time);
  std::shared_ptr<model::Player> player = std::make_shared<model::Player>("1", "player_logo", map->getPlayerStartingPosition(1), map);
  players.push_back(player);
  std::vector<std::shared_ptr<model::Bomb>> bombs;
  std::vector<std::shared_ptr<model::IA>> ias;
  for(unsigned short i = 1; i < map->getTotalPlayers(); ++i)
  {
    std::shared_ptr<model::IA> ia = std::make_shared<model::IA>("AI " + std::to_string(i), "player_logo", map->getPlayerStartingPosition(i+1), map);
    ias.push_back( ia );
    players.push_back( ia );
  }

  graphics::HUD hud {players, game_remaining_time};

  srand(time(NULL));

  sf::View game_view{ {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT} };
  game_view.move(0, -HUD_HEIGHT);
  sf::View hud_view{ {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT} };

  sf::Time last_update {sf::Time::Zero};  

  // Start game
  std::unique_ptr<model::Game>& game = model::Game::reset(map, players);
  sf::Sound sound {sound::SoundManager::get("game_start.wav")};
  sound.play();  

  while(window.isOpen())
  {
    sf::Event event;
    while(window.pollEvent(event))
    {
      // Remove compiler warnings about enumeration value not handled in switch
      #pragma GCC diagnostic push
      #pragma GCC diagnostic ignored "-Wswitch"
      switch(event.type)
      {
        case sf::Event::Closed:
        {
          window.close();
          break;
        }
        case sf::Event::KeyPressed:
        case sf::Event::KeyReleased:
        {
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
          {
            player->setDirection( utils::graphics::Direction::Top );
            player->setMoving(true);
          }
          else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
          {
            player->setDirection( utils::graphics::Direction::Bottom );
            player->setMoving(true);
          }
          else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
          {
            player->setDirection( utils::graphics::Direction::Left );
            player->setMoving(true);
          }
          else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
          {
            player->setDirection( utils::graphics::Direction::Right );
            player->setMoving(true);
          }
          else player->setMoving(false);

          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
          {
            std::shared_ptr<model::Bomb> bomb = player->dropBomb();
            if(bomb)
              bombs.push_back(bomb);
          }
        }
      }
      #pragma GCC diagnostic pop
    }

    // Get elapsed time since last update
    const sf::Time elapsed_time = game->_timer.getElapsedTime() - last_update;
    *game_remaining_time -= elapsed_time;

    // Update elements
    hud.update(elapsed_time);
    map->update(elapsed_time);
    for(std::shared_ptr<model::BomberMan>& player : players)
      player->update(elapsed_time);

    for(size_t i = 0; i < bombs.size(); ++i)
    {
      std::shared_ptr<model::Bomb>& bomb = bombs[i];
      bomb->update(elapsed_time);
      if( bomb->isExploded() )
      {
        std::vector<std::shared_ptr<model::Tile>> exploded_tiles = map->bombExplose(bomb->position(), bomb->power());
        bombs.erase(bombs.begin() + i);

        // If a player stands on one of those tiles, well that player is dead
        for( std::shared_ptr<model::BomberMan>& player : players )
        {
          if( player->isDead() )
            continue;

          const std::shared_ptr<model::Tile>& player_tile = map->getTile( player->getPosition() );
          for( const std::shared_ptr<model::Tile>& exploded_tile : exploded_tiles )
          {
            if( exploded_tile->getPosition() == player_tile->getPosition() )
            {
              player->setDead();
              break;
            }
          }
        }
      }
    }

    // Save last update time
    last_update = game->_timer.getElapsedTime();

    // Draw everything
    window.clear();
    window.setView(game_view);
    window.draw(*map.get());
    for(const std::shared_ptr<model::Bomb>& bomb : bombs)
      window.draw(*bomb.get());    
    for(const std::shared_ptr<model::BomberMan>& player : players)
      window.draw(*player);
    window.setView(hud_view);
    window.draw(hud);
    window.display();
  }

  return EXIT_SUCCESS;
}
