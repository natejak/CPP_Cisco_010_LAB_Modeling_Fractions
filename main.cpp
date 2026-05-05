/*
    Fraction Modelling - Parts 1, 2 and 3

    This program works with fractions written in the form:
        numerator / denominator

    The user can choose one of three modes:

    1 - Single fraction mode
        Reads one fraction and prints:
        - its text representation,
        - its decimal representation.

    2 - Operations mode
        Reads two fractions and performs:
        - addition,
        - subtraction,
        - multiplication,
        - division.

        The results of the operations are reduced to their lowest terms.

    3 - Comparison mode
        Reads two fractions, converts them to decimal values,
        compares them, and prints the comparison result.

    Note:
        The comparison mode uses decimal values because it is easier to understand.
        For very precise mathematical comparison, cross-multiplication would be safer.
*/

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

class Fraction {
public:
    Fraction(int numerator, int denominator);

    // Returns the fraction as a text representation
    string toString();

    // Returns the fraction as a decimal number
    double toDouble();

    // Basic fraction operations
    Fraction add(Fraction other);
    Fraction subtract(Fraction other);
    Fraction multiply(Fraction other);
    Fraction divide(Fraction other);

private:
    int numerator;
    int denominator;

    // Calculates the greatest common divisor using the Euclidean algorithm
    int gcd(int a, int b);
};

// Constructor: stores the numerator and denominator inside the object
Fraction::Fraction(int numerator, int denominator) {
    this->numerator = numerator;
    this->denominator = denominator;
}

// Returns the fraction as a string.
//
// This method handles:
// - proper fractions, for example: 3/4
// - mixed numbers, for example: 7/4 -> 1 3/4
// - negative signs, for example: 7/-4 -> -1 3/4
// - whole numbers, for example: 8/4 -> 2
string Fraction::toString() {
    // Use absolute values for calculations.
    // This makes it easier to build the text without worrying about signs.
    int num = abs(numerator);
    int den = abs(denominator);

    // The fraction is negative if exactly one value is negative.
    // Example:
    //  3 / -4 -> negative
    // -3 /  4 -> negative
    // -3 / -4 -> positive
    bool isNegative = (numerator < 0) != (denominator < 0);

    int whole;
    int rest;

    // Case 1:
    // The fraction is a whole number.
    // Example:
    // 8/4 -> 2
    // -8/4 -> -2
    if (num == den || (num % den == 0)) {
        whole = num / den;

        if (isNegative) {
            return "-" + to_string(whole);
        } else {
            return to_string(whole);
        }

        // Case 2:
        // The fraction is greater than 1 and should be displayed as a mixed number.
        // Example:
        // 7/4 -> 1 3/4
        // -7/4 -> -1 3/4
    } else if (num > den) {
        whole = num / den;
        rest = num % den;

        if (isNegative) {
            return "-" + to_string(whole) + " " + to_string(rest) + "/" + to_string(den);
        } else {
            return to_string(whole) + " " + to_string(rest) + "/" + to_string(den);
        }

        // Case 3:
        // The fraction is smaller than 1.
        // Example:
        // 3/4 -> 3/4
        // -3/4 -> -3/4
    } else {
        if (isNegative) {
            return "-" + to_string(num) + "/" + to_string(den);
        } else {
            return to_string(num) + "/" + to_string(den);
        }
    }
}

// Converts the fraction to a decimal number.
//
// The numerator is cast to double to avoid integer division.
// Without the cast, 1 / 2 would give 0 instead of 0.5.
double Fraction::toDouble() {
    return (double)numerator / (double)denominator;
}

// Adds another fraction to this fraction and returns the reduced result.
//
// Formula:
// a/b + c/d = (a*d + c*b) / (b*d)
Fraction Fraction::add(Fraction other) {
    int newNumerator;
    int newDenominator;

    // Calculate the numerator and denominator of the result
    newNumerator = numerator * other.denominator + other.numerator * denominator;
    newDenominator = denominator * other.denominator;

    // Reduce the result to its lowest terms
    int divisor = gcd(newNumerator, newDenominator);
    newNumerator = newNumerator / divisor;
    newDenominator = newDenominator / divisor;

    // Return the result as a new Fraction object
    return Fraction(newNumerator, newDenominator);
}

// Subtracts another fraction from this fraction and returns the reduced result.
//
// Formula:
// a/b - c/d = (a*d - c*b) / (b*d)
Fraction Fraction::subtract(Fraction other) {
    int newNumerator;
    int newDenominator;

    // Calculate the numerator and denominator of the result
    newNumerator = numerator * other.denominator - other.numerator * denominator;
    newDenominator = denominator * other.denominator;

    // Reduce the result to its lowest terms
    int divisor = gcd(newNumerator, newDenominator);
    newNumerator = newNumerator / divisor;
    newDenominator = newDenominator / divisor;

    // Return the result as a new Fraction object
    return Fraction(newNumerator, newDenominator);
}

