#include<iostream>
#include<map>
#include<set>
#include<sstream>

class Tweet {
    int id;
    std::string username;
    std::string msg;
    std::set<std::string> likes;   
    Tweet *rt;
public:   
    Tweet(int id, std::string username, std::string msg) : id{id}, username{username}, msg{msg} {}

    int getId(){
        return id;
    }

    std::string getUsername(){
        return username;
    }

    std::string getMsg(){
        return msg;
    }

    std::string toString(){
        std::stringstream ss;

        ss<<id;
        ss<<username;
        ss<<msg;
        for(auto x:likes){
            ss<<x;
        }
        return ss.str();
    }



////////////////like/////////////////
    void like(std::string username){
       likes.insert(username);
    }

    std::set<std::string> getLikes(){
        return likes;
    }

////////////////retweet/////////////////
    void setRt(Tweet tw){
        rt = &tw;   
    }

////////////////remover/////////////////
    bool deleted{true};

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


    ////////twittar///////
    void storeInTimeLine(Tweet tweet){
        timeline[tweet.getId()] = &tweet;
    }

    std::map<int, Tweet*> getTimeline(){
        return timeline;
    }
    
    std::string toString(){
        std::stringstream ss;

        for( auto x : timeline){
            ss<<x.second->toString();
        }

        for( auto x : myTweets){
            ss<<x.second->toString();
        }

        return ss.str();
    }

////////like///////
    Tweet getTwitter(int id){
        return *myTweets[id];
    }

////////unfollow///////
    void rmMsgsFrom(std::string username){
        for(auto x: timeline){
            if(x.second->getUsername() == username){
                timeline[x.first] = nullptr;
            }
        }
    }

////////remover///////
    void storeInMyTweets(Tweet tweet){
        myTweets[tweet.getId()] = &tweet;
    }
    
    std::map<int, Tweet*> getMyTweets(){
        return myTweets;
    }

};


class User{
    std::string username;
    Inbox inbox;
    std::map<std::string, User> followers;
    std::map<std::string, User> following;
public:
    User(){}
    User(std::string username): username{username} {}

    std::string toString(){
        std::stringstream ss;

        ss<<username;
        ss<<inbox.toString();
        
        for(auto x : followers){
            ss<<x.first;
        }

        for(auto x:following){
            ss<<x.first;
        }

        return ss.str();
    }

////////follow/////////
    void follow(User other){
        following[other.username] = other;
    }
    
////////twittar/////////
    Inbox getInbox(){
        return inbox;
    }
    void sendTweet(Tweet tw){
        inbox.storeInMyTweets(tw);
        inbox.storeInTimeLine(tw);

        for(auto x: followers){
            x.second.getInbox().storeInTimeLine(tw);
        }

    }


////////unfollow/////////
    void unfollow(std::string other){
        following.erase(other);
        inbox.rmMsgsFrom(other);
    }

////////remover/////////
    void unfollowAll(){
        following.clear();
    }

    void rejectAll(){
        for(auto x: followers){
            x.second.unfollow(username);
        }

        followers.clear();
    }
};

class Controller{
    int nextTweetId;
    std::map<std::string, User> users;
    std::map<int, Tweet> tweet;
public:
    Controller() {}

    void addUser(std::string username){
        users[username] = User(username);
    }

    std::string toString(){
        std::stringstream ss;

        ss<<nextTweetId;
                
        for(auto x : users){
            ss<<x.second.toString();
        }

        for(auto x : tweet){
            ss<<x.second.toString();
        }
    }
//////////twittar////////
    Tweet createTweet(std::string sender, std::string msg){
        Tweet tweet(nextTweetId, sender, msg);
        return tweet;
    }
    User getUser(std::string username){
        return users[username];
    }

    void sendTweet(std::string username, std::string msg){
        users[username].sendTweet(createTweet(username, msg));
    }

//////////remover////////
    void rmUser(std::string username){
        users.erase(username);
    }

};

int main(){
    Controller c;
    c.addUser("samuel");
    
}