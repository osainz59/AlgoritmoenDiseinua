#include "SAT.hpp"
//#include <vector>
//#include <utility>
#include <queue>
#include <fstream>
#include <iostream>

int NC, NV;
std::vector<std::pair<std::vector<int>, int> >  Formula;

std::vector<bool> aldagai_aktiboak;
std::vector<int> aldagai_positibo, aldagai_negatibo;

long DK;

/*
                   A   B   C   D   E   F   G
(A v ¬B)        [  1, -1,  0,  0,  0,  0,  0 ] | B (1)
(C v ¬A v D)    [ -1,  0,  1,  1,  0,  0,  0 ] | D (3)
(E)             [  0,  0,  0,  0,  1,  0,  0 ] | E (4)
(¬F v G)        [  0,  0,  0,  0,  0, -1,  1 ] | G (6)

Izanda matrize bat NCxNV, non NV datuetan ager litezkeen proposamen aldagaien kopurua
eta NC datuetan agertzen diren klausulen kopurua den.

*/

void kargatu_formula(std::string &sarrera_fitxategia) {

    /*
     *  IRAKURKETA FASEA
     */
    
    std::ifstream sarrera;
    std::string lag;
    int balioa, max_ind;
    bool garbitu;

    try {
        sarrera.open(sarrera_fitxategia);
        if (sarrera.is_open()) {
            // Lehenengo 5 lerroak jauzi
            for (int i = 0; i<5; i++) std::getline(sarrera, lag);

            sarrera >> lag; // p
            sarrera >> lag; // cnf
            sarrera >> NV >> NC;

            //Formula.resize(NC); // NC klausula egongo dira.
            //aldagai_positibo.resize(NV+1); aldagai_negatibo.resize(NV+1);

            Formula = std::vector<std::pair<std::vector<int>, int> >(NC);
            aldagai_positibo = std::vector<int>(NV+1,0);
            aldagai_negatibo = std::vector<int>(NV+1,0);

            // Klausulak irakurri
            for (int i = 0; i<NC; i++) {
                // klausulak NV+1 aldagai izango dituzte baina 0. ez da erabiliko
                Formula[i].first.resize(NV+1);  
                max_ind = 0;
                garbitu = false;
                do {
                    sarrera >> balioa;
                    if (balioa > 0) {
                        if (Formula[i].first[balioa] == -1) {
                            garbitu = true;
                        }
                        Formula[i].first[balioa] = 1;
                        aldagai_positibo[balioa]++;
                    } else if(balioa < 0) {
                        balioa = -1*balioa;
                        if (Formula[i].first[balioa] == 1) {
                            garbitu = true;
                        }
                        Formula[i].first[balioa] = -1;
                        aldagai_negatibo[balioa]++;
                    }
                    if (balioa > max_ind) max_ind = balioa;
                } while (balioa != 0);
                if (!garbitu) Formula[i].second = max_ind;
                else Formula[i].second = 0;
            }
        } else {
            std::cerr << "Errorea fitxategiak irekitzean." << sarrera_fitxategia << std::endl;
		    return;
        }

        sarrera.close();

    } catch (int e) {
		std::cerr << "Errorea fitxategiak irekitzean." << sarrera_fitxategia << std::endl;
		return;
	}
}

int lortu_hurrengoa(int i) {
    for (int j = i+1; j<=NV; j++) {
        if(aldagai_aktiboak[j]) {
            return j;
        } 
    }
    return NV+1;
}


bool ebaluatu_formula(std::vector<bool> &SP) {
    bool emaitza = true;

    for (int i = 0; i<NC; i++) {    // Klausula bakoitzeko
        if (Formula[i].second == 0) continue;
        emaitza = false;
        for (int j = 1; j<=NV; j++) {
            if (Formula[i].first[j] == 0) continue;
            if ((Formula[i].first[j] == 1 && SP[j]) ||(Formula[i].first[j] == -1 && !SP[j])) {
                emaitza = true;
                break;
            }
        }
        if (!emaitza) break;
    }

    return emaitza;
}

