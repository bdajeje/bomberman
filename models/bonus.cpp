#include "bonus.hpp"

#include "managers/texturemanager.hpp"
#include "utils/graphics.hpp"

namespace model {

Bonus::Bonus(const Position<float>& position, const std::string& texture_name)
{
  _sprite.setTexture( texture::TextureManager::get(texture_name + ".png") );
  _sprite.setPosition(position.x, position.y);
  utils::graphics::resize(_sprite, _sprite_size, _sprite_size);
}

void Bonus::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(_sprite, states);
}

}
