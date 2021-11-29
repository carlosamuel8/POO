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

    void setName(){
        this->name = name;
    }


};

class Agenda{
    std::vector<Contact> contacts;

    void addContact(Contact contato){
        contacts.push_back(contato);
    }

    Contact getContato(std::string nome){
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

int main(){
    // teste vc mesmo



    return 0;
}



