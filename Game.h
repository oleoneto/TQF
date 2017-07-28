//
//  Game.h
//  The Q Factor
//
//  Created by Leo N. on 11/21/16.
//  Copyright © 2016 Leo Neto. All rights reserved.
//

#ifndef Game_h
#define Game_h
#include "Libraries.h"
#include "Questions.h"
#include "Player.h"
#include "Manager.h"
#include "Quiz.h"

class Game{
    
    private:
    
    // Booleans and Numbers
    int Qindex;
    float ScorePercent;
    bool is_Manager;
    bool is_Player;
    bool nowPlaying;
    bool quitting;
    bool firstRun;
    bool reLoading;
    bool didEscape;
    bool returningUser;
    bool errorLoading;
    bool loadedPreviousQuiz;
    bool providedValidPath;
    bool didPrintQuizInfo;
    
    // Strings
    std::string pName, pLang, pAnswer, answer;
    std::string Feedback;
    std::string PreviousQuizPath;
    std::string CurrentQuizPath;
    
    // File Streams
    std::ifstream File;
    std::ifstream QuizPathIn;
    std::ifstream QuizInfoIn;
    std::ifstream RemainingQuestionsIn;
    std::ofstream Results;
    std::ofstream QuizProgress;
    std::ofstream QuizPathOut;
    std::ofstream QuizInfoOut;
    std::ofstream RemainingQuestionsOut;
    
    // Classes
    Player *P;
    Manager M;
    Questions Q;
    Questions *QA;
    Questions *AR;
    Quiz *QuizInfo;
    
    // Heap Arrays
    std::string *GameQuestions;
    
    
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    
    
    public:
    Game(){
        
        //Initializing Booleans
        is_Manager = false;
        is_Player = false;
        nowPlaying = true;
        quitting = false;
        firstRun = true;
        reLoading = false;
        didEscape = false;
        returningUser = false;
        errorLoading = false;
        loadedPreviousQuiz = false;
        providedValidPath = false;
        didPrintQuizInfo = false;
        
        //Initializing Player
        P = new Player;
        
    }//constructor
    
    ~Game(){
        
    }//desctructor
    
    // Instructions and Options...
    //*************************************************
    //*************************************************
    //*************************************************
    
    void FormatLines(){
        std::cout<<"--------------------------------------------------------------------------"<< std::endl;
    }//end FormatLines
    
