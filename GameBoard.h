#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<iomanip>

using namespace std;

class GameBoard
{
public:
	friend class GenericPlayer; // Allows Player class access to all of GameBoards members.
	friend class Player;
	friend class Legion;
	GameBoard();
	GameBoard(const int unsigned rows,const int unsigned columns);
	~GameBoard();
	void SetDeploymentZones();
	void IdentifyBorders();
	void DisplayInstructions(string x);
	void DisplayAnnouncement(string x);
	void AddTurn();
	int GetTurnNumber()const;
	bool PlayersReady = false;

private:
	int turnCount;
	unsigned const int ROWS;
	unsigned const int COLUMNS;
	string BoardDivision = ("____________________________________________________________");;
	string Announcement = "";
	string Instructions = "";
	string LetterCoordinates = ("ABCDEFGH");
	vector<string> Player1DeploymentZoneSpaces;
	vector<string> Player2DeploymentZoneSpaces;
	vector<string> BorderSpaces;
	vector<string> TopBorderSpaces;
	vector<string> BottomBorderSpaces;
	vector<string> LeftBorderSpaces;
	vector<string> RightBorderSpaces;
	vector<vector<char>> BoardVector;
};

