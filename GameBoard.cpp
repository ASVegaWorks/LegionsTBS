#include "GameBoard.h"

GameBoard::GameBoard():
	 ROWS(0),  COLUMNS(0),turnCount(0)
{
	cout << right << setw(135) << "Generating field of Mars..." << endl;
	BoardVector = { ROWS,vector<char>(COLUMNS,'.') };// Initializing vector of vectors

	Player1DeploymentZoneSpaces.reserve(ROWS * 3);
	Player2DeploymentZoneSpaces.reserve(ROWS * 3);
	BorderSpaces.reserve((ROWS * 2) + (COLUMNS * 2));
	TopBorderSpaces.reserve(ROWS);
	BottomBorderSpaces.reserve(ROWS);
	LeftBorderSpaces.reserve(ROWS);
	RightBorderSpaces.reserve(ROWS);

	IdentifyBorders();
	SetDeploymentZones();
}

GameBoard::GameBoard(const int unsigned rows, const int unsigned columns) :
	ROWS(rows), COLUMNS(columns), turnCount(0)
{	
	cout << right << setw(135) << "Generating field of Mars..." << endl;
	BoardVector = { rows,vector<char>(columns,'.') }; // Initializing vector of vectors

	Player1DeploymentZoneSpaces.reserve(rows * 3);
	Player2DeploymentZoneSpaces.reserve(rows * 3);
	BorderSpaces.reserve((ROWS * 2) + (COLUMNS * 2));
	TopBorderSpaces.reserve(ROWS);
	BottomBorderSpaces.reserve(ROWS);
	LeftBorderSpaces.reserve(ROWS);
	RightBorderSpaces.reserve(ROWS);

	IdentifyBorders();
	SetDeploymentZones();
}

GameBoard::~GameBoard()
{
}

void GameBoard::SetDeploymentZones() {
	int columnNum = 0;
	int columnNum2 = 0;
	for (int i = ROWS; i >= ROWS - 2; i--) {
		for (int w = 0; w < COLUMNS; w++) {
			Player1DeploymentZoneSpaces.push_back(LetterCoordinates[w] + to_string(i));
			columnNum++;
		}
	}
	for (int i = 1; i <= ROWS - 5; i++) {
		for (int w = 0; w < COLUMNS; w++) {
			Player2DeploymentZoneSpaces.push_back(LetterCoordinates[w] + to_string(i));
			columnNum2++;
		}
	}
}

void GameBoard:: IdentifyBorders() {
	int rowNum = 1;
	for (int i = 0; i < ROWS; i++) {
		TopBorderSpaces.push_back(LetterCoordinates.at(i) + to_string(rowNum));
		BottomBorderSpaces.push_back(LetterCoordinates.at(i) + to_string(rowNum + ROWS - 1));
		LeftBorderSpaces.push_back(LetterCoordinates.at(0) + to_string(rowNum + i));
		RightBorderSpaces.push_back(LetterCoordinates.at(ROWS - 1) + to_string(rowNum + i));
		BorderSpaces.push_back(TopBorderSpaces.at(i));
		BorderSpaces.push_back(BottomBorderSpaces.at(i));
		BorderSpaces.push_back(LeftBorderSpaces.at(i));
		BorderSpaces.push_back(RightBorderSpaces.at(i));
	}
}

void GameBoard::DisplayInstructions(string instructions) {
	cout << left<<setw(85) <<""<< instructions << endl;
}

void GameBoard::DisplayAnnouncement(string announcement) {
	cout<< left << setw(110) << ""<< announcement << endl;
}

void GameBoard::AddTurn() {
	this->turnCount++;
}

int GameBoard::GetTurnNumber()const {
	return this->turnCount;
}