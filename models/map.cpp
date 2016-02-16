#include "map.hpp"

#include <exception>
#include <iostream>
#include <boost/algorithm/string.hpp>

#include "utils/file.hpp"
#include "models/bonus.hpp"

namespace model {

Map::Map(const std::string& name)
  : _name {name}
{
  // Load map
  loadMap("resources/maps/" + _name);
}

void Map::loadMap(const std::string filepath)
{
  // Read map content
  std::string map_content;
  if(!utils::files::read(filepath, map_content))
  {
    std::cerr << "Can't read map: " << filepath << std::endl;
    throw std::exception();
  }

  std::vector<std::string> lines;
  boost::algorithm::split(lines, map_content, boost::is_any_of("\n"));
  _tiles.resize(lines.size());

  // Iterating throw Y and X
  for( size_t y = 0; y < lines.size(); ++y )
  {
    size_t x = 0;

    for( char character : lines[y] )
    {
      Position<float> position{x * _tile_size, y * _tile_size};

      if(character == '#')
        _tiles[y].emplace_back( Tile{"block", 1, position});
      else if(character == '$')
        _tiles[y].emplace_back( Tile{"block_border", 1, position});
      else
        _tiles[y].emplace_back( Tile{"path", 0, position} );

      // Read player position information if here
      try
      {
        Position<float> position {x * _tile_size + Map::_tile_size / 2, y * _tile_size + Map::_tile_size / 2};
        _player_starting_positions.emplace(std::stoi(std::string{character}), position);
      }
      catch(...)
      { /* Nothing */ }

      x++;
    }
  }
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  for(size_t y = 0; y < _tiles.size(); ++y)
  {
    for(size_t x = 0; x < _tiles[y].size(); ++x)
      _tiles[y][x].draw(target, states);
  }
}

void Map::update(const sf::Time& elapsed_time)
{
  for( std::vector<Tile>& line : _tiles )
  {
    for( Tile& tile : line )
      tile.update(elapsed_time);
  }
}

Position<float> Map::getPlayerStartingPosition(unsigned short player_nbr) const
{
  try { return _player_starting_positions.at(player_nbr); }
  catch(...)
  {
    return {0.f, 0.f};
  }
}

bool Map::isAllowedPosition(const Position<float>& position, unsigned short player_size) const
{
  // Find four points of player square,
  // and check if any of these points if not free
  // \note: we don't check if values actually exist in _tiles because boundaries should always be valid here

  player_size /= 2;

  const float left = (position.x - player_size) / _tile_size;
  const float top  = (position.y - player_size) / _tile_size;

  // Point top left  
  if( _tiles[top][left].isBlocking() )
    return false;

  // Point top right
  const float right = (position.x + player_size) / _tile_size;
  if( _tiles[top][right].isBlocking() )
    return false;

  const float bottom = (position.y + player_size) / _tile_size;

  // Point bottom left
  if( _tiles[bottom][left].isBlocking() )
    return false;
  // Point bottom right
  else if( _tiles[bottom][right].isBlocking() )
    return false;

  return true;
}

Position<size_t> Map::getTilePosition(const Position<float>& position) const
{
  return Position<size_t>{ position.x / _tile_size, position.y / _tile_size };
}

Tile& Map::getTile(const Position<float>& position)
{
  Position<size_t> tile_position = getTilePosition(position);
  return _tiles[tile_position.y][tile_position.x];
}

size_t Map::width() const
{
  return _tiles[0].size();
}

size_t Map::height() const
{
  return _tiles.size();
}

void Map::bombExplose(const Position<float>& position, unsigned short power)
{
  // Find center tile of explosion
  const Position<size_t> center_tile_position = getTilePosition(position);

  // Find neighbour tiles which exploses too
  std::string animation_name;

  // Horizontal tiles
  size_t x_min = std::max( static_cast<long unsigned int>(1), center_tile_position.x - power );
  size_t x_max = std::min( width()-2, center_tile_position.x + power );
  for(size_t x = x_min; x <= x_max; ++x)
  {
    if( x == x_min )
      animation_name = "horizontal_left_explosion";
    else if( x == x_max )
      animation_name = "horizontal_right_explosion";
    else
      animation_name = "horizontal_explosion";

    _tiles[center_tile_position.y][x].exploses(animation_name);
  }

  // Vertical tiles
  size_t y_min = std::max( static_cast<long unsigned int>(1), center_tile_position.y - power );
  size_t y_max = std::min( height()-3, center_tile_position.y + power );
  for(size_t y = y_min; y <= y_max; ++y)
  {
    if( y == y_min )
      animation_name = "vertical_top_explosion";
    else if( y == y_max )
      animation_name = "vertical_bottom_explosion";
    else
      animation_name = "vertical_explosion";

    _tiles[y][center_tile_position.x].exploses(animation_name);
  }

  // Center tile
  _tiles[center_tile_position.y][center_tile_position.x].exploses("center_explosion");
}

Position<float> Map::getTileCenterPosition(const Position<float>& position)
{
  const Tile& tile = getTile(position);
  Position<float> tile_position = tile.getPosition();
  tile_position.x += _tile_size / 2;
  tile_position.y += _tile_size / 2;
  return tile_position;
}

}
