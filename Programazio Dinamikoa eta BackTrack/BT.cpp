#include "BT.hpp"

#include <iostream>
#include <algorithm>
#include <utility>
#include <cmath>


float min(float a, float b) {
	return (a < b) ? a : b;
} 


void SBT1NProz(std::vector<int> &spb,		// Soluzio partzialaren bektorea
			   int sp, 						// Soluzio partzialaren balioa
			   int N, 						// Soluzio partzialaren iN azpizuahitza adierazten duen I
			   int I,						// Produktu kopurua
			   int m,						// Soluzio partzialean gelditzen den minutu kopurua
			   std::vector<int> &Os,		// Soluzio partzialaren produktuetako sor daitezkeen ale kopurua
			   std::vector<int> &T,			// Produktuen kostua
			   std::vector<int> &On, 		// Produktuen onura (irabazia)
			   std::vector<int> &soptb, 	// Soluzio optimoaren bektorea
			   int &sopt, 					// Soluzio optimoaren balioa
			   std::vector<int> &gehienez)	// Gehienez lor dezakeen onura 				
{	

	if ( m == 0) {	// Soluzioa da eta uneko optimoa baino hobea
		if (sp > sopt) {
			for (int i = 1; i<=N; i++) {
				soptb[i] = spb[i];
			}
			sopt = sp;
		}	
	} else
	for (int i = I; i<=N; i++) {	// 1. KIMAKETA <-- Soluzio berdinak behin eta berriz ez kalkulatzeko.
		// 2. KIMAKETA <-- Gehienez lor dezakeena soluzio partziala hobetzen ez badu ebaki.
		if ( gehienez[i] - (spb[i]*On[i]) < sopt - sp) continue;	
		if ( spb[i] < Os[i] && T[i] <= m) {	// Ez da soluzioa, beraz segi bilatzen.

			spb[i]++;
			SBT1NProz(spb, sp + On[i], N, i, m - T[i], Os, T, On, soptb, sopt, gehienez);
			spb[i]--;

		} else if ( sp > sopt ) {	// Soluzioa da eta uneko optimoa baino hobea
			for (int i = 1; i<=N; i++) {
				soptb[i] = spb[i];
			}
			sopt = sp;
		}
	}
}


int SBT1N(std::vector<int> &emaitza, int N, int M, std::vector<int> &T, std::vector<int> &On, std::vector<int> &Os){

	if (N == 0 || M == 0) return 0;

	// Hasieratu emaitza 0-ra
	std::vector<int> spb(N+1, 0);
	int emaitza_balioa = 0;

	// 3. KIMAKETA Ordenatu onura-proportzioaren arabera, horrela 2. Kimaketa eraginkorragoa
	// izango da. T[i] inoiz ez da 0 izango bestela onura infinitu
	std::vector<std::pair<float, int> > onura_zati_denbora(N+1, std::pair<float, int>(0,0));
	for (int i = 1; i<=N; i++) {
		float f = float(On[i]) / float(T[i]);
		onura_zati_denbora[i] = std::pair<float, int>(f, i);
	}

	std::sort(onura_zati_denbora.begin(), onura_zati_denbora.end(), [](std::pair<float, int> a, std::pair<float, int> b){
        return a.first > b.first;                           // sort() funtzioa MergeSort algoritmoa aplikatzen du C++11-tik aurrera
    });

    std::vector<int> T_berria(N+1), On_berria(N+1), Os_berria(N+1), indizeak(N+1), gehienez(N+1), emaitza_berria(N+1,0);

    for (int i = 0; i<N; i++) {
    	indizeak[i+1] = onura_zati_denbora[i].second;
    	T_berria[i+1] = T[onura_zati_denbora[i].second];
    	On_berria[i+1] = On[onura_zati_denbora[i].second];
    	Os_berria[i+1] = Os[onura_zati_denbora[i].second];
    }
    ////


	//std::vector<int> gehienez(N+1);
	gehienez[N] = On_berria[N]*Os_berria[N];
	for (int i = N-1; i>0; i--){
		gehienez[i] = gehienez[i+1] + On_berria[i]*Os_berria[i];
	}

	SBT1NProz(spb, 0, N, 1, M, Os_berria, T_berria, On_berria, emaitza_berria, emaitza_balioa, gehienez);

	for (int i = 1; i<=N; i++) {
    	emaitza[indizeak[i]] = emaitza_berria[i];
    }

	return emaitza_balioa;

}

