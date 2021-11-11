#ifndef GLTRIANGLE_HPP
#define GLTRIANGLE_HPP

#include "IDrawable.hpp"

class GlTriangle : public IDrawable
{
public:
    explicit GlTriangle();


    virtual bool init() override;
    virtual void cleanUp() override;
    virtual void draw() override;

private:
    unsigned int VBO, VAO, EBO, shaderProgram;
};

#endif // GLTRIANGLE_HPP