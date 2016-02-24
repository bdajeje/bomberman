#include "time_trigger.hpp"

namespace utils {

TimeTrigger::TimeTrigger(unsigned int toggle_time)
  : _toggle_time {toggle_time}
{}

void TimeTrigger::update(const sf::Time& elapsed_time)
{
  _elapsed_time += elapsed_time.asMilliseconds();
  if( _elapsed_time >= _toggle_time )
  {
    _elapsed_time -= _toggle_time;
    _to_toggle = true;
  }
}

bool TimeTrigger::toggle()
{
  if( !_to_toggle )
    return false;

  _to_toggle = false;
  return true;
}

}
