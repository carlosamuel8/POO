#include<iostream>
#include<vector>



int briga( const std::vector<int>& v){
    int cont {0};
    
    for (int i = 0; i < (int)v.size(); i++) {
        if(  abs(v[i])>50 &&  abs(v[i-1])>30 && abs(v[i+1])>30)
            cont++;
    }
    
    return cont;
}

std::vector<int> apaziguados( const std::vector<int>& v){
    std::vector<int> apaziguados;
  
    for (int i = 0; i < (int)v.size(); i++) {
        if( (abs(v[i])>80) && ( abs(v[i-1])<10  || abs(v[i+1])<10 )  )
            apaziguados.push_back(i);
    }
    return apaziguados;
}




int main(){

    std::vector<int> vetor{1, 33, 56, 40, -1, -2, -31, 60, 60};
    std::cout << "=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" <<"\n";
   /*
    auto sozinhoss = sozinhos({1, 3, 4, 3, -1, -3, -3});
    std::cout << "Sozinhos: ";
    for (size_t i = 0; i < sozinhoss.size(); ++i) {
        std::cout << sozinhoss.at(i) << " ";
    }*/

    std::cout << "Briga: " << briga(vetor)<<"\n";
    
    auto apazi = apaziguados({1, 3, 85, 90, -1, -3, -3});
    std::cout << "\nApaziguados: ";
    for (size_t i = 0; i < apazi.size(); ++i) {
        std::cout << apazi.at(i) << " ";
    }

  
    std::cout << "\n=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" <<"\n";

    return 0;
}