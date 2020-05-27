#include "Bonus.h"

Bonus::Bonus(int width, int height) {
    setX(0);
    setY(0);
    setWidth(width);
    setHeight(height);
    setSpeed(Parameters::BONUS_SPEED);
    type = NONE;
    loadSprites();
}

Bonus::~Bonus() {}

void Bonus::loadSprites() {
    texture.loadFromFile("images\\arkanoid.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(TexSet::BONUS_X, TexSet::BONUS_Y, TexSet::BONUS_WIDTH, TexSet::BONUS_HEIGHT));
    sprite.setScale(getWidth() / sprite.getLocalBounds().width, getHeight() / sprite.getLocalBounds().height);
}

void Bonus::createBonus(Block *block) {
    setX(block->getCenterX()+getWidth()/2);
    setY(block->getY() );
    sprite.setPosition(getX(), getY());
    setBonusType();
    inMove = true;
}

void Bonus::deleteBonus() {
    setX(0);
    setY(0);
    type = NONE;
}

void Bonus::setBonusType() {
    int tmp = getRandomNumber(1, 6);
    type = bonusType_t(tmp);
}

Bonus::bonusType_t Bonus::getBonusType() {
    return type;
}

void Bonus::update(float time) {
    if (inMove) {
        setY(getY() + getSpeed());
        sprite.setPosition(getX(), getY());
    }
}

void Bonus::activate(){
    activated = true;
}

bool Bonus::isActiv() {
   return activated;
}

 void Bonus::fail() {
    inMove = false;
    activated = false;
    run = false;
    type = NONE;
}

bool Bonus::isExist() {
    if (type != NONE) {
        return true;
    } else return false;
}

bool Bonus::isRun() {
    return run;
}

void Bonus::runBonus() {
    run = true;
}