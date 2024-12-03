#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
// #include <Windows.h>
#include <sstream>
// better version of the demo https://github.com/CSCIFORTWAYNE/CSCI101-0BC-SP24-Demos/blob/main/calculationDemo/main.cpp
using namespace std;

enum suitType
{
    HEART,
    SPADE,
    DIAMOND,
    CLUB,
    DEFAULTS
};
enum rankType
{
    A,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    J,
    Q,
    K,
    DEFAULTR
};
const rankType ranks[] = {A, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, J, Q, K, DEFAULTR};
const suitType suits[] = {HEART, SPADE, DIAMOND, CLUB, DEFAULTS};
const string rankStr[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", " "};
const string suitStr[] = {"♥", "♠", "♦", "♣", " "};

struct card
{
    suitType s = DEFAULTS;
    rankType r = DEFAULTR;
};

struct deck
{
    card d[52];
    bool used[52];
    int next = -1;
    int remain = 52;
};

struct pile
{
    card p[52];
    int topCard = -1;
};

void setUpDeck(deck &, pile[]);
void shuffleDeck(deck &);
void setUpFoundations(deck &, pile[]);
string printCard(card &);
int displayMenu(bool, bool, bool);
bool processChoice(bool, bool, bool, int, deck &, pile[], pile[]);
string printASCIICards(pile[]);
void displayOptions(bool &);
string printASCIICard(card &);

int main()
{
    int seed;
    cout << "Enter a seed: ";
    cin >> seed;
    cout << endl;
    while (!cin)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> seed;
    }
    srand(seed);
    // SetConsoleOutputCP(CP_UTF8);
    pile foundations[4];
    pile waste[4];
    deck d;
    // setUpDeck(d,foundations);
    // shuffleDeck(d);
    // setUpFoundations(d, foundations);
    bool drawnCard = false;
    bool finished = false;
    char play = 'N';
    int choice;
    bool print = false;
    // cout << printASCIICards(foundations);
    // return 0;
    do
    {
        cout << "Welcome to Calculation!" << endl;
        cout << "1. Start Game" << endl;
        cout << "2. Options" << endl;
        cout << "3. Quit" << endl;
        cin >> choice;
        while (!cin || choice < 1 || choice > 3)
        {
            if (!cin)
            {
                cin.clear();
                cin.ignore(1000, '\n');
            }
            cout << "That is not a valid choice." << endl;
            cout << "1. Start Game" << endl;
            cout << "2. Options" << endl;
            cout << "3. Quit" << endl;
            cin >> choice;
        }
        if (choice == 1)
        {
            cout << "Are you ready to play? ";
            cin >> play;
            play = toupper(play);
            while (play != 'Y' && play != 'N')
            {
                cout << "I don't understand.  I was expecting Y or N." << endl;
                cout << "Are you ready to play? ";
                cin >> play;
                play = toupper(play);
            }
            setUpDeck(d, foundations);
            shuffleDeck(d);
            setUpFoundations(d, foundations);
        }
        else if (choice == 2)
        {
            displayOptions(print);
        }
        while (play == 'Y')
        {
            while (!finished)
            {
                int choice;

                if (!print)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        cout << "F" << i + 1 << ":  " << printCard(foundations[i].p[foundations[i].topCard]) << "     ";
                    }
                    cout << endl;
                    for (int i = 0; i < 4; i++)
                    {
                        cout << "W" << i + 1 << ":  ";
                        if (waste[i].topCard > -1)
                            cout << printCard(waste[i].p[waste[i].topCard]) << "     ";
                        else
                            cout << "       ";
                    }
                    cout << endl;
                    if (drawnCard)
                    {
                        cout << "Drawn Card: " << printCard(d.d[d.next]) << endl;
                    }
                    else
                    {
                        cout << "Remaining Cards (" << d.remain << ")" << endl;
                    }
                }
                else
                {
                    cout << "Foundation Piles:" << endl;
                    cout << printASCIICards(foundations);
                    cout << endl;
                    cout << "Waste Piles:" << endl;
                    cout << printASCIICards(waste);
                    cout << endl;
                    if (drawnCard)
                    {
                        cout << "Drawn Card: " << endl;
                        cout << printASCIICard(d.d[d.next]) << endl;
                    }
                    else
                    {
                        card c;
                        cout << "Remaining Cards (" << d.remain << ")" << endl;
                        cout << printASCIICard(c);
                    }
                }
                bool isWaste, isFin;
                isWaste = waste[0].topCard > -1 || waste[1].topCard > -1 || waste[2].topCard > -1 || waste[3].topCard > -1;
                isFin = d.next == 51 && d.used[51];
                choice = displayMenu(drawnCard, isWaste, isFin);

                if (choice == 1)
                {
                    if (drawnCard)
                    {
                        char pileType;
                        cout << "Do you want to play on a: " << endl;
                        cout << "F. Foundation Pile" << endl;
                        cout << "W. Waste Pile" << endl;
                        cin >> pileType;
                        pileType = toupper(pileType);
                        while (pileType != 'F' && pileType != 'W')
                        {
                            cout << "I do not understand. I am expecting an F or W." << endl;
                            cout << "Do you want to play on a: " << endl;
                            cout << "F. Foundation Pile" << endl;
                            cout << "W. Waste Pile" << endl;
                            cin >> pileType;
                            pileType = toupper(pileType);
                        }
                        string pileOut = pileType == 'F' ? "foundation " : "waste ";
                        cout << "Which " << pileOut << "pile (1-4) do you want to play on? ";
                        cin >> choice;
                        while (!cin || choice < 1 || choice > 4)
                        {
                            if (!cin)
                            {
                                cin.clear();
                                cin.ignore(1000, '\n');
                            }
                            cout << "That is not a valid pile." << endl;
                            cout << "Which " << pileOut << "pile (1-4) do you want to play on? ";
                            cin >> choice;
                        }
                        if (pileType == 'F')
                        {
                            if (foundations[choice - 1].p[foundations[choice - 1].topCard + 1].r == d.d[d.next].r)
                            {
                                foundations[choice - 1].p[foundations[choice - 1].topCard + 1] = d.d[d.next];
                                foundations[choice - 1].topCard++;
                                d.used[d.next] = true;
                                drawnCard = false;
                            }
                            else
                            {
                                cout << "That is an invalid play. The next card for that pile is a " << rankStr[foundations[choice - 1].p[foundations[choice - 1].topCard + 1].r] << endl;
                            }
                        }
                        else
                        {
                            waste[choice - 1].p[++waste[choice - 1].topCard] = d.d[d.next];
                            d.used[d.next] = true;
                            drawnCard = false;
                        }
                    }
                    else if (d.next < 51)
                    {
                        while (d.used[++d.next])
                            ;
                        drawnCard = true;
                    }
                    else
                    {
                        finished = true;
                    }
                }
                else if (choice == 2)
                {
                    cout << "Which waste pile (1-4) do you want to play from? ";
                    cin >> choice;
                    while (!cin || choice < 1 || choice > 4)
                    {
                        if (!cin)
                        {
                            cin.clear();
                            cin.ignore(1000, '\n');
                        }
                        cout << "That is not a valid pile." << endl;
                        cout << "Which waste pile (1-4) do you want to play from? ";
                        cin >> choice;
                    }
                    int choice2;
                    cout << "Which foundation pile(1-4) do you want to play on? ";
                    cin >> choice2;
                    while (!cin || choice2 < 1 || choice2 > 4)
                    {
                        if (!cin)
                        {
                            cin.clear();
                            cin.ignore(1000, '\n');
                        }
                        cout << "That is not a valid pile." << endl;
                        cout << "Which foundation pile(1-4) do you want to play on? ";
                        cin >> choice2;
                    }
                    if (foundations[choice2 - 1].p[foundations[choice2 - 1].topCard + 1].r == waste[choice - 1].p[waste[choice - 1].topCard].r)
                    {
                        foundations[choice2 - 1].p[foundations[choice2 - 1].topCard + 1] = waste[choice - 1].p[waste[choice - 1].topCard];
                        foundations[choice2 - 1].topCard++;
                        waste[choice - 1].topCard--;
                    }
                    else
                    {
                        cout << "That is an invalid play. The next card for that pile is a " << rankStr[foundations[choice - 1].p[foundations[choice - 1].topCard + 1].r] << endl;
                    }
                }
                else if (choice == 3)
                {
                    cout << "Which waste pile (1-4) do you want to see? ";
                    cin >> choice;
                    while (!cin || choice < 1 || choice > 4)
                    {
                        if (!cin)
                        {
                            cin.clear();
                            cin.ignore(1000, '\n');
                        }
                        cout << "That is not a valid pile." << endl;
                        cout << "Which waste pile (1-4) do you want to see? ";
                        cin >> choice;
                    }
                    for (int i = waste[choice - 1].topCard; i >= 0; i--)
                    {
                        if (!print)
                            cout << printCard(waste[choice - 1].p[i]) << endl;
                        else
                            cout << printASCIICard(waste[choice - 1].p[i]);
                    }
                }
            }
            int score = 0;
            for (int i = 0; i < 4; i++)
            {
                score += waste[i].topCard + 1;
            }
            cout << "Game Over! You scored " << score << " points." << endl;
            cout << "Would you like to play again? ";
            cin >> play;
            play = toupper(play);
            while (play != 'Y' && play != 'N')
            {
                cout << "I don't understand.  I was expecting Y or N." << endl;
                cout << "Would you like to play again? ";
                cin >> play;
                play = toupper(play);
            }
        }
    } while (choice != 3);
    return 0;
}

