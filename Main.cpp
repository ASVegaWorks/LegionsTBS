#include "GameBoard.h"
#include "GenericPlayer.h"
#include "Player.h"
#include "Legion.h"
#include"TitleScreen.h"
#include<iostream>

using namespace std;

template<typename B, typename P1, typename P2>
void DeploymentStage(B &board, P1 &player1, P2 &player2);

template<typename B, typename P1, typename P2>
void BattleStage(B &board, P1 &player1, P2 &player2);

template<typename B, typename P1, typename P2>
void EndGame(B &board, P1 &player1, P2 &player2);

int main() {
	vector<GenericPlayer*> MainPlayerList;
	TitleScreen titlescreen;
	size_t menuInput;
	cout << "\n\n\n\n\n";
	titlescreen.GetTitle();
	cout << "\n\n\n\n\n" << right << setw(127) << "1. PLAY AGAINST ANOTHER PLAYER." << endl;
	cout << "\n\n" << right << setw(120) << "2. HOW TO PLAY." << endl;
	cout << "\n\n" << right << setw(117) << "3. EXIT." << endl;
	do {
		cin >> menuInput;
		switch (menuInput) {
		case 1:
			//system("cls");
			Player *player1;
			Player *player2;
			GameBoard *MainBoard;
			MainBoard = new GameBoard(8, 8);
			MainPlayerList.emplace_back(player1 = new Player("Player1",MainBoard,MainPlayerList));
			MainPlayerList.emplace_back(player2 = new Player("Player2",MainBoard,MainPlayerList));
			player1->SetOpponent();
			player2->SetOpponent();
			DeploymentStage(MainBoard,player1,player2);
			break;
		case 2:
			//system("cls");
			titlescreen.HowToPlay();
			cout << "\n\n\n\n\n";
			titlescreen.GetTitle();
			cout << "\n\n\n\n\n" << right << setw(127) << "1. PLAY AGAINST ANOTHER PLAYER." << endl;
			cout << "\n\n" << right << setw(120) << "2. HOW TO PLAY." << endl;
			cout << "\n\n" << right << setw(117) << "3. EXIT." << endl;
			break;
		default:
			//system("cls");
			cout << "\n\n\n\n\n";
			titlescreen.GetTitle();
			cout << "\n\n\n\n\n" << right << setw(127) << "1. PLAY AGAINST ANOTHER PLAYER." << endl;
			cout << "\n\n" << right << setw(120) << "2. HOW TO PLAY." << endl;
			cout << "\n\n" << right << setw(117) << "3. EXIT." << endl;

			cout << "\n\n" << right << setw(123) << "Invalid user input." << endl;
			cin.clear();
			cin.ignore(256,'\n'); // ensures only 1 character read, ignore until new line
			break;
		}
	} while (menuInput != 3);
}

template<typename B,typename P1, typename P2>
void DeploymentStage(B &board, P1 &player1, P2 &player2) {
	do {
		if (player1->isTurn) {
			player1->DeployInput();
		}
		else {
			player2->DeployInput();
		}
		if (player1->isReady && player2->isReady) {
			board->PlayersReady = true;
		}
	} while (board->PlayersReady == false);
	player1->isTurn = true;
	player2->isTurn = false;
	BattleStage(board,player1,player2);
}
template<typename B, typename P1, typename P2>
void BattleStage(B &board, P1 &player1, P2 &player2) {
	player1->inBattleStage = true;
	player2->inBattleStage = true;
	do {
		if (player1->isTurn) {
			player1->SelectLegion();
		}
		else if (player2->isTurn) {
				player2->SelectLegion();
		}
		} while (player1->winner == false && player2->winner == false);
		EndGame(board,player1,player2);
	}
template<typename B, typename P1, typename P2> 
void EndGame(B &board, P1 &player1, P2 &player2) {
	GenericPlayer *winner;
	GenericPlayer *loser;
	auto input = 0;
	player1->winner == true ? winner = player1 : winner = player2;
	player1->loser == true ? loser = player1 : loser = player2;
	player1->DisplayPlayerBoard();
	cout << right << setw(135) << winner->GetPlayerName() + " is victorious!\n\n";
	cout << right << setw(156) << winner->GetPlayerName() + " has routed or annihilated all of " + loser->GetPlayerName() + "'s legions!\n\n";
	cout << right << setw(145) << "| Legions left: " + to_string(winner->GetLegionCount()) + " | Men: " + to_string(winner->GetTotalMen()) + " | Turn #: " + to_string(board->GetTurnNumber()) + " |\n";
	cin >> input;
	delete board;
	board = 0;
	delete player1;
	player1 = 0;
	delete player2;
	player2 = 0;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	main();
}

