#include "effect_core.hpp"

namespace graphics {

EffectCore::EffectCore(EffectInterface* wrappee)
  : _wrappee {wrappee}
{}

EffectCore::~EffectCore()
{
  delete _wrappee;
}

void EffectCore::update(const sf::Time& elapsed_time)
{
  _wrappee->update(elapsed_time);
}

}
