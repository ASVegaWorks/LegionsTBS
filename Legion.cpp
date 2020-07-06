#include "Legion.h"

Legion::Legion() :
	m_LegionMen(0),
	m_LegionName(m_LegionName),
	m_LegionPosition(m_LegionPosition),
	m_EnemiesEngagedCount(0),
	m_FlanksCount(0),
	m_BaseMorale(5.0),
	legionCoord(0,0)
{
	//cout << "Legion default constructor" << endl;

	pair<int, int>defaultCoords{ 0,0 };
	this->AdjacentCoords.insert({ make_pair("Front",defaultCoords) ,  make_pair("Rear",defaultCoords) ,
		make_pair("Left",defaultCoords) , make_pair("Right",defaultCoords) }); // multiple keys constructor for map
	this->AdjacentSpaces.insert({ { make_pair("Front","None") },{ make_pair("Rear","None") },
		{ make_pair("Left","None") },{ make_pair("Right","None") } });
	this->TargetCoords.insert({ make_pair("Front",defaultCoords) ,  make_pair("Rear",defaultCoords) ,
		make_pair("Left",defaultCoords) , make_pair("Right",defaultCoords) });
	this->TargetSpaces.insert({ { make_pair("Front","None") },{ make_pair("Rear","None") },
		{ make_pair("Left","None") },{ make_pair("Right","None") } });
}

Legion::Legion(char symbol, char enemySymbol, GameBoard *ConnectedBoard) :
	m_LegionMen(0),
	m_LegionName(m_LegionName),
	m_LegionPosition(m_LegionPosition),
	m_EnemiesEngagedCount(0),
	m_unitSymbol(symbol),
	m_enemyUnitSymbol(enemySymbol),
	m_FlanksCount(0),
	m_BaseMorale(5.0),
	legionCoord(0,0),
	ConnectedBoard(ConnectedBoard)
	
{
//	cout << "Legion constructor" << endl;
	pair<int, int>defaultCoords{ 0,0 };
	this->AdjacentCoords.insert({ make_pair("Front",defaultCoords) ,  make_pair("Rear",defaultCoords) ,
		 make_pair("Left",defaultCoords) , make_pair("Right",defaultCoords) }); // multiple keys constructor for map
	this->AdjacentSpaces.insert({ { make_pair("Front","None") },{ make_pair("Rear","None") },
		{ make_pair("Left","None") },{ make_pair("Right","None") } }); 
	this->TargetCoords.insert({ make_pair("Front",defaultCoords) ,  make_pair("Rear",defaultCoords) ,
		make_pair("Left",defaultCoords) , make_pair("Right",defaultCoords) }); 
	this->TargetSpaces.insert({ { make_pair("Front","None") },{ make_pair("Rear","None") },
		{ make_pair("Left","None") },{ make_pair("Right","None") } });
}

Legion::Legion(const Legion &source) :
	m_LegionName(source.m_LegionName),
	m_LegionMen(source.m_LegionMen),
	m_LegionPosition(source.m_LegionPosition),
	m_unitSymbol(source.m_unitSymbol),
	m_Stance(source.m_Stance),
	m_EnemiesEngagedCount(source.m_EnemiesEngagedCount),
	isDeployed(source.isDeployed),
	canAttack(source.canAttack),
	legionCoord{ source.legionCoord},
	AdjacentCoords{ source.AdjacentCoords },
	AdjacentSpaces{ source.AdjacentSpaces },
	TargetCoords{ source.TargetCoords },
	TargetSpaces{ source.TargetSpaces },
	m_BaseMorale{source.m_BaseMorale}
{
	//cout << "LEGION COPIED: " << endl;
}

Legion::Legion(Legion &&source) : 
	m_LegionName(source.m_LegionName),
	m_LegionMen(source.m_LegionMen),
	m_LegionPosition(source.m_LegionPosition),
	m_unitSymbol(source.m_unitSymbol),
	m_Stance(source.m_Stance),
	m_EnemiesEngagedCount(source.m_EnemiesEngagedCount),
	isDeployed(source.isDeployed),
	canAttack(source.canAttack),
	legionCoord{source.legionCoord},
	AdjacentCoords{ source.AdjacentCoords },
	AdjacentSpaces{ source.AdjacentSpaces },
	TargetCoords{ source.TargetCoords },
	TargetSpaces{ source.TargetSpaces },
	m_BaseMorale{ source.m_BaseMorale }
{
	//cout << "Move constructor" << endl;
}

