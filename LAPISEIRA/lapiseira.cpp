
#include<iostream>
#include<algorithm>

struct Grafite{
    float calibre;
    std::string dureza;
    int tamanho;

    Grafite(float calibre, std::string dureza, int tamanho) : calibre(calibre), dureza(dureza), tamanho(tamanho){
    }

    int desgaste_folha(){
        if(this-> dureza == "HB"){
            return 1;
        }
        if(this-> dureza == "2B"){
            return 2;
        }
        if(this-> dureza == "4B"){
            return 4;
        }
        if(this-> dureza == "6B"){
            return 6;
        }

    }
};

struct Lapiseira{
    float calibre;
    Grafite *grafite = nullptr;
    Lapiseira(float calibre) : calibre(calibre) {
    }

    Lapiseira(){}

    void inserir_grafite(Grafite *grafite){
        if( this-> calibre != grafite->calibre){
            return;
        }
        
        delete this->grafite;
        this-> grafite = grafite;
        std::cout<<this->grafite->calibre;
    }

    Grafite* remover(){
        if( this-> grafite == nullptr){
            std::cout << "sem grafite\n";
            return nullptr;
        }
        return std::exchange(this->grafite, nullptr);
    }

    void write(int folhas){
        while(folhas > 0 && this-> grafite->tamanho > 0){
            folhas--;
            this->grafite->tamanho -= this->grafite->desgaste_folha();
        }
        if(this-> grafite->tamanho <=0){
            std::cout<<"grafite acabou\n";
        }
        if(folhas > 0 ){
            std::cout<<"fail,  folhas restantes" << folhas << "\n";
        }
    }

    void to_String(){
        std::cout<< this->grafite->calibre <<"\n";
        std::cout<< this->grafite->dureza <<"\n";
        std::cout<< this->grafite->tamanho <<"\n";
    }

};


int main(){
    std::string comando;
    Lapiseira lapiseira;
    

    while(true){
        std::cin >> comando;
        if(comando == "init"){
            float calibre;
            std::cin >> calibre;
            lapiseira = Lapiseira(calibre);
        }  
        if(comando == "end"){
            return 0;
        }
        if(comando == "inserir"){
            int tamanho;
            std::string dureza;
            float calibre;
            Grafite grafite(calibre, dureza, tamanho);
            lapiseira.inserir_grafite(&grafite);
        }
        if(comando == "show"){
            lapiseira.to_String();
        }

    }

    return 0;
}
