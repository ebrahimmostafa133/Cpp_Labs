#include "DynamicList.h"

using namespace std;

// DynamicList methods

DynamicList::DynamicList() {
    head = 0;
    list_size = 0;
}

DynamicList::~DynamicList() {
    Node* current = head;
    while (current != 0) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

void DynamicList::append(const string& data, const string& type) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->type = type;
    newNode->next = 0;

    if (head == 0) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != 0) {
            current = current->next;
        }
        current->next = newNode;
    }
    list_size++;
}

int DynamicList::size() const {
    return list_size;
}

string DynamicList::get_value(int index) const {
    if (index < 0 || index >= list_size) {
        cout << "Error: index " << index << " out of bounds" << endl;
        return "";
    }

    Node* current = head;
    int i = 0;
    while (i < index) {
        current = current->next;
        i++;
    }
    return current->data;
}

string DynamicList::get_type(int index) const {
    if (index < 0 || index >= list_size) {
        cout << "Error: index " << index << " out of bounds" << endl;
        return "";
    }

    Node* current = head;
    int i = 0;
    while (i < index) {
        current = current->next;
        i++;
    }
    return current->type;
}

// Helper functions

void trim_string(string& s) {
    int start = 0;
    while (start < (int)s.size() &&
           (s[start] == ' ' || s[start] == '\t' || s[start] == '\n')) {
        start++;
    }

    int end = (int)s.size() - 1;
    while (end >= start &&
           (s[end] == ' ' || s[end] == '\t' || s[end] == '\n')) {
        end--;
    }

    string result;
    for (int i = start; i <= end; ++i) {
        result += s[i];
    }
    s = result;
}

bool is_int_string(const string& s) {
    if (s.empty()) return false;

    int i = 0;
    if (s[i] == '+' || s[i] == '-') {
        i++;
        if (i >= (int)s.size()) return false;
    }

    for (; i < (int)s.size(); ++i) {
        if (!isdigit((unsigned char)s[i])) {
            return false;
        }
    }
    return true;
}

bool is_double_string(const string& s) {
    if (s.empty()) return false;

    int i = 0;
    if (s[i] == '+' || s[i] == '-') {
        i++;
        if (i >= (int)s.size()) return false;
    }

    bool has_digit = false;
    bool has_dot = false;

    for (; i < (int)s.size(); ++i) {
        if (isdigit((unsigned char)s[i])) {
            has_digit = true;
        } else if (s[i] == '.') {
            if (has_dot) {
                return false;
            }
            has_dot = true;
        } else {
            return false;
        }
    }

    if (!has_digit) return false;
    if (!has_dot) return false;

    return true;
}
