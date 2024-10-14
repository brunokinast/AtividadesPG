#include "Player.h"
#include "SpriteRenderer.h"
#include "Texture.h"

Player::Player(vec3 position)
    : GameObject(position, new SpriteRenderer(new Texture("Textures/player.png"), vec2(12, 2), position, 1.0f, 16.0f))
{
}

void Player::handleInput(keyInfo keys[])
{
    vec3 position = this->position;
    if (keys[GLFW_KEY_W].pressed || keys[GLFW_KEY_W].held)
        position.y -= speed;
    if (keys[GLFW_KEY_S].pressed || keys[GLFW_KEY_S].held)
        position.y += speed;
    if (keys[GLFW_KEY_A].pressed || keys[GLFW_KEY_A].held)
        position.x -= speed;
    if (keys[GLFW_KEY_D].pressed || keys[GLFW_KEY_D].held)
        position.x += speed;

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
    // Implement shooting logic here
}