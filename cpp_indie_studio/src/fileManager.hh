//
// fileManager.hh for fileManager in /home/debrab_t/rendu/cpp_indie_studio
//
// Made by debrab_t
// Login   <debrab_t@epitech.net>
//
// Started on  Sat May 21 19:52:05 2016 debrab_t
// Last update Tue May 31 16:12:03 2016 David Calo
//

#ifndef FILEMANAGER_HH_
# define FILEMANAGER_HH_

# include <iostream>
# include <fstream>
# include <vector>

class fileManager
{
public:
  fileManager();
  ~fileManager();

public:
  static bool				openOk(std::string const &);
  std::string				openFile(std::string const &);
  static std::vector<std::string>	openFileToVector(std::string const &);
};

#endif /*!FILEMANAGER_HH_*/
