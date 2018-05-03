#include "BT.hpp"
#include <vector>
#include <utility>

std::vector<std::pair<std::vector<int>, int> >  Formula;
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
            klausula = KlausulaZerrenda.pop();

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