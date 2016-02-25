#ifndef BOMBERMAN_HPP
#define BOMBERMAN_HPP

#include <SFML/Graphics.hpp>

#include <array>
#include <memory>

#include "models/bomb.hpp"
#include "utils/position.hpp"
#include "utils/graphics.hpp"
#include "map.hpp"

namespace model {

class Bomb;
class Map;

class BomberMan : public std::enable_shared_from_this<BomberMan>,
                  public sf::Drawable
{
  enum class Texture
  {
    Top, Bottom, Left, Right
  };

  static constexpr short _sprite_size {30};

  public:

    BomberMan(const std::string& name, const std::string& logo, Position<float> position, std::shared_ptr<Map>& map);
    virtual ~BomberMan() = default;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update(const sf::Time& elapsed_time);

    void setDirection(utils::graphics::Direction direction);
    void setMoving(bool is_moving) { _is_moving = is_moving; }
    void setCanKickBombs(bool can_kick_bombs) { _can_kick_bombs = can_kick_bombs; }
    void setCanThrowBombs(bool can_throw_bombs) { _can_throw_bombs = can_throw_bombs; }    
    std::shared_ptr<Bomb> dropBomb();
    void setDead();

    void raiseAvailableBombs();
    void raisePower();
    void raiseSpeed();
    void raiseNbrBombs();

    const std::string& getName() const { return _name; }
    const std::string& getLogoName() const { return _logo_name; }
    unsigned short getAvailableBombs() const { return _available_bombs; }
    unsigned short getBombsPower() const { return _bomb_power; }
    const Position<float>& getPosition() const { return _position; }

    bool isAlive() const { return _is_alive; }
    bool isDead() const { return !_is_alive; }
    bool canKickBombs() const { return _can_kick_bombs; }
    bool canThrowBombs() const { return _can_throw_bombs; }

  private:

    void updatePosition(const Position<float>& position);
    void setCurrentTexture(Texture texture);
    Position<float> findFuturePosition(const sf::Time& elapsed_time) const;
    void movementUpdate(const sf::Time& elapsed_time);

    static Texture directionToTexture(utils::graphics::Direction direction);

  private:

    float _movement_speed {0.17}; // pixels/ms
    bool _is_alive {true};
    bool _is_moving {false};
    bool _can_kick_bombs{false};
    bool _can_throw_bombs{false};
    std::string _name;
    std::string _logo_name;
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
