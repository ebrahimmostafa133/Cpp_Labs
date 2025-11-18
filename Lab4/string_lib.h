#include "custom_datatypes.h"

#ifndef STRING_LIB_H
#define STRING_LIB_H

// calculate the length of a string
u32 string_length(u8 str []);

// compare two strings  
u32 str_cmp(u8 str1[], u8 str2[]);

// transform lowercase to uppercase
void to_uppercase(u8 str[]);

// transform uppercase to lowercase
void to_lowercase(u8 str[]);

// concatenate two strings
void str_concat(u8 str1[], u8 str2[], u32 size_str1);

//copy a string
void str_copy(u8 str1[], u8 str2[], u32 size_str1); 






#endif // STRING_LIB_H