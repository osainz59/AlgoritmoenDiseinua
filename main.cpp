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
#include <vector>
#include <fstream>
#include <unistd.h>
#include "Grafoak/Grafoa.hpp"
#include <list>
#include "test_Grafoa.hpp"

// /Users/osainz59/Documents/workspace/Algoritmoen_Diseinua/Proba_Fitxategiak/

#define PATH "/Users/osainz59/Documents/workspace/Algoritmoen Diseinua/Proba_Fitxategiak/"
#define Ordenazio_Topologikoa "OrdenazioTopologikoa.txt"
#define Zikloa_Du_Grafo_Ez_Zuzendua_Bai "ZikloaDuGEZBAI.txt"
#define Sendoki_Konektatutako_Osagaiak "sendokiKonektatutakoOsagaiakGZ8n13a.txt"

int main(int argc, const char * argv[]) {
    
    Grafoa graf = Grafoa::sortuGZ(PATH+std::string(Zikloa_Du_Grafo_Ez_Zuzendua_Bai));
    graf.HZMKruskal("");
    

    return 0;
}
