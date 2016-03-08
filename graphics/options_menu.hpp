#ifndef OPTIONSMENU_HPP
#define OPTIONSMENU_HPP

#include <SFML/Graphics.hpp>

namespace graphics {

class OptionsMenu final
{
  public:

    OptionsMenu(sf::RenderWindow& window);

    void run();

  private:

    void update(const sf::Time& elapsed_time);
    void draw() const;

  private:

    sf::RenderWindow& _window;
    sf::Text _title;
};

}

#endif // OPTIONSMENU_HPP
