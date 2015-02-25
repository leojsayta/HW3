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
    this->Suit = CardSuit::Club;
    this->Value = CardValue::Ace;   
}

Card::Card(CardSuit suit, CardValue val) : Card()
{
    this->Suit = suit;
    this->Value = val;
}

HandValue::HandValue()
{
    this->TypeOfHand = HandType::HighCard;
    this->HighCard1 = Card();
    this->HighCard2 = Card();
}

HandValue::HandValue(const Hand* hnd) : HandValue()
{
    this->p_hand = hnd;
}

Hand::Hand()
{
    this->cards = vector<Card>(5);
    
    for(Card& cd : cards)
    {
        cd.Suit++;
        cd.Value++;
    }
}

Hand::Hand(vector<Card>& cards) : Hand()
{
    this->SetCards(cards);
}

constexpr CardSuit operator++(CardSuit& cs, int)
{   
    return cs = (cs == CardSuit::Spade) ? CardSuit::Club : static_cast<CardSuit>(static_cast<int>(cs) + 1);
}

constexpr CardValue operator++(CardValue& cv, int)
{
   return cv = (cv == CardValue::Ace) ? CardValue::Two : static_cast<CardValue>(static_cast<int>(cv) + 1);
}