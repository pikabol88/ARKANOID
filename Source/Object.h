#ifndef OBJECT_H
#define OBJECT_H
#pragma once
#include <SFML/Graphics.hpp>
#include "Parameters.h"
#include <ctime>

class Object {

public:

    virtual sf::FloatRect getRect() const;
    virtual sf::FloatRect getGlobalBounds(); 
      
    float getSpeed() const;
    void setSpeed(float newSpeed);

    // position helpers --------------------------------------------------------  
    float getX() const;
    float getY() const;
    void setX(float x);
    void setY(float y);
    float getCenterX() const;
    float getCenterY() const;

    // size helpers ------------------------------------------------------------
    float getWidth() const;
    float getHeight() const;
    void setWidth(float x);
    void setHeight(float y);
    
    virtual void resizeSprite(sf::Vector2f size);
    void drawObject(sf::RenderWindow * m_window);

    int bonusActiveTime = -1;
    bool bonuseIsActivated = false;

    bool bonusTimeManager();
    virtual void bonusActive();
    virtual void bonusInactive();

    
protected:
    sf::Vector2f coordinate;
    sf::Vector2f size;
    sf::Vector2f displacement;
    sf::Sprite sprite;
    sf::Texture texture;

    float speed;
    virtual void loadSprites() = 0;
       
};
#endif // !OBJECT_H

int getRandomNumber(int min, int max);