#include <iostream>
#include <string>
#include <sstream>

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


    if ((numerator < 0) != (denominator <0) ){
        return "-" + to_string(numerator) + "/" + to_string(denominator);
    }else{
        return  to_string(numerator) + "/" + to_string(denominator);
    }

}

double Fraction::toDouble(){
    return (double)numerator / denominator;
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

    cout << fraction.toString() << " is " << fraction.toDouble() << " in decimal" << endl;
    return 0;
}