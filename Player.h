//
//  Player.h
//  The Q Factor
//
//  Created by Leo N. on 11/21/16.
//  Copyright © 2016 Leo Neto. All rights reserved.
//

#ifndef Player_h
#define Player_h
#include "Libraries.h"


class Player{
    
    private:
    
    // Integers and Booleans
    int playerage;
    int playerscore;
    //int srand(time(NULL));
    bool correctAnswer;
    
    
    // Strings
    std::string playername;
    std::string playerlanguage;
    std::string playeranswer;
    std::string feedback;
    
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    
    
    public:
    // Contructors
    Player(){
        playerscore = 0;
    }//NULL constructor
    
    Player(std::string username, int age){
        Player::playername = username;
        Player::playerage = age;
    }//end User constructor
    // *** end Contructors
    ~Player(){
        
    }//destructor
    
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    
    void SetPlayer(){
        
        std::cout << "What is your name: ";
        getline(std::cin, playername);
        
        std::cout <<""<< std::endl;
        std::cout << "Alright, "<<getPlayerName()<<". You're all set to take the quiz."<<std::endl;
    }//end SetPlayer()
    
    
    // *** Name Methods
    void setPlayerName(std::string username){
        Player::playername = username;
    }//end setName(); no return
    std::string getPlayerName(){
        return playername;
    }//end getUserName(); returns name
    // *** end Name Methods
    
    
    
    
    
    // *** Language Methods
    void setPlayerLanguage(std::string userlanguage){
        Player::playerlanguage = userlanguage;
    }//end setUserLanguage();
    std::string getPlayerLanguage(){
        return playerlanguage;
    }//end getUserLanguage();
    // **** end Langauge Methods
    
    
    
    
    // *** Age Methods
    void setPlayerAge(int userage){
        Player::playerage = userage;
    }//end setUserAge();
    int getPlayerAge(){
        return playerage;
    }//end getUserAge();
    // *** end Age Methods
    
    
    
    
    
    // *** Answer Methods
    void setPlayerAnswer(std::string answer){
        Player::playeranswer = answer;
    }//end setUserAnswer
    std::string getPlayerAnswer(){
        return playeranswer;
    }//end get UserAnswer();
    //*** end Answer Methods
    
    
    
    
    
    // *** Feedback Methods
    void setPlayerFeedback(std::string feedback){
        Player::feedback = feedback;
    }//end setUserAnswer
    std::string getPlayerFeedback(){
        return feedback;
    }//end get UserAnswer();
    //*** end Feedback Methods
    
    
    
    
    // *** Score Methods
    void IncreaseScore(){
        Player::playerscore++;
    }//end setUserScore()
    
    int getPlayerScore(){
        return playerscore;
    }//end setUserScore()
    
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    
    
    
    void Greet(){
        if(getPlayerAge()>9 & getPlayerAge()<39){
            std::cout <<"Hope you're ready for some prime time!"<<std::endl;
            std::cout <<"You can expect me to ask you questions from the past ";
            std::cout <<getPlayerAge()-2*2<<" years or so..."<<std::endl;
        } // Older than 9, younger than 39
        
        
        else if(getPlayerAge()>=39){
            std::cout <<getPlayerAge()<<" uh...? ";
            std::cout <<"Quite a journey on your shoes!"<<std::endl;
            std::cout <<"Don't worry, you've lived long enough to know the answers to these questions."<<std::endl;
        }// Older than 39
        
        
        else if(getPlayerAge()<=9){
            std::cout <<"You are quite a young fellow to play this game."<<std::endl;
            std::cout <<"Alright, I'll have to only ask you questions from the past ";
            std::cout <<getPlayerAge()<<" years." <<std::endl;
        } // Younger and equal to 9 years of age.
    }//end Greet()
    

    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    
    
    void isCorrect(){
        long long randomized = rand()%700;
        
        if((randomized)%2 == 0){
                std::cout <<"Well done!"<<std::endl;
        }else if(randomized%3 == 0){
                std::cout <<"Young and bright!"<<std::endl;
        }else if(randomized%5 == 0){
                std::cout<<"Correct is an understatement. Well done!"<<std::endl;
        }else if((randomized)%7 == 0){
                std::cout <<"Yeah, make me proud...!"<<std::endl;
        }else if(randomized%2 == 1){
                std::cout <<"I'm sure you've been reading a lot!"<<std::endl;
        }else if((randomized)%3 == 1){
                std::cout <<"Experience has it all!"<<std::endl;
        }else if(randomized%5 == 1){
                std::cout <<"Exactly what I expected!"<<std::endl;
        }else if(randomized%7 == 1){
                std::cout <<"Overflowing knowledge..."<<std::endl;
        }else{
                std::cout <<"That is absolutely correct!"<<std::endl;
        }
    }//end isCorrect()
    
    

    void isWrong(){
        long long randomized = rand()%700;
        
        if((randomized)%2 == 0){
                std::cout <<"Not, quite."<<std::endl;
        }else if(randomized%3 == 0){
                std::cout <<"Not exactly what either of us expected."<<std::endl;
        }else if(randomized%5 ==0){
                std::cout <<"Even I knew that..."<<std::endl;
        }else if(randomized%7 == 0){
                std::cout <<"No experience, uh!?"<<std::endl;
        }else if(randomized%2 == 1){
                std::cout <<"Well, you should have googled that..."<<std::endl;
        }else if(randomized%3 == 1){
                std::cout <<"Tricky, uh!?"<<std::endl;
        }else if(randomized%5 == 1){
                std::cout <<"Sorry you missed that."<<std::endl;
        }else{
            std::cout <<"Let's keep trying to get one right..."<<std::endl;
        }
    }//end isWrong()
    
    
    
};//endof Player
#endif /* Player_h */
