#include "complexClass.h"
#include <iostream>
#include <stdexcept>
#include <sstream>

using namespace std;

void print_result(const string& operation, const Complex& result) {
    cout << "  " << operation << " = " << result << endl;
}

int main() {
    cout << "--- Complex Class Test ---" << endl;

    cout << "\n[1] Constructor Test:" << endl;
    Complex c1;
    Complex c2(3.0, 4.0);
    Complex c3(5.0);
    Complex c4 = c2;

    cout << "  c1 (Default): " << c1 << endl;
    cout << "  c2 (3 + 4i): " << c2 << endl;
    cout << "  c3 (5 + 0i): " << c3 << endl;
    cout << "  c4 (Copy of c2): " << c4 << endl;

    cout << "\n[2] Accessors and Mutators Test:" << endl;
    cout << "  Real part of c2: " << c2.getReal() << endl;
    cout << "  Imaginary part of c2: " << c2.getImaginary() << endl;
    c1.setReal(1.0);
    c1.setImaginary(-2.0);
    cout << "  c1 after modification (1 - 2i): " << c1 << endl;

    cout << "\n[3] Assignment Operator Test:" << endl;
    Complex c5;
    c5 = c1;
    cout << "  c5 = c1: " << c5 << endl;

    cout << "\n[4] Binary Arithmetic Operators Test (c2 = 3+4i, c1 = 1-2i):" << endl;
    Complex sum = c2 + c1;
    print_result("c2 + c1", sum);

    Complex diff = c2 - c1;
    print_result("c2 - c1", diff);

    Complex prod = c2 * c1;
    print_result("c2 * c1", prod);

    try {
        Complex quot = c2 / c1;
        print_result("c2 / c1", quot);
    } catch (const runtime_error& e) {
        cerr << "  Division Error: " << e.what() << endl;
    }

    cout << "\n[5] Mixed Arithmetic Operations Test (c2 = 3+4i):" << endl;
    Complex mixed_sum_left = 10.0 + c2;
    print_result("10.0 + c2", mixed_sum_left);

    Complex mixed_sum_right = c2 + 10.0;
    print_result("c2 + 10.0", mixed_sum_right);

    Complex c_test(10.0, 15.5);
    Complex custom_test = 10 + c_test;
    print_result("10 + c(10, 15.5)", custom_test);

    cout << "\n[6] Compound Assignment Operators Test (c3 = 5+0i, c1 = 1-2i):" << endl;
    Complex c6 = c3;
    c6 += c1;
    print_result("c6 (c3 += c1)", c6);

    c6 = c3;
    c6 -= c1;
    print_result("c6 (c3 -= c1)", c6);

    c6 = c3;
    c6 *= c1;
    print_result("c6 (c3 *= c1)", c6);

    c6 = c3;
    c6 /= c1;
    print_result("c6 (c3 /= c1)", c6);

    cout << "\n[7] Unary Negation Operator Test (c2 = 3+4i):" << endl;
    Complex neg_c2 = -c2;
    print_result("-c2", neg_c2);

    cout << "\n[8] Comparison Operators Test (c2 = 3+4i, c4 = 3+4i, c1 = 1-2i):" << endl;
    cout << "  c2 == c4: " << (c2 == c4 ? "True" : "False") << endl;
    cout << "  c2 != c1: " << (c2 != c1 ? "True" : "False") << endl;
    cout << "  c2 == c1: " << (c2 == c1 ? "True" : "False") << endl;

    cout << "\n[9] Property Functions Test (c2 = 3+4i):" << endl;
    cout << "  Magnitude of c2: " << c2.magnitude() << " (Expected 5)" << endl;
    cout << "  Magnitude Squared of c2: " << c2.magnitudeSquared() << " (Expected 25)" << endl;
    Complex conj_c2 = c2.conjugate();
    print_result("Conjugate of c2", conj_c2);
    cout << "  Phase of c2 in radians: " << c2.phase() << endl;

    cout << "\n[10] Input Operator (>>) Test:" << endl;
    Complex c_input;
    cout << "  Enter a complex number (Real then Imaginary, e.g., 10.5 -3.2): ";
    stringstream ss("10.5 -3.2");
    ss >> c_input;
    cout << "  The entered complex number (simulated): " << c_input << endl;

    cout << "\n[11] Division by Zero Test:" << endl;
    Complex c_zero(0.0, 0.0);
    try {
        Complex result = c2 / c_zero;
        cout << "  Result (should not appear): " << result << endl;
    } catch (const runtime_error& e) {
        cerr << "  Exception caught successfully: " << e.what() << endl;
    }

    return 0;
}