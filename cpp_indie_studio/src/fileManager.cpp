//
// fileManager.cpp for fileManager in /home/debrab_t/rendu/cpp_indie_studio
//
// Made by debrab_t
// Login   <debrab_t@epitech.net>
//
// Started on  Sat May 21 19:47:31 2016 debrab_t
// Last update Tue May 31 16:07:34 2016 David Calo
//

#include "fileManager.hh"

fileManager::fileManager()
{
}

fileManager::~fileManager()
{
}

bool		fileManager::openOk(std::string const & file)
{
  std::ifstream sfile(file, std::ifstream::binary);

  if (!sfile)
    {
      sfile.close();
      return false;
    }
  sfile.close();
  return true;
}

std::string	fileManager::openFile(std::string const & filename)
{
  std::string	line;
  std::string	str;
  std::ifstream	file(filename);

  if (file)
    {
      while (getline(file, line))
	str = str + line + '\n';
      file.close();
    }
  return (str);
}

std::vector<std::string> fileManager::openFileToVector(std::string const & name)
{
  std::string	line;
  std::vector<std::string> vfile;
  std::ifstream	file(name);

  if (file)
    {
      while (getline(file, line))
	vfile.push_back(line);
      file.close();
    }
  return (vfile);
}
