#include<iostream>
#include<vector>

int quantos_casais(std::vector<int> v){
  int cont {0};

  for(int i = 0; i < (int) v.size() ; i++){
    for(int j = i + 1; j < (int) v.size(); j++){
        if( abs(v[i]) == abs(v[j]) && v[i] != v[j])
          cont++;
    }
  }
  return cont;
}

int quantos_trios(std::vector<int> v){
  int cont {0};
  int trio {0};

  for(int i = 0; i < (int) v.size() ; i++){
    for(int j = 0; j < (int) v.size(); j++){
        if( abs(v[i]) == abs(v[j]) )
          cont++;
    }
    if(cont == 3)
      trio++;
  }
  return trio;
}

int main(){

    std::vector<int> vetor{1, 5, -5, 31, -31, -60, -31, 5};
    std::cout << "=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" <<"\n";

    std::cout << "casais: " << quantos_casais(vetor)<<"\n";
    std::cout << "trios: " << quantos_trios(vetor)<<"\n";


    std::cout << "\n=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" <<"\n";

    return 0;
}