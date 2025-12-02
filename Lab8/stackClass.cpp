#include "stackClass.h"
#include <iostream>
#include "../custom_types.h"

using namespace std;

Stack::Stack() {
    m_size = 10;
    m_top = -1;
    m_ptr = new i32[m_size];
}

Stack::Stack(u32 input_size) {
    m_size = input_size;
    m_top = -1;
    m_ptr = new i32[m_size];
}

Stack::~Stack() {
    delete[] m_ptr;
}

bool_t Stack::isFull() const {
    return m_top == (i32)(m_size - 1);
}

bool_t Stack::isEmpty() const {
    return m_top == -1;
}

void Stack::push(i32 number) {
    if(isFull()) return;
    m_top++;
    m_ptr[m_top] = number;
}

void Stack::pop(){
    if(isEmpty()) return;
    m_top--;
}

void Stack::pop(i32 &x){
    if(isEmpty()) return;
    x = m_ptr[m_top];
    m_top--;
}

i32 Stack::peek() const {
    if(isEmpty()) {
        cerr << "Error: Cannot peek on an empty stack." << endl;
        return 0; 
    }
    return m_ptr[m_top];
}

u32 Stack::getSize() const {
    return (u32)(m_top + 1);
}

void Stack::display() const {
    for(i32 i = m_top; i >= 0; i--) {
        cout << m_ptr[i] << " ";
    }
    cout << "\n";
}

Stack& Stack::operator=(const Stack& other) {
    if(this == &other) {
        return *this;
    }
    
    delete[] m_ptr;
    
    m_size = other.m_size;
    m_top = other.m_top;
    
    m_ptr = new i32[m_size];
    
    for(i32 i = 0; i <= m_top; i++) {
        m_ptr[i] = other.m_ptr[i];
    }
    return *this;
}