    void Welcome(){
        FormatLines();
        std::cout<<"Welcome to The Q Factor, an \"open-souce\" program by Leo Neto."<<std::endl;
        FormatLines();
        EmptySpace();
    }//end Welcome
    
    
    void CheckReturningUser(){
        std::cout<<"Are you starting a new quiz? ";
        getline(std::cin, Feedback);
        
        YESorNO();
        
        if(Feedback=="Yes"){
            std::cout<<"Alright, let help you set up an new quiz."<<std::endl;
            EmptySpace();
        }//end if YES - starting a new quiz
        
        else if(Feedback=="No"){
            std::cout<<"If you quit in the middle of a quiz, would you like to pick up where you left off? ";
            getline(std::cin, Feedback);
            
            YESorNO();
            
            // Picking up where the user left off...
            if(Feedback=="Yes"){
                std::cout<<"Let me check your previous progress..."<<std::endl;
                
                int number, index;
                std::string Path, storage;
                std::stringstream temporary;
                
                
                QuizPathIn.open("LastPath.tqf");
                if(QuizPathIn.is_open()){
                    getline(QuizPathIn, Path);
                    CurrentQuizPath = Path;
                    QuizInfo = new Quiz[1];
                    QuizPathIn.close();
                }else{
                    //std::cout<<"I couln't find any files from last time..."<<std::endl;
                    errorLoading = true;
                }//end if-else path is open
                
                
                QuizInfoIn.open("QuizInfo.tqf");
                if(QuizInfoIn.is_open()){
                    getline(QuizInfoIn, storage);
                    QuizInfo[0].setQuizLanguage(storage);
                    
                    getline(QuizInfoIn, storage);
                    QuizInfo[0].setQuizTopic(storage);
                    
                    getline(QuizInfoIn, storage);
                    temporary << storage;
                    temporary >> number;
                    QuizInfo[0].setQuizTotalQuestions(number);
                    
                    temporary.clear();
                    
                    getline(QuizInfoIn, storage);
                    temporary << storage;
                    temporary >> Qindex;
                    //Qindex;
                    
                    QuizInfoIn.close();
                    returningUser = true;
                }else{
                    std::cout<<"I couldn't find any files from last time..."<<std::endl;
                    errorLoading = true;
                }//end if-else info is open

                
                if(!errorLoading){
                    LoadPreviousQuiz();
                    is_Player = true;
                }
                
                
                if(errorLoading){
                    returningUser = false;
                    EmptySpace();
                    std::cout<<"Sorry, quiz progress could not be retrieved from file."<<std::endl;
                    std::cout<<"I can still run the program if you supply a file with the quiz."<<std::endl;
                    std::cout<<"Please, provide a path: ";
                    getline(std::cin, Feedback);
                    
                    LoadQuestions(Feedback);
                    EmptySpace();
                }
            }//end if picking up where user left off
            
            else{
                returningUser = false;
                EmptySpace();
                std::cout<<"Oh, okay! I'll run the default version of the program, then."<<std::endl;
                EmptySpace();
                LoadDefaultQuestions();
            }

        }//end else-if not starting a new quiz
        
    }//end CheckReturningUser
    
    
    void LoadPreviousQuiz(){
        int counter, index;
        std::string content;
        std::stringstream temporary;
        
        File.open("RemainingQuestions.tqf");
        
        counter = 0;
        
        // This is used instead of a fixed number,
        // to help with flexibility and portability...
        QA = new Questions[QuizInfo[0].getQuizTotalQuestions()];
        
        for(index=0; index<=(QuizInfo[0].getQuizTotalQuestions()); index++){
            
            if(File.is_open()){
                getline(File, content);
                QA[index].setQuestion(content);
                getline(File, content);
                QA[index].setOptionA(content);
                getline(File, content);
                QA[index].setOptionB(content);
                getline(File, content);
                QA[index].setOptionC(content);
                getline(File, content);
                QA[index].setOptionD(content);
                getline(File, content);
                QA[index].setAnswer(content);
        
                errorLoading = false;
                returningUser = true;
                loadedPreviousQuiz = true;
                providedValidPath = true;
            }else{
                std::cout<<"I couldn't find the file with your progress."<<std::endl;
                errorLoading = true;
                returningUser = false;
            }
        }
        
        CurrentQuizPath = "RemainingQuestions.tqf";
        File.close();
        //is_Player = true;
    }//end LoadPreviousQuiz
    
    
    void FirstInstructions(){
        std::cout<<"The Q Factor will allow you to setup quizzes for students, friends,";
        std::cout<<"family members"<<std::endl;
    }//end FirstInstructions
    
    
    
    void PlayerInstructions(){
        std::cout << "To answer a question just type any of the letters a, b, c, or d"<<std::endl;
        std::cout << "After answering a question, you'll be told whether or not you are correct."<<std::endl;
    }//end ShortInstructions()
    
    //*************************************************
    //*************************************************
    //*************************************************
    
    
    void GameRole(){
        
        std::cout <<"Please provide some information about yourself."<<std::endl;
        std::cout <<"Do you want to run the program as a (P)Player or as a (M)Manager? ";
        getline(std::cin, Feedback);
        
        if(Feedback=="both" || Feedback=="Both"){
            std::cout<<"I understand you're not Java but please slow down..."<<std::endl;
            EmptySpace();
        }
        
        
        if(Feedback=="manager" | Feedback=="Manager" | Feedback =="m"){
            Feedback = "M";
        }else if(Feedback =="player" | Feedback=="Player" | Feedback =="p"){
            Feedback = "P";
        }
        
        while(Feedback!="P" & Feedback!="M"){
            std::cout << "Try P for Player, or M for Manager: ";
            getline(std::cin, Feedback);
        }
        
        if(Feedback=="P"){
            P->SetPlayer();
            PlayerInstructions();
            if(!providedValidPath){
                LoadDefaultQuestions();
            }
        }else if(Feedback=="M"){
            M.SetManager();
            ManagerInstructions();
            ManagerPath();
        }
    }//end GameRole()
    
    
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    
    