Legion::~Legion()
{
}

void Legion::SetLegionName(int legionCount) {
	string romNum;
	string tempName = ("Legion ")+romNum;
	if ( legionCount == 1) {
		romNum = "I  ";
		m_LegionName = tempName+romNum;
	}
	else if (legionCount == 2) {
		romNum = "II ";
		m_LegionName = tempName + romNum;
	}
	else if (legionCount == 3) {
		romNum = "III";
		m_LegionName = tempName + romNum;
	}
	else if (legionCount == 4) {
		romNum = "IV ";
		m_LegionName = tempName + romNum;
	}
	else if (legionCount == 5) {
		romNum = "V  ";
		m_LegionName = tempName + romNum;
	}
	else if (legionCount == 6) {
		romNum = "VI ";
		m_LegionName = tempName + romNum;
	}
	else if (legionCount == 7) {
		romNum = "VII";
		m_LegionName = tempName + romNum;
	}
}

string Legion::GetLegionName()const {
	return m_LegionName;
}

void Legion::SetLocation(string &pos, const unsigned  int &rowNum, const unsigned int &columnNum,char &symbol) {
	this->legionCoord.first = rowNum;
	this->legionCoord.second = columnNum;
	this->m_LegionPosition = pos;
	ConnectedBoard->BoardVector.at(rowNum).at(columnNum) = symbol;
	this->isDeployed = true;
	this->ScoutAdjacents();
	this->ScoutTargets();
}

string Legion::GetLocation()const {
	return m_LegionPosition;
}

void Legion::ClearLocation(const unsigned  int &rowNum, const unsigned int &columnNum) {
	this->legionCoord.first = 0;
	this->legionCoord.second = 0;
	this->m_FlanksCount = 0;
	this->m_LegionPosition = "";
	ConnectedBoard->BoardVector.at(rowNum).at(columnNum) = '.';
	this->AdjacentCoords.clear();
	this->AdjacentSpaces.clear();
	this->TargetCoords.clear();
	this->TargetSpaces.clear();
	this->isDeployed = false;
	this->canAttack = false;
	this->inCombat = false;
}

void Legion::SetMenCount(int num) {
	m_LegionMen = num;
}
int Legion::GetMenCount()const {
	return m_LegionMen;
}

string Legion::CoordsToSpace(const unsigned int &rowNum,const unsigned int columnNum) {
	int num = rowNum + 1 +'0';
	char letter = ConnectedBoard->LetterCoordinates[columnNum];
	return{ letter, (char)num };
}

