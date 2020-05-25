#include"Object.h"

float Object::getX() const {
    return coordinate.x;
}

float Object::getY() const {
    return coordinate.y;
}

void Object::setX(float x) {
    coordinate.x = x;
}

void Object::setY(float y) {
    coordinate.y = y;
}

float Object::getCenterX() const {
    return (this->getX() + this->getWidth() / 2.0);
}

float Object::getCenterY() const {
    return (this->getY() + this->getHeight() / 2.0);
}

float Object::getWidth() const {
    return size.x;
}

float Object::getHeight() const {
    return size.y;
}

void Object::setWidth(float x){
    size.x = x;
}

void Object::setHeight(float y){
    size.y = y;
}

float Object::getSpeed() const {
    return speed;
}

void Object::setSpeed(float newSpeed) {
    speed = newSpeed;
}

sf::FloatRect Object::getRect() const {
    return sf::FloatRect(coordinate.x, coordinate.y, size.x, size.y);
}

sf::FloatRect Object::getGlobalBounds() {
    return sprite.getGlobalBounds();
}

void Object::resizeSprite(sf::Vector2f size) {
    sf::Vector2f currentSize(this->sprite.getLocalBounds().width, this->sprite.getLocalBounds().height);
    this->sprite.setScale(size.x / currentSize.x, size.y / currentSize.y);
}

void Object::drawObject(sf::RenderWindow *m_window){
    sprite.setPosition(coordinate.x, coordinate.y);
    m_window->draw(sprite);
}

bool Object::bonusTimeManager() {
    if (this->bonuseIsActivated) {
        this->bonusActiveTime--;
        return true;
    }
    return false;
}

void Object::bonusActive() {
    bonusActiveTime = Parameters::BONUS_ACTIVE_TIME;
    bonuseIsActivated = true;
}

void Object::bonusInactive() {
    bonusActiveTime = -1;
    bonuseIsActivated = false;
}

int getRandomNumber(int min, int max) {
    srand(clock());
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}


