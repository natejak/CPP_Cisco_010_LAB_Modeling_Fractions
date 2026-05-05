#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

class Fraction{
public:
    Fraction(int numerator, int denominator);
    string toString();
    double toDouble();
private:
    int numerator;
    int denominator;
};

// implement Fraction methods

Fraction::Fraction(int numerator, int denominator){
    this->numerator = numerator;
    this->denominator = denominator;
}


string Fraction::toString(){
    int num = abs(numerator);
    int den = abs(denominator);

    int whole;
    int rest;

    if (num == den || (num % den == 0)){
        whole = num / den;
        if ((numerator < 0) != (denominator <0) ){
            return "-" + to_string(whole);
        }else{
            return  to_string(whole);
        }

    }else if(num > den){

        whole = num/den;
        rest = num % den;
        if ((numerator < 0) != (denominator <0) ){
            return "-" + to_string(whole) + " " + to_string(rest) + "/" + to_string(den);
        }else{
            return  to_string(whole) + " " + to_string(rest) + "/" + to_string(den);
        }
    }else{
        if ((numerator < 0) != (denominator <0) ){
            return "-" + to_string(num) + "/" + to_string(den);
        }else{
            return  to_string(num) + "/" + to_string(den);
        }
    }
}

double Fraction::toDouble(){
    return (double)numerator / (double)denominator;
}

int main(void) {
    int num, den;
    string input = "";
    getline(cin, input);

    char slash;
    stringstream ss(input);
    ss >> num >> slash >> den;

    // parse input and get numerator and denominator

    Fraction fraction(num, den);

    cout << fraction.toString() << " is " << fixed << setprecision(2) << fraction.toDouble() << " in decimal" << endl;
    return 0;
}