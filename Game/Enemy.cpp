#include "Enemy.h"
#include "SpriteRenderer.h"
#include "Texture.h"

Enemy::Enemy(vec3 position)
    : GameObject(new SpriteRenderer(new Texture("Textures/enemy.png"), vec2(12, 2), position, 1.0f, 16.0f))
{
}

void Enemy::update(vec3 playerPosition)
{
    // Make the enemy move towards the player.
    // The new position is a vector towards the player with the same length as the speed.
    vec3 position = getPosition();
    vec3 direction = playerPosition - position;
    vec3 newPosition = position + normalize(direction) * speed;

    updatePosition(newPosition);
}