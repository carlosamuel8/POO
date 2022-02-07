#include<iostream>
#include<map>
#include<vector>
#include<sstream>
#include <stdexcept>



class IMedico;
class Medico;

class IPaciente {
    public:
        virtual void addMedico(IMedico*) = 0;
        virtual std::string getDiagnostico() = 0;
        virtual std::string getId() = 0;
        virtual std::map<std::string, IMedico*> getMedicos() = 0;
        virtual void removerMedico(std::string idMedico) = 0;
        virtual std::string toString() = 0;

};

class IMedico{
    public:
        virtual void addPaciente(IPaciente*) = 0;
        virtual std::string getClasse() = 0;    
        virtual std::string getId() = 0;
        virtual std::map<std::string, IPaciente*> getPacientes() = 0;
        virtual void removerPaciente(std::string idmedico) = 0;
        virtual std::string toString() = 0;
};


class Paciente : public IPaciente{
    std::string id;
    std::string diagnostico;
    std::map<std::string, IMedico*> medicos;
public:
    Paciente(std::string id, std::string diagnostico) : id{id}, diagnostico{diagnostico}{}

    void addMedico(IMedico *medico){
        if(medicos.find(medico->getId()) == medicos.end() ){
            medicos[medico->getId()] = medico;
        }
        else{
            throw std::runtime_error("medico ja esta cadastrado");
        }
    }

    std::string getDiagnostico(){
        return diagnostico;
    }

    std::string getId(){
        return id;
    }

    std::map<std::string, IMedico*> getMedicos(){
        return medicos;
    }   

    void removerMedico(std::string medicoId){
        if(medicos.find(medicoId) != medicos.end() )
            medicos.erase(medicoId);
        else{
            throw std::runtime_error("medico nao existe");
        }
    }

    std::string toString(){
        std::stringstream ss;

        ss << "Pac: " <<  this->getId() << ":" << this->getDiagnostico() <<"     Meds[";
        
        for(auto x : medicos){
            ss<<x.second->getId()<< ", ";
        }
        ss << "]";
        return ss.str();
    }  
    
};


class Medico : public IMedico{
    std::string id;
    std::string classe;
    std::map<std::string, IPaciente*> pacientes;
public:
    Medico(std::string id, std::string classe) : id{id}, classe{classe}{}

    void addPaciente(IPaciente *paciente){
        if(pacientes.find(paciente->getId()) == pacientes.end() )
            pacientes[paciente->getId()] = paciente;
        else{
            throw std::runtime_error("paciente ja existe");
        }
    }

    std::string getClasse(){
        return classe;
    }

    std::string getId(){
        return id;
    } 

    std::map<std::string, IPaciente*> getPacientes(){
       return pacientes;
    } 

    void removerPaciente(std::string idPaciente){
        if(pacientes.find(idPaciente) == pacientes.end() )
            pacientes.erase(idPaciente);
        else{
            throw std::runtime_error("paciente nao existe");
        }
    }

    std::string toString(){
        std::stringstream ss;

        ss << "Med: " << this->getId() << ":" << this->getClasse()<< "     Pacs[";
        
        for(auto x : pacientes){
            ss<<x.second->getId() << ", ";
        }
        ss << "]";
        return ss.str();
    }  
};


class Hospital{
    std::map<std::string, IMedico*> medicos;
    std::map<std::string, IPaciente*> pacientes;

public:
    Hospital(){}

    void addMedico(IMedico *medico){
        if(medicos.find(medico->getId()) == medicos.end())
            medicos[medico->getId()] = medico;
        else{
            throw std::runtime_error("medico ja esta cadastrado");
        }
    }

    void addPaciente(IPaciente *paciente){
        if(pacientes.find(paciente->getId()) == pacientes.end() )
            pacientes[paciente->getId()] = paciente;
        else{
            throw std::runtime_error("paciennte ja esta cadastrado");
        }  
    }

    void removerMedico(std:: string medicoId){
        if(medicos.find(medicoId) != medicos.end() )
            medicos.erase(medicoId);
        else{
            throw std::runtime_error("medico nao existe");
        }
    }

    void removerPaciente(std:: string pacienteId){
        if(pacientes.find(pacienteId) != pacientes.end() )
            pacientes.erase(pacienteId);
        else{
            throw std::runtime_error("paciente nao existe");
        }
    }

    std::string showAll(){
        std::stringstream ss;

        for(auto x : pacientes){
           ss << x.second->toString() << "\n";
        }

        for(auto x : medicos){
          ss << x.second->toString() << "\n";
        }

        return ss.str();
    }

    void vincular(std::string medico, std::string paciente){
        //verificar se existem
        if(medicos.find(medico) == medicos.end() ){
            throw std::runtime_error("medico nao existe");
        }

        if(pacientes.find(paciente) == pacientes.end() ){
            throw std::runtime_error("paciente nao existe");
        }

        for(auto i : pacientes[paciente]->getMedicos()){
            if(i.second->getId() == medico){
                throw std::runtime_error("medico ja existe") ;
            }
            if(i.second->getClasse() == medicos[medico]->getClasse() ){
                throw std::runtime_error("medico de especialidade ja existente");
            }

        }
        //adicionar
        medicos[medico]->addPaciente(pacientes[paciente]); 
        pacientes[paciente]->addMedico(medicos[medico]); 
    }

};



int main() {
    Hospital hospital;

    std::string linha{""};
    std::string comando{""};

    while (true){
        
        getline(std::cin, linha);
        std::stringstream ss(linha);
        ss >> comando;

        try{
            if(comando == "addPacs"){
            std::string temp;

            while(ss >> temp){
               int separador = temp.find("-");

               std::string paciente = temp.substr(0, separador);
               std::string diagnostico = temp.substr(separador + 1);

               hospital.addPaciente(new Paciente(paciente, diagnostico));
            }

            }
            
            else if(comando == "addMeds"){
                std::string temp;

                while(ss >> temp){
                int pos = temp.find("-");

                std::string id = temp.substr(0, pos);
                std::string classe = temp.substr(pos + 1);

                hospital.addMedico(new Medico(id, classe));
                }
            }
            
            else if(comando == "rmPac"){
                std::string pacId;

                ss >> pacId;

                hospital.removerPaciente(pacId);
            }
            
            else if(comando == "rmMed"){
                std::string medId;

                ss >> medId;

                hospital.removerMedico(medId);
            }
            
            else if(comando == "show"){
                std::cout << hospital.showAll();
            }

            else if(comando == "tie"){
                std::string medId;
                std::string pacId;

                ss >> medId;

                while(ss >> pacId){
                    hospital.vincular(medId, pacId);
                }
            }

            else if(comando == "end"){
                break;
            }

            else{
                throw std::runtime_error("comando invalido");
            }
 
        }
        catch(const std::exception& erro){
            std::cout << erro.what() << '\n';
        }
    }

}


/*
addPacs fred-fratura alvis-avc goku-hemorragia silva-sinusite
addMeds bisturi-cirurgia snif-alergologia facada-cirurgia

show

tie bisturi fred alvis goku
tie snif silva alvis
tie facada goku

show
*/