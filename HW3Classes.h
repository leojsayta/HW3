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
enum class CardValue {Two = 0, Three, Four, Five, Six, Seven, Eight, Nine, Jack, Queen, King, Ace};

class Card
{
    
private:
    
    
    
public:
    
    CardSuit Suit;
    CardValue Value;
    
    Card();
    
};

class Hand
{
    
private:
    
    vector<Card> cards;
    
public:
    
    Hand();
    
};

#endif /* defined(__HW3__HW3Classes__) */
