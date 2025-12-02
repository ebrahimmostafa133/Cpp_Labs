#include <iostream>
#include "stringClass.h" 
#include "../custom_types.h" 

using namespace std;

int main()
{    
    // Test Constructor and Display
    String s1("Data"); 
    cout << "s1: ";
    s1.stringDisplay();

    // Test Copy Constructor
    String s2 = s1; 
    cout << "s2 (Copy): ";
    s2.stringDisplay();

    // Test Operator= and Constructor from const char*
    String s3;
    s3 = "Structure"; 
    cout << "s3 (Assignment): ";
    s3.stringDisplay();
    
    // Test Operator+
    String s4 = s1 + s3; 
    cout << "s4 (s1 + s3): ";
    s4.stringDisplay();
    
    return 0;
}