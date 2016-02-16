#ifndef BONUSKICK_HPP
#define BONUSKICK_HPP

#include "models/bonus.hpp"

namespace model {

class BonusKick final : public Bonus
{
  public:

    BonusKick(const Position<float>& position);

    void playerPickUp(BomberMan& bomberman) const;
};

}

#endif // BONUSKICK_HPP
