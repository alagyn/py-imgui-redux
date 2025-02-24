#pragma once

#include <glad/gl.h>

class Texture
{
public:
    int width;
    int height;
    int numChannels;

    GLuint texID;

    Texture()
        : width(0)
        , height(0)
        , numChannels(0)
        , texID(0)
    {
    }
};
