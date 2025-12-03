#include "shapes_geo.h"
#include "../custom_types.h"
#include <cmath>
using namespace std;
// --- Triangle ---
float Triangle::calculateArea() {
    return (d1 * d2) / 2.0f; 
}
void Triangle::setBase(float base){
    this->d1 = base;
}
void Triangle::setHeight(float height){
    this->d2 = height;
}
float Triangle::getBase(){
    return d1;
}
float Triangle::getHeight(){
    return d2;
}

// --- Rect ---
float Rect::calculateArea(){
    return d1 * d2;
}
void Rect::setLength(float length){
    this->d1 = length;
}
void Rect::setWidth(float width){
    this->d2 = width;
}
float Rect::getLength(){
    return d1;
}
float Rect::getWidth(){
    return d2;
}

// --- Circle (Private Inheritance) ---
float Circle::calculateArea() {
    float result = M_PI * d1 * d1;
    return result;
}
void Circle::setRadius(float radius) {
    // d1 is used for radius
    this->d1 = radius;
}
float Circle::getRadius() {
    return d1;
}

// --- Square (Private Inheritance) ---
float Square::calculateArea() {
    return Rect::calculateArea();
}

void Square::setSide(float side) {
    Rect::setLength(side);
    Rect::setWidth(side); 
}

float Square::getSide() {
    // Call Rect's protected getter
    return Rect::getLength();
}