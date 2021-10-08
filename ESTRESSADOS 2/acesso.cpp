#include<iostream>
#include<vector>
#include <algorithm>
#include <ctime>

std::vector<int> inverter_com_copia(const std::vector<int>& v){
    std::vector<int> a(v);
    std::reverse(a.begin(), a.end());

    return a;
}

void inverter_inplace(std::vector<int>& v){
    std::reverse(v.begin(), v.end());
}


int sortear(const std::vector<int>& v){
    int num{};
    unsigned seed = time(0);

    srand(seed);
    num = v[ rand()%(int)v.size() ];

    return num; 
}


void embaralhar(std::vector<int>& v){
	for (size_t i = 0; i < v.size() ; i++)
	{
		int r = rand() % (int) v.size();

		int temp = v[i];
		v[i] = v[r];
		v[r] = temp;
	}
}


void ordenar(std::vector<int>& v){
    int next{};
    int aux{};

    for(int prev=0 ; prev<(int) v.size()-1 ; prev++)
        for(next=prev+1 ; next<v.size() ; next++){
            aux=v[prev];

            if(v[next]<v[prev]){
                v[prev]=v[next];
                v[next] = aux;
            }
        }
}



int main(){
    std::vector<int> vetor{90, -90, 80, -80, -8, 10};
    std::cout << "=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" <<"\n";
    std::cout<< "Vetor inverso: ";
    auto a = inverter_com_copia(vetor);
    for (size_t i = 0; i <a.size(); ++i) {
        std::cout << a.at(i) << " ";
    }

    inverter_inplace(vetor);
    std::cout <<"\nInvertido inplace: ";
    for (size_t i = 0; i <vetor.size(); ++i) {
        std::cout << vetor.at(i) << " ";
    }

    std::cout << "\nSorteado: " << sortear(vetor);
    embaralhar(vetor);
    std::cout <<"\nEmbaralhado: " ;
    for (size_t i = 0; i <vetor.size(); ++i) {
        std::cout << vetor.at(i) << " ";
    }    embaralhar(vetor);

    ordenar(vetor);
    std::cout <<"\nOrdenado: " ;
    for (size_t i = 0; i <vetor.size(); ++i) {
        std::cout << vetor.at(i) << " ";
    }
    std::cout << "\n=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" <<"\n";

    return 0;
}