//
//  Grafoa.cpp
//  Algoritmoen Diseinua
//
//  Created by Oscar Sainz Jimenez on 16/2/18.
//  Copyright © 2018 Oscar Sainz Jimenez. All rights reserved.
//

#include "Grafoa.hpp"
#include <fstream>
#include <iostream>
#include <exception>
#include <algorithm>
#include <queue>

Grafoa::Grafoa(){}

Grafoa::Grafoa(std::vector<std::list<std::pair<int, float> > > &auzokideak, bool zuzendua, bool pisuduna, int N, int A){
    this->auzokideZerrenda = auzokideak;
    this->N = N;
    this->A = A;
    this->zuzendua = zuzendua;
    this->pisuduna = pisuduna;
}

Grafoa::~Grafoa(){}

int Grafoa::getN(){
    return this->N;
}

void Grafoa::setN(int N){
    this->N = N;
}

int Grafoa::getA(){
    return this->A;
}

void Grafoa::setA(int A){
    this->A = A;
}

bool Grafoa::getZuzendua(){
    return this->zuzendua;
}

void Grafoa::setZuzendua(bool zuzendua){
    this->zuzendua = zuzendua;
}

bool Grafoa::getPisuduna(){
    return this->pisuduna;
}

void Grafoa::setPisuduna(bool pisuduna){
    this->pisuduna = pisuduna;
}

void Grafoa::gehituErtza(int erpina, std::pair<int, float> ertza){
    this->auzokideZerrenda[erpina].push_front(ertza);
    this->A++;
}

bool Grafoa::eguneratuErtza(int erpina, std::pair<int, float> ertza){
    bool aurkitua = false;
    std::list<std::pair<int, float> >::iterator it;
    for(it = this->auzokideZerrenda[erpina].begin();
        it != this->auzokideZerrenda[erpina].end();
        ++it){
        if (it->first == ertza.first){
            aurkitua = true;
            it->second = ertza.second;
            break;
        }
    }
    if(!aurkitua) gehituErtza(erpina, ertza);
    return aurkitua;
}

bool Grafoa::borratuErtza(int hasierakoErpina, int helburukoErpina){
    bool aurkitua = false;
    std::list<std::pair<int, float> >::iterator it;
    for(it = this->auzokideZerrenda[hasierakoErpina].begin();
        it != this->auzokideZerrenda[hasierakoErpina].end();
        ++it){
        if (it->first == helburukoErpina){
            aurkitua = true;
            this->auzokideZerrenda[hasierakoErpina].erase(it);
            this->A--;
            break;
        }
    }
    if (this->zuzendua) {
        for(it = this->auzokideZerrenda[helburukoErpina].begin();
            it != this->auzokideZerrenda[helburukoErpina].end();
            ++it){
            if (it->first == hasierakoErpina){
                aurkitua = true;
                this->auzokideZerrenda[helburukoErpina].erase(it);
                this->A--;
                break;
            }
        }
    }
    return aurkitua;
}

std::list<std::pair<int, float> > &Grafoa::getErpinarenAuzokideak(int erpina){
    return this->auzokideZerrenda[erpina];
}

std::pair<int, float> kargatuListaFitxategitik(std::vector<std::list<std::pair<int, float> > > &auzokideLista,
                                             std::string fitxategia,
                                             int pisuduna,
                                             bool zuzendua)
{
    std::ifstream file;
    std::string lag;
    int N = 0, A, hasierakoa, helburukoa;
    int a = 0;
    float pisua;
    std::pair<int, float> ertza;
    std::pair<int, float> ertza2;
    std::list<std::pair<int, float > >::iterator it;
    bool aurkitua;
    file.open(fitxategia);
    if(file.is_open()){
        std::getline(file, lag);
        N = std::stoi(lag);                                                     // Irakurri erpin kopurua
        auzokideLista.resize(N);                                                // Hasieratu lista N espazioekin
        std::getline(file, lag);
        A = std::stoi(lag);                                                     // Irakurri ertz kopurua
        for (int i = 0; i<A && !file.eof(); i++) {                              // Dokumentua bukatu arte edo ertz guztiak jaso arte
            file >> hasierakoa >> helburukoa >> pisua;                          // ertzak jaso eta gorde grafoan.
            /*Konprobatu existitzen den */
            aurkitua = false;
            for(it = auzokideLista[hasierakoa].begin();
                it != auzokideLista[hasierakoa].end();
                ++it){
                    if(it->first == helburukoa){
                        aurkitua = true;
                        break;
                    }
                }
            if(!aurkitua){
                ertza = std::pair<int, float>(helburukoa, pisuduna*pisua);
                auzokideLista[hasierakoa].push_front(ertza);
                a++;
            }
            /* */
            if(!zuzendua && !aurkitua){
                ertza2 = std::pair<int, float>(hasierakoa, pisuduna*pisua);
                auzokideLista[helburukoa].push_front(ertza2);
            }
        }
        
        file.close();
    } else {
        throw std::invalid_argument("Errorea fitxategia irekitzean.");
    }
    
    return std::pair<int, float>(N, a);
}

