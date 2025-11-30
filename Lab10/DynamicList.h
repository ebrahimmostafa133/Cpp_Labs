#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include <string>
#include <iostream>
#include <cctype>

using namespace std;

class DynamicList {
private:
    struct Node {
        string data;   // stored as string
        string type;   // "int", "double", "string"
        Node* next;
    };

    Node* head;
    int list_size;

public:
    DynamicList();
    ~DynamicList();

    void append(const string& data, const string& type);
    int size() const;
    string get_value(int index) const;
    string get_type(int index) const;
};

// Trim spaces from both ends of a string (in-place)
void trim_string(string& s);

// Check if string is an integer
bool is_int_string(const string& s);

// Check if string is a double
bool is_double_string(const string& s);

#endif // DYNAMICLIST_H
