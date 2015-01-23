//
//  linear.cpp
//  HW 3
//
//  Created by Li-Wei Tseng on 5/5/14.
//  Copyright (c) 2014 Li-Wei Tseng. All rights reserved.
//

#include <string>
#include <cassert>
#include <iostream>
using namespace std;



// Return true if any of the strings in the array is empty, false
// otherwise.

bool anyEmpty(const string a[], int n)
{
    //recursion case(s)
	//each solve a problem that is strictly “smaller” than the current problem
	//closer to a base case
    if(n <= 0)
        return false;
    
    if(a[0] == "") //base case, check if the first item in the array is an empty string
        return true;
    
    return anyEmpty(a + 1, n - 1);
}

// Return the number of empty strings in the array.
int countEmpties(const string a[], int n)
{
    //recursion case(s)
	//each solve a problem that is strictly “smaller” than the current problem
	//closer to a base case
    if(n <= 0)
        return 0;
    
    int count = 0;
    
    if(a[0] == "") //base case, check if the first item in the array is an empty string
        count++;
    
    return count + countEmpties(a+1, n-1);
}

// Return the subscript of the first empty string in the array.
// If no element is empty, return -1.
int firstEmpty(const string a[], int n)
{
    //recursion case(s)
	//each solve a problem that is strictly “smaller” than the current problem
	//closer to a base case
    if(n <= 0)
        return -1;
    
    if(a[0] == "") //base case, check if the first item in the array is an empty string
    {
        return 0;
    }
    
    int subsript = 1 + firstEmpty(a+1, n-1); //add 1 to the first empty string subscript of the array excluding the first term

    if(subsript == 0)
        return -1;
    else
        return subsript;
}

