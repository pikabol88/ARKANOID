#ifndef SCORE_H
#define SCORE_H
#pragma once
#include <SFML/Graphics.hpp>

class Score : public sf::Text {
public:
    Score(sf::Font &font, unsigned int size);
    void incrementScore();
    void incrementScore(int points);
    void update();

private:
    int value;
};
#endif // !SCORE_H