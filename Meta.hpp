//
//  Meta.hpp
//  Algoritmoen Diseinua
//
//  Created by Oscar Sainz Jimenez on 15/2/18.
//

#ifndef Meta_hpp
#define Meta_hpp

#include <stdio.h>

class Meta {
    
public:
    Meta();
    Meta(int bektorea[], int N);
    Meta(int N);
    ~Meta();
    int operator[](int index) const;
    int get(int index);
    void insert(int balioa);
    int remove(int index);
    void sort();
    void sort(char mota);

private:
    int* bektorea;
    int N;
    int azkenekoa;
};

void azaleratu(int bektorea[], int P);
void meta_eraiki_azaleratu(int bektorea[], int N);
void hondoratu(int bektorea[], int P, int N);
void meta_eraiki_hondoratu(int bektorea[], int N);
void sort_the_heap(int bektorea[], int N, char mota);
void sort_the_heap(int bektorea[], int N);
void heap_sort(int bektorea[], int N);
void heap_sort(int bektorea[], int N, char mota);

#endif /* Meta_hpp */
