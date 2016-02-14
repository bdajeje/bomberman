#ifndef TILE_HPP
#define TILE_HPP

#include <string>

#include <SFML/Graphics.hpp>

#include "utils/position.hpp"
#include "graphics/animation.hpp"

namespace model {

class Tile final
{
  public:

    Tile(const std::string& texture_name, bool blockable, const Position<float>& position);
    ~Tile();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update(const sf::Time& elapsed_time);

    bool isBlocking() const { return _blockable; }
    void exploses(const std::string& animation);
    const Position<float>& getPosition() const { return _position; }

  private:

    void cleanExplosionAnimation();

  private:

    bool _blockable;
    Position<float> _position;
    sf::Sprite _sprite;
    graphics::Animation* _explosion_animation{nullptr};
};

}

#endif // TILE_HPP
