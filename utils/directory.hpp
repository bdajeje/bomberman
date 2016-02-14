#ifndef JENGINE_DIRECTORY_HPP
#define JENGINE_DIRECTORY_HPP

#include <string>
#include <vector>

namespace utils {

// Ensure '/' and the end of directory string
std::string& ensureDirectoryEnd(std::string& path);
std::string ensureDirectoryEndCopy(const std::string& path);

/* Get the directory part of a filepath */
std::string getDirectory(const std::string& path);

/*! List files under directory */
std::vector<std::string> listFiles(const std::string& directory_path, const std::string& regex_str);

} // utils

#endif // JENGINE_DIRECTORY_HPP
