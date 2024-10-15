#include "SpriteRenderer.h"
#include <iostream>

SpriteRenderer::SpriteRenderer(Texture *texture, vec2 sheetSize, vec3 position, float scale, float fps)
    : sheetSize(sheetSize), position(position), factor(scale), fps(fps), currentFrame(vec2(0.0, 0.0)), lastLoopingRow(0), lastTime(0), looping(true)
{
    this->texture = texture;
    initRenderData();
}

vec3 SpriteRenderer::getSize()
{
    return vec3(texture->GetWidth() / sheetSize.x, texture->GetHeight() / sheetSize.y, 0);
}

vec2 SpriteRenderer::getSheetSize()
{
    return sheetSize;
}

void SpriteRenderer::playAnimation(int row, bool loop)
{
    if (currentFrame.y != row)
    {
        currentFrame.y = row;
        currentFrame.x = 0;
        if (loop)
            lastLoopingRow = row;
        looping = loop;
    }
}

void SpriteRenderer::render(GLuint shaderID)
{
    float now = glfwGetTime();
    float dt = now - lastTime;
    if (dt >= 1.0f / fps)
    {
        if (currentFrame.x < sheetSize.x - 1)
        {
            currentFrame.x++;
        }
        else
        {
            if (looping)
            {
                currentFrame.x = 0;
            }
            else
            {
                currentFrame.y = lastLoopingRow;
                currentFrame.x = 0;
                looping = true;
            }
        }
        lastTime = now;
    }

    glUniform2f(glGetUniformLocation(shaderID, "offsetTex"), currentFrame.x / sheetSize.x, currentFrame.y / sheetSize.y);
    glBindVertexArray(VAO);
    texture->Bind();

    mat4 model = translate(mat4(1.0f), position);
    model = scale(model, vec3(texture->GetWidth() / sheetSize.x, texture->GetHeight() / sheetSize.y, 1.0f));
    model = scale(model, vec3(factor, factor, 1.0f));

    glUniformMatrix4fv(glGetUniformLocation(shaderID, "model"), 1, GL_FALSE, value_ptr(model));
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindVertexArray(0);
}

vec3 SpriteRenderer::getPosition()
{
    return position;
}

void SpriteRenderer::updatePosition(vec3 position)
{
    this->position = position;
}

void SpriteRenderer::initRenderData()
{
    GLfloat s = 1.0 / (float)sheetSize.x;
    GLfloat t = 1.0 / (float)sheetSize.y;
    GLfloat vertices[] = {
        -0.5, -0.5, 0.0, 0.0, 0.0,
        -0.5, 0.5, 0.0, 0.0, t,
        0.5, -0.5, 0.0, s, 0.0,
        0.5, 0.5, 0.0, s, t};

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}