//
//  Partiketa.hpp
//  Algoritmoen Diseinua
//
//  Created by Oscar Sainz Jimenez on 8/3/18.
//  Copyright © 2018 Oscar Sainz Jimenez. All rights reserved.
//

#ifndef Partiketa_hpp
#define Partiketa_hpp

#include <stdio.h>
#include <vector>

/* PARTIKETA V4 BERTSIOA */
class Partiketa{
    
public:
    Partiketa(int N);
    ~Partiketa();
    
    /*
     *  Partition v4 bertsioko bilaketa, non bilatutako nodoa erroaren adabegitzat jartzen den.
     */
    int bilatu(int index);
    
    /*
     *  Bi nodo emanda, erro ezberdinekoak izanik, baten erroa bestearen erroaren adabegitzat jarriko da.
     */
    bool bateratu(int a, int b);
    
    /*
     *  Margotu partiketa.
     */
    void print();
    
    /*
     *  Itzuli partiketa oinarritzat duen bektorea.
     */
    std::vector<int> & getBektorea();
    
private:
    std::vector<int> bektorea;
    int N;
    
    Partiketa();
};


#endif /* Partiketa_hpp */
