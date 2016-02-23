#ifndef BLINKEFFECT_HPP
#define BLINKEFFECT_HPP

#include "graphics/effects/effect_core.hpp"

namespace graphics {

class BlinkEffect final : public EffectCore
{
  public:

    BlinkEffect(EffectInterface* interface, int time_between_states);

    void update(const sf::Time& elapsed_time);

  private:

    int _time_between_states;
};

}

#endif // BLINKEFFECT_HPP
