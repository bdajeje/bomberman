#ifndef EFFECT_HPP
#define EFFECT_HPP

#include "graphics/effects/effect_interface.hpp"

namespace graphics {

class Effect final : public EffectInterface
{
  public:

    void update(const sf::Time& /*elapsed_time*/) {}
};

}

#endif // EFFECT_HPP
