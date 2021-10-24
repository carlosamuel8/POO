
#include<iostream>
#include<vector>
#include <algorithm>

void remove(std::vector<int>& v, int x) {
  v.erase(std::find(v.begin(), v.end(), x));
}

void insert(std::vector<int>& v, int x, int pos) {
  v.insert(v.begin() + pos, x);
}



int main(){

    std::vector<int> vetor{1, 5, -5, 31, -31, -60, -31, 5};
    std::cout << "=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" <<"\n";

   // std::cout << "casais: " << quantos_casais(vetor)<<"\n";

    remove(vetor, 5);
    std::cout << "\nremovendo: ";
    for (size_t i = 0; i < vetor.size(); ++i) {
        std::cout << vetor.at(i) << " ";
    }

    insert(vetor, 5, 0);
    std::cout << "\ninserindo: ";
    for (size_t i = 0; i < vetor.size(); ++i) {
        std::cout << vetor.at(i) << " ";
    }

    std::cout << "\n=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" <<"\n";

    return 0;
}

