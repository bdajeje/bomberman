#ifndef GAME_HPP
#define GAME_HPP

#include <memory>

#include <SFML/Graphics.hpp>

#include "utils/timer.hpp"
#include "models/bomberman.hpp"
#include "models/map.hpp"
#include "models/bomb.hpp"
#include "graphics/hud.hpp"
#include "models/player.hpp"

namespace model {

class Game final
{
  public:

    static std::unique_ptr<Game>& reset(sf::RenderWindow& window, const std::__cxx11::string& map_name);
    static std::unique_ptr<Game>& instance() { return _instance; }

    void start();

  private:

    Game(sf::RenderWindow& window, const std::__cxx11::string& map_name);
    void draw() const;
    void handleEvents();
    void update(const sf::Time& elapsed_time);

  public:

    utils::time::Timer _timer;
    sf::RenderWindow& _window;
    std::shared_ptr<sf::Time> _game_remaining_time;
    sf::View _game_view;
    sf::View _hud_view;
    std::shared_ptr<Map> _map;
    std::shared_ptr<model::Player> _player;
    std::vector<std::shared_ptr<model::BomberMan>> _players;
    std::vector<std::shared_ptr<model::Bomb>> _bombs;
    std::shared_ptr<graphics::HUD> _hud;

  private:

    static std::unique_ptr<Game> _instance;
};

}

#endif // GAME_HPP
