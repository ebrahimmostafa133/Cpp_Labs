#ifndef STRINGCLASS_H_INCLUDED
#define STRINGCLASS_H_INCLUDED

#include "../custom_types.h" 

class String
{
private:
    char * data;
    u32 Size; 

public:
    String();
    ~String(); 
    String(const char* data);
    
    // Copy Constructor - passing by const reference is standard
    String(const String& s); 

    // Display function - marked const
    void stringDisplay() const; 
    
    // Operator Overloads - marked const where appropriate
    String operator+(const String& s) const;
    void operator=(const String& s);
};


#endif // STRINGCLASS_H_INCLUDED