#include "string_lib.h"
#include <iostream>

int main() {
    char str1[50] = "Hello, ";
    char str2[] = "World!";
    
    std::cout << "String 1: " << str1 << std::endl;
    std::cout << "String 2: " << str2 << std::endl;

    // Test string_length
    u32 len1 = string_length(str1);
    u32 len2 = string_length(str2);
    std::cout << "Length of String 1: " << len1 << std::endl;
    std::cout << "Length of String 2: " << len2 << std::endl;

    // Test str_cmp
    int cmp_result = str_cmp(str1, str2);
    std::cout << "Comparison Result: " << cmp_result << std::endl;

    // Test to_uppercase
    to_uppercase(str2);
    std::cout << "String 2 to Uppercase: " << str2 << std::endl;

    // Test to_lowercase
    to_lowercase(str2);
    std::cout << "String 2 to Lowercase: " << str2 << std::endl;

    // Test str_concat
    str_concat(str1, str2, len1);
    std::cout << "Concatenated String: " << str1 << std::endl;

    // Test str_copy
    char str3[50];
    str_copy(str3, str1, len1 + string_length(str2));
    std::cout << "Copied String: " << str3 << std::endl;

    return 0;
}