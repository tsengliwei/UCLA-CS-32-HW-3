//
//  tree.cpp
//  HW 3
//
//  Created by Li-Wei Tseng on 5/6/14.
//  Copyright (c) 2014 Li-Wei Tseng. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

// Return the number of ways that all n2 elements of a2 appear
// in the n1 element array a1 in the same order (though not
// necessarily consecutively).  The empty sequence appears in a
// sequence of length n1 in 1 way, even if n1 is 0.
// For example, if a1 is the 7 element array
//    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// then for this value of a2            the function must return
//    "stan" "kenny" "cartman"                      1
//    "stan" "cartman" "butters"                    2
//    "kenny" "stan" "cartman"                      0
//    "kyle" "cartman" "butters"                    3
int countIncludes(const string a1[], int n1, const string a2[], int n2)
{
    //recursion case(s)
	//each solve a problem that is strictly “smaller” than the current problem
	//closer to a base case
    if(n2 <= 0) //If any of the parameters n, n1, or n2 is negative, act as if it were zero.
        return 1;
    if(n1 < n2)
        return 0;
    
    int count = countIncludes(a1 + 1, n1 - 1, a2, n2);//count how many includes are in the rest of the array
    
    if(a1[0] == a2[0])//base case
    {
        //count how many possible orders for the first element in a1
        return count + countIncludes(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
    }
    else
        return count;
}

// Exchange two strings
void exchange(string& x, string& y)
{
    string t = x;
    x = y;
    y = t;
}

// Rearrange the elements of the array so that all the elements
// whose value is < barrier come before all the other elements,
// and all the elements whose value is > barrier come after all
// the other elements.  Upon return, firstNotLess is set to the index
// of the first element in the rearranged array that is >= barrier,
// or n if there is no such element, and firstGreater is set to
// the index of the first element that is > barrier, or n if
// there is no such element.
// In other words, upon return from the function, the array is a
// permutation of its original value such that
//   * for 0 <= i < firstNotLess, a[i] < barrier
//   * for firstNotLess <= i < firstGreater, a[i] == barrier
//   * for firstGreater <= i < n, a[i] > barrier
// All the elements < barrier end up in no particular order.
// All the elements > barrier end up in no particular order.
void takeSides(string a[], int n, string barrier,
               int& firstNotLess, int& firstGreater)
{
    if (n < 0)
        n = 0;
    
    // It will always be the case that just before evaluating the loop
    // condition:
    //  firstNotLess <= firstUnknown and firstUnknown <= firstGreater
    //  Every element earlier than position firstNotLess is < barrier
    //  Every element from position firstNotLess to firstUnknown-1 is
    //    == barrier
    //  Every element from firstUnknown to firstGreater-1 is not
    //     known yet
    //  Every element at position firstGreater or later is > barrier
    
    firstNotLess = 0;
    firstGreater = n;
    int firstUnknown = 0;
    while (firstUnknown < firstGreater)
    {
        if (a[firstUnknown] > barrier)
        {
            firstGreater--;
            exchange(a[firstUnknown], a[firstGreater]);
        }
        else
        {
            if (a[firstUnknown] < barrier)
            {
                exchange(a[firstNotLess], a[firstUnknown]);
                firstNotLess++;
            }
            firstUnknown++;
        }
    }
}

// Rearrange the elements of the array so that
// a[0] <= a[1] <= a[2] <= ... <= a[n-2] <= a[n-1]
// If n <= 1, do nothing.
void order(string a[], int n)
{
    if(n <= 1)
        return;
    
    int mid = n / 2, firstNotLess, firstGreater; //divide the array into two half
	
    takeSides(a, n, a[mid], firstNotLess, firstGreater); //choose the middle element as the barrier 
    
    if(firstNotLess != n)
        order(a, firstNotLess); //rearrange the elements on the left half, if there are elements on the left
    if(firstGreater != n)
        order(a + firstGreater, n - firstGreater);  //rearrange the elements on the right half, if there are elements on the right
    
}


//////////////////////////test cases/////////////////////


//#define __HW_3__tree__
#ifdef __HW_3__tree__

void testCountIncludes()
{
    const int SIZE = 7;
    const int SIZE1 = 3;
    const int SIZE2 = 1;
    const int SIZE3 = 0;
    
    string a1[SIZE] = {"stan", "kyle", "cartman", "kenny", "kyle", "cartman", "butters"};
    string a2[SIZE1] = {"stan", "kenny", "cartman"};
    string a3[SIZE1] = {"stan", "cartman", "butters"};
    string a4[SIZE1] = {"kenny", "stan", "cartman"};
    string a5[SIZE1] = {"kyle", "cartman", "butters"};
    string a6[SIZE2] = {""};
    
    assert(countIncludes(a1, SIZE, a2, SIZE1) == 1);
    assert(countIncludes(a1, SIZE, a3, SIZE1) == 2);
    assert(countIncludes(a1, SIZE3, a6, SIZE2) == 0);
    
    assert(countIncludes(a1, SIZE, a4, SIZE1) == 0);
    assert(countIncludes(a1, SIZE, a5, SIZE1) == 3);
}

void testOrder()
{
    const int SIZE = 4;
    const int SIZE1 = 3;
    const int SIZE2 = 1;
    
    //single element cases
    string aaa[SIZE2] = {"a"};
    
    order(aaa, SIZE2);
    assert(aaa[0] == "a");

    //even elements cases
    string aa1[SIZE] = {"a", "b", "c", "d"};
    string aa2[SIZE] = {"a", "b", "d", "c"};
    string aa3[SIZE] = {"a", "c", "b", "d"};
    string aa4[SIZE] = {"a", "c", "d", "b"};
    string aa5[SIZE] = {"a", "d", "b", "c"};
    string aa6[SIZE] = {"a", "d", "c", "b"};
    
    string aa7[SIZE] = {"b", "a", "c", "d"};
    string aa8[SIZE] = {"b", "a", "d", "c"};
    string aa9[SIZE] = {"b", "c", "a", "d"};
    string aa10[SIZE] = {"b", "c", "d", "a"};
    string aa11[SIZE] = {"b", "d", "a", "c"};
    string aa12[SIZE] = {"b", "d", "c", "a"};
    
    string aa13[SIZE] = {"c", "a", "b", "d"};
    string aa14[SIZE] = {"c", "a", "d", "b"};
    string aa15[SIZE] = {"c", "b", "a", "d"};
    string aa16[SIZE] = {"c", "b", "d", "a"};
    string aa17[SIZE] = {"c", "d", "a", "b"};
    string aa18[SIZE] = {"c", "d", "b", "a"};
    
    string aa19[SIZE] = {"d", "a", "c", "b"};
    string aa20[SIZE] = {"d", "a", "b", "c"};
    string aa21[SIZE] = {"d", "b", "a", "c"};
    string aa22[SIZE] = {"d", "b", "c", "a"};
    string aa23[SIZE] = {"d", "c", "a", "b"};
    string aa24[SIZE] = {"d", "c", "b", "a"};
    
    //repeated cases
    string aa25[SIZE] = {"d", "d", "b", "a"};
    
    order(aa25, SIZE);
    assert(aa25[0] == "a" && aa25[1] == "b" && aa25[2] == "d" && aa25[3] == "d");
    
    //odd elements cases
    string a2[SIZE1] = {"a", "b", "c"};
    string a3[SIZE1] = {"a", "c", "b"};
    string a4[SIZE1] = {"c", "a", "b"};
    string a5[SIZE1] = {"c", "b", "a"};
    string a6[SIZE1] = {"b", "c", "a"};
    string a7[SIZE1] = {"b", "a", "c"};

    order(aa1, SIZE);
    assert(aa1[0] == "a" && aa1[1] == "b" && aa1[2] == "c" && aa1[3] == "d");
    
    order(aa2, SIZE);
    assert(aa2[0] == "a" && aa2[1] == "b" && aa2[2] == "c" && aa2[3] == "d");
    
    order(aa3, SIZE);
    assert(aa3[0] == "a" && aa3[1] == "b" && aa3[2] == "c" && aa3[3] == "d");
    
    order(aa4, SIZE);
    assert(aa4[0] == "a" && aa4[1] == "b" && aa4[2] == "c" && aa4[3] == "d");
    
    order(aa5, SIZE);
    assert(aa5[0] == "a" && aa5[1] == "b" && aa5[2] == "c" && aa5[3] == "d");
    
    order(aa6, SIZE);
    assert(aa6[0] == "a" && aa6[1] == "b" && aa6[2] == "c" && aa6[3] == "d");
    
    order(aa7, SIZE);
    assert(aa7[0] == "a" && aa7[1] == "b" && aa7[2] == "c" && aa7[3] == "d");
    
    order(aa8, SIZE);
    assert(aa8[0] == "a" && aa8[1] == "b" && aa8[2] == "c" && aa8[3] == "d");
    
    order(aa9, SIZE);
    assert(aa9[0] == "a" && aa9[1] == "b" && aa9[2] == "c" && aa9[3] == "d");
    
    order(aa10, SIZE);
    assert(aa10[0] == "a" && aa10[1] == "b" && aa10[2] == "c" && aa10[3] == "d");
    
    order(aa11, SIZE);
    assert(aa11[0] == "a" && aa11[1] == "b" && aa11[2] == "c" && aa11[3] == "d");
    
    order(aa12, SIZE);
    assert(aa12[0] == "a" && aa12[1] == "b" && aa12[2] == "c" && aa12[3] == "d");
    
    order(aa13, SIZE);
    assert(aa13[0] == "a" && aa13[1] == "b" && aa13[2] == "c" && aa13[3] == "d");
    
    order(aa14, SIZE);
    assert(aa14[0] == "a" && aa14[1] == "b" && aa14[2] == "c" && aa14[3] == "d");
    
    order(aa15, SIZE);
    assert(aa15[0] == "a" && aa15[1] == "b" && aa15[2] == "c" && aa15[3] == "d");
    
    order(aa16, SIZE);
    assert(aa16[0] == "a" && aa16[1] == "b" && aa16[2] == "c" && aa16[3] == "d");
    
    order(aa17, SIZE);
    assert(aa17[0] == "a" && aa17[1] == "b" && aa17[2] == "c" && aa17[3] == "d");
    
    order(aa18, SIZE);
    assert(aa18[0] == "a" && aa18[1] == "b" && aa18[2] == "c" && aa18[3] == "d");
    
    order(aa19, SIZE);
    assert(aa19[0] == "a" && aa19[1] == "b" && aa19[2] == "c" && aa19[3] == "d");
    
    order(aa20, SIZE);
    assert(aa20[0] == "a" && aa20[1] == "b" && aa20[2] == "c" && aa20[3] == "d");
    
    order(aa21, SIZE);
    assert(aa21[0] == "a" && aa21[1] == "b" && aa21[2] == "c" && aa21[3] == "d");
    
    order(aa22, SIZE);
    assert(aa22[0] == "a" && aa22[1] == "b" && aa22[2] == "c" && aa22[3] == "d");
    
    order(aa23, SIZE);
    assert(aa23[0] == "a" && aa23[1] == "b" && aa23[2] == "c" && aa23[3] == "d");
    
    order(aa24, SIZE);
    assert(aa24[0] == "a" && aa24[1] == "b" && aa24[2] == "c" && aa24[3] == "d");
    
    order(a2, SIZE1);
    assert(a2[0] == "a" && a2[1] == "b" && a2[2] == "c");
    
    order(a3, SIZE1);
    assert(a3[0] == "a" && a3[1] == "b" && a3[2] == "c");
   
    order(a4, SIZE1);
    assert(a4[0] == "a" && a4[1] == "b" && a4[2] == "c");
    
    order(a5, SIZE1);
    assert(a5[0] == "a" && a5[1] == "b" && a5[2] == "c");

    order(a6, SIZE1);
    assert(a6[0] == "a" && a6[1] == "b" && a6[2] == "c");

    order(a7, SIZE1);
    assert(a7[0] == "a" && a7[1] == "b" && a7[2] == "c");

}


int main()
{
    testCountIncludes();
    testOrder();
    cout << "Pass all tests!" << endl;
}


#endif /* defined(__HW_3__tree__) */
