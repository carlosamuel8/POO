#include <iostream>
#include <sstream>
#include <vector>
#include <list>


class Kid{
    int idade;
    std::string nome;
public:
    Kid(std::string nome, int idade) : nome(nome), idade(idade){
    }

    std::string get_name(){
        return nome;
    }

    int  get_idade(){
        return idade;
    }

    int set_idade(){
        this->idade=idade;
    } 

    bool operator==(const Kid& kid){
        return kid.nome==this->nome;
    }
    bool operator!=(const Kid& kid){
        return kid.nome!=this->nome;
    }



};



class Trampolim{
    std::list<Kid> pulando;
    std::list<Kid> esperando;
public:
    void entrar(){
        pulando.push_back(esperando.front());
        esperando.pop_front();
    }

    void sair(){
       esperando.push_back(pulando.front());
       pulando.pop_front();
    }

    void chegar(Kid crianca){
        esperando.push_back(crianca);
    }

    ///remove de onde ela estiver
    void remover(std::string nome){
        Kid kid_vazia=Kid("nome", 0);
        for(auto x: esperando ){
            if(x.get_name() == nome){
                kid_vazia = x;
            }
        }
        esperando.remove(kid_vazia);

        for(auto x: pulando ){
            if(x.get_name() == nome){
                kid_vazia = x;
            }
        }
        pulando.remove(kid_vazia);
    }

    void printar(){
        for(auto x: pulando ){
            std::cout << "pulando: " << x.get_name() << "\n";
        }
        for(auto x: esperando ){
            std::cout << "esperando: " << x.get_name() << "\n";
        }
    }

};

struct Controller{
    Trampolim trampolim;

    void shell(std::string line){
        std::stringstream in(line);
        std::string op;
        in >> op;
        if(op == "show"){
            trampolim.printar();
        }else if(op == "remove"){
            std::string nome;
            in >> nome;
            trampolim.remover(nome);
        }else if(op == "in"){
            std::string nome;
            int idade;
            in >> nome;
            std::cin >> idade; 
            Kid kid(nome, idade);
            trampolim.chegar(kid);
        }else if(op == "out"){
            trampolim.sair();
        }
        else
            std::cout << "fail: comando invalido" << "\n";
    }

    void exec(){
        std::string line;
        while(true){
            getline(std::cin, line);
            std::cout << "$" << line << "\n";
            if(line == "end")
                return;
            shell(line);
        }
    }
};

int main(){

    Controller c;
    c.exec();
    return 0;

    /*
    Trampolim trampolim;
    Kid kid1("samuel", 12);
    Kid kid2("Fagner", 47);

    trampolim.chegar(kid1);
    trampolim.chegar(kid2);
    trampolim.printar();
    trampolim.remover("Fagner");
    trampolim.printar();
    */
}