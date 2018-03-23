//
//  Grafoa.hpp
//  Algoritmoen Diseinua
//
//  Created by Oscar Sainz Jimenez on 16/2/18.
//  Copyright © 2018 Oscar Sainz Jimenez. All rights reserved.
//

#ifndef Grafoa_hpp
#define Grafoa_hpp

#include <stdio.h>
#include <list>
#include <vector>
#include <utility>
#include <string>
#include "Partiketa.hpp"
#include "LehentasunIlara.hpp"

class Grafoa {
    
public:
    
    /*
     *  Grafoa klasearen suntsitzailea.
     */
    ~Grafoa();
    
    /*
     *  Grafo klasearen eraikitzaile hutsa.
     */
    Grafoa();
    
    /*
     *  Grafoaren erpin kopurua itzultzen duen funtzioa. Funtzio honekin O(1) lortzen dugu eta ez O(n).
     */
    int getN();
    
    /*
     *  Grafoaren ertz kopurua itzultzen duen funtzioa.
     */
    int getA();
    
    /*
     *  Grafoa zuzendua edo ez den jakiteko funtzioa. O(1)
     */
    bool getZuzendua();
    
    /*
     *  Grafoa pisuduna edo ez den jakiteko funtzioa. O(1)
     */
    bool getPisuduna();
    
    /*
     *  Grafoari ertz bat gehitzen zaio. Erpinaren auzokideen listaren hasieran gehitzen da ertza, beraz O(1)
     */
    void gehituErtza(int erpina, std::pair<int, float> ertza);
    
    /*
     *  Grafoari ertz bat gehitzen zaio. Erpinaren auzokideen lista korritzen da gehitu/aldatu nahi den
     *  ertza existitzen den begiratuz, existitzen bada eguneratzeko, bestela gehitzeko. True itzultzen
     *  da ertza ordeztu badu, false ertza aurretik existitzen ez bada. O(a)
     */
    bool eguneratuErtza(int erpina, std::pair<int, float> ertza);
    
    /*
     *  Grafoan dagoen ertz bat kentzen du. Zuzendua bada arkua kenduko du. Lista bat erabiltzen dugunez. O(n)
     */
    bool borratuErtza(int hasierakoErpina, int helburukoErpina);
    
    /*
     *  Erpin baten auzokideen lista itzultzen duen funtzioa. O(1)
     */
    std::list<std::pair<int, float> > &getErpinarenAuzokideak(int erpina);
    
    /*
     *  Grafoa pantailaratzen du. O(n+a)
     */
    void print();
    
    /*  EREDUA
     *  Grafoa sakoneran korritzen duen funtzioa. O(n+a)
     */
    void grafoaKorrituSakoneran();
    
    /*
     *  Uneko grafoaren iraulia itzultzen duen metodoa. O(n+a)
     */
    void lortuIraulia(Grafoa &graf);

    static void sortuGrafoDentsoa(Grafoa &graf);
    static void sortuGrafoMinimoa(Grafoa &graf);
    
    /*
     *  1. INPLEMENTAZIORAKO ARIKETAK
     */
    
    /*
     *  Grafoa fitxategi batetik sortzeko erabiltzen den funtzioa. Begiratzen da jadanik existitzen den ertz hori, kasu txarrenean
     *  O(a) beraz grafoa sortzeko O(n + a^2) gelditzen zaigu.
     */
    static void sortuGZ(std::string datuak, Grafoa &graf);              // Sortu Grafo Zuzendua O(n+a^2)
    static void sortuGEzZ(std::string datuak, Grafoa &graf);            // Sortu Grafo ez Zuzendua O(n+a^2)
    static void sortuGZPisuduna(std::string datuak, Grafoa &graf);      // Sortu Grafo Zuzendu Pisuduna O(n+a^2)
    static void sortuGEzZPisuduna(std::string datuak, Grafoa &graf);    // Sortu Grafo ez Zuzendu Pisuduna O(n+a^2)
    
    /*
     *  Grafoaren ordenazio Topologikoa itzultzen du baldin eta grafoa zuzendua bada, bestela array huts bat itzuliko du. O(n+a)
     */
    std::vector<int> ordenazioaTopologikoa();
    
    /*
     *  Grafoan ziklorik dagoen itzultzen duen funtzioa. Grafo zuzenduetarako eta ez-zuzenduetarako balio du. O(n+a)
     */
    bool zikloaDuG();
    
    /*
     *  Array bat itzultzen du, non elementu bakoitza osagai konexu bat adieraziz, haren erpin guztien zerrenda jasotzen den.
     *  Grafoa zuzendua ez bada array hutsa itzuliko du. O(n+a)
     */
    std::vector<std::list<int> > osagaiKonexuak();
    
