#ifndef HUD_HPP
#define HUD_HPP

#include <SFML/Graphics.hpp>

#include "models/bomberman.hpp"
#include "utils/time_trigger.hpp"

namespace graphics {

class HUD;

class HUDPlayer final : public sf::Drawable
{
  friend class HUD;

  public:

    HUDPlayer(const std::shared_ptr<model::BomberMan>& player, Position<float> position);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  private:

    std::shared_ptr<model::BomberMan> _player;
    sf::Sprite _player_logo;
    sf::Text _name;
    sf::Sprite _bombs;
    sf::Text _bombs_number;
    sf::Sprite _power;
    sf::Text _power_number;
    sf::Sprite _throw_bomb;
    sf::Sprite _kick_bomb;
    sf::Text _dead_text;
};

class HUD final : public sf::Drawable
{
  public:

    HUD(const std::vector<std::shared_ptr<model::BomberMan>>& players, const std::shared_ptr<sf::Time>& game_remaining_time);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update(const sf::Time& elapsed_time);

  private:

    void updateRemainingTime();

  private:

    std::vector<std::shared_ptr<model::BomberMan>> _players;
    std::shared_ptr<sf::Time> _game_remaining_time;
    std::vector<HUDPlayer> _player_informations;
    sf::View _view;
    bool _draw_remaining_time {true};
    sf::Text _remaining_time;
    std::unique_ptr<utils::TimeTrigger> _end_blinking_trigger;
};

}

#endif // HUD_HPP
