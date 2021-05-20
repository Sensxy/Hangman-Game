#include "GamePlay.h"
#include "Death.png"

GamePlay::GamePlay(): MAX_TRIES(5)
{
    words[0] = "pizza";
	words[1] = "sushi";
	words[2] = "salad";
	words[3] = "chicken";
	words[4] = "streak";
	words[5] = "fries";
	words[6] = "hamburger";
	words[7] = "potatochips";
	words[8] = "cereal";
	words[9] = "fish";
    player_name = "default";

   
    ifstream fin("./data/scores.txt");
    if (!fin)
    {

        system("mkdir data");
        ofstream fout("./data/scores.txt");
        fout.close();
    }
    fin.close();
}

void GamePlay::showTitle()
{
    cout<<"\t *    *     **     **    *  *****   **   **     **     **    *"<<endl;
    cout<<"\t *    *    *  *    * *   * *        * * * *    *  *    * *   *"<<endl;
    cout<<"\t ******   ******   *  *  * *  ***** *  *  *   ******   *  *  *"<<endl;
    cout<<"\t *    *  *      *  *   * * *      * *     *  *      *  *   * *"<<endl;
    cout<<"\t *    * *        * *    **  ******  *     * *        * *    **"<<endl;
}

void GamePlay::showRules()
{
   
    cout<<endl;
    cout<<"\t\t\t HOW TO PLAY"<<endl;
    cout<<"\t\t\t-------------"<<endl;
	cout<<"Welcome to hangman."<<endl;
    cout<<"You have to guess a food name."<<endl;
	cout<< "You have "<<MAX_TRIES<<" tries to try and guess the word."<<endl;
	cout<<"-------------------------------------------------------------"<<endl;
    cout<<endl;
    cout<<"Press any key to continue."<<endl;
    cin.ignore();
    cin.get();
}

void GamePlay::startGame()
{
    int num_of_wrong_guesses = 0, cur_score = 100;  
	srand(time(NULL));
	int n = rand() % 10;
	word = words[n];

    string unknown = string(word.length(), '*');

   
    system("cls");
	while (num_of_wrong_guesses < MAX_TRIES)
	{
        cout<<endl;
		cout<<unknown<<endl;
		cout<<"Guess a letter: ";
        char letter;
		cin>>letter;
	
        cout<<endl;
		if (letterFill(letter, unknown) == 0)
		{
			cout<<"Sorry, wrong letter"<<endl;
			num_of_wrong_guesses++;
            cur_score -= 10;    
		}
		else
		{
			cout<<"You found a letter!"<<endl;
		}
	
		cout<<"You have "<<MAX_TRIES - num_of_wrong_guesses;
		cout<<" guesses left."<<endl;
	
		if (word == unknown)
		{
			cout<<word<<endl;
			cout<<"You guessed it!"<<endl;
			break;
		}
	}
	if(num_of_wrong_guesses == MAX_TRIES)
	{
		cout<<"Sorry, you lose"<<endl;
		cout<<"The word was : "<<word<<endl;
        cur_score -= 20;    

	}
    if (cur_score < 0)
        cur_score = 0;

    cout<<"Your score: "<<cur_score<<endl;
    cout<<endl;
    updateHighScores(cur_score);   
}

int GamePlay::letterFill(char guess, string &guessword)
{
	int i;
	int matches = 0;
	int len = word.length();
	for (i = 0; i < len; i++)
	{
	
		if (guess == guessword[i])
			return 0;
	
		if (guess == word[i])
		{
			guessword[i] = guess;
			matches++;
		}
	}
	return matches;
}

void GamePlay::getPlayerName()
{
    cout<<"Please enter your name: ";
    cin>>player_name;
}

void GamePlay::updateHighScores(int current_score)
{
  
    ifstream fin("./data/scores.txt");

    priority_queue<pair<int, string>> pq;
    string name;
    int score;
    fin>>name;
    while (!fin.eof())
    {
        fin>>score;
        pq.push({ score, name});
        fin>>name;
    }
    pq.push({ current_score, player_name });
    fin.close();

    ofstream fout("./data/scores.txt");
    for (int i = 0; !pq.empty() && i < 5; i++)
    {
        fout<<pq.top().second<<" "<<pq.top().first<<endl;
        pq.pop();
    }
    fout.close();
}

void GamePlay::showHighScores()
{
    ifstream fin("data/scores.txt");
    system("cls");
    cout<<"\tTOP SCORERS"<<endl;

    string n;
    int score;
    fin>>n;
    int i = 1;
    while (!fin.eof())
    {
        fin>>score;
        cout<<i<<". "<<n<<"   "<<score<<endl;
        fin>>n;
        i++;
    }
    if (i == 1)
    {
        cout<<"No entries yet."<<endl;
       
    }

    cout<<"---------------------------------------------"<<endl;
    cout<<endl;
    cout<<"Press any key to continue."<<endl;
    cin.ignore();
    cin.get();
}
