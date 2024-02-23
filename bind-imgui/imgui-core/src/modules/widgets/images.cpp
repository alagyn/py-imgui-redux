#include <binder/inc/struct-utility.h>
#include <imgui-core/inc/imgui-modules.h>

#include <sstream>

#include <glad/gl.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

Texture _LoadTexture(
    char* bytes,
    unsigned width,
    unsigned height,
    int numChannels = 3,
    int mipMapLevel = 0
)
{
    Texture out;
    out.width = width;
    out.height = height;
    out.numChannels = numChannels;

    int format = 0;

    switch(numChannels)
    {
    case 3:
        format = GL_RGB;
        break;
    case 4:
        format = GL_RGBA;
        break;
    default:
        std::stringstream ss;
        ss << "imgui.LoadTexture() Invalid numChannels, expected 3 or 4, got "
           << numChannels;
        throw std::runtime_error(ss.str());
    }

    glGenTextures(1, &out.texID);
    glBindTexture(GL_TEXTURE_2D, out.texID);
    glTexImage2D(
        GL_TEXTURE_2D,
        mipMapLevel,
        format,
        out.width,
        out.height,
        0, // Always zero
        format,
        GL_UNSIGNED_BYTE,
        bytes
    );
    glGenerateMipmap(GL_TEXTURE_2D);

    return out;
}

// Public facing func, so we can enforce bytes type
Texture LoadTexture(
    py::bytes bytes,
    unsigned width,
    unsigned height,
    int numChannels = 3,
    int mipMapLevel = 0
)
{
    if(width == 0)
    {
        throw py::value_error("width == 0");
    }

    if(height == 0)
    {
        throw py::value_error("height == 0");
    }

    unsigned len = bytes.attr("__len__")().cast<unsigned>();
    unsigned calcLen = width * height * numChannels;
    py::print("Got len", len);

    if(calcLen != len)
    {
        std::stringstream ss;
        ss << "(width * height * numChannels) != len(data), " << calcLen
           << " != " << len;
        throw py::value_error(ss.str());
    }

    // Preallocate to zero
    std::vector<char> data(len, 0);
    auto iter = py::iter(bytes);
    for(size_t idx = 0; iter != py::iterator::sentinel(); ++iter, ++idx)
    {
        data[idx] = (char)iter->cast<unsigned int>();
    }

    return _LoadTexture(data.data(), width, height, numChannels, mipMapLevel);
}

Texture LoadTextureFile(
    const char* filename,
    int requestedChannels = 0,
    int mipMapLevel = 0
)
{
    int width, height, numChannels;
    unsigned char* data =
        stbi_load(filename, &width, &height, &numChannels, requestedChannels);

    if(!data)
    {
        std::stringstream ss;
        ss << "imgui.LoadTextureFile() Unable to load texture: "
           << stbi_failure_reason();
        throw std::runtime_error(ss.str());
    }

    Texture out =
        _LoadTexture((char*)data, width, height, numChannels, mipMapLevel);

    stbi_image_free(data);

    return out;
}

void UnloadTexture(Texture tex)
{
    glDeleteTextures(1, &tex.texID);
}

void init_widgets_images(py::module& m)
{
    m.def(
        "LoadTextureFile",
        LoadTextureFile,
        "filename"_a,
        "requestedChannels"_a = 0,
        "lsmipMapLevel"_a = 0
    );
    m.def(
        "LoadTexture",
        LoadTexture,
        "data"_a,
        "width"_a,
        "height"_a,
        "numChannels"_a = 3,
        "mipMapLevel"_a = 0
    );
    m.def("UnloadTexture", UnloadTexture, "texture"_a);

    py::class_<Texture>(m, "Texture")
        .RW(Texture, width)
        .RW(Texture, height)
        .RW(Texture, texID);
}