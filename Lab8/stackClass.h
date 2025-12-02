#ifndef STACKCLASS_H
#define STACKCLASS_H

#include "../custom_types.h" 

class Stack {
private:
    i32 m_top; 
    u32 m_size; 
    i32 *m_ptr; 

public:
    Stack();
    Stack(u32 input_size);
    ~Stack();
    
    Stack& operator=(const Stack& other);
    
    void push(i32 number);
    void pop();
    void pop(i32 &x);
    
    bool_t isEmpty() const;
    bool_t isFull() const;
    
    i32 peek() const;
    u32 getSize() const;
    void display() const;
};

#endif