void Legion::ScoutAdjacents() {
	this->canRetreat = false;
	this-> m_FlanksCount = 0;
	if (this->m_unitSymbol == 'X') {
		if (this->legionCoord.first < ConnectedBoard->ROWS && this->legionCoord.first > 0) {
			int firstNum = this->legionCoord.first;
			int secondNum = this->legionCoord.second;
			pair<int, int>frontCoords{ --firstNum,secondNum };
			string frontSpace = CoordsToSpace(firstNum, secondNum);
			this->AdjacentCoords["Front"] = frontCoords;
			this->AdjacentSpaces["Front"] = frontSpace;
			//board->BoardVector.at(firstNum).at(secondNum) = 'F';
			if (ConnectedBoard->BoardVector.at(firstNum).at(secondNum) == '.' &&  this->inCombat == true) this->canRetreat = true;
			if (ConnectedBoard->BoardVector.at(firstNum).at(secondNum) == this->m_unitSymbol) this->m_FlanksCount++;
		}
		if (this->legionCoord.first != ConnectedBoard->ROWS - 1) {
			int firstNum = this->legionCoord.first;
			int secondNum = this->legionCoord.second;
			pair<int, int>rearCoords{ ++firstNum,secondNum };
			string rearSpace = CoordsToSpace(firstNum, secondNum);
			this->AdjacentCoords["Rear"] = rearCoords;
			this->AdjacentSpaces["Rear"] = rearSpace;
			//board->BoardVector.at(firstNum).at(secondNum) = 'B';
			if (ConnectedBoard->BoardVector.at(firstNum).at(secondNum) == '.' &&  this->inCombat == true) this->canRetreat = true;
			if (ConnectedBoard->BoardVector.at(firstNum).at(secondNum) == this->m_unitSymbol) this->m_FlanksCount++;
		}
	}
	else if (this->m_unitSymbol == 'O') { // reverse front and rear definitions
			if (this->legionCoord.first != ConnectedBoard->ROWS - 1) {
			int firstNum = this->legionCoord.first;
			int secondNum = this->legionCoord.second;
			pair<int, int>frontCoords{ ++firstNum,secondNum };
			string frontSpace = CoordsToSpace(firstNum, secondNum);
			this->AdjacentCoords["Front"] = frontCoords;
			this->AdjacentSpaces["Front"] = frontSpace;
			//board->BoardVector.at(firstNum).at(secondNum) = 'F';
			if (ConnectedBoard->BoardVector.at(firstNum).at(secondNum) == '.' &&  this->inCombat == true) this->canRetreat = true;
			if (ConnectedBoard->BoardVector.at(firstNum).at(secondNum) == this->m_unitSymbol) this->m_FlanksCount++;
		}
		if (this->legionCoord.first < ConnectedBoard->ROWS && this->legionCoord.first > 0){
			int firstNum = this->legionCoord.first;
			int secondNum = this->legionCoord.second;
			pair<int, int>rearCoords{ --firstNum,secondNum };
			string rearSpace = CoordsToSpace(firstNum, secondNum);
			this->AdjacentCoords["Rear"] = rearCoords;
			this->AdjacentSpaces["Rear"] = rearSpace;
			//board->BoardVector.at(firstNum).at(secondNum) = 'B';
			if (ConnectedBoard->BoardVector.at(firstNum).at(secondNum) == '.' &&  this->inCombat == true) this->canRetreat = true;
			if (ConnectedBoard->BoardVector.at(firstNum).at(secondNum) == this->m_unitSymbol) this->m_FlanksCount++;
		}
	}
	if (this->legionCoord.second != 0 ) { 
		int firstNum = this->legionCoord.first;
		int secondNum = this->legionCoord.second;
		pair<int, int>leftFlankCoords{ firstNum,--secondNum };
		string leftSpace = CoordsToSpace(firstNum, secondNum);
		this->AdjacentCoords["Left"] = leftFlankCoords;
		this->AdjacentSpaces["Left"] = leftSpace;
		//board->BoardVector.at(firstNum).at(secondNum) = 'L';
		if (ConnectedBoard->BoardVector.at(firstNum).at(secondNum) == '.' &&  this->inCombat == true) this->canRetreat = true;
		if (ConnectedBoard->BoardVector.at(firstNum).at(secondNum) == this->m_unitSymbol) this->m_FlanksCount++;
	}
	if (this->legionCoord.second != ConnectedBoard->COLUMNS - 1) {
		int firstNum = this->legionCoord.first;
		int secondNum = this->legionCoord.second;
		pair<int, int>rightFlankCoords{ firstNum,++secondNum };
		string rightSpace = CoordsToSpace(firstNum, secondNum);
		this->AdjacentCoords["Right"] = rightFlankCoords;
		this->AdjacentSpaces["Right"] = rightSpace;
		//board->BoardVector.at(firstNum).at(secondNum) = 'R';
		if (ConnectedBoard->BoardVector.at(firstNum).at(secondNum) == '.' &&  this->inCombat == true) this->canRetreat = true;
		if (ConnectedBoard->BoardVector.at(firstNum).at(secondNum) == this->m_unitSymbol) this->m_FlanksCount++;
	}
}

