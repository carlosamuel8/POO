#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class Fone{
    std::string id;
    std::string number;


public:
    Fone(std::string id="-", std::string number="-"){
        this->id = id;
        this->number = number;
    }

    std::string getId(){
        return this->id;
    };

    std::string getNumber(){
        return this->number;
    };

    void setId(std::string id){
        this->id = id;
    };

    void setNumber(std::string number){
        this->number = number;
    };
};

class Contact{
    std::string prefix = "-";
    std::vector<Fone> fones;
    std::string name;

public:
    Contact(std::string name = ""){
        this->name = name;
    }

    void addFone(Fone fone){
        fones.push_back(fone);
    }
   
    void rmFone(int index){
        fones.erase(fones.begin() + index);
    }

    std::string toString(){
        std::stringstream str;
        str << prefix << " " << this->name << "\n";
        for(int i = 0; i < fones.size(); i++){
            str << "[" << i << " : " << fones[i].getId() << " : " << fones[i].getNumber() << "]\n";
        }
        return str.str();
    }

    std::string getName(){
        return this->name;
    }

    void setName(std::string name){
        this->name = name;
    }
};

int main(){
    Contact contato;
    Fone fone;

    while(true){
        std::string str;
        std::cin >> str;
        if(str == "init"){
            std::string name;
            std::cin >> name;
            contato = Contact(name);

        }else if(str == "add"){
            std::string id;
            std::string number;
            std::cin >> id >> number;
            contato.addFone(fone);
        }

        else if(str == "rm"){
            int indice;
            std::cin >> indice;
            contato.rmFone(indice);
        }
        
        else if(str == "show"){
            std::cout << contato.toString() << std::endl;
        }
        else if(str == "end"){
            break;
        }
        else{
            std::cout << "-Comando invalido-" << std::endl;
        }
    }
}