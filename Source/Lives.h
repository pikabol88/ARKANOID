#ifndef LIVES_H
#define LIVES_H
#pragma once
#include <SFML/Graphics.hpp>

#include "Object.h"


class Live : public Object {
public:

    Live(float coordinateX, float coordinateY, int liveW, int liveH);

    void failLive();
    void drawingLive(sf::RenderWindow * m_window);  

private:
    void loadSprites() override;
};
#endif // !PADLE_H