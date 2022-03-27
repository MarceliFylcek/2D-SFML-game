#pragma once
#include <SFML/Graphics.hpp>
//Vector class made for storing data about collisions
class Vector4b
{
public:
    Vector4b(bool l, bool r, bool t, bool d);
    Vector4b();
    bool l, r, t, d;
};

