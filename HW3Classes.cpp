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

Hand::Hand()
{
    this->cards = vector<Card>(5);
    
}
