#include "Player.h"

Player::Player() 
{
}

Player::Player(const string name, GameBoard *board, vector<GenericPlayer*> &playerlist) :
	ConnectedBoard(board) ,GenericPlayer(board,name,playerlist)
{
	this->PassBoardandName(board, name); // calls function in GenericPlayer
	//cout << m_Pname << " has joined!" << endl;
}

Player::Player(const Player &source):
	ConnectedBoard(source.ConnectedBoard)
{
	//cout << "Player copied" << endl;
}

Player::~Player()
{
}

void Player::DisplayPlayerBoard()const {
	int rowNum = 1;
	cout << right << setw(150) << ConnectedBoard->BoardDivision << endl;
	for (int w = 0; w < 1; w++) {
		cout << "											   ";
		for (int i = 0; i < ConnectedBoard->COLUMNS; i++) {
			cout << right << setw(7) << ConnectedBoard->LetterCoordinates[i];
		}
	}
	cout << "\n";
	for (auto&i : ConnectedBoard->BoardVector) {
		cout << right << setw(90) << "|" << rowNum;
		for (auto&w : i) {
			cout << setw(7) << w << setw(7);
		}

		cout << "|\n\n\n";
		rowNum++;
	}
}

void Player::DisplayUi()const {
	int num = 0;
	DisplayPlayerBoard();
	if (this->inBattleStage == false) {
		ConnectedBoard->DisplayInstructions("[DEPLOYMENT STAGE]: Enter a space to deploy a legion. Enter the same space to remove it.");
	}else {
		ConnectedBoard->DisplayInstructions("[BATTLE STAGE]: Enter the number of a Legion '1,2,3' to select an action.");
		}

	auto ListIterat = LegionList.cbegin(); //cbegin() is a const iterator , rbegin()/rend() for reverse iterators
	//vector<Legion>::const_iterator ListIterat; //also works

	cout << left << setw(89) << "\n" << " | " << this->m_Pname << " | Legions deployed: " << this->deployedLegions << "/" << this->maxLegions
		<< " | Total men: " << this->totalMen << " | Turn #" << ConnectedBoard->turnCount << endl << endl;
	for (ListIterat = LegionList.cbegin(); ListIterat != LegionList.cend(); ListIterat++) {
		if ((*ListIterat).isDeployed == true) {
			num++;
			cout << right << setw(86) << "" << num << ". |" << (*ListIterat).GetLegionName() << ": " << (*ListIterat).GetLocation() << " |" << " Men: " << (*ListIterat).GetMenCount() << " | "
				<< (*ListIterat).GetStance() << ((*ListIterat).GetEngangedCount() == 0 ? "" : (" | Fighting " + to_string((*ListIterat).GetEngangedCount()) + " Legions"))
				<< ((*ListIterat).isDeployed == false ? "" : (" | Flanks Secured: " + to_string((*ListIterat).GetFlanksCount())))
				<< ((*ListIterat).GetMoraleStatus() == "" ? "" : (" | Morale: " + (*ListIterat).GetMoraleStatus())) << endl;
		}
	}
	cout << right << setw(100) << (this->inBattleStage == true ? to_string(++num) + ". |Select All" : "") << endl;
	cout << right << setw(99) << "0. |Next Turn" << endl;
}

void Player::DisplayActionUi()const {
	DisplayPlayerBoard();
	ConnectedBoard->DisplayInstructions("\t\t\tEnter action for: " + SelectedLegion->GetLegionName() + " at " + SelectedLegion->GetLocation());// at() function does bounds checking as opposed to the [] operator.
	cout << endl << right << setw(110) << "Legion Selected: " << SelectedLegion->GetLegionName() << "| Location: " << SelectedLegion->GetLocation() << "| Men: " << SelectedLegion->GetMenCount() 
		<<" | "<< (SelectedLegion->GetEngangedCount() == 0 ? "" : ("Fighting " + to_string(SelectedLegion->GetEngangedCount()) + " Legions"))  << endl;
	cout << endl << right << setw(100) <<(SelectedLegion->inCombat == false ? "1. |Move  " : "	  1. |Disengeage") << endl;
	cout << right << setw(100) << "2. |Attack" << endl;
	cout << right << setw(98) << "B. |Back" << endl;
}

