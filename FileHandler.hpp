#ifndef FILEHANDLER_HPP
#define FILEHANDLER_HPP

#include <string>

#include "IHandler.hpp"

class FileHandler : public IHandler
{
public:
    explicit FileHandler();
    std::string readFile(const std::string& fileName);

    virtual bool init() override;
    virtual void cleanUp() override;

};

#endif // FILEHANDLER_HPP

