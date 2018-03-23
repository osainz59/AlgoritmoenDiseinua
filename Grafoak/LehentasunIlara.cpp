#include "LehentasunIlara.hpp"
#include <iostream>
#include <vector>

LehentasunIlara::LehentasunIlara(){
	this->N = 0;
	this->erpinHandiena = this->posizioa.size();
}

LehentasunIlara::LehentasunIlara(std::vector<std::pair<float, int> > v, int N){
	this->N = N;
	this->v = v;
	this->erpinHandiena = this->posizioa.size();
	this->meta_eraiki();
}

std::pair<float, int>& LehentasunIlara::operator[](int index){
	return this->v[this->posizioa[index]];		// Atzipen zuzena erpinera
}
const std::pair<float, int>& LehentasunIlara::operator[](int index) const{
	return this->v[this->posizioa[index]];		// Atzipen zuzena erpinera
}

bool LehentasunIlara::exist(int index){
	return index <= this->erpinHandiena;
}

void LehentasunIlara::meta_eraiki(){
	for (int i = 0; i<this->N; i++){
		this->posizioa[this->v[i].second] = i;
	}
	for (int i = this->N/2; i>0; i--){
        this->hondoratu(i);
    }
}

void LehentasunIlara::hondoratu(int i){
	std::pair<float, int> unekoa = this->v[i-1];
	int J = i;
	int umeMax;
	while(2*J <= this->N){
		umeMax = 2*J;
		if(umeMax < this->N)
			if (this->v[umeMax-1].first > this->v[umeMax].first) umeMax++;

		if(unekoa.first > this->v[umeMax-1].first){
			this->posizioa[this->v[umeMax-1].second] = J-1;		// Eguneratu posizioa
			this->v[J-1] = this->v[umeMax-1];
			J = umeMax;
		}else break;
	}
	this->posizioa[unekoa.second] = J-1;						// Eguneratu posizioa
	this->v[J-1] = unekoa;
}

void LehentasunIlara::azaleratu(int i){
	int J = i;
	std::pair<float, int> lag;
	while(J > 1){
		if(this->v[(J/2)-1].first > this->v[J-1].first) {
			// Posizioa eguneratu
			this->posizioa[this->v[(J/2)-1].second] = J-1;
			this->posizioa[this->v[J-1].second] = (J/2)-1;
			// Eguneratu
			lag = this->v[(J/2)-1];
			this->v[(J/2)-1] = this->v[J-1];
			this->v[J-1] = lag;

			J = J/2;

		} else break;
	}
}

std::pair<float, int> & LehentasunIlara::top(){
	return this->v[0];
}

void LehentasunIlara::pop(){ // O(lgN)
	this->posizioa[this->v[0].second] = -1;
	this->posizioa[this->v[N-1].second] = 0;
	this->v[0] = this->v[N-1];
	this->N--;
	this->v.pop_back();
	this->hondoratu(1); 
}

void LehentasunIlara::push(std::pair<float, int> p){ //O(lgN)
	if (p.second >= this->erpinHandiena){
		this->posizioa.resize(p.second+1);
		for(int i = this->erpinHandiena+1; i<p.second+1; i++){
			this->posizioa[i] = -1;
		}
		this->posizioa[p.second] = this->N;
	}
	this->N++;
	this->v.push_back(p);
	this->azaleratu(this->N);
}

bool LehentasunIlara::empty(){
	return this->N==0;
}

void LehentasunIlara::update(std::pair<float, int> p){
	if(!exist(p.second))
		push(p);
	else{
		if(this->v[this->posizioa[p.second]].first < p.first){
			this->v[this->posizioa[p.second]] = p;
			hondoratu(this->posizioa[p.second]+1);
		} else if(this->v[this->posizioa[p.second]].first > p.first){
			this->v[this->posizioa[p.second]] = p;
			azaleratu(this->posizioa[p.second]+1);
		}
	}
}

void LehentasunIlara::print(){
	std::cout << "[";
	for(int i = 0; i<this->N; i++){
//		std::cout << " (" << this->v[i].first << ", " << this->v[i].second << ")";
		std::cout << " " << this->v[i].first;
	}
	std::cout << " ]\n";
}




