#pragma once

#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad.h>
#include <glfw3.h>

using namespace glm;

class SpriteRenderer
{
public:
    SpriteRenderer(Texture* texture, vec2 sheetSize, vec3 position, float scale, float fps);
    void playAnimation(int row, bool loop);
    void render(GLuint shaderID);
    vec3 getPosition();
    vec3 getSize();
    void updatePosition(vec3 position);
    vec2 getSheetSize();

private:
    Texture* texture;
    vec2 sheetSize;
    vec2 currentFrame;
    vec3 position;
    float factor;
    int lastLoopingRow;
    float lastTime;
    float fps;
    bool looping;
    GLuint VBO, VAO;

    void initRenderData();
};