// Multiplies this fraction by another fraction and returns the reduced result.
//
// Formula:
// a/b * c/d = (a*c) / (b*d)
Fraction Fraction::multiply(Fraction other) {
    int newNumerator;
    int newDenominator;

    // Calculate the numerator and denominator of the result
    newNumerator = numerator * other.numerator;
    newDenominator = denominator * other.denominator;

    // Reduce the result to its lowest terms
    int divisor = gcd(newNumerator, newDenominator);
    newNumerator = newNumerator / divisor;
    newDenominator = newDenominator / divisor;

    // Return the result as a new Fraction object
    return Fraction(newNumerator, newDenominator);
}

// Divides this fraction by another fraction and returns the reduced result.
//
// Formula:
// a/b / c/d = (a*d) / (b*c)
//
// Dividing by a fraction means multiplying by its reciprocal.
Fraction Fraction::divide(Fraction other) {
    int newNumerator;
    int newDenominator;

    // Calculate the numerator and denominator of the result
    newNumerator = numerator * other.denominator;
    newDenominator = denominator * other.numerator;

    // Reduce the result to its lowest terms
    int divisor = gcd(newNumerator, newDenominator);
    newNumerator = newNumerator / divisor;
    newDenominator = newDenominator / divisor;

    // Return the result as a new Fraction object
    return Fraction(newNumerator, newDenominator);
}

// Calculates the greatest common divisor using the Euclidean algorithm.
//
// Example:
// gcd(3, 12) = 3
// gcd(6, 10) = 2
//
// This is used to reduce fractions to their lowest terms.
int Fraction::gcd(int a, int b) {
    // Work with positive values only
    a = abs(a);
    b = abs(b);

    int rest;

    // Repeat until the second number becomes zero
    while (b != 0) {
        // Calculate the remainder
        rest = a % b;

        // Move the values one step forward in the algorithm
        a = b;
        b = rest;
    }

    // When b is zero, a contains the greatest common divisor
    return a;
}

int main(void) {
    int option;

    // Display the menu
    cout << "Choose mode:" << endl;
    cout << "1 - Single fraction decimal representation" << endl;
    cout << "2 - Fraction operations" << endl;
    cout << "3 - Fraction comparison" << endl;
    cout << "Option: ";

    // Read the selected option
    cin >> option;

    // Clear the Enter character left in the input buffer after cin
    cin.ignore();

    if (option == 1) {
        int num, den;
        char slash;
        string input = "";

        // Read one fraction as a full line
        // Example input:
        // 3 / 4
        getline(cin, input);

        // Parse the input line into numerator, slash character, and denominator
        stringstream ss(input);
        ss >> num >> slash >> den;

        // Create one Fraction object
        Fraction fraction(num, den);

        // Print the text and decimal representation of the fraction
        cout << fraction.toString()
             << " is "
             << fraction.toDouble()
             << " in decimal"
             << endl;

    } else if (option == 2) {
        int num1, den1;
        int num2, den2;

        string input1 = "";
        string input2 = "";

        // Read two fractions as two separate lines
        // Example input:
        // 3 / 4
        // 1 / 3
        getline(cin, input1);
        getline(cin, input2);

        char slash1;
        char slash2;

        // Parse the first fraction
        stringstream ss1(input1);
        ss1 >> num1 >> slash1 >> den1;

        // Parse the second fraction
        stringstream ss2(input2);
        ss2 >> num2 >> slash2 >> den2;

        // Create two Fraction objects
        Fraction fraction1(num1, den1);
        Fraction fraction2(num2, den2);

        // Perform all four basic operations
        Fraction sum = fraction1.add(fraction2);
        Fraction difference = fraction1.subtract(fraction2);
        Fraction product = fraction1.multiply(fraction2);
        Fraction quotient = fraction1.divide(fraction2);

        // Print the results of all operations
        cout << fraction1.toString() << " + " << fraction2.toString() << " = " << sum.toString() << endl;
        cout << fraction1.toString() << " - " << fraction2.toString() << " = " << difference.toString() << endl;
        cout << fraction1.toString() << " * " << fraction2.toString() << " = " << product.toString() << endl;
        cout << fraction1.toString() << " / " << fraction2.toString() << " = " << quotient.toString() << endl;

    } else if (option == 3) {
        int num1, den1;
        int num2, den2;

        string input1 = "";
        string input2 = "";

        // Read two fractions as two separate lines for comparison
        // Example input:
        // 2 / 4
        // 1 / 2
        getline(cin, input1);
        getline(cin, input2);

        char slash1;
        char slash2;

        // Parse the first fraction
        stringstream ss1(input1);
        ss1 >> num1 >> slash1 >> den1;

        // Parse the second fraction
        stringstream ss2(input2);
        ss2 >> num2 >> slash2 >> den2;

        // Create two Fraction objects
        Fraction fraction1(num1, den1);
        Fraction fraction2(num2, den2);

        // Convert both fractions to decimal values
        // This makes the comparison easy to understand
        double decimal1 = fraction1.toDouble();
        double decimal2 = fraction2.toDouble();

        string sign;

        // Choose the correct comparison sign
        if (decimal1 == decimal2) {
            sign = " = ";
        } else if (decimal1 > decimal2) {
            sign = " > ";
        } else {
            sign = " < ";
        }

        // Print the comparison result
        cout << fraction1.toString() << sign << fraction2.toString() << endl;

    } else {
        // Handle invalid menu options
        cout << "Unknown option" << endl;
    }

    return 0;
}