bool SATBT(std::vector<bool> &SP, int I, std::queue<int> &KlausulaZerrenda){

    // Kontrola: Inkrementatu dei kopurua.
    DK++;
    // TRAZA: std::cout << I << ": (" << SP[I] << ") " << KlausulaZerrenda.size() << std::endl; 

    // Klausula guztiak TRUE dira beraz Formula TRUE da.
    if (KlausulaZerrenda.empty()) return true;    
    // Bukaerara iritsi gara eta ez da soluziorik aurkitu
    else if (I > NV) return false;      
    // Ebaluatu gelditzen diren klausulak I. literalarekin.            
    else
    {                                               
        std::queue<int> false_zerrenda, true_zerrenda;
        int klausula;
        while (!KlausulaZerrenda.empty())
        {
            klausula = KlausulaZerrenda.front();
            KlausulaZerrenda.pop();

            // Klausula huts bat da, beraz Formula ez da Betegarria
            if (Formula[klausula].second < I) return false; 

            // Ez bada existitzen I literala klausula horretan true emanez klausula true emango duenik
            // aztertzen jarraitu behar da.
            if (Formula[klausula].first[I] != 1) true_zerrenda.push(klausula);  

            // Ez bada existitzen I literala klausula horretan false emanez klausula true emango duenik
            // aztertzen jarraitu behar da.
            if (Formula[klausula].first[I] != -1) false_zerrenda.push(klausula); 
        }
        // TRAZA: std::cout << I << "-->";
        int J = lortu_hurrengoa(I);
        // TRAZA: std::cout << J << std::endl;

        // Adarkatu false bezela
        SP[I] = false;
        if (SATBT(SP, J, false_zerrenda)) return true;
        // Adarkatu true bezela
        SP[I] = true;
        if (SATBT(SP, J, true_zerrenda)) return true;
    }

    // Azpizuhaitza aztertu ondoren ez da aurkitu soluziorik.
    return false;

}

bool SAT(std::string &sarrera_fitxategia, long &dei_kop) {

    kargatu_formula(sarrera_fitxategia);

    /*
     *  PRE-PROZESU FASEA
     */
    

    // Agertzen bada literal bat, non bakarrik egoera positiboan edo negatiboan 
    // dagoen. Orduan garbitu literal hori dauzkaten klausulak.
    std::vector<bool> SP(NV+1,false);
    aldagai_aktiboak.resize(NV+1);
    for (int i = 1; i<=NV; i++) {
        if (aldagai_positibo[i] == 0 || aldagai_negatibo[i] == 0) {
            aldagai_aktiboak[i] = false;
            for (int j = 0; j<NC; j++) {
                if (Formula[j].first[i] != 0) Formula[j].second = 0;
            }
            if (aldagai_positibo[i] > aldagai_negatibo[i]) SP[i] = true;
        } else aldagai_aktiboak[i] = true;
    }
    std::queue<int> KlausulaZerrenda;
    for (int i = 0; i<NC; i++) {
        if (Formula[i].second > 0) KlausulaZerrenda.push(i);    // Klausula honetan ez da aurkitu (A V ¬A) motakorik
    } 
    DK = -1;
    // TRAZA: std::cout << "Hasierako zerrenda luzeera: " << KlausulaZerrenda.size() << std::endl;

    /*
     *  BACKTRACK DEIA
     */
    
    bool emaitza = SATBT(SP, lortu_hurrengoa(-1), KlausulaZerrenda);

    /*
    std::cout << "BT adarkatze kopurua: " << DK << std::endl;

    
     *  MARGOTU EMAITZA
     

    for (int j = 1; j<=NV; j++) {
        std::cout << SP[j] << " ";
    }
    std::cout << std::endl;

    std::cout << "Ebaluatu formula: " << ebaluatu_formula(SP) << std::endl;
    */

    dei_kop = DK;

    return emaitza;
}


bool SATBT_geldoa(std::vector<bool> &SP, int I){

    // Kontrola: Inkrementatu dei kopurua.
    DK++;

    if (I > NV) {
        return ebaluatu_formula(SP);
    } else {
        int J = lortu_hurrengoa(I);
        // Adarkatu false bezela
        SP[I] = false;
        if (SATBT_geldoa(SP, J)) return true;
        // Adarkatu true bezela
        SP[I] = true;
        if (SATBT_geldoa(SP, J)) return true;
    }

    return false;

}


bool SAT_geldoa(std::string &sarrera_fitxategia, long &dei_kop) {

    kargatu_formula(sarrera_fitxategia);

    std::vector<bool> SP(NV+1,false);

     /*
     *  PRE-PROZESU FASEA
     */
    

    // Agertzen bada literal bat, non bakarrik egoera positiboan edo negatiboan 
    // dagoen. Orduan garbitu literal hori dauzkaten klausulak.
    aldagai_aktiboak.resize(NV+1);
    for (int i = 1; i<=NV; i++) {
        if (aldagai_positibo[i] == 0 || aldagai_negatibo[i] == 0) {
            aldagai_aktiboak[i] = false;
            for (int j = 0; j<NC; j++) {
                if (Formula[j].first[i] != 0) Formula[j].second = 0;
            }
            if (aldagai_positibo[i] > aldagai_negatibo[i]) SP[i] = true;
        } else aldagai_aktiboak[i] = true;
    }

    DK = 0;
    bool emaitza = SATBT_geldoa(SP, 1);

    /*
    std::cout << "BT adarkatze kopurua: " << DK << std::endl;

    
     *  MARGOTU EMAITZA
    

    for (int j = 1; j<=NV; j++) {
        std::cout << SP[j] << " ";
    }
    std::cout << std::endl;
    */

    dei_kop = DK;

    return emaitza;

}