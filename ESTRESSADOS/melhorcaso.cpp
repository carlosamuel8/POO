
#include<iostream>
#include<vector>

using namespace std;

int procurar_menor(std::vector<int> vetor){
    int menor = vetor[0];
    for (int i = 0; i < (int)vetor.size(); i++){
        if(vetor[i] <= menor)
            menor = vetor[i];       
    }
    return menor;
}

int procurar_maior(std::vector<int> vetor){
    int maior = vetor[0];
    for (int i = 0; i < (int)vetor.size(); i++){
        if(vetor[i] >= maior)
            maior = vetor[i];       
    }
    return maior;
}

int procurar_menor_pos(std::vector<int> vetor){
    int menor = vetor[0];
    int posic = NULL;
    for (int i = 0; i < (int)vetor.size(); i++){
        if(vetor[i] <= menor){
            menor = vetor[i];   
            posic = i;
        }    
    }
    return posic;
}


int procurar_menor_pos_apos(std::vector<int> vetor, int p){
    int menor = vetor[0];
    int posic = 0;
    for (int i = p+1; i < (int)vetor.size(); i++){
        if(vetor[i] <= menor){
            menor = vetor[i];   
            posic = i;
        }    
    }
    return posic;
}

int procurar_melhor_se(std::vector<int> vetor){
    int menor = vetor[0];
    int posic = 0;

    for (int i = 0; i < (int)vetor.size(); i++){
        if(vetor[i]>0){
            if(vetor[i] > 0){
                if(vetor[i] <menor)   
                    posic = i;
            }   
        }
    }
    return posic;
}


int main(){ 
    std::vector<int> meuVetor {5, 90, -90, -80, -85, 1};
    int posicao=2;

    cout << "=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" <<"\n";
    cout << "Menor valor: " << procurar_menor(meuVetor) << "\n";
    cout << "Maior valor: " << procurar_maior(meuVetor) << "\n";
    cout << "Posicao do menor valor: " << procurar_menor_pos(meuVetor) << "\n";
    cout << "Posicao do menor valor apos a posicao "<< posicao <<": "  << procurar_menor_pos_apos(meuVetor, posicao) << "\n";
    cout << "Posicao do homem mais calmo: " << procurar_melhor_se(meuVetor) << "\n";
    cout << "=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" <<"\n";

    return 0;
}  




