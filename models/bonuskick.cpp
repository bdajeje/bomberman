#include "bonuskick.hpp"

namespace model {

BonusKick::BonusKick(const Position<float>& position)
  : Bonus { position, "bonus_kick" }
{}

void BonusKick::playerPickUp(BomberMan& bomberman) const
{
  bomberman.setCanKickBombs(true);
}

}
