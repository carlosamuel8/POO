#include<iostream>
#include<vector>
#include <algorithm> 

std::vector<int> exclusivos( const std::vector<int>& v){
  std::vector<int> exclus;
  
    int cont=0;
    for (int i = 0; i < (int)v.size(); i++) {
        for (int j = 0; j < (int)v.size(); j++) {
            if (i!=j ) {
                if(v[i] == v[j] )
                    cont++;
            }
        }
        if(cont == 0)
            exclus.push_back(v[i]);

        cont = 0;
    }
    
    return exclus;
}


std::vector<int> diferentes( const std::vector<int>& v){
  std::vector<int> dif;
  std::vector<int> exclus;

    for (int i = 0; i < (int)v.size(); i++) {
        dif.push_back(abs(v[i]));
    }

    
    int cont=0;
    for (int i = 0; i < (int)dif.size(); i++) {
        for (int j = i+1; j < (int) dif.size(); j++) {
            if (i!=j ) {
                if(dif[i] == dif[j] )
                    cont++;
            }
        }
        if(cont == 0)
            exclus.push_back(dif[i]);

        cont = 0;
    }

    return exclus;
}

std::vector<int> abandonados( const std::vector<int>& v){
  std::vector<int> dif;
  
    for (int i = 0; i < (int)v.size(); i++) {
        for (int j = i+1; j < (int)v.size(); j++) {
            if (i!=j ) {
                if(v[i] == v[j] )
                    dif.push_back(v[i]);
            }
        }
    }
    return dif;
}


int main(){

    std::vector<int> vetor{1, 3, 4, 3, -1, -2, -2, -60, 60};

    std::cout << "=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" <<"\n";
    std::cout<< "exclusivos: ";
    auto excl = exclusivos(vetor);
    for (size_t i = 0; i <excl.size(); ++i) {
        std::cout << excl.at(i) << " ";
    }

    std::cout<< "\ndiferentes: ";
    auto dif = diferentes(vetor);
    for (size_t i = 0; i <dif.size(); ++i) {
        std::cout << dif.at(i) << " ";
    }

    std::cout<< "\nabandonados: ";
    auto aband = abandonados(vetor);
    for (size_t i = 0; i <aband.size(); ++i) {
        std::cout << aband.at(i) << " ";
    }
    std::cout << "\n=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" <<"\n";
    return 0;
}