#ifndef MANAGERS_SOUND_MANAGER_HPP
#define MANAGERS_SOUND_MANAGER_HPP

#include <SFML/Audio/SoundBuffer.hpp>

#include <map>
#include <memory>

namespace sound {

class SoundManager final
{
  public:

    static void init(const std::string& sound_directory);

    /* Get the unique instance */
    static SoundManager& instance() { return *_instance; }

    static const sf::SoundBuffer& get(const std::string& sound_file_path);

  private:

    SoundManager(const std::string& sound_directory);

    const sf::SoundBuffer& loadSound(const std::string& sound);

  private:

    static std::unique_ptr<SoundManager> _instance;

    /* Directory when to find resources */
    const std::string _directory;

    /* Cached sounds */
    std::map<std::string, sf::SoundBuffer> _sounds;
};

} // sound

#endif // MANAGERS_SOUND_MANAGER_HPP
