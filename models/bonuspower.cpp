#include "bonuspower.hpp"

namespace model {

BonusPower::BonusPower(const Position<float>& position)
  : Bonus { position, "bonus_power" }
{}

void BonusPower::playerPickUp(BomberMan& bomberman) const
{
  bomberman.raisePower();
}

}
