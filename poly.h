#ifndef POLY_H
#define POLY_H

#include <fstream> 
#include <utility>  // For pairs 
#include <iostream>
using namespace std;

//---------------------------------------------------------------------------
// Poly class: Creates the polynomial coefficients and stores the values within
//  an array, as well as:
//   -- multiplies, adds, and subtracts polynomial coefficients
//   -- adds in new polynomial coefficient values
//   -- returns coefficient at certain exponent
//   -- checks if two polynomial  are equal or not
//   -- sets one polynomial equal to another polynomial 
//
// Implementation and assumptions:
//   -- implemented using a private array
//   -- size defaults to a size of 0 if size is not specified
//   -- array elements are initialized to zero
//   -- user must enter valid integers when using >>
//   -- in <<, polynomial coefficients printed in specific layout
//---------------------------------------------------------------------------
struct Node 
{
	pair<int, int> data;
	Node* next;
};

const int TEN = 10;                     // Global variable for the value of 10

class Poly 
{
    friend ostream& operator<<(ostream &, const Poly &);
    friend istream& operator>>(istream &, Poly &);
public:
    Poly();                             // default constructor
    Poly(int number);                   // constructor, takes in coefficient
    Poly(int number, int position);     // constructor, takes coefficient & max power
    Poly(const Poly &);                 // copy constructor
    ~Poly();                            // destructor

    int getCoeff(int position) const;       // return coefficient at a certain position
    bool setCoeff(int number, int position); // sets a coefficient to a certain position to a particular number

    Poly& operator=(const Poly& poly);              // assign Poly objects
    Poly operator+(const Poly& poly) const;         // add 2 Polys
    Poly operator-(const Poly& poly) const;         // subtract 2 Polys
    Poly  operator*(const Poly& poly) const;        // multiply 2 Polys    
    Poly& operator+=(const Poly& poly);             // current object += parameter
    Poly& operator-=(const Poly& poly);             // current object -= parameter
    Poly& operator*=(const Poly& poly);             // current object *= parameter
    bool operator==(const Poly& poly) const;        // equality, 2 Polys are identical
    bool operator!=(const Poly& poly) const;        // not equal, 2 Polys different

private:
    void deleteArr();                               // helper for deleting an array 
    int number;                                     // coefficient value
    int position;                                   // polynomial value
    Node* head;                                     // root for a linked list
};
#endif