    /*
     *  Array bat itzultzen du, non elementu bakoitza sendoki konektaturiko osagai bat adieraziz, haren erpin guztien zerrenda jasotzen
     *  duen. Grafoa ez-zuzendua bada array hutsa itzuliko du. O(n+a)
     */
    std::vector<std::list<int> > sendokiKonektatutakoOsagaiak();
    
    /*
     *  Hedapen Zuhaitz Minimoa fitxategi batean idazten duen funtzioa. Kruskal-en algoritmoa erabiliz eta partiketa 3edo4 bertsioa inplementatuta. O(a·lga)
     */
    void HZMKruskal(std::string path);

    /*
     *
     */
    float Prim();
    
private:
    
    /*
     *  Auzokideen zerrenda, LinkedList-en Array bat. Ordenak: n = erpin kopurua, a = ertz kopurua
     *                                                  - O(1) Erpin baten auzokide lista atzitzea.
     *                                                  - O(1) Erpin bati auzokide bat gehitzea. (push_front erabiliz)
     *                                                  - O(n) Erpinak korritzea.
     *                                                  - O(a) Erpin baten auzokide bat atzitzea.
     *                                                  - O(a) Erpin baten auzokideak korritzea.
     *                                                  - O(n+a) Grafoa korritzea.
     */
    std::vector<std::list<std::pair<int, float> > > auzokideZerrenda;
    
    /*
     *  Grafoa zuzendua den ala ez adierazten duen boolearra.
     */
    bool zuzendua;
    
    /*
     *  Erpin kopurua adierazten duen osokoa.
     */
    int N;
    
    /*
     *  Ertz kopurua adierazten duen osokoa.
     */
    int A;
    
    /*
     *  Pisuduna den ala ez adierazten duen boolearra
     */
    bool pisuduna;
    
    /*
     *  Grafoa klasearen eraikitzaileak. Pribatuak dira grafoak sortzeko beste funtzio batzuk erabili behar direlako.
     *  Hain zuzen ere: sortuGZ, sortuGEzZ, sortuGZPisuduna eta sortuGEzZPisuduna.
     */
    Grafoa(std::vector<std::list<std::pair<int, float> > > &auzokidea, bool zuzendua, bool pisuduna, int N, int A);
    
    /*
     *  Grafoaren erpin kopurua aldatzen duen funtzioa. Ez litzake erabili behar.
     */
    void setN(int N);
    
    /*
     *  Grafoaren ertz kopurua aldatzen duen funtzioa. Ez litzake erabili behar.
     */
    void setA(int A);
    
    /*
     *  Grafoa zuzendua edo ez-zuzendua ezartzeko funtzioa. Ez litzake erabili behar.
     */
    void setZuzendua(bool zuzendua);
    
    /*
     *  Grafoa pisuduna edo ez ezartzeko funtzioa. Ez litzateke erabili behar.
     */
    void setPisuduna(bool pisuduna);
    
    /*
     *  Sakonerako korritzea. Erpin batetik egin dezakeen sakonerako korritzea.
     */
    void SK(int erpina, int *markak, int *marka);
    
    /*
     *  Ordenazio Topologikorako SK. Ezaugarriak:
     *                                      - Markak adierazteko ez da denbora markak erabiliko, bisitatua edo ez baizik.
     *                                      - Postprozesaketan hasieran txertatuko da aztertutako erpina bektore batean.
     */
    void OTSK(int erpina, bool *markak, int *posizioa, std::vector<int> &bektorea);
    
    /*
     *  Grafo Zuzendu batek ziklorik duen esaten duen funtzioa.
     */
    bool zikloaDuGZ();
    
    /*
     *  Zikloa Du Grafo Zuzenduko Sakonerako Korritzea. Ezaugarriak:
     *                                      - Markak adierazteko ez da denbora markak erabiliko:
     *                                              -1 => Ez bisitatua
     *                                               0 => Uneko azpigrafoan (beraz zikloa)
     *                                               1 => Bisitatua baina beste azpigrafo batean.
     */
    bool ZDGZSK(int erpina, int *markak);
    
    /*
     *  Grafo Ez-Zuzendu batek ziklorik duen esaten duen funtzioa.
     */
    bool zikloaDuGEzZ();
    
    /*
     *  Zikloa Du Grafo Ez Zuzenduko Sakonerako Korritzea. Ezaugarriak:
     *                                      - Markak adierazteko ez da denbora markak erabiliko:
     *                                              -1 => Ez bisitatua
     *                                               0 => Uneko azpigrafoan (beraz zikloa)
     *                                               1 => Bisitatua baina beste azpigrafo batean.
     */
    bool ZDGEZSK(int erpina, int gurasoa, int *markak);
    
    /*
     *  Osagai Konexuetarako Sakonerako Korritzea
     */
    void OKSK(int erpina, bool *markak, std::list<int> &zerrenda);
};

#endif /* Grafoa_hpp */