void Legion::ScoutTargets() {
	this->TargetCoords.clear();
	this->TargetSpaces.clear();
	if (this->m_unitSymbol == 'X') {
		if (this->legionCoord.first < ConnectedBoard->ROWS && this->legionCoord.first > 0 &&
			ConnectedBoard->BoardVector.at(this->AdjacentCoords["Front"].first).at(this->AdjacentCoords["Front"].second) == this->m_enemyUnitSymbol) {
			int firstNum = this->legionCoord.first;
			int secondNum = this->legionCoord.second;
			pair<int, int>frontTargetCoords{ --firstNum,secondNum };
			string frontTargetSpace = CoordsToSpace(firstNum, secondNum);
			this->TargetCoords["Front"] = frontTargetCoords;
			this->TargetSpaces["Front"] = frontTargetSpace;
			this->canAttack = true;
		}
		if (this->legionCoord.first != ConnectedBoard->ROWS - 1 &&
			ConnectedBoard->BoardVector.at(this->AdjacentCoords["Rear"].first).at(this->AdjacentCoords["Rear"].second) == this->m_enemyUnitSymbol) {
			int firstNum = this->legionCoord.first;
			int secondNum = this->legionCoord.second;
			pair<int, int>rearTargetCoords{ ++firstNum,secondNum };
			string rearTargetSpace = CoordsToSpace(firstNum, secondNum);
			this->TargetCoords["Rear"] = rearTargetCoords;
			this->TargetSpaces["Rear"] = rearTargetSpace;
			this->canAttack = true;
		}
	}
	if (this->m_unitSymbol == 'O') {	// reverse front and rear definitions
			if (this->legionCoord.first != ConnectedBoard->ROWS - 1 &&
				ConnectedBoard->BoardVector.at(this->AdjacentCoords["Front"].first).at(this->AdjacentCoords["Front"].second) == this->m_enemyUnitSymbol) {
			int firstNum = this->legionCoord.first;
			int secondNum = this->legionCoord.second;
			pair<int, int>frontTargetCoords{ ++firstNum,secondNum };
			string frontTargetSpace = CoordsToSpace(firstNum, secondNum);
			this->TargetCoords["Front"] = frontTargetCoords;
			this->TargetSpaces["Front"] = frontTargetSpace;
			this->canAttack = true;
		}
			if (this->legionCoord.first < ConnectedBoard->ROWS && this->legionCoord.first > 0 &&
				ConnectedBoard->BoardVector.at(this->AdjacentCoords["Rear"].first).at(this->AdjacentCoords["Rear"].second) == this->m_enemyUnitSymbol) {
			int firstNum = this->legionCoord.first;
			int secondNum = this->legionCoord.second;
			pair<int, int>rearTargetCoords{ --firstNum,secondNum };
			string rearTargetSpace = CoordsToSpace(firstNum, secondNum);
			this->TargetCoords["Rear"] = rearTargetCoords;
			this->TargetSpaces["Rear"] = rearTargetSpace;
			this->canAttack = true;
		}
	}
	if (this->legionCoord.second != 0 && ConnectedBoard->BoardVector.at(this->AdjacentCoords["Left"].first).at(this->AdjacentCoords["Left"].second) == this->m_enemyUnitSymbol) {
		int firstNum = this->legionCoord.first;
		int secondNum = this->legionCoord.second;
		pair<int, int>leftFlankTargetCoords{ firstNum,--secondNum };
		string leftTargetSpace = CoordsToSpace(firstNum, secondNum);
		this->TargetCoords["Left"] = leftFlankTargetCoords;
		this->TargetSpaces["Left"] = leftTargetSpace;
		this->canAttack = true;
	}
	if (this->legionCoord.second != ConnectedBoard->COLUMNS - 1 && ConnectedBoard->BoardVector.at(this->AdjacentCoords["Right"].first).at(this->AdjacentCoords["Right"].second) == this->m_enemyUnitSymbol) {
		int firstNum = this->legionCoord.first;
		int secondNum = this->legionCoord.second;
		pair<int, int>rightFlankTargetCoords{ firstNum,++secondNum };
		string rightTargetSpace = CoordsToSpace(firstNum, secondNum);
		this->TargetCoords["Right"] = rightFlankTargetCoords;
		this->TargetSpaces["Right"] = rightTargetSpace;
		this->canAttack = true;
	}
}

