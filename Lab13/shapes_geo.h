#ifndef SHAPES_GEO_H
#define SHAPES_GEO_H

#include "../custom_types.h"
#include <iostream> 

using namespace std;

// Base Class as per Diagram (GeoShape)
class GeoShape {
    protected:
        // # d1 : float
        float d1;
        // # d2 : float
        float d2;
    public:
        // Area calculation must be virtual and return a float
        virtual float calculateArea() = 0;
        virtual ~GeoShape() = default; 
};

// --- Triangle (Public +) ---
class Triangle : public GeoShape {
    public:
        float calculateArea() override;
        void setBase(float base);
        void setHeight(float height);
        float getBase();
        float getHeight();
};

// --- Rect (Public +) ---
class Rect : public GeoShape {
    public:
        float calculateArea() override;
        void setLength(float length);
        void setWidth(float width);
        float getLength();
        float getWidth();
};

// --- Circle (Private -) ---
class Circle : private GeoShape {
    public:
        // Must expose calculateArea publicly, and use d1 for radius
        float calculateArea() override; 
        void setRadius(float radius);
        float getRadius();
};

// --- Square (Private - from Rect) ---
class Square : private Rect {
    public:
        // Must expose calculateArea publicly
        float calculateArea() override; 
        void setSide(float side);
        float getSide();
};

#endif