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

    void update(const sf::Time& elapsed_time);

  private:

    sf::RenderWindow& _window;
    const uint _display_time;
    sf::Sprite _background;
};

}

#endif // INTROSCREEN_HPP
