#include "GamePlay.h"

int main()
{
    GamePlay game;

    int choice;
    do
    {
        system("cls");
        game.showTitle();

        cout<<endl;
        cout<<"\t1. Play\n";
        cout<<"\t2. View scores\n";
        cout<<"\t3. How to play?\n";
        cout<<"\t4. Exit\n";
        cout<<"Enter your choice (1/2/3/4): ";
        cin>>choice;

        if (choice == 1)
        {
            game.getPlayerName();
            char ch;
            do {
                game.startGame();
                cout<<"Want to play again? (y/n): ";
                cin>>ch;
            } while (ch == 'y');
        }
        else if (choice == 2)
        {
            game.showHighScores();
        }
        else if (choice == 3)
        {
            game.showRules();
        }
        else if (choice == 4)
        {
            cout<<"Goodbye"<<endl;
        }

    return 0;
}
