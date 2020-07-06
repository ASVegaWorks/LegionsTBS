#include "GenericPlayer.h"

int GenericPlayer::numPlayers = 0;

GenericPlayer::GenericPlayer() 
{
	//cout << "GenericPlayer default constructor" << endl;
	char enemySymbol;
	if (numPlayers == 0) { // 0 = Player1
		this->isTurn = true;
		this->unitSymbol = 'X';
		enemySymbol = 'O';
	}
	else {
		this->isTurn = false;
		this->unitSymbol = 'O';
		enemySymbol = 'X';
	}
	numPlayers++;
	LegionList.reserve(maxLegions); // Resizing vectors activate copy constructors
									//LegionList.shrink_to_fit(); // If the vector size doubles, this function fits the size of the vector to the amount of elements on vector
	while (this->availableLegions < this->maxLegions) {
		LegionList.emplace_back(this->unitSymbol, enemySymbol, ConnectedBoard); // emplace_back creates the object already within the vector, can take parameters then and there, calls constructor and move constructor.
		LegionList[availableLegions].SetLegionName(this->availableLegions + 1);
		this->availableLegions++;
		
	}
}
GenericPlayer::GenericPlayer(GameBoard *board, string name, vector<GenericPlayer*> &playerlist):
	ConnectedBoard(board), m_Pname(name),PlayerList(&playerlist)
{
	//cout << "GenericPlayer constructor" << endl;

	char enemySymbol;
	if (numPlayers == 0) {
		this->isTurn = true;
		this->unitSymbol = 'X';
		enemySymbol = 'O';
	}
	else {
		this->isTurn = false;
		this->unitSymbol = 'O';
		enemySymbol = 'X';
	}
	numPlayers++;
	LegionList.reserve(maxLegions); // Resizing vectors activate copy constructors
	//LegionList.shrink_to_fit(); // If the vector size doubles, this function fits the size of the vector to the amount of elements on vector
	while (this -> availableLegions < this-> maxLegions) {
		LegionList.emplace_back(this->unitSymbol, enemySymbol,ConnectedBoard); // emplace_back creates the object already within the vector, can take parameters then and there, calls constructor and move constructor.
		LegionList[availableLegions].SetLegionName(this->availableLegions + 1);
		this->availableLegions++;
	}
}

GenericPlayer::~GenericPlayer(){

}

void GenericPlayer::PassBoardandName(GameBoard* board, string name) {
	this->ConnectedBoard = board;
	this->m_Pname = name;
}

void GenericPlayer::SetOpponent() {
	if (this->m_Pname == "Player1") {
		this->Opponent = this->PlayerList->at(1);
	}
	else if (this->m_Pname == "Player2") {
		this->Opponent = this->PlayerList->at(0);
	}
}
bool GenericPlayer::IsInDeploymentZone(string input) {
	bool inDepZone = false;
	if (this->m_Pname == "Player1") {
		if (find(ConnectedBoard->Player1DeploymentZoneSpaces.begin(), ConnectedBoard->Player1DeploymentZoneSpaces.end(), input) == ConnectedBoard->Player1DeploymentZoneSpaces.end()) {
			return false;
		}
		else
			return true;
	}
	if (this->m_Pname == "Player2") {
		if (find(ConnectedBoard->Player2DeploymentZoneSpaces.begin(), ConnectedBoard->Player2DeploymentZoneSpaces.end(), input) == ConnectedBoard->Player2DeploymentZoneSpaces.end()) {
			return false;
		}
		else
			return true;
	}
}

BoardIndex GenericPlayer::SearchSpace(string &input, char &letter, int &number) {
		for (int rows = 0; rows < ConnectedBoard->ROWS; rows++) {
			for (int columns = 0; columns < ConnectedBoard->COLUMNS; columns++) {
				if (letter == ConnectedBoard->LetterCoordinates[columns] && number == rows && number < ConnectedBoard->ROWS && number >= 0 && ConnectedBoard->BoardVector.at(rows).at(columns) != this->unitSymbol) {
					return { rows, columns, true };
				}else if (letter == ConnectedBoard->LetterCoordinates[columns] && number == rows && number < ConnectedBoard->ROWS && number >= 0 && ConnectedBoard->BoardVector.at(rows).at(columns) == this->unitSymbol) {
					return { rows, columns , false };
				}
			}
		}
	}

