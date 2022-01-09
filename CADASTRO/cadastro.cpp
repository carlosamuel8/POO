#include<iostream>
#include<vector>
#include<sstream>
#include<memory>
#include<map>

class Account{
protected:
    float balance;
    std:: string clienteID;
    int id;
    std:: string type; 

public:
    Account(int id, std:: string clienteID ) : clienteID{clienteID}, id{id} {}

    void deposit(float valor){
        balance+=valor;
    }

    void monthlyUpdate(){
        throw "erro de implementacao";
    }

    void transfer(std::shared_ptr<Account> conta, float valor){
        withdraw(valor);
        conta->deposit(valor);
    }

    void withdraw(float valor){
        balance-=valor;
    }

    std::string toString(){
        std::stringstream temp;
        temp<<"=~=~=~=~=~=~=~=~=~=~=~=~==~=";
        temp<<"Nome: "<<clienteID;
        temp<<"ID " <<id;
        temp<<"Tipo de conta: " << type;
        temp<<"Saldo: " <<balance;
        temp<<"=~=~=~=~=~=~=~=~=~=~=~=~==~=";
        return temp.str();
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
    std::vector<std::shared_ptr<Account>> accounts;
    std::string clientid;
public:
    Client(std::string clientid): clientid{clientid} {}

    void addAcount(std::shared_ptr<Account> conta){
        accounts.push_back(conta);
    }

    std::string toString(){
        std::stringstream temp;

        temp<<clientid;

        for(auto x: accounts){
            temp<<x->toString();
        }
        return temp.str();
    }

    std::vector<std::shared_ptr<Account>> getAccounts() {
        return accounts;
    }

    std::string ClientId(){
        return clientid;
    }
    
    void setAccounts(std::vector<std::shared_ptr<Account>> contas){
        accounts=contas;
    }

    void setClientId(std::string clientid){
        this->clientid=clientid;
    }
};


class SavingsAccount : public Account {
    float balance;
    std:: string clienteID;
    int id;
    std:: string type; 

    SavingsAccount(int id, std::string clientId) : Account(id, clientId) {
        this->type = "Poupanca";
    }

    void monthlyUpdate() {
        this->balance += 0.01 * this->balance;
        std::cout << "Atualizacao mensal da conta poupanca foi realizada.";
    }
};


class CheckingAccount : public Account {
    CheckingAccount(int id, std::string clientId) : Account(id, clientId) {
        this->type = "Corrente";
    }

    void monthlyUpdate() {
        this->balance -= 20;
        std::cout << "Atualizacao mensal da conta corrente foi realizada.";
    }   
};

class BankAgency{
    std::map<int, std::shared_ptr<Account>> contas;
    std::map<std::string, std::shared_ptr<Client>> clientes;
    int nextAccountId;

    std::shared_ptr<Account>  getAccount(int id){
        return contas[id];

    }

    void addClient(std::string client){
        this->clientes[client] = std::make_shared<Client> (new Client(client));
    }

    void deposit(int idConta, float valor){
        getAccount(idConta)->deposit(valor);
    }

    void monthlyUpdate(){
        for(auto [x, y]: contas){
            y->monthlyUpdate();
        }
    } 

    void transferer(int contaDe, int contaPara, float valor){
        getAccount(contaDe)->withdraw(valor);
        getAccount(contaPara)->deposit(valor); 
    }
    void withdraw(int idConta, float valor){
        getAccount(idConta)->withdraw(valor);
    }

    std::string toString(){
        std::stringstream temp;
        temp<<"CONTAS";
        for(auto [x, y]: contas){
            temp<<y->toString();
        }

        temp<<"CLIENTES";
        for(auto [x, y]: clientes){
            temp<<y->toString();
        }
        return temp.str();
    }
};

int main(){

}