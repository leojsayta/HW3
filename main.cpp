//
//  main.cpp
//  HW3
//
//  Created by Joel Atyas on 2/22/15.
//  Copyright (c) 2015 Joel Atyas. All rights reserved.
//

#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include "HW3Classes.h"

using namespace std;

int main(int argc, const char *argv[])
{
    try
    {
        CardValue ca1 = CardValue::Ace;
        CardValue ca2 = CardValue::Five;
        CardValue ca3 = CardValue::Five;
        CardValue ca4 = CardValue::Three;
        CardValue ca5 = CardValue::Five;
        CardValue ca6 = CardValue::Nine;
        
        CardValue cb1 = CardValue::Ace;
        CardValue cb2 = CardValue::Five;
        CardValue cb3 = CardValue::Four;
        CardValue cb4 = CardValue::Three;
        CardValue cb5 = CardValue::Four;
        CardValue cb6 = CardValue::Five;
        CardValue cb7 = CardValue::NAC;
        
        
        vector<CardValue> cardas = {ca1,ca2,ca3,ca4,ca5,ca6};
        vector<CardValue> cardbs = {cb1,cb2,cb3,cb4,cb5,cb6,cb7};
        
        sort(cardas.begin(), cardas.end());
        sort(cardbs.begin(), cardbs.end());
        
        printf("\nSomething went wrong!  Please start over.");
        
        
    }
    catch (exception &)
    {
        printf("\nSomething went wrong!  Please start over.");
        return -1;
    }
    
    return 0;
}

