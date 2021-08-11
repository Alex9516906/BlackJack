
#include <iostream>
#include <vector>
#include <set>
#include <cassert>
#include <iterator>

using namespace std;

enum Mast
{
    Spades,
    Hearts,
    Clubs,
    Diamonds
};
enum Znach
{
    Two = 2,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack = 10,
    Queen = 10,
    King = 10,
    Ace = 1
};
class Card
{
    Mast m_mast;
    Znach m_znach;
    bool m_openCard;

public:

    Card(Mast mast, Znach znac, bool openCard)
        : m_mast(mast), m_znach(znac), m_openCard(openCard)
    {
        m_mast = mast;
        m_znach = znac;
        m_openCard = openCard;
    }
    void Flip()
    {
        if (m_openCard == true)
            m_openCard = false;
        else
            m_openCard = true;
    }
    int GetValue()
    {
        return m_znach;
    }
    friend ostream& operator<<(ostream& os, const Card& aCard);
};

class Hand
{
    vector<Card*> cardInHand;
public:

    void Add(Card* newCart)
    {
        cardInHand.push_back(newCart);
    }
    void Clear()
    {
        vector<Card*>::iterator it = cardInHand.begin();
        for (it = cardInHand.begin(); it != cardInHand.end(); it++)
        {
            delete* it;
            *it = 0;
        }
        cardInHand.clear();
    }
    int GetValue()const
    {
        int value = 0;
        for (int i = 0; i < cardInHand.size(); ++i)
        {
            value += cardInHand[i]->GetValue();

        }
        if (value <= 11)
        {
            for (int i = 0; i < cardInHand.size(); ++i)
            {
                if (cardInHand[i]->GetValue() == 1 && value <= 11)
                {
                    value += 10;
                }
            }
        }
        return value;
    }
    virtual ~Hand()
    {
        Clear();
    }
};

class GenericPlayer : public Hand
{
    string m_name;
public:
    GenericPlayer(const string& name=" ") :Hand(), m_name(name)
    {
    }
    string GetName() const
    {
        return m_name;
    }
    virtual ~GenericPlayer() {}
    virtual bool isHitting() const = 0
    {

    }
    bool isBoosted() 
    {
        return (GetValue() > 21);
    }
    void Bust()
    {
        cout << m_name << ": " << "Bust" << endl;
    }
};
class Player : public GenericPlayer
{
    Hand m_hand;
public:
    Player(const string& name = "Player") : GenericPlayer(name)
    {}
    virtual bool isHitting() const override
    {
        int i = 0;
        cout << "Do you need a card? 1-no\\2-yes" << endl;
        cin >> i;
        if(i!=1 & i != 2)
        {
            while (true)
            {
                cout << "Enter again !\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.sync();
                cout << "Do you need a card? y\\n" << endl;
                cin >> i;
                if (i==1 || i==2)
                {
                    break;
                }
            }
        }
        return i==1 ? false : true;
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
    House() :GenericPlayer("Diller")
    {
    }
    virtual bool IsHitting()
    {
        return (GetValue() <= 16);
    }
    void FlipFirstCard()
    {
        

    }
};
ostream& operator<<(ostream& os, const Card& aCard)
{
    const string RANKS[] = { "0", "A", "2", "3", "4", "5", "6", "7", "8", "9","10", "J", "Q", "K" };
    const string SUITS[] = { "c", "d", "h", "s" };

    if (aCard.m_openCard)
    {
        os << RANKS[aCard.m_znach] << SUITS[aCard.m_mast];
    }
    else
    {
        os << "XX";
    }

    return os;
}

int main()
{
    
}

