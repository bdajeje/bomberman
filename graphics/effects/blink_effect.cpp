#include "blink_effect.hpp"

#include <iostream>

namespace graphics {

BlinkEffect::BlinkEffect(EffectInterface* interface, int time_between_states)
  : EffectCore(interface)
  , _time_between_states {time_between_states}
{}

void BlinkEffect::update(const sf::Time& elapsed_time)
{
  EffectCore::update(elapsed_time);

  std::cout << "Blink Effect" << std::endl;
}

}
