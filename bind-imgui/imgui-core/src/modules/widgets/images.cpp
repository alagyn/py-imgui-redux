#include <binder/inc/struct-utility.h>
#include <imgui-core/inc/imgui-modules.h>

#include <glad/gl.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Texture
{
public:
    int width;
    int height;

    GLuint texID;

    Texture()
        : width(0)
        , height(0)
        , texID(0)
    {
    }
};

Texture
loadTexture(char* bytes, unsigned width, unsigned height, int mipMapLevel = 0)
{
    Texture out;
    out.width = width;
    out.height = height;
    glGenTextures(1, &out.texID);
    glBindTexture(GL_TEXTURE_2D, out.texID);
    glTexImage2D(
        GL_TEXTURE_2D,
        mipMapLevel, // TODO: Mipmap level?
        GL_RGB,
        out.width,
        out.height,
        0, // Always zero
        GL_RGB,
        GL_UNSIGNED_BYTE,
        bytes
    );
    glGenerateMipmap(GL_TEXTURE_2D);

    return out;
}

Texture loadTextureFile(const char* filename, int mipMapLevel = 0)
{
    int width, height, numChannels;
    unsigned char* data = stbi_load(filename, &width, &height, &numChannels, 0);
    Texture out = loadTexture((char*)data, width, height, mipMapLevel);
    stbi_image_free(data);

    return out;
}

void unloadTexture(Texture tex)
{
    glDeleteTextures(1, &tex.texID);
}

void init_widgets_images(py::module& m)
{
    m.def("LoadTextureFile", loadTextureFile, "filename"_a, "mipMapLevel"_a = 0);
    m.def(
        "loadTexture",
        loadTexture,
        "data"_a,
        "width"_a,
        "height"_a,
        "mipMapLevel"_a = 0
    );
    m.def("UnloadTexture", unloadTexture, "texture"_a);

    py::class_<Texture>(m, "Texture")
        .RW(Texture, width)
        .RW(Texture, height)
        .RW(Texture, texID);
}