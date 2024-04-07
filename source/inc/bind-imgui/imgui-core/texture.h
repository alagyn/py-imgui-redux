#pragma once

#ifdef IMGUI_IMPL_OPENGL_ES2
    #include <glad/gles2.h>
#else
    #include <glad/gl.h>
#endif

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
