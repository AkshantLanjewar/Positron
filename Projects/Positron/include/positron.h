#pragma once
#include <iostream>

#include "positron_graphics/positron_graphics.h"

class Positron {
public:
    Positron();
    ~Positron();

private:
    PositronGraphics::PositronGraphics _graphics;
};