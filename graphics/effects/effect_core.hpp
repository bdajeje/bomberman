#ifndef EFFECTCORE_HPP
#define EFFECTCORE_HPP

#include "graphics/effects/effect.hpp"
#include "graphics/effects/effect_interface.hpp"

namespace graphics {

class EffectCore : public EffectInterface
{
  public:

    EffectCore(EffectInterface* wrappee);
    ~EffectCore();

    void update(const sf::Time& elapsed_time);

  private:

    EffectInterface* _wrappee;
};

}

#endif // EFFECTCORE_HPP
