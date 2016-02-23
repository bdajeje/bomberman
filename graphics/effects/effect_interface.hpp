#ifndef EFFECT_INTERFACE_HPP
#define EFFECT_INTERFACE_HPP

#include <SFML/Graphics.hpp>

namespace graphics {

class EffectInterface
{
  public:

    virtual ~EffectInterface() = default;

    virtual void update(const sf::Time& elapsed_time) = 0;
};

}

#endif // EFFECT_INTERFACE_HPP
