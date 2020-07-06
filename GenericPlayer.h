#pragma once
#include<iostream>
#include<vector>
#include "GameBoard.h"
#include "Legion.h"

class Legion;
struct BoardIndex;

using namespace std;

class GenericPlayer
{
	public:
		GenericPlayer();
		GenericPlayer(GameBoard*board, string name, vector<GenericPlayer*> &playerlist);
		~GenericPlayer();
		bool isTurn = false;
		bool isReady = false;
		bool inBattleStage = false;
		bool winner = false;
		bool loser = false;
		int GetLegionCount()const;
		int GetMovableLegions()const;
		int GetTotalMen()const;
		string GetPlayerName()const;
		BoardIndex SearchSpace(string &input, char &letter, int &number);
		void PassBoardandName(GameBoard* board, string name);
		void PlaceLegion(string input, const unsigned int rowNum, const unsigned int columnNum);
		void RemoveLegion(string input, const unsigned int rowNum, const unsigned int columnNum);
		int MoveLegions(char moveDir);
		int DisengagementCasualties();
		void UpdateBattle();
		void UpdateTotalMen();
		void SetOpponent();
		void SetLegionCount();
		bool IsInDeploymentZone(string input);
		bool RollDisengagement();
		vector<Legion> LegionList;
	private:
	protected:
		string m_Pname;
		static int numPlayers;
		const int maxLegions = 7;
		int availableLegions = 0;
		int deployedLegions = 0;
		int totalMen = 0;
		char unitSymbol;
		GameBoard *ConnectedBoard;
		Legion *SelectedLegion;
		GenericPlayer *Opponent;
		vector<GenericPlayer*> *PlayerList;
};

struct BoardIndex {
	int rows;
	int columns;
	bool Placing = true;
};