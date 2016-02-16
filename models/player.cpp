#include "player.hpp"

namespace model {

Player::Player(const std::string& name, const std::__cxx11::string& logo, Position<float> position, std::shared_ptr<Map>& map)
  : BomberMan{name, logo, position, map}
{

}

}
