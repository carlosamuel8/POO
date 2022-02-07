#include<iostream>
#include<vector>
#include<sstream>
#include<memory>
#include<map>
#include <iomanip>

class Account{
protected:
    float balance;
    std:: string clienteID;
    int id;
    std:: string type; 

public:
    Account(int id, std:: string clienteID ) : clienteID{clienteID}, id{id} {}
   
    virtual void monthlyUpdate(){
        throw std::runtime_error("erro de implementacao");
    }

    void deposit(float valor){
        balance+=valor;
    }

    void transfer(Account* conta, float valor){
        withdraw(valor);
        conta->deposit(valor);
    }

    void withdraw(float valor){
        balance-=valor;
    }

    friend std::ostream &operator<<(std::ostream& os, Account& account){
        os << account.getId() << ":" << account.getClientid() << ":" << std::setprecision(2) << std::fixed << account.getBalance() << ":" << account.getType();
        return os;
    }

    float getBalance(){
        return balance;
    }

    std::string getClientid(){
        return clienteID;
    }

    int getId(){
        return id;
    }

    std::string getType(){
        return type;
    }

};


class Client {
    std::vector<Account*> accounts;
    std::string clientid;
public:
    Client(){}
    Client(std::string clientid) : clientid{clientid} {}

    void addAcount(Account* conta){
        accounts.push_back(conta);
    }
    
    friend std::ostream &operator<<(std::ostream& os, const Client& client) {
        for(auto& account : client.accounts){
            os << *account << "\n";
        }

        return os;
    }

    std::vector<Account*> getAccounts() {
        return accounts;
    }

    std::string ClientId(){
        return clientid;
    }
    
    void setAccounts(std::vector<Account*> contas){
        accounts=contas;
    }

    void setClientId(std::string clientid){
        this->clientid=clientid;
    }
};


class SavingsAccount : public Account {
public:

    SavingsAccount(int id, std::string clientId) : Account(id, clientId) {
        this->type = "Poupanca";
    }

    void monthlyUpdate() {
        this->balance += 0.01 * this->balance;
        //std::cout << "Atualizacao mensal da conta poupanca foi realizada.";
    }
};


class CheckingAccount : public Account {
public:
    CheckingAccount(int id, std::string clientId) : Account(id, clientId) {
        this->type = "Corrente";
    }

    void monthlyUpdate() {
        this->balance -= 20;
       // std::cout << "Atualizacao mensal da conta corrente foi realizada.";
    }   
};

class BankAgency{
    std::map<int, Account*> contas;
    std::map<std::string, std::shared_ptr<Client>> clientes;
    int nextAccountId=0;

    Account*  getAccount(int id){
        return contas[id];
    }

public:

    void addClient(std::string client){

        this->clientes[client] = std::make_shared<Client> ( Client(client));
    
        this->contas[this->nextAccountId] = new CheckingAccount(this->nextAccountId, client );

        this->clientes[client]->addAcount(this->contas[this->nextAccountId]); 
        this->nextAccountId++;//mudar o id

        this->contas[this->nextAccountId] = new SavingsAccount(this->nextAccountId, client);
    
        this->clientes[client]->addAcount(this->contas[this->nextAccountId]); 
        this->nextAccountId++;
        //std::cout << "aqui " <<this->nextAccountId;
    }

    void deposit(int idConta, float valor){
        if(idConta<0 || idConta >= this->nextAccountId){
            throw std::runtime_error("conta nao existe");
        }
        else{
            getAccount(idConta)->deposit(valor);
        }
    }

    void monthlyUpdate(){
        for(auto [x, y]: contas){
            y->monthlyUpdate();
        }

    } 

    void transferir(int contaDe, int contaPara, float valor){
        if( contaDe >= this->nextAccountId || contaPara >= this->nextAccountId 
            || contaDe < 0 || contaPara < 0 ){
            
            throw std::runtime_error("conta nao existe");
        }

        else if(this->contas[contaDe]->getBalance() - valor < 0 
                && this->contas[contaDe]->getType() == "CP"){
            throw std::runtime_error("saldo insuficiente");
        }
        else{
            getAccount(contaDe)->transfer(getAccount(contaPara), valor);
        }
    }

    void withdraw(int idConta, float valor){
        if(idConta<0 || idConta >= this->nextAccountId){
            throw std::runtime_error("conta nao existe");
        }

        else if(this->contas[idConta]->getBalance() - valor<0 ){
            throw std::runtime_error("saldo insuficiente");
        }
        else{
            getAccount(idConta)->withdraw(valor);
        }
    }

    friend std::ostream &operator<<(std::ostream& os, const BankAgency& bank){
        os << "Clients:\n";

        for(auto& client : bank.clientes){
            os << "- " << client.first << "[";
            int contador = 1;
            for(auto& i : client.second.get()->getAccounts()){
                if(contador < (int) client.second.get()->getAccounts().size()){
                    os << i->getId() << ", ";
                    contador++;
                }
                else{
                    os << i->getId();
                }
            }
            os << "]\n";
        }
            os <<"Accounts:\n";

            for(auto& account : bank.contas){
                os <<  *account.second << "\n";
            }
        

    }
};


int main(){
    BankAgency bank;

    while(true){
        std::string linha{""};
        getline(std::cin, linha);

        std::stringstream ss(linha);
        std::string comando;

        ss >> comando;

        try{
            if(comando == "addCli"){
                std::string clientId;

                ss >> clientId;

                bank.addClient(clientId);
            }              
            else if(comando == "show"){
                std::cout << bank;
            }          
            else if(comando == "saque"){
                int id = -1;
                float value = 0;
                ss >> id >> value;

                bank.withdraw(id, value);
            }
            else if(comando == "deposito"){
                int id = -1;
                float value = 0;
                ss >> id >> value;

                bank.deposit(id, value);
            }
            else if(comando == "transf"){
                int idPara = -1;
                int idDe = -1;
                float valor = 0;
                ss >> idDe;
                ss>> idPara;
                ss >> valor;

                bank.transferir(idDe, idPara, valor);
            }
            else if(comando == "update"){
                bank.monthlyUpdate();
            }
            else if(comando == "end"){
                break;
            }
            else{
                std::cout << "Comando invalido\n";
            } 
        }
        catch(const std::exception& erro){
            std::cout << erro.what() << '\n';
        }
    }

    return 0;
}

/*
addCli Almir
addCli Julia
addCli Maria

deposito 0 100
deposito 1 200
deposito 2 50
deposito 3 300
saque 3 50
saque 0 70
saque 1 300

transf 3 5 200
transf 0 4 25
transf 9 1 30

update

*/