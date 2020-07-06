#include "GameBoard.h"
#include "GenericPlayer.h"
#include "Player.h"
#include "Legion.h"
#include<iostream>

using namespace std;

template<typename B, typename P1, typename P2>
void DeploymentStage(B &board, P1 &player1, P2 &player2);

template<typename B, typename P1, typename P2>
void BattleStage(B &board, P1 &player1, P2 &player2);

template<typename B, typename P1, typename P2>
void EndGame(B &board, P1 &player1, P2 &player2);

void GetTitle();

void HowToPlay();

int main() {
	vector<GenericPlayer*> MainPlayerList;
	size_t menuInput;
	cout << "\n\n\n\n\n";
	GetTitle();
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
			HowToPlay();
			cout << "\n\n\n\n\n";
			GetTitle();
			cout << "\n\n\n\n\n" << right << setw(127) << "1. PLAY AGAINST ANOTHER PLAYER." << endl;
			cout << "\n\n" << right << setw(120) << "2. HOW TO PLAY." << endl;
			cout << "\n\n" << right << setw(117) << "3. EXIT." << endl;
			break;
		default:
			//system("cls");
			cout << "\n\n\n\n\n";
			GetTitle();
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

void GetTitle() {
	cout << right << setw(180) <<"      ===================================================================================================================================\n";
	cout << right << setw(180) <<"                                                                                                                                         \n";
	cout << right << setw(180) << "        VIVIVIV           VIVIVIVIVIVIV    VIVIVIVIVIVIVIIV    IVIVIVIV     IVIVIVIVIVVIVIVI    VIVIVIV       IVIVIV    VIVIVIVIVIVIVI  \n";
	cout << right << setw(180) <<"          IVIVI             IVIVIVIVIVIV     IVIVIVIVIVIVIIV      IVIV       IVIVIVIVIVIVIVIV     IVIVIVI       VIVI      IVIVIVIVIVIVI  \n";
	cout << right << setw(180) << "         IVIVI             IVIV      IV     IVIV         VI      IVIV       IVIV        VIVI     IVIV  VIV     VIVI      IVIV       VI  \n";
	cout << right << setw(180) << "         IVIVI             IVIV             IVIV                 IVIV       IVIV        VIVI     IVIV   VIV    VIVI      IVIV           \n";
	cout << right << setw(180) << "         IVIVI             IVIVIVIVIV       IVIV                 IVIV       IVIV   IV   VIVI     IVIV    VIV   VIVI      IVIVIVIVIVIVI  \n";
	cout << right << setw(180) << "         IVIVI             IVIV             IVIV     IVIVIVI     IVIV       IVIV        VIVI     IVIV     VIV  VIVI               VIVI  \n";
	cout << right << setw(180) << "         IVIVI      IV     IVIV      IV     IVIV         VI      IVIV       IVIV        VIVI     IVIV      VIV VIVI      IV       VIVI  \n";
	cout << right << setw(180) << "         IVIVIVIVIVIVI     IVIVIVIVIVIV     IVIVIVIVIVIVIVI      IVIV       IVIVIVIVIVIVIVIV     IVIV       VIVVIVI      IVIVIVIVIVIVI  \n";
	cout << right << setw(180) << "        VIVIVIVIVIVIVI    VIVIVIVIVIVIV    VIVIVIVIVIVIVIVI    IVIVIVIV     IVIVIVIVIVIVIVIV    VIVIVI       VIVIVIV    VIVIVIVIVIVIVI  \n";
	cout << right << setw(180) << "                                                                                                                                        \n";
	cout << right << setw(180) << "      ==================================================================================================================================\n";
	cout << right << setw(180) << "                                                                                                                                        \n";
	cout << right << setw(180) << "                                                       Project by Alonso S. Vega                                                        \n";

}

void HowToPlay() {
	size_t menuInput;
		do {
			cout << right << setw(180) << "                                                 HOW TO PLAY                                                       \n\n\n";
			cout << right << setw(180) << "DEPLOYMENT ZONES: During the deployment phase, Player1 can only deploy legions in the bottom 3 rows of the board       \n";
			cout << right << setw(180) << "and Player2 may only deploy legions in the top 3 rows of the board.                                                  \n\n";
			cout << right << setw(180) << "MOVEMENT: Legions may only move to an adjacent space per turn, they can not be moved to a space already occupied.    \n\n";
			cout << right << setw(180) << "COMBAT: If the legion hasn't already moved that same turn, a legion may target an enemy legion adjacent to its space.  \n";
			cout << right << setw(180) << "A legion may be targeted by up to 4 enemy legions, if they occupy all the spaces around it. The more men a legion has, \n";
			cout << right << setw(180) << "the more damage it will inflict on the enemy. Once a legion's men count has reached zero it will be destroyed.       \n\n";
			cout << right << setw(180) << "DISENGANGING: A legion may attempt to disengage from a fight if there are available spaces around it although not      \n";
			cout << right << setw(180) << "without a penalty. The more enemy legions it's engaged in combat with, the lesser the chance there is for a successful \n";
			cout << right << setw(180) << "disengagement. Successful disengagement or not, the legion may suffer casualties during the attempt.                 \n\n";
			cout << right << setw(180) << "MORALE: Each legion has a calculated morale which its value depends on the amount of men it has, and the amount of     \n";
			cout << right << setw(180) << "adjacent flanks secured by a friendly legion. As morale dwindles and reaches status of 'wavering', there will be a     \n";
			cout << right << setw(180) << "a chance every turn the legion may reach 'fleeing' status.                                                           \n\n";
			cout << right << setw(180) << "FLEEING: When a legion flees, it will disengage from a fight and will automatically move to the end of the board each  \n";
			cout << right << setw(180) << "turn. During this, the fleeing legion cannot be controlled, and once it reaches the border, it will be 'destroyed'.  \n\n";
			cout << right << setw(180) << "HOW TO WIN: Destroy or rout all of the enemy's legions for the your to glory!                                      \n\n\n";
			cout << right << setw(180) << "1. Continue                                                                                                        \n\n\n";
			cin >> menuInput;
			switch (menuInput) {
			case 1:
				return;
			default:
				cin.clear();
				cin.ignore(256, '\n'); // ensures only 1 character read, ignore until new line
				continue;
			}
		} while (menuInput != 1);
		return;
}