#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <windows.h>
#include <cmath>


using namespace std;

class Player
{
public:

	string name;
	int PlayerNumber;
	double BatSucessRate;
	int runs;
	int ballsFaced;
	string type;
	double BallSucessRate;
	double wicketBallRate;
	double oversBowled;
	int runsConceded;
	int wicketsTaken;

	Player* next;

	Player(int n, string N, double bat, string x, double ball, double wball, int s, int B, double o, int rc, int w)
	{
		PlayerNumber = n;
		name = N;
		BatSucessRate = bat;
		runs = s;
		ballsFaced = B;
		type = x;
		BallSucessRate = ball;
		wicketBallRate = wball;
		oversBowled = o;
		runsConceded = rc;
		wicketsTaken = w;

		next = NULL;
	}
};

class PlayersList
{
public:
	Player* start;

	PlayersList()
	{
		start = NULL;
	}

	void insertPlayer(int n, string N, double bat, string x = "bat", double ball = 0, double wball = 0, int s = 0, int B = 0, double o = 0, int rc = 0, int w = 0)
	{
		Player* newPlayer = new Player(n, N, bat, x, ball, wball, s, B, o, rc, w);

		if (start == NULL)
		{
			start = newPlayer;
		}
		else
		{
			Player* ptr = start;
			int count = 1;
			while (ptr->next != NULL)
			{
				ptr = ptr->next;
				count++;
			}
			if (count > 11)
			{
				cout << "Too many players in the team!" << endl;
				return;
			}
			else
			{
				ptr->next = newPlayer;
			}

		}
	}

	Player* searchPlayer(int n)
	{
		if (start == NULL)
		{
			cout << "There are no players in the team!" << endl;
			return NULL;
		}
		else
		{
			Player* ptr = start;
			while (ptr->next != NULL)
			{
				if (ptr->PlayerNumber == n)
				{
					break;
				}
				ptr = ptr->next;
			}

			return ptr;

		}

	}

	int getPlayerNo(int x)
	{
		Player* ptr = start;
		int count = 1;
		if (start == NULL)
		{
			cout << "There are no players in the team!" << endl;
			return -1;
		}
		else
		{
			while (ptr->next != NULL)
			{
				if (count == x)
				{
					break;
				}
				ptr = ptr->next;
				count++;
			}
			return ptr->PlayerNumber;
		}
	}

	void showPlayers()
	{
		Player* ptr = start;
		if (start == NULL)
		{
			cout << "There are no players in the team!" << endl;
			return;
		}
		else
		{
			while (ptr->next != NULL)
			{
				cout << ptr->PlayerNumber << " " << ptr->name << " " << ptr->BatSucessRate << " " << ptr->type << " " << ptr->BallSucessRate << endl;
				ptr = ptr->next;
			}
		}
	}
};

class Team
{
public:
	string teamName;
	PlayersList players;
	int	totalRuns;
	double oversBowled;
	int totalWickets;
	int extras;

	Team()
	{
		totalRuns = 0;
		oversBowled = 0;
		totalWickets = 0;
		extras = 0;
	}
};

class Match
{
public:
	Team* team1;
	Team* team2;
	Player* batsman1;
	Player* batsman2;
	Player* bowler;
	int batsmanArr[11];
	int bowlerArr[5];
	double currentRunRate;
	double requiredRunRate;


	Match()
	{
		team1 = new Team();
		team2 = new Team();
		batsman1 = NULL;
		batsman2 = NULL;
		bowler = NULL;
		currentRunRate = 0;
		requiredRunRate = 0;
	}
};

class Scoreboard
{
public:
	Match match;
	int total;
	double overs;
	int wickets;
	int extras;
	int ball;

	Scoreboard(Match& m, Team* t, int b)
	{
		match = m;
		total = t->totalRuns;
		overs = t->oversBowled;
		wickets = t->totalWickets;
		extras = t->extras;
		ball = b;
	}

