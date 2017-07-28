//
//  Questions.h
//  The Q Factor
//
//  Created by Leo N. on 11/21/16.
//  Copyright © 2016 Leo Neto. All rights reserved.
//

#ifndef Questions_h
#define Questions_h
#include "Libraries.h"

class Questions{
    
    private:
    
    //integers and booleans
    bool is_correct;
    
    //Strings
    std::string OptionA, OptionB, OptionC, OptionD;
    std::string question, correctOption, playeranswer;
    
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
    //*************************************************
    //*************************************************
    
    
    public:
    
    Questions(){
        Questions::question = "No questions here.";
        Questions::OptionA = "No options to display.";
        Questions::OptionB = "No options to display.";
        Questions::OptionC = "No options to display.";
        Questions::OptionD = "No options to display.";
        Questions::correctOption = "No answer available.";
    }//constructor
    
    
    ~Questions(){
    
     }//destructor
    
    
    // The question constructor should take in two strings and an integer.
    // The strings will be the question itself and the multiple choice answer.
    // The integer will be the index of the correct answer.
    void setQuestions(std::string Question, std::string a, std::string b,
                      std::string c, std::string d, std::string CorrectAnswer){
        Questions::question = Question;
        Questions::OptionA = a;
        Questions::OptionB = b;
        Questions::OptionC = c;
        Questions::OptionD = d;
        Questions::correctOption = CorrectAnswer;
    }//Questions
    
    
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
    //***** Setters for Questions *****/
    
    
    void setPlayerAnswer(std::string ans){
        Questions::playeranswer = ans;
    }
    void setQuestion(std::string question){
        Questions::question = question;
    }
    void setOptionA(std::string a){
        Questions::OptionA = a;
    }
    void setOptionB(std::string b){
        Questions::OptionB = b;
    }
    void setOptionC(std::string c){
        Questions::OptionC = c;
    }
    void setOptionD(std::string d){
        Questions::OptionD = d;
    }
    void setAnswer(std::string answer){
        Questions::correctOption = answer;
    }
    
    
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //********* Getters ********/
    
    
    std::string getQuestion(){
        return question;
    }
    std::string getOptions(){
        return OptionA;
        return OptionB;
        return OptionC;
        return OptionD;
    }
    std::string getOptionA(){
        return OptionA;
    }
    std::string getOptionB(){
        return OptionB;
    }
    std::string getOptionC(){
        return OptionC;
    }
    std::string getOptionD(){
        return OptionD;
    }
    std::string getAnswer(){
        return correctOption;
    }
    std::string getCorrectAnswer(){
        std::string answer;
        if(this->correctOption=="a"){
            answer = OptionA;
        }else if (this->correctOption=="b"){
            answer = OptionB;
        }else if (this->correctOption=="c"){
            answer = OptionC;
        }else if (this->correctOption=="d"){
            answer = OptionD;
        }
        return answer;
    }
    
    std::string getCorrectOption(){
        return correctOption;
    }
    
    std::string getPlayerAnswer(){
        return playeranswer;
    }
    
    
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*** Other Methods..
    
    // This prints a question and its four options.
    // To be used if index of question is not to be shown.
    void PrintMe(){
        std::cout<<Questions::question<<std::endl;
        std::cout<<Questions::OptionA<<std::endl;
        std::cout<<Questions::OptionB<<std::endl;
        std::cout<<Questions::OptionC<<std::endl;
        std::cout<<Questions::OptionD<<std::endl;
    }//end PrintMe()
    
    
    // This prints a question and its four options. QuestionIndex is
    // used to print the number of a question when it is printed.
    void PrintMe(int QuestionIndex){
        std::cout<<QuestionIndex<<". ";
        std::cout<<Questions::question<<std::endl;
        std::cout<<Questions::OptionA<<std::endl;
        std::cout<<Questions::OptionB<<std::endl;
        std::cout<<Questions::OptionC<<std::endl;
        std::cout<<Questions::OptionD<<std::endl;
        QuestionIndex++;
    }//end PrintMe(int)
    
    
    // This method checks if what the user enters as answer
    // Matches the predefined correct option.
    bool isThisCorrect(std::string useranswer){

        std::string correctanswer;
        correctanswer = getAnswer();
        if(useranswer == correctanswer){
            is_correct = true;
        }else{
            is_correct = false;
        }
        return is_correct;
    }//end isThisCorrect
    
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    
};//end Questions
#endif /* Questions_h */
