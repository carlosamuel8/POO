#include<iostream>

class Animal{
    bool alive{true};

public:
    Animal(){}

    void morrer(){
        alive=false;
    }

    void comer(){
        std::cout<<"animal esta comendo" <<"\n";
    }

    bool isAlive(){
        return alive;
    }

    friend std::ostream& operator<<(std::ostream& os, const Animal& animal){
        os << "Animal esta vivo: " << animal.alive <<"\n";
    }

};


class Pet : public Animal{
public:
 std::string nome{""};

    Pet(std::string nome) : nome{nome} {
        std::cout<< nome <<" nasceu" <<"\n";
    }

    void brincar(){
        if (this->isAlive())
            std::cout<< this->nome <<" esta brincando..." <<"\n";
        else    
            std::cout<<"nao se brinca com o animal morto" <<"\n";
    }

    void comer(){
        std::cout<< this->nome <<" esta comendo" <<"\n";
    }

    void morrer(){
        Animal::morrer(); 
        std::cout <<"Sinto muito, " << this->nome << " morreu"<<"\n";
    }
    
};

class Cachorro : public Pet {
public:
    Cachorro(std::string nome) : Pet{nome}{}

    void latir(){
        if( this->isAlive() ) {
            std::cout<< this->nome <<" esta latindo..." <<"\n";
        } else {
            std::cout<< this->nome <<" esta morta, nao pode latir" <<"\n";
        }
    } 

};





int main(){
    Cachorro teste("alguem");

    teste.comer();
    teste.brincar();
    
    teste.latir();
    teste.morrer();
    teste.brincar();


}