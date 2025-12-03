// Filename: shapes.h
// Contains all class declarations for the Shape hierarchy.

#ifndef SHAPES_H
#define SHAPES_H

#include <iostream>

// =================================================================
// 1. Point Class Definition (Kept constructors/getters/setters inline)
// =================================================================

class Point {
private:
    int x;
    int y;

public:
    // Constructors
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
    
    // Setters
    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    
    // Getters
    int getX() const { return x; }
    int getY() const { return y; }
};

// =================================================================
// 2. Shape Abstract Base Class Definition
// =================================================================

class Shape {
public:
    // Pure virtual function
    virtual void draw() const = 0;
    
    // Virtual destructor (essential for polymorphic cleanup)
    virtual ~Shape() {}
};

// =================================================================
// 3. Derived Class: Circle Definition
// =================================================================

class Circle : public Shape {
private:
    Point center;
    int radius;

public:
    Circle();
    Circle(int x, int y, int r);
    void draw() const override;
};

// =================================================================
// 4. Derived Class: Line Definition
// =================================================================

class Line : public Shape {
private:
    Point start;
    Point end;

public:
    Line();
    Line(int x1, int y1, int x2, int y2);
    void draw() const override;
};

// =================================================================
// 5. Derived Class: Rect Definition
// =================================================================

class Rect : public Shape {
private:
    Point ul; // Upper-left
    Point lr; // Lower-right

public:
    Rect();
    // Corrected typo: 'int2' changed to 'int y2'
    Rect(int x1, int y1, int x2, int y2); 
    void draw() const override;
};

// =================================================================
// 6. Picture Class Definition
// =================================================================

class Picture {
private:
    Shape** shapes; // Array of Shape pointers (polymorphism)
    int shapeCount;

public:
    Picture();
    ~Picture();
    
    // Setter: Takes ownership of the array and the contained shapes
    void setShapes(Shape** shapes, int count);
    
    // Calls draw() on all shapes
    void paint() const;
};

#endif // SHAPES_H