void Player::DisplayMoveDirectionUi()const {
	DisplayPlayerBoard();
	ConnectedBoard->DisplayInstructions(SelectedLegion->isRetreating == false ? ("\t\t\tEnter movement for: " + SelectedLegion->GetLegionName() + " at " + 
		SelectedLegion->GetLocation()): "\t\t\tEnter disengagement for: " + SelectedLegion->GetLegionName() + " at " + SelectedLegion->GetLocation());// at() function does bounds checking as opposed to the [] operator.
	cout << endl << right << setw(110) << "Legion Selected: " << SelectedLegion->GetLegionName() << "| Location: " << SelectedLegion->GetLocation() << "| Men: " << SelectedLegion->GetMenCount() << endl;
	cout << right << setw(109) << "W. |Advance Forward" << endl;
	cout << right << setw(109) << "S. |Retreat a Space" << endl;
	cout << right << setw(104) << "A. |Shift Left" << endl;
	cout << right << setw(105) << "D. |Shift Right" << endl;
	cout << right << setw(98) << "B. |Back" << endl;
}

void Player::DisplayMoveAllDirectionUi()const {
	DisplayPlayerBoard();
	ConnectedBoard->DisplayInstructions("\t\t\tEnter movement for the selected " + to_string(this->deployedLegions) + " legions.");// at() function does bounds checking as opposed to the [] operator.
	cout << right << setw(109) << "W. |Advance Forward" << endl;
	cout << right << setw(109) << "S. |Retreat a Space" << endl;
	cout << right << setw(98) << "B. |Back" << endl;
}

void Player::DisplayConfirmMoveAllUi()const {
	ConnectedBoard->DisplayInstructions("		Confirm move order for all " + to_string(this->deployedLegions) + " legions?");
	cout << endl << right << setw(98) << "1. |Yes" << endl;
	cout << right << setw(101) << "2. |Cancel" << endl;
}
void Player::DisplayConfirmMoveUi()const {
	ConnectedBoard->DisplayInstructions("		Confirm move order for " + SelectedLegion->GetLegionName() + " at " + SelectedLegion->GetLocation() + " ?");
	cout << endl << right << setw(98) << "1. |Yes" << endl;
	cout << right << setw(101) << "2. |Cancel" << endl;
}
void Player::DisplayConfirmAttackUi(Legion &targetedLegion)const {
	ConnectedBoard->DisplayInstructions("Confirm attack order for " + SelectedLegion->GetLegionName() + " at " + SelectedLegion->GetLocation() + " against enemy " + targetedLegion.GetLegionName() + " at " + targetedLegion.GetLocation() + " ?" );
	cout << endl<< right << setw(98) << "1. |Yes" << endl;
	cout << right << setw(101) << "2. |Cancel" << endl;
}

void Player::DisplayChargeDamageUi(Legion &targetedLegion, int damage)const {
	DisplayPlayerBoard();
	cout <<right<<setw(120)<< "Your Legion charges the enemy and inflicts " << damage << " casualties to enemy " << targetedLegion.GetLegionName() << " at " << targetedLegion.GetLocation() << endl;
	cout << endl << right << setw(101) << "1. |Continue" << endl;
}
void Player::DisplayConfirmEndTurnUi()const {
	ConnectedBoard->DisplayInstructions("			Confirm end turn?");
	cout << endl << right << setw(98) << "1. |Yes" << endl;
	cout << right << setw(101) << "2. |Cancel" << endl;
}

void Player::DisplayTargetUi()const {
	int num = 0;
	DisplayPlayerBoard();
	ConnectedBoard->DisplayAnnouncement("Select target for " + SelectedLegion->GetLegionName()+"to attack.");
	cout << endl << right << setw(115) << SelectedLegion->GetLegionName() << "| Location: " << SelectedLegion->GetLocation() << "| Men: " << SelectedLegion->GetMenCount() << endl << endl;
	for (auto &targets : SelectedLegion->TargetSpaces) {
		if (targets.second != "None") {
			num++;
			cout << right << setw(91) << num <<". |Attack enemy Legion at: " <<targets.second << endl;
		}
	}
	if (num == 0) {
		cout << right << setw(120) << "No enemy within reach." << endl;
	}
	cout << right << setw(98) << "B. |Back" << endl;
}

