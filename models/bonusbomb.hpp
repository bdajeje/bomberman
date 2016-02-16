#ifndef BONUSBOMB_HPP
#define BONUSBOMB_HPP

#include "models/bonus.hpp"

namespace model {

class BonusBomb final : public Bonus
{
  public:

    BonusBomb(const Position<float>& position);

    void playerPickUp(BomberMan& bomberman) const;
};

}

#endif // BONUSBOMB_HPP
