#ifndef MAP_H
#define MAP_H
#pragma once

#include <SFML\Graphics.hpp>

#include "Block.h"
#include "UnkilledBlock.h"
#include "StoneBlock.h"
#include "MoveBlock.h"
#include "Parameters.h"

class Map {
public:
    Map(float width, float height);
    std::vector<std::vector<Block*>> blocks;
    Block *moveBlock = nullptr;
   
    sf::Vector2u getBlocksCount();
    void addMoveBlock();
    void decrementBlockCount();
    void drawingMap(sf::RenderWindow * m_window, float time);
    int getCurrentBlockCount();

private:  

    typedef enum blockType {
        UNKILLABLE,
        IMMUNITY,
        USUALL
    } blockType_t;
    
    float mapWidth;
    float mapHeight;
    int blockCount = 0;

    void loadMap();

    sf::Vector2f setBlockSize();
    void addBlock(int i,int j);
    void addUsualBlock(int i, int j, sf::Vector2f size, int pattern);
    void addUnkilledBlock(int i, int j, sf::Vector2f size, int pattern);
    void addStoneBlock(int i, int j, sf::Vector2f size, int pattern);
    

    sf::Vector2f maxCoordinates();
    sf::Vector2f maxCoordinates(sf::Vector2f &finish);

    static const int BLOCKS_ROW = Parameters::BLOCKS_IN_ROW;
    static const int BLOCKS_COL = Parameters::BLOCKS_IN_COL;
    static const int PADDING_TOP = Parameters::MAP_PADDING_TOP;
    static const int PADDING_LR = Parameters::MAP_PADDING_WALL;
    static const int BLOCK_LIVES = Parameters::BLOCK_LIVES;

    int mapPattern[BLOCKS_ROW][BLOCKS_COL] = {

       {10,10,10,10,10,10,10,10,10,10,10,10,10,10},
       {11,11,11,11,29,29,29,29,29,29,11,11,11,11},
       {2,2,2,2,11,29,29,29,29,11,2,2,2,2},
       {3,3,3,3,2,11,29,29,11,2,3,3,3,3},
       {4,4,4,4,3,2,29,29,2,3,4,4,4,4},
       {6,6,6,6,4,3,2,2,3,4,6,6,6,6},
       {15,15,6,6,6,4,3,3,4,6,6,6,15,15},
       {15,15,15,6,6,6,4,4,6,6,6,15,15,15}

    };
};
#endif // !MAP_H