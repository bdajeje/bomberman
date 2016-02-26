#include "map.hpp"

#include <exception>
#include <iostream>
#include <boost/algorithm/string.hpp>

#include "utils/file.hpp"
#include "models/bonus.hpp"

namespace model {

Map::Map(const std::string& name, const std::shared_ptr<sf::Time>& game_remaining_time)
  : _name {name}
  , _game_remaining_time {game_remaining_time}
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
      std::shared_ptr<Tile> tile;

      if(character == '#')
        tile = std::make_shared<Tile>("block", true, true, position);
      else if(character == '$')
        tile = std::make_shared<Tile>("block_border", true, false, position);
      else
        tile = std::make_shared<Tile>("path", false, true, position);

      _tiles[y].push_back( tile );

      // Read player position information if here
      try
      {
        // Position is the center of the tile
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
      _tiles[y][x]->draw(target, states);
  }
}

void Map::update(const sf::Time& elapsed_time)
{
  for( std::vector<std::shared_ptr<Tile>>& line : _tiles )
  {
    for( std::shared_ptr<Tile>& tile : line )
      tile->update(elapsed_time);
  }

  if( _game_remaining_time->asSeconds() < 0 )
    createBlockOfDeath(elapsed_time);
}

void Map::createBlockOfDeath(const sf::Time& elapsed_time)
{
  if(!_block_of_death_trigger)
    _block_of_death_trigger.reset( new utils::TimeTrigger(1000) );

  _block_of_death_trigger->update(elapsed_time);
  if(!_block_of_death_trigger->toggle())
    return;

  // Find where to create block of death
  std::vector<Position<size_t>> free_positions = findFreeTilePositionsOnBorders();

  if( free_positions.empty() )
    return;

  // Mark random spot as block of death incoming
  int random_index = free_positions.size() == 1 ? 0 : rand() % (free_positions.size() - 1);
  std::shared_ptr<Tile>& tile = getTile( free_positions[random_index].x, free_positions[random_index].y );
  tile->blockOfDeathIncoming();
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
  if( _tiles[top][left]->isBlocking() )
    return false;

  // Point top right
  const float right = (position.x + player_size) / _tile_size;
  if( _tiles[top][right]->isBlocking() )
    return false;

  const float bottom = (position.y + player_size) / _tile_size;

  // Point bottom left
  if( _tiles[bottom][left]->isBlocking() )
    return false;
  // Point bottom right
  else if( _tiles[bottom][right]->isBlocking() )
    return false;

  return true;
}

Position<size_t> Map::getTilePosition(const Position<float>& position) const
{
  return Position<size_t>{ position.x / _tile_size, position.y / _tile_size };
}

std::shared_ptr<Tile>& Map::getTile(const Position<float>& position)
{
  Position<size_t> tile_position = getTilePosition(position);
  return _tiles[tile_position.y][tile_position.x];
}

std::shared_ptr<Tile>& Map::getTile(size_t x, size_t y)
{
  return _tiles[y][x];
}

size_t Map::width() const
{
  return _tiles[0].size();
}

size_t Map::height() const
{
  return _tiles.size();
}

