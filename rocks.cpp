#define _CRT_SECURE_NO_DEPRECATE
#include <cstring>
#include <iostream>
#include "utilities.h"
#include <cctype>
using namespace std;

int manageOneRound(const char words[][MAXWORDLEN+1], int nWords, int wordnum)
{
	if (nWords <= 0 || wordnum < 0 || wordnum >= nWords)
		return -1;
	int roundScore = 0;
	char secWordCpy[100] = "";
	char probe[100] = ""; 
	char shadowProbe[100] = "";  //(ow, the edge) this cstring keeps the probe word unchanged in the following loops
	while (strcmp(shadowProbe, words[wordnum]) != 0)
	{
		int rocks = 0;
		int pebbles = 0;
		strcpy(secWordCpy, words[wordnum]);
		strcpy(shadowProbe, ""); 
		strcpy(probe, "");
		cout << "Probe word: ";
		cin.getline(shadowProbe, 100);
		strcpy(probe, shadowProbe); //I made a copy of the probe word that I can change 
		if (strlen(probe) < 4 || strlen(probe) > 6)
		{
			cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
			continue;
		}
		else
		{
			int i;
			for (i = 0; probe[i] != '\0'; i++)
				if (!islower(probe[i]))
				{
					cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
					break;
				}
			if (probe[i] != '\0')
				continue;
		}
		for (int j = 0; j < nWords; j++)  //checks all words in array
		{
			if (strcmp(probe, words[j]) == 0)
			{
				for (int k = 0; words[wordnum][k] != '\0'; k++) //checks all chars in secret word
				{
					for (int l = 0; probe[l] != '\0'; l++) //checks all chars in probe word
					{
						if (probe[l] == secWordCpy[k] && l == k)
						{
								rocks++;	//finds all rocks first
								probe[l] = '0';	//I turned the probe word char at position l to 0 to prevent the loop from checking that char again 
								secWordCpy[k] = '1';
						}
					}
				}
			
			    for (int k = 0; words[wordnum][k] != '\0'; k++)
				{
					for (int l = 0; probe[l] != '\0'; l++)
					{
						if (probe[l] == secWordCpy[k] && l != k)
						{
							pebbles++;     //finds all pebbles
							probe[l] = '2'; 
							break;
						}
					}
				}
				if (strcmp(shadowProbe, words[wordnum]) != 0)  //only outputs rocks and pebbles if not the correct word
					cout << "Rocks: " << rocks << ", Pebbles: " << pebbles << endl;
				roundScore++;
				break;
			}
			else if (j == nWords - 1 && probe != words[j])
				cout << "I don't know that word." << endl;
		}
	}
	return roundScore;
}
int main()
{
	int rounds;
	const int MAXWORDS = 9000;  
	char wordList[MAXWORDS][MAXWORDLEN + 1];
	int nWords = loadWords(wordList, MAXWORDS);

	if (nWords < 1)
	{
		cout << "No words were loaded, so I can't play the game." << endl;
		return 1;
	}
	cout << "How many rounds do you want to play? ";
	cin >> rounds;
	if (rounds <= 0)
	{
		cout << "The number of rounds must be positive." << endl;
		return 1;
	}
	cin.ignore(10000, '\n');
	int maxTries = 0;
	int minTries = 0;
	double totalTries = 0;
	
	cout.setf(ios::fixed);  //sets two decimal places after a double
	cout.precision(2);
	for (int m = 1; m <= rounds; m++)
	{
		cout << endl << "Round " << m << endl;
		int secWord = randInt(0, nWords - 1);
		cout << "The secret word is " << strlen(wordList[secWord]) << " letters long." << endl;
		int tries = manageOneRound(wordList, nWords, secWord);
		if (tries == 1)
			cout << "You got it in 1 try." << endl;
		else
			cout << "You got it in " << tries << " tries." << endl;
		totalTries += tries;
		double avg = totalTries / m;
		if (tries > maxTries)
			maxTries = tries;
		if (minTries == 0 || tries < minTries)
			minTries = tries;
		cout << "Average: " << avg << ", minimum: " << minTries << ", maximum: " << maxTries << endl;
	}
}