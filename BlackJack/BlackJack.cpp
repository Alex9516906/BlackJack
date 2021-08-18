
#include <iostream>
#include <vector>
#include <set>
#include <cassert>
#include <iterator>
#include <algorithm>

using namespace std;

enum Suits
{
    Spades,
    Hearts,
    Clubs,
    Diamonds
};
enum Ranks
{
    Ace=1,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,

};
class Card
{
    Suits m_suits;
    Ranks m_ranks;
    bool m_openCard;
public:
    Card(Suits mast, Ranks znac, bool openCard)
        : m_suits(mast), m_ranks(znac), m_openCard(openCard) {}
    void Flip() { m_openCard = !m_openCard; }
    int GetValue() const
    {
        int value = 0;
        if(m_openCard)
        {
            value = m_ranks;
            if (value > 10)
            {
                value = 10;
            }
        }
        return value;
    }
    friend ostream& operator<<(ostream& os, const Card& aCard);
};

class Hand
{
protected:
    vector<Card*> m_Cards;
public:
    Hand()
    {
        m_Cards.reserve(7);
    }
    void Add(Card* newCart)
    {
        m_Cards.push_back(newCart);
    }
    void Clear()
    {
        vector<Card*>::iterator it = m_Cards.begin();
        for (it = m_Cards.begin(); it != m_Cards.end(); it++)
        {
            delete* it;
            *it = 0;
        }
        m_Cards.clear();
    }
    int GetValue()const
    {
        if (m_Cards.empty())
            return 0;
        if (m_Cards[0]->GetValue() == 0)
            return 0;
        
        int total = 0;
        
        for (int i =0; i<m_Cards.size(); i++)
        {
            total += m_Cards[i]->GetValue();
        }
        bool containsAce = false;
        for (int i = 0; i < m_Cards.size(); i++)
        {
            if(m_Cards[i]->GetValue()==Ace)
                containsAce = true;
        }
        if (containsAce && total <= 11)
        {
            total += 10;
        }
        return total;
    }
    virtual ~Hand()
    {
        Clear();
    }
};

class GenericPlayer : public Hand
{
    friend ostream& operator<<(ostream& os, const GenericPlayer& player);
protected:
    string m_name;
public:
    GenericPlayer(const string& name = " ") :Hand(), m_name(name)
    {
    }
    string GetName() const
    {
        return m_name;
    }
    virtual ~GenericPlayer() {}
    virtual bool isHitting() const = 0 {}
    bool isBoosted() const {return (GetValue() > 21);}
    void Bust() const
    {
        cout << m_name << ": " << "Bust" << endl;
    }
};



class Player : public GenericPlayer
{
public:
    Player(const string& name = "Player") : GenericPlayer(name)
    {}
    virtual ~Player(){}
    virtual bool isHitting() const 
    {
        cout << GetName() << " Do you want a hit? (1-y/0-n):";
        int response;
        cin >> response;
        return (response == 1);
        
    }
    void Win() const
    {

        cout << GetName() << ": You Win!" << endl;
    }
    void Lose() const
    {
        cout << GetName() << ": You Lose!" << endl;
    }
    void Push() const
    {
        cout << GetName() << ": draw!" << endl;
    }
};
class House : public GenericPlayer
{
public:
     