void Grafoa::sortuGZ(std::string datuak, Grafoa &graf){
    std::vector<std::list<std::pair<int, float> > > auzokideak;
    std::pair<int, float> dim;
    try {
        dim = kargatuListaFitxategitik(auzokideak, datuak, 0, true);
        graf = Grafoa(auzokideak, true, false, dim.first, dim.second);
    } catch (const std::invalid_argument& ia) {
        throw std::invalid_argument("Errorea fitxategia irekitzean.");
    }
}

void Grafoa::sortuGEzZ(std::string datuak, Grafoa &graf){
    std::vector<std::list<std::pair<int, float> > > auzokideak;
    std::pair<int, float> dim;
    try {
        dim = kargatuListaFitxategitik(auzokideak, datuak, 0, false);
        graf = Grafoa(auzokideak, false, false, dim.first, 2*dim.second);
    } catch (const std::invalid_argument& ia) {
        throw std::invalid_argument("Errorea fitxategia irekitzean.");
    }
}

void Grafoa::sortuGZPisuduna(std::string datuak, Grafoa &graf){
    std::vector<std::list<std::pair<int, float> > > auzokideak;
    std::pair<int, float> dim;
    try {
        dim = kargatuListaFitxategitik(auzokideak, datuak, 1, true);
        graf = Grafoa(auzokideak, true, true, dim.first, dim.second);
    } catch (const std::invalid_argument& ia) {
        throw std::invalid_argument("Errorea fitxategia irekitzean.");
    }
}

void Grafoa::sortuGEzZPisuduna(std::string datuak, Grafoa &graf){
    std::vector<std::list<std::pair<int, float> > > auzokideak;
    Grafoa grafoa;
    std::pair<int, float> dim;
    try {
        dim = kargatuListaFitxategitik(auzokideak, datuak, 1, false);
        graf = Grafoa(auzokideak, false, true, dim.first, 2*dim.second);
    } catch (const std::invalid_argument& ia) {
        throw std::invalid_argument("Errorea fitxategia irekitzean.");
    }
}

void Grafoa::sortuGrafoDentsoa(Grafoa &graf) { // A = n(n-1)
    std::vector<std::list<std::pair<int, float> > > auzokideak(100);
    for(int i = 0; i<100; i++){
        for(int j = 0; j<i; j++){
            auzokideak[j].push_front(std::pair<int, float>(i, (i*j)+i));
            auzokideak[i].push_front(std::pair<int, float>(j, (i*j)+i));
        }
    }
    graf = Grafoa(auzokideak, false, true, 100, 9900);
}

void Grafoa::sortuGrafoMinimoa(Grafoa &graf) {  // A = n - 1
    std::vector<std::list<std::pair<int, float> > > auzokideak(100);
    for(int i = 1; i<100; i++){
        auzokideak[i-1].push_front(std::pair<int, float>(i, i+1));
        auzokideak[i].push_front(std::pair<int, float>(i-1, i+1));
    }
    graf = Grafoa(auzokideak, false, true, 100, 99);
}

void Grafoa::print(){
    std::cout << "Erpina\t | Ertzak" << std::endl;
    std::list<std::pair<int, float> >::iterator it;
    for (int i = 0; i<this->N; i++) {
        std::cout << i << "\t |";
        for (it = this->auzokideZerrenda[i].begin(); it != this->auzokideZerrenda[i].end(); ++it) {
            std::cout << "-(" << it->first << "," << it->second << ")";
        }
        std::cout << "-|" << std::endl;
    }
}

void Grafoa::SK(int erpina, int *markak, int *marka){
    // Preprozesaketa: Markatu denbora-etiketarekin eta print egin.
    markak[erpina] = ++(*marka);
    std::cout << erpina << std::endl;
    // Auzokideak prozesatu:
    std::list<std::pair<int, float> >::iterator it;
    for (it = this->auzokideZerrenda[erpina].begin();
         it != this->auzokideZerrenda[erpina].end();
         ++it) {
        
        if (!markak[it->first]) {               // 0 bada exekutatuko da.
            SK(it->first, markak, marka);
        }
    }
    // Postprozesaketa: Markatu denbora-etiketarekin
    markak[erpina] = ++(*marka);
}

