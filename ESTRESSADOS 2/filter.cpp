
#include<iostream>
#include<vector>

std::vector<int> clone(const std::vector<int>& v){
    std::vector<int> copia(v);
    return copia;
}

std::vector<int> pegar_homens(const std::vector<int>& v){
    std::vector<int> homens;

    for (size_t i = 0; i < v.size(); ++i) {
        if(v[i]>0)
            homens.push_back (v[i]);
    }
    return homens;
}

std::vector<int> pegar_calmos(const std::vector<int>& v){
    std::vector<int> calmos;

    for (size_t i = 0; i < v.size(); ++i) {
        if(abs(v[i]) <=10)
            calmos.push_back (abs(v[i]));
    }
    return calmos;
}


std::vector<int> pegar_mulheres_calmas(const std::vector<int>& v){
    std::vector<int> mulherescalmas;

    for (size_t i = 0; i < v.size(); ++i) {
        if( v[i] <0 && v[i] > -10)
            mulherescalmas.push_back (v[i]);
    }
    return mulherescalmas;
}

int main(){
    std::vector<int> vetor{90, -90, 80, -80, -8, 10};

    std::cout << "=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" <<"\n";
    
    auto copiavet = clone(vetor);
    std::cout << "Clone: ";
    for (size_t i = 0; i < copiavet.size(); ++i) {
        std::cout << copiavet.at(i) << " ";
    }

    auto homens = pegar_homens(vetor);
    std::cout << "\nHomens: ";
    for (size_t i = 0; i < homens.size(); ++i) {
        std::cout << homens.at(i) << " ";
    }

    auto calmos = pegar_calmos(vetor);
    std::cout << "\nCalmos: ";
    for (size_t i = 0; i < calmos.size(); ++i) {
        std::cout << calmos.at(i) << " ";
    }

    auto mulherescalmas = pegar_mulheres_calmas(vetor);
    std::cout << "\nMulheres calmas: ";
    for (size_t i = 0; i < mulherescalmas.size(); ++i) {
        std::cout << mulherescalmas.at(i) << " ";
    }

    std::cout << "\n=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" <<"\n";


    return 0;
}


