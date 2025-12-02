#include <iostream>
#include "stringClass.h" 
#include "../custom_types.h" 

using namespace std;

String::String()
{
    data = nullptr;
    Size = 0;
}

String::String(const char* inputData)
{
    u32 i = 0;
    for(i = 0; inputData[i] != '\0'; i++); 
    
    this->Size = i;
    this->data = new char[Size];
    
    for(u32 j = 0; j < Size; j++)
    {
        this->data[j] = inputData[j];
    }
}

String::String(const String& s)
{
    this->Size = s.Size;
    this->data = new char[Size];
    
    for(u32 j = 0; j < Size; j++)
    {
        this->data[j] = s.data[j];
    }
}

void String::stringDisplay() const
{
    for(u32 j = 0; j < Size; j++)
    {
       cout << data[j];
    }
    cout << endl;
}

String String::operator+(const String& s) const
{
    u32 i = 0, j = 0;
    String res;

    res.Size = this->Size + s.Size;
    res.data = new char[res.Size];

    for(j = 0; j < this->Size; j++)
    {
        res.data[j] = this->data[j];
    }
    
    for(i = 0; i < s.Size; i++)
    {
        res.data[j + i] = s.data[i];
    }
    
    return res;
}


void String::operator=(const String& s)
{
    if (this == &s) 
    {
        return;
    }
    
    if(this->data != nullptr)
    {
        delete [] this->data; 
        this->data = nullptr;
    }
    
    this->Size = s.Size;
    this->data = new char[Size];
    for(u32 j = 0; j < Size; j++)
    {
        this->data[j] = s.data[j];
    }
}


String::~String()
{
    if(data != nullptr)
    {
        delete [] data; 
        data = nullptr;
    }
}