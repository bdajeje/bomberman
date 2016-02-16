#include "bonusthrow.hpp"

namespace model {

BonusThrow::BonusThrow(const Position<float>& position)
  : Bonus { position, "bonus_speed" }
{}

void BonusThrow::playerPickUp(BomberMan& bomberman) const
{
  bomberman.setCanThrowBombs(true);
}

}
