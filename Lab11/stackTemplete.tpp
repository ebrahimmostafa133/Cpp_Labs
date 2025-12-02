#include <iostream>
#include "stackTemplete.h"
using namespace std;


template<typename Type1>
Stack<Type1>::Stack(u32 stackElements)
{
    this->stackCapacity = stackElements;
    if(stackElements > 0)
    {
        this->stackPtr = new Type1[stackElements];
        this->tos = -1;
    }
    else
    {
        this->stackPtr = nullptr;
    }
}

template<typename Type1>
Stack<Type1>::Stack(const Stack<Type1>& s)
{
    this->tos = s.tos;
    this->stackCapacity = s.stackCapacity;
    this->stackPtr = new Type1 [this->stackCapacity];
    for(i32 i = 0; i <= this->tos; i++)
    {
        this->stackPtr[i] = s.stackPtr[i];
    }
}

template<typename Type1>
Stack<Type1>::~Stack()
{
    if(this->stackPtr != nullptr)
    {
        delete [] stackPtr;
    }
}

template<typename Type1>
bool_t Stack<Type1>::isStackFull() const
{
    return this->tos == (i32)(this->stackCapacity - 1);
}

template<typename Type1>
bool_t Stack<Type1>::isStackEmpty() const
{
    return this->tos == -1;
}

template<typename Type1>
void Stack<Type1>::stackDisplay() const
{
    if(this->tos != -1)
    {
        for(i32 i = 0; i <= this->tos; i++)
        {
            cout << this->stackPtr[i] << " | ";
        }
        cout << endl;
    }
    else
    {
        cout << "Stack is Empty." << endl;
    }
}

template<typename Type1>
bool_t Stack<Type1>::push(const Type1& element)
{
    if(isStackFull())
    {
        return 0;
    }
    else
    {
        tos++;
        this->stackPtr[this->tos] = element;
        return 1;
    }
}

template<typename Type1>
bool_t Stack<Type1>::pop(Type1& popedElement)
{
    if(isStackEmpty())
    {
        return 0;
    }
    else
    {
        popedElement = this->stackPtr[this->tos];
        this->tos--; 
        return 1;
    }
}

template<typename Type1>
void Stack<Type1>::stackTop() const
{
    if (!isStackEmpty())
        cout << "Top element is: " << this->stackPtr[this->tos] << endl;
    else
        cout << "Stack is empty, no top element." << endl;
}

template<typename Type1>
bool_t Stack<Type1>::operator==(const Stack<Type1>& s) const
{
    if(this->tos != s.tos || this->stackCapacity != s.stackCapacity)
        return 0;

    for(i32 i = 0; i <= this->tos; i++)
    {
        if(this->stackPtr[i] != s.stackPtr[i])
        {
            return 0;
        }
    }
    return 1;
}

template<typename Type1>
Stack<Type1>& Stack<Type1>::operator=(const Stack<Type1>& s)
{
    if(this == &s)
        return *this;

    delete [] this->stackPtr;

    this->tos = s.tos;
    this->stackCapacity = s.stackCapacity;
    
    this->stackPtr = new Type1 [this->stackCapacity];
    
    for(i32 i = 0; i <= s.tos; i++)
    {
        this->stackPtr[i] = s.stackPtr[i];
    }
    return *this;
}