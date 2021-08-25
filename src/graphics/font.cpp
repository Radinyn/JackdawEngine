#include "../core/glfunctions.h"
#include "../../include/JackdawGraphics.h"
#include "../vendor/stb_truetype.h"

namespace jdw
{
    Font::Font(const char* filepath, unsigned int fontSize, bool pixelart) 
    {
        mBuffer = new unsigned char[mCapacity];
        mBitmap = new unsigned char[mBitmapSize];
        mBakedChars = new stbtt_bakedchar[96];

        fread(mBuffer, 1, mCapacity, fopen(filepath, "rb"));
        stbtt_BakeFontBitmap(mBuffer, 0, fontSize, mBitmap, 512, 512, 32, 96, (stbtt_bakedchar*)mBakedChars);
        delete[] mBuffer;

        glGenTextures(1, &mID);
        glBindTexture(GL_TEXTURE_2D, mID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, 512, 512, 0, GL_RED, GL_UNSIGNED_BYTE, mBitmap);
        delete[] mBitmap;

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, pixelart ? GL_NEAREST : GL_LINEAR);
    }

    Font::~Font()
    {
        delete[] (stbtt_bakedchar*)mBakedChars;
        glDeleteTextures(1, &mID);
    }

    void Font::bind(unsigned int slot)
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, mID);
    }

    void Font::unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

}