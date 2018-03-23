//
//  test_Grafoa.cpp
//  Algoritmoen Diseinua
//
//  Created by Oscar Sainz Jimenez on 4/3/18.
//  Copyright © 2018 Oscar Sainz Jimenez. All rights reserved.
//

#include "Grafoa.hpp"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>

void clear_screen()
{
#ifdef WINDOWS
    std::system("cls");
#else
    // Assume POSIX
    std::system ("clear");
#endif
}

void pause() {
	printf("Press ENTER to continue...\n");
	std::cin.get();
}

std::string kargatuGrafoa(Grafoa &graf, int mota) {
    std::string path;
    std::cout << "Idatzi grafoaren fitxategiaren PATH-a" << std::endl;
    std::cin >> path;
    switch (mota) {
        case 0:
            Grafoa::sortuGZ(path,graf);
            break;
        case 1:
            Grafoa::sortuGEzZ(path,graf);
            break;
        case 2:
            Grafoa::sortuGZPisuduna(path,graf);
            break;
        case 3:
            Grafoa::sortuGEzZPisuduna(path,graf);
            break;
    }
    
    return path;
    
}

// TEST FUNTZIOAK

void test_ZikloaDuG(){
    Grafoa GZB;
    std::string PATH = kargatuGrafoa(GZB, 0);
    std::cout << "Kargatutako grafoa: " << PATH << std::endl;
    GZB.print();
    std::cout << "Zikloa du: " << GZB.zikloaDuG() << std::endl;
}

void test_OrdenazioTopologikoa(){
    Grafoa graf;
    std::string PATH = kargatuGrafoa(graf, 0);
    std::cout << "Kargatutako grafoa: " << PATH << std::endl;
    graf.print();
    std::vector<int> emaitza = graf.ordenazioaTopologikoa();
    std::cout << "Lortutako ordenazioa:" << std::endl;
    std::vector<int>::iterator it;
    std::cout << "[";
    for (it = emaitza.begin();
         it != emaitza.end();
         ++it){
        std::cout << *it;
        if((it + 1) != emaitza.end()) std::cout << ", ";
    }
    std::cout << "]\n";
}

void test_ZikloaDuGEzZ(){
    std::string PATH;
    // ZIKLOA DUEN GRAFO BAT
    Grafoa GZB;
    PATH = kargatuGrafoa(GZB, 1);
    std::cout << "Kargatutako grafoa: " << PATH << std::endl;
    GZB.print();
    std::cout << "Zikloa du: " << GZB.zikloaDuG() << std::endl;
}

