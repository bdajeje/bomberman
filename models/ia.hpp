#ifndef IA_HPP
#define IA_HPP

#include "models/bomberman.hpp"

namespace model {

class IA final : public BomberMan
{
  public:

    IA(const std::string& name, Position<float> position, std::shared_ptr<Map>& map);
};

}

#endif // IA_HPP
