#include<iostream>
#include<vector>


int quantos_times(const std::vector<int>& v){
    int cont {0};
    
    for (int i = 0; i < (int)v.size(); i+=2) {
        if( (v[i]>0 && v[i+1]>0) || (v[i]<0 && v[i+1]>0) )
            cont++;
    }
    
    return cont;
}

int maior_time(const std::vector<int>& v){
    int contP{0};
    int contN{0};

    int maiorP{2};
    int maiorN{2};

    for (int i = 0; i < (int)v.size(); i++ ) {
        if (v[i]>0) {
            contP++;
            if (contP > maiorP)
                maiorP = contP;
            contN = 0;
        }
        else {
            contN++;
            if ( contN > maiorN ){            
                maiorN = contN;
            }
            contP = 0;
        }
    }

    if (maiorP>maiorN )
        return maiorP;
    else 
        return maiorN;    
}

int sozinhos(const std::vector<int>& v){
    int cont{0};

    for (int i = 0; i < (int)v.size(); i++ ) {
        if( (v[i]>0 && v[i+1]<0) || (v[i]<0 && v[i+1]>0) )
            cont++;
    }

    return cont;
}
int main(){

    std::vector<int> vetor{1, 33, -56, -1, -1, 60, -31, 60};
    std::cout << "=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" <<"\n";

    std::cout << "quantos times: " << quantos_times(vetor)<<"\n";
    
  /*  auto apazi = qua({1, 3, 85, 90, -1, -3, -3});
    std::cout << "\nApaziguados: ";
    for (size_t i = 0; i < apazi.size(); ++i) {
        std::cout << apazi.at(i) << " ";
    }*/

    std::cout << "quantos times: " << maior_time(vetor)<<"\n";
    std::cout << "sozinhos: " << sozinhos(vetor)<<"\n";
    std::cout << "\n=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" <<"\n";

    return 0;
}