void Grafoa::grafoaKorrituSakoneran(){
    int markak[this->N];
    for (int i = 0; i<this->N; i++) {           // Hasieratu 0-ra
        markak[i] = 0;
    }
    int marka = 0;
    for (int i = 0; i<this->N; i++) {
        if (!markak[i]) {                       // 0 bada exekutatuko da.
            SK(i, markak, &marka);
        }
    }
}

void Grafoa::OTSK(int erpina, bool *markak, int *posizioa, std::vector<int> &bektorea){
    // Preprozesaketa: Markatu bisitatu egin dela.
    markak[erpina] = true;
    // Auzokideak prozesatu:
    std::list<std::pair<int, float> >::iterator it;
    for (it = this->auzokideZerrenda[erpina].begin();
         it != this->auzokideZerrenda[erpina].end();
         ++it) {
        
        if (!markak[it->first]) {               // true ez bada exekutatuko da.
            OTSK(it->first, markak, posizioa, bektorea);
        }
    }
    // Postprozesaketa:
    bektorea[(*posizioa)--] = erpina;           // Erpina bere posizioan kokatu eta indizea jaitsi
}

std::vector<int> Grafoa::ordenazioaTopologikoa(){
    std::vector<int> bektorea(0);               // 0 tamainako bektore bat sortu.
    if (!this->zuzendua) {
        return bektorea;
    }
    bektorea.resize(this->N);                   // Bektorearen tamaina N-ra aldatu.
    bool markak[this->N];                       // Markaketa boolearrak erabiliz, ez dugu denbora markarik behar.
    for (int i = 0; i<this->N; i++) {           // Hasieratu marka guztiak falsera. O(n)
        markak[i] = false;
    }
    int posizioa = this->N - 1;                 // Hasieratu txertatu behar den posizioa. Hasieran azkenekoa.
    for (int i = 0; i<this->N; i++) {
        if (!markak[i]) {                       // true ez bada exekutatuko da.
            OTSK(i, markak, &posizioa, bektorea);
        }
    }
    
    return bektorea;
}

bool Grafoa::zikloaDuG(){
    if (this->zuzendua) {
        return zikloaDuGZ();
    } else return zikloaDuGEzZ();
}

bool Grafoa::ZDGZSK(int erpina, int *markak){
    // Preprozesaketa: Uneko azpigrafoan dagoela atzituko diogu marketan.
    markak[erpina] = 0;
    // Auzokideak prozesatu:
    std::list<std::pair<int, float> >::iterator it;
    for (it = this->auzokideZerrenda[erpina].begin();
         it != this->auzokideZerrenda[erpina].end();
         ++it) {
        
        if (markak[it->first] == 0) {
            return true;
        } else
        if (markak[it->first] == -1) {
            if (ZDGZSK(it->first, markak)) return true;
        }
    }
    // Postprozesaketa: Uneko erpina bisitatua bezela markatu, azpigrafoa itxiz.
    markak[erpina] = 1;
    return false;
}

bool Grafoa::zikloaDuGZ(){
    bool zikloaDu = false;
    int markak[this->N];
    for (int i = 0; i<this->N; i++) {           // Hasieratu -1-ra: marka = -1 => Ez bisitatua
        markak[i] = -1;                         //                           0 => Uneko azpigrafoan (beraz zikloa)
    }                                           //                           1 => Bisitatua baina beste azpigrafo batean.
    for (int i = 0; i<this->N; i++) {
        if (markak[i] == -1) {
            zikloaDu = ZDGZSK(i, markak);
        }
        if (zikloaDu) {
            break;
        }
    }
    
    return zikloaDu;
}

bool Grafoa::ZDGEZSK(int erpina, int gurasoa, int *markak){
    // Preprozesaketa: Uneko azpigrafoan dagoela atzituko diogu marketan.
    markak[erpina] = 0;
    // Auzokideak prozesatu:
    std::list<std::pair<int, float> >::iterator it;
    for (it = this->auzokideZerrenda[erpina].begin();
         it != this->auzokideZerrenda[erpina].end();
         ++it) {
        
        if (it->first == gurasoa) continue;     // Uneko auzokidea gurasoa bada kasurik ez egin.
        
        if (markak[it->first] == 0) {
            return true;
        } else
            if (markak[it->first] == -1) {
                if (ZDGEZSK(it->first, erpina, markak)) return true;
            }
    }
    // Postprozesaketa: Uneko erpina bisitatua bezela markatu, azpigrafoa itxiz.
    markak[erpina] = 1;
    return false;
}

