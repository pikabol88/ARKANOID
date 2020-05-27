#ifndef GAME_H
#define GAME_H
#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include "Lives.h"
#include "Object.h"
#include "Map.h"
#include "Paddle.h"
#include "Ball.h"
#include "Bonus.h"
#include "Bottom.h"
#include "Collision.h"
#include "Score.h"
#include "Parameters.h"

class Game {
public:
    void initGame();   
    void runGame();
    ~Game();
        
private:   

    typedef enum game_status {
        START,
        RUN,
        FAIL,
        STEAK,
        GAME_OVER,
        WIN
    } game_status_t;
    
    bool additionalLife = false;
    game_status_t status;

    Map *map = nullptr;
    Paddle *paddle = nullptr;
    Ball *ball = nullptr;
    Ball *secondBall = nullptr;
    Bonus *bonus = nullptr;
    Bottom *bottom = nullptr;
    Score *score = nullptr;
    
    sf::RenderWindow *m_window = nullptr;
    sf::Clock *m_clock = nullptr;
    sf::Font *font = nullptr;
    sf::Text* gameOverText = nullptr;
    sf::Text* winText = nullptr;

    sf::Sprite sprite;
    sf::Texture texture;
    
    int livesCount = LIVES;
    std::vector<Live*>lives;

    static const int WINDOW_WIDTH = Parameters::WINDOW_WIDTH;
    static const int WINDOW_HEIGHT = Parameters::WINDOW_HEIGHT;
    static const int PADDING_BOTTOM = Parameters::PADDING_BOTTOM;
    static const int PADDING_LR = Parameters::PADDING_LR;
    static const int PADDING_TOP = Parameters::PADDING_TOP;
    static const int LIVES = Parameters::LIVES_COUNT;
    static const int LIVES_SIZE = Parameters::LIVES_SIZE;
    static const int POINTS = Parameters::SCORE_FOR_BLOCK;
    

    void drawMessage(sf::Text * text);

    void keyPressProcessing();
    void loadBackground();
    void activateBonus();
    bool saveLifeBonus();

    void createLives();
    void createScore();
    void createIcon();
    void createFont();
    
    void drawProcessing(float time);
    void ballProcessing();
    void bonusManage(float time);
    void bonusProcessing();

    void checkWinStatus();
    void gameOver();
    void win();
    void fail();
};


#endif // !GAME_H