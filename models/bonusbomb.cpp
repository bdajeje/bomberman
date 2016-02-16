#include "bonusbomb.hpp"

namespace model {

BonusBomb::BonusBomb(const Position<float>& position)
  : Bonus { position, "bonus_bomb" }
{}

void BonusBomb::playerPickUp(BomberMan& bomberman) const
{
  bomberman.raiseNbrBombs();
}

}