    void ManagerInstructions(){
        
        if(providedValidPath){
            std::cout<<"Let's make sure your quiz is setup correctly."<<std::endl;
        }
        else{
            std::cout<<"As a manager you can set up the program for others."<<std::endl;
            std::cout<<"You can choose whether the program runs with the standard 17 questions,"<<std::endl;
            std::cout<<"or you can supply your own data file."<<std::endl;
            
            EmptySpace();
            std::cout << "You can choose to either:"<<std::endl;
            std::cout << "LOAD questions from your own file, or"<<std::endl;
            std::cout << "RUN the standard version of the quiz."<<std::endl;
        }
    }//end ManagerInstructions
    
    
    void ManagerPath(){
      is_Manager = true;
        
      if(!providedValidPath){
      
            // If it is the first time running the program
            // ask the manager whether they want to load a custom file
            // Set FirstRun to true.
            if(firstRun){
                EmptySpace();
                
                std::cout <<"What will it be? ";
                getline(std::cin, Feedback);
            
                if(Feedback=="Load" | Feedback == "load" | Feedback == "LOAD" | Feedback=="l"){
                    Feedback = "L";
                }else if(Feedback=="Run" | Feedback == "run" | Feedback == "RUN" | Feedback == "r"){
                    Feedback = "R";
                }
                
                while(Feedback !="L" & Feedback != "R"
                      & Feedback !="l" & Feedback !="r"){
                    std::cout <<"Type L to load, or R to run: ";
                    getline(std::cin, Feedback);
                }
            }//end if FirstRun
          
            // If it is not the first time the program has run
            // Ask the manager whether they want to retake the previous quiz
            if(!firstRun){
                std::cout<<"Do you want to RELOAD the previous quiz? ";
                getline(std::cin, Feedback);
                
                YESorNO();
                
                if(Feedback=="Yes"){
                    reLoading = true;
                }else{
                    std::cout<<"Do you want to load a NEW quiz? ";
                    getline(std::cin, Feedback);
                    
                    YESorNO();
                    
                    if(Feedback=="No"){
                        std::cout<<"Terminating the program..."<<std::endl;
                    }else{
                        Feedback = "L";
                    }
                }
                
                EmptySpace();
            }
            

            if(reLoading){
                Feedback = "L";
                LoadQuestions(PreviousQuizPath);
            }

            
            if(!reLoading){
            
                if(Feedback == "L"){
                    
                    std::cout <<"Type the path of the file (i.e. \"/Users/John/Documents/file.csv\"):"<<std::endl;
                    getline(std::cin, Feedback);
                    
                    File.open(Feedback);
                    std::cout<<""<<std::endl;
                    
                    while(!File.is_open()){
                        std::cout <<""<< std::endl;
                        std::cout <<"File NOT Found."<<std::endl;
                        std::cout <<"Type the path of the file: ";
                        getline(std::cin, Feedback);
                        std::cout<<"The path you chose is: "<<Feedback<<std::endl;
                        File.open(Feedback);
                    }
                    
                    PreviousQuizPath = Feedback;
                    
                    if(firstRun){
                        // Close file to open later.
                        File.close();
                        LoadQuestions(Feedback);
                        //SetQuestionsArray();
                        
                        FormatLines();
                        std::cout <<"The Program is ready to run..."<<std::endl;
                        std::cout <<"Now you'll need to set up a player to play the program."<<std::endl;
            
                        EmptySpace();
                        SetPlayer();
                        is_Player = true;
                    }
                    
                }else{
                    
                    LoadDefaultQuestions();
                    //SetQuestionsArray();
                    
                    SetPlayer();
                    std::cout <<""<< std::endl;
                    FormatLines();
                    std::cout <<"Running default version..."<<std::endl;
                }
                    FormatLines();
            }//end if Not Reloading
        
        }//end if NOT loaded from a previous quiz
        
      else{
          FormatLines();
          std::cout <<"The Program is ready to run..."<<std::endl;
          std::cout <<"Now you'll need to set up a player to play the program."<<std::endl;
          
          EmptySpace();
          SetPlayer();
          is_Player = true;
      }
        
      firstRun = false;
        
    }//end ManagerInstructions()
    
    
    void SetPlayer(){
        
        std::string playername;
        
        std::cout << "What is the player's name? ";
        getline(std::cin, playername);
        P->setPlayerName(playername);
        
        std::cout <<""<< std::endl;
        std::cout << "Alright, "<<P->getPlayerName()<<" is all set to take the quiz."<<std::endl;
    }//end SetPlayer
    
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
    
