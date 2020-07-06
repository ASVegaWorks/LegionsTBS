#include"TitleScreen.h"

void TitleScreen::GetTitle() {
	cout << right << setw(180) << "      ===================================================================================================================================\n";
	cout << right << setw(180) << "                                                                                                                                         \n";
	cout << right << setw(180) << "        VIVIVIV           VIVIVIVIVIVIV    VIVIVIVIVIVIVIIV    IVIVIVIV     IVIVIVIVIVVIVIVI    VIVIVIV       IVIVIV    VIVIVIVIVIVIVI  \n";
	cout << right << setw(180) << "          IVIVI             IVIVIVIVIVIV     IVIVIVIVIVIVIIV      IVIV       IVIVIVIVIVIVIVIV     IVIVIVI       VIVI      IVIVIVIVIVIVI  \n";
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

void TitleScreen::HowToPlay() {
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

TitleScreen::TitleScreen()
{
}


TitleScreen::~TitleScreen()
{
}
