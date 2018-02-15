//
//  Sort.cpp
//  Algoritmoen Diseinua
//
//  Created by Oscar Sainz Jimenez on 15/2/18.
//

#include "Sort.hpp"


void merge(int b1[] , int N1 , int b2[] , int N2 , int lag[])
{
    int i1, i2, i3;
    i1 = 0; i2 = 0; i3 = 0;
    while (i1 < N1 && i2 < N2) {
        if (b1[i1] < b2[i2]) {
            lag[i3++] = b1[i1++];
        }
        else {
            lag[i3++] = b2[i2++];
        }
    }
    while (i1 < N1) {
        lag[i3++] = b1[i1++];
    }
    while (i2 < N2) {
        lag[i3++] = b2[i2++];
    }
}

void merge_sort(int array[], int size)
{
    int temp[size];
    int mid, i;
    if (size < 2) {
        return;
    }
    else {
        mid = size / 2;
        merge_sort(array, mid);
        merge_sort(array + mid, size - mid);
        merge(array, mid, array + mid, size - mid, temp);
        for (i = 0; i < size; i++) {
            array[i] = temp[i];
        }
    }
}
