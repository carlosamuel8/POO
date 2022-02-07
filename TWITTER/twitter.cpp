#include<iostream>
#include<map>
#include<set>
#include<sstream>
#include <memory>
#include<vector>

class Tweet {
    int id;
    std::string username;
    std::string msg;
    std::set<std::string> likes;
    bool deleted{true};
    Tweet *rt;

public:   
    Tweet(int id, std::string username, std::string msg) : id{id}, username{username}, msg{msg} {}

    int getId()const{
        return id;
    }

    std::string getUsername(){
        return username;
    }

    std::string getMsg(){
        return msg;
    }

    friend std::ostream& operator<<(std::ostream& os, const Tweet& msg){
        os << msg.id << ":" << msg.username << " ("<< msg.msg <<")";
        
        if( (int) msg.likes.size() > 0){
            os << "  " << "[";

            int contador = 1;
            for(auto i : msg.likes){
                if(contador < (int) msg.likes.size()) {
                    os << i << ", ";
                }
                else{
                    os << i;
                }
                contador++;
            }
            os << "]";
        }

        if(msg.rt != nullptr){
            os << "\n    " << *msg.rt;
        }

        return os;

    }

////////////////like/////////////////
    void like(std::string username){
       likes.insert(username);
    }

    std::set<std::string> getLikes(){
        return likes;
    }

    void setRt(Tweet* tw){
        rt = tw;   
    }

    void setDeleted(){
        deleted = false;
    }

    bool isDeleted(){
        return deleted;

    }



};


class Inbox{
    std::map<int, Tweet*> timeline;
    std::map<int, Tweet*> myTweets;
public:
    Inbox(){}

    void storeInTimeLine(Tweet* tweet){
        timeline[tweet->getId()] = tweet;
    }

    std::map<int, Tweet*> getTimeline() const{
        return timeline;
    }

    std::string showTimeline(){
        std::stringstream ss;

        for(auto i : this->getTimeline()){
            ss << *i.second << "\n";
        }

        return ss.str();
    }

////////like///////
    Tweet* getTwitter(int id){
        if(timeline.find(id) == timeline.end() ){
            throw std::runtime_error("id nao existe");
        }
        else{
            return timeline[id];
        }
    }

////////unfollow///////
    void rmMsgsFrom(std::string username){

        std::vector<int> auxiliar; //vetor pra apagar 

        for(auto i=timeline.begin(); i != timeline.end(); i++ ){
            if(i->second->getUsername() == username){
                auxiliar.push_back(i->first);
            }
        }  

        for(auto i : auxiliar){
            timeline.erase(i);
        }
    }

////////remover///////
    void storeInMyTweets(Tweet* tweet){
        myTweets[tweet->getId()] = tweet;
    }
    
    std::map<int, Tweet*> getMyTweets(){
        return myTweets;
    }

};


class User{
    std::string username;
    Inbox inbox;
    std::map<std::string, User*> followers;
    std::map<std::string, User*> following;
public:
    User(std::string username): username{username} {}

    friend std::ostream &operator<<(std::ostream& os, const User& user){
        
        os << user.username << "\n";
        os << "    seguidos      [";

        int contador = 1;
        for(auto i : user.following){
            if(contador < (int) user.following.size() ) {
                os << i.first << ", ";
            } 
            else{
                os << i.first; 
            }
            contador++;
        }
        os << "]\n";

        os << "    seguidores    [";

        contador = 1;
        for(auto i : user.followers){
            if(contador < (int) user.followers.size()){
                os << i.first << ", ";
            }
            else{
                os << i.first; 
            }
            contador++;
        }
        os << "]\n";

        return os;
    }


    void follow(User* user2){
        following[user2->username] = user2;
        user2->followers[this->username] = this;
    }
    

    Inbox& getInbox(){
        return inbox;
    }
    void sendTweet(Tweet* tw){
        inbox.storeInMyTweets(tw);
        inbox.storeInTimeLine(tw);

        //adicionando tweet na timeline dos seguidores
        for(auto x: followers){
            x.second->getInbox().storeInTimeLine(tw);
        }

    }

    void like(int idTweet){
        //inbox vai procurar o tweet, se existir ele recebe um like do usuario curtidor 
        inbox.getTwitter(idTweet)->like(this->username);
    }


////////unfollow/////////
    void unfollow(User* other){
        //tirar as mensagens
        inbox.rmMsgsFrom(other->username);
        
        //remover user da lista de seguidos
        following.erase(other->username);

        //remover da lista de seguidores do outro user
        other->followers.erase(this->username);
    }

////////remover/////////
    void unfollowAll(){
        following.clear();
    }

