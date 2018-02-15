//
//  Meta.cpp
//  Algoritmoen Diseinua
//
//  Created by Oscar Sainz Jimenez on 15/2/18.
//

#include "Meta.hpp"
#include <stdexcept>
#include <limits>

Meta::Meta(){
    this->bektorea = new int[0];
    this->N = 0;
    this->azkenekoa = 0;
}

Meta::Meta(int N){
    this->bektorea = new int[N];
    this->N = N;
    this->azkenekoa = 0;
}

Meta::Meta(int bektorea[], int N){
    this->bektorea = bektorea;
    meta_eraiki_hondoratu(this->bektorea, N);
    this->N = N;
    this->azkenekoa = N;
}

Meta::~Meta(){
    delete this->bektorea;
}

int Meta::operator[](int index) const{
    if (this->azkenekoa <= index) {
        throw std::out_of_range("Out of range exception.");
    }
    return this->bektorea[index];
}

int Meta::get(int index) {
    if (this->azkenekoa <= index) {
        throw std::out_of_range("Out of range exception.");
    }
    return this->bektorea[index];
}

void Meta::insert(int balioa) {
    if (this->azkenekoa >= this->N) {
        throw std::out_of_range("Out of range exception.");
    }
    this->bektorea[this->azkenekoa] = balioa;
    this->azkenekoa++;
    azaleratu(this->bektorea, this->azkenekoa);
}

int Meta::remove(int index) {
    if (this->azkenekoa <= index) {
        throw std::out_of_range("Out of range exception.");
    }
    int value = this->bektorea[index];
    this->bektorea[index] = std::numeric_limits<int>::min();
    hondoratu(this->bektorea, index, this->N);
    
    return value;
}

void Meta::sort() {
    sort_the_heap(this->bektorea, this->N);
}

void Meta::sort(char mota) {
    sort_the_heap(this->bektorea, this->N, mota);
}


void azaleratu(int bektorea[], int P){
    int J = P;
    int lag;
    while( J > 1 ){ // Bitartean lehena ez izan, ezin duzu hori gehiago azaleratu
        if (bektorea[(J/2)-1] < bektorea[J-1]) { // Bere gurasoa baino handiagoa bada trukatu
            lag = bektorea[(J/2)-1];
            bektorea[(J/2)-1] = bektorea[J-1];
            bektorea[J-1] = lag;
            
            J = J/2;
        } else break; // Bukatu bestela
    }
}

void meta_eraiki_azaleratu(int bektorea[], int N) {
    for (int i = 2; i<=N; i++) {
        azaleratu(bektorea,i);
    }
}

void hondoratu(int bektorea[], int P, int N) {
    int unekoa = bektorea[P-1];
    int J = P;
    int umeMax;
    while (2*J <= N) {
        umeMax = 2*J;
        // Konprobatu adabegietatik zein den txikiena
        if (umeMax < N ) {
            if (bektorea[umeMax+1 -1] > bektorea[umeMax -1]) umeMax++;
        }
        // Konprobatu hondoratu behar den, ala bada egin.
        if (unekoa < bektorea[umeMax-1]){
            bektorea[J-1] = bektorea[umeMax-1];
            J = umeMax;
        }else break; // Bukatu bestela
    }
    bektorea[J-1] = unekoa;
}

void meta_eraiki_hondoratu(int bektorea[], int N){
    for (int i = N/2; i>0; i--){
        hondoratu(bektorea,i,N);
    }
}

void sort_the_heap(int bektorea[], int N, char mota){
    int* berria = bektorea;
    int lag;
    for (int i = 0; i<N; i++) {
        lag = berria[0];
        berria[0] = berria[N-1-i];
        berria[N-1-i] = lag;
        hondoratu(berria, 1, N-i-1);
    }
    if (mota == '>') {
        for (int i = 0; i<N/2; i++) {
            lag = berria[i];
            berria[i] = berria[N-i-1];
            berria[N-i-1] = lag;
        }
    }
    bektorea = berria;
}

void sort_the_heap(int bektorea[], int N){ sort_the_heap(bektorea, N, '<');}

void heap_sort(int bektorea[], int N, char mota) {
    meta_eraiki_hondoratu(bektorea, N);
    sort_the_heap(bektorea, N, mota);
}

void heap_sort(int bektorea[], int N){ heap_sort(bektorea, N, '<');}
