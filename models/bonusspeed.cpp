#include "bonusspeed.hpp"

namespace model {

BonusSpeed::BonusSpeed(const Position<float>& position)
  : Bonus { position, "bonus_speed" }
{}

void BonusSpeed::playerPickUp(BomberMan& bomberman) const
{
  bomberman.raiseSpeed();
}

}
