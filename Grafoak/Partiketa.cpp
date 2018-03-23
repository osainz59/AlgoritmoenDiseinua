//
//  Partiketa.cpp
//  Algoritmoen Diseinua
//
//  Created by Oscar Sainz Jimenez on 8/3/18.
//  Copyright © 2018 Oscar Sainz Jimenez. All rights reserved.
//

#include "Partiketa.hpp"
#include <iostream>

Partiketa::Partiketa(){
    this->N = 0;
}

Partiketa::~Partiketa(){}

Partiketa::Partiketa(int N){
    bektorea.resize(N);
    this->N = N;
    for (int i = 0; i<N; i++) {
        bektorea[i] = -1;
    }
}

int Partiketa::bilatu(int index){
    int root = this->bektorea[index];
    if(root < 0) return index;                // Burukoa bada itzuli bera.
    while(root >= 0){
        if(bektorea[root]<0) break;             // Bere gurasoa burua bada atera eta itzuli gurasoa
        root = bektorea[root];                  // bestela gurasoaren gurasoaren bila joan
    }
    this->bektorea[index] = root;               // Gurasoa eguneratu. Partiketaren 4. bertsioa.
    return root;
}

bool Partiketa::bateratu(int a, int b){
    bool posible = false;                                    // Bateratzea posiblea izan den boolearra
    int A = bilatu(a);                                       // a-ko zuhaitzaren erroa
    int B = bilatu(b);                                       // b-ko zuhaitzaren erroa
    if (A!=B) {                                              // Erro ezberdina badute bateratu, bestela ez
        if (this->bektorea[A] >= this->bektorea[B]) {
            this->bektorea[A] = this->bektorea[B] - 1;
        };
        this->bektorea[B] = A;
        posible = true;
    }
    return posible;
}

void Partiketa::print(){
    std::cout << "[";
    for (int i = 0; i<this->N; i++) {
        std::cout << this->bektorea[i];
        if(i+1 !=this->N) std::cout << ", ";
    }
    std::cout << "]\n";
}
