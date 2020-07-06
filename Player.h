#pragma once
#include <iostream>
#include <iomanip>
#include<sstream>
#include"GenericPlayer.h"
#include "Legion.h"


using namespace std;

class GenericPLayer;

class Player : public GenericPlayer
{
	public:
		bool selectingAction = false;
		Player();
		Player(const string name,GameBoard *board, vector<GenericPlayer*> &playerlist);
		Player(const Player &source);
		~Player();
		void DeployInput();
		void SelectLegion();
		void SelectAction();
		void SelectTarget();
		void SelectMoveDirection();
		void SelectMoveAllDirection();
		void SelectDisengageDirection();
		bool ConfirmMove();
		bool ConfirmMoveAll();
		bool ConfirmAttack(Legion &targetedLegion);
		bool ConfirmTurn();
		void DisplayUi()const;
		void DisplayPlayerBoard()const;
		void DisplayActionUi()const;
		void DisplayMoveDirectionUi()const;
		void DisplayMoveAllDirectionUi()const;
		void DisplayConfirmMoveUi()const;
		void DisplayConfirmMoveAllUi()const;
		void DisplayConfirmAttackUi(Legion &targetedLegion)const;
		void DisplayChargeDamageUi(Legion &targetedLegion, int damage)const;
		void ChargeOutcome(Legion &targetedLegion, int damage);
		void DisplayConfirmEndTurnUi()const;
		void DisplayTargetUi()const;
		void NextTurn();
		void ClearInput();
	private:
		string spaceInput;
		char letterInput;
		int numberInput;
		GameBoard *ConnectedBoard;

};

