#include "player.hpp"

namespace model {

Player::Player(const std::string& name, Position<float> position, std::shared_ptr<Map>& map)
  : BomberMan{name, position, map}
{

}

}