	void displayScoreboard1()
	{
		cout << "			                1st ING SCOREBOARD			" << endl;
		cout << "************************************************************************************************************************************************" << endl;
		cout << match.team1->teamName << " " << match.team1->totalRuns << "/" << match.team1->totalWickets << "  " << match.team1->oversBowled << "." << ball % 6 << "			|" << match.batsman1->name << "* " << match.batsman1->runs << "		|" << match.batsman2->name << " " << match.batsman2->runs << "		" << match.bowler->name << " " << match.bowler->oversBowled << "-" << match.bowler->runsConceded << "-" << match.bowler->wicketsTaken <<"  (Bowler name-Numberof Overs-Runs-Number Of wickets)" <<endl;
		cout << "CRR: " << match.currentRunRate << endl;
		cout << "***********************************************************************************************************************************************" << endl;
		cout << endl;
	}

	void displayScoreboard2()
	{
		cout << "			                2 nd ING SCOREBOARD			" << endl;
		cout << "***********************************************************************************************************************************************" << endl;
		cout << match.team2->teamName << " " << match.team2->totalRuns << "/" << match.team2->totalWickets << "  " << match.team2->oversBowled << "." << ball % 6 << "   |" << match.batsman1->name << "* " << match.batsman1->runs << "	    |" << match.batsman2->name << match.batsman2->runs << "		" << match.bowler->name << " " << match.bowler->oversBowled << "-" << match.bowler->runsConceded << "-" << match.bowler->wicketsTaken<< "  (Bowler name-Numberof Overs-Runs-Number Of wickets)" << endl;
		cout << "CRR: " << match.currentRunRate << " " << "Req RR: " << match.requiredRunRate << endl;
		cout << "***********************************************************************************************************************************************" << endl;
		cout << endl;
	}
};

void scoringRuns(Match& m, Team* t, int& in);
Player* selectBowler(Match& m, Team* t, int n, int x);
void displayMatchSummary(Match match);

