#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <random>

using std::cout;
using std::vector;




class Cell 
{
    bool _isAlive;
    int row;
    int col;

public:
    Cell(bool isAlive, int row, int col)
    {
        this->_isAlive = isAlive;
        this->row = row;
        this->col = col;
    }

    bool isAlive()
    {
        return _isAlive;
    }

    Cell mutate(int siblingsAlive)
    {
        if (siblingsAlive < 2 || siblingsAlive > 3)
            return Cell(false, row, col);

        return Cell(true, row, col); 
    }
};

class LifeMap
{
    int baseSize;
    bool isActive;
    vector<vector<Cell>> grid;

public:
    LifeMap(int baseSize)
    {
        this->isActive = true;
        this->baseSize = baseSize;
    }

    void setUp()
    {
        this->grid = createGrid();
        this->randomizeCells();
    }

    void update()
    {
        while(this->isActive)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::system("clear");
            this->draw();
            this->calculate();
        }
    }

private:
    vector<vector<Cell>> createGrid()
    {
        vector<vector<Cell>> grid = {};
        for (int i = 0; i < baseSize + 1; i++) 
        {
            vector<Cell> newVector;
            for (int j = 0; j < baseSize + 1; j++)
            {
                newVector.push_back(Cell(false, i, j));
            }
            grid.push_back(newVector);
        }
        return grid;
    }

    void randomizeCells()
    {
        for (int i = 0; i < baseSize; i++)
        {
            for (int j = 0; j < baseSize; j++)
            {
                std::random_device rd;   
                std::mt19937 rng(rd());    
                std::uniform_int_distribution<int> uni(1, 50); 
                auto randomInt = uni(rng);
                if (randomInt == 1)
                {
                    grid[i][j] = Cell(true, i, j);
                }
            }
        }
    }

    void draw()
    {
        for (int i = 0; i < baseSize; i++)
        {
            for (int j = 0; j < baseSize; j++)
            {
                if (grid[i][j].isAlive()) 
                {
                    cout << "0";
                }
                else
                {
                    cout << " ";
                }
            }
            cout << std::endl;
        }
    }
    
    void calculate()
    {
        // TODO: ref
        for (int i = 0; i < baseSize; i++)
        {
            for (int j = 0; j < baseSize; j++)
            {
                int aliveSiblings = 0;
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
                        if (grid[i+c][j+d].isAlive())
                            aliveSiblings++;
                    }
                }
                grid[i][j] = grid[i][j].mutate(aliveSiblings);
            }
        }
    }
};

int main()
{
    // TODO: ref
    const int mapSize = 40;
    LifeMap map = LifeMap(mapSize);
    map.setUp();
    map.update();
    return 0;
}
