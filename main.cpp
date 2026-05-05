/*
    Fraction Modelling - Part 2

    This program reads two fractions in the form:
        numerator / denominator
        numerator / denominator

    It creates two Fraction objects and performs four basic operations:
    - addition,
    - subtraction,
    - multiplication,
    - division.

    The results of the operations are reduced to their lowest terms.

    Examples:
        3 / 4
        1 / 3

        3/4 + 1/3 = 1 1/12
        3/4 - 1/3 = 5/12
        3/4 * 1/3 = 1/4
        3/4 / 1/3 = 2 1/4
*/

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

class Fraction {
public:
    Fraction(int numerator, int denominator);
    string toString();

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

// Constructor: saves the numerator and denominator in the object
Fraction::Fraction(int numerator, int denominator) {
    this->numerator = numerator;
    this->denominator = denominator;
}

// Returns the fraction as a string.
// It handles:
// - proper fractions, for example 3/4
// - mixed numbers, for example 7/4 -> 1 3/4
// - negative signs, for example 7/-4 -> -1 3/4
// - whole numbers, for example 8/4 -> 2
string Fraction::toString() {
    // Use positive values for calculations and text formatting
    int num = abs(numerator);
    int den = abs(denominator);

    // The result is negative if exactly one value is negative
    bool isNegative = (numerator < 0) != (denominator < 0);

    int whole;
    int rest;

    // Case 1: the fraction is a whole number, for example 8/4 -> 2
    if (num == den || (num % den == 0)) {
        whole = num / den;

        if (isNegative) {
            return "-" + to_string(whole);
        } else {
            return to_string(whole);
        }

        // Case 2: the fraction is greater than 1, for example 7/4 -> 1 3/4
    } else if (num > den) {
        whole = num / den;
        rest = num % den;

        if (isNegative) {
            return "-" + to_string(whole) + " " + to_string(rest) + "/" + to_string(den);
        } else {
            return to_string(whole) + " " + to_string(rest) + "/" + to_string(den);
        }

        // Case 3: the fraction is smaller than 1, for example 3/4
    } else {
        if (isNegative) {
            return "-" + to_string(num) + "/" + to_string(den);
        } else {
            return to_string(num) + "/" + to_string(den);
        }
    }
}

// Adds another fraction to this fraction and returns the reduced result
Fraction Fraction::add(Fraction other) {
    int newNumerator;
    int newDenominator;

    // a/b + c/d = (a*d + c*b) / (b*d)
    newNumerator = numerator * other.denominator + other.numerator * denominator;
    newDenominator = denominator * other.denominator;

    // Reduce the result to its lowest terms
    int divisor = gcd(newNumerator, newDenominator);
    newNumerator = newNumerator / divisor;
    newDenominator = newDenominator / divisor;

    return Fraction(newNumerator, newDenominator);
}

// Subtracts another fraction from this fraction and returns the reduced result
Fraction Fraction::subtract(Fraction other) {
    int newNumerator;
    int newDenominator;

    // a/b - c/d = (a*d - c*b) / (b*d)
    newNumerator = numerator * other.denominator - other.numerator * denominator;
    newDenominator = denominator * other.denominator;

    // Reduce the result to its lowest terms
    int divisor = gcd(newNumerator, newDenominator);
    newNumerator = newNumerator / divisor;
    newDenominator = newDenominator / divisor;

    return Fraction(newNumerator, newDenominator);
}

// Multiplies this fraction by another fraction and returns the reduced result
Fraction Fraction::multiply(Fraction other) {
    int newNumerator;
    int newDenominator;

    // a/b * c/d = (a*c) / (b*d)
    newNumerator = numerator * other.numerator;
    newDenominator = denominator * other.denominator;

    // Reduce the result to its lowest terms
    int divisor = gcd(newNumerator, newDenominator);
    newNumerator = newNumerator / divisor;
    newDenominator = newDenominator / divisor;

    return Fraction(newNumerator, newDenominator);
}

// Divides this fraction by another fraction and returns the reduced result
Fraction Fraction::divide(Fraction other) {
    int newNumerator;
    int newDenominator;

    // a/b / c/d = (a*d) / (b*c)
    newNumerator = numerator * other.denominator;
    newDenominator = denominator * other.numerator;

    // Reduce the result to its lowest terms
    int divisor = gcd(newNumerator, newDenominator);
    newNumerator = newNumerator / divisor;
    newDenominator = newDenominator / divisor;

    return Fraction(newNumerator, newDenominator);
}

// Calculates the greatest common divisor using the Euclidean algorithm
int Fraction::gcd(int a, int b) {
    a = abs(a);
    b = abs(b);

    int rest;

    while (b != 0) {
        // Calculate the remainder
        rest = a % b;

        // Move the values one step forward in the algorithm
        a = b;
        b = rest;
    }

    return a;
}

int main(void) {
    int num1, den1;
    int num2, den2;

    string input1 = "";
    string input2 = "";

    // Read two input lines, for example:
    // 3 / 4
    // 1 / 3
    getline(cin, input1);
    getline(cin, input2);

    char slash1;
    char slash2;

    // Parse the first input line into numerator, slash character, and denominator
    stringstream ss1(input1);
    ss1 >> num1 >> slash1 >> den1;

    // Parse the second input line into numerator, slash character, and denominator
    stringstream ss2(input2);
    ss2 >> num2 >> slash2 >> den2;

    // Create Fraction objects using the parsed values
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

    return 0;
}