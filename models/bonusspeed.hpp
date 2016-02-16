#ifndef BONUSSPEED_HPP
#define BONUSSPEED_HPP

#include "models/bonus.hpp"

namespace model {

class BonusSpeed final : public Bonus
{
  public:

    BonusSpeed(const Position<float>& position);

    void playerPickUp(BomberMan& bomberman) const;
};

}

#endif // BONUSSPEED_HPP
