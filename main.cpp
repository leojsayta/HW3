//
//  main.cpp
//  HW3
//
//  Created by Joel Atyas on 2/22/15.
//  Copyright (c) 2015 Joel Atyas. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <exception>
#include <vector>
#include "HW3Classes.h"

using namespace std;

#define SIZE_Of_HAND 5

void loadCSV(istream& in, vector<vector<string>*>& data);

int main(int argc, const char *argv[])
{
    try
    {
        printf("Starting...\n");

//        if (argc < 2)
//            return (EXIT_FAILURE);

        //ifstream in(argv[1]);
        ifstream in("p054_poker.txt");

        if (!in)
            return (EXIT_FAILURE);

        //vector<string>* data;

        vector<string>* pAllCardTxt = NULL;
        vector<string>* pLeftHandCardTxt = NULL;
        vector<string>* pRightHandCardTxt = NULL;
        string strInput;
        string strOutput;
        
        //Hand lh;
        //Hand rh;
        
        int lHandWon = 0;
        int rHandWon = 0;
        int draw = 0;

        while (!in.eof()) 
        {
            getline(in, strInput, '\n'); // Grab the next line
            //cout << strInput << '\n';
            
            if (strInput.empty())
                continue;
            
            pAllCardTxt = split(strInput, ' ');
            pLeftHandCardTxt = new vector<string>(pAllCardTxt->begin(), pAllCardTxt->begin() + SIZE_Of_HAND);            
            pRightHandCardTxt = new vector<string>(pAllCardTxt->begin() + SIZE_Of_HAND, pAllCardTxt->end());            
            
            Hand lh = Hand::CreateHand(*pLeftHandCardTxt);
            Hand rh = Hand::CreateHand(*pRightHandCardTxt);
            
            //vector<string> vstr{"QH", "9D", "9H", "TS", "TC"};
            //rh = Hand::CreateHand(vstr);
            
            if (lh == rh)
            {
                //strOutput = "Its a draw.";
                draw++;
            }
            else if (lh > rh)
            {
                //strOutput = "Lefthand won.";
                lHandWon++;
            }
            else
            {
                //strOutput = "Righhand won.";
                rHandWon++;
            }
                
            //data->push_back(strOutput);
            //cout << tmp << '\n';
            //cout << tmp << '\n';
            
            
        }
        
        cout << "Left Hand won " << lHandWon << '\n';
        cout << "Righ Hand won " << rHandWon << '\n';

        
//        for (vector<string>::iterator p = data.begin(); p != data.end(); ++p) 
//        {
//            delete *p; // Be sure to de-reference p!
//        }
        
    }
    catch (exception& ex)
    {
        printf("\nSomething went wrong:\n");
        //printf(ex.what());
        printf("\nPlease start over.");
        return 1;
    }
    
    return 0;
}



void loadCSV(istream& in, vector<vector<string>*>& data) 
{

   vector<string>* p = NULL;
   string tmp;

   while (!in.eof()) 
   {
      getline(in, tmp, '\n');                     // Grab the next line

      p = split(tmp, ' ');                        // Use split from
                                                  // Recipe 4.7
      data.push_back(p);

      cout << tmp << '\n';
      tmp.clear();
   }
}