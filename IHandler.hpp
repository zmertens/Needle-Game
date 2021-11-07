#ifndef IHANDLER_HPP
#define IHANDLER_HPP

class IHandler
{
    virtual bool init() = 0;
    virtual void cleanUp() = 0;
};

#endif // IHANDLER_HPP
