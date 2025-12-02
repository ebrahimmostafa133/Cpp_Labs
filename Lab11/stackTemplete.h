#ifndef STACKTEMPLETEHEADER_H
#define STACKTEMPLETEHEADER_H

#include "../custom_types.h" 
#include <iostream>

template<typename Type1>
class Stack{
private:
    Type1 * stackPtr;
    i32 tos; 
    u32 stackCapacity; 

public:
    Stack(u32 stackElements = 5);

    Stack(const Stack<Type1>& s);

    ~Stack();

    bool_t isStackFull() const;
    bool_t isStackEmpty() const;

    void stackDisplay() const;
    bool_t push(const Type1& element);
    bool_t pop(Type1& popedElement); 

    bool_t operator==(const Stack<Type1>& s) const;
    Stack<Type1>& operator=(const Stack<Type1>& s); 

    void stackTop() const;
};

#include "stackTemplete.tpp"

#endif // STACKTEMPLETEHEADER_H