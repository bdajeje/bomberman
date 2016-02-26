#include "game.hpp"

#include <SFML/Audio/Sound.hpp>

#include "defines.hpp"
#include "utils/graphics.hpp"
#include "models/ia.hpp"
#include "managers/soundmanager.hpp"

namespace model {

std::unique_ptr<Game> Game::_instance;

std::unique_ptr<Game>& Game::reset(sf::RenderWindow& window, const std::string& map_name)
{
  _instance.reset( new Game(window, map_name) );
  return _instance;
}

Game::Game(sf::RenderWindow& window, const std::string& map_name)
  : _window {window}
  , _game_remaining_time { std::make_shared<sf::Time>(sf::seconds(120)) }
  , _game_view { {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT} }
  , _hud_view { {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT} }
{
  // Create map
  _map = std::make_shared<model::Map>(map_name, _game_remaining_time);

  // Create player
  _player = std::make_shared<model::Player>("1", "player_logo", _map->getPlayerStartingPosition(1), _map);
  _players.push_back(_player);

  // Create IAs
  for(unsigned short i = 1; i < _map->getTotalPlayers(); ++i)
  {
    std::shared_ptr<model::IA> ia = std::make_shared<model::IA>("AI " + std::to_string(i), "player_logo", _map->getPlayerStartingPosition(i+1), _map);
    _players.push_back( ia );
  }

  // Create HUD
  _hud = std::make_shared<graphics::HUD>(_players, _game_remaining_time);

  // Move game view after HUD
  _game_view.move(0, -HUD_HEIGHT);
}

void Game::start()
{
  sf::Time last_update {sf::Time::Zero};
  _timer.start();

  sf::Sound sound {sound::SoundManager::get("game_start.wav")};
  sound.play();

  while(_window.isOpen())
  {
    handleEvents();

    // Get elapsed time since last update
    const sf::Time elapsed_time = _timer.getElapsedTime() - last_update;
    *_game_remaining_time -= elapsed_time;

    // Update elements
    update( elapsed_time );

    // Save last update time
    last_update = _timer.getElapsedTime();

    // Draw everything
    draw();
  }
}

void Game::handleEvents()
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
      case sf::Event::KeyReleased:
      {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
          _player->setDirection( utils::graphics::Direction::Top );
          _player->setMoving(true);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
          _player->setDirection( utils::graphics::Direction::Bottom );
          _player->setMoving(true);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
          _player->setDirection( utils::graphics::Direction::Left );
          _player->setMoving(true);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
          _player->setDirection( utils::graphics::Direction::Right );
          _player->setMoving(true);
        }
        else _player->setMoving(false);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
          std::shared_ptr<model::Bomb> bomb = _player->dropBomb();
          if(bomb)
            _bombs.push_back(bomb);
        }
      }
    }
    #pragma GCC diagnostic pop
  }
}

void Game::update(const sf::Time& elapsed_time)
{
  // HUD
  _hud->update(elapsed_time);

  // Map
  _map->update(elapsed_time);

  // Players
  for(std::shared_ptr<model::BomberMan>& player : _players)
    player->update(elapsed_time);

  // Update bombs
  for(size_t i = 0; i < _bombs.size(); ++i)
  {
    std::shared_ptr<model::Bomb>& bomb = _bombs[i];
    bomb->update(elapsed_time);
    if( bomb->isExploded() )
    {
      std::vector<std::shared_ptr<model::Tile>> exploded_tiles = _map->bombExplose(bomb->position(), bomb->power());
      _bombs.erase(_bombs.begin() + i);

      // If a player stands on one of those tiles, well that player is dead
      for( std::shared_ptr<model::BomberMan>& player : _players )
      {
        if( player->isDead() )
          continue;

        const std::shared_ptr<model::Tile>& player_tile = _map->getTile( player->getPosition() );
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
}

void Game::draw() const
{
  _window.clear();

  _window.setView(_game_view);
  _window.draw(*_map.get());

  for(const std::shared_ptr<model::Bomb>& bomb : _bombs)
    _window.draw(*bomb.get());

  for(const std::shared_ptr<model::BomberMan>& player : _players)
    _window.draw(*player);

  _window.setView(_hud_view);
  _window.draw(*_hud);


}

}
