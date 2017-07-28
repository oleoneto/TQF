//  Info.h
//  The Q Factor
//  Created by Leo N. on 11/28/16.
//  Copyright © 2016 Leo Neto. All rights reserved.


#ifndef Quiz_h
#define Quiz_h
#include "Libraries.h"
#include "Player.h"


class Quiz{
    
    
    private:
    int QuizTotalQuestions;
    std::string QuizTopic, QuizLanguage;
    
    
    
    public:
    Quiz(){
        QuizTopic = "No topic";
        QuizLanguage = "No languague";
        QuizTotalQuestions = 0;
    }//constructor
    
    ~Quiz(){
    }//destructor
    
    
    
    // Super setter for Quiz object. This sets the topic,
    // the language, and total number of question for the quiz.
    void SetQuizInfo(std::string input){
        
        int length;
        std::string storage;
        std::stringstream QuestionInfo, temporary;
        QuestionInfo << input;
        
        // Language, Topic, and Length...
        getline(QuestionInfo, storage, ',');
        //Questions::QuestionLanguage = storage;
        setQuizLanguage(storage);
        
        getline(QuestionInfo, storage, ',');
        //Questions::QuestionTopic = storage;
        setQuizTopic(storage);
        
        getline(QuestionInfo, storage);
        temporary << storage;
        temporary >> length;
        setQuizTotalQuestions(length);
    }//end SetQuizInfo
    
    
    
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //***** Set Methods
    
    void setQuizTopic(std::string topic){
        Quiz::QuizTopic = topic;
    }
    void setQuizLanguage(std::string lang){
        Quiz::QuizLanguage = lang;
    }
    void setQuizTotalQuestions(int num){
        Quiz::QuizTotalQuestions = num;
    }
    
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //***** Get Methods..
    
    std::string getQuizTopic(){
        return QuizTopic;
    }
    std::string getQuizLanguage(){
        return QuizLanguage;
    }
    int getQuizTotalQuestions(){
        return QuizTotalQuestions;
    }
    
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //***** Other Methods..
    
    void PrintQuizInfo(){
        std::cout<<""<<std::endl;
        std::cout<<"Language: "<<QuizLanguage<<std::endl;
        std::cout<<"Subject: "<<QuizTopic<<std::endl;
        std::cout<<"Total Questions: "<<QuizTotalQuestions<<std::endl;
        std::cout<<""<<std::endl;
    }
    
    void Help(){
        std::cout<<""<<std::endl;
        std::cout<<"***** Help menu ******"<<std::endl;
        std::cout<<"You can answer most questions by simply typing Yes or No."<<std::endl;
        std::cout<<"For most interactions, you can type the first letter of your desired option as answer."<<std::endl;
        std::cout<<"i.e P for Player, M for Manager... Q for Quit, L for Load, R for Run..."<<std::endl;
        std::cout<<"--------"<<std::endl;
        std::cout<<"During a quiz, type either of the letters a, b, c, or d to answer a question."<<std::endl;
        std::cout<<"If during a quiz you feel like quitting, you may do so by pressing Q."<<std::endl;
        std::cout<<"Your game will be saved and you may be able to reload from it next time the program runs."<<std::endl;
        std::cout<<"--------"<<std::endl;
        std::cout<<"If you are managing a quiz, you will be able to create a program report after each quiz."<<std::endl;
        std::cout<<"This will help you see all the answers in context as well the percentage of wrong and correct answers."<<std::endl;
        std::cout<<"***** End *****"<<std::endl;
        std::cout<<""<<std::endl;
    }
    
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    
};

#endif /* Quiz_h */
