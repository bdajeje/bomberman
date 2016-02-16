#ifndef BONUSTHROW_HPP
#define BONUSTHROW_HPP

#include "models/bonus.hpp"

namespace model {

class BonusThrow final : public Bonus
{
  public:

    BonusThrow(const Position<float>& position);

    void playerPickUp(BomberMan& bomberman) const;
};

}

#endif // BONUSTHROW_HPP
