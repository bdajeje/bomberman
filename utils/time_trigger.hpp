#ifndef TIMETRIGGER_HPP
#define TIMETRIGGER_HPP

#include <SFML/System/Time.hpp>

namespace utils {

class TimeTrigger final
{
  public:

    /* Constructor
     * \paran toggle_time - time between two toggles (in milliseconds)
     */
    TimeTrigger(unsigned int toggle_time);

    void update(const sf::Time& elapsed_time);
    bool toggle();

  private:

    bool _to_toggle {false};
    const unsigned int _toggle_time;
    unsigned int _elapsed_time {0};
};

}

#endif // TIMETRIGGER_HPP
