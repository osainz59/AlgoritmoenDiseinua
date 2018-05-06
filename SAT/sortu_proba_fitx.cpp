#include <iostream>
#include <fstream>
#include <random>


int main(int argc, char **argv) {
    /*
     * Erabilpena: ./sortu_proba_fitx <output>.txt NC NV D 
     *              <output>.txt : Non gordeko den sortutako proba.
     *              NC           : Klausula kopurua
     *              NV           : Aldagai kopurua
     *              D            : Dentsitatea, hau da, klausula bakoitza izan dezakeen
                                   aldagai kopurua.
     */

    if (argc != 5) {
        std::cerr << "./sortu_proba_fitx <output>.txt NC NV D \n";
        return 1;
    }

    std::ofstream emaitza(argv[1]);
    int NC = atoi(argv[2]);
    int NV = atoi(argv[3]);
    int D = atoi(argv[4]);

    emaitza << "c Automatikoki sortutako proba kasua\n";
    emaitza << "c Egilea: Oscar Sainz\n";
    emaitza << "c NC:\t" << NC << std::endl;
    emaitza << "c NV:\t" << NV << std::endl;
    emaitza << "c D:\t" << D << std::endl;
    emaitza << "p cnf " << NV << " " << NC << std::endl;

    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> distD(1,D); // distribution in range [1, D]
    std::uniform_int_distribution<std::mt19937::result_type> distNV(1,NV); // distribution in range [1, NV]
    std::uniform_int_distribution<std::mt19937::result_type> distPoN(0,100); // distribution in range [0, 1]

    // Idatzi hurrengo NC klausulak:
    for (int C = 0; C<NC; C++) {
        int aldagai_kopurua = distD(rng);
        for (int V = 0; V<aldagai_kopurua; V++) {
            int aldagaia = distNV(rng);
            if (distPoN(rng)%2==0) emaitza << aldagaia << " ";
            else emaitza << -1*aldagaia << " ";
        }
        // Klausula bukaera
        emaitza << "0\n";
    }
    return 0;
}