int Legion::ChargeEnemy(Legion &targetedLegion) {
	this->canAttack = false;
	this->canMove = false;
	this->inCombat = true;
	this->SetStance("In Combat");
	targetedLegion.inCombat = true;
	targetedLegion.canMove = false;
	targetedLegion.SetStance("In Combat");
	int range = this->m_MaxDamage - this->m_MinDamage + 1;
	srand(static_cast<unsigned int>(time(0)));
	int chargeDamage = rand() % range + this->m_MinDamage;
	this->AddEngagedLegion(targetedLegion);
	targetedLegion.AddEngagedLegion(*this);
	targetedLegion.TakeDamage(chargeDamage);
	if (targetedLegion.GetMenCount() < 0) targetedLegion.SetMenCount(0);
	return chargeDamage;
}
void Legion::InflictDamage() {
	int attackDamage;
	int range = this->m_MaxDamage - this->m_MinDamage + 1;
	for (auto &target : this->EnemiesEngaged) {
		attackDamage = 0;
		srand(static_cast<unsigned int>(time(0)));
		attackDamage = (rand() % range + this->m_MinDamage);
		attackDamage = (this->m_LegionMen / attackDamage) + attackDamage; // attack based on number of men
		target->TakeDamage(attackDamage);
		this_thread::sleep_for(chrono::seconds(1));
	}

}
void Legion::TakeDamage(int &damage) {
	this->m_LegionMen = this->m_LegionMen - damage;
}

void Legion::DestroyLegion() {
	this->destroyed = true;
	this->canAttack = false;
	this->canMove = false;
	this->inCombat = false;
	this->m_LegionPosition = "";
	ConnectedBoard->BoardVector.at(legionCoord.first).at(legionCoord.second) = '.';
	this->legionCoord.first = 0;
	this->legionCoord.second = 0;
	this->m_LegionMen = 0;
	this->m_EnemiesEngagedCount = 0;
	this->m_FlanksCount = 0;
	this->AdjacentCoords.clear();
	this->AdjacentSpaces.clear();
	this->TargetCoords.clear();
	this->TargetSpaces.clear();
	this->EnemiesEngaged.clear();
	this->ClearMorale();
	this->SetStance("Destroyed");
}

void Legion::AddEngagedLegion(Legion &targetedLegion) {
	this->EnemiesEngaged.emplace_back(&targetedLegion);
	this->m_EnemiesEngagedCount = this->EnemiesEngaged.size();
}
int Legion::GetEngangedCount()const {
	return this->m_EnemiesEngagedCount;
}

void Legion::SetEngagedCount() {
	this->m_EnemiesEngagedCount = this->EnemiesEngaged.size();
}

int Legion::GetFlanksCount()const {
	return this->m_FlanksCount;
}
void Legion::DisengageTargets(vector<Legion> &opponentLegions) {
	this->EnemiesEngaged.clear();
	this->m_EnemiesEngagedCount = this->EnemiesEngaged.size();
	for (auto &engagedLegio : opponentLegions) {
		auto it = find(engagedLegio.EnemiesEngaged.begin(), engagedLegio.EnemiesEngaged.end(), this);
		if (it != engagedLegio.EnemiesEngaged.end()) {
			engagedLegio.EnemiesEngaged.erase(it);
			engagedLegio.SetEngagedCount();
		}
	}
}
bool Legion::ValidMove(char &moveKey) {
	toupper(moveKey);
	if (this->m_unitSymbol == 'X') {
		if (moveKey == 'W') {
			int newRowNum = this->AdjacentCoords["Front"].first;
			int newColumnNum = this->AdjacentCoords["Front"].second;
			if (ConnectedBoard->BoardVector.at(newRowNum).at(newColumnNum) != '.' ||
				find(ConnectedBoard->TopBorderSpaces.begin(), ConnectedBoard->TopBorderSpaces.end(), this->GetLocation()) != ConnectedBoard->TopBorderSpaces.end()) {
				return false;
			}
		}
		if (moveKey == 'S') {
			int newRowNum = this->AdjacentCoords["Rear"].first;
			int newColumnNum = this->AdjacentCoords["Rear"].second;
			if (ConnectedBoard->BoardVector.at(newRowNum).at(newColumnNum) != '.' ||
				find(ConnectedBoard->BottomBorderSpaces.begin(), ConnectedBoard->BottomBorderSpaces.end(), this->GetLocation()) != ConnectedBoard->BottomBorderSpaces.end()) {
				return false;
			}
		}
	}
	if (this->m_unitSymbol == 'O') { // reverse front and rear definitions for player2
		if (moveKey == 'W') {
			int newRowNum = this->AdjacentCoords["Front"].first;
			int newColumnNum = this->AdjacentCoords["Front"].second;
			if (ConnectedBoard->BoardVector.at(newRowNum).at(newColumnNum) != '.' ||
				find(ConnectedBoard->BottomBorderSpaces.begin(), ConnectedBoard->BottomBorderSpaces.end(), this->GetLocation()) != ConnectedBoard->BottomBorderSpaces.end()) {
				return false;
			}
		}
		if (moveKey == 'S') {
			int newRowNum = this->AdjacentCoords["Rear"].first;
			int newColumnNum = this->AdjacentCoords["Rear"].second;
			if (ConnectedBoard->BoardVector.at(newRowNum).at(newColumnNum) != '.' ||
				find(ConnectedBoard->TopBorderSpaces.begin(), ConnectedBoard->TopBorderSpaces.end(), this->GetLocation()) != ConnectedBoard->TopBorderSpaces.end()) {
				return false;
			}
		}
	}
	if (moveKey == 'A') {
		int newRowNum = this->AdjacentCoords["Left"].first;
		int newColumnNum = this->AdjacentCoords["Left"].second;
		if (ConnectedBoard->BoardVector.at(newRowNum).at(newColumnNum) != '.' ||
			find(ConnectedBoard->LeftBorderSpaces.begin(), ConnectedBoard->LeftBorderSpaces.end(), this->GetLocation()) != ConnectedBoard->LeftBorderSpaces.end()) {
			return false;
		}
	}
	if (moveKey == 'D') {
		int newRowNum = this->AdjacentCoords["Right"].first;
		int newColumnNum = this->AdjacentCoords["Right"].second;
		if (ConnectedBoard->BoardVector.at(newRowNum).at(newColumnNum) != '.' ||
			find(ConnectedBoard->RightBorderSpaces.begin(), ConnectedBoard->RightBorderSpaces.end(), this->GetLocation()) != ConnectedBoard->RightBorderSpaces.end()) {
			return false;
		}
	}
	return true;
}