bool Grafoa::zikloaDuGEzZ(){
    bool zikloaDu = false;
    int markak[this->N];
    for (int i = 0; i<this->N; i++) {           // Hasieratu -1-ra: marka = -1 => Ez bisitatua
        markak[i] = -1;                         //                           0 => Uneko azpigrafoan (beraz zikloa)
    }                                           //                           1 => Bisitatua baina beste azpigrafo batean.
    for (int i = 0; i<this->N; i++) {
        if (markak[i] == -1) {
            zikloaDu = ZDGEZSK(i, -1, markak);  // Hasieran gurasorik ez duenez -1 erpina (ez dana existitzen) esleituko diogu
        }
        if (zikloaDu) {
            break;
        }
    }
    
    return zikloaDu;
}

void Grafoa::OKSK(int erpina, bool *markak, std::list<int> &zerrenda){
    // Preprozesaketa:
    markak[erpina] = true;
    zerrenda.push_front(erpina);                // O(1)
    // Auzokideak prozesatu:
    std::list<std::pair<int, float> >::iterator it;
    for (it = this->auzokideZerrenda[erpina].begin();
         it != this->auzokideZerrenda[erpina].end();
         ++it) {
        if (!markak[it->first]) {
            OKSK(it->first, markak, zerrenda);
        }
    }
    // Posprozesaketa: ez da behar.
}

std::vector<std::list<int> > Grafoa::osagaiKonexuak(){
    std::vector<std::list<int> > bektorea(0);    // 0 dimentsioarekin hasieratu zuzendua den edo ez begiratu aurretik
    if (this->zuzendua) return bektorea;       // Zuzendua ez bada itzuli array hutsa
    bektorea.resize(this->N);                   // Kasu txarrenean N elementu izango ditu
    bool markak[this->N];
    for (int i = 0; i<this->N; i++) {           // Hasieratu marka guztiak falsera. O(n)
        markak[i] = false;
    }
    int pos = 0;
    for (int i = 0; i<this->N; i++) {
        if (!markak[i]){
            OKSK(i, markak, bektorea[pos++]);    // Zerrenda osatu eta bektorean gorde, honela egiten bada erreferentziaz
        }                                        // pasatuko da eta ez da kopiarik egin beharko.
    }
    bektorea.resize(pos);                        // Bektorearen tamaina txikitu soluzioraino
    return bektorea;
}

void Grafoa::lortuIraulia(Grafoa &graf){
    std::vector<std::list<std::pair<int, float> > > auzokideak(this->N);
    std::list<std::pair<int, float> >::iterator it;
    for (int i = 0; i<this->N; i++) {
        for (it = this->auzokideZerrenda[i].begin();
             it != this->auzokideZerrenda[i].end();
             ++it) {
            auzokideak[it->first].push_front(std::pair<int, float>(i, it->second));
        }
    }
    graf = Grafoa(auzokideak, this->zuzendua, this->pisuduna, this->N, this->A);
}

std::vector<std::list<int> > Grafoa::sendokiKonektatutakoOsagaiak(){
    std::vector<std::list<int> > bektorea(0);                        // 0 dimentsioarekin hasieratu zuzendua den edo ez begiratu aurretik
    if (!this->zuzendua) return bektorea;                           // Zuzendua ez bada itzuli array hutsa
    bektorea.resize(this->N);                                       // Kasu txarrenean N elementu izango ditu
    // Grafoaren denbora marken alderantzizko ordena lortu, hain zuzen ere ordenazio topologikoa
    std::vector<int> ordena = this->ordenazioaTopologikoa();        // O(n+a)
    // Grafo iraulia lortu
    Grafoa iraulia;
    this->lortuIraulia(iraulia);                                     // O(n+a)
    // Grafo irauliaren osagai konexuak lortu ordena jarraituz
    bool markak[this->N];
    for (int i = 0; i<this->N; i++) {
        markak[i] = false;
    }
    int pos = 0;
    for (int i = 0; i<this->N; i++) {
        if (!markak[ordena[i]]){
            iraulia.OKSK(ordena[i], markak, bektorea[pos++]);       // Zerrenda osatu eta bektorean gorde, honela egiten bada erreferentziaz
        }                                                           // pasatuko da eta ez da kopiarik egin beharko. O(n+a)
    }
    bektorea.resize(pos);
    
    return bektorea;
}

