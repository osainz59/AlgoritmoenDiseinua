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
    
    const int N = 10;
    
    Meta meta(N);
    
    // Hasieratu bektora
    for (int i = 0; i<N; i++){
        meta.insert(i);
    }
    
    meta.sort();
    
    for (int j = 0; j<N; j++) {
        std::cout << meta[j] << ", ";
    }
    std::cout << std::endl;

    return 0;
}
