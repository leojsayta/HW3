//
//  HW3Classes.cpp
//  HW3
//
//  Created by Joel Atyas on 2/22/15.
//  Copyright (c) 2015 Joel Atyas. All rights reserved.
//

#include "HW3Classes.h"

#define HEART 'H'
#define CLUB 'C'
#define DIAMOND 'D'
#define SPADE 'S'

#define TWO '2'
#define THREE '3'
#define FOUR '4'
#define FIVE '5'
#define SIX '6'
#define SEVEN '7'
#define EIGHT '8'
#define NINE '9'
#define TEN 'T'
#define JACK 'J'
#define QUEEN 'Q'
#define KING 'K'
#define ACE 'A'


Card::Card()
{
    this->Suit = CardSuit::NAC;
    this->Value = CardValue::NAC;
}

Card::Card(CardSuit suit, CardValue val) : Card()
{
    this->Suit = suit;
    this->Value = val;
}

Card::Card(char suit, char val) : Card()
{
    switch (suit)
    {
        case HEART:
            this->Suit = CardSuit::Heart;
            break;
        case CLUB:
            this->Suit = CardSuit::Club;
            break;
        case DIAMOND:
            this->Suit = CardSuit::Diamond;
            break;
        case SPADE:
            this->Suit = CardSuit::Spade;
            break;
        default:
            throw string("\'%c\' is not a valid suit.", suit);
            break;
    }
    
    switch (val)
    {
        case TWO:
            this->Value = CardValue::Two;
            break;
        case THREE:
            this->Value = CardValue::Three;
            break;
        case FOUR:
            this->Value = CardValue::Four;
            break;
        case FIVE:
            this->Value = CardValue::Five;
            break;
        case SIX:
            this->Value = CardValue::Six;
            break;
        case SEVEN:
            this->Value = CardValue::Seven;
            break;
        case EIGHT:
            this->Value = CardValue::Eight;
            break;
        case NINE:
            this->Value = CardValue::Nine;
            break;
        case TEN:
            this->Value = CardValue::Ten;
            break;
        case JACK:
            this->Value = CardValue::Jack;
            break;
        case QUEEN:
            this->Value = CardValue::Queen;
            break;
        case KING:
            this->Value = CardValue::King;
            break;
        case ACE:
            this->Value = CardValue::Ace;
            break;
        default:
            throw string("\'%c\' is not a valid value.", val);
            break;
    }
}

bool Card::operator==(const Card& otherCard) const
{
    return this->Value == otherCard.Value;
}

bool Card::operator!=(const Card& otherCard) const
{
    return !(*this == otherCard);
}

bool Card::operator<(const Card& otherCard) const
{
    return this->Value < otherCard.Value;
}

bool Card::operator>(const Card& otherCard) const
{
    return this->Value > otherCard.Value;
}

bool Card::operator<=(const Card& otherCard) const
{
    return *this < otherCard || *this == otherCard;
}

bool Card::operator>=(const Card& otherCard) const
{
    return *this > otherCard || *this == otherCard;
}

HandValue::HandValue()
{
    this->TypeOfHand = HandType::HighCard;
    this->HighCardVal1 = CardValue::NAC;
    this->HighCardVal2 = CardValue::NAC;
    this->HighCardVal3 = CardValue::NAC;
}

//HandValue::HandValue(Hand& hnd) : HandValue()
//{
//    hnd.setP_handValue(this);
//}

Hand::Hand()
{
    this->cards = vector<Card>(5, {CardSuit::NAC,CardValue::NAC});
}

Hand::Hand(vector<Card>& cards) : Hand()
{
    this->SetCards(cards);
}

Hand::Hand(Card& c1, Card& c2, Card& c3, Card& c4, Card& c5) : Hand()
{
    vector<Card> crds = {c1,c2,c3,c4,c5};
    this->SetCards(crds);
}

