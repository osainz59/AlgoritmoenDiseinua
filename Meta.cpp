//
//  Meta.cpp
//  Algoritmoen Diseinua
//
//  Created by Oscar Sainz Jimenez on 15/2/18.
//

#include "Meta.hpp"


void azaleratu(int bektorea[], int P, int N){
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
        azaleratu(bektorea,i,N);
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