void Player::DeployInput() {
	int indexOffset;
	this->DisplayUi();
	ConnectedBoard->DisplayAnnouncement("\t"+this->m_Pname + "'s turn");
	do {
		cin >> spaceInput;
		//cout << "Input: " << spaceInput << endl;
		if (this->spaceInput == "0" &&  this->deployedLegions > 0) {
			this->isReady = true;
			this->isTurn = false;
			return;
		}
		else if (this->spaceInput == "0" &&  this->deployedLegions == 0) {
			this->DisplayUi();
			ConnectedBoard->DisplayAnnouncement("Must deploy at least one legion before engaging.");
			continue;
		}

		if (this->spaceInput.size() == 2 && isalpha(this->spaceInput[0]) && isdigit(this->spaceInput[1])) {
			letterInput = toupper(this->spaceInput[0]);
			numberInput = atoi(&this->spaceInput[1]); //atoi function converts strings or chars to integers. int atoi(const char *str);
			indexOffset = numberInput - 1;
			this->spaceInput = letterInput + to_string(numberInput);
			BoardIndex indices = this->SearchSpace(this->spaceInput, letterInput, indexOffset);
			if ( indices.Placing == true && this->IsInDeploymentZone(spaceInput) && this->deployedLegions < this->maxLegions) {
				this->PlaceLegion(spaceInput, indices.rows, indices.columns);
				this->DisplayUi();
				ConnectedBoard->DisplayAnnouncement("Deploying legion at: " + spaceInput);
			}
			else if ( indices.Placing == false && this->IsInDeploymentZone(spaceInput)) {
				this->RemoveLegion(spaceInput, indices.rows, indices.columns);
				this->DisplayUi();
				ConnectedBoard->DisplayAnnouncement("Removing legion at: " + spaceInput);
			}
			else if (this->deployedLegions == this->maxLegions) {
				this->DisplayUi();
				ConnectedBoard->DisplayAnnouncement("No legions left to deploy.");
			}
			else if (this->spaceInput.size() == 2 && !this->IsInDeploymentZone(spaceInput)) {
				this->DisplayUi();
				ConnectedBoard->DisplayAnnouncement("Must deploy within the deployment zone");
			}
		}
		else {
			this->DisplayUi();
			ConnectedBoard->DisplayAnnouncement("Invalid space input.");
		}
	} while (this->isReady = true);
	ClearInput();
	return;
}

void Player::SelectLegion() { // At battle stage
	size_t  legionSelect = 0;
	size_t indexSelect = 0;
	int movableLegions;
	this->DisplayUi();
	ConnectedBoard->DisplayAnnouncement("\t" + this->m_Pname + "'s turn");
	do {
		this->SelectedLegion = 0;
		cin >> legionSelect;
		try {
			indexSelect = legionSelect;
			indexSelect = indexSelect == 0 ? 0: (indexSelect = legionSelect) - 1;
			movableLegions = this->GetMovableLegions();
			if (legionSelect != maxLegions + 1 && indexSelect < maxLegions) this->SelectedLegion = &LegionList.at(indexSelect);
			if (legionSelect > maxLegions + 1 || legionSelect < 0 || this->SelectedLegion == NULL ) {
				throw 4;
			}
			if (legionSelect > 0 && legionSelect <= maxLegions && SelectedLegion->isDeployed == true && SelectedLegion->destroyed == false && SelectedLegion->Fleeing == false) {
				this->SelectAction();
			}
			else if (legionSelect > 0 &&  legionSelect == this->deployedLegions + 1 && movableLegions !=0) { // move all
				this->SelectMoveAllDirection();
			}
			else if (legionSelect > 0 && movableLegions == 0 && legionSelect == this->deployedLegions + 1  ) {
				this->DisplayUi();
				ConnectedBoard->DisplayAnnouncement("No legions are able to move.");
				ClearInput();
			}
			else if (legionSelect == 0 && indexSelect == 0) { // next turn
				if (ConfirmTurn()) {
					this->NextTurn();
					continue;
				}
				else {
					continue;
				}
			}
			else if (SelectedLegion->isDeployed == true && SelectedLegion->destroyed == true) {
				this->DisplayUi();
				ConnectedBoard->DisplayAnnouncement("This legion has been destroyed.");
				ClearInput();
			}
			else if (SelectedLegion->isDeployed == true && SelectedLegion->destroyed == false && SelectedLegion->Fleeing == true) {
				this->DisplayUi();
				ConnectedBoard->DisplayAnnouncement("This legion is fleeing.");
				ClearInput();
			}
			else {
				this->DisplayUi();
				ConnectedBoard->DisplayAnnouncement("Invalid input.");
				ClearInput();
			}
		}
		catch (int) {
			this->DisplayUi();
			ConnectedBoard->DisplayAnnouncement("Invalid input.");
			ClearInput();
		}
	} while (this->isTurn);
}

