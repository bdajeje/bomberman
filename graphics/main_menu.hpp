#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include <SFML/Graphics.hpp>

#include "utils/key_limitor.hpp"

namespace graphics {

class MainMenu
{
  public:

    enum class Action { NewGame, Options, Quit, None };

    MainMenu(sf::RenderWindow& window);

    Action run();

  private:

    Action handleEvents();
    void draw();
    void setSelectedMenuItem(int offset, bool play_sound);
    Action selectCurrentMenuItem();

  private:

    sf::RenderWindow& _window;
    utils::KeyLimitor _key_limitor;
    bool _is_quitting {false};
    int _selected_menu_item {0};
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
