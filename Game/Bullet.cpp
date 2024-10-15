#include "Bullet.h"
#include "SpriteRenderer.h"
#include "Texture.h"

Bullet::Bullet(vec3 position, vec3 direction)
    : GameObject(new SpriteRenderer(new Texture("Textures/bullet.png"), vec2(1, 1), position, 1.0f, 16.0f)), direction(normalize(direction))
{
}

void Bullet::update()
{
    vec3 position = getPosition();
    // Normalize the direction vector
    position += direction * speed;
    updatePosition(position);
}