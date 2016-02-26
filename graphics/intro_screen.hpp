#ifndef INTROSCREEN_HPP
#define INTROSCREEN_HPP

#include <SFML/Graphics.hpp>

namespace graphics {

class IntroScreen
{
  public:

    IntroScreen(sf::RenderWindow& window, const std::string& texture_filename, uint display_time);

    void run();

  private:

    sf::RenderWindow& _window;
    const uint _display_time;
    sf::Sprite _background;
};

}

#endif // INTROSCREEN_HPP
