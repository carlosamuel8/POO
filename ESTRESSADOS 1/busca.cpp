
#include<iostream>
#include<vector>

using namespace std;

string existe(std::vector<int> vetor, int x ){
    for (int i = 0; i < (int)(vetor.size()); i++){
        if(vetor[i] == x)
            return "sim";
    }
    return "não";
}

int contar(std::vector<int> vetor, int x){
    int cont = 0;
    for (int i = 0; i < (int)(vetor.size()); i++){
        if(vetor[i] == x)
            cont++;
    }
    return cont;
}

string procurar_valor(std::vector<int> vetor, int x){
    for (int i = 0; i < (int)vetor.size(); i++){
        if(vetor[i] == x)
            return std::to_string(i);
    }
    return "não existe no vetor";
}


string procurar_valor_apos(std::vector<int> vetor, int x, int pos){
    int cont = 0;
    
    if(pos>(int)(vetor.size()))
        return "posição excede o tamanho do vetor";

    for (int i = pos+1; i < (int)(vetor.size()); i++){
        if(vetor[i] == x)
            return std::to_string(i);
    }
    return "não aparece mais";
}


int main(){ 
    std::vector<int> meuVetor {5, 6, 5, 6, 8, 9};
    int x=6;
    int posicao=2;


    cout << "=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" <<"\n";
    cout << "Existe no Vetor:  " << existe(meuVetor, x) << "\n";
    cout << "Quantidade de vezes em que X aparece no vetor: " << contar(meuVetor, x) << "\n";
    cout << "Posição em que X aparece pela primeira vez:  " << procurar_valor(meuVetor, x) << "\n";
    cout << "Próxima posicao em que X aparece após a posição " << posicao << ": " << procurar_valor_apos(meuVetor, x, posicao) << "\n";
    cout << "=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" <<"\n";
}