void Player::SelectAction() {
	char actionSelect = ' ';
	this->DisplayActionUi();
	do {
		cin >> actionSelect;
		actionSelect = toupper(actionSelect);
		if (atoi(&actionSelect) == 1 && SelectedLegion->canMove == true && SelectedLegion->inCombat == false ) {
			SelectMoveDirection();
		}else if (atoi(&actionSelect) == 1 && SelectedLegion->inCombat == true && SelectedLegion->canRetreat == true) { // retreat move
			SelectDisengageDirection();
		}
		else if (atoi(&actionSelect) == 2 && SelectedLegion->inCombat == false && SelectedLegion->canAttack == true && SelectedLegion->canMove == true) {
			SelectTarget();
		}
		else if (atoi(&actionSelect) == 2 && SelectedLegion->inCombat == false && SelectedLegion->canAttack == false && SelectedLegion->canMove == false) {
			this->DisplayActionUi();
			ConnectedBoard->DisplayAnnouncement("This Legion cannot attack this turn.");
		}
		else if (atoi(&actionSelect) == 1 && SelectedLegion->canMove == false && SelectedLegion->canAttack == false 
			|| atoi(&actionSelect) == 2 && SelectedLegion->canMove == false && SelectedLegion->canAttack == false ) {
			this->DisplayActionUi();
			ConnectedBoard->DisplayAnnouncement("This Legion has already moved this turn.");
			ClearInput();
		}
		else if (atoi(&actionSelect) == 2 && SelectedLegion->inCombat == false && SelectedLegion->canAttack == false && SelectedLegion->canMove == true) {
			this->DisplayActionUi();
			ConnectedBoard->DisplayAnnouncement("No enemies near to attack.");
		}else if (actionSelect == 'B') {
			ConnectedBoard->DisplayAnnouncement("");
			ClearInput();
		}
		else if (atoi(&actionSelect) == 2 && this->SelectedLegion->inCombat == true) {
			this->DisplayActionUi();
			ConnectedBoard->DisplayAnnouncement("This Legion is already in combat.");
			ClearInput();
		}
		else {
			this->DisplayActionUi();
			ConnectedBoard->DisplayAnnouncement("Invalid input.");
			ClearInput();
		}
	} while (actionSelect != 'B');
	this->DisplayUi();
}

void Player::SelectMoveDirection() {
	char moveSelect = ' ';
	this->DisplayMoveDirectionUi();
	do {
	cin >> moveSelect;
	moveSelect = toupper(moveSelect);
	if (moveSelect == 'W' || moveSelect == 'A' || moveSelect == 'S' || moveSelect == 'D') {
		if (this->SelectedLegion->canMove == true && SelectedLegion->ValidMove(moveSelect) && this->ConfirmMove()) {
			this->SelectedLegion->MoveLegion(moveSelect);
			for (auto &legio : this->LegionList) {
				if (legio.isDeployed == true) {
					legio.UpdateLegion();
				}
			}
			this->DisplayActionUi();
			ConnectedBoard->DisplayAnnouncement("Legion moved to " + SelectedLegion->GetLocation() + ".");
			return;
		}
		else if (!SelectedLegion->ValidMove(moveSelect)) {
			this->DisplayMoveDirectionUi();
			ConnectedBoard->DisplayAnnouncement("Invalid move.");
			ClearInput();
		}
	}
	else if (moveSelect == 'B') {
		ConnectedBoard->DisplayAnnouncement("");
		ClearInput();
	}
	else {
		this->DisplayMoveDirectionUi();
		ConnectedBoard->DisplayAnnouncement("Invalid input.");
		ClearInput();
	}
	} while (moveSelect != 'B');
	this->DisplayActionUi();
}