void SBT01Proz(std::vector<int> &spb,		// Soluzio partzialaren bektorea
			   int sp, 						// Soluzio partzialaren balioa
			   int N, 						// Produktu kopurua
			   int I,						// Soluzio partzialaren iN azpizuahitza adierazten duen I
			   int m,						// Soluzio partzialean gelditzen den minutu kopurua
			   std::vector<int> &Os,		// Soluzio partzialaren produktuetako sor daitezkeen ale kopurua
			   std::vector<int> &T,			// Produktuen kostua
			   std::vector<int> &On, 		// Produktuen onura (irabazia)
			   std::vector<int> &soptb, 	// Soluzio optimoaren bektorea
			   int &sopt, 					// Soluzio optimoaren balioa
			   std::vector<int> &gehienez)	// Gehienez lor dezakeen onura 				
{

	if ( I > N || m == 0 ) {			// Soluzioa da || m == 0 1. KIMAKETA
		if (sp > sopt) {				// Optimoa baino hobeagoa denez eguneratu
			for (int i = 1; i<=N; i++) {
				soptb[i] = spb[i];
			}
			sopt = sp;
		}
	} 
	else if (sp + gehienez[I] <= sopt) return;	// 2. KIMAKETA sp ezin du uneko sopt hobetu
	else {								// Soluzioa ez bada eta emaitza hobetu badezake hurrengoak begiratu
		int kop_max = std::floor(min(Os[I], m / T[I]));
		//std::cout << I << " " << Os[I] << "/" << m / T[I] << "=" << kop_max << std::endl;
		for (int i = kop_max; i >= 0; i--) {	// 3. KIMAKETA 

			spb[I] = i;
			SBT01Proz(spb, sp+(i*On[I]), N, I+1, m-(i*T[I]), Os, T, On, soptb, sopt, gehienez);

		}
	}

}

int SBT01(std::vector<int> &emaitza, int N, int M, std::vector<int> &T, std::vector<int> &On, std::vector<int> &Os){

	if (N == 0 || M == 0) return 0;

	int emaitza_balioa = 0;
	std::vector<int> spb(N+1, 0);

	// 3. KIMAKETA Ordenatu onura-proportzioaren arabera, horrela 2. Kimaketa eraginkorragoa
	// izango da. T[i] inoiz ez da 0 izango bestela onura infinitu
	std::vector<std::pair<float, int> > onura_zati_denbora(N+1, std::pair<float, int>(0,0));
	for (int i = 1; i<=N; i++) {
		float f = float(On[i]) / float(T[i]);
		onura_zati_denbora[i] = std::pair<float, int>(f, i);
	}

	std::sort(onura_zati_denbora.begin(), onura_zati_denbora.end(), [](std::pair<float, int> a, std::pair<float, int> b){
        return a.first > b.first;                           // sort() funtzioa MergeSort algoritmoa aplikatzen du C++11-tik aurrera
    });

    std::vector<int> T_berria(N+1), On_berria(N+1), Os_berria(N+1), indizeak(N+1), gehienez(N+1), emaitza_berria(N+1,0);

    for (int i = 0; i<N; i++) {
    	indizeak[i+1] = onura_zati_denbora[i].second;
    	T_berria[i+1] = T[onura_zati_denbora[i].second];
    	On_berria[i+1] = On[onura_zati_denbora[i].second];
    	Os_berria[i+1] = Os[onura_zati_denbora[i].second];
    }
    ////

    gehienez[N] = On_berria[N]*Os_berria[N];
	for (int i = N-1; i>0; i--){
		gehienez[i] = gehienez[i+1] + On_berria[i]*Os_berria[i];
	}

    SBT01Proz(spb, 0, N, 1, M, Os_berria, T_berria, On_berria, emaitza_berria, emaitza_balioa, gehienez);

    for (int i = 1; i<=N; i++) {
    	emaitza[indizeak[i]] = emaitza_berria[i];
    }

	return emaitza_balioa;

}








