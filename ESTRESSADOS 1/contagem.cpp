/*calcular_stress_medio: qual a média de stress da fila? (abs)
mais_homens_ou_mulheres: Na fila existem mais homens ou mulheres?
qual_metade_eh_mais_estressada: O nível de stress somado de todas as pessoas da primeira metade é maior que o nível de stress somado das pessoas da segunda metade da fila? (abs)
homens_sao_mais_estressados_que_mulheres: a média do stress dos homens é maior que a das mulheres?*/


#include<iostream>
#include<vector>

using namespace std;

float media_vetor(std::vector<int> vetor){
    int soma = 0;
    float media = 0;

    for (int i = 0; i < (int)vetor.size(); i++){
        soma+=vetor[i];
    }
    media = (float) soma/(int)vetor.size();

    return media;
}


float calcular_stress_medio(std::vector<int> vetor){

    int somaestresse=0;
    for (int i = 0; i < (int)vetor.size(); i++){
        somaestresse += abs(vetor[i]);
    }

    float estressemedio = (float) somaestresse/(int)vetor.size();

    return estressemedio;
}


string mais_homens_ou_mulheres(std::vector<int> vetor){
    int men = 0;
    int woman = 0;

    for (int i = 0; i < (int)vetor.size(); i++){
        if(vetor[i] < 0)
            woman ++;
        else if(vetor[i] > 0)
            men ++;  
    }

    if(woman>men)
        return "mulheres";
    else if(woman<men)   
        return "homens";
    else
        return "mesma quantidade";
}


string qual_metade_eh_mais_estressada(std::vector<int> vetor){
    if ( (int)vetor.size()%2 != 0)
        return "vetor inválido, entre com um vetor de tamanho par";

    int metade = ((int)(vetor.size()))/2;
    int primeira=0; 
    int segunda=0;

    for (int i = 0; i < metade ; i++){
        primeira+=abs(vetor[i]);
    }

    for (int i = metade; i < (int)vetor.size() ; i++){
        segunda+= abs(vetor[i]);
    }


    if(primeira > segunda)
        return "primeira";
    else if(segunda > primeira)   
        return "segunda";
    else
        return "empate";

}


string homens_sao_mais_estressados_que_mulheres(std::vector<int> vetor){
    std::vector<int> estressWoman;
    std::vector<int> estressMen;

    for (int i = 0; i < (int)vetor.size(); i++){
        if(vetor[i] < 0)
            estressWoman.push_back(abs(vetor[i]));
        else if(vetor[i] > 0)
            estressMen.push_back(vetor[i]);
    }

    float mediamen = media_vetor(estressMen);
    float mediawoman = media_vetor(estressWoman);

    if(mediamen > mediawoman)
        return "sim";
    else    
        return "não"; 
}

int main(){ 
    std::vector<int> meuVetor {90, -90, 80, -80, -98, 52};

    cout << "=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" << "\n";
    cout << "Qual a média de stress da fila?: " <<  calcular_stress_medio(meuVetor) << "\n";
    cout << "Na fila existem mais homens ou mulheres?: " << mais_homens_ou_mulheres(meuVetor) << "\n";
    cout << "qual metade é mais estressada?: " << qual_metade_eh_mais_estressada(meuVetor)<< "\n";
    cout << "A média do stress dos homens é maior que a das mulheres?: " << homens_sao_mais_estressados_que_mulheres(meuVetor) << "\n";
    cout << "=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" <<"\n";   


    return 0;
}  