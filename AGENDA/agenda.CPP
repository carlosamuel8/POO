#include<iostream>
#include<sstream>
#include <vector>

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

    Contact( std::string prefix, std::vector<Fone> fones) : prefix(prefix), fones(fones){
    }
    Contact(){}
    
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

    std::string toString(){
        std::stringstream ss;

        for(auto i : fones){
            std::cout << name << i.getNumero() << "\n";
        }

        return ss.str();
    } 

    std::vector<Fone> getFones() {
        return this->fones;
    }

    std::string getName(){
        return this->name;
    }

    void setName(std::string name){
        this->name = name;
    }
/*
    std::string toString(){
        std::stringstream ss;

        ss<<prefix;
        ss<<name;

        for(auto i : fones){
           std::cout << i.toString();
        }
    }*/

};

class Agenda{
    std::vector<Contact> contacts;
public:
    void addContact(Contact contato){
        contacts.push_back(contato);
    }

    Contact getContact(std::string nome){
        for(auto x: contacts){
            if(x.getName() == nome )
                return x;
        }
    }

    void rmContact(std::string nome){
        for(int i = 0; i<(int)contacts.size(); i++){
            if(contacts[i].getName() == nome )
                contacts.erase(contacts.begin()+i);
        }
    }

    std::vector<Contact> search(std::string pattern){
        std::vector<Contact> auxiliar;

        for(auto x: contacts){
            if(x.getName().find(pattern)){
                auxiliar.push_back(x);
                continue;
            }
              
            for(auto i: x.getFones()){
                if(i.getNumero().find(pattern)){
                    auxiliar.push_back(x);
                    break;
                }
            }
        }

        return auxiliar;
    }

    std::string toString(){
        std::stringstream ss;

        for(auto i : contacts){
            std::cout << i.getName() << "\n";
            for(auto j: i.getFones()){
                 std::cout << j.getId() <<", " << j.getNumero() << "\n";
            }
        }
    }

};


void controle(Agenda& agenda){
    std::string linha{""};

    while(true){
        std::cout << "$";

        getline(std::cin, linha);

        std::stringstream ss(linha);
        std::string comando;

        ss >> comando;

        if(comando == "init"){
           agenda = Agenda();
        }

        else if(comando == "show"){
            std::cout << agenda.toString();
        }

        else if(comando == "add"){
           std::string name;

            ss >> name;
            Contact contact;
            contact.setName(name);
            agenda.addContact(contact);
        }

        else if(comando == "rm"){
           std::string name;

           ss >> name;

           agenda.rmContact(name);
        }

        else if(comando == "rmFone"){
            std::string name;
            int id;

            ss >> name >> id;
            agenda.getContact(name).rmFone(id);

            if(agenda.getContact(name).getFones().size() == 0){
                agenda.rmContact(name);
            }
        }

        else if(comando == "end"){
            break;
        }

        else if(comando == "search"){
            std::string pesquisa;

            ss >> pesquisa;

            std::vector<Contact> result = agenda.search(pesquisa);

            if((int) result.size() == 0){
                std::cout << "nao encontrou\n";

            }else{
                for(auto contact : result){
                    std::cout << contact.toString() << "\n";
                }
            }

        }
        
        else{
            std::cout << "Comando invalido\n";
        }
    }
}


int main(){
    Agenda agenda;

    controle(agenda);


    return 0;
}



