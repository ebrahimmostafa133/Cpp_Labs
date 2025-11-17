#ifndef CUSTOM_DATATYPES_H
#define CUSTOM_DATATYPES_H

// --- 8-bit (1 byte) Types ---
typedef unsigned char       u8;     // Unsigned 8-bit integer (0 to 255)         
typedef signed char         i8;     // Signed 8-bit integer (-128 to 127)          

// --- 16-bit (2 byte) Types ---
typedef unsigned short      u16;    // Unsigned 16-bit integer                    
typedef signed short        i16;    // Signed 16-bit integer                    

// --- 32-bit (4 byte) Types ---
typedef unsigned int        u32;    // Unsigned 32-bit integer                                              
typedef signed int          i32;    // Signed 32-bit integer                          

// --- 64-bit (8 byte) Types ---
typedef unsigned long long  u64;    // Unsigned 64-bit integer                 
typedef signed long long    i64;    // Signed 64-bit integer                                 

// --- Example: Custom Boolean Type ---
// Can be used instead of 'bool' or standard C 'int' for clarity.
typedef int                 bool_t; // Simple integer-based boolean (0=false, non-zero=true)

#endif // CUSTOM_DATATYPES_H