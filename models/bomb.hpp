#ifndef BOMB_HPP
#define BOMB_HPP

#include <memory>

#include "models/bomberman.hpp"
#include "graphics/animation.hpp"

namespace model {

class BomberMan;

class Bomb final : public sf::Drawable
{
  static constexpr unsigned short _sprite_size {30};
  static constexpr unsigned short _countdown {2000}; // milliseconds

  public:

    Bomb(std::shared_ptr<BomberMan> owner, unsigned short power, Position<float> position);
    ~Bomb();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update(const sf::Time& elapsed_time);
    bool isExploded() const { return _remaining_time < 0; }
    const Position<float>& position() const { return _position; }
    unsigned short power() const { return _power; }

  private:

    short _remaining_time {_countdown};
    std::shared_ptr<BomberMan> _owner;
    unsigned short _power;
    Position<float> _position;
    graphics::Animation _animation;
};

}

#endif // BOMB_HPP
