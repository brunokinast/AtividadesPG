#pragma once

#include <glad.h>
#include <glfw3.h>

class Texture
{
public:
    Texture(const char *filePath);
    ~Texture();
    void Bind() const;
    void Unbind() const;
    int GetWidth() const;
    int GetHeight() const;

private:
    GLuint textureID;
    int width, height, nrChannels;
};
