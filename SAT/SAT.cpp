#include "BT.hpp"
#include <vector>
#include <utility>
#include <queue>

std::vector<std::pair<std::vector<int>, int> >  Formula;
int NV;
int NC;
'''
                   A   B   C   D   E   F   G
(A v ¬B)        [  1, -1,  0,  0,  0,  0,  0 ] | B (1)
(C v ¬A v D)    [ -1,  0,  1,  1,  0,  0,  0 ] | D (3)
(E)             [  0,  0,  0,  0,  1,  0,  0 ] | E (4)
(¬F v G)        [  0,  0,  0,  0,  0, -1,  1 ] | G (6)

Izanda matrize bat NCxNV, non NV datuetan ager litezkeen proposamen aldagaien kopurua
eta NC datuetan agertzen diren klausulen kopurua den.

Algoritmoa:

proz SATBT ( SP : inout Vector; I : in Integer; KlausulaZerrenda : in Queue ) is
    zerrenda_false, zerrenda_true : Queue;
    klausula = Integer;
begin
    if KlausulaZerrenda.isEmpty() then
        return True;
    else if not KlausulaZerrenda.isEmpty() and I > NV then
        return False;
    else
        zerrenda_false, zerrenda_true = hasieratu_zerrenda();
        while not KlausulaZerrenda.isEmpty() loop
            klausula = KlausulaZerrenda.top();
            KlausulaZerrenda.pop();

            if Formula[klausula].handiena < I then
                return False;
            end if;

            if Formula[klausula].bektorea[I] != 1 then
                zerrenda_true.push(klausula);
            end if;
            if Formula[klausula].bektorea[I] != -1 then
                zerrenda_false.push(klausula);
            end if;
        end loop;
        SP[I] = False; 
        if SATBT(SP, I+1, zerrenda_false) then return True;
        SP[I] = True;  
        if SATBT(SP, I+1, zerrenda_true) then return True;

        return False;
end SATBT
'''


bool SATBT(std::vector<bool> &SP, int I, std::queue<int> &KlausulaZerrenda){

    // Klausula guztiak TRUE dira beraz Formula TRUE da.
    if (KlausulaZerrenda.isEmpty()) return true;    
    // Bukaerara iritsi gara eta ez da soluziorik aurkitu
    else if (I > NV) return false;      
    // Ebaluatu gelditzen diren klausulak I. literalarekin.            
    else
    {                                               
        std::queue<int> false_zerrenda, true_zerrenda;
        int klausula;
        while (!KlausulaZerrenda.isEmpty())
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

        SP[I] = false;
        if SATBT(SP, I+1, zerrenda_false) return true;
        SP[I] = true;
        if SATBT(SP, I+1, zerrenda_true) return true;
    }

    // Azpizuhaitza aztertu ondoren ez da aurkitu soluziorik.
    return false;

}

bool SAT(std::string &sarrera_fitxategia) {
    
}