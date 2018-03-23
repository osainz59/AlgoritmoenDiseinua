#ifndef LehentasunIlara_hpp
#define LehentasunIlara_hpp

#include <vector>

class LehentasunIlara {

public:

	LehentasunIlara();
	LehentasunIlara(std::vector<std::pair<float, int> > v, int N);

	void pop();
	std::pair<float, int> &top();
	void push(std::pair<float, int> p);

	bool empty();

	std::pair<float, int>& operator[](int index);
	const std::pair<float, int>& operator[](int index) const;

	bool exist(int index);

	void update(std::pair<float, int> p);

	void print();


private:
	std::vector<std::pair<float, int> > v;
	std::vector<int> posizioa;
	int N;
	int erpinHandiena;

	void meta_eraiki();
	void hondoratu(int i);
	void azaleratu(int i);

};

#endif /* LehentasunIlara_hpp */