#include<iostream>
#include<sstream>
#include <vector>
#include <map>
#include <stdexcept>


class Fone{
    std::string id;
    std::string numero;

public:

    Fone(std::string id, std::string numero) : id(id), numero(numero){
    }

    bool validate(){
        for(int i = 0; i < (int)numero.size(); i++){
            if( (numero[i] >= '0' && numero[i] <= '9') || numero[i] == '.' || numero[i] == '(' || numero[i] == ')'){
                return true;
            }
        }
        return false;
    }   

    std::string toString(){
        std::stringstream ss;
        ss<< id << ", " << numero;

        return ss.str();
    } 

    std::string getId(){
        return this->id;
    }

    std::string getNumero(){
        return this->numero;
    }

    void setId(){
        this->id = id;
    }

    void setNumero(){
        this->numero = numero;
    }
};

class Contact{
    std::string prefix;
    std::string name = "";
    std::vector<Fone> fones;

public:
    Contact(){}
    Contact( std::string name, std::vector<Fone> fones) : name(name), fones(fones){
    }

    void addFone(Fone fone) {
        if( !fone.validate() ) {
            std::cout << "Fone invalido" << std::endl;
            return;
        }
        fones.push_back(fone);
    }

    void rmFone(int index){
        if(index < 0 || index >= fones.size()) {
                std::cout << "Invalid index" << std::endl;
                return;
            }
            fones.erase(fones.begin()+index);
    }

    std::vector<Fone> getFones() {
        return this->fones;
    }

    std::string getName(){
        return this->name;
    }

    void setName(){
        this->name = name;
    }

     std::string toString(){
        std::stringstream ss;

        ss << this->name;
        for(int i=0; i< fones.size(); i++){
            ss<< " [" << i << ":"<< fones[i].getId() << ":" << fones[i].getNumero() << "]";
        }

        return ss.str();
    } 
};

class Agenda{
    std::map<std::string, Contact> contacts;
    
public:
    Agenda(){}

    void addContact(std::string s, Contact contato){
        if( contacts.find(s) != contacts.end() ){
            for(auto i: contato.getFones() ){
                contacts[s].addFone(i);
            }
        }
        else {
            contacts[s] = contato;
        }
    }

    Contact& getContato(std::string nome){
        auto var = contacts.find(nome);
        
        if(var!=contacts.end())
            return var->second;
        else    
            throw std::runtime_error("contato nao encontrado");
    }

    void rmContact(std::string nome){
        auto var = contacts.find(nome);
        if (var != contacts.end()){
            contacts.erase(var);
        }
        else{
            throw std::runtime_error("Contato nao encontrado");
        }
    }

    std::vector<Contact> search(std::string pattern){
        std::vector<Contact> auxiliar;

        for(auto [key, value]: contacts){
            if(key.find(pattern) != std::string::npos){
                auxiliar.push_back(value);
                continue;
            }
              
            for(auto i: value.getFones()){
                if((i.getNumero().find(pattern) != std::string::npos || i.getId().find(pattern) != std::string::npos ) ){
                    auxiliar.push_back(value);
                    break;
                }
            }
        }

        if(auxiliar.size()<=0){
            throw std::runtime_error("sem resultado de busca");
        }

        return auxiliar;
    }

    std::string toString(){
        std::stringstream ss;

        for(auto i : contacts){
            ss<< "-" << i.second.toString()<<"\n";
        }

        return ss.str();
    }


    Fone addVarios(std::string str){
        std::string id{""};
        std::string num{""};
        for (int i{0}; i < (int)str.length(); i++){
            if (str[i] == ':'){
                id = num;
                num = "";
            }
            else{
                num += str[i];
            }
        }
        Fone *fone = new Fone(id, num);
        return *fone;
    }
};

int main(){
    
    Agenda *agenda = new Agenda();

    while (true) {
        std::string comando;
        std::cin >> comando;

        std::string linha;
        getline(std::cin, linha);

        std::stringstream ss(linha);

        try{
            if (comando == "show") {
                std::cout << agenda->toString();
            }
            else if (comando == "rmContact") {
                std::string nome;
                ss >> nome;
                agenda->rmContact(nome);
            }
            else if (comando == "rmFone") {
                std::string nome;
                int index;
                ss >> nome >> index;
                agenda->getContato(nome).rmFone(index);
            }
            else if (comando == "add") {
                std::string nome;
                std::string fone;
                std::vector<Fone> fones;

                ss >> nome;
                
                while (ss >> fone){
                    fones.push_back(agenda->addVarios(fone));
                }

                Contact contato = Contact(nome,fones);
                agenda->addContact(nome, contato);
            }
            else if (comando == "search") {
                std::string padrao;
                ss >> padrao;

                for(auto i : agenda->search(padrao)) {
                    std::cout << i.toString();
                }
            }
            else if (comando == "end") {
                break;
            }
            else {
                throw std::runtime_error("comando invalido");
            }
        }

        catch(std::runtime_error erro){
            std::cout<<erro.what() <<"\n";
        }
    }
    return 0;
}

/*

add eva oio:8585 cla:9999
add ana tim:3434 
add bia viv:5454

add ana cas:4567 oio:8754

show

rmFone ana 0

show
add ava tim:5454

rmContact bia

search va


*/