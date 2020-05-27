#include "Map.h"

Map::Map(float width, float height) {
    mapWidth = width; 
    mapHeight = height;
    loadMap();
}

sf::Vector2u Map::getBlocksCount() {
    sf::Vector2u blockCount(BLOCKS_ROW, BLOCKS_COL);
    return blockCount;
}

sf::Vector2f Map::setBlockSize() {
    sf::Vector2f size;
    size.x = float(mapWidth - PADDING_LR * 2) / float(BLOCKS_COL);
    size.y = size.x / 2;
    return size;
}

void Map::loadMap() {
    blocks.resize(BLOCKS_ROW);
    for (int i = 0; i < BLOCKS_ROW; i++) {
        for (int j = 0; j < BLOCKS_COL; j++) {
            addBlock(i, j);
        }
    }
}

void Map::addBlock(int i,int j) {
    sf::Vector2f size = setBlockSize();
    int pattern = mapPattern[i][j] % Parameters::MAP_PATTERN_NUM;
    if (mapPattern[i][j] < Parameters::USUAL_BLOCK_NUM) { addUsualBlock(i, j, size, pattern); blockCount++; }
    else if (mapPattern[i][j] < Parameters::UNKILLED_BLOCK_NUM) { addUnkilledBlock(i, j, size, pattern); blockCount++;}
    else if (mapPattern[i][j] < Parameters::STONE_BLOCK_NUM) { addStoneBlock(i, j, size, pattern); }

    blocks[i][j]->resizeSprite(size);
}

void Map::addUsualBlock(int i, int j, sf::Vector2f size, int pattern) {
    blocks[i].emplace_back(new Block(size.x*j + PADDING_LR, size.y*i + PADDING_TOP, size.x, size.y, mapPattern[i][j]));
}

void Map::addUnkilledBlock(int i, int j, sf::Vector2f size, int pattern) {
    blocks[i].emplace_back(new UnkilledBlock(size.x*j + PADDING_LR, size.y*i + PADDING_TOP, size.x, size.y, pattern, BLOCK_LIVES));
}

void Map::addStoneBlock(int i, int j, sf::Vector2f size, int pattern) {
    blocks[i].emplace_back(new StoneBlock(size.x*j + PADDING_LR, size.y*i + PADDING_TOP, size.x, size.y, pattern));
}

void Map::addMoveBlock() {
   sf::Vector2f size = setBlockSize();
   int pattern = getRandomNumber(1, 8);
   sf::Vector2f max = maxCoordinates();
   sf::Vector2f finish;
   moveBlock = new MoveBlock(PADDING_LR, max.y + size.y, size.x, size.y,BLOCKS_COL *size.x+PADDING_LR,PADDING_LR, pattern, BLOCK_LIVES);
   moveBlock->resizeSprite(size);
   blockCount++;
}

void Map::decrementBlockCount() {
    this->blockCount = blockCount-1;
}

sf::Vector2f Map::maxCoordinates() {
    sf::Vector2f size = setBlockSize();
    sf::Vector2f max(PADDING_LR, size.y * BLOCKS_ROW + PADDING_TOP);
    bool addHeight = false;
    for (int i = BLOCKS_ROW - 1; i >= 0; i--) {
        max.y = size.y * i + PADDING_TOP;
        if (addHeight) break;
        for (int j = BLOCKS_COL - 1; j >= 0; j--) {
            if (blocks[i][j]->getX() != 0 && blocks[i][j]->getY() != 0) {
                addHeight = true;
            }
        }
    
    }
    if (addHeight) {
        max.y += size.y;
    }
   return max;
}

sf::Vector2f Map::maxCoordinates(sf::Vector2f &finish) {
    int i, j;
    float tmp;
    int count = 0;
    sf::Vector2f size = setBlockSize();
    sf::Vector2f start(PADDING_LR, size.y * BLOCKS_ROW + PADDING_TOP + size.y);
    bool addHeight = false;
    for (i = BLOCKS_ROW - 1; i >= 0; i--) {
        start.y = size.y * i + PADDING_TOP;
        if (count >= 3) break;
        for (j = BLOCKS_COL - 1; j >= 0; j--) {
            if (blocks[i][j]->getX() == 0 && blocks[i][j]->getY() == 0) {
                count++;
            }
            if (count >= 3) {
                break;
            }
            count = 0;
        }

    }
    if (count >= 3) {
        start.x = PADDING_LR + (j + 1 - count)*size.x;
        finish.y = start.y;
        finish.x = PADDING_LR + (j)*size.x;
    }
    else {
        start.x = PADDING_LR;
        start.y = size.y * BLOCKS_ROW + PADDING_TOP + size.y;
        finish.x = PADDING_LR + BLOCKS_ROW*size.x;
        start.y = size.y * BLOCKS_ROW + PADDING_TOP + size.y;
    }
    return start;
}


void Map::drawingMap(sf::RenderWindow *m_window, float time) {
    for (int i = 0; i < BLOCKS_ROW; i++) {
        for (int j = 0; j < BLOCKS_COL; j++) {
            blocks[i][j]->drawObject(m_window);
        }
    }
    if (moveBlock) {
        if (moveBlock->getX() != 0 && moveBlock->getY() != 0) {
            moveBlock->move(time);
            moveBlock->drawObject(m_window);
        }
        else moveBlock = nullptr;
    }
}

int Map::getCurrentBlockCount() {
    return blockCount;
}

Map::~Map() {
    for (int i = 0; i < BLOCKS_ROW; i++) {
        for (int j = 0; j < BLOCKS_COL; j++) {
            delete blocks[i][j];
        }
    }
    if (moveBlock) delete moveBlock;
}
