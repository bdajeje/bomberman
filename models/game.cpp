#include "game.hpp"

namespace model {

std::unique_ptr<Game> Game::_instance;

std::unique_ptr<Game>& Game::reset(std::shared_ptr<Map>& map, std::vector<std::shared_ptr<model::BomberMan>>& players)
{
  _instance.reset( new Game(map, players) );
  return _instance;
}

Game::Game(std::shared_ptr<Map>& map, std::vector<std::shared_ptr<model::BomberMan>>& players)
  : _map {map}
  , _players {players}
{
  _timer.start();
}

}
