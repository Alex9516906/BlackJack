
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
    int GetValue()
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
    virtual ~GenericPlayer() {}
    virtual bool isHitting() = 0
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


int main()
{
   
}

