//
//  main.cpp
//  Algoritmoen Diseinua
//
//  Created by Oscar Sainz Jimenez on 8/2/18.
//  Copyright © 2018 Oscar Sainz Jimenez. All rights reserved.
//

#include <iostream>
#include <array>
#include <ctime>
#include "Meta.hpp"
#include "Sort.hpp"


int main(int argc, const char * argv[]) {
    
    const int N = 100000000;
    clock_t begin_time, end_time;
    int* bektorea = new int[N];
    
    // Hasieratu bektora
    for (int i = 0; i<N; i++){
        bektorea[i] = i;
    }
    // Hondoratuz
    begin_time = std::clock();
    meta_eraiki_hondoratu(bektorea, N);
    end_time = std::clock();
    std::cout << "N = " << N << " izanda hondoratu metodoarekin: " << double(end_time - begin_time) / CLOCKS_PER_SEC << std::endl;
    
    for (int i = 0; i<N; i++){
        bektorea[i] = i;
    }
    //Azaleratuz
    begin_time = std::clock();
    meta_eraiki_azaleratu(bektorea, N);
    end_time = std::clock();
    std::cout << "N = " << N << " izanda azaleratu metodoarekin: " << double(end_time - begin_time) / CLOCKS_PER_SEC << std::endl;

    return 0;
}

// N = 10^2              N = 10^4                  N = 10^6                 N = 10^8
// Hondoratu: 4e-06s     Hondoratu: 9.2e-05s       Hondoratu: 0.010257s     Hondoratu: 1.04738s
// Azaleratu: 8e-06s     Azaleratu: 0.001662s      Azaleratu: 0.264946s     Azaleratu: 34.9322s
