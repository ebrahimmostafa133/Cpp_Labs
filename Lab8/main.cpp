#include <iostream>
#include "stackClass.h" 
#include "../custom_types.h" 

using namespace std;

int main()
{
    cout << "--- Stack Class Demonstration ---" << endl;
    
    u32 initial_size = 5;
    Stack stack1(initial_size); 
    
    cout << "Stack 1 created with size: " << initial_size << endl;
    
    stack1.push(10);
    stack1.push(20);
    stack1.push(30);
    
    cout << "After pushing 10, 20, 30:" << endl;
    cout << "Stack 1 contents (Top to Bottom): ";
    stack1.display();
    cout << "Current Size: " << stack1.getSize() << endl;

    i32 top_element = stack1.peek();
    cout << "Peeked element: " << top_element << endl;
    
    i32 popped_value;
    stack1.pop(popped_value);
    cout << "Popped value: " << popped_value << endl;
    
    bool_t empty_status = stack1.isEmpty();
    cout << "Is Stack 1 empty? (0=False, 1=True): " << empty_status << endl;
    
    Stack stack2;
    stack2.push(999);
    
    cout << "\nStack 2 before assignment: ";
    stack2.display();
    
    stack2 = stack1;
    
    cout << "Stack 1 (original): ";
    stack1.display();
    
    cout << "Stack 2 (after assignment from stack1): ";
    stack2.display();
    
    stack1.pop();
    stack1.pop();
    
    cout << "\nStack 1 after final pops: ";
    stack1.display();
    
    if (stack1.isEmpty()) {
        cout << "Stack 1 is now empty." << endl;
    }
    
    return 0;
}