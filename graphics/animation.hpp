#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "utils/position.hpp"

namespace graphics {

class Animation final : public sf::Drawable
{
  public:

    Animation(const std::string& textures_filename, const Position<float>& position,
              unsigned int wanted_width, unsigned int wanted_height,
              unsigned int texture_width, unsigned int texture_height);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update(const sf::Time& elapsed_time);

    void start(unsigned int sprite_time, bool loop);
    bool finished() const { return _finished; }

  private:

    void updateSprite();

  private:

    unsigned int _texture_width;
    unsigned int _texture_height;
    bool _loop {false};
    bool _finished {false};
    sf::Sprite _sprite;
    unsigned int _elapsed_time {0}; // milliseconds
    unsigned int _time_between_textures; // milliseconds
};

}

#endif // ANIMATION_HPP
