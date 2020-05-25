#ifndef PARAMETERS_H
#define PARAMETERS_H
#pragma once

class Parameters {

public:
    //Main game settings
    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 600;
    static const int PADDING_BOTTOM = 50;
    static const int PADDING_LR = 20;
    static const int PADDING_TOP = 10;
    static const int LIVES_SIZE = 20;
    static const int FRAMERATE = 200;
    static const int FREQUENCY = 800;
    static const float BACKGROUND_SCALE;
    static const unsigned int LIVES_COUNT = 5;

    //Ball settings
    static const int BALL_WIDTH = 13;
    static const int BALL_HEIGHT = 13;
    static const float BALL_SPEED_INC;
    static const float BALL_SPEED_DEC;
    static const float BALL_SPEED;
    
    //Bonus settings
    static const int BONUS_WIDTH = 20;
    static const int BONUS_HEIGHT = 20;
    static const float BONUS_SPEED;
    static const int BONUS_ACTIVE_TIME = 3;

    //Rand Coeficient
    static const int RAND_COEF = 100;
    static const int START_RAND = 0;
    static const int END_RAND = 20;

    //Random angle deviation
    static const float X_ANGLE_D;
    static const float Y_ANGLE_D;

    //Paddle settings
    static const int PADDLE_WIDTH = 100;
    static const int PADDLE_HEIGHT = 20;
    static const int LEFT = 1;
    static const int RIGHT = 0;
    static const float PADDLE_SPEED;
    static const int PADDLE_PADDING = 5;
    static const int BOTTOM_HEIGHT = 25;
    static const float PADDLE_CHANDE_COEFFICIENT;

    //Score settings
    static const int SCORE_FONT = 30U;
    static const int FAIL_SCORE = -50;
    static const int SCORE_FOR_BLOCK = 5;

    //Text settings
    static const unsigned int GAME_OVER_FONT_SIZE = 120U;
    static const unsigned int WIN_FONT_SIZE = 120U;
       
    //Block settings    
    static const float MOVING_BLOCK_SPEED;
    static const int BLOCK_IMG_WIDTH = 385;
    static const int BLOCK_IMG_HEIGHT = 130;
    static const int USUAL_BLOCK_NUM = 10;
    static const int UNKILLED_BLOCK_NUM = 20;
    static const int STONE_BLOCK_NUM = 30;
    static const int MAP_PATTERN_NUM = 10;

    //Map settings
    static const int BLOCKS_IN_ROW = 8;
    static const int BLOCKS_IN_COL = 14;
    static const int MAP_PADDING_TOP = 40;
    static const int MAP_PADDING_WALL = 55;
    static const int BLOCK_LIVES = 3;

};

#endif // !PARAMETERS_H