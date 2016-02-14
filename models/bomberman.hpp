#ifndef BOMBERMAN_HPP
#define BOMBERMAN_HPP

#include <array>
#include <memory>

#include "models/tile.hpp"
#include "models/bomb.hpp"
#include "utils/position.hpp"
#include "utils/graphics.hpp"
#include "map.hpp"

namespace model {

class Bomb;

class BomberMan : public std::enable_shared_from_this<BomberMan>,
                  public sf::Drawable
{
  enum class Texture
  {
    Top, Bottom, Left, Right
  };

  static constexpr short _sprite_size {30};

  public:

    BomberMan(const std::string& name, Position<float> position, std::shared_ptr<Map>& map);
    virtual ~BomberMan();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update(const sf::Time& elapsed_time);

    void setDirection(utils::graphics::Direction direction);
    void setMoving(bool is_moving) { _is_moving = is_moving; }
    std::shared_ptr<Bomb> dropBomb();
    void raiseAvailableBombs();

  private:

    void updatePosition(const Position<float>& position);
    void setCurrentTexture(Texture texture);
    Position<float> findFuturePosition(const sf::Time& elapsed_time) const;
    void movementUpdate(const sf::Time& elapsed_time);

    static Texture directionToTexture(utils::graphics::Direction direction);

  private:

    float _movement_speed {0.17}; // pixels/ms
    bool _is_moving {false};
    std::string _name;
    Position<float> _position;
    sf::Sprite _sprite;
    std::map<Texture, const sf::Texture&> _textures;
    utils::graphics::Direction _direction{utils::graphics::Direction::Bottom};
    std::shared_ptr<Map> _map;
    unsigned short _available_bombs {1};
    unsigned short _bomb_power {1};
};

}

#endif // BOMBERMAN_HPP
