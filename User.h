//  User.h
//  The Q Factor
//  Created by Leo N. on 11/27/16.
//  Copyright © 2016 Leo Neto. All rights reserved.
//  Applying Inheritance...


#ifndef User_h
#define User_h
#include "Libraries.h"

class User{
    
    
    private:
    std::string name;
    std::string ocupation;
    int age;
    bool admin;
    
    
    
    public:
    User(){
        User::name = "Anonymous";
        User::age = 10;
        
    }//constructor
    
    
    void setName(std::string name){
        Manager::name = name;
    }
    
    void setAge(int age){
        Manager::age = age;
    }
    
    
    std::string getName(){
        return name;
    }
    int getAge(){
        return age;
    }
    
    
    
    
    void SetManager(){
        std::string input;
        std::string name;
        std::string language;
        std::stringstream temporary;
        int age;
        
        
        std::cout << "What is your full name? ";
        getline(std::cin, name);
        setName(name);
        
        std::cout << "What is your age? ";
        getline(std::cin, input);
        
        while(age > 119 & age < 5){
            std::cout << "Please enter a valid age: ";
            getline(std::cin, input);
            temporary << input;
            temporary >> age;
            setAge(age);
        }
        
        std::cout <<""<< std::endl;
        std::cout << "You're all set, "<<getName()<<". Now you can manage the program."<<std::endl;
        std::cout <<""<< std::endl;
        std::cout <<"-------------------------------"<< std::endl;
    }
    
    
    
    void SetPlayer(Player P){
        
        int age;
        std::stringstream temporary;
        std::string playername, feedback;
        
        
        std::cout << "What is the player's name? ";
        getline(std::cin, playername);
        P.setPlayerName(playername);
        
        
        std::cout << "How old is the player? ";
        getline(std::cin, feedback);
        
        while(age > 119 & age < 5){
            std::cout << "Please enter a valid age: ";
            getline(std::cin, feedback);
            temporary << feedback;
            temporary >> age;
            P.setPlayerAge(age);
        }
        
        std::cout <<""<< std::endl;
        std::cout << "Alright, "<<P.getPlayerName()<<" has been set up and is ready to play."<<std::endl;
    }//end Introductions()
    
    
};














#endif /* User_h */
