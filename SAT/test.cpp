#include <iostream>
#include <string>
#include "SAT.hpp"
#include <fstream>



int main(int argc, char **argv){

    if (argc > 2) {
        std::cerr << "Errorea: \'./test sarrera.txt\' espero zen.\n";
        return 1;
    }

    long DK;

    if (argc == 2) {
        std::string PATH(argv[1]);
        std::cout << "SAT azkarra:\n";
        std::cout << "Emaitza: " << SAT(PATH, DK) << std::endl;
        std::cout << "SAT geldoa:\n";
        std::cout << "Emaitza: " << SAT_geldoa(PATH, DK) << std::endl;

        return 0;
    }
    
    std::string PATH;

    const int N = 4, M = 10;
    long emaitza_faltsu_okerrena_azkarra, emaitza_faltsu_okerrena_geldoa, emaitza_egiazko_okerrena_azkarra, emaitza_egiazko_okerrena_geldoa, lag;

    long emaitza_egiazkoakA[N][M];
    long emaitza_faltsuakA[N][M]; 
    long emaitza_egiazkoakG[N][M];
    long emaitza_faltsuakG[N][M]; 

    int NV[N] = { 5, 10, 15, 20 };
    int NC[M] = { 5, 10, 15, 20, 25, 30, 35, 40, 45, 50 };

    for (int i = 0; i<N; i++) {
        std::cout << "NV = " << NV[i] << std::endl;
        for (int j = 0; j<M; j++) {
            std::cout << "NC = " << NC[j] << std::endl;
            emaitza_faltsu_okerrena_azkarra = 0; emaitza_egiazko_okerrena_azkarra = 0;
            emaitza_faltsu_okerrena_geldoa = 0; emaitza_egiazko_okerrena_geldoa = 0;
            for (int v = 1; v <= NV[i]; v++) {
                for (int z = 1; z <= 5; z++) {

                    PATH = "sarrerak/";
                    PATH += std::to_string(NC[j]);
                    PATH += "-";
                    PATH += std::to_string(NV[i]);
                    PATH += "-";
                    PATH += std::to_string(v);
                    PATH += "-";
                    PATH += std::to_string(z);
                    PATH += ".txt";

                    //std::cout << PATH << std::endl;

                    if (SAT(PATH, lag)) 
                        if (emaitza_egiazko_okerrena_azkarra < lag) emaitza_egiazko_okerrena_azkarra = lag;
                    else
                        if (emaitza_faltsu_okerrena_azkarra < lag) emaitza_faltsu_okerrena_azkarra = lag;

                    if (SAT_geldoa(PATH, lag)) 
                        if (emaitza_egiazko_okerrena_geldoa < lag) emaitza_egiazko_okerrena_geldoa = lag;
                    else
                        if (emaitza_faltsu_okerrena_geldoa < lag) emaitza_faltsu_okerrena_geldoa = lag;
                }
            }
            emaitza_egiazkoakA[i][j] = emaitza_egiazko_okerrena_azkarra;
            emaitza_faltsuakA[i][j] = emaitza_faltsu_okerrena_azkarra;
            emaitza_egiazkoakG[i][j] = emaitza_egiazko_okerrena_geldoa;
            emaitza_faltsuakG[i][j] = emaitza_faltsu_okerrena_geldoa;
        }
    }


    std::ofstream emaitza_egiazko_azkarra("emaitzak/egiazko_azkarra.csv");
    std::ofstream emaitza_faltsua_azkarra("emaitzak/faltsua_azkarra.csv");	
    std::ofstream emaitza_egiazko_geldoa("emaitzak/egiazko_geldoa.csv");	
    std::ofstream emaitza_faltsua_geldoa("emaitzak/faltsua_geldoa.csv");	

    std::cout << "Emaitzak idazten...\n";	

    std::string goiburukoa = "";

    for (int j = 0; j<M; j++) {
        goiburukoa += "," + std::to_string(NC[j]);
    }

    goiburukoa += "\n";

    emaitza_egiazko_azkarra << goiburukoa;
    emaitza_faltsua_azkarra << goiburukoa;
    emaitza_egiazko_geldoa << goiburukoa;
    emaitza_faltsua_geldoa << goiburukoa;

    for (int i = 0; i<N; i++) {
        emaitza_egiazko_azkarra << NV[i];
        emaitza_faltsua_azkarra << NV[i];
        emaitza_egiazko_geldoa << NV[i];
        emaitza_faltsua_geldoa << NV[i];
        for (int j = 0; j<M; j++) {
            emaitza_egiazko_azkarra << "," << emaitza_egiazkoakA[i][j];
            emaitza_faltsua_azkarra << "," << emaitza_faltsuakA[i][j];
            emaitza_egiazko_geldoa << "," << emaitza_egiazkoakG[i][j];
            emaitza_faltsua_geldoa << "," << emaitza_faltsuakG[i][j];
        }
        emaitza_egiazko_azkarra << std::endl;
        emaitza_faltsua_azkarra << std::endl;
        emaitza_egiazko_geldoa << std::endl;
        emaitza_faltsua_geldoa << std::endl;
    }

    emaitza_egiazko_azkarra.close();
    emaitza_faltsua_azkarra.close();	
    emaitza_egiazko_geldoa.close();	
    emaitza_faltsua_geldoa.close();
    
}