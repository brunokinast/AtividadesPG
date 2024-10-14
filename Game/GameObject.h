#pragma once

#include "SpriteRenderer.h"
#include <glm/glm.hpp>
#include <glad.h>

using namespace glm;

class GameObject
{
public:
    GameObject(vec3 position, SpriteRenderer *renderer);
    void render(GLuint shaderID);
    vec3 getPosition();

protected:
    SpriteRenderer *renderer;
    vec3 position;

    void updatePosition(vec3 position);
};
