#include "soundmanager.hpp"

#include "utils/directory.hpp"

namespace sound {

std::unique_ptr<SoundManager> SoundManager::_instance;

void SoundManager::init(const std::string& sound_directory)
{
  if( _instance )
    return;

  _instance.reset( new SoundManager(sound_directory) );
}

SoundManager::SoundManager(const std::string& sound_directory)
  : _directory { utils::ensureDirectoryEndCopy(sound_directory) }
{}

const sf::SoundBuffer& SoundManager::get(const std::string& sound_file_path)
{
  SoundManager& instance = SoundManager::instance();

  // Find texture
  auto found_it = instance._sounds.find(sound_file_path);

  // Found, return it
  if( found_it != instance._sounds.end() )
    return found_it->second;

  // Not already loaded, so load it then return it
  return instance.loadSound(sound_file_path);
}

const sf::SoundBuffer& SoundManager::loadSound(const std::string& sound_file_path)
{
  // Load sound
  sf::SoundBuffer& sound = _sounds[sound_file_path];
  if( !sound.loadFromFile( _directory + sound_file_path ) )
    throw std::invalid_argument {"Can't load sound: " + sound_file_path};

  return sound;
}

} // sound
