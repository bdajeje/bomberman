#ifndef MAP_HPP
#define MAP_HPP

#include <string>
#include <vector>
#include <map>

#include "models/tile.hpp"
#include "utils/position.hpp"
#include "utils/graphics.hpp"

namespace model {

class Map final : public sf::Drawable
{
  public:

    static constexpr unsigned short _tile_size {40};

    Map(const std::string& name);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update(const sf::Time& elapsed_time);

    size_t width() const;
    size_t height() const;
    Position<float> getPlayerStartingPosition(unsigned short player_nbr) const;
    unsigned short getTotalPlayers() const { return _player_starting_positions.size(); }
    const Tile& getTile(const Position<float>& position) const;
    Position<float> getTileCenterPosition(const Position<float>& position);
    Position<size_t> getTilePosition(const Position<float>& position) const;
    bool isAllowedPosition(const Position<float>& position, unsigned short player_size) const;
    void bombExplose(const Position<float>& position, unsigned short power);

  private:

    void loadMap(const std::string filepath);

  private:

    std::string _name;
    std::vector<std::vector<Tile>> _tiles;
    std::map<int, Position<float>> _player_starting_positions;
};

}

#endif // MAP_HPP
