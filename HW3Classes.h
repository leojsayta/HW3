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
#include <string.h>
#include <vector>

using namespace std;

enum class CardSuit {Club = 0, Diamond, Heart, Spade};
constexpr CardSuit operator++(CardSuit& a, int);

enum class CardValue {Two = 0, Three, Four, Five, Six, Seven, Eight, Nine, Jack, Queen, King, Ace};
constexpr CardValue operator++(CardValue& cv, int);

enum class HandType {
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
    
    
    
public:
    
    CardSuit Suit;
    CardValue Value;
    
    Card();
    
    Card(CardSuit suit, CardValue val);
};

class Hand;

class HandValue
{
private:

    const Hand* p_hand = nullptr;
    
    HandValue();

public:

    HandType TypeOfHand;

    /*
     * highCard1: For 1st pair or 3 of a kind or 4 of a kind or
     * straight or flush or straight flush.
     * highCard2: For 2nd pair or lower pair of full house, etc.
    */
    Card HighCard1; 
    Card HighCard2;

    HandValue(const Hand* hnd);

};

class Hand
{   
    
private:
    
    vector<Card> cards;
    HandValue* p_handValue = nullptr;
    
public:
    
    Hand();
    
    Hand(vector<Card>& cards);

    void SetCards(vector<Card>& cards) {
        this->cards = cards;
    }

    vector<Card> GetCards() const {
        return cards;
    }
    
    void SortByValue();
    
    void SortBySuit();
    
    bool IsFlush();
    
    bool operator==(const Hand& otherHand); 
    
    bool operator!=(const Hand& otherHand); 
    
    bool operator<(const Hand& otherHand); 
    
    bool operator>(const Hand& otherHand);
    
};


constexpr CardSuit operator++(CardSuit a); 


#endif /* defined(__HW3__HW3Classes__) */
