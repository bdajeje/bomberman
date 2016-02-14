#include "ia.hpp"

namespace model {

IA::IA(const std::string& name, Position<float> position, std::shared_ptr<Map>& map)
  : BomberMan{name, position, map}
{

}

}
