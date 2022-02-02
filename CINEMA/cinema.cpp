#include <iostream>
#include <vector>
#include <sstream>

class Cliente{
    std::string fone;
    std::string id_nome;

public:
    Cliente (std::string id_nome="", std::string fone="") : id_nome {id_nome}, fone {fone} {}

    std::string getFone(){
        return fone;
    }

    std::string getId_Nome(){
        return id_nome;
    }

    std::string setFone(){
        this->fone = fone;
    } 

    std::string setId_nome(){
        this->id_nome = id_nome;
    } 


};


class Sala {
    std::vector<Cliente*> cadeiras;

public:
    Sala (int capacidade = 0) {
        this->iniciar(capacidade);
    }

    void iniciar (int capacidade) {
        std::vector<Cliente*> aux;
        for (int i=0; i < capacidade; i++) {
            aux.push_back(new Cliente);
        }
        this->cadeiras = aux;
    } 

    void cancelar (std::string id) {
        bool teste = true;
        for (auto& i : this->cadeiras) {
            if (i->getId_Nome() == id) {
                i->getId_Nome();
                i->setFone();
                teste = false;
                break;
            }
        }
        if (teste == true) {
            std::cout << "cliente nao esta no cinema\n";
        }
    }
    bool reservar(std::string id, std::string fone, int ind) {
        if (ind >= this->cadeiras.size()) {
            std::cout << "Cadeira invalida \n";
            return false;
        }

        for (auto& i : this->cadeiras) {
            if (i->getId_Nome() == id) {
                std::cout << "Cliente ja esta no cinema \n";
                return false;
            }
        }

        this->cadeiras.insert(cadeiras.begin()+ind, new Cliente(id, fone));
        return true;
    }


    std::string toString(){

        std::stringstream ss;
        ss<< "CINEMA\n";
        for (auto x: cadeiras) {
            ss<< x->getId_Nome() <<": " << x->getFone() <<"\n";
    
        }

        return ss.str();
    }
}; 

int main(){
    Sala sala;
    sala.iniciar(12);
    sala.reservar("davi", "3232", 0 );
    //std::cout << sala.toString();
    sala.reservar("zacarias", "fdg", 2 );
    std::cout << sala.toString();

    return 0;
}