std::vector<std::shared_ptr<model::Tile>> Map::bombExplose(const Position<float>& position, unsigned short power)
{
  std::vector<std::shared_ptr<model::Tile>> exploded_tiles;

  // Find center tile of explosion
  const Position<size_t> center_tile_position = getTilePosition(position);

  // Find neighbour tiles which exploses too

  // To left
  const size_t x_min = std::max( static_cast<long unsigned int>(1), center_tile_position.x - power );
  for(size_t x = center_tile_position.x - 1; x >= x_min; --x)
  {
    std::shared_ptr<Tile>& tile = _tiles[center_tile_position.y][x];

    if( !tile->isBreakable() )
      break;
    else if( tile->isBlocking() || x == x_min )
    {
      tile->exploses("horizontal_left_explosion");
      exploded_tiles.push_back( tile );
      break;
    }
    else
    {
      tile->exploses("horizontal_explosion");
      exploded_tiles.push_back( tile );
    }
  }

  // To right
  const size_t x_max = std::min( width()-2, center_tile_position.x + power );
  for(size_t x = center_tile_position.x + 1; x <= x_max; ++x)
  {
    std::shared_ptr<Tile>& tile = _tiles[center_tile_position.y][x];

    if( !tile->isBreakable() )
      break;
    else if( tile->isBlocking() || x == x_max )
    {
      tile->exploses("horizontal_right_explosion");
      exploded_tiles.push_back( tile );
      break;
    }
    else
    {
      tile->exploses("horizontal_explosion");
      exploded_tiles.push_back( tile );
    }
  }

  // To top
  size_t y_min = std::max( static_cast<long unsigned int>(1), center_tile_position.y - power );
  for(size_t y = center_tile_position.y - 1; y >= y_min; --y)
  {
    std::shared_ptr<Tile>& tile = _tiles[y][center_tile_position.x];

    if( !tile->isBreakable() )
      break;
    else if( tile->isBlocking() || y == y_min )
    {
      tile->exploses("vertical_top_explosion");
      exploded_tiles.push_back( tile );
      break;
    }
    else
    {
      tile->exploses("vertical_explosion");
      exploded_tiles.push_back( tile );
    }
  }

  // To bottom
  size_t y_max = std::min( height()-3, center_tile_position.y + power );
  for(size_t y = center_tile_position.y + 1; y <= y_max; ++y)
  {
    std::shared_ptr<Tile>& tile = _tiles[y][center_tile_position.x];

    if( !tile->isBreakable() )
      break;
    else if( tile->isBlocking() || y == y_max )
    {
      tile->exploses("vertical_bottom_explosion");
      exploded_tiles.push_back( tile );
      break;
    }
    else
    {
      tile->exploses("vertical_explosion");
      exploded_tiles.push_back( tile );
    }
  }

  // Center tile
  std::shared_ptr<Tile> middle_tile = _tiles[center_tile_position.y][center_tile_position.x];
  middle_tile->exploses("center_explosion");
  exploded_tiles.push_back( middle_tile );

  return std::move( exploded_tiles );
}

Position<float> Map::getTileCenterPosition(const Position<float>& position)
{
  const std::shared_ptr<Tile>& tile = getTile(position);
  Position<float> tile_position = tile->getPosition();
  tile_position.x += _tile_size / 2;
  tile_position.y += _tile_size / 2;
  return tile_position;
}

std::vector<Position<size_t>> Map::findFreeTilePositionsOnBorders(size_t depth) const
{
  if( depth >= width() / 2 )
    return {};

  std::vector<Position<size_t>> results;

  size_t min_x = depth;
  size_t min_y = depth;
  size_t max_x = width() - 1 - depth;
  size_t max_y = height() - 1 - depth;

  // Top and bottom lines
  for( size_t x = min_x; x <= max_x; ++x )
  {
    if( !_tiles[min_y][x]->isBlocking() && !_tiles[min_y][x]->isBlockOfDeathIncoming() ) results.emplace_back( x, min_y );
    if( !_tiles[max_y][x]->isBlocking() && !_tiles[max_y][x]->isBlockOfDeathIncoming() ) results.emplace_back( x, max_y );
  }

  // Left and right lines
  min_y++;
  max_y--;
  for( size_t y = min_y; y <= max_y; ++y )
  {
    const std::vector<std::shared_ptr<Tile>>& line = _tiles[y];
    if( !line[min_x]->isBlocking() && !line[min_x]->isBlockOfDeathIncoming() ) results.emplace_back( min_x, y );
    if( !line[max_x]->isBlocking() && !line[max_x]->isBlockOfDeathIncoming() ) results.emplace_back( max_x, y );
  }

  if(results.empty())
    return findFreeTilePositionsOnBorders(++depth);

  return std::move(results);
}

}
