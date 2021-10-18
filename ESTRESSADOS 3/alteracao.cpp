
#include<iostream>
#include<vector>
#include <algorithm>

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

void insert(std::vector<int>& v, int x, int pos) {
  v.insert(v.begin() + pos, x);
}

void remove(std::vector<int>& v, int x) {
  v.erase(std::find(v.begin(), v.end(), x));
}

int main(){

    std::vector<int> vetor{1, 5, -5, 31, -31, -60, -31, 5};
    std::cout << "=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" <<"\n";

   // std::cout << "casais: " << quantos_casais(vetor)<<"\n";

    insert(vetor, 5, 0);
    std::cout << "\nrecorrentes: ";
    for (size_t i = 0; i < vetor.size(); ++i) {
        std::cout << vetor.at(i) << " ";
    }

    std::cout << "\n=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" <<"\n";

    return 0;
}

