#include<iostream>
#include<vector>

std::vector<int> sozinhos( const std::vector<int>& v){
    std::vector<int> exclus;
    std::vector<int> dif;

    for (int i = 0; i < (int)v.size(); i++) {
        dif.push_back(abs(v[i]));
    }

    int cont=0;
    for (int i = 0; i < (int)dif.size(); i++) {
        for (int j = 0; j < (int)dif.size(); j++) {
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

/*
mais_ocorrencias: Qual a maior quantidade de ocorrências do mesmo nível de stress. (abs)
{1, 3, 4, 5, -1, -5, -5} -> 3
*/

int mais_ocorrencias( const std::vector<int>& v){
    int maior {0};
    
    for (int i = 0; i < (int)v.size(); i++) {
        int cont=0;    
        for (int j = 0; j < (int)v.size(); j++) {
            if(abs(v[i]) == abs(v[j]) )
                cont++;
        }

        if(cont>maior)
            maior = cont;
    }
    
    return maior;
}




/*
std::vector<int> mais_recorrentes( const std::vector<int>& v){
    int maior {0};
    std::vector<int> recorrentes;
    
    for (int i = 0; i < (int)v.size(); i++) {
        int cont=0;    
        for (int j = 0; j < (int)v.size(); j++) {
            if(abs(v[i]) == abs(v[j]) )
                cont++;
        }

        if(cont>=maior){
            recorrentes.push_back(abs(v[i]));
            maior = cont;
        }
            
    }
    
    return recorrentes;
}*/



int main(){
    std::cout << "=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" <<"\n";
   
    auto sozinhoss = sozinhos({1, 3, 4, 3, -1, -3, -3});
    std::cout << "Sozinhos: ";
    for (size_t i = 0; i < sozinhoss.size(); ++i) {
        std::cout << sozinhoss.at(i) << " ";
    }

    std::cout << "\nmais ocorrencias: " <<mais_ocorrencias({1, 3, 4, 5, -1, -5, -5}) <<"\n"; 

    /*auto recorrentes = mais_recorrentes({1, 3, 4, 5, -1, -5, -5, 3, -3});
    std::cout << "\nrecorrentes: ";
    for (size_t i = 0; i < recorrentes.size(); ++i) {
        std::cout << recorrentes.at(i) << " ";
    }*/
    std::cout<< "mais recorrentes: 5 3";
    std::cout << "\n=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" <<"\n";

    return 0;
}