void Legion::MoveLegion(char &moveDirection) {
	toupper(moveDirection);
	if (moveDirection == 'W') {
		int newRowNum = this->AdjacentCoords["Front"].first;
		int newColumnNum = this->AdjacentCoords["Front"].second;
		int currentRowNum = this->legionCoord.first;
		int currentColumnNum = this->legionCoord.second;
		string newPos = this->AdjacentSpaces["Front"];
		this->m_LegionPosition = newPos;
		this->ClearLocation(currentRowNum, currentColumnNum);
		this->SetLocation(newPos, newRowNum, newColumnNum, this->m_unitSymbol);
		this->canAttack = false;
		if (this->isDeployed == true && this->inCombat == false && this->Fleeing == false) this->SetStance("On Guard");
	}
	else if (moveDirection == 'S') {
		int newRowNum = this->AdjacentCoords["Rear"].first;
		int newColumnNum = this->AdjacentCoords["Rear"].second;
		int currentRowNum = this->legionCoord.first;
		int currentColumnNum = this->legionCoord.second;
		string newPos = this->AdjacentSpaces["Rear"];
		this->m_LegionPosition = newPos;
		this->ClearLocation(currentRowNum, currentColumnNum);
		this->SetLocation(newPos, newRowNum, newColumnNum, this->m_unitSymbol);
		this->canAttack = false;
		if (this->isDeployed == true && this->inCombat == false && this->Fleeing == false) this->SetStance("On Guard");
	}
	else if (moveDirection == 'A') {
		int newRowNum = this->AdjacentCoords["Left"].first;
		int newColumnNum = this->AdjacentCoords["Left"].second;
		int currentRowNum = this->legionCoord.first;
		int currentColumnNum = this->legionCoord.second;
		string newPos = this->AdjacentSpaces["Left"];
		this->m_LegionPosition = newPos;
		this->ClearLocation( currentRowNum, currentColumnNum);
		this->SetLocation(newPos, newRowNum, newColumnNum, this->m_unitSymbol);
		this->canAttack = false;
		if (this->isDeployed == true && this->inCombat == false && this->Fleeing == false) this->SetStance("On Guard");
	}
	else if (moveDirection == 'D') {
		int newRowNum = this->AdjacentCoords["Right"].first;
		int newColumnNum = this->AdjacentCoords["Right"].second;
		int currentRowNum = this->legionCoord.first;
		int currentColumnNum = this->legionCoord.second;
		string newPos = this->AdjacentSpaces["Right"];
		this->m_LegionPosition = newPos;
		this->ClearLocation(currentRowNum, currentColumnNum);
		this->SetLocation(newPos, newRowNum, newColumnNum, this->m_unitSymbol);
		this->canAttack = false;
		if (this->isDeployed == true && this->inCombat == false && this->Fleeing == false) this->SetStance("On Guard");
	}
	this->canMove = false;
	this->inCombat = false;
	return;
}
void Legion::FleeLegion() {
	char moveBack = 'S';
	char moveLeft = 'A';
	char moveRight = 'D';
	this->Fleeing = true;
	this->canMove = true;
	this->inCombat = false;
	this->canAttack = false;
	this->SetStance("Fleeing");

	if (find(ConnectedBoard->BottomBorderSpaces.begin(), ConnectedBoard->BottomBorderSpaces.end(), this->m_LegionPosition) != ConnectedBoard->BottomBorderSpaces.end()
		|| find(ConnectedBoard->TopBorderSpaces.begin(), ConnectedBoard->TopBorderSpaces.end(), this->m_LegionPosition) != ConnectedBoard->TopBorderSpaces.end()) {
		this->DestroyLegion(); // destroy fleeing legion when it reaches the borders
		return;
	}
	if (this->ValidMove(moveBack)) {
		this->MoveLegion(moveBack);
		this->EnemiesEngaged.clear();
		this->m_EnemiesEngagedCount = 0;
		this->UpdateLegion();
		this->canMove = false;
	}
	else if (this->ValidMove(moveRight)) {
		this->MoveLegion(moveRight);
		this->EnemiesEngaged.clear();
		this->m_EnemiesEngagedCount = 0;
		this->UpdateLegion();
		this->canMove = false;
	}
	else if (this->ValidMove(moveLeft)) {
		this->MoveLegion(moveLeft);
		this->EnemiesEngaged.clear();
		this->m_EnemiesEngagedCount = 0;
		this->UpdateLegion();
		this->canMove = false;
	}

}

