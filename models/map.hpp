#ifndef MAP_HPP
#define MAP_HPP

#include <string>
#include <vector>
#include <map>

#include "models/tile.hpp"
#include "utils/position.hpp"
#include "utils/graphics.hpp"
#include "utils/time_trigger.hpp"

namespace model {

class Tile;

class Map final : public sf::Drawable
{
  public:

    static constexpr unsigned short _tile_size {40};

    Map(const std::string& name, const std::shared_ptr<sf::Time>& game_remaining_time);

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update(const sf::Time& elapsed_time);

    size_t width() const;
    size_t height() const;
    Position<float> getPlayerStartingPosition(unsigned short player_nbr) const;
    unsigned short getTotalPlayers() const { return _player_starting_positions.size(); }

    /*! Get tile from a pixel position */
    Tile& getTile(const Position<float>& position);

    /*! Get tile located at map position X/Y
     *  \warning no checks are done on array bounds
     */
    Tile& getTile(size_t x, size_t y);

    Position<float> getTileCenterPosition(const Position<float>& position);
    Position<size_t> getTilePosition(const Position<float>& position) const;
    bool isAllowedPosition(const Position<float>& position, unsigned short player_size) const;
    void bombExplose(const Position<float>& position, unsigned short power);

  private:

    void loadMap(const std::string filepath);
    void createBlockOfDeath(const sf::Time& elapsed_time);

    /*! Find free tile positions located at depth from borders the map
     *  \example a depth of 1 will return free positions on columns 1 and width()-1 and rows 1 and height()-1
     */
    std::vector<Position<size_t>> findFreeTilePositionsOnBorders(size_t depth = 1) const;

  private:

    std::string _name;
    std::shared_ptr<sf::Time> _game_remaining_time;
    std::vector<std::vector<Tile>> _tiles;
    std::map<int, Position<float>> _player_starting_positions;
    std::unique_ptr<utils::TimeTrigger> _block_of_death_trigger;
};

}

#endif // MAP_HPP