// Return the subscript of the least string in the array (i.e.,
// the smallest subscript m such that there is no k for which
// a[k] < a[m].)  If the array has no elements to examine, return -1.
int indexOfLeast(const string a[], int n)
{
    if(n <= 0)
        return -1;
    
    if(n == 1)
        return 0;
    
    int mid = n / 2; //divide the array into two half
	
    int subsript1 = indexOfLeast(a, mid); //find the index of least on the left
    int subscript2 = indexOfLeast(a + mid, n - mid) + mid;  //find the index of least on the right
    
    if(a[subsript1] <= a[subscript2]) //return the smallest one
        return subsript1;
    else
        return subscript2;
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// then the function should return true if a2 is
//    "kyle" "kenny" "butters"
// or
//    "kyle" "cartman" "cartman"
// and it should return false if a2 is
//    "kyle" "butters" "kenny"
// or
//    "stan" "kenny" "kenny"
bool includes(const string a1[], int n1, const string a2[], int n2)
{
    //recursion case(s)
	//each solve a problem that is strictly “smaller” than the current problem
	//closer to a base case
    if(n2 <= 0)
        return true;
    if(n1 < n2)
        return false;
    
    if(a1[0] == a2[0])//base case
    {
        return includes(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
    }
    else
        return includes(a1 + 1, n1 - 1, a2, n2);
}

/////////////////////test cases/////////////////////

//#define LINEAR
#ifdef LINEAR

void testAnyEmpty()
{
    const int SIZE = 3;
    
    string a[SIZE] = {"", "abc", "asd"};
    
    assert(!anyEmpty(a, 0));
    assert(anyEmpty(a, 1));
    assert(anyEmpty(a, 2));
    assert(anyEmpty(a, 3));
    
    string b[SIZE] = {"abc", "", "asd"};
    
    assert(!anyEmpty(b, 0));
    assert(!anyEmpty(b, 1));
    assert(anyEmpty(b, 2));
    assert(anyEmpty(b, 3));
    
    string c[SIZE] = {"abc", "asd", ""};
    
    assert(!anyEmpty(c, 0));
    assert(!anyEmpty(c, 1));
    assert(!anyEmpty(c, 2));
    assert(anyEmpty(c, 3));

    string d[SIZE] = {"", "asd", ""};
    
    assert(!anyEmpty(d, 0));
    assert(anyEmpty(d, 1));
    assert(anyEmpty(d, 2));
    assert(anyEmpty(d, 3));
    
    string e[SIZE] = {"abc", "as", "ae"};
    
    assert(!anyEmpty(e, 0));
    assert(!anyEmpty(e, 1));
    assert(!anyEmpty(e, 2));
    assert(!anyEmpty(e, 3));
}

void testCountEmpties()
{
    const int SIZE = 3;
    
    string a[SIZE] = {"", "abc", "asd"};
    
    assert(countEmpties(a, 0) == 0);
    assert(countEmpties(a, 1) == 1);
    assert(countEmpties(a, 2) == 1);
    assert(countEmpties(a, 3) == 1);
    
    string b[SIZE] = {"abc", "", "asd"};
    
    assert(countEmpties(b, 0) == 0);
    assert(countEmpties(b, 1) == 0);
    assert(countEmpties(b, 2) == 1);
    assert(countEmpties(b, 3) == 1);
    
    string c[SIZE] = {"abc", "asd", ""};
    
    assert(countEmpties(c, 0) == 0);
    assert(countEmpties(c, 1) == 0);
    assert(countEmpties(c, 2) == 0);
    assert(countEmpties(c, 3) == 1);
    
    string d[SIZE] = {"", "asd", ""};
    
    assert(countEmpties(d, 0) == 0);
    assert(countEmpties(d, 1) == 1);
    assert(countEmpties(d, 2) == 1);
    assert(countEmpties(d, 3) == 2);
    
    string e[SIZE] = {"abc", "as", "ae"};
    
    assert(countEmpties(e, 0) == 0);
    assert(countEmpties(e, 1) == 0);
    assert(countEmpties(e, 2) == 0);
    assert(countEmpties(e, 3) == 0);
}

void testFirstEmpty()
{
    const int SIZE = 3;
    
    string a[SIZE] = {"", "abc", "asd"};
    
    assert(firstEmpty(a, 0) == -1);
    assert(firstEmpty(a, 1) == 0);
    assert(firstEmpty(a, 2) == 0);
    assert(firstEmpty(a, 3) == 0);
    
    string b[SIZE] = {"abc", "", "asd"};
    
    assert(firstEmpty(b, 0) == -1);
    assert(firstEmpty(b, 1) == -1);
    assert(firstEmpty(b, 2) == 1);
    assert(firstEmpty(b, 3) == 1);
    
    string c[SIZE] = {"abc", "asd", ""};
    
    assert(firstEmpty(c, 0) == -1);
    assert(firstEmpty(c, 1) == -1);
    assert(firstEmpty(c, 2) == -1);
    assert(firstEmpty(c, 3) == 2);
    
    string d[SIZE] = {"", "asd", ""};
    
    assert(firstEmpty(d, 0) == -1);
    assert(firstEmpty(d, 1) == 0);
    assert(firstEmpty(d, 2) == 0);
    assert(firstEmpty(d, 3) == 0);
    
    string e[SIZE] = {"abc", "as", "ae"};
    
    assert(firstEmpty(e, 0) == -1);
    assert(firstEmpty(e, 1) == -1);
    assert(firstEmpty(e, 2) == -1);
    assert(firstEmpty(e, 3) == -1);
}

void testIndexOfLeast()
{
    const int SIZE = 3;
    
    string a[SIZE] = {"", "abc", "asd"};
    
    assert(indexOfLeast(a, 0) == -1);
    assert(indexOfLeast(a, 1) == 0);
    assert(indexOfLeast(a, 2) == 0);
    assert(indexOfLeast(a, 3) == 0);
    
    string b[SIZE] = {"abc", "", "asd"};
    
    assert(indexOfLeast(b, 0) == -1);
    assert(indexOfLeast(b, 1) == 0);
    assert(indexOfLeast(b, 2) == 1);
    assert(indexOfLeast(b, 3) == 1);
    
    string c[SIZE] = {"abc", "asd", ""};
    
    assert(indexOfLeast(c, 0) == -1);
    assert(indexOfLeast(c, 1) == 0);
    assert(indexOfLeast(c, 2) == 0);
    assert(indexOfLeast(c, 3) == 2);
    
    string d[SIZE] = {"", "asd", ""};
    
    assert(indexOfLeast(d, 0) == -1);
    assert(indexOfLeast(d, 1) == 0);
    assert(indexOfLeast(d, 2) == 0);
    assert(indexOfLeast(d, 3) == 0);
    
    string e[SIZE] = {"abc", "as", "ae"};
    
    assert(indexOfLeast(e, 0) == -1);
    assert(indexOfLeast(e, 1) == 0);
    assert(indexOfLeast(e, 2) == 0);
    assert(indexOfLeast(e, 3) == 0);
}

void testIncludes()
{
    const int SIZE = 7;
    const int SIZE1 = 3;
    const int SIZE2 = 0;
    
    string a1[SIZE] = {"stan", "kyle", "cartman", "kenny", "kyle", "cartman", "butters"};
    string a2[SIZE1] = {"kyle", "kenny", "butters"};
    string a3[SIZE1] = {"kyle", "cartman", "cartman"};
    string a4[SIZE1] = {"kyle", "butters", "kenny"};
    string a5[SIZE1] = {"stan", "kenny", "kenny"};
    string a6[SIZE1] = {""};
    
    assert(includes(a1, SIZE, a2, SIZE1));
    assert(includes(a1, SIZE, a3, SIZE1));
    assert(includes(a1, SIZE, a6, SIZE2));
    
    assert(!includes(a1, SIZE, a4, SIZE1));
    assert(!includes(a1, SIZE, a5, SIZE1));
}


int main()
{
    testAnyEmpty();
    testCountEmpties();
    testFirstEmpty();
    testIndexOfLeast();
    testIncludes();
    cout << "Pass all tests!" << endl;
}

#endif //LINEAR
