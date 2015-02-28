//
//  HW3Classes.cpp
//  HW3
//
//  Created by Joel Atyas on 2/22/15.
//  Copyright (c) 2015 Joel Atyas. All rights reserved.
//

#include "HW3Classes.h"

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

HandValue::HandValue(Hand* hnd) : HandValue()
{
    this->p_hand = hnd;
    //hnd->p_handValue = this;
}

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
    sort(this->cards.begin(), this->cards.end());
    
    this->p_handValue->HighCardVal1 = this->cards[this->cards.size() - 1].Value;
    this->p_handValue->HighCardVal2 = this->cards[this->cards.size() - 2].Value;
    this->p_handValue->HighCardVal3 = this->cards[this->cards.size() - 3].Value;
    
    // Check cards of equal value:
    CardValue pair1Val = CardValue::NAC;
    CardValue pair2Val = CardValue::NAC;
    CardValue threeOfKindVal = CardValue::NAC;
    CardValue fourOfKindVal = CardValue::NAC;
    
    int index = 0;
    int count = 0;
    
    do
    {
        if (checkForRepeatedVals(index, count))     // 2, 3, or 4 of a kind
        {
            if (count > 2)                          // 3 or 4 of a kind
            {
                if (count >3)                       // 4 of a kind
                {
                    fourOfKindVal = this->cards[index].Value;
                }
                else
                {
                    threeOfKindVal = this->cards[index].Value;
                }
            }
            else                                    // 2 of a kind
            {
                if (pair1Val != CardValue::NAC)     // is this a second pair?
                {
                    pair2Val = this->cards[index].Value;
                }
                else                                // this is the first pair
                {
                    pair1Val = this->cards[index].Value;
                }
            }
        }
        else
            index++;
        
    } while (count > 0 && index < (this->cards.size() - 2));
    
    if (fourOfKindVal != CardValue::NAC)
    {
        this->p_handValue->TypeOfHand = HandType::Four_of_Kind;
        this->p_handValue->HighCardVal1 = fourOfKindVal;
    }
    else
    {
        if (threeOfKindVal != CardValue::NAC)
        {
            this->p_handValue->HighCardVal1 = threeOfKindVal;
            if (pair1Val != CardValue::NAC)
            {
                this->p_handValue->HighCardVal2 = pair1Val;
                this->p_handValue->TypeOfHand = HandType::FullHouse;
            }
            else
                this->p_handValue->TypeOfHand = HandType::Three_of_Kind;
        }
        else
        {
            if (pair1Val != CardValue::NAC)
            {
                this->p_handValue->HighCardVal1 = pair1Val;
                if (pair2Val != CardValue::NAC)
                {
                    this->p_handValue->HighCardVal2 = pair2Val;
                    this->p_handValue->TypeOfHand = HandType::TwoPair;
                }
                else
                    this->p_handValue->TypeOfHand = HandType::OnePair;
            }
        }
    }
    
    // Check for straight and flush
    bool isStraight = true;
    bool isFlush = true;
    
    if (pair1Val == CardValue::NAC
        && threeOfKindVal == CardValue::NAC
        && fourOfKindVal == CardValue::NAC)
    {
        if (this->cards[0].Value > CardValue::Nine)         // Need to check this b/c of the way
            isStraight = false;                             // the ++ operator is implemented
        
        for (int i = 0; i < (this->cards.size() - 1); i++)
        {
            if (++this->cards[i].Value != this->cards[i + 1].Value)
            {
                isStraight = false;
            }
            
            if (this->cards[i].Suit != this->cards[i + 1].Suit)
            {
                isFlush = false;
            }
        }
        
        if (isStraight)
        {
            if (isFlush)
                this->p_handValue->TypeOfHand = HandType::StraightFlush;
            else
                this->p_handValue->TypeOfHand = HandType::Straight;
        }
        else if (isFlush)
        {
            this->p_handValue->TypeOfHand = HandType::Flush;
        }
    }
}

bool Hand::checkForRepeatedVals(int& index, int& count)
{
    if ((index + 1) < this->cards.size())
    {
        if (this->cards[index] == this->cards[index + 1])
        {
            count++;
            index++;
            checkForRepeatedVals(index, count);
        }
    }
    
    if (count > 0)
        return true;
    else
        return false;
}

bool Hand::operator==(const Hand& otherHand) const
{
    for (int i = 0; i < this->cards.size(); i++)
    {
        if (this->cards[i] != otherHand.cards[i])
        {
            return false;
        }
    }
    
    if ((this->p_handValue->TypeOfHand == HandType::Flush ||
         this->p_handValue->TypeOfHand == HandType::StraightFlush)
        &&
        (otherHand.p_handValue->TypeOfHand != HandType::Flush ||
         otherHand.p_handValue->TypeOfHand != HandType::StraightFlush))
    {
        return false;
    }
    else
        if (otherHand.p_handValue->TypeOfHand == HandType::Flush ||
            otherHand.p_handValue->TypeOfHand == HandType::StraightFlush)
    {
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
            long i = this->cards.size() -1;
            
            do
            {
                if (this->cards[i] < otherHand.cards[i])
                    return true;
                else if (this->cards[i] > otherHand.cards[i])
                    return false;
                --i;
                
            } while (i >= 0 && this->cards[i] == otherHand.cards[i]);
            
            return false;
        }
        else
        {
            return false;
        }
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

