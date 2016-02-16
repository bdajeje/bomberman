#include "ia.hpp"

namespace model {

IA::IA(const std::string& name, const std::__cxx11::string& logo, Position<float> position, std::shared_ptr<Map>& map)
  : BomberMan{name, logo, position, map}
{

}

}
