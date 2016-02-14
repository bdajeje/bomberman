#include <iostream>

#include <SFML/Graphics.hpp>

#include "utils/timer.hpp"
#include "utils/graphics.hpp"
#include "managers/texturemanager.hpp"
#include "models/map.hpp"
#include "models/player.hpp"
#include "models/ia.hpp"
#include "models/bomb.hpp"

int main()
{
  sf::RenderWindow window(sf::VideoMode(800, 800), "Bomber Man");
  window.setFramerateLimit(60);

  texture::TextureManager::init("resources/textures/");
  std::shared_ptr<model::Map> map = std::make_shared<model::Map>("1");
  std::shared_ptr<model::Player> player = std::make_shared<model::Player>("1", map->getPlayerStartingPosition(1), map);
  std::vector<std::shared_ptr<model::Bomb>> bombs;
  std::vector<std::shared_ptr<model::IA>> ias;
  for(unsigned short i = 1; i < map->getTotalPlayers(); ++i)
    ias.push_back( std::make_shared<model::IA>("IA " + std::to_string(i), map->getPlayerStartingPosition(i+1), map) );

  sf::Time last_update {sf::Time::Zero};
  utils::time::Timer timer;
  timer.start();

  while(window.isOpen())
  {
    sf::Event event;
    while(window.pollEvent(event))
    {
      player->setMoving(false);

      switch(event.type)
      {
        case sf::Event::Closed:
        {
          window.close();
          break;
        }
        case sf::Event::KeyPressed:
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
          else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
          {
            std::shared_ptr<model::Bomb> bomb = player->dropBomb();
            if(bomb)
              bombs.push_back(bomb);
          }
        }
      }
    }

    // Get elapsed time since last update
    const sf::Time elapsed_time = timer.getElapsedTime() - last_update;

    // Update elements
    map->update(elapsed_time);
    player->update(elapsed_time);

    for(std::shared_ptr<model::IA>& ia : ias)
      ia->update(elapsed_time);

    for(size_t i = 0; i < bombs.size(); ++i)
    {
      std::shared_ptr<model::Bomb>& bomb = bombs[i];
      bomb->update(elapsed_time);
      if( bomb->isExploded() )
      {
        map->bombExplose(bomb->position(), bomb->power());
        bombs.erase(bombs.begin() + i);
      }
    }

    // Save last update time
    last_update = timer.getElapsedTime();

    // Draw everything
    window.clear();
    window.draw(*map.get());
    for(const std::shared_ptr<model::Bomb>& bomb : bombs)
      window.draw(*bomb.get());
    window.draw(*player.get());
    for(const std::shared_ptr<model::IA>& ia : ias)
      window.draw(*ia.get());
    window.display();
  }

  return 0;
}
