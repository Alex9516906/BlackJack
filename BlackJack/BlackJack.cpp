
#include <iostream>
#include <vector>
#include <set>
#include <cassert>
#include <iterator>

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
    Ace,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack = 10,
    Queen = 11,
    King = 12,

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
    int GetValue()
    {
        if (m_ranks > 10)
        {
            return 10;
        }
        else
            return m_ranks;
    }
    friend ostream& operator<<(ostream& os, const Card& aCard);
};

class Hand
{

public:
    vector<Card*> cardInHand;
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
    GenericPlayer(const string& name = " ") :Hand(), m_name(name)
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
        if ((i != 1) & (i != 2))
        {
            while (true)
            {
                cout << "Enter again !\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.sync();
                cout << "Do you need a card? y\\n" << endl;
                cin >> i;
                if (i == 1 || i == 2)
                {
                    break;
                }
            }
        }
        return i == 1 ? false : true;
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
        if (!cardInHand.empty())
        {
            cardInHand[0]->Flip();
        }
        else
        {
            cout << "No card to flip!" << endl;
        }
    }
};
ostream& operator<<(ostream& os, const Card& aCard)
{
    const string RANKS[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9","10", "J", "Q", "K" };
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

int main()
{


    return 0;
}

