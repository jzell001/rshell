    // Copyright 2017 Duran Hughes and Jason Zellmer

    // This file is part of rshell.

    // rshell is free software: you can redistribute it and/or modify
    // it under the terms of the GNU General Public License as published by
    // the Free Software Foundation, either version 3 of the License, or
    // (at your option) any later version.

    // rshell is distributed in the hope that it will be useful,
    // but WITHOUT ANY WARRANTY; without even the implied warranty of
    // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    // GNU General Public License for more details.

    // You should have received a copy of the GNU General Public License
    // along with rshell.  If not, see <http://www.gnu.org/licenses/>.


#include "Base.h"

#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <stdio.h>
using namespace std;

int main() {
    
    //variables
    string input = "";
    int poundSignIndex = -1;
    
    cout << "$ ";
    
    while(getline(cin,input)) {
        
        // //print prompt
        // cout << "$ ";
        // getline(cin,input);
        
        if(input == "exit") {
            return 0;
        }
        // if(input == "") {
        //     //jump to top of loop
        //     cout << "empty input" << endl;
        // }
        
        //look for '#'
        poundSignIndex = input.find("#");
        
        //if "#" is found, removed it and everything that follows
        if(poundSignIndex != -1) {
            //cout << "pound sign found at index: " << poundSignIndex << endl;
            input.erase(input.begin() + poundSignIndex, input.end()); 
            //cout << "reformatted input: " << input << endl;
        }
        
        //parse(input);
        if(input != "") {
            Parse* p = new Parse(input);
            p->processText();
            delete p;
        }
        
        // test code
        //Cmd* c = new Cmd(p->getLeftText());
        //c->tokenize();
        //c->execute();
        //cout << c->successCheck() << endl;
        

        //print prompt
        cout << "$ ";
        
    }
    
    return 0;
    
}