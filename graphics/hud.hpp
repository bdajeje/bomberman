#ifndef HUD_HPP
#define HUD_HPP

#include <SFML/Graphics.hpp>

#include "models/bomberman.hpp"

namespace graphics {

class HUD;

class HUDPlayer final : public sf::Drawable
{
  friend class HUD;

  public:

    HUDPlayer(const std::shared_ptr<model::BomberMan>& player, Position<float> position);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  private:

    sf::Sprite _player_logo;
    sf::Text _name;
    sf::Sprite _bombs;
    sf::Text _bombs_number;
    sf::Sprite _power;
    sf::Text _power_number;
    std::unique_ptr<sf::Sprite> _throw_bomb;
    std::unique_ptr<sf::Sprite> _kick_bomb;
};

class HUD final : public sf::Drawable
{
  public:

    HUD(const std::vector<std::shared_ptr<model::BomberMan>>& players, const sf::Time& remaining_time);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update(const sf::Time& remaining_time);

  private:

    void setRemainingTime(const sf::Time& remaining_time);

  private:

    std::vector<std::shared_ptr<model::BomberMan>> _players;
    std::vector<HUDPlayer> _player_informations;
    sf::Text _remaining_time;
};

}

#endif // HUD_HPP
