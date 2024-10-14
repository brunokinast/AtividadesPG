#include "GameObject.h"

GameObject::GameObject(vec3 position, SpriteRenderer *renderer) : position(position)
{
    this->renderer = renderer;
}

void GameObject::render(GLuint shaderID)
{
    renderer->render(shaderID);
}

vec3 GameObject::getPosition()
{
    return position;
}

void GameObject::updatePosition(vec3 position)
{
    if (this->position == position)
    {
        renderer->playAnimation(0, true);
    }
    else
    {
        this->position = position;
        renderer->updatePosition(position);
        renderer->playAnimation(1, false);
    }
}