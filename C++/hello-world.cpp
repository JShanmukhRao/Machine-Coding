#include<bits/stdc++.h>
using namespace std;
class Players{
    private:
        int currentScore;
    public:
        Players(){
            currentScore=0;
        }
        int getCurrentScore() {
            return this->currentScore;
        }
        void setCurrentScore(int currentScore) {
            this->currentScore = currentScore;
        }

    
};
class ScoreBoard{

};
class ValidationService{
    public:
     bool validateInput(int chanceValue1){
            if(chanceValue1<0 || chanceValue1>10 ){
                cout<<"INVALID INPUT"<<endl;
                return false;
            }
            return true;
        }
};
class ScoreCard{
    private:
        unordered_map<string,Players*> playersList;
    public:

        unordered_map<string,Players*>& getPlayersList() {
        	return this->playersList;
        }
        void setPlayersList(unordered_map<string,Players*> playersList) {
        	this->playersList = playersList;
        }
        

};

class GameServices{

    public:
    void setplayers(int numberOfPlayers,ScoreCard *scoreCard){
         unordered_map<string,Players*> playersList=scoreCard->getPlayersList();
        for(int i=0;i<numberOfPlayers;i++){
            string playerName="p"+ to_string(i+1);
            playersList[playerName]=new Players();
        }
    }
    void printScoreBoard(ScoreCard *scoreCard,bool isFinal){
        unordered_map<string,Players*> playersList=scoreCard->getPlayersList();
        for(auto player:playersList){
           
            cout<<player.first<<" -> "<<player.second->getCurrentScore()<<endl;
        }
         priority_queue<pair<int,string>> finalScoreList;
         if(isFinal){
             for(auto player:playersList){
                 finalScoreList.push({player.second->getCurrentScore(),player.first});
                 
             }
             
            //  Printing Final Scores
            while(!finalScoreList.empty()){
                cout<<finalScoreList.top().second<<" - "<<finalScoreList.top().first<<" points"<<endl;
            }
         }

    }
  
    void setScore(int chance1,int chance2,Players *player){
         ValidationService *validationService= new ValidationService();
         
        if(validationService->validateInput(chance1)){
            int totalPoints=chance1+chance2;
           
            if(chance1==10){
                totalPoints+=10;
            }else if(chance1>5){
                totalPoints+=5;
                
            }   
            // Second chance point
            if(chance2==10){
                    totalPoints+=10;
            }else if(chance2>5){
                    totalPoints+=5;
            }    

            // Setting final player score
            totalPoints+=player->getCurrentScore();
            player->setCurrentScore(totalPoints);
        }
    }
    void startRound(bool isFinal,Players *player){
       
        int chance1,chance2=0;
        // cout<<"Enter Score for Player"<<playerNumber<<" - Chance1"<<endl;
        cin>>chance1;
        // cout<<"Enter Score for Player"<<playerNumber<<" - Chance2"<<endl;
         if(chance1<10){
             cin>> chance2;
         }
         if(!isFinal){
             setScore(chance1,chance2,player);
         }else{
              setScore(chance1,chance2,player);
             if(chance1>5 ){
                
                 int extraChance1,extraChance2;
                 cin>>extraChance1>>extraChance2;
                setScore(extraChance1,extraChance2,player);
             }

         }
       
        
    }
};

int main()
{
    ScoreCard *scoreCard= new ScoreCard();
    GameServices *gameServices =new GameServices();
    int numberOfRounds=1;
    int numberOfPlayers;
    cin>>numberOfPlayers;
    gameServices->setplayers(numberOfPlayers,scoreCard);
    int currentRound=1;
    
    while(currentRound<=numberOfRounds){
         unordered_map<string,Players*> playersList=scoreCard->getPlayersList();

        if(currentRound<numberOfRounds){
            
            for(int i=0;i<numberOfPlayers;i++){
               string playerName="p"+ to_string(i+1);
                gameServices->startRound(false,playersList[playerName]);
                
                // Printing scorecard
                gameServices->printScoreBoard(scoreCard,false);
            }
            

        }else{
            for(int i=0;i<numberOfPlayers;i++){
               string playerName="p"+ to_string(i+1);
                gameServices->startRound(true,playersList[playerName]);
                
                // Printing scorecard
                gameServices->printScoreBoard(scoreCard,true);
            }
            // FINAL ROUND
        }


        currentRound++;
    }
    return 0;
}