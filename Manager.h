//
//  Manager.h
//  The Q Factor
//
//  Created by Leo N. on 11/21/16.
//  Copyright © 2016 Leo Neto. All rights reserved.
//

#ifndef Manager_h
#define Manager_h
#include "Libraries.h"
#include "Player.h"

class Manager{
    
    private:
    int age;
    std::string name;
    std::string ocupation;
    
    public:
    Manager(){
        Manager::name = "Anonymous";
        Manager::age = 0;
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
    
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    
    void SetManager(){
        std::string input;
        std::string name;
        std::string language;
        std::stringstream temporary;
        
        
        std::cout << "What is your full name? ";
        getline(std::cin, name);
        setName(name);
        
        std::cout <<""<< std::endl;
        std::cout << "You're all set, "<<getName()<<". Now you can manage the program."<<std::endl;
        std::cout <<""<< std::endl;
        std::cout <<"-----------------------------------------------------------------"<< std::endl;
    }
    
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    
    // Passing Player by reference.
    // This function sets information regarding the player
    void SetPlayer(Player &P){
    
        std::string playername;
        
        std::cout << "What is the player's name? ";
        getline(std::cin, playername);
        P.setPlayerName(playername);
        
        std::cout <<""<< std::endl;
        std::cout << "Alright, "<<P.getPlayerName()<<" is all set to take the quiz."<<std::endl;
    }//end SetPlayer()
    
    
};

#endif /* Manager_h */