void test_OsagaiKonexuak(){
    Grafoa graf;
    std::string PATH = kargatuGrafoa(graf, 1);
    std::cout << "Kargatutako grafoa: " << PATH << std::endl;
    graf.print();
    std::vector<std::list<int> > emaitza = graf.osagaiKonexuak();
    std::cout << "Lortutako osagaiak:" << std::endl;
    int N = (int)emaitza.size();
    std::list<int>::iterator it;
    std::cout << "Taldea\tOsagaiak" << std::endl;
    for (int i = 0; i<N; i++){
        std::cout << i+1 << ":\t";
        for (it = emaitza[i].begin();
             it != emaitza[i].end();
             ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
}

void test_SendokiKonektatutakoOsagaiak(){
    Grafoa graf;
    std::string PATH = kargatuGrafoa(graf, 0);
    std::cout << "Kargatutako grafoa: " << PATH << std::endl;
    graf.print();
    std::vector<std::list<int> > emaitza = graf.sendokiKonektatutakoOsagaiak();
    std::cout << "Lortutako osagaiak:" << std::endl;
    int N = (int)emaitza.size();
    std::list<int>::iterator it;
    std::cout << "Taldea\tOsagaiak" << std::endl;
    for (int i = 0; i<N; i++){
        std::cout << i+1 << ":\t";
        for (it = emaitza[i].begin();
             it != emaitza[i].end();
             ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
}

/*
 *  Test honek ez du ezer pantailarazten. "kruskal_emaitza.txt" fitxategian gordetzen du.
 */
void test_Kruskal(){
    std::string SAVEPATH = "kruskal_emaitza.txt";
    Grafoa graf;
    std::string PATH = kargatuGrafoa(graf, 3);
    std::cout << "Kargatutako grafoa: " << PATH << std::endl;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    graf.HZMKruskal(SAVEPATH);
    std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() <<std::endl;
}

/*
 *  Prim - priority_queue algoritmoaren testa
 */
void test_Prim(){
    Grafoa graf;
    /*
    std::string PATH = kargatuGrafoa(graf, 3);
    std::cout << "Kargatutako grafoa: " << PATH << std::endl;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::cout << graf.Prim() << std::endl;
    std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() <<std::endl;
    */
    std::cout << "Grafo dentsoa:" << std::endl;
    Grafoa::sortuGrafoDentsoa(graf);
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::cout << graf.Prim() << std::endl;
    std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() <<std::endl;
    ///////
    std::cout << "Grafo minimoa:" << std::endl;
    Grafoa::sortuGrafoMinimoa(graf);
    begin = std::chrono::steady_clock::now();
    std::cout << graf.Prim() << std::endl;
    end= std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() <<std::endl;
}

void erakutsi_menua(Grafoa &graf, int &EGOERA, std::string &path){
    std::cout << "GRAFOAK TESTEATZEKO PROGRAMA" << std::endl;
    std::cout << "Grafo fitxategien path-a: Proba_Fitxategiak/" << std::endl << std::endl;
    std::cout << "Aukeratu testeatzeko algoritmoa:" << std::endl;
    std::cout << "(0) ATERA programatik." << std::endl;
    std::cout << "(1) ZikloaDuGZ() ZIKLOA DU (GRAFO ZUZENDUENTZAT)." << std::endl;
    std::cout << "(2) OrdenazioTopologikoa() ORDENAZIO TOPOLOGIKOA (GRAFO ZUZENDUENTZAT)." << std::endl;
    std::cout << "(3) ZikloaDuGEz() ZIKLOA DU (GRAFO EZ-ZUZENDUENTZAT)." << std::endl;
    std::cout << "(4) OsagaiKonexuak() OSAGAI KONEXUAK (GRAFO EZ-ZUZENDUENTZAT)." << std::endl;
    std::cout << "(5) SendokiKonektatutakoOsagaiak() SKO (GRAFO ZUZENDUENTZAT)." << std::endl;
    std::cout << "(6) HZMKruskal() HEDAPEN ZUHAITZ MINIMOA (GRAFO PISUDUN EZ-ZUZENDUENTZAT)." << std::endl;
    std::cout << "(7) Prim() HEDAPEN ZUHAITZ MINIMOA (GRAFO PISUDUN EZ-ZUZENDUENTZAT)." << std::endl << std::endl;
    std::cin >> EGOERA;
    switch (EGOERA) {
        case 0: // BUKATZEKO
            break;
        case 1: // ZIKLOA DU GRAFO ZUZENDUA
            test_ZikloaDuG();
            break;
        case 2: // ORDENAZIO TOPOLOGIKOA
            test_OrdenazioTopologikoa();
            break;
        case 3: // ZIKLOA DU GRAFO EZ ZUZENDUA
            test_ZikloaDuGEzZ();
            break;
        case 4: // OSAGAI KONEXUAK
            test_OsagaiKonexuak();
            break;
        case 5: // SENDOKI KONEKTATURIKO OSAGAIAK
            test_SendokiKonektatutakoOsagaiak();
            break;
        case 6: // KRUSKAL
            test_Kruskal();
            break;
        case 7: // PRIM
            test_Prim();
            break;
    }
    std::cin.get();
    
}

void start_test(){
    int EGOERA = 1;
    Grafoa graf;
    std::string path;
    while (EGOERA) {
        //system("clear");
        clear_screen();
        erakutsi_menua(graf, EGOERA, path);
        pause();
    }
}

int main(){
    start_test();
    return 0;
}

