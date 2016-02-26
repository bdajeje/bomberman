#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include <SFML/Graphics.hpp>

namespace graphics {

class MainMenu
{
  public:

    enum class Action { Quit, NewGame };

    MainMenu(sf::RenderWindow& window);

    Action run();

  private:

    void handleEvents();
    void draw();
    void setSelectedMenuItem(int offset);

  private:

    bool _is_quitting {false};
    int _selected_menu_item {0};
    sf::RenderWindow& _window;
    sf::Text _play_text;
    sf::Text _options_text;
    sf::Text _quit_text;
    sf::Sprite _background;
    sf::Sprite _bomb_icon;
    std::vector<sf::Text*> _menu_items;
    const sf::Color _menu_item_color = sf::Color::White;
    const sf::Color _selected_menu_item_color = sf::Color::Blue;
};

}

#endif // MAINMENU_HPP
