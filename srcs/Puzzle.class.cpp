#include <iostream>
#include <vector>
#include <stdexcept>

#include "Puzzle.class.hpp"

Puzzle::Puzzle()
{
    this->_puzzle = NULL;
    this->_size = -1;
    this->_heuristic = -1;
    this->_depth = -1;
}

Puzzle::Puzzle(int **puzzle, int size, int heuristic, int depth):
_puzzle(puzzle), _size(size), _heuristic(heuristic), _depth(depth)
{

}

Puzzle::Puzzle(Puzzle const & instance)
{
    this->_puzzle = instance.getPuzzle();
    this->_size = instance.getSize();
    this->_heuristic = instance.getHeuristic();
    this->_depth = instance.getDepth();
}

Puzzle::~Puzzle(void)
{
    for (int i = 0; i < this->_size; ++i)
        delete this->_puzzle[i];
    delete this->_puzzle;
}

Puzzle  &Puzzle::operator=(Puzzle const rhs)
{
    this->_puzzle = rhs.getPuzzle();
    this->_size = rhs.getSize();
    this->_heuristic = rhs.getHeuristic();
    this->_depth = rhs.getDepth();
    return *this;
}

bool    Puzzle::operator==(Puzzle const rhs)
{
    int     **tmp = rhs.getPuzzle();

    if (rhs.getSize() != this->_size)
        throw std::runtime_error(std::string("Tried to compare puzzles of different size"));
    for(int i = 0; i < this->_size; ++i)
        for (int j = 0; j < this->_size; j++)
            if (tmp[i][j] != this->_puzzle[i][j])
                return (false);
    return (true);
}

int     **Puzzle::getPuzzle(void) const
{
    return this->_puzzle;
}

int     Puzzle::getSize(void) const
{
    return this->_size;
}

int     Puzzle::getHeuristic(void) const
{
    return this->_heuristic;
}

int     Puzzle::getDepth(void) const
{
    return this->_depth;
}

void                    Puzzle::swapValues(int x1, int y1,
    int x2, int y2)
{
    int     tmp;

    tmp = this->_puzzle[y1][x1];
    this->_puzzle[y1][x1] = this->_puzzle[y2][x2];
    this->_puzzle[y2][x2] = tmp;
}

std::vector<Puzzle*>    Puzzle::generatePuzzleFromPosition(void)
{
    std::vector<Puzzle*> retPoss;
    int poss[4][2] = {
        {1, 0},
        {0, 1},
        {-1, 0},
        {0, -1}
    };
    int x, y;

    for (x = 0; x < this->_size; ++x)
        for (y = 0; y < this->_size; ++y)
            if (this->_puzzle[y][x] == 0)
                break;
    if (x == this->_size && y == this->_size)
        throw std::runtime_error(std::string("Tried to generate puzzles from puzzle without empty space"));

    for(int i = 0; i < 4; ++i)
    {
        if (y + poss[i][0] < 0 || y + poss[i][0] >= this->_size
            || x + poss[i][1] < 0 || y + poss[i][1] >= this->_size)
            continue;
        Puzzle *tmp = new Puzzle(*this);
        tmp->swapValues(x, y, x + poss[i][1], y + poss[i][0]);
        retPoss.push_back(tmp);
    }

    return (retPoss);
}