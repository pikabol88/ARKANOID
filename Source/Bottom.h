#ifndef BOTTOM_H
#define BOTTOM_H
#pragma once
#include <SFML/Graphics.hpp>

#include "Object.h"

class Bottom :public Object {

public:

    Bottom(int x, int y, int width, int height);
    ~Bottom();

protected:

    virtual void loadSprites() override;
};

#endif // !BOTTOM_H