    void LoadDefaultQuestions(){
        
        CurrentQuizPath = "code.tqf";
        QuizPathOut.open("LastPath.tqf");
        
        if(QuizPathOut.is_open()){
            QuizPathOut << CurrentQuizPath <<std::endl;
            QuizPathOut.close();
        }
        
        
        
        int counter, index;
        std::string content;
        std::stringstream temporary;
        
        //Info: Language, Topic, Total Questions
        QuizInfo = new Quiz[1];
        
        File.open("code.tqf");
        
        // This takes care of the first line
        // which has the format: English, Biology, 25
        // This iteration will store "English, Biology, 25"
        // into one single string.
        // This string will be parsed into three variables:
        // Language, Topic, and TotalQuestions...
        // TotalQuestions will be used to iterate through with getline
        // the total number of questions times 6, as seen in the for-loop
        
        counter = 0;
        if(File.is_open()){
            if(counter==0){
                getline(File, content);
                QuizInfo[0].SetQuizInfo(content);
                
                // Test printing...
                // std::cout<<"Loading..."<<std::endl;
                // QuizInfo[0].PrintQuizInfo();
                counter++;
            }
        }
        
        while(QuizInfo[0].getQuizTotalQuestions()<=0){
            std::cout<<"Something is wrong. The default file was moved."<<std::endl;
            std::cout<<"Please provide a valid path to a quiz file: ";
            getline(std::cin, Feedback);
            
            File.open(Feedback);
            if(File.is_open()){
                getline(File, content);
                QuizInfo[0].SetQuizInfo(content);
            }
            
            // Test printing...
            std::cout<<"Data Loaded..."<<std::endl;
            QuizInfo[0].PrintQuizInfo();
            didPrintQuizInfo=true;
            EmptySpace();
        }
        
        
        
        // This is used instead of a fixed number,
        // to help with flexibility and portability...
        QA = new Questions[QuizInfo[0].getQuizTotalQuestions()];
        
        for(index=0; index<=(QuizInfo[0].getQuizTotalQuestions()); index++){
            
            // This should not be here... Placing it above the initialization of the for-loop.
            // QA = new Questions[QuizInfo[0].getQuizTotalQuestions()];
            
            if(File.is_open()){
                getline(File, content);
                QA[index].setQuestion(content);
                getline(File, content);
                QA[index].setOptionA(content);
                getline(File, content);
                QA[index].setOptionB(content);
                getline(File, content);
                QA[index].setOptionC(content);
                getline(File, content);
                QA[index].setOptionD(content);
                getline(File, content);
                QA[index].setAnswer(content);
                
                // Testing output from input.
                // std::cout<<index<<".[LQ]: "<<QA[index].getQuestion()<<std::endl;
                
                errorLoading = false;
                providedValidPath = true;
            }else{
                std::cout<<"Default file NOT in directory."<<std::endl;
                while(!File.is_open()){
                    std::cout<<"Please provide another path for the quiz file: ";
                    getline(std::cin, Feedback);
                    File.open(Feedback);
                    errorLoading = true;
                }
            }//end if-else
        }//end for-loop
        
        CurrentQuizPath = "code.tqf";
        File.close();
    }//end LoadQuestions
    
    
    void LoadQuestions(std::string Path){
        
        CurrentQuizPath = Path;
        QuizPathOut.open("LastPath.tqf");
        QuizPathOut.close();
        
        int counter, index;
        std::string content;
        std::stringstream temporary;
        
        //Info: Language, Topic, Total Questions
        QuizInfo = new Quiz[1];
        File.open(Path);
        
        counter = 0;
        if(File.is_open()){
            
            if(counter==0){
                getline(File, content);
                QuizInfo[0].SetQuizInfo(content);
                
                // Test printing...
                std::cout<<"Data Loaded..."<<std::endl;
                QuizInfo[0].PrintQuizInfo();
                didPrintQuizInfo=true;
                std::cout<<""<<std::endl;
                counter++;
            }
        }else{
            std::cout<<"File NOT found"<<std::endl;
            errorLoading = true;
        }
        
        
        while(QuizInfo[0].getQuizTotalQuestions()<=0){
            std::cout<<"File NOT found."<<std::endl;
            std::cout<<"Please provide a valid path to your quiz file: ";
            getline(std::cin, Feedback);
            CurrentQuizPath = Feedback;
            
            File.open(Feedback);
            if(File.is_open()){
                getline(File, content);
                QuizInfo[0].SetQuizInfo(content);
            }
            
            // Test printing...
            std::cout<<"Data Loaded..."<<std::endl;
            QuizInfo[0].PrintQuizInfo();
            didPrintQuizInfo=true;
            EmptySpace();
        }
        
        
        // This is used instead of a fixed number,
        // to help with flexibility and portability...
        QA = new Questions[QuizInfo[0].getQuizTotalQuestions()];
        
        for(index=0; index<=(QuizInfo[0].getQuizTotalQuestions()); index++){
            
            if(File.is_open()){
                getline(File, content);
                QA[index].setQuestion(content);
                getline(File, content);
                QA[index].setOptionA(content);
                getline(File, content);
                QA[index].setOptionB(content);
                getline(File, content);
                QA[index].setOptionC(content);
                getline(File, content);
                QA[index].setOptionD(content);
                getline(File, content);
                QA[index].setAnswer(content);
                
                errorLoading = false;
                providedValidPath = true;
                
            }else{
                std::cout<<"File NOT Open."<<std::endl;
                errorLoading = true;
            }
        }
        
        if(QuizPathOut.is_open()){
            QuizPathOut << CurrentQuizPath <<std::endl;
            QuizPathOut.close();
        }
        
        
        File.close();
    }//end LoadQuestions
    
    
    void ValidateAnswer(std::string useranswer){
        
        while(useranswer!="a" && useranswer!="b" && useranswer!="c" && useranswer!="d"){
            
            if(useranswer=="Q" || useranswer=="q" ||
               useranswer=="quit" || useranswer=="Quit" ||
               useranswer=="exit" || useranswer=="Exit"){
                nowPlaying=false;
                quitting=true;
                QuitBeforeTime();
                break;
            }
            
            std::cout<<"Invalid answer. Try either a, b, c, or d: ";
            getline(std::cin, useranswer);
        }//end while
        
    }//end ValidateAnswer
    
    
    void VerifyAndShout(){
        // If isThisCorrect returns true, increment score.
        // If isThisCorrect returns false, do nothing.
        if(QA[Qindex].isThisCorrect(pAnswer)){
            if(!quitting){
                P->IncreaseScore();
                if(!is_Manager){
                    P->isCorrect();
                }
            }else{
                std::cout<<"That was correct, why are you quitting?"<<std::endl;
            }
        }else{
            if(!quitting){
                if(!is_Manager){
                    P->isWrong();
                }
            }else{
                std::cout<<"Wrapping up now..."<<std::endl;
            }
        }
    }//end VerifyAndShout
    
    
    void EndQuiz(){
        if(Qindex==(QuizInfo[0].getQuizTotalQuestions())-1){
            nowPlaying = false;
            if(is_Manager){
                ManagerReport();
            }else{
                AnotherQuiz();
            }
        }else{
            Qindex++;
        }
    }//end EndQuiz
    
    
    void ScoreReport(){
        std::cout<<""<<std::endl;
        std::cout<<"Final score ";
        std::cout<<P->getPlayerScore();
        std::cout<<" points."<<std::endl;
        std::cout<<""<<std::endl;
        FormatLines();
        
        //Percent Calculator...
        //ScorePercent = (P->getPlayerScore()/QuizInfo[0].getQuizTotalQuestions())*100;
    }//end ScoreReport
    
    
    void YESorNO(){
        while(Feedback!="Yes" && Feedback!="YES" && Feedback!="yes" && Feedback!="Y" && Feedback!="y" && Feedback!="YEAH" &&
              Feedback!="Yep" && Feedback!="Yeah" && Feedback!="yeah" && Feedback!="yep" && Feedback!="YEP" &&
              Feedback!="No" && Feedback!="NO" && Feedback!="no" && Feedback!="N" && Feedback!="n" &&
              Feedback!="Nope" && Feedback!="nope" && Feedback!="NOPE"){
            
            std::cout<<"Invalid input. Try YES, or NO: ";
            getline(std::cin, Feedback);
        }
        if(Feedback=="YES" || Feedback=="YEP" || Feedback=="Yeah" || Feedback=="Yes" || Feedback=="Yep" || Feedback=="yes" || Feedback=="Y" || Feedback=="y" || Feedback=="yeah" || Feedback=="yep" || Feedback=="YEAH"){
            Feedback = "Yes";
        }else if(Feedback=="No" || Feedback=="NO" || Feedback=="no" || Feedback=="N" || Feedback=="n" || Feedback=="nope" || Feedback=="Nope" || Feedback=="NOPE"){
            Feedback = "No";
        }
    }//end YESorNO
    
    
    void ManagerReport(){
        if(is_Manager){
            EmptySpace();
            FormatLines();
            std::cout<<"Hello again, "<<M.getName()<<"!"<<std::endl;
            std::cout<<"The quiz is over. Would you like to save the results to a file? ";
            getline(std::cin, Feedback);
            
            YESorNO();
            
            if(Feedback=="Yes"){
                // Output stream...
                int counter, index;
                Results.open("REPORT-"+P->getPlayerName()+".tqf", std::ofstream::app);
                if(!Results.is_open()){
                    Results.open("REPORT-"+P->getPlayerName()+".tqf");
                }
                
                if(Results.is_open()){
                    for(counter=0, index=0; counter<QuizInfo[0].getQuizTotalQuestions(); counter++, index++){
                        
                        if(counter==0){
                            Results << "-----------------------------------------------------"<<std::endl;
                            Results << "Quiz results for " << P->getPlayerName() <<"."<<std::endl;
                            Results << "Administered by " << M.getName()<<std::endl;
                            Results << "Quiz Topic: " << QuizInfo[0].getQuizTopic()<<std::endl;
                            Results << "Total Number of Questions: " << QuizInfo[0].getQuizTotalQuestions()<<std::endl;
                            Results << "-----------------------------------------------------"<<std::endl;
                        }
                        
                        Results << AR[index].getQuestion()<<std::endl;
                        Results <<"Correct: "<< QA[index].getCorrectAnswer()<<std::endl;
                        Results <<"Answered: "<<AR[index].getPlayerAnswer()<<std::endl;
                        Results << " "<<std::endl;
                        
                        if(counter==(QuizInfo[0].getQuizTotalQuestions())-1){
                            Results <<"Final Score: "<<P->getPlayerScore()<<" out of "<<QuizInfo[0].getQuizTotalQuestions()<<std::endl;
                        }
                    }
                    Results.close();
                    EmptySpace();
                    EmptySpace();
                    FormatLines();
                    std::cout<<"Report saved."<<std::endl;
                    FormatLines();
                    
                }else{
                    std::cout<<"Error writing to file."<<std::endl;
                    FormatLines();
                }
            }
        
            //ANOTHER QUIZ...
            AnotherQuiz();
            
        }//if is_Manager
        
    }//end ManagerReport
    
    
    void AnotherQuiz(){
        EmptySpace();
        std::cout<<"Alright, the quiz is now over. Would you like to setup another quiz? ";
        getline(std::cin, Feedback);
        
        YESorNO();
        
        if(Feedback=="Yes"){
            nowPlaying = true;
            Qindex = 0;
            
            std::cout <<"Type the path of the file (i.e. \"/Users/John/Documents/file.txt\"):"<<std::endl;
            getline(std::cin, Feedback);
            
            File.open(Feedback);
            EmptySpace();
            
            while(!File.is_open()){
                EmptySpace();
                std::cout <<"The given file could NOT be found."<<std::endl;
                std::cout <<"Please type a valid path for the next quiz: ";
                getline(std::cin, Feedback);
                std::cout<<"The path you chose is: "<<Feedback<<std::endl;
                File.open(Feedback);
            }
            
            File.close();
            PreviousQuizPath = Feedback;
            LoadQuestions(Feedback);
            
        }else{
            FormatLines();
            std::cout<<"Ok! Ending program now..."<<std::endl;
            FormatLines();
            EmptySpace();
        }
    }//end AnotherQuiz
    
    
    void SetAnswersArray(){
        AR = new Questions[QuizInfo[0].getQuizTotalQuestions()];
    }//end SetAnswersArray
    
    
    void AppendAnswer(){
        AR[Qindex].setQuestion(QA[Qindex].getQuestion());
        AR[Qindex].setPlayerAnswer(pAnswer);
    }//end AppendAnswer
    
    
    void QuitBeforeTime(){
        
        int counter, index;
        
        // If the user quits before time, we'll start the quiz
        QuizProgress.open("QuizProgress.tqf");
        Results.open("QuizAnswers.tqf");
        RemainingQuestionsOut.open("RemainingQuestions.tqf");
        QuizInfoOut.open("QuizInfo.tqf");
        
        EmptySpace();
        if(QuizProgress.is_open()){
            QuizProgress << Qindex <<std::endl;
            std::cout<<"Your progress was saved for when you come back..."<<std::endl;
            QuizProgress.close();
        }else{
            std::cout<<"Your progress could not be saved..."<<std::endl;
        }
        
        
        if(Results.is_open()){
            
            for(counter=0; counter<Qindex; counter++, index++){

                Results << AR[counter].getQuestion()<<std::endl;
                Results <<"Correct: "<< QA[counter].getCorrectAnswer()<<std::endl;
                Results <<"Answered: "<<AR[counter].getPlayerAnswer()<<std::endl;
                
                if(counter==(QuizInfo[0].getQuizTotalQuestions())-1){
                    Results <<"Final Score: "<<P->getPlayerScore()<<" out of "<<QuizInfo[0].getQuizTotalQuestions()<<std::endl;
                }
            }//end for-loop
            Results.close();
            std::cout<<"Your answers to this quiz were saved."<<std::endl;

        }else{
            std::cout<<"Your answers could not be saved..."<<std::endl;
        }
        
        
        
        if(RemainingQuestionsOut.is_open()){
            
            // Get all the remaining questions, including the current at Qindex
            // since the user will not have answered the question from which they quit.
            for(counter=Qindex; counter<QuizInfo[0].getQuizTotalQuestions(); counter++){
                RemainingQuestionsOut << QA[counter].getQuestion()<< std::endl;
                RemainingQuestionsOut << QA[counter].getOptionA() << std::endl;
                RemainingQuestionsOut << QA[counter].getOptionB() << std::endl;
                RemainingQuestionsOut << QA[counter].getOptionC() << std::endl;
                RemainingQuestionsOut << QA[counter].getOptionD() << std::endl;
                RemainingQuestionsOut << QA[counter].getCorrectOption() << std::endl;
            }//end for-loop
            RemainingQuestionsOut.close();
            std::cout<<"The remaining questions were saved to a file."<<std::endl;
            
        }else{
            std::cout<<"The remaining questions could not be saved..." <<std::endl;
        }
        
        if(QuizInfoOut.is_open()){
            
            QuizInfoOut << QuizInfo[0].getQuizLanguage()<<std::endl;
            QuizInfoOut << QuizInfo[0].getQuizTopic()<<std::endl;
            
            // Number of questions left to answer...
            QuizInfoOut << QuizInfo[0].getQuizTotalQuestions()-Qindex<<std::endl;
            
            // Index of answer from which user quit...
            QuizInfoOut << Qindex <<std::endl;
            
            QuizInfoOut.close();
            std::cout<<"Quiz information saved..."<<std::endl;
        }else{
            std::cout<<"Quiz information could not be saved..."<<std::endl;
        }
        
    }// QuitBeforeTime...
    
    
    void FreeHeap(){
        delete P;
        delete [] QA;
        delete [] QuizInfo;
        delete [] AR;
    }//end FreeHeap
    
    
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    //*************************************************
    
    
    /*************************************************
     *************************************************
     *************************************************
     *************************************************
     *************************************************
     *************************************************
     
     Game runs here...
     
     How it works:
     We start off by outputing an empty line and then call the
     PrintQuestions() function which is part of the Questions class.
     PrintQuestions() will output a question followed by four possible answers.
     We then ask the user for an answer.
     Once the answer is received, we check to see if the input is valid.
     Valid inputs are a, b, c, d, and q. The latter quits the game.
     While the input is not valid we'll keep asking for a valid input.
     If the input matches the valid criteria, we'll check if the answer
     is correct by calling the Analyzer() function.
     
     *************************************************
     *************************************************
     *************************************************
     *************************************************
     *************************************************
     ***************************/
    
    
    void StartGame(){
        
        // Developer info...
        Welcome();
        
        // Check if the user is returning...
        // If the user is returning, we'll check for files in the directory
        // that hold information about the last time the program ran.
        // If that fails, an error will be collected.
        // That error is used to check if the game should run...
        CheckReturningUser();
       
        if(!errorLoading){
        
                if(!returningUser){
                    GameRole();
                    Qindex = 0;
                    if(!didPrintQuizInfo){
                        QuizInfo[0].PrintQuizInfo();
                    }
                }
            
            
                Qindex = 0;
            
                SetAnswersArray();
                std::cout<<""<<std::endl;
            
                if(returningUser){
                    std::cout<<"HERE'S YOUR QUIZ FROM LAST TIME..."<<std::endl;
                }
            
                else{
                    std::cout<<"THE QUIZ HAS STARTED..."<<std::endl;
                }
            
                while(nowPlaying){
                    
                    // Added spacing.
                    std::cout<<""<<std::endl;
                    
                    // Printing questions.
                    // This will be used to iterate though the arrays.
                    // PrintMe will output the question with its possible answers.
                    if(!returningUser){
                        QA[Qindex].PrintMe(Qindex+1);
                    }else{
                        QA[Qindex].PrintMe();
                    }
                    
                    // Input is taken here.
                    std::cout<<"Answer: ";
                    getline(std::cin, pAnswer);
                    
                    // Input validation.
                    // This will loop till input is valid.
                    ValidateAnswer(pAnswer);
                    
                    // Verify result.
                    // Tell the user how it went.
                    VerifyAndShout();
                    
                    // Write to AnswersArray - appending
                    AppendAnswer();
                    
                    // Quit condition...
                    EndQuiz();
                    
                }//end while loop
                
                // Reporting the score
                if(!is_Manager){
                    ScoreReport();
                }
        }//end if errorloading
        
        
        if(errorLoading){
            std::cout<<""<<std::endl;
            std::cout<<"The program was not supplied with any data."<<std::endl;
            std::cout<<"It will now exit..."<<std::endl;
            EmptySpace();
        }
        
        // Freeing Heap data.
        FreeHeap();
        
        // Call PretendIamAndy
        if(!is_Manager){
            PretendIamAndy();
        }
        
    }//end StartGame()
    
    
    // Game Ends....
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
    
    
    void PretendIamAndy(){
        long long rAndy = rand()%700;
        
        std::cout<<"Hey, Andy here. Wanna see or hear something fun? ";
        getline(std::cin, Feedback);
        
        YESorNO();
        
        if(Feedback=="No"){
            if(rAndy%2==0){
                std::cout<<"Have I been of no use to you?!"<<std::endl;
            }else{
                std::cout<<"Hey, there's no such thing as a DoNothing method..."<<std::endl;
            }
        }//end if
        
        else if(Feedback=="Yes"){
            if(rAndy%2==0){
                std::cout<<"I was around when Linus Torvalds was born..."<<std::endl;
            }else if(rAndy%3==0){
                std::cout<<"There's only two kinds of people in this world, and I am both of them."<<std::endl;
            }else if(rAndy%3==1){
                std::cout<<"If you don't pass this course, may I call the slap method on your facial properties?"<<std::endl;
            }else{
                std::cout<<"https://cs.iupui.edu/~aharris/"<<std::endl;
            }
        
        }//end else-if
    }//end PretendIamAndy
    
    void EmptySpace(){
        std::cout<<""<<std::endl;
    }//end EmptySpace
    
    
};//endof Game
#endif /* Game_h */