    void rejectAll(){
        for(auto x : followers){
            x.second->following.erase(username);
        }

        followers.clear();
    }
};

class Controller{
    int nextTweetId{0};
    std::map<std::string, std::shared_ptr<User>> users;
    std::map<int, std::shared_ptr<Tweet>> tweet;
public:
    Controller() {}

    friend std::ostream &operator<<(std::ostream& os, const Controller& controller){
        for(auto user : controller.users){
            os << *user.second;
        }

        return os;
    }

    void addUser(std::string username){
        // procura se o user existe
        if(users.find(username) == users.end()){
            users[username] = std::make_shared<User>(username);
        }else{
           throw std::runtime_error("usuario ja existe");
        }
    }



    Tweet* createTweet(std::string sender, std::string msg){
        auto tweet = std::make_shared<Tweet>(nextTweetId++, sender, msg);
        this->tweet[tweet->getId()] = tweet;
        
        return tweet.get();
    }
    
    User* getUser(std::string username){
        if(users.find(username) != users.end()){
            return users[username].get();
        }
        else{
            throw std::runtime_error("usuario inexistente");
        }
    }

    void sendTweet(std::string username, std::string msg){
        users[username]->sendTweet(createTweet(username, msg));
    }

    void sendRt(std::string user, int id, std::string msg){
        auto i = this->tweet.find(id);
        if (i == this->tweet.end()){
            throw std::runtime_error("tweet nao existe");
        }
        else{
            // pesquisa o tweet que será feito o rt e retorna ele
            Tweet* rt = getUser(user)->getInbox().getTwitter(id);
            
            // cria o novo tweet que sera o rt 
            Tweet* newTweet = createTweet(user, msg);

            //adiciona o novo tweet como rt do tweet selecionado
            rt->setRt(newTweet);

            //seta o novo tweet na timeline do user
            getUser(user)->sendTweet(newTweet);
        }
    }

//////////remover////////
    void rmUser(std::string username){

        if(users.find(username) == users.end() ){
            throw std::runtime_error("usuario nao existe");
        }
        else{
            User* user = getUser(username);

            //remover todos os seguidores e seguidos do user
            user->unfollowAll();
            user->rejectAll();

            //deletar todos os tweets referentes ao usuario
            for(auto tweet : user->getInbox().getMyTweets()){
                tweet.second->setDeleted();
            }

            // deletar o user
            users.erase(username);
        }
    }

    

};

int main(){
    Controller controle;

    std::string linha;
    std::string comando;

    
    while(true){
       
        getline(std::cin, linha);
        
        
        std::stringstream ss(linha);

        ss >> comando;

        try{   
            if(comando == "add"){
                std::string username;

                ss >> username;

                controle.addUser(username);

            }            
            else if(comando == "follow"){
                std::string user1;
                std::string user2;
            
                ss >> user1;
                    ss >> user2;

            //fazendo o user1 seguir o user2
                controle.getUser(user1)->follow(controle.getUser(user2));

            }
            else if(comando == "show"){
                std::cout << controle;
                
            }
            else if(comando == "twittar"){
                std::string username;
                std::string tweet;
                    
                ss >> username;

                getline(ss, tweet);

                controle.sendTweet(username, tweet.substr(1));
                
            }
            else if(comando == "timeline"){
                std::string user1;

                ss >> user1;

                std::cout << controle.getUser(user1)->getInbox().showTimeline();
                    
            }
            else if(comando == "like"){
                std::string curtidor;
                int id;

                ss>> curtidor;
                ss>> id;

                controle.getUser(curtidor)->like(id);
            }
            else if(comando == "unfollow"){
                std::string user1;
                std::string user2;

                ss>> user1;
                ss>> user2;

                controle.getUser(user1)->unfollow(controle.getUser(user2));
            }
            else if(comando == "rm"){
                std::string user;

                ss>>user;

                controle.rmUser(user);

            }
            else if(comando == "rt"){
                int id;
                std::string user;
                std::string msg;

                ss >> user >> id;

                getline(ss, msg);

                controle.sendRt(user, id, msg.substr(1));
                
            }
            else if(comando == "end"){
                    break;
            }
            else{
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
cadastrar

follow

twittar
    
like
    .
unfollow
   
retweet

remover

*/

/*
add joao
add maria
follow joao maria
twittar joao aaaaaaaaaa
twittar joao oioioi
timeline maria

rt maria 0 hahaha


*/
