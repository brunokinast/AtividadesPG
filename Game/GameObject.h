#pragma once

#include "SpriteRenderer.h"
#include <glm/glm.hpp>
#include <glad.h>

using namespace glm;

class GameObject
{
public:
    GameObject(SpriteRenderer *renderer);
    void render(GLuint shaderID);
    vec3 getPosition();
    vec3 getSize();
    bool isColliding(GameObject *other);
    void updatePosition(vec3 position);

protected:
    SpriteRenderer *renderer;
};
