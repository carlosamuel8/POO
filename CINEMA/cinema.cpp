#include <iostream>
#include <sstream>
#include <vector>


class Cliente{
    std::string fone;
    std::string id_nome;
    
public:
    Cliente (std::string id_nome = "", std::string fone = "") : id_nome {id_nome}, fone {fone} {
    }

    std::string getFone(){
        return fone;
    }

    std::string getId_Nome(){
        return id_nome;
    }

    std::string setFone(){
        this->fone=fone;
    } 

    std::string setId_nome(){
        this->id_nome=id_nome;
    } 


};


class Sala {
    std::vector<Cliente> cadeiras;

public:
    Sala (int capacidade = 0) {
        this->iniciar(capacidade);
    }

    void iniciar (int capacidade) {
        std::vector<Cliente> auxiliar;
        for (int i{0}; i < capacidade; i++) {
            Cliente cliente;
            auxiliar.push_back(cliente);
        }
        this->cadeiras = auxiliar;
    }

    void cancelar (std::string id) {
        bool teste = true;
        for (auto& i : this->cadeiras) {
            if (i.getId_Nome() == id) {
                i.getId_Nome();
                i.setFone();
                teste = false;
                break;
            }
        }
        if (teste == true) {
            std::cout << "Operacao invalida, o cliente nao esta no cinema\n";
        }

    }

    bool reservar(std::string id, std::string fone, int ind) {
        if (ind >= this->cadeiras.size()) {
            std::cout << "Cadeira invalida \n";
            return false;
        }

        for (auto& i : this->cadeiras) {
            if (i.getId_Nome() == id) {
                std::cout << "Cliente ja esta no cinema \n";
                return false;
            }
        }

        if (this->cadeiras[ind].setId_nome() == "-") {
            this->cadeiras[ind].setFone();
            this->cadeiras[ind].setId_nome();
            return true;
        }
        
        std::cout << "fail: cadeira ja esta ocupada\n";
        return false;
    }
};


























