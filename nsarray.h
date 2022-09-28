//
// Created by Matt Andrews on 9/21/2022.
// nsarray.h written for CS311
// This is an array management program to provide additional functionality
// Input and advice was given by Mr Chappell
//

#ifndef CS311_ASSIGNMENT_2_NSARRAY_H
#define CS311_ASSIGNMENT_2_NSARRAY_H

#include <cstddef> //for std::size_t
#include <typeinfo> // for typeid
#include <utility> //for swap

template <typename mrSmart>
class NSArray {
public:

    using size_type = std::size_t;
    using value_type = mrSmart; //

    //declarations of the objects which will be used
    value_type * myArray; //this will be the dynamically allocated array
    int mySize; //this will hold the size of the array
    value_type * myLast; //this will indicate the end of the array

    NSArray(): myArray(new value_type[8]){
        mySize = 8;
    } //default constructor

    NSArray(size_type x): myArray(new value_type[x]){
        mySize = x;
    } //1 parameter constructor

    NSArray(size_type x, value_type y): myArray(new value_type[x]){
        mySize = x;
        for (int count = 0; count < x; count++){
            myArray[count] = y;
        }
    } //2 paramater constructor


    //bracket operator, requires requested values to be between 0 and mySize-1, otherwise returns a reference to the first item in the array
    value_type & operator[](size_type index){
        if ((index >= 0) && (index <= mySize-1)){
        return myArray[index];}
        return myArray[0]; //what should this return if the requested item is out of bounds?
    }

    //bracket operator, requires requested values to be between 0 and mySize-1, otherwise returns a const reference to the first item in the array
    const value_type & operator[](size_type index) const {
        if ((index >= 0) && (index <= mySize-1)){
            return myArray[index];}
        return myArray[0]; //what should this return if the requested item is out of bounds?
        }

    int size() const { return mySize; } //needs to return the size of the held array

    value_type* begin(){ return &myArray[0]; } //return a pointer to the beginning of the array
    value_type* end(){ return &myArray[mySize]; } //return a pointer to the end of the array

    const value_type* begin() const { return &myArray[0]; } //return a const pointer to the beginning of the array
    const value_type* end() const { return (myArray+mySize); } //return a const pointer to the end of the array

    // Deconstructor
    ~NSArray()
    { delete [] myArray; } //clean up the dynamically allocated array

    //other essentials
    //copy constructor
    NSArray(const NSArray & other) noexcept : myArray(new value_type[other.mySize]){
        mySize = other.mySize;
        for (int count = 0; count < mySize; count++){
            myArray[count] = other.myArray[count];
        }
    }

    //copy assignment operator
    NSArray & operator=(const NSArray & rhs) noexcept{
        NSArray copy_of_rhs(rhs);
        mswap(copy_of_rhs);
        return *this;
    }

    //move constructor
    NSArray(NSArray && other) noexcept : myArray(other.myArray), mySize(other.mySize)
    {
        other.myArray = 0;
        other.mySize = 0;
    }
    //move assignment operator
    NSArray & operator=(NSArray && rhs) noexcept {
        mswap(rhs);
        return *this;
    }

private:
    void mswap(NSArray & other) noexcept //implement mswap for use in the copy assignment and move assignment operators
    {
        std::swap(mySize, other.mySize);
        std::swap(myArray, other.myArray);
    }

};


template <typename mrSmart>
bool operator<(NSArray<mrSmart> a, NSArray<mrSmart> b){
    if (a.size() == b.size()){ //check if the sizes are the same
        bool valCheck = true;
        for (int x=0; x<a.size(); x++){ //walk through each item in the arrays
            if (a[x] < b[x]){} //compare each item in the array
            else valCheck = false;
        }
        return valCheck;}
    return false;
} //write this one


template <typename mrSmart>
bool operator==(NSArray<mrSmart> a, NSArray<mrSmart> b){
    if (a.size() == b.size()){
        bool valCheck = true;
        for (int x=0; x<a.size(); x++){ //walk through each item in the arrays
            if (typeid(a[x]) == typeid(b[x])){} //compare each item in the array (making sure we are comparing the same types with typeid)
            else valCheck = false;
        }
        return valCheck;}
    return false;
} //and this one

template <typename mrSmart>
bool operator!=(NSArray<mrSmart> a, NSArray<mrSmart> b){ if (a==b){return false;} return true;}

template <typename mrSmart>
bool operator<=(NSArray<mrSmart> a, NSArray<mrSmart> b){if ((a==b)||(a<b)){return true;} return false;}

template <typename mrSmart>
bool operator>(NSArray<mrSmart> a, NSArray<mrSmart> b){if (!(a<=b)){return false;} return true;}

template <typename mrSmart>
bool operator>=(NSArray<mrSmart> a, NSArray<mrSmart> b){if (!(a<b)){return true;} return false;}


#endif //CS311_ASSIGNMENT_2_NSARRAY_H
