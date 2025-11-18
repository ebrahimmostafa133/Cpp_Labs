#include "string_lib.h"

// calculate the length of a string
u32 string_length(u8 str []){
    u32 length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// compare two strings  
u32 str_cmp(u8 str1[], u8 str2[]){
    //return 0 if equal, 1 if str1 > str2, -1 if str1 < str2
    // work on the length & ASCII values of characters
    u32 i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] < str2[i]) {            //compare character by character
            return -1;
        } else if (str1[i] > str2[i]) {     //compare character by character
            return 1;
        }
        i++;
    }
    if (str1[i] == '\0' && str2[i] == '\0') {   //strings are equal
        return 0;                                
    } else if (str1[i] == '\0') {                   //str2 is longer
        return -5;
    } else {                                        //str1 is longer
        return 5;
    }
}

// transform lowercase to uppercase
void to_uppercase(u8 str[]){
    u32 i = 0;
    while (str[i] != '\0') {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - ('a' - 'A');
        }
        i++;
    }
}

// transform uppercase to lowercase
void to_lowercase(u8 str[]){
    u32 i = 0;
    while (str[i] != '\0') {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + ('a' - 'A');
        }
        i++;
    }
}

// concatenate two strings
void str_concat(u8 str1[], u8 str2[], u32 size_str1){
    //check that str1 has enough space to hold str2
    u32 len1 = string_length(str1);
    u32 len2 = string_length(str2);
    if (len1 + len2 + 1 > size_str1) {
        return; // not enough space to concatenate
    }
    u32 i = 0;
    while (str2[i] != '\0') {
        str1[len1 + i] = str2[i];
        i++;
    }
    str1[len1 + i] = '\0'; // null terminate str1
}

//copy a string
void str_copy(u8 str1[], u8 str2[], u32 size_str1){
    u32 i = 0;
    while (str2[i] != '\0' && i < size_str1 - 1) {
        str1[i] = str2[i];
        i++;
    }
    str1[i] = '\0'; // null terminate str1
} 