void Grafoa::HZMKruskal(std::string path){
    // Testerako
    int erag_kopurua = 0;
    if(this->zuzendua) return;
    // LORTU HERTZAK O(n+a)
    std::vector<std::pair<std::pair<int, int>, float> > hertzak(this->A);    // Bektore bat non ((A, B), P) motako elementuak dauden (A, B) hertza P pisua, A elementukoa, hain zuzen ere 2a
    int i = 0;
    for (int j = 0; j<this->N; j++) {
        std::list<std::pair<int, float> >::iterator it;
        for (it = this->auzokideZerrenda[j].begin();
             it != this->auzokideZerrenda[j].end();
             ++it) {
            std::pair<int, int> hertza(j, it->first);
            hertzak[i++] = std::pair<std::pair<int, int>, float>(hertza, it->second);
        }
    }
    // ORDENATU HERTZAK O(a·lga)
    std::sort(hertzak.begin(), hertzak.end(), [](std::pair<std::pair<int, int>, float> a, std::pair<std::pair<int, int>, float> b){
        if(a.second == b.second){
            return a.first.first < b.first.first;
        }
        return a.second < b.second;                             // sort() funtzioa MergeSort algoritmoa aplikatzen du C++11-tik aurrera
    });                                                         // QuickSort bestela, gomendatzen da C++11 erabiltzea.
    // HASIERAKETA + PARTIKETA O(1 + n)
    Partiketa partiketa(this->N);
    std::list<std::pair<std::pair<int, int>, float> > soluzioa;
    // ZIKLOA
    i = 0;
    float pisua = 0;
    for(int j = 0; j<this->A; j++){
        if (i == this->N) break;
        if (partiketa.bateratu(hertzak[j].first.first, hertzak[j].first.second)){
            i++;
            pisua += hertzak[j].second;
            soluzioa.push_front(hertzak[j]);
        }
    }
    // IDATZI EMAITZA
    std::ofstream emaitza(path);
    
    std::cout << i << std::endl;
    emaitza << i << std::endl;
    std::cout << pisua << std::endl;
    emaitza << pisua << std::endl;
    std::list<std::pair<std::pair<int, int>, float> >::reverse_iterator it;
    for (it = soluzioa.rbegin();
         it != soluzioa.rend();
         ++it) {
        std::cout << it->first.first << " " << it->first.second << " " << it->second << std::endl;
        emaitza << it->first.first << " " << it->first.second << " " << it->second << std::endl;
    }
    
    emaitza.close();
    
}


float Grafoa::Prim(){
    // Uneko pisurik txikienekoa hartzeko meta, non pair<PISUA, ERPINA> moduko ertzak dauden.
    LehentasunIlara pq;
    pq.push(std::pair<float, int>(0, 0));// Hasieratu 0 erpinarekin 0 pisuarekin.
    // Erpinak listan dauden jakiteko denbora konstantean.
    std::vector<bool> hartuta(this->N, false);
    int erpinKop = 0; // Ahal bada lehenago bukatzeko
    // Pisua gordetzeko aldagaia
    int pisuTotala = 0;
    while(!pq.empty()){ // Lehentasun ilara (Meta) hutsik ez dagoen bitartean
        int erpina = pq.top().second;
        float pisua = pq.top().first;
        pq.pop();
        if(!hartuta[erpina]) {  // Begiratu erpina jadanik aukeratuta dagoen, horrela ez bada gehitu
            hartuta[erpina] = true;
            pisuTotala += pisua;
            if(++erpinKop == this->N) break;    // Erpin guztiak gorde baditugu bukatu.

            // Bestela, erpin berriaren auzokideak sartu, baldin eta lehendik aukeratuak ez egon
            for(std::list<std::pair<int, float> >::iterator it = this->auzokideZerrenda[erpina].begin();
                it != this->auzokideZerrenda[erpina].end();
                ++it){

                    // Jadanik hartuta ez badaude
                    if(!hartuta[it->first]){
                        // Erpina meta barruan badago eguneratu, bestela gehitu.
                        // Bi eragiketak O(lgn) egingo dira atzipen zuzeneko meta delako eta meta
                        // egitura berreskuratu behar delako.
                        if(pq.exist(it->first)){
                            if(pq[it->first].first <= it->second) continue; // Dagoena unekoa baino txikiagoa bada
                            pq.update(std::pair<float, int>(it->second, it->first));
                        }else pq.push(std::pair<float, int>(it->second, it->first));
                    }

            }
        }
    }
    return pisuTotala;
}




