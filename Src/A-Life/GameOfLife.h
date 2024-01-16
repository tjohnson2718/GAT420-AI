#pragma once
#include "Environment.h"
#include "Texture.h"
#include "Random.h"

class GameOfLife : public Environment
{
public:
    GameOfLife(int width, int height, std::shared_ptr<class Texture> texture) :
        Environment(width, height, texture)
        //bufferA(width* height, 0),
        //bufferB(width* height, 0) 
        {}

    bool Initialize() override
    {
        bufferA.resize(size.x * size.y);
        bufferB.resize(size.x * size.y);
        return true;
    }

    void Step() override
    {
        frame++;
        std::vector<uint8_t>& readBuffer = (frame % 2) ? bufferA : bufferB;
        std::vector<uint8_t>& writeBuffer = (frame % 2) ? bufferB : bufferA;

        std::fill(writeBuffer.begin(), writeBuffer.end(), 0);

        for (int y = 0; y < size.y; y++)
        {
            for (int x = 0; x < size.x; x++)
            {
                int weight = 0;

                // read surrounding 8 cells, accumulate weight
                //XXX
                //X0X
                //XXX
                // read surrounding cells (8 cells)
                weight += Read<uint8_t>(readBuffer, x - 1, y - 1);
                weight += Read<uint8_t>(readBuffer, x + 0, y - 1);
                weight += Read<uint8_t>(readBuffer, x + 1, y - 1);

                weight += Read<uint8_t>(readBuffer, x - 1, y);
                weight += Read<uint8_t>(readBuffer, x + 1, y);

                weight += Read<uint8_t>(readBuffer, x - 1, y + 1);
                weight += Read<uint8_t>(readBuffer, x, y + 1);
                weight += Read<uint8_t>(readBuffer, x + 1, y + 1);

                // game of life rules
                // if cell is alive, update
                if (Read<uint8_t>(readBuffer, x, y))
                {
                    if (weight < 2 || weight > 3) //rule 1 & 3
                    {
                        Write<uint8_t>(writeBuffer, x, y, 0);
                    }
                    else //rule 2
                    {
                        Write<uint8_t>(writeBuffer, x, y, 1);
                    }
                }
                else // rule 4
                {
                    if (weight == 3)
                    {
                        Write<uint8_t>(writeBuffer, x, y, 1);
                    }
                }
            }
        }

        // convert buffer data format to color buffer
        std::transform((writeBuffer).begin(), (writeBuffer).end(), color_buffer.begin(), [](uint8_t v)
            {
                { return  v ? 0xffffffff : 0; }
            });

        // copy color buffer to texture
        texture->Copy(color_buffer);
    }

    void KeyDown(SDL_Keycode keycode) override
    {
        if (keycode == SDLK_r)
        {
            // write random 'alive' cells to buffer
            std::vector<uint8_t>& writeBuffer = (frame % 2) ? bufferB : bufferA;

            for (int i = 0; i < writeBuffer.size(); i++)
            {
                writeBuffer[i] = (random(0, 10) == 0) ? 1 : 0;
            }
        }
    }

private:
    int frame{ 0 };
    std::vector<uint8_t> bufferA;
    std::vector<uint8_t> bufferB;

};
