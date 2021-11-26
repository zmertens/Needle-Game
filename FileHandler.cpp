#include "FileHandler.hpp"

#include <stdexcept>
#include <fstream>

FileHandler::FileHandler()
{
}

std::string FileHandler::readFile(const std::string &fileName)
{
    if (fileName.length() == 0)
    {
        throw std::runtime_error("Filename is invalid");
    }
    std::string ret = "";
    std::fstream newfile;
    newfile.open(fileName.c_str(), std::ios::in);
    if (newfile.is_open())
    {
        std::string temp = "";
        while (std::getline(newfile, temp))
        {
            ret += temp;
        }
        newfile.close();
    }
    return ret;
}

bool FileHandler::init()
{
    bool success = true;

    return success;
}

void FileHandler::cleanUp()
{
}