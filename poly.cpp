#include "poly.h"
#include <iostream>
using namespace std; 

// ---------------------------------------------------------------------------
// Constructor 
// Default constructor for class Poly
Poly::Poly() 
{
    this->head = nullptr; 
}

// ---------------------------------------------------------------------------
// Constructor 
// Constructor for class Poly that takes in a single parameter
Poly::Poly(int number) 
{
    head = new Node(); 
    head->data.first = number;
    head->data.second = 0; 
    head->next = nullptr; 
}

// ---------------------------------------------------------------------------
// Constructor 
// Constructor for class Poly that takes in two parameters
Poly::Poly(int number, int position) 
{
    head = new Node(); 
    head->data.first = number;
    head->data.second = position; 
    head->next = nullptr; 
}

// ---------------------------------------------------------------------------
// Copy Constructor 
// Copy Constructor for class Poly
Poly::Poly(const Poly& poly) 
{
    this->head = nullptr; 
    *this = poly;
}

// ---------------------------------------------------------------------------
// Destructor 
// Destructor for class Poly
Poly::~Poly() 
{
    this->deleteArr();
}

//----------------------------------------------------------------------------
// Getter 
// getCoeff: fetches the coefficient value from the array
int Poly::getCoeff(int position) const
{
    Node* temp = head; 
	while(temp != nullptr)
	{
		Node* holder = temp;
        if (temp->data.second == position) 
        {
            return temp->data.first; 
        }
		temp = temp->next; 
	}
    return 0; 
}

//----------------------------------------------------------------------------
// Setter
// setCoeff: sets a coeffecient when given the posisiton and the value
bool Poly::setCoeff(int number, int position)
{
    Node* temp = new Node(); 
    pair<int, int> num(number, position); 
    temp->data = num; 
    temp->next = nullptr; 
    Node* current = this->head;
    if (head == nullptr) 
    {
        this->head = temp; 
        return true; 
    } 
    else if (head->data.second < position)
    {
        temp->next = this->head;
        temp = head; 
        return true; 
    }
    else 
    {
        while(current->next != nullptr)
	    {
            if (current->data.second < position && current->next->data.second > position)
            {
                temp->next = current->next;
                current = temp; 
                return true; 
            }
            current = current->next;
	    } 
    }
    temp->next = current->next;
	current->next = temp;
    return true; 
}

//----------------------------------------------------------------------------
// operator=  
// overloaded =: sets the left side object to the same value as the right side
// object
Poly& Poly::operator=(const Poly& poly) 
{
    if (*this == poly)
    {
        return *this; 
    }
    if (poly.head == nullptr)
    {
        this->deleteArr(); 
        return *this;   
    }
    Node* rhs = poly.head;
    Node* lhs = poly.head->next; 
    this->deleteArr(); 
    this->head = rhs; 
	while(lhs != nullptr)
	{
		rhs->next = new Node();
		rhs->next->data = lhs->data; 
        rhs->next->next = lhs->next;
		lhs = lhs->next;
		rhs = rhs->next;
	} 
    return *this;
}

//----------------------------------------------------------------------------
// operator+  
// overloaded +: adds two Poly objects together
Poly Poly::operator+(const Poly& poly) const
{
    Poly sum; 
    Node *rhs = poly.head; 
	Node *lhs = this->head; 
    if (poly.head == nullptr) 
    {
        return *this; 
    }
    if (head == nullptr) 
    {
        return poly;
    }
    while (rhs != nullptr && lhs != nullptr)
    {
        if (rhs->data.second < lhs->data.second)
        {
            sum.setCoeff(lhs->data.first, lhs->data.second);
            lhs = lhs->next;            
        }
        else if (rhs->data.second > lhs->data.second)
        {
            sum.setCoeff(rhs->data.first, rhs->data.second);
            rhs = rhs->next;
        }
        else
        {
            int x = rhs->data.first + lhs->data.first;
            if (x >= TEN)
            {
                sum.setCoeff( (x/TEN), rhs->data.second + 1);
                lhs = lhs->next;
                rhs = rhs->next;                
            }
            else 
            {
                sum.setCoeff(x, rhs->data.second); 
                lhs = lhs->next;
                rhs = rhs->next; 
            }
        }
    } 
    while (lhs != nullptr) 
    {
        sum.setCoeff(lhs->data.first, lhs->data.second);
        lhs = lhs->next;
    }
    while (rhs != nullptr) {
        sum.setCoeff(rhs->data.first, rhs->data.second);
        rhs = rhs->next;
    }
    return sum;
}

//----------------------------------------------------------------------------
// operator-  
// overloaded -: subtracts two Poly objects 
Poly Poly::operator-(const Poly& poly) const
{
    Poly difference; 
    Node *rhs = poly.head; 
	Node *lhs = this->head; 
    if (poly.head == nullptr) 
    {
        return *this; 
    }
    if (head == nullptr) 
    {
        while (rhs != nullptr)
        {
            difference.setCoeff(-1 * rhs->data.first, rhs->data.second);
            rhs = rhs->next; 
        }
        return difference;
    }
    while (rhs != nullptr && lhs != nullptr)
    {
        if (rhs->data.second < lhs->data.second)
        {
            difference.setCoeff(lhs->data.first, lhs->data.second);
            lhs = lhs->next;            
        }
        else if (rhs->data.second > lhs->data.second)
        {
            difference.setCoeff(rhs->data.first, rhs->data.second);
            rhs = rhs->next;
        }
        else
        {
            int x = lhs->data.first - rhs->data.first;
            difference.setCoeff(x, rhs->data.second); 
            lhs = lhs->next;
            rhs = rhs->next; 
        }
    } 
    while (lhs != nullptr) 
    {
        difference.setCoeff(lhs->data.first, lhs->data.second);
        lhs = lhs->next;
    }
    while (rhs != nullptr) {
        difference.setCoeff(rhs->data.first, rhs->data.second);
        rhs = rhs->next;
    }
    return difference;
} 

