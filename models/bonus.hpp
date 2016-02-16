#ifndef BONUS_HPP
#define BONUS_HPP

#include <SFML/Graphics.hpp>

#include "utils/position.hpp"
#include "models/bomberman.hpp"

namespace model {

class BomberMan;

class Bonus : public sf::Drawable
{
  static constexpr short _sprite_size {30};

  public:

    Bonus(const Position<float>& position, const std::string& texture_name);
    virtual ~Bonus() = default;

    virtual void playerPickUp(BomberMan& bomberman) const = 0;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  private:

    sf::Sprite _sprite;
};

}

#endif // BONUS_HPP
