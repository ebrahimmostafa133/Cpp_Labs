#include "DynamicList.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    DynamicList lst;

    int n;
    cout << "Enter size of the list: ";
    cin >> n;

    // clear the newline left in the buffer
    cin.ignore(1000, '\n');

    for (int i = 0; i < n; ++i) {
        cout << "Enter value for index " << i << ": ";

        string input;
        getline(cin, input);

        trim_string(input);

        string type;
        if (is_int_string(input)) {
            type = "int";
        } else if (is_double_string(input)) {
            type = "double";
        } else {
            type = "string";
        }

        lst.append(input, type);
    }

    cout << "\nYou entered " << lst.size() << " elements:\n";

    for (int i = 0; i < lst.size(); ++i) {
        string value = lst.get_value(i);
        string type = lst.get_type(i);
        cout << "Index " << i << ": value = '" << value << "', type = " << type << endl;
    }

    cout << "Done.\n";

    return 0;
}
