#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

#include "models/bomberman.hpp"
#include "utils/graphics.hpp"

namespace model {

class Player final : public BomberMan
{
  public:

    Player(const std::string& name, const std::string& logo, Position<float> position, std::shared_ptr<Map>& map);
};

}

#endif // PLAYER_HPP
