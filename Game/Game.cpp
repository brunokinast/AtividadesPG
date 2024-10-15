#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include <vector>
#include <string>
#include <chrono>
#include <random>
#include <text/text.h>

using namespace std;

class Game
{
public:
    Game(const int width, const int height)
        : width(width), height(height), rng(random_device{}()), dist(0, 1), lastSpawnTime(chrono::steady_clock::now()), enemiesKilled(0), lastScore(0), gameStarted(false)
    {
        // Initialize player and UI elements
        player = new Player(vec3(width / 2, height / 2, 0), bind(&Game::createBullet, this, placeholders::_1), vec4(32, 32, width - 32, height - 32));
        scoreText = add_text("Pts: 0", -0.95f, 1.01f, 25, 0.0f, 0.0f, 0.0f, 1.0f);
        lastScoreText = add_text("Last score: 0", -0.3f, -0.3f, 25, 0.0f, 0.0f, 0.0f, 1.0f);

        // Create boundary boxes
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

        // Initialize start image and background
        startImage = new SpriteRenderer(new Texture("Textures/start.png"), vec2(1, 1), vec3(width / 2, height / 2, 0), 1.0f, 1.0f);
        background = new SpriteRenderer(new Texture("Textures/background.png"), vec2(1, 1), vec3(width / 2, height / 2, 0), 1.0f, 1.0f);
    }

    void handleInput(keyInfo keys[])
    {
        if (!gameStarted)
        {
            gameStarted = keys[GLFW_KEY_ENTER].pressed;
        }
        else
        {
            player->handleInput(keys);
        }
    }

    void render(GLuint shaderID)
    {
        processCollisions();

        background->render(shaderID);

        // Render bullets
        for (auto &bullet : bullets)
        {
            bullet->update();
            bullet->render(shaderID);
        }

        // Render enemies
        for (auto &enemy : enemies)
        {
            enemy->update(player->getPosition());
            enemy->render(shaderID);
        }

        // Render boundary boxes
        for (auto &box : boxes)
        {
            box->render(shaderID);
        }

        player->render(shaderID);

        if (!gameStarted)
        {
            startImage->render(shaderID);
            update_text(lastScoreText, ("Last score: " + to_string(lastScore)).c_str());
            draw_text(lastScoreText);
            return;
        }

        draw_text(scoreText);
        spawnEnemies();
    }

    void resetGame()
    {
        player->updatePosition(vec3(width / 2, height / 2, 0));

        // Clear enemies and bullets
        for (auto &enemy : enemies)
        {
            delete enemy;
        }
        enemies.clear();

        for (auto &bullet : bullets)
        {
            delete bullet;
        }
        bullets.clear();

        enemiesKilled = 0;
        update_text(scoreText, "Pts: 0");

        lastSpawnTime = chrono::steady_clock::now();
        spawnInterval = 2000.0f;

        gameStarted = false;
    }

private:
    Player *player;
    vector<SpriteRenderer *> boxes;
    vector<Enemy *> enemies;
    vector<Bullet *> bullets;
    SpriteRenderer *startImage;
    SpriteRenderer *background;
    int width;
    int height;
    int enemiesKilled;
    int scoreText;
    int lastScoreText;
    int lastScore;
    bool gameStarted;

    chrono::steady_clock::time_point lastSpawnTime;
    float spawnInterval = 2000.0f;
    mt19937 rng;
    uniform_real_distribution<float> dist;

    void processCollisions()
    {
        // Check player-enemy collisions
        for (auto &enemy : enemies)
        {
            if (player->isColliding(enemy))
            {
                lastScore = enemiesKilled;
                resetGame();
                return;
            }
        }

        // Check bullet collisions
        for (auto bullet = bullets.begin(); bullet != bullets.end();)
        {
            vec3 position = (*bullet)->getPosition();
            if (position.x < 32 || position.x > width - 32 || position.y < 32 || position.y > height - 32)
            {
                delete *bullet;
                bullet = bullets.erase(bullet);
            }
            else
            {
                bool bulletErased = false;
                for (auto enemy = enemies.begin(); enemy != enemies.end();)
                {
                    if ((*bullet)->isColliding(*enemy))
                    {
                        delete *bullet;
                        bullet = bullets.erase(bullet);

                        delete *enemy;
                        enemy = enemies.erase(enemy);

                        bulletErased = true;
                        enemiesKilled++;
                        update_text(scoreText, ("Pts: " + to_string(enemiesKilled)).c_str());
                        break;
                    }
                    else
                    {
                        ++enemy;
                    }
                }
                if (!bulletErased)
                {
                    ++bullet;
                }
            }
        }
    }

    void createBullet(vec3 direction)
    {
        bullets.push_back(new Bullet(player->getPosition(), direction));
    }

    void spawnEnemies()
    {
        auto now = chrono::steady_clock::now();
        auto elapsed = chrono::duration_cast<chrono::milliseconds>(now - lastSpawnTime).count();

        if (elapsed >= spawnInterval)
        {
            float x, y;
            if (dist(rng) < 0.5f)
            {
                x = dist(rng) * width;
                y = (dist(rng) < 0.5f) ? 0 : height;
            }
            else
            {
                x = (dist(rng) < 0.5f) ? 0 : width;
                y = dist(rng) * height;
            }

            enemies.push_back(new Enemy(vec3(x, y, 0)));

            lastSpawnTime = now;

            spawnInterval = std::max(250.0f, spawnInterval - 20.0f);
        }
    }
};
