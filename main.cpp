//
//  main.cpp
//  HW3
//
//  Created by Joel Atyas on 2/22/15.
//  Copyright (c) 2015 Joel Atyas. All rights reserved.
//

#include <iostream>
#include <string.h>
#include <exception>
#include <vector>
#include "HW3Classes.h"

using namespace std;

int main(int argc, const char *argv[])
{
    try
    {
        CardValue c1 = CardValue::Ace;
        CardValue c2 = CardValue::Five;
        CardValue c3 = CardValue::Jack;
        CardValue c4 = CardValue::Three;
        CardValue c5 = CardValue::Six;
        CardValue c6 = CardValue::Nine;
        
        
        vector<CardValue> cards{c1,c2,c3,c4,c5,c6};
        
        sort(cards.begin(), cards.end());
        
        printf("\nSomething went wrong!  Please start over.");
        
        
    }
    catch (exception &)
    {
        printf("\nSomething went wrong!  Please start over.");
        return -1;
    }
    
    return 0;
}