int main() {
	Match match;

		match.team1->teamName = "TeamA";
		match.team2->teamName = "TeamB";

		int ball = 0;

		ifstream inputFile("Teams.txt");
		if (!inputFile.is_open())
		{
			cerr << "Error opening file." << endl;
			return 1;
		}

		string line;
		while (getline(inputFile, line))
		{
			istringstream iss(line);

			int word1 = 0;
			string word2;
			double word3 = 0;
			string word4;
			string word5;
			double word6 = 0;
			double word7 = 0;

			if (iss >> word1 >> word2 >> word3 >> word4 >> word5 >> word6 >> word7)
			{
				if (word4 == "TeamA")
				{
					match.team1->players.insertPlayer(word1, word2, word3, word5, word6, word7);
				}
				else if (word4 == "TeamB")
				{
					match.team2->players.insertPlayer(word1, word2, word3, word5, word6, word7);
				}
			}
			else {
				cerr << "Error extracting words." << endl;
			}
		}

		inputFile.close();

		for (int i = 0; i < 11; i++)
		{
			match.batsmanArr[i] = match.team1->players.getPlayerNo(i + 1);
		}

		for (int i = 0; i < 5; i++)
		{
			match.bowlerArr[i] = match.team2->players.getPlayerNo(i + 7);
		}

		match.batsman1 = match.team1->players.start;
		match.batsman2 = match.team1->players.start->next;

		match.bowler = match.team2->players.searchPlayer(match.bowlerArr[rand() % 5]);
		int ballValue = 0;
		int ballStat = 0;
		int batValue = 0;
		int batStat = 0;
		int batIn = 1;

		while (ball <= 30 && match.team1->totalWickets < 5)
		{
			Scoreboard s1(match, match.team1, ball);
			if (ball == 0)
			{
				s1.displayScoreboard1();
				Sleep(1200);
				system("cls");
			}

			ballValue = 1 + (rand() % 100);
			if (ballValue <= match.bowler->BallSucessRate)
			{
				scoringRuns(match, match.team1, batIn);


				ball++;
				match.batsman1->ballsFaced++;
				if (ball % 6 == 0)
				{
					match.team1->oversBowled++;
					match.bowler->oversBowled++;
					Player* temp;
					temp = match.batsman1;
					match.batsman1 = match.batsman2;
					match.batsman2 = temp;
					match.bowler = selectBowler(match, match.team2, rand() % 5, match.bowler->PlayerNumber);
				}
			}
			else
			{
				match.team1->totalRuns++;
				match.team1->extras++;
				match.bowler->runsConceded++;
			}



			match.currentRunRate = match.team1->totalRuns / match.team1->oversBowled;
			s1.displayScoreboard1();
			Sleep(1200);
			system("cls");
		}


		cout << "***********************End Of First Inning & Let's Start Second Inning***********************" << endl;
		Sleep(4000);


		ball = 0;
		for (int i = 0; i < 11; i++)
		{
			match.batsmanArr[i] = match.team2->players.getPlayerNo(i + 1);
		}

		for (int i = 0; i < 5; i++)
		{
			match.bowlerArr[i] = match.team1->players.getPlayerNo(i + 7);
		}

		match.batsman1 = match.team2->players.start;
		match.batsman2 = match.team2->players.start->next;
		match.currentRunRate = 0;
		match.requiredRunRate = 0;

		match.bowler = match.team1->players.searchPlayer(match.bowlerArr[rand() % 5]);
		ballValue = 0;
		ballStat = 0;
		batValue = 0;
		batStat = 0;
		batIn = 1;

		while (ball <= 30 && match.team2->totalRuns <= match.team1->totalRuns && match.team2->totalWickets < 5)
		{
			Scoreboard s2(match, match.team1, ball);
			if (ball == 0)
			{
				s2.displayScoreboard2();
				Sleep(3000);
				system("cls");
			}

			ballValue = 1 + (rand() % 100);
			if (ballValue <= match.bowler->BallSucessRate)
			{
				scoringRuns(match, match.team2, batIn);


				ball++;
				match.batsman1->ballsFaced++;
				if (ball % 6 == 0)
				{
					match.team2->oversBowled++;
					match.bowler->oversBowled++;
					Player* temp;
					temp = match.batsman1;
					match.batsman1 = match.batsman2;
					match.batsman2 = temp;
					match.bowler = selectBowler(match, match.team1, rand() % 5, match.bowler->PlayerNumber);
				}
			}
			else
			{
				match.team2->totalRuns++;
				match.team2->extras++;
				match.bowler->runsConceded++;
			}

			match.currentRunRate = match.team2->totalRuns / match.team2->oversBowled;
			match.requiredRunRate = (match.team1->totalRuns - match.team2->totalRuns) / (10 - match.team1->oversBowled);
			s2.displayScoreboard2();
			Sleep(1000);
			system("cls");
		}

		displayMatchSummary(match);
		Sleep(5000);

	return 0;
}