//----------------------------------------------------------------------------
// operator*  
// overloaded *: multiplies two Poly objects together
Poly Poly::operator*(const Poly& poly)  const
{
    Poly product;  
    Node *rhs = poly.head; 
	Node *lhs = this->head; 
    if (poly.head == nullptr) 
    {
        return *this; 
    }
    if (head == nullptr) 
    {
        return poly;
    }
    while (rhs != nullptr)
    {
        while (lhs != nullptr)
        {
            int x = lhs->data.first * rhs->data.first;
            int y = lhs->data.second + rhs->data.second;
            if (x >= TEN)
            {
                product.setCoeff(x/TEN, y + 1);
                int x2 = x - (x/TEN * 10); 
                product.setCoeff(x2, y);
            }
            else
            {
              product.setCoeff(x, y);  
            }
            lhs = lhs->next; 
        }
        rhs = rhs->next;
    } 
    return product;
} 

//----------------------------------------------------------------------------
// operator+=  
// overloaded +=: adds the left and right Poly objects together and sets the 
// left object to the sum
Poly& Poly::operator+=(const Poly& poly) 
{
    *this = poly + *this;
    return *this; 
}

//----------------------------------------------------------------------------
// operator-=  
// overloaded -=: subtracts the left and right Poly objects together and sets the
// left object to the difference
Poly& Poly::operator-=(const Poly& poly) 
{
    *this = poly - *this;
    return *this; 
}

//----------------------------------------------------------------------------
// operator*=  
// overloaded *=: multiplies the left and right Poly objects together and sets the
// left object to the product
Poly& Poly::operator*=(const Poly& poly) 
{
    *this = poly * *this;
    return *this; 
} 

//----------------------------------------------------------------------------
// operator==  
// overloaded ==: checks if two Poly objects are the same
bool Poly::operator==(const Poly& poly) const 
{
    bool ans = false; 
    Node *rhs = poly.head; 
	Node *lhs = this->head; 
    if (rhs == nullptr && lhs == nullptr) 
    {
        return true; 
    } 
    if ((rhs != nullptr && lhs == nullptr) || (rhs == nullptr && lhs != nullptr))
    {
        return false;
    }
    while (rhs != nullptr && lhs != nullptr) 
    {
        if ((rhs->data.second != lhs->data.second) && (rhs->data.first != lhs->data.first))
        {
            return false;  
        }
        rhs = rhs->next;
        lhs = lhs->next;
    }
    if ((rhs != nullptr && lhs == nullptr) || (rhs == nullptr && lhs != nullptr))
    {
        return false;
    }
    return true;
} 

//----------------------------------------------------------------------------
// operator!= 
// overloaded !=: checks if two Poly objects are not the same
bool Poly::operator!=(const Poly& poly) const 
{
    return !(*this == poly);
} 

//----------------------------------------------------------------------------
// operator<< 
// overloaded <<: prints out the object with the right formatting
ostream& operator<<(ostream &output, const Poly &poly) 
{
    Node *temp = poly.head; 
    while (temp != nullptr)
    {
        int maxPosition = temp->data.second; 
        int maxData = temp->data.first; 
        Node *compare = temp->next;
        while (compare != nullptr) 
        {
            if (compare->data.second > maxPosition)
            {
                maxPosition = compare->data.second; 
                maxData = compare->data.first; 
            }
            compare = compare->next; 
        }
        if (maxPosition == 0) 
        {
            if (maxData < 0)
            {
                output << " " << maxData; 
            }
            else
            {
                output << " +" << maxData;
            }
        }
        else if (maxPosition == 1) 
        {
            if (maxData < 0)
            {
                output << " " << maxData << "x"; 
            } 
            else 
            {
                output << " +" << maxData << "x"; 
            }
        }
        else 
        {
            if (maxData < 0)
            {
                output << " " << maxData << "x^" << maxPosition; 
            }
            else
            {
                output << " +" << maxData << "x^" << maxPosition; 
            }
            
        }
        temp = temp->next; 
    } 
    return output;
}

//----------------------------------------------------------------------------
// operator>>
// overloaded >>: reads in input from the user to create the object accordingly
istream& operator>>(istream &input, Poly &poly) {
    int exp, coeff;
    while (exp != -1 && coeff != -1) 
    {
        input >> coeff >> exp;
        if (poly.head == nullptr && (exp != -1 && coeff != -1)) 
        {
            poly.head = new Node();
            poly.head->data.first = coeff;
            poly.head->data.second = exp;
            poly.head->next = nullptr; 
        }
        else if (exp != -1 && coeff != -1)
        {
            poly.setCoeff(coeff, exp); 
        }
    }
    return input;                        
} 

//----------------------------------------------------------------------------
// deleteArr() 
// deleteArr(): deletes an array
void Poly::deleteArr()
{
	Node* temp = this->head; 
    Node* next = new Node(); 
	while(temp != nullptr)
	{
        next = temp->next; 
		delete temp; 
        temp = next; 
	}
	this->head = nullptr; 
}
