#include "Paddle.h"
#include "Bonus.h"


void Paddle::loadSprites() {
    texture.loadFromFile("images\\paddles.png");
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(1055, 240, 83, 16));
    sprite.setScale(getWidth() / sprite.getLocalBounds().width, getHeight() / sprite.getLocalBounds().height);
}

Paddle::Paddle(int winW, int winH, int width, int height) {
    setWidth(width);
    setHeight(height);
    setX(winW / 2.0 - (size.x / 2.0));
    setY(winH);
    this->displacement.x = 0;
    this->displacement.y = 0;
    this->direction = 0;
    setSpeed(0);
    this->loadSprites();
}

void Paddle::update(float time, Bonus &bonus) {
    padleBonusManager(bonus);
    switch (direction) {
    case 0: displacement.x = getSpeed(); displacement.y = 0; break;
    case 1: displacement.x = -getSpeed(); displacement.y = 0; break; }
    setX(getX() + displacement.x * time);
    sprite.setPosition(getX(), getY());
    setSpeed(0);
}

void Paddle::padleBonusManager(Bonus &bonus) {
    if (bonusActiveTime == 0) {        
        bonusInactive();
        bonus.fail();
        if (this->isSteak) {
            this->isSteak = false;
        } else changeSize(0);
    }
}

void Paddle::changeSize(int mode) {
    float currentwidth = getWidth();
    float center = getCenterX();
    switch (mode) {
    case -1:  
        sizeDelta = -(currentwidth*SIZE_CHANGE_FACTOR); 
        setWidth(currentwidth + sizeDelta);
        break;
    case 0:  
        setWidth(getWidth() - sizeDelta); 
        sizeDelta = 0;
        break;
    case 1:  
        sizeDelta = (currentwidth*SIZE_CHANGE_FACTOR); 
        setWidth(currentwidth + sizeDelta); 
        break;
    }
    this->setX(center - (this->getWidth() / 2.0));
    sprite.setScale(getWidth()/ sprite.getLocalBounds().width,getHeight() / sprite.getLocalBounds().height);
}


sf::FloatRect Paddle::getGlobalBounds() {
    return sf::FloatRect(getX(), getY(), getWidth(), 1);
}