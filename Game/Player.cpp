#include "Player.h"
#include "SpriteRenderer.h"
#include "Texture.h"
#include <functional>

using namespace std;

Player::Player(vec3 position, function<void(vec3)> createBullet, vec4 limits)
    : GameObject(new SpriteRenderer(new Texture("Textures/player.png"), vec2(12, 2), position, 1.0f, 16.0f)), createBullet(createBullet), limits(limits)
{
}

vec3 Player::getSize() 
{
    // Make the player a bit smaller than the sprite to make it easier
    return renderer->getSize() * 0.45f;
}

void Player::handleInput(keyInfo keys[])
{
    vec3 position = this->getPosition();
    if (keys[GLFW_KEY_W].pressed || keys[GLFW_KEY_W].held)
        position.y -= speed;
    if (keys[GLFW_KEY_S].pressed || keys[GLFW_KEY_S].held)
        position.y += speed;
    if (keys[GLFW_KEY_A].pressed || keys[GLFW_KEY_A].held)
        position.x -= speed;
    if (keys[GLFW_KEY_D].pressed || keys[GLFW_KEY_D].held)
        position.x += speed;

    // Constrain the position to the limits
    float halfWidth = this->getSize().x / 2.0f;
    float halfHeight = this->getSize().y / 2.0f;

    if (position.x - halfWidth < limits.x)
        position.x = limits.x + halfWidth;
    if (position.x + halfWidth > limits.z)
        position.x = limits.z - halfWidth;
    if (position.y - halfHeight < limits.y)
        position.y = limits.y + halfHeight;
    if (position.y + halfHeight > limits.w)
        position.y = limits.w - halfHeight;

    updatePosition(position);

    if (keys[GLFW_KEY_UP].pressed && !keys[GLFW_KEY_UP].held)
        shoot(0, -1);
    if (keys[GLFW_KEY_DOWN].pressed && !keys[GLFW_KEY_DOWN].held)
        shoot(0, 1);
    if (keys[GLFW_KEY_LEFT].pressed && !keys[GLFW_KEY_LEFT].held)
        shoot(-1, 0);
    if (keys[GLFW_KEY_RIGHT].pressed && !keys[GLFW_KEY_RIGHT].held)
        shoot(1, 0);
}

void Player::shoot(int dx, int dy)
{
    createBullet(vec3(dx, dy, 0));
}