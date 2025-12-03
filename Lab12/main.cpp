#include "shapes.h"
#include <iostream>

using namespace std;

/**
 * @brief Helper function to create a dynamic array of Shape pointers.
 * @param count The size of the array to create.
 * @return A new array of Shape pointers.
 */
Shape** createShapesArray(int count) {
    return new Shape*[count];
}

int main() {

    Shape* circle = new Circle(10, 20, 5);
    Shape* rect = new Rect(50, 60, 100, 120);
    Shape* line = new Line(5, 5, 95, 95);

    const int NUM_SHAPES = 3;
    Shape** shapeArray = createShapesArray(NUM_SHAPES);

    // Populate the array. Picture will take ownership of these pointers.
    shapeArray[0] = circle;
    shapeArray[1] = rect;
    shapeArray[2] = line;

    Picture myScene;

    myScene.setShapes(shapeArray, NUM_SHAPES);

    myScene.paint();

    
    return 0;
}