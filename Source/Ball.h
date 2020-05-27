#ifndef BALL_H
#define BALL_H
#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>

#include "Object.h"
#include "Map.h"
#include "Paddle.h"
#include "Bonus.h" 
#include "Score.h"
#include "Parameters.h"

//! Сlass implementing ball behavior
class Ball : public Object {

public:
    //!ball status Types
    typedef enum ballState {
        IN_GAME,//!<ball in the game
        FAIL,//!<ball fell
        STEAK//!<ball glued to paddle
    } state_t;

    Ball(int winW, int winH, int ballW, int ballH);
    ~Ball();

    //!Main ball method - ball movement in the game
    bool moveBall(Paddle & paddle, Map &map, Bonus & bonus, Score & score, int winW, int winH);
    /*! Ball speed ​changes
    param mode -1 to decrease, 0 to reset, 1 to decrease*/
    void changeSpeed(int mode);    
    /*! Ball sticks to the center of the paddle*/
    void stickPadle(Object & paddle);
    /*! Ball sticks to to a specific place in the paddle*/
    void stickPadle(Object & paddle, sf::Vector2f current_coordinates);

    void setState(bool newState);
    Ball::state_t getState();
    /*!Information about the ball is copied to another ball*/
    void copy(Ball & secondBall);
    /*!Changing of the ball vertical direction*/
    void changeVDirection();
    /*!Second ball collision handling*/
    void checkAnotherBallCollision(Object & secondBall);

private:
    
    state_t state;   
    /*!The difference between the initial and current speeds*/
    float speedDelta = 0;
    
    /*!The main blocks and ball collision handling*/
    void checkMapCollision(Map & map, Bonus * bonus, Score * score, int type);
    /*!Vertecal collision handling*/
    bool checkBlockVerticalCollision(Map & map, Bonus * bonus, Block * block, Score * score);
    /*!Horizontal collision handling*/
    bool checkBlockHorizontalCollision(Map & map, Bonus * bonus, Block * block, Score * score);
    /*!With bonus block collision handling*/
    void checkBonusCollision(Bonus * bonus, Block * block);
    /*!Wall collision handling*/
    void checkWallCollision(int winH);
    /*!Check is rhe ball fail?*/
    bool checkFail(int winW);
    /*!Paddle collision handling*/
    bool checkPadleCollision(Object & paddle);
    /*!Ыtops performing the bonus if its time is up*/
    void stopBallBonus(Bonus & bonus);
    /*Sstops performing the bonus if its time is up*/
    void setRandDisplacement();

    void loadSprites() override;    

    
};
#endif // !PADLE_H
