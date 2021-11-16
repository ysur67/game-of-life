#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <random>

using std::cout;
using std::vector;


const int mapSize = 26;

void updateScreen(vector<vector<bool>> grid)
{
    for (int i = 0; i < mapSize; i++)
    {
        for (int j = 0; j < mapSize; j++)
        {
            if (grid[i][j]) 
            {
                cout << "0";
            }
            else
            {
                cout << ".";
            }
        }
        cout << std::endl;
    }
}

vector<vector<bool>> updateState(vector<vector<bool>> grid)
{
    for (int i = 0; i < mapSize; i++)
    {
        for (int j = 0; j < mapSize; j++)
        {
            int life = 0;
            for (int c = -1; c < 2; c++) 
            {
                if (i == 0 && c == -1) 
                {
                    continue;
                } 
                for (int d = -1; d < 2; d++)
                {
                    if (c == 0 && d == 0)
                        continue;
                    if (j == 0 && d == -1)
                    {
                        continue;
                    }
                    if (grid[i+c][j+d])
                        life++;
                }
            }
            if (life < 2 || life > 3)
            {
                grid[i][j] = false;
            }
            else if (life == 3)
            {
                grid[i][j] = true;
            }
        }
    }
    return grid;
}

int main()
{
    vector<vector<bool>> grid = {};
    for (int i = 0; i < mapSize + 1; i++) 
    {
        vector<bool> newVector;
        for (int j = 0; j < mapSize + 1; j++)
        {
            newVector.push_back(false);
        }
        grid.push_back(newVector);
    }
    for (int i = 0; i < mapSize; i++)
    {
        for (int j = 0; j < mapSize; j++)
        {
            std::random_device rd;   
            std::mt19937 rng(rd());    
            std::uniform_int_distribution<int> uni(1, 2); 

            auto randomInt = uni(rng);
            if (randomInt % 2 == 0)
            {
                grid[i][j] = true;
            }
        }
    }
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::system("clear");
        updateScreen(grid); 
        grid = updateState(grid);
    }
    return 0;
}
