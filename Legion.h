#pragma once
#include<iostream>
#include<vector>
#include<map>
#include"GameBoard.h"
#include "GenericPlayer.h"
#include <thread>

using namespace std;

class Legion 
{
	public:
		Legion();
		Legion(char symbol, char enemySymbol, GameBoard *ConnectedBoard);
		~Legion();
		Legion(const Legion &source);
		Legion(Legion &&source);
		//Legion &operator=(const Legion &source);
		string GetLegionName()const;
		string GetLocation()const;
		string GetStance()const;
		int GetMenCount()const;
		string CoordsToSpace(const unsigned int &rowNum,const unsigned int columnNum);
		void SetLegionName(int legionCount);
		void SetLocation(string &pos, const unsigned  int &rowNum, const unsigned int &columnNum, char &symbol);
		void SetStance(string stance);
		void ClearLocation(const unsigned  int &rowNum, const unsigned int &columnNum);
		void ClearMorale();
		void SetMenCount(int num);
		void MoveLegion(char &moveDirection);
		void FleeLegion();
		void ScoutAdjacents();
		void ScoutTargets();
		void UpdateLegion();
		int ChargeEnemy(Legion &targetedLegion);
		void InflictDamage();
		void DestroyLegion();
		void TakeDamage(int &damage);
		void AddEngagedLegion(Legion &targetedLegion);
		int GetEngangedCount()const;
		int GetFlanksCount()const;
		double GetMoraleValue()const;
		string GetMoraleStatus()const;
		void SetEngagedCount();
		void DisengageTargets(vector<Legion> &opponentEnemiesEngaged);
		void UpdateMorale();
		bool RollMorale();
		bool ValidMove(char &moveKey);
		bool destroyed = false;
		bool isDeployed = false;
		bool canMove = true;
		bool canAttack = false;
		bool inCombat = false;
		bool isRetreating = false;
		bool canRetreat = false;
		bool Fleeing = false;
		pair<int, int> legionCoord;
		map<string, string> AdjacentSpaces;
		map<string, pair<int, int>> AdjacentCoords;
		map<string, string> TargetSpaces;
		map<string, pair<int, int>> TargetCoords;
		vector<Legion*> EnemiesEngaged;
	private:
		char m_unitSymbol;
		char m_enemyUnitSymbol;
		int m_LegionMen;
		int m_EnemiesEngagedCount;
		int m_FlanksCount;
		double m_Morale;
		const int m_MinDamage = 10;
		const int m_MaxDamage = 25;
		const double m_BaseMorale;
		int damageModifier;
		string m_LegionName;
		string m_LegionPosition;
		string m_Stance;
		string m_MoraleStatus;
		GameBoard *ConnectedBoard;
};
