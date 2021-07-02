#include "../../include/JackdawGraphics.h"
#include "../core/glfunctions.h"
#include "../vendor/stb_image.h"

namespace jdw
{
    Texture::Texture(const std::string& filepath, bool pixelart)
    {
        stbi_set_flip_vertically_on_load(1);
        mBuffer = stbi_load(filepath.c_str(), &mWidth, &mHeight, &mBPP, 4);

        glGenTextures(1, &mID);
        glBindTexture(GL_TEXTURE_2D, mID);

        const GLfloat resampling = pixelart ? GL_NEAREST : GL_LINEAR;
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, resampling);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, resampling);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, mBuffer);

        glBindTexture(GL_TEXTURE_2D, 0);

        if (this->mBuffer)
            stbi_image_free(this->mBuffer);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &mID);
    }

    void Texture::bind(unsigned int slot)
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, mID);
    }

    void Texture::unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
