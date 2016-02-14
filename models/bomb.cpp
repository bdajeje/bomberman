#include "bomb.hpp"

namespace model {

Bomb::Bomb(std::shared_ptr<BomberMan> owner, unsigned short power, Position<float> position)
  : _owner{owner}
  , _power{power}
  , _position{position}
  , _animation{ "bomb", (position - Position<float>(_sprite_size / 2, _sprite_size / 2)), _sprite_size, _sprite_size, 16, 16 }
{
  _animation.start(200, true);
}

Bomb::~Bomb()
{
  _owner->raiseAvailableBombs();
}

void Bomb::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(_animation, states);
}

void Bomb::update(const sf::Time& elapsed_time)
{
  _remaining_time -= elapsed_time.asMilliseconds();
  _animation.update(elapsed_time);
}

}