void Player::SelectMoveAllDirection() { 
	char moveSelect = ' ';
	int movedLegions;
	int movableLegions = 0;
	this->DisplayMoveAllDirectionUi();
	do {
		cin >> moveSelect;
		moveSelect = toupper(moveSelect);
		movableLegions = this->GetMovableLegions();
		if (moveSelect == 'W' && this->GetMovableLegions() != 0 &&  this->ConfirmMoveAll() || moveSelect == 'S'&& this->GetMovableLegions() != 0 && this->ConfirmMoveAll()) {
			movedLegions = this->MoveLegions(moveSelect);
				if (movedLegions > 0) {
					this->DisplayMoveAllDirectionUi();
					ConnectedBoard->DisplayAnnouncement(to_string(movedLegions) + " legions of " + to_string(this->deployedLegions) + " legions were successfully moved");
				}
				else if (movedLegions == 0) {
					this->DisplayMoveAllDirectionUi();
					ConnectedBoard->DisplayAnnouncement("No legions could be moved.");
				}
				continue;
		}
		else if (moveSelect != 'B' && movableLegions == 0) {
			this->DisplayMoveAllDirectionUi();
			ConnectedBoard->DisplayAnnouncement("No legions are able to move.");
			ClearInput();
		}
		else if (moveSelect == 'B') {
			ConnectedBoard->DisplayAnnouncement("");
			ClearInput();
		}
		else {
			this->DisplayMoveAllDirectionUi();
			ConnectedBoard->DisplayAnnouncement("Invalid input.");
			ClearInput();
		}
	} while (moveSelect != 'B');
	this->DisplayUi();
}
void Player::SelectDisengageDirection() {
	char retreatSelect = ' ';
	this->SelectedLegion->isRetreating = true;
	this->DisplayMoveDirectionUi();
	do {
		cin >> retreatSelect;
		retreatSelect = toupper(retreatSelect);
		if (retreatSelect == 'W' || retreatSelect == 'A' || retreatSelect == 'S' || retreatSelect == 'D') {
			if (SelectedLegion->ValidMove(retreatSelect) && this->ConfirmMove() && this->RollDisengagement()) {
				int casualties = this->DisengagementCasualties();
				this->SelectedLegion->MoveLegion(retreatSelect);
				this->SelectedLegion->canRetreat = false;
				this->SelectedLegion->inCombat = false;
				this->SelectedLegion->DisengageTargets(this->Opponent->LegionList);
				this->DisplayActionUi();
				if (SelectedLegion->destroyed == false) {
					for (auto &legio : this->LegionList) {
						if (legio.isDeployed == true) {
							legio.UpdateLegion();
						}
					}
				ConnectedBoard->DisplayAnnouncement("Legion disengaged to " + SelectedLegion->GetLocation() + " but suffered " + to_string(casualties) + " casualties.");
				}else if (SelectedLegion->destroyed == true) {
					for (auto &legio : this->LegionList) {
						if (legio.isDeployed == true) {
							legio.UpdateLegion();
						}
					}
				ConnectedBoard->DisplayAnnouncement(this->SelectedLegion->GetLegionName() + " has been destroyed during the disengagement");
				}
				return;
			}
			else if (!SelectedLegion->ValidMove(retreatSelect)) {
				this->DisplayMoveDirectionUi();
				ConnectedBoard->DisplayAnnouncement("Invalid disengagement move.");
				ClearInput();
			}
			else {
				int casualties = this->DisengagementCasualties();
				this->DisplayActionUi();
				this->SelectedLegion->canRetreat = false;
				this->SelectedLegion->inCombat = false;
				if (SelectedLegion->destroyed == false) {
				ConnectedBoard->DisplayAnnouncement(this->SelectedLegion->GetLegionName() + " failed to disengage from battle and suffered " + to_string(casualties) + " casualties.");
				}
				else if (SelectedLegion->destroyed == true) {
					ConnectedBoard->DisplayAnnouncement(this->SelectedLegion->GetLegionName() + " has been destroyed during the disengagement");
				}
				ClearInput();
			}
		}
		else if (retreatSelect == 'B') {
			ConnectedBoard->DisplayAnnouncement("");
			ClearInput();
		}
		else {
			this->DisplayMoveDirectionUi();
			ConnectedBoard->DisplayAnnouncement("Invalid input.");
			ClearInput();
		}
	} while (retreatSelect != 'B');
	this->SelectedLegion->isRetreating = false;
	this->DisplayActionUi();
}
void Player::SelectTarget() { //ATTACK
	char moveSelect = ' ';
	string selectedTargetSpace;
	int targetCount = 0;
	Legion *enemyLegionTarget = 0; // enemy legion to be targeted
	this->DisplayTargetUi();
	map <int,string> AvailableTargets;
	for (auto &targets : SelectedLegion->TargetSpaces) {
		if (targets.second != "None") {
			targetCount++;
			selectedTargetSpace = targets.second;
			AvailableTargets.insert(make_pair(targetCount, selectedTargetSpace));
		}
	}
	do{
	cin >> moveSelect;
	moveSelect = toupper(moveSelect);
	for (auto &i : Opponent->LegionList) { // target display list
		if (AvailableTargets[atoi(&moveSelect)] == i.GetLocation()) {
			i.ScoutTargets();
			enemyLegionTarget = &i;
			break;
		}
	}
	if (enemyLegionTarget != NULL && atoi(&moveSelect) > 0 && atoi(&moveSelect) <= targetCount && this->SelectedLegion->canAttack == true
		&& this->SelectedLegion->inCombat == false) {
		int damageDone = 0;
		if (this->ConfirmAttack(*enemyLegionTarget)) {
			damageDone = SelectedLegion->ChargeEnemy(*enemyLegionTarget);
			this->ChargeOutcome(*enemyLegionTarget, damageDone);
			this->DisplayActionUi();
			return;
		}
		else {
			this->DisplayTargetUi();
			ConnectedBoard->DisplayAnnouncement("");
			continue;
		}
	}
	else if (isalpha(moveSelect) && moveSelect == 'B') {
		ConnectedBoard->DisplayAnnouncement("");
		ClearInput();
	}
	else  {
		this->DisplayTargetUi();
		ConnectedBoard->DisplayAnnouncement("Invalid target.");
		ClearInput();
	}
	}while (!isalpha(moveSelect) || (char)moveSelect != 'B');
	this->DisplayActionUi();
}