void setUpDeck(deck &theDeck, pile found[])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            theDeck.d[i * 13 + j].s = suits[i];
            theDeck.d[i * 13 + j].r = ranks[j];
            theDeck.used[i * 13 + j] = false;
            found[i].p[j].r = ranks[((i + 1) * (j + 1) - 1) % 13];
        }
    }
}

void shuffleDeck(deck &theDeck)
{
    card temp[52];
    for (int i = 0; i < 52; i++)
    {
        int x = rand() % 52;
        while (theDeck.used[x])
        {
            x = rand() % 52;
        }
        temp[i] = theDeck.d[x];
        theDeck.used[x] = true;
    }
    for (int i = 0; i < 52; i++)
    {
        theDeck.d[i] = temp[i];
        theDeck.used[i] = false;
    }
}

void setUpFoundations(deck &theDeck, pile foundations[])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 52; j++)
        {
            if (theDeck.d[j].r == i)
            {
                foundations[i].p[++foundations[i].topCard] = theDeck.d[j];
                theDeck.used[j] = true;
                theDeck.remain--;
                break;
            }
        }
    }
}

string printCard(card &c)
{
    return rankStr[c.r] + suitStr[c.s];
}

int displayMenu(bool drawn, bool waste, bool finished)
{
    int choice;
    cout << "What would you like to do: " << endl;
    if (!drawn && !finished)
    {
        cout << "1. Draw Card" << endl;
    }
    else if (drawn)
    {
        cout << "1. Play Drawn Card" << endl;
    }
    else if (finished)
    {
        cout << "1. Finish Game and Calculate Score" << endl;
    }
    if (waste)
    {
        cout << "2. Play Card from Waste Pile" << endl;
        cout << "3. Display an entire waste pile" << endl;
    }

    cin >> choice;
    while (!cin || choice < 1 || (waste && choice > 3) || (choice > 1 && !waste))
    {
        if (!cin)
        {
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cout << "That is an invalid choice" << endl;
        cin >> choice;
    }
    return choice;
}

bool processChoice(bool drawnCard, bool isFinished, int choice, deck &d, pile f[], pile w[])
{
    return false;
}

string printASCIICards(pile p[])
{
    ostringstream out;
    // ┌─────────┐
    for (int i = 0; i < 4; i++)
    {
        out << "  ┌─────────┐ ";
    }
    out << endl
        << " ";
    for (int i = 0; i < 4; i++)
    {
        out << setfill(' ') << left;
        out << " │ " << setw(8);
        if (p[i].topCard > -1)
        {
            out << rankStr[p[i].p[p[i].topCard].r];
        }
        else
        {
            out << " ";
        }
        out << "│  ";
    }
    out << endl;
    for (int i = 0; i < 4; i++)
    {
        out << setfill(' ') << left;
        out << "  │" << setw(9) << " " << "│ ";
    }
    out << endl;

    for (int i = 0; i < 4; i++)
    {
        out << setfill(' ') << right;
        out << "  │";
        if (p[i].topCard > -1)
        {
            out << setw(7);
            out << suitStr[p[i].p[p[i].topCard].s];
        }
        else
        {
            out << setw(5);
            out << " ";
        }
        out << setw(4) << " " << "│ ";
    }
    out << endl;
    for (int i = 0; i < 4; i++)
    {
        out << setfill(' ') << left;
        out << "  │" << setw(9) << " " << "│ ";
    }
    out << endl;
    for (int i = 0; i < 4; i++)
    {
        out << setfill(' ') << right;
        out << "  │" << setw(8);
        if (p[i].topCard > -1)
        {
            out << rankStr[p[i].p[p[i].topCard].r];
        }
        else
        {
            out << " ";
        }
        out << " │ ";
    }
    out << endl;

    for (int i = 0; i < 4; i++)
    {
        out << i + 1 << " └─────────┘ ";
        // out << setw(6) << "'" << "'  ";
    }
    out << endl;

    return out.str();
}

void displayOptions(bool &print)
{
    int choice;
    cout << "Options Menu:" << endl;
    if (print)
        cout << "1. Disable ASCII Cards " << endl;
    else
        cout << "1. Enable ASCII Cards" << endl;
    cout << "2. Display Stats" << endl;
    cin >> choice;
    while (!cin || choice < 1 || choice > 2)
    {
        if (!cin)
        {
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cout << "That is not a valid choice." << endl;
        cin >> choice;
    }
    if (choice == 1)
    {
        print = !print;
    }
    else
    {
        cout << "This is extra credit and is not implemented in the solution." << endl;
    }
}

string printASCIICard(card &c)
{
    ostringstream out;
    if (c.r != DEFAULTR && c.s != DEFAULTS)
    {
        out << "┌─────────┐ " << endl;
        out << setfill(' ') << left;
        out << "│ " << setw(8);
        out << rankStr[c.r];
        out << "│  " << endl;
        out << setfill(' ') << left;
        out << "│" << setw(9) << " " << "│ " << endl;
        out << setfill(' ') << right;
        out << "│" << setw(7);
        out << suitStr[c.s];
        out << setw(4) << " " << "│ " << endl;
        out << setfill(' ') << left;
        out << "│" << setw(9) << " " << "│ " << endl;
        out << setfill(' ') << right;
        out << "│" << setw(8);
        out << rankStr[c.r];
        out << " │ " << endl;
        out << "└─────────┘ " << endl;
    }
    else
    {
        out << "┌─────────┐" << endl;
        out << "│░░░░░░░░░│" << endl;
        out << "│░░░░░░░░░│" << endl;
        out << "│░░░░░░░░░│" << endl;
        out << "│░░░░░░░░░│" << endl;
        out << "│░░░░░░░░░│" << endl;
        out << "└─────────┘" << endl;
    }
    return out.str();
}