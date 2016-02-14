#include "directory.hpp"

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

namespace utils {

std::string& ensureDirectoryEnd(std::string& path)
{
  if(!boost::algorithm::ends_with(path, "/"))
    path += '/';

  return path;
}

std::string ensureDirectoryEndCopy(const std::string& path)
{
  if(!boost::algorithm::ends_with(path, "/"))
    return path + '/';

  return path;
}

std::string getDirectory(const std::string& path)
{
  const size_t index = path.find_last_of('/');
  if(index == std::string::npos)
    return {};

  return path.substr(0, index + 1);
}

std::vector<std::string> listFiles(const std::string& directory_path, const std::string& regex_str)
{
  namespace fs = boost::filesystem;

  std::vector<std::string> results;

  // Check given path
  if( !fs::exists( directory_path ) ||
      !fs::is_directory( directory_path ) )
    return results;

  // Create regex
  const boost::regex regex {regex_str};

  // List files
  fs::directory_iterator end_iter;
  for( fs::directory_iterator dir_itr( directory_path ); dir_itr != end_iter; ++dir_itr )
  {
    if( fs::is_regular_file( dir_itr->status() ) &&
        boost::regex_match( dir_itr->path().filename().string(), regex ))
      results.emplace_back( dir_itr->path().filename().string() );
  }

  // Alphabetically sort
  std::sort( results.begin(), results.end() );

  return results;
}

} // utils
