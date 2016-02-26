#ifndef GAME_HPP
#define GAME_HPP

#include <memory>

#include "utils/timer.hpp"
#include "models/bomberman.hpp"
#include "models/map.hpp"

namespace model {

class Game final
{
  public:

    static std::unique_ptr<Game>& reset(std::shared_ptr<Map>& map, std::vector<std::shared_ptr<model::BomberMan>>& players);
    static std::unique_ptr<Game>& instance() { return _instance; }

  private:

    Game(std::shared_ptr<Map>& map, std::vector<std::shared_ptr<model::BomberMan>>& players);

  public:

    utils::time::Timer _timer;
    std::shared_ptr<Map> _map;
    std::vector<std::shared_ptr<model::BomberMan>> _players;

  private:

    static std::unique_ptr<Game> _instance;
};

}

#endif // GAME_HPP
