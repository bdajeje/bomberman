#ifndef BONUSPOWER_HPP
#define BONUSPOWER_HPP

#include "models/bonus.hpp"

namespace model {

class BonusPower final : public Bonus
{
  public:

    BonusPower(const Position<float>& position);

    void playerPickUp(BomberMan& bomberman) const;
};

}

#endif // BONUSPOWER_HPP
