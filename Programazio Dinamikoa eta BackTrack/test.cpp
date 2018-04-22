
#include "PD.hpp"
#include "BT.hpp"
#include <vector>
#include <iostream>
#include <random>
#include <chrono>
#include <fstream>
#include <ostream>
#include <utility>
#include <string>

std::pair<int, int> lortu_datuak(std::vector<int> &T, std::vector<int> &On, std::vector<int> &Os, std::string PATH) {
	try {

		std::ifstream sarrera;
		std::string lag;	
		int N = 0, M = 0;

		sarrera.open(PATH);
		if (sarrera.is_open()) {
			std::getline(sarrera, lag);
        	N = std::stoi(lag);
			T.resize(N+1); On.resize(N+1); Os.resize(N+1);
			for(int i = 1; i<=N; i++) {
				sarrera >> T[i] >> On[i] >> Os[i];
			}

			sarrera >> M;  

			T[0] = M; On[0] = 0; Os[0] = 0;

			sarrera.close();

			return std::pair<int, int>(N,M);
		} else {
			std::cerr << "Fitxategia ez da existitzen.\n";
			return std::pair<int, int>(0, 0);
		}

	} catch (int e) {
		std::cerr << "Errorea fitxategiak irekitzean.\n";
		return std::pair<int, int>(0, 0);
	}
}

void idatzi_emaitza(std::vector<int> &emaitza_bektorea, std::vector<int> &On, int N, int emaitza, std::ostream& cout) {
	
	cout << "## Emaitza:\n";

	cout << emaitza << std::endl;

	for (int i = 1; i<=N; i++) {
		cout << emaitza_bektorea[i]*On[i] << " " << emaitza_bektorea[i] << std::endl;
	}

}

int test(int N, int M, std::vector<int> &T, std::vector<int> &On, std::vector<int> &Os, std::vector<int> &emaitza, std::ostream& cout) {
	// Hasieraketak
	int emaitzaPD, emaitzaBT01, emaitzaBT1N;
	std::vector<int> v1(N+1), v2(N+1), v3(N+1);
	std::chrono::steady_clock::time_point begin, end;


	// Programazio Dinamikoko testa:
	begin = std::chrono::steady_clock::now();
	emaitzaPD = SPD(v1, N, M, T, On, Os);
	end = std::chrono::steady_clock::now();

	cout << "Programazio Dinamikoko Testa\n";
	cout << "Emaitza: " << emaitzaPD << std::endl;
	cout << "Denbora: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " μs\n";

	// BackTrack 01-eko testa:
	begin = std::chrono::steady_clock::now();
	emaitzaBT01 = SBT01(v2, N, M, T, On, Os);
	end = std::chrono::steady_clock::now();

	cout << "BackTrack 01-eko testa\n";
	cout << "Emaitza: " << emaitzaBT01 << std::endl;
	cout << "Denbora: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " μs\n";

	// BackTrack 1N-ko testa:
	begin = std::chrono::steady_clock::now();
	emaitzaBT1N = SBT1N(v3, N, M, T, On, Os);
	end = std::chrono::steady_clock::now();

	cout << "BackTrack 1N-ko testa\n";
	cout << "Emaitza: " << emaitzaBT1N << std::endl;
	cout << "Denbora: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " μs\n";

	emaitza.swap(v1);

	return emaitzaPD;

}

int main(int argc, char ** argv){

	if (argc < 2 || argc > 3) {
		std::cerr << "Argumentu kopuru desegokia, erabilera: ./<programaren izena> sarrera.txt [irteera.txt]\n";
		exit(1);
	}

	int emaitza_balioa;
	std::vector<int> T, On, Os, emaitza_bektorea;
	std::pair<int, int> N_M = lortu_datuak(T, On, Os, argv[1]);

	if (argc == 3) {
		std::ofstream emaitza(argv[2]);	
		emaitza_balioa = test(N_M.first, N_M.second, T, On, Os, emaitza_bektorea, emaitza);
		idatzi_emaitza(emaitza_bektorea, On, N_M.first, emaitza_balioa, emaitza);
		emaitza.close();
	} else {
		emaitza_balioa = test(N_M.first, N_M.second, T, On, Os, emaitza_bektorea, std::cout);
		idatzi_emaitza(emaitza_bektorea, On, N_M.first, emaitza_balioa, std::cout);
	}

	return 0;
}