void Hand::determineValue()
{
    if (this->p_handValue == nullptr)
    {
        this->p_handValue = new HandValue();
    }
    
    sort(this->cards.begin(), this->cards.end());
    
    this->p_handValue->TypeOfHand = HandType::NAH;
    this->p_handValue->HighCardVal1 = CardValue::NAC;
    this->p_handValue->HighCardVal2 = CardValue::NAC;
    this->p_handValue->HighCardVal3 = CardValue::NAC;
    this->p_handValue->HighCardVal4 = CardValue::NAC;
    this->p_handValue->HighCardVal5 = CardValue::NAC;
    
    // Check cards of equal value:
    CardValue pair1Val = CardValue::NAC;
    CardValue pair2Val = CardValue::NAC;
    CardValue threeOfKindVal = CardValue::NAC;
    CardValue fourOfKindVal = CardValue::NAC;
    
    int index = 0;
    int count = 0;
    CardValue cv = CardValue::NAC;
    
    do
    {
        count = 0;
        cv = CardValue::NAC;
        if (findRepeatedVals(index, cv, count))     // 2, 3, or 4 of a kind
        {
            if (count >= 2)                          // 3 or 4 of a kind
            {
                if (count == 3)                       // 4 of a kind
                {
                    fourOfKindVal = cv;
                }
                else
                {
                    threeOfKindVal = cv;
                }
            }
            else                                    // 2 of a kind
            {
                if (pair1Val != CardValue::NAC)     // is this a second pair?
                {
                    pair2Val = cv;
                }
                else                                // this is the first pair
                {
                    pair1Val = cv;
                }
            }
        }
//        else
//            index++;
        
    } while (index < (this->cards.size() - 1));
    
	if (fourOfKindVal != CardValue::NAC)
    {
		this->p_handValue->TypeOfHand = HandType::Four_of_Kind;
		this->p_handValue->HighCardVal1 = fourOfKindVal;

		for (Card crd : this->cards)
        {
			if (crd.Value != fourOfKindVal)
            {
				this->p_handValue->HighCardVal2 = crd.Value;
				break;
			}
		}
	}
	else if (threeOfKindVal != CardValue::NAC)
    {
		this->p_handValue->HighCardVal1 = threeOfKindVal;

		if (pair1Val != CardValue::NAC)
        {
			this->p_handValue->HighCardVal2 = pair1Val;
			this->p_handValue->TypeOfHand = HandType::FullHouse;
		}
		else
        {
			this->p_handValue->TypeOfHand = HandType::Three_of_Kind;

			for (long crdIndex = (this->cards.size() - 1); crdIndex >= 0; --crdIndex)
            {
				if (this->cards[crdIndex].Value != threeOfKindVal)
                {
					if (this->p_handValue->HighCardVal2 != CardValue::NAC)
						this->p_handValue->HighCardVal3 = this->cards[crdIndex].Value;
					else
						this->p_handValue->HighCardVal2 = this->cards[crdIndex].Value;
				}
			}
		}
	}
	else if (pair2Val != CardValue::NAC)
    {
		this->p_handValue->TypeOfHand = HandType::TwoPair;

		if (pair1Val > pair2Val)
        {
			this->p_handValue->HighCardVal1 = pair1Val;
			this->p_handValue->HighCardVal2 = pair2Val;
		}
		else
        {
			this->p_handValue->HighCardVal1 = pair2Val;
			this->p_handValue->HighCardVal2 = pair1Val;
		}

		for (Card crd : this->cards)
        {
			if (crd.Value != pair1Val && crd.Value != pair2Val)
            {
				this->p_handValue->HighCardVal3 = crd.Value;
				break;
			}
		}
	}
	else if (pair1Val != CardValue::NAC)
    {
		this->p_handValue->TypeOfHand = HandType::OnePair;
		this->p_handValue->HighCardVal1 = pair1Val;

		for (long crdIndex = (this->cards.size() - 1); crdIndex >= 0; --crdIndex)
        {
			if (this->cards[crdIndex].Value != pair1Val)
            {
				if (this->p_handValue->HighCardVal2 != CardValue::NAC)
                {
                    if (this->p_handValue->HighCardVal3 != CardValue::NAC)
                    {
                        if (this->p_handValue->HighCardVal4 != CardValue::NAC)
                            this->p_handValue->HighCardVal5 = this->cards[crdIndex].Value;
                        else
                            this->p_handValue->HighCardVal4 = this->cards[crdIndex].Value;
                    }
                    else
                        this->p_handValue->HighCardVal3 = this->cards[crdIndex].Value;
                }
                else
                    this->p_handValue->HighCardVal2 = this->cards[crdIndex].Value;
			}
		}
	}
	else
    {
        this->p_handValue->TypeOfHand = HandType::HighCard;
        this->p_handValue->HighCardVal1 = this->cards[this->cards.size() - 1].Value;
        this->p_handValue->HighCardVal2 = this->cards[this->cards.size() - 2].Value;
        this->p_handValue->HighCardVal3 = this->cards[this->cards.size() - 3].Value;
        this->p_handValue->HighCardVal4 = this->cards[this->cards.size() - 4].Value;
        this->p_handValue->HighCardVal5 = this->cards[this->cards.size() - 5].Value;
	}
    
    // Check for straight and flush
    bool isPossibleStraight = true;
    bool isPossibleFlush = true;
    
    if (this->p_handValue->TypeOfHand == HandType::HighCard)
    {
        if (this->cards[0].Value > CardValue::Ten)
            isPossibleStraight = false;
        
        CardValue nextCardVal = CardValue::NAC;
        for (int i = 0; i < (this->cards.size() - 1); i++)
        {
            if (isPossibleStraight)
            {
                nextCardVal = static_cast<CardValue>(static_cast<int>(this->cards[i].Value) + 1);
                if (this->cards[i + 1].Value != nextCardVal)
                {
                    isPossibleStraight = false;
                }
            }
            
            if (this->cards[i].Suit != this->cards[i + 1].Suit)
            {
                isPossibleFlush = false;
            }
        }
        
        if (isPossibleStraight)
        {
            if (isPossibleFlush)
                this->p_handValue->TypeOfHand = HandType::StraightFlush;
            else
                this->p_handValue->TypeOfHand = HandType::Straight;
        }
        else if (isPossibleFlush)
            this->p_handValue->TypeOfHand = HandType::Flush;
    }
}

