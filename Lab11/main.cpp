#include <iostream>
#include "stackTemplete.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;

        int x=9;

    Stack<u32> s(30.9);
    Stack<u32> s2(100);
    s.push(30);
    s2.push(100);
    //s2=s;
    s.stackDisplay();
    s2.stackDisplay();
  
    return 0;
}