bool Player::ConfirmMove() {
	int confirmSelect = 0;
	this->DisplayPlayerBoard();
	this->DisplayConfirmMoveUi();
	do {
		cin >> confirmSelect;
		if (confirmSelect == 1 )
			return true;
		else if (confirmSelect == 2) {
			this->DisplayMoveDirectionUi();
			return false;
		}
		else {
			this->DisplayPlayerBoard();
			this->DisplayConfirmMoveUi();
			ConnectedBoard->DisplayAnnouncement("Invalid input.");
			ClearInput();
		}
	} while (confirmSelect != 2);
	this->DisplayMoveDirectionUi();
}

bool Player::ConfirmMoveAll() {
	int confirmSelect = 0;
	this->DisplayPlayerBoard();
	this->DisplayConfirmMoveAllUi();
	do {
		cin >> confirmSelect;
		if (confirmSelect == 1)
			return true;
		else if (confirmSelect == 2) {
			return false;
		}
		else {
			this->DisplayPlayerBoard();
			this->DisplayConfirmMoveAllUi();
			ConnectedBoard->DisplayAnnouncement("Invalid input.");
			ClearInput();
		}
	} while (confirmSelect != 2);
	this->DisplayMoveAllDirectionUi();
}
bool Player::ConfirmAttack(Legion &targetedLegion) {
	int confirmSelect = 0;
	this->DisplayPlayerBoard();
	this->DisplayConfirmAttackUi(targetedLegion);
	do {
		cin >> confirmSelect;
		if (confirmSelect == 1)
			return true;
		else if (confirmSelect == 2) {
			ClearInput();
			return false;
		}
		else {
			this->DisplayPlayerBoard();
			this->DisplayConfirmAttackUi(targetedLegion);
			ConnectedBoard->DisplayAnnouncement("Invalid input.");
			ClearInput();
		}
	} while (confirmSelect != 2);
}

void Player::ChargeOutcome(Legion &targetedLegion, int damage) {
	int select = 0;
	this->DisplayChargeDamageUi(targetedLegion, damage);
	do {
		cin >> select;
		if (select == 1) {
			ClearInput();
			return;
		}
		else {
			this->DisplayChargeDamageUi(targetedLegion, damage);
			ConnectedBoard->DisplayAnnouncement("Invalid input.");
			ClearInput();
		}

	} while (select != 1);
}
bool Player::ConfirmTurn() {
	int confirmSelect = 0;
	this->DisplayPlayerBoard();
	this->DisplayConfirmEndTurnUi();
	do {
		cin >> confirmSelect;
		if (confirmSelect == 1) {
			return true;
		}
		else if (confirmSelect == 2) {
			this->DisplayUi();
			ConnectedBoard->DisplayAnnouncement("");
			ClearInput();
			return false;
		}
		else {
			this->DisplayPlayerBoard();
			this->DisplayConfirmEndTurnUi();
			ConnectedBoard->DisplayAnnouncement("Invalid input.");
			ClearInput();
		}
	} while (confirmSelect != 2);
}
void Player::NextTurn() {
	this->isTurn = false;
	this->Opponent->isTurn = true;
	this->Opponent->isTurn = true;
	this->UpdateBattle();
	ConnectedBoard->AddTurn();
	return;
}

void Player::ClearInput() { // Clears buffer
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignores everything up to end of line.
}

