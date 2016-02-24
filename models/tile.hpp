#ifndef TILE_HPP
#define TILE_HPP

#include <string>

#include <SFML/Graphics.hpp>

#include "utils/position.hpp"
#include "graphics/animation.hpp"
#include "models/bonus.hpp"
#include "models/bonus_types.hpp"

namespace model {

class Map;
class Bonus;

class Tile final
{
  public:

    Tile(const std::string& texture_name, bool blockable, bool breakable, const Position<float>& position);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update(const sf::Time& elapsed_time);

    void exploses(const std::string& animation);

    /*! Update the tile to mark it with an incoming block of death
     *  Block of death animation starts, soon a new unbrakable block
     *  will land on this tile and the tile will become blockable.
     */
    void blockOfDeathIncoming();

    bool isBlocking() const { return _blockable; }
    bool isBreakable() const { return _breakable; }
    bool isBlockOfDeathIncoming() const;
    const Position<float>& getPosition() const { return _position; }

    bool hasBonus() const { return _bonus.get() != nullptr; }
    void removeBonus() { _bonus.release(); }
    const std::unique_ptr<Bonus>& getBonus() const { return _bonus; }

  private:

    // Chance to get a bonus when exploding a block (in percentage)
    static constexpr unsigned short _bonus_chance {20};

    void createBonus();

  private:

    bool _blockable;
    bool _breakable;
    Position<float> _position;
    sf::Sprite _sprite;
    std::unique_ptr<graphics::Animation> _explosion_animation;
    std::unique_ptr<Bonus> _bonus;

    /*! Animation of the growing shadow of an incoming block of death */
    std::unique_ptr<graphics::Animation> _incoming_block_of_death_shadow_animation;

    /*! Animation of the block of death incoming onto the tile */
    std::unique_ptr<graphics::Animation> _incoming_block_of_death_animation;
};

}

#endif // TILE_HPP