    House(const string& name = "Diller") :GenericPlayer("Diller")
    {
    }
    virtual bool isHitting() const
    {
        return (GetValue() <= 16);
    }
    void FlipFirstCard()
    {
        if (!(m_Cards.empty()))
        {
            m_Cards[0]->Flip();
        }
        else
        {
            cout << "No card to flip!" << endl;
        }
    }
};
ostream& operator<<(ostream& os, const Card& aCard)
{
    const string RANKS[] = {"0", "A", "2", "3", "4", "5", "6", "7", "8", "9","10", "J", "Q", "K" };
    const string SUITS[] = { "s","h", "c", "d" };

    if (aCard.m_openCard)
    {
        os << RANKS[aCard.m_ranks] << SUITS[aCard.m_suits];
    }
    else
    {
        os << "XX";
    }

    return os;
}
ostream& operator<<(ostream& os, const GenericPlayer& player) 
{
    os << player.GetName() << ": ";
    vector<Card*>::const_iterator pCard;
    if (!player.m_Cards.empty())
    {
        for (pCard = player.m_Cards.begin(); pCard   != player.m_Cards.end(); ++pCard)
        {
            os << *(*pCard) << "\t";

        }if (player.GetValue() != 0)
        {
            cout << "(" << player.GetValue() << ")";
        }
        else
        {
            os << "empty";
        }
        return os;
    }

}
class Deck : public Hand
{
public:
    Deck()
    {
        m_Cards.reserve(52);
        Populate();
    }
    ~Deck(){}
    void Populate()
    {
        Clear();
        for (int i = Spades; i <= Diamonds; i++)
        {
            for (int j = Ace; j < King; j++) 
            {
                Add(new Card(Suits(i), Ranks(j), true));
            }
            
        }
    }
    void Shuffle()
    {
        random_shuffle(m_Cards.begin(), m_Cards.end());
    }
    void Deal(Hand& aHand)
    {
        if (!m_Cards.empty())
        {
            aHand.Add(m_Cards.back());
            m_Cards.pop_back();
        }
        else
        {
            cout << "Out of card";
        }
    }
    void AddltionalCards(GenericPlayer& aGenerlcPlayer)
    {
        cout << endl;
        while (!(aGenerlcPlayer.isBoosted()) && aGenerlcPlayer.isHitting() )
        {
            Deal(aGenerlcPlayer);
            cout << aGenerlcPlayer << endl;
            if (aGenerlcPlayer.isBoosted())
            {
                aGenerlcPlayer.Bust();
            }
        }
    }
    
private:
    
};
class Game
{
private:
    Deck m_deck;
    House m_house;
    vector<Player> m_player;
    
public:
    Game(const vector<string>& names)
    {
        vector<string> ::const_iterator pNames;
        for (pNames=names.begin();pNames!=names.end();++pNames)
        {
            
            m_player.push_back(Player(*pNames));

        }
        m_deck.Populate();
        m_deck.Shuffle();

    }
    void Play()
    {
        vector<Player>::iterator pPlayer;
        for (int i = 0; i < 2; ++i)
        {
            for (pPlayer = m_player.begin(); pPlayer != m_player.end(); ++pPlayer)
            {
                m_deck.Deal(*pPlayer);
            }
            m_deck.Deal(m_house);
        }
        m_house.FlipFirstCard();
        for (pPlayer = m_player.begin(); pPlayer != m_player.end(); ++pPlayer) 
        {
                cout << *pPlayer << endl;
        }
        cout << m_house << endl;
        for (pPlayer = m_player.begin(); pPlayer != m_player.end(); ++pPlayer)
        {
            m_deck.AddltionalCards(*pPlayer);
        }
        m_house.FlipFirstCard();
        cout << endl << m_house;

        m_deck.AddltionalCards(m_house);
        if (m_house.isBoosted())
        {
            for (pPlayer = m_player.begin(); pPlayer != m_player.end(); ++pPlayer)
            {
                if (!(pPlayer->isBoosted()))
                    pPlayer->Win();
            }
        }
        else 
        {

      
            for (pPlayer = m_player.begin(); pPlayer != m_player.end(); ++pPlayer)
            {
                if (!(pPlayer->isBoosted()))
                {
                    if (pPlayer->GetValue() > m_house.GetValue()) 
                    {
                        
                            pPlayer->Win();
                    }
                    else if (pPlayer->GetValue() < m_house.GetValue())
                    {
                        pPlayer->Lose();
                    }
                    else
                    {
                        pPlayer->Push();
                    }
                }
            }
        }
        for (pPlayer = m_player.begin() ; pPlayer != m_player.end() ; ++pPlayer)
        {
            pPlayer->Clear();
        }
        m_house.Clear();

    }
    
};
int main()
{
    cout << "\t\tWelcome to Blackjack!\n\n";
    int numPlayers = 0;
    while (numPlayers < 1 || numPlayers > 7)
    {
        cout << "How many players? (1 - 7): ";
        cin >> numPlayers;
    }
    vector<string> names;
    string name;
    for (int i = 0; i < numPlayers; ++i)
    {
        cout << "Enter player name: ";
        cin >> name;
        names.push_back(name);
    }
    cout << endl;
    Game aGame(names);
    char again = 'у';
    while (again != 'n' && again != 'N') 
    {
        aGame.Play();
        cout << "\nDo you want to play again? (Y/N): ";
        cin >> again;
    }
    return 0;
   

    return 0;
}