void GenericPlayer::PlaceLegion(string input, const unsigned  int rowNum, const unsigned  int columnNum) {
	for (auto &legio : this->LegionList) {
		if (legio.GetLocation() != input && legio.GetLocation() == "") {
			legio.SetMenCount(1000);
			legio.SetLocation(input, rowNum, columnNum,this->unitSymbol);
			legio.SetStance("Ready");
			this->totalMen += legio.GetMenCount();
			this->deployedLegions++;
			for (auto &updateLegio : this->LegionList) {
				if (updateLegio.isDeployed == true) {
					updateLegio.ScoutAdjacents();
					updateLegio.UpdateMorale();
				}
			}
			break;
		}
	}
}

void GenericPlayer::RemoveLegion(string input, const unsigned  int rowNum, const unsigned  int columnNum) {
	for (auto &legio : this->LegionList) {
		if (legio.GetLocation() == input) {
			this->totalMen -= legio.GetMenCount();
			legio.SetMenCount(0);
			legio.SetStance("");
			legio.ClearMorale();
			this->deployedLegions--;
			legio.ClearLocation(rowNum, columnNum);
			legio.isDeployed == false;
			for (auto &updateLegio : this->LegionList) {
				if (updateLegio.isDeployed == true) {
					updateLegio.ScoutAdjacents();
					updateLegio.UpdateMorale();
				}
			}
			break;
		}
	}
}

int GenericPlayer::MoveLegions(char moveDir) {
	int movedLegions = 0;
	int unmovedLegions = 0;
	int movableLegions = this->GetMovableLegions();
	while (movedLegions + unmovedLegions < movableLegions) {
		for (auto &legio : this->LegionList) {
			if (legio.isDeployed == true && legio.canMove == true && legio.inCombat == false && legio.destroyed == false
				&& legio.Fleeing == false && legio.ValidMove(moveDir)) {
				legio.MoveLegion(moveDir);
				legio.UpdateLegion();
				movedLegions++;
			}
			else if(legio.ValidMove(moveDir) == false){
				unmovedLegions++;
			}
		}
	}
	return movedLegions;
}

int GenericPlayer::GetMovableLegions()const {
	int movableLegions = 0;
	for (auto &legio : this->LegionList) {
		if (legio.isDeployed == true && legio.canMove == true && legio.inCombat == false && legio.destroyed == false
			&& legio.Fleeing == false ) {
			movableLegions++;
		}
	}
	return movableLegions;
}
void GenericPlayer::UpdateTotalMen() {
	this->totalMen = 0;
	for (auto &i : this->LegionList) {
		this->totalMen += i.GetMenCount();
	}
}

int GenericPlayer::GetTotalMen()const {
	return this->totalMen;
}

bool GenericPlayer::RollDisengagement() {
	srand(static_cast<unsigned int>(time(0)));
	int disengageChance = rand() % this->SelectedLegion->GetEngangedCount()+1;
	if (this->SelectedLegion->GetEngangedCount() < 2) {
		return true;
	}
	else if (this->SelectedLegion->GetEngangedCount() >= 2 &&  disengageChance == 1) {
		return true;
	}
	else {
		return false;
	}
}