void scoringRuns(Match& m, Team* t, int& in)
{
	Player* temp;
	int batValue = 1 + (rand() % 100);
	if (batValue <= m.batsman1->BatSucessRate) {
		int batStat = 1 + (rand() % 100);
		if (batStat <= 45)
		{
			t->totalRuns = t->totalRuns + 1;
			m.batsman1->runs = m.batsman1->runs + 1;
			m.batsman1->ballsFaced++;
			m.bowler->runsConceded = m.bowler->runsConceded + 1;
			temp = m.batsman1;
			m.batsman1 = m.batsman2;
			m.batsman2 = temp;
		}
		else if (45 < batStat && batStat <= 65)
		{
			t->totalRuns = t->totalRuns + 2;
			m.batsman1->runs = m.batsman1->runs + 2;
			m.batsman1->ballsFaced++;
			m.bowler->runsConceded = m.bowler->runsConceded + 2;
		}
		else if (65 < batStat && batStat <= 70)
		{
			t->totalRuns = t->totalRuns + 3;
			m.batsman1->runs = m.batsman1->runs + 3;
			m.batsman1->ballsFaced++;
			m.bowler->runsConceded = m.bowler->runsConceded + 3;
			temp = m.batsman1;
			m.batsman1 = m.batsman2;
			m.batsman2 = temp;
		}
		else if (70 < batStat && batStat <= 82)
		{
			t->totalRuns = t->totalRuns + 4;
			m.batsman1->runs = m.batsman1->runs + 4;
			m.batsman1->ballsFaced++;
			m.bowler->runsConceded = m.bowler->runsConceded + 4;
		}
		else if (82 < batStat && batStat <= 90)
		{
			t->totalRuns = t->totalRuns + 4;
			m.batsman1->runs = m.batsman1->runs + 4;
			m.batsman1->ballsFaced++;
			m.bowler->runsConceded = m.bowler->runsConceded + 6;
		}
		else
		{
			//wicket by catch
			t->totalWickets++;
			m.bowler->wicketsTaken++;
			m.batsman1->ballsFaced++;
			in++;
			m.batsman1 = t->players.searchPlayer(m.batsmanArr[in]);
		}
	}
	else
	{

		int noBatValue = 1 + (rand() % 100);
		if (noBatValue <= m.bowler->wicketBallRate)
		{

			t->totalWickets++;
			m.bowler->wicketsTaken++;
			m.batsman1->ballsFaced++;
			in++;
			m.batsman1 = t->players.searchPlayer(m.batsmanArr[in]);
		}
		else
		{

			m.batsman1->ballsFaced++;
		}
	}
}

Player* selectBowler(Match& m, Team* t, int n, int x)
{
	int No = m.bowlerArr[n];
	Player* ptr = t->players.searchPlayer(No);
	while (No == x && ptr->oversBowled >= 4)
	{
		n = rand() % 5;
		No = m.bowlerArr[n];
	}
	return ptr;
}

void displayMatchSummary(Match match) {
	cout << "Match Summary:" << endl;
	cout << "----------------------" << endl;
	cout << "Team 1: " << match.team1->teamName << " - " << match.team1->totalRuns << "/" << match.team1->totalWickets << " in " << match.team1->oversBowled << " overs" << endl;
	cout << "      Extras: " << match.team1->extras << endl;

	cout << "Batting Performances:" << endl;
	cout << "----------------------" << endl;
	for (int i = 0; i < 11; i++) {
		Player* player = match.team1->players.searchPlayer(i);
		cout << player->name << ": " << player->runs << " runs (" << player->ballsFaced << " balls)" << endl;
	}

	cout << "Bowling Performances:" << endl;
	cout << "----------------------" << endl;
	for (int i = 0; i < 5; i++) {
		Player* player = match.team1->players.searchPlayer(i + 7);
		cout << player->name << ": " << player->oversBowled << " overs, " << player->runsConceded << " runs, " << player->wicketsTaken << " wickets" << endl;
	}

	cout << "----------------------" << endl;
	cout << "Team 2: " << match.team2->teamName << " - " << match.team2->totalRuns << "/" << match.team2->totalWickets << " in " << match.team2->oversBowled << " overs" << endl;
	cout << "      Extras: " << match.team2->extras << endl;

	cout << "Batting Performances:" << endl;
	cout << "----------------------" << endl;
	for (int i = 0; i < 11; i++) {
		Player* player = match.team2->players.searchPlayer(i);
		cout << player->name << ": " << player->runs << " runs (" << player->ballsFaced << " balls)" << endl;
	}

	cout << "Bowling Performances:" << endl;
	cout << "----------------------" << endl;
	for (int i = 0; i < 5; i++) {
		Player* player = match.team2->players.searchPlayer(i + 7);
		cout << player->name << ": " << player->oversBowled << " overs, " << player->runsConceded << " runs, " << player->wicketsTaken << " wickets" << endl;
	}
}
