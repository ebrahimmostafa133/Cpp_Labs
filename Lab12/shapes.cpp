#include "shapes.h"
#include <iostream>

using namespace std;

// =================================================================
// 3. Circle Implementations
// =================================================================

Circle::Circle() : center(0, 0), radius(0) {}

Circle::Circle(int x, int y, int r) : center(x, y), radius(r) {}

void Circle::draw() const {
    cout << "Drawing Circle: Center(" << center.getX() << ", " << center.getY() 
         << "), Radius: " << radius << endl;
}

// =================================================================
// 4. Line Implementations
// =================================================================

Line::Line() : start(0, 0), end(0, 0) {}

Line::Line(int x1, int y1, int x2, int y2) : start(x1, y1), end(x2, y2) {}

void Line::draw() const {
    cout << "Drawing Line: From(" << start.getX() << ", " << start.getY()
         << ") to (" << end.getX() << ", " << end.getY() << ")" << endl;
}

// =================================================================
// 5. Rect Implementations
// =================================================================

Rect::Rect() : ul(0, 0), lr(0, 0) {}

// Corrected constructor signature to match shapes.h
Rect::Rect(int x1, int y1, int x2, int y2) : ul(x1, y1), lr(x2, y2) {}

void Rect::draw() const {
    cout << "Drawing Rectangle: Upper-Left(" << ul.getX() << ", " << ul.getY() 
         << "), Lower-Right(" << lr.getX() << ", " << lr.getY() << ")" << endl;
}

// =================================================================
// 6. Picture Implementations
// =================================================================

Picture::Picture() : shapes(nullptr), shapeCount(0) {}

// Destructor: Responsible for deep cleanup (deleting all contained shapes)
Picture::~Picture() {
    cout << "Destroying Picture and its " << shapeCount << " shapes." << endl;
    for (int i = 0; i < shapeCount; ++i) {
        // Polymorphic deletion: relies on virtual ~Shape()
        delete shapes[i];
    }
    // Delete the array itself
    delete[] shapes;
}

// Setter: Picture takes ownership of the dynamically allocated array and its contents
void Picture::setShapes(Shape** newShapes, int count) {
    // Note: In a production environment, we should check if 'shapes' already holds memory
    // and delete it before assignment to prevent memory leaks.
    // For this demonstration, we assume setShapes is called only once.
    this->shapes = newShapes;
    this->shapeCount = count;
}

void Picture::paint() const {
    cout << "\n--- Painting Picture (" << shapeCount << " shapes) ---" << endl;
    for (int i = 0; i < shapeCount; ++i) {
        // Polymorphism in action: dynamically calls the correct draw() method
        shapes[i]->draw();
    }
    cout << "--------------------------------------" << endl;
}