#include "GameObject.h"

GameObject::GameObject(SpriteRenderer *renderer)
{
    this->renderer = renderer;
}

void GameObject::render(GLuint shaderID)
{
    renderer->render(shaderID);
}

bool GameObject::isColliding(GameObject *other)
{
    // Be aware that the position is the center of the object
    vec3 position = getPosition();
    vec3 otherPosition = other->getPosition();
    vec3 size = getSize();
    vec3 otherSize = other->getSize();

    return position.x - size.x / 2 < otherPosition.x + otherSize.x / 2 &&
           position.x + size.x / 2 > otherPosition.x - otherSize.x / 2 &&
           position.y - size.y / 2 < otherPosition.y + otherSize.y / 2 &&
           position.y + size.y / 2 > otherPosition.y - otherSize.y / 2;
}

vec3 GameObject::getSize()
{
    return renderer->getSize();
}

vec3 GameObject::getPosition()
{
    return renderer->getPosition();
}

void GameObject::updatePosition(vec3 position)
{
    if (getPosition() == position)
    {
        renderer->playAnimation(0, true);
    }
    else
    {
        if (renderer->getSheetSize().x > 1)
            renderer->playAnimation(1, false);

        renderer->updatePosition(position);
    }
}