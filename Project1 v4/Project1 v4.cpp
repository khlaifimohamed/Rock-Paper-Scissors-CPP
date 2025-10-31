#include <iostream>
#include <cstdlib>
using namespace std;
enum enChoice
{
    stone=1,paper=2,scissors=3
};
enum enWinner
{
    Player1=1,Computer=2,Draw=3
};
struct strRoundInfo
{
    short RoundNumber;
    enChoice Player1Choice;
    enChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;
};
struct strGameInfo
{
    short RoundsNumber;
    short Player1Score;
    short ComputerScore;
    short DrawTimes;
    enWinner Winner;
    string WinnerName;
};


int HowManyRounds() {
    int number;
    do
    {
        cout << "how many rounds do you wanna play\n";
        cin >> number;
    } while (number<1||number>10);
    return number;
}
enChoice ReadPlayerChoice() {
    int Choice;
    do
    {
        cout << "Your Choice Stone(1) Paper(2) Scissors(3) ?";
        cin >> Choice;
    } while (Choice<1||Choice>3);
    return (enChoice)Choice;
}
int RandomNumber(int From,int To) {
    return rand() % (To - From + 1) + From;
}
enChoice MakeComputerChoice() {
    return (enChoice)RandomNumber(1, 3);
}
enWinner WhoWinTheRound(strRoundInfo Roundinfo) {
    if (Roundinfo.ComputerChoice == Roundinfo.Player1Choice) {
        return enWinner::Draw;
    }
    else
    {
        switch (Roundinfo.ComputerChoice) {
        case enChoice::paper:
            if (Roundinfo.Player1Choice == enChoice::stone) {
                return enWinner::Computer;
            }
            break;
        case enChoice::scissors:
            if (Roundinfo.Player1Choice == enChoice::paper) {
                return enWinner::Computer;
            }
            break;
        case enChoice::stone:
            if (Roundinfo.Player1Choice == enChoice::scissors) {
                return enWinner::Computer;
            }
            break;
        }
    }
    return enWinner::Player1;
}
string WinnerName(enWinner winner) {
    string WinnerArray[3] = {"Player1","Computer","Draw"};
    return WinnerArray[winner - 1];
}
string ChoiceName(enChoice Choice) {
    string ChoiceArray[3] = { "Stone","Paper","Scissors" };
    return ChoiceArray[Choice - 1];
}
void PrintRoundResults(strRoundInfo RoundInfo) {
    cout << "\n------------------------------------------------------------\n";
    cout << "Player1 Choice :" << ChoiceName(RoundInfo.Player1Choice)<<"\n";
    cout << "Computer Choice : " << ChoiceName(RoundInfo.ComputerChoice) << "\n";
    cout << "Round Winner :" << RoundInfo.WinnerName << "\n";
    cout << "\n------------------------------------------------------------\n";
}
enWinner WhoWinTheGame(strGameInfo GameInfo) {
    if (GameInfo.ComputerScore > GameInfo.Player1Score) {
        return enWinner::Computer;
    }
    else if(GameInfo.ComputerScore < GameInfo.Player1Score)
    {
        return enWinner::Player1;
    }
    else
    {
        return enWinner::Draw;
    }
}
strGameInfo FillGameInfo(int RoundsNumber,int Player1Score,int ComputerScore,int DrawTimes) {
    strGameInfo GameInfo;
    GameInfo.ComputerScore = ComputerScore;
    GameInfo.DrawTimes = DrawTimes;
    GameInfo.Player1Score = Player1Score;
    GameInfo.RoundsNumber = RoundsNumber;
    GameInfo.Winner = WhoWinTheGame(GameInfo);
    GameInfo.WinnerName = WinnerName(GameInfo.Winner);
    return GameInfo;
}
strGameInfo PlayGame(int RoundsNumber) {
    cout << "\n";
    int Player1Score = 0, ComputerScore = 0, DrawTimes = 0;
    for (short i = 1; i <= RoundsNumber; i++)
    {
        cout << "Round [" << i << "] begins";
        strRoundInfo RoundInfo;
        RoundInfo.RoundNumber = i;
        RoundInfo.Player1Choice = ReadPlayerChoice();
        RoundInfo.ComputerChoice = MakeComputerChoice();
        RoundInfo.Winner = WhoWinTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);
        if (RoundInfo.Winner == enWinner::Player1) {
            Player1Score++;
        }
        else if (RoundInfo.Winner == enWinner::Computer) {
            ComputerScore++;
        }
        else
        {
            DrawTimes++;
        }
        PrintRoundResults(RoundInfo);
    }
    return FillGameInfo(RoundsNumber, Player1Score, ComputerScore, DrawTimes);
}
void STARTGAME() {
    char AskNewGame = 'Y';
    do
    {
        system("cls");
        strGameInfo GameInfo = PlayGame(HowManyRounds());
        cout << "do you wanna paly another game\n";
        cin >> AskNewGame;
    } while (AskNewGame =='Y'||AskNewGame =='y');

}
int main()
{
    srand((unsigned)time(NULL));
    STARTGAME();
}