bool Hand::findRepeatedVals(int& index, CardValue& val, int& count)
{
    if ((index + 1) < this->cards.size())
    {
        if (this->cards[index] == this->cards[index + 1])
        {
            val = this->cards[index].Value;
            findRepeatedVals(++index, val, ++count);
        }
        else
            index++;
    }
    
    if (count > 0)
        return true;
    else
        return false;
}

Hand Hand::CreateHand(vector<string>& hndStrings)
{
    vector<Card> cards;
    
    for(string crdStr : hndStrings)
    {
        cards.push_back({crdStr[1], crdStr[0]});
    }
 
    Hand tmp = Hand(cards);
    tmp.determineValue();
    
    return tmp;
}

bool Hand::operator==(const Hand& otherHand) const
{
    if (this->p_handValue->TypeOfHand != otherHand.p_handValue->TypeOfHand)
        return false;
    
    for (int i = 0; i < this->cards.size(); i++)
    {
        if (this->cards[i] != otherHand.cards[i])
            return false;
    }
    
    return true;
}

bool Hand::operator!=(const Hand& otherHand) const
{
    return !(*this == otherHand);
}

bool Hand::operator<(const Hand& otherHand) const
{
    if (this->p_handValue->TypeOfHand < otherHand.p_handValue->TypeOfHand)
    {
        return true;
    }
    else
        if (this->p_handValue->TypeOfHand == otherHand.p_handValue->TypeOfHand)
        {
            vector<CardValue> lh = this->getP_handValue()->GetOrderedCardVals();
            vector<CardValue> rh = otherHand.getP_handValue()->GetOrderedCardVals();
            
            for (long i = 0; i < lh.size(); i++)
            {
                if (lh[i] > rh[i])
                    return false;
                else if (lh[i] < rh[i])
                    return true;
                else
                    continue;
            }
        }
        else
        {
            return false;
        }
    return true;
}

bool Hand::operator>(const Hand& otherHand) const
{
    return !(*this < otherHand || *this == otherHand);
}

bool Hand::operator<=(const Hand& otherHand) const
{
    return *this < otherHand || *this == otherHand;
}

bool Hand::operator>=(const Hand& otherHand) const
{
    return *this > otherHand || *this == otherHand;
}

// post-increment
constexpr CardSuit operator++(CardSuit& cs, int)
{
    return cs = (cs == CardSuit::Spade) ? CardSuit::Club : static_cast<CardSuit>(static_cast<int>(cs) + 1);
}

// post-increment
constexpr CardValue operator++(CardValue& cv, int)
{
    return cv = (cv == CardValue::Ace) ? CardValue::Two : static_cast<CardValue>(static_cast<int>(cv) + 1);
}
// pre-increment
constexpr CardValue& operator++(CardValue& cv)
{
    return cv = (cv == CardValue::Ace) ? CardValue::Two : static_cast<CardValue>(static_cast<int>(cv) + 1);
}

// based on: https://www.safaribooksonline.com/library/view/C+++Cookbook/0596007612/ch04s07.html
vector<string>* split(const string& s, char c) 
{
    vector<string>* v = new vector<string>();
    string::size_type i = 0;
    string::size_type j = s.find(c);

    while (j != string::npos) 
    {
        v->push_back(s.substr(i, j - i));
        do
        {
            i = ++j;
            j = s.find(c, j);
        }
        while (j == i);      // bypass duplicate delimiters
        
        if (j == string::npos)
            v->push_back( s.substr(i, s.length()));
    }
    
    return v;
}