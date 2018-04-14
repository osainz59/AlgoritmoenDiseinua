
#include "PD.hpp"
#include "BT.hpp"
#include <vector>
#include <iostream>
#include <random>

int main(){

	int MAX = 10, MIN = 1;
	int N = 10, M = 1440;
	std::vector<int> v1(N+1), v2(N+1), v3(N+1), T(N+1), On(N+1), Os(N+1);
	for (int i = 0; i<=N; i++) {
		T[i] = MIN + (rand() % static_cast<int>(MAX - MIN + 1));
		On[i] = MIN + (rand() % static_cast<int>(MAX - MIN + 1));
		Os[i] = MIN + (rand() % static_cast<int>(MAX - MIN + 1));
	}
	std::cout << SPD(v1, N, M, T, On, Os) << std::endl;
	std::cout << "[ ";
	for (int i = 1; i<=N; i++) {
		std::cout << v1[i] << " ";
	}
	std::cout << "]\n";
	std::cout << SBT1N(v2, N, M, T, On, Os) << std::endl;
	std::cout << "[ ";
	for (int i = 1; i<=N; i++) {
		std::cout << v2[i] << " ";
	}
	std::cout << "]\n";

	std::cout << SBT01(v3, N, M, T, On, Os) << std::endl;
	std::cout << "[ ";
	for (int i = 1; i<=N; i++) {
		std::cout << v3[i] << " ";
	}
	std::cout << "]\n";

	return 0;
}