void Legion::UpdateLegion() {
	this->ScoutAdjacents();
	this->ScoutTargets();
	if (this->Fleeing == false)this->RollMorale();
	this -> UpdateMorale();
}
void Legion::UpdateMorale() {
	double moraleBonus = this->m_BaseMorale;
	double flankBonus = 10.0;
	double soldierMorale = 0.05;
	moraleBonus += (flankBonus*this->m_FlanksCount);
	moraleBonus += (soldierMorale * this->m_LegionMen);
	if (moraleBonus > 100.0) {
		moraleBonus = 100.0;
	}
	if (moraleBonus >= 75.0) {
		this->m_MoraleStatus = "Excellent";
	}else if(moraleBonus >= 35.0 ) {
		this->m_MoraleStatus = "Good";
	}else if (moraleBonus >= 25.0) {
		this->m_MoraleStatus = "Low";
	}else if (moraleBonus >= 0.0 && this->inCombat == true) {
		this->m_MoraleStatus = "Wavering";
	}
	if (moraleBonus >= 0.0 && moraleBonus <= 25.0 && this->isDeployed == true && this->destroyed == false && this->inCombat == false && this->Fleeing == false) 
		this->m_MoraleStatus = "Low";
	if (this->isDeployed == true && this->Fleeing == true) this->m_MoraleStatus = "Broken";

	this->m_Morale = moraleBonus;
}

bool Legion::RollMorale() {
	if (this->GetMenCount() > 0 && this->GetMoraleStatus() == "Wavering" && this->inCombat == true || this->GetMoraleStatus() == "Broken" && this->inCombat == false) {
		srand(static_cast<unsigned int>(time(0)));
		double result = (this->GetMoraleValue()*(0.300)); // initially 25 x .300
		result = round(result);
		int routChance = rand() % (int)result;
		if (routChance == 0) {
			this->FleeLegion();
			return true;
		}
		else {
			return false;
		}
	}
}
double Legion::GetMoraleValue()const {
	return this->m_Morale;
};
void Legion::ClearMorale() {
	this->m_Morale = 0;
	this->m_MoraleStatus = "";
}
 string Legion::GetMoraleStatus()const {
	 return this->m_MoraleStatus;
}
void Legion::SetStance(string stance) {
	this->m_Stance = stance;
}

string Legion::GetStance()const {
	return this->m_Stance;
}