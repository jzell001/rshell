//     Copyright 2017 Duran Hughes and Jason Zellmer

//     This file is part of rshell.

//     rshell is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     (at your option) any later version.

//     rshell is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.

//     You should have received a copy of the GNU General Public License
//     along with rshell.  If not, see <http://www.gnu.org/licenses/>.


#ifndef BASE_H
#define BASE_H

#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include <stdio.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>

using namespace std;


class Base {
    
    public:

        Base() { };
        ~Base() { };
        void exitProgram();
        void execute();
        void setCheck(const bool& val);
        bool getCheck() const;
        
    private:
        static bool value;
        
};


class Parse : public Base {
    public:
  
        Parse();
        ~Parse();
        Parse( string input );
        void processText();
    
    protected:
        
        int foundSemiColon;
        int foundOr;
        int foundAnd;
        int firstConIndex;
        int userInputLength;
        int rightLength;
        string userInput;
        string firstConType;
        string leftText;
        string rightText;
       
};


class Cmd : public Base {
    
    public:
  
        Cmd();
        ~Cmd();
        Cmd( string processedInput );
        void tokenize();
        void execute();        // bool successCheck();
        //void setArgmSize();
    
    //protected:
    
        string command;
        char * argm[1024];
        bool successExecution;
       
};


class Both : public Base {
    
    public:
    
        Both();
        ~Both();
        Both(string left, string right);
        void execute();
        
    protected:
        
        string l;
        string r;
};


class Or : public Base {
    
    public:
    
        Or();
        ~Or();
        Or(string left, string right);
        void execute();
        
    protected:
        
        string l;
        string r;
};


class And : public Base {
    
    public:
    
        And();
        ~And();
        And(string left, string right);
        void execute();
        
    protected:
        
        string l;
        string r;
};


#endif