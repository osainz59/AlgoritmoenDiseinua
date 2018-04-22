
#include "PD.hpp"


int SPD(std::vector<int> &emaitza, int N, int M, std::vector<int> &T, std::vector<int> &On, std::vector<int> &Os) {
	X OnuraM[N+1][M+1];
	// 1. Kasu nabaria
	for (int i = 0; i<=N; i++) {
		OnuraM[i][0].balioa = 0;
		OnuraM[i][0].z = 0;
	}
	// 2. Kasu nabaria
	for (int j = 0; j<=M; j++) {
		OnuraM[0][j].balioa = 0;
		OnuraM[0][j].z = 0;
	}
	// Kasu orokorra:
	for (int i = 1; i<=N; i++) {
		for (int j = 1; j<=M; j++) {
			//Ekuazioak
			int k = j / T[i];
			int max = 0, max_z = 0;
			if (k > Os[i]) k = Os[i];
			for (int z = 0; z<=k; z++) {
				if (max < OnuraM[i-1][j-(z*T[i])].balioa + z*On[i]) {
					max = OnuraM[i-1][j-(z*T[i])].balioa + z*On[i];
					max_z = z;
				}
			}
			OnuraM[i][j].balioa = max;
			OnuraM[i][j].z = max_z;

		}
	}
	// Errekuperazioa
	int j = M;
	for (int i = N; i>0; i--) {
		emaitza[i] = OnuraM[i][j].z;
		j -= emaitza[i]*T[i];
	}

	return OnuraM[N][M].balioa;
}