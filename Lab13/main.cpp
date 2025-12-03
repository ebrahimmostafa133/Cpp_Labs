#include <iostream>
#include <vector>
#include "shapes_geo.h"

using namespace std;
#include <iomanip>

i32 main() {
    cout << fixed << setprecision(2);

    Triangle tri;
    tri.setBase(8.5f);
    tri.setHeight(6.0f);
    cout << "Triangle (Base 8.5, Height 6.0) Area: " << tri.calculateArea() << endl;

    Rect rect;
    rect.setLength(10.2f);
    rect.setWidth(5.0f);
    cout << "Rect (10.2x5.0) Area: " << rect.calculateArea() << endl;

    Circle circ;
    circ.setRadius(4.0f);
    cout << "Circle (Radius 4.0) Area: " << circ.calculateArea() << endl;

    Square sq;
    sq.setSide(7.5f);
    cout << "Square (Side 7.5) Area: " << sq.calculateArea() << endl;

    cout << "\n--- Demonstrating Polymorphism (Publicly Inherited Shapes Only) ---\n" << endl;

    vector<GeoShape*> public_shapes;
    
    public_shapes.push_back(&rect);
    public_shapes.push_back(&tri);

    i32 i = 1;
    for (const auto& shape : public_shapes) {
        cout << "Public Shape " << i++ << " calculated area: " << shape->calculateArea() << endl;
    }

    return 0;
}
