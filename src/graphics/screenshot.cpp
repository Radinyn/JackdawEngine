#include "../vendor/stb_image_write.h"
#include "../core/glfunctions.h"
#include "../../include/JackdawCore.h"

namespace jdw
{
    void screenshot(const char* filename, IMG_FORMAT format, int quality)
    {
        unsigned char* buffer = new unsigned char[Application::mWidth*Application::mHeight*4];
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        glReadPixels(0, 0, Application::mWidth, Application::mHeight, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
        stbi_flip_vertically_on_write(true);
        if (format == IMG_FORMAT::PNG)
            stbi_write_png(filename, Application::mWidth, Application::mHeight, 4, buffer, Application::mWidth*4);
        else if (format == IMG_FORMAT::JPG)
            stbi_write_jpg(filename, Application::mWidth, Application::mHeight, 4, buffer, quality);
        delete[] buffer;
    }
}