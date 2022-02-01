#include<iostream>
#include<map>
#include<vector>
#include<sstream>

class IMedico;
class Medico;

class IPaciente {
    public:
        virtual void addMedico(IMedico*) = 0;
        virtual std::string getDiagnostico() = 0;
        virtual std::string getId() = 0;
        virtual std::map<std::string, IMedico*> getMedicos() = 0;
        virtual void removerMedico(std::string idMedico) = 0;
        //virtual std::string to_String();
};

class IMedico{
    public:
        virtual void addPaciente(IPaciente*) = 0;
        virtual std::string getClasse() = 0;    
        virtual std::string getId() = 0;
        virtual std::map<std::string, IPaciente*> getPacientes() = 0;
        virtual void removerPaciente(std::string idmedico) = 0;
};


class Paciente : public IPaciente{
    std::string diagnostico;
    std::map<std::string, IMedico*> medicos;
    std::string id;
public:
    Paciente(std::string id, std::string diagnostico) : id{id}, diagnostico{diagnostico}{}

    void addMedico(IMedico *medico){
        medicos[medico->getId()] = medico;
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
        medicos.erase(medicoId);
    }

    std::string toString(){
        std::stringstream ss;

        ss<<diagnostico;
        ss<<id;

        for(auto x : medicos){
            ss<<x.second->getId();
        }

        return ss.str();
    }  
    
};


class Medico : public IMedico{
    std::string classe;
    std::map<std::string, IPaciente*> pacientes;
    std::string id;
public:
    Medico(std::string id, std::string classe) : id{id}, classe{classe}{}

    void addPaciente(IPaciente *paciente){
        pacientes[paciente->getId()] = paciente;
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
        pacientes.erase(idPaciente);
    }

    std::string toString(){
        std::stringstream ss;

        ss<<classe;
        ss<<id;

        for(auto x : pacientes){
            ss<<x.second->getId();
        }

        return ss.str();
    }  
};


class Hospital{
    std::map<std::string, IMedico*> medicos;
    std::map<std::string, IPaciente*> pacientes;

public:
    Hospital(){}

    void addMedico(IMedico *medico){
        medicos[medico->getId()] = medico;
    }

    void addPaciente(IPaciente *paciente){
        pacientes[paciente->getId()] = paciente;
    }

    void removerMedico(std:: string medicoId){
        medicos.erase(medicoId);
    }

    void removerPaciente(std:: string pacienteId){
        pacientes.erase(pacienteId);
    }

    void showAll(){
        std::cout<< "PACIENTES: ";
        for(auto x : pacientes){
            std::cout<< x.second->getId() << " ";
        }
        std::cout<< "\nMEDICOS: ";
        for(auto x : medicos){
            std::cout<< x.second->getId() << " ";
        }
    }

    void vincular(std::string medico, std::string paciente){
        medicos[medico]->addPaciente(pacientes[paciente]); 
        pacientes[paciente]->addMedico(medicos[medico]); 
    }

};



int main() {
    Hospital hospital;

    hospital.addPaciente(new Paciente("Fagner", "Preguiça"));
    hospital.addPaciente(new Paciente("Carlos", "Obesidade"));
    hospital.addPaciente(new Paciente("Yasmin", "covid"));

    hospital.addMedico(new Medico("Samuel", "Obstetra"));
    hospital.addMedico(new Medico("Augusto", "Pediatra"));
    hospital.addMedico(new Medico("Eliza", "clinica geral"));

    hospital.vincular("Samuel", "Fagner");
    hospital.vincular("Eliza", "Yasmin");

    hospital.showAll();
}

