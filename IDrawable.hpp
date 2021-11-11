#ifndef IDRAWABLE_HPP
#define IDRAWABLE_HPP

#include "IHandler.hpp"

class IDrawable : public IHandler
{
    virtual void draw() = 0;
};

#endif // IDRAWABLE_HPP
