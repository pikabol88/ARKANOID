#ifndef PADLE_H
#define PADLE_H
#pragma once
#include <SFML/Graphics.hpp>

#include "Object.h"
#include "Bonus.h"

class Paddle: public Object {

public:
    Paddle(int winW, int winH, int width, int height);

    bool isSteak = false;
    int direction;

    void update(float time, Bonus & bonus);
    void changeSize(int mode);

    void padleBonusManager(Bonus & bonus);
    sf::FloatRect getGlobalBounds() override;
private:

    float sizeDelta;
   
    const float SIZE_CHANGE_FACTOR = Parameters::PADDLE_CHANDE_COEFFICIENT;
    void loadSprites()override;
};
#endif // !PADLE_H