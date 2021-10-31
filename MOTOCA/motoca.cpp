#include <iostream>
#include <sstream>
#include <vector>

struct Pessoa {
    std::string nome; //atributo
    int idade;

    Pessoa(std::string nome = "", int idade = 0) { //construtor default
        this->nome = nome;
        this->idade = idade;
    }

    Pessoa(int idade) : Pessoa("", idade) {
    }

    friend std::ostream& operator<<(std::ostream& os, const Pessoa& p) {
        os << "Nome: " << p.nome << " Idade: " << p.idade;
        return os;
    }
};


struct Motoca {
    std::vector<Pessoa> pessoas; 
    int tempo {0};
    int potencia {1};
    Motoca(int pot): potencia {pot} {
    }


    bool inserirPessoa(Pessoa p) {
        if ( pessoas.size() < 3 ){
            pessoas.push_back(p);
            std::cout<< pessoas.size() << " pessoa na moto" << "\n";
        }
        else 
            std::cout<<"ja tem duas pessoas" << "\n"; 

    }

    std::string buzinar() {
        return "P" + std::string(this->potencia, 'e') + "m";
    }

    Pessoa removerPessoa() {
        Pessoa p = pessoas[pessoas.size()-1];
        pessoas.pop_back();
        return p;
    }

    bool dirigir() {
        if (pessoas.size() == 0) {
            std::cout << "nao tem gente pra dirigir" << std::endl;
            return false;
        }

        std::cout<<"a motoca esta lotada" << "\n";

    }

};

int main() {
    Motoca motoca(1);
    while (true) {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        if (cmd == "end") {
            break;
        } 

        else if (cmd == "init") {
            int pot = 0;
            ss >> pot;
            motoca = Motoca(pot);
        } 

        else if (cmd == "inserir") {
            std::string nome {};
            int idade {};
            ss >> nome >> idade;
            Pessoa pessoa(nome, idade);
            motoca.inserirPessoa(pessoa); 
        } 
        
        else if (cmd == "retirar") {
            Pessoa pessoa = motoca.removerPessoa();
        } 
        
        else {
            std::cout << "Comando nao existe\n";
        }
    }
}

