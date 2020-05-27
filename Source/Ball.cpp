#include"Ball.h"


//Объединить в общий конструктор
Ball::Ball(int winW, int winH, int ballW, int ballH) {
    state = FAIL;
    setWidth(ballW);
    setHeight(ballH);
    setX(winW / 2.0 - size.x / 2.0);
    setY(coordinate.y = winH - size.y);
    setSpeed(Parameters::BALL_SPEED);
    this->displacement.x = getSpeed() / 2;
    this->displacement.y = getSpeed() / 2;
    this->loadSprites();
}
Ball::~Ball(){}
void Ball::changeSpeed(int moode) {
    sf::Vector2i sign;
    (displacement.x > 0) ? (sign.x = 1):(sign.x = -1);
    (displacement.y > 0) ? (sign.y = 1) : (sign.y = -1);

    switch (moode) {
    case -1: speedDelta = -getSpeed() * Parameters::BALL_SPEED_DEC; setSpeed(getSpeed() - getSpeed() * Parameters::BALL_SPEED_DEC); break;
    case 0:  setSpeed(getSpeed() - speedDelta); speedDelta = 0; break;
    case 1: speedDelta = getSpeed() * Parameters::BALL_SPEED_INC; setSpeed(getSpeed() + getSpeed() * Parameters::BALL_SPEED_INC);  break;
    default: break; }

    displacement.x = getSpeed() / 2 * sign.x;
    displacement.y = getSpeed() / 2 * sign.y;
}

void Ball::changeVDirection() {
    displacement.y = -displacement.y;
}

void Ball::loadSprites() {
    texture.loadFromFile("images\\arkanoid.png");
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setColor(sf::Color::Cyan);
    sprite.setTextureRect(sf::IntRect(TexSet::BALL_X, TexSet::BALL_Y, TexSet::BALL_WIDTH, TexSet::BALL_HEIGHT));
    sprite.setScale(getWidth() / sprite.getLocalBounds().width, getHeight()/ sprite.getLocalBounds().height);
}

void Ball::setState(bool inGame) {
    if (inGame) {
        state = IN_GAME;
    }
}

Ball::state_t Ball::getState() {
    return state;
}


void Ball::setRandDisplacement() {
    double randCoef = Parameters::RAND_COEF;
    float del = static_cast<float>(getRandomNumber(static_cast<int>((getSpeed()*Parameters::X_ANGLE_D)*randCoef), static_cast<int>(((getSpeed() - Parameters::Y_ANGLE_D *getSpeed()))*randCoef)));
    displacement.x = del/randCoef;
    int sign = getRandomNumber(Parameters::START_RAND, Parameters::END_RAND);
    (sign > (Parameters::START_RAND + Parameters::END_RAND)/2) ? (displacement.x = displacement.x) : (displacement.x = -displacement.x);
    displacement.y = -(getSpeed() - fabs(displacement.x));
}

void Ball::stickPadle(Object &paddle) {
    coordinate.x = paddle.getX() + ((paddle.getWidth()) / 2)-(size.x/2);
    coordinate.y = paddle.getY() - size.y;
}

void Ball::stickPadle(Object &paddle, sf::Vector2f current_coordinates) {
    setX(current_coordinates.x);
    setY(current_coordinates.y);
}

bool Ball::checkFail(int winW) {
    if (getY() > winW) {
        state = FAIL;    
        return 1;
    }
    return 0;
}

void Ball::stopBallBonus(Bonus &bonus) {
    if (bonuseIsActivated && bonusActiveTime == 0) {
        changeSpeed(0);
        bonusInactive();
        bonus.fail();
    }
}

bool Ball::moveBall(Paddle &paddle, Map &map, Bonus &bonus,Score &score, int winW, int winH) {
    stopBallBonus(bonus);
    if (state != FAIL && state != STEAK) {
        setX(getX() + displacement.x);
        checkMapCollision(map, &bonus,&score, 0);
        setY(getY() + displacement.y);
        checkMapCollision(map, &bonus, &score, 1);
        checkWallCollision(winW);

        if (checkPadleCollision(paddle)) {
            setRandDisplacement();
            this->bonusTimeManager();
            if (paddle.bonusTimeManager()) {
                if (paddle.isSteak) {
                    stickPadle(paddle, coordinate);
                    state = STEAK;
                }
            }
        }
        if (checkFail(winH)) {
            stickPadle(paddle);
            setRandDisplacement();
            sprite.setPosition(getX(), getY());
            return 0;
        }
        sprite.setPosition(getX(), getY());
    } else {
        stickPadle(paddle);
        sprite.setPosition(getX(), getY());
        return 1;
    }  
    return 1;
}


void Ball::copy(Ball &secondBall) {
    setX(secondBall.getX());
    setY(secondBall.getY());
    setWidth(secondBall.getWidth());
    setHeight(secondBall.getHeight());
    speedDelta = secondBall.speedDelta;
}