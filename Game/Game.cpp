#include "Player.h"
#include "Enemy.h"
#include <vector>

using namespace std;

class Game
{
public:
    Game(const int width, const int height)
        : width(width), height(height)
    {
        player = new Player(vec3(width / 2, height / 2, 0));

        // Create the walls
        Texture *texture = new Texture("Textures/box.png");
        for (int i = 0; i < width; i += 32)
        {
            boxes.push_back(new SpriteRenderer(texture, vec2(1, 1), vec3(i + 16, 16, 0), 1.0f, 1.0f));
            boxes.push_back(new SpriteRenderer(texture, vec2(1, 1), vec3(i + 16, height - 16, 0), 1.0f, 1.0f));
        }
        for (int i = 32; i < height - 32; i += 32)
        {
            boxes.push_back(new SpriteRenderer(texture, vec2(1, 1), vec3(16, i + 16, 0), 1.0f, 1.0f));
            boxes.push_back(new SpriteRenderer(texture, vec2(1, 1), vec3(width - 16, i + 16, 0), 1.0f, 1.0f));
        }

        // Create the enemies, one in each corner
        enemies.push_back(new Enemy(vec3(48, 48, 0)));
        enemies.push_back(new Enemy(vec3(width - 48, 48, 0)));
        enemies.push_back(new Enemy(vec3(48, height - 48, 0)));
        enemies.push_back(new Enemy(vec3(width - 48, height - 48, 0)));
    }

    void handleInput(keyInfo keys[])
    {
        player->handleInput(keys);
    }

    void render(GLuint shaderID)
    {
        for (auto &box : boxes)
        {
            box->render(shaderID);
        }
        for (auto &enemy : enemies)
        {
            enemy->update(player->getPosition());
            enemy->render(shaderID);
        }
        player->render(shaderID);
    }

private:
    Player *player;
    vector<SpriteRenderer *> boxes;
    vector<Enemy *> enemies;
    int width;
    int height;
};