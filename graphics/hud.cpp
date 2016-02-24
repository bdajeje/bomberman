#include "hud.hpp"

#include <iostream>
#include <array>
#include <math.h>

#include "defines.hpp"
#include "managers/fontmanager.hpp"
#include "managers/texturemanager.hpp"
#include "utils/graphics.hpp"

namespace graphics {

HUDPlayer::HUDPlayer(const std::shared_ptr<model::BomberMan>& player, Position<float> position)
  : _player {player}
{
  // Logo
  _player_logo.setTexture( texture::TextureManager::get(player->getLogoName() + ".png") );
  _player_logo.setPosition(position.x, position.y);
  utils::graphics::resize(_player_logo, 15, 15);

  position.x += 20;

  const sf::Font& font = font::FontManager::get("consolas.ttf");
  std::array<sf::Text*, 4> texts = {&_name, &_bombs_number, &_power_number, &_dead_text};
  for( sf::Text* text : texts )
  {
    text->setFont(font);
    text->setCharacterSize(15);
    text->setColor(sf::Color::White);
  }

  // Name
  _name.setString(player->getName());
  _name.setPosition(position.x, position.y);

  position.x -= 20;
  position.y += 20;

  // Dead text
  _dead_text.setString("DEAD");
  _dead_text.setPosition(position.x, position.y);

  // Bomb number skill
  _bombs.setTexture( texture::TextureManager::get("bonus_bomb.png") );
  _bombs.setPosition(position.x, position.y);
  utils::graphics::resize(_bombs, 15, 15);  

  position.x += 20;
  _bombs_number.setPosition(position.x, position.y);

  position.x += 15;

  // Bomb power skill
  _power.setTexture( texture::TextureManager::get("bonus_power.png") );
  _power.setPosition(position.x, position.y);
  utils::graphics::resize(_power, 15, 15);

  position.x += 20;
  _power_number.setPosition(position.x, position.y);

  position.x += 15;

  // Bomb kick skill
  _kick_bomb.setTexture( texture::TextureManager::get("bonus_kick.png") );
  _kick_bomb.setPosition(position.x, position.y);
  utils::graphics::resize(_kick_bomb, 15, 15);

  position.x += 15;

  // Bomb throw skill
  _throw_bomb.setTexture( texture::TextureManager::get("bonus_throw.png") );
  _throw_bomb.setPosition(position.x, position.y);
  utils::graphics::resize(_throw_bomb, 15, 15);
}

void HUDPlayer::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  target.draw(_player_logo, states);
  target.draw(_name, states);
  if( _player->isAlive() )
  {
    target.draw(_bombs, states);
    target.draw(_bombs_number, states);
    target.draw(_power, states);
    target.draw(_power_number, states);

    if(_player->canThrowBombs())
      target.draw(_throw_bomb, states);

    if(_player->canKickBombs())
      target.draw(_kick_bomb, states);
  }
  else target.draw(_dead_text);
}

HUD::HUD(const std::vector<std::shared_ptr<model::BomberMan>>& players, const std::shared_ptr<sf::Time>& game_remaining_time)
  : _players {players}
  , _game_remaining_time {game_remaining_time}
{
  _remaining_time.setFont(font::FontManager::get("consolas.ttf"));
  _remaining_time.setCharacterSize(15);
  _remaining_time.setColor(sf::Color::White);
  updateRemainingTime();

  Position<float> position {50, 5};
  _player_informations.reserve(players.size());
  for( size_t i = 0; i < players.size(); ++i )
  {
    _player_informations.emplace_back( players[i], position );
    position.x += WINDOW_WIDTH / players.size();
  }
}

void HUD::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  if(_draw_remaining_time)
    target.draw( _remaining_time, states );

  for( size_t i = 0; i < _player_informations.size(); ++i )
    target.draw( _player_informations[i], states );
}

void HUD::update(const sf::Time& elapsed_time)
{
  // Update remaining time
  if( _game_remaining_time->asSeconds() > 0 )
    updateRemainingTime();
  else
  {
    // Update text
    if(!_end_blinking_trigger)
    {
      _remaining_time.setString("finishing!");
      _remaining_time.setPosition( (WINDOW_WIDTH - _remaining_time.getGlobalBounds().width) / 2, _remaining_time.getPosition().y );
      _end_blinking_trigger.reset( new utils::TimeTrigger(350) );
    }

    // Make remaining time blink
    _end_blinking_trigger->update(elapsed_time);
    if( _end_blinking_trigger->toggle() )
      _draw_remaining_time = !_draw_remaining_time;
  }

  // Update user info
  for( size_t i = 0; i < _players.size(); ++i )
  {
    const std::shared_ptr<model::BomberMan>& player = _players[i];
    if( player->isAlive() )
    {
      HUDPlayer& hud_player = _player_informations[i];
      hud_player._bombs_number.setString(std::to_string(player->getAvailableBombs()));
      hud_player._power_number.setString(std::to_string(player->getBombsPower()));
    }
  }
}

void HUD::updateRemainingTime()
{
  int remaining_seconds = static_cast<int>(_game_remaining_time->asSeconds());
  int remaining_mins = remaining_seconds / 60;
  remaining_seconds -= remaining_mins * 60;

  _remaining_time.setString( std::to_string(remaining_mins) + ":" + std::to_string(remaining_seconds) );
  _remaining_time.setPosition( (WINDOW_WIDTH - _remaining_time.getGlobalBounds().width) / 2, 20 );
}

}