int GenericPlayer::DisengagementCasualties() {
	int minCasualties = 35;
	int maxCasualties = 56;
	int range = maxCasualties - minCasualties + 1;
	srand(static_cast<unsigned int>(time(0)));
	int disengageCasualties = rand() % range + minCasualties;
	this->SelectedLegion->TakeDamage(disengageCasualties);
	if (this->SelectedLegion->GetMenCount() <= 0) {
		this->SelectedLegion->DestroyLegion();
	}
	return disengageCasualties;
}
void GenericPlayer::UpdateBattle() {

	if (this->GetLegionCount() == 0) this->loser = true, this->Opponent->winner = true;

	for (auto &legio : this->LegionList) {// iterate through current players legions to update
		if (legio.isDeployed == true && legio.destroyed == false && legio.GetMenCount() <= 0) {// if destroyed
			legio.DestroyLegion();
			legio.SetEngagedCount();
			this->deployedLegions--;
		}
		if (legio.EnemiesEngaged.size() == 0) {
			legio.inCombat = false;
		}
		if (legio.inCombat == false) {
			legio.EnemiesEngaged.clear();
			legio.SetEngagedCount();
		}
		if (legio.isDeployed == true && legio.destroyed == false && legio.inCombat == true &&  legio.Fleeing == false && legio.GetMenCount() > 0) {
			legio.SetStance("In Combat");
			legio.InflictDamage();
		}
		else if (legio.isDeployed == true && legio.destroyed == false && legio.inCombat == false && legio.Fleeing == false) {
			legio.canMove = true;
			legio.SetStance("Ready");
		}
		else if (legio.isDeployed == true && legio.destroyed == false && legio.Fleeing == true) {
			legio.FleeLegion();
			if (legio.destroyed == true) this->deployedLegions--;
			legio.ScoutAdjacents();
			legio.ScoutTargets();
		}
		if (legio.isDeployed == true && legio.destroyed == false) legio.UpdateLegion();
	}

	for (auto &enemyLegio : this->Opponent->LegionList) { // iterate through enemy's legions to update
		if (enemyLegio.isDeployed == true && enemyLegio.destroyed == false && enemyLegio.GetMenCount() <= 0) {// if destroyed
			enemyLegio.DestroyLegion();
			enemyLegio.SetEngagedCount();
			this->Opponent->deployedLegions--;
		}

		for (auto &legio : this->LegionList) { // iterate through current players legions to update their targets
			auto it = find(enemyLegio.EnemiesEngaged.begin(), enemyLegio.EnemiesEngaged.end(), &legio);
			auto it2 = find(legio.EnemiesEngaged.begin(), legio.EnemiesEngaged.end(), &enemyLegio);
			if (legio.isDeployed == true && enemyLegio.destroyed == true && !legio.EnemiesEngaged.empty()
				&& it2 != legio.EnemiesEngaged.end() || enemyLegio.Fleeing == true && it2 != legio.EnemiesEngaged.end()) {
				legio.EnemiesEngaged.erase(it2);
				legio.SetEngagedCount();
			}
			if (enemyLegio.isDeployed == true && enemyLegio.destroyed == false && !enemyLegio.EnemiesEngaged.empty()
				&& it != enemyLegio.EnemiesEngaged.end() && legio.Fleeing == true) { // if enemy legion's targets flee.
				enemyLegio.EnemiesEngaged.erase(it);
				enemyLegio.SetEngagedCount();
			}
		}
		if (enemyLegio.EnemiesEngaged.size() == 0) {
			enemyLegio.inCombat = false;
		}
		if (enemyLegio.inCombat == false) {
			enemyLegio.EnemiesEngaged.clear();
			enemyLegio.SetEngagedCount();
		}
		if (enemyLegio.isDeployed == true && enemyLegio.destroyed == false && enemyLegio.inCombat == true  &&  enemyLegio.Fleeing == false && enemyLegio.GetMenCount() > 0) {
			enemyLegio.SetStance("In Combat");
		}
		else if (enemyLegio.isDeployed == true && enemyLegio.destroyed == false && enemyLegio.inCombat == false && enemyLegio.Fleeing == false) {
			enemyLegio.canMove = true;
			enemyLegio.SetStance("Ready");
		}
		else if (enemyLegio.isDeployed == true && enemyLegio.destroyed == false && enemyLegio.Fleeing == true) {
			enemyLegio.FleeLegion();
			if (enemyLegio.destroyed == true) Opponent->deployedLegions--;
			enemyLegio.ScoutAdjacents();
			enemyLegio.ScoutTargets();
		}
		if (enemyLegio.isDeployed == true && enemyLegio.destroyed == false) enemyLegio.UpdateLegion();
	}
	this->UpdateTotalMen();
	this->Opponent->UpdateTotalMen();
}

void GenericPlayer::SetLegionCount() {
	if (this->deployedLegions > maxLegions) {
		deployedLegions = maxLegions;
	}
	else {
		this->deployedLegions++;
	}
}

int GenericPlayer::GetLegionCount()const {
	return this->deployedLegions;
}

string GenericPlayer::GetPlayerName()const {
	return this->m_Pname;
}
