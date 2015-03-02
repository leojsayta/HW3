//
//  HW3Classes.h
//  HW3
//
//  Created by Joel Atyas on 2/22/15.
//  Copyright (c) 2015 Joel Atyas. All rights reserved.
//

#ifndef __HW3__HW3Classes__
#define __HW3__HW3Classes__

#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include <string>
#include <exception>
#include <vector>

using namespace std;

enum class CardSuit {NAC = -1, Club = 0, Diamond, Heart, Spade};
constexpr CardSuit operator++(CardSuit& a, int);

enum class CardValue {NAC = -1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace};
constexpr CardValue operator++(CardValue& cv, int);
constexpr CardValue& operator++(CardValue& cv);

enum class HandType {
    NAH = -1,
    HighCard = 0,
    OnePair,
    TwoPair,
    Three_of_Kind,
    Straight,
    Flush,
    FullHouse,
    Four_of_Kind,
    StraightFlush
};

class Card
{
    
private:
    
    Card();
    
public:
    
    CardSuit Suit;
    CardValue Value;
    
    Card(CardSuit suit, CardValue val);
    
    Card(char suit, char val);
    
    bool operator==(const Card& otherCard) const;
    
    bool operator!=(const Card& otherCard) const;
    
    bool operator<(const Card& otherCard) const;
    
    bool operator>(const Card& otherCard) const;
    
    bool operator<=(const Card& otherCard) const;
    
    bool operator>=(const Card& otherCard) const;

};

class Hand;

class HandValue
{
private:
    
    //Hand* p_hand = nullptr;
    
public:
    
    HandType TypeOfHand;
    
    /*
     * HighCard1: For 1st pair or 3 of a kind or 4 of a kind or
     * straight or flush or straight flush.
     * HighCard2: For 2nd pair or lower pair of full house, etc.
     * HighCard3: like above
     */
    CardValue HighCardVal1;
    CardValue HighCardVal2;
    CardValue HighCardVal3;
    CardValue HighCardVal4;
    CardValue HighCardVal5;
    
    HandValue();
    
    //HandValue(Hand& hnd);
    
};

class Hand
{
    
private:
    
    vector<Card> cards;
    HandValue* p_handValue = nullptr;
    
    Hand();
    
    void determineValue();
    
    bool findRepeatedVals(int& index, CardValue& val, int& count);
    
public:
    
    Hand(vector<Card>& cards);
    
    Hand(Card& c1, Card& c2, Card& c3, Card& c4, Card& c5);
    
    static Hand* CreateHand(vector<string>& hndStrings);
    
    void SetCards(vector<Card>& cards)
    {
        this->cards = cards;
    }
    
    vector<Card> GetCards()
    {
        return cards;
    }
    
    bool operator==(const Hand& otherHand) const;
    
    bool operator!=(const Hand& otherHand) const;
    
    bool operator<(const Hand& otherHand) const;
    
    bool operator>(const Hand& otherHand) const;
    
    bool operator>=(const Hand& otherHand) const;
    
    bool operator<=(const Hand& otherHand) const;

    void setP_handValue(HandValue* p_handValue) 
    {
        this->p_handValue = p_handValue;
    }

    HandValue* getP_handValue() const 
    {
        return p_handValue;
    }
    
};

vector<string>* split(const string& s, char c);

#endif /* defined(__HW3__HW3Classes__) */
