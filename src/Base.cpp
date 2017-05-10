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


#include "Base.h"

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


// set the success flag of left collection
void Base::setCheck(const bool& val) {
    value = val;
}
        
// check the success flag of left collection
bool Base::getCheck() const {
    return value;
}

// static variable accessable to all classes
bool Base::value = true;


// default contructer
Parse::Parse():Base(){}

// deconstructer
Parse::~Parse() {}

// constructer
Parse::Parse( string input ) {
    userInput = input;
}

// process text function
void Parse::processText() {
    
    // variables
    foundSemiColon = -1;
    foundOr = -1;
    foundAnd = -1;
    firstConIndex = -1;
    userInputLength = userInput.length();
    rightLength = 0;
    int firstSemiColon = userInput.rfind(";");
    
    // get rid of any ';'s at the end of the command
    if( (userInputLength - 1) == firstSemiColon) {
        userInput = userInput.substr(0 , userInput.rfind(";"));
    }
    
    // look for instances of ";", "||", "&&"
    foundSemiColon = userInput.rfind(";");
    foundOr = userInput.rfind("||");
    foundAnd = userInput.rfind("&&");
    
    //if connector isn't found run CMD
    if(foundSemiColon == -1 && foundAnd == -1 && foundOr == -1) {
        Cmd* c = new Cmd(userInput);
        c->tokenize();
        c->execute();
    }
   
    else {
        
        // find index and type of first connector
        if(foundSemiColon != -1) {
            firstConIndex = foundSemiColon;
            firstConType = ";";
        }
        if(foundOr != -1 && firstConIndex < foundOr) {
            firstConIndex = foundOr;
            firstConType = "||";
        }
        if(foundAnd != -1 && firstConIndex < foundAnd) {
            firstConIndex = foundAnd;
            firstConType = "&&";
        }
        
        // create left and right substrings
        leftText = userInput.substr(0, firstConIndex);
        rightLength = userInputLength - (firstConIndex + 2); 
        
        
        // if firstConType is ";" set normally
        if(firstConType == ";") {
            
            // command is alone
            if(rightLength == -1) {
                rightText = leftText;
            }
            // set rightText normally
            else {
                rightText = userInput.substr(firstConIndex + 2, rightLength);
            }
        }
        // if firstConType is "||" or "&&" then set rightText with extra space
        else {
            rightText = userInput.substr(firstConIndex + 3, rightLength + 1);
        }
        
        // decide which connector to call (AND, OR, BOTH) using if statements
        if(firstConType == ";") {
            Both* b = new Both(leftText,rightText);
            b->execute();
        }
        else if(firstConType == "||") {
            Or* o = new Or(leftText,rightText);
            o->execute();
        }
        else {
            And* a = new And(leftText,rightText);
            a->execute();
        }
        
    }
    
}


// default contructer
Cmd::Cmd():Base(){}

// deconstructer
Cmd::~Cmd() {}

// constructer
Cmd::Cmd( string processedInput ) {
    command = processedInput;
    successExecution = false;
}

// tokenize text function
void Cmd::tokenize() {

	// varibles 
    char str[1024];
    int i = 0;
    char *p;
    
    // convert string command into a char array
    strcpy(str, command.c_str());

    // tokenize our char array
    p = strtok (str, " ");
    while (p != NULL) {
        argm[i] = p;
        p = strtok (NULL, " ");
        i++;
    }
    // capp end with a NULL
    argm[i++] = '\0';
    
    // delete pointer p
    delete p;
}

// execute function
void Cmd::execute() {
    
    // Execute Command
    int pid = -1;
    int returnStatus; 
  
    // fork
    pid = fork(); 
    
    // child process.
    if(pid == 0) { 
        
        string commandName = argm[0];
        execvp(argm[0], argm);
        // int errCode = errno;
        
        cout << "bash: " << commandName << ": command not found" << endl;
        
        // exit(errCode);
        exit(EXIT_SUCCESS);
    } 
    // parent process.
    else if(pid > 0) { 
        
        // Wait for the child process to exit
        // below is same as waitpid(-1, &status, 0);
        // wait(&returnStatus);
        
        if ((pid = wait(&returnStatus)) == -1) {
           perror("wait error");
        }
        else {
            
            // Program succeeded
            if ((WIFEXITED(returnStatus)) && (WEXITSTATUS(returnStatus) == 0)) {
                setCheck(true);
            }
            // Program failed
            else { 
                setCheck(false);
                perror("execvp failed");
            }
        }
            
    } 
    // Error with fork() calls
    else {
        perror("fork call failed");
        cout << "There was an error with the fork() sys() call." << endl;
        exit(EXIT_FAILURE); 
    } 
}


// default constructer
Both::Both():Base(){}

// deconstructer
Both::~Both() {}

// constructer
Both::Both(string left, string right) {
    l = left;
    r = right;
}

// Both's implementation of execute
void Both::execute() {
    
    // execute left command
    Parse * leftCommand = new Parse(l);
    leftCommand->processText();
    
    // execute right command
    Cmd * rightCommand = new Cmd(r);
    rightCommand->tokenize();
    rightCommand->execute();
    
}


// default constructer
Or::Or():Base(){}

// deconstructer
Or::~Or() {}

// constructer
Or::Or(string left, string right) {
    l = left;
    r = right;
}

// Or's implementation of execute
void Or::execute() {
    
    // execute left command
    Parse * leftCommand = new Parse(l);
    leftCommand->processText();
    
    // if lsuccess is false, execute r
    if(getCheck() == false) {
        Cmd * rightCommand = new Cmd(r);
        rightCommand->tokenize();
        rightCommand->execute();
    }
}


// default constructer
And::And():Base(){}

// deconstructer
And::~And() {}

// constructer
And::And(string left, string right) {
    l = left;
    r = right;
}

// And's implementation of execute
void And::execute() {
    
    // execute left command
    Parse * leftCommand = new Parse(l);
    leftCommand->processText();
    
    // if lsuccess is true, execute r
    if(getCheck() == true) {
        Cmd * rightCommand = new Cmd(r);
        rightCommand->tokenize();
        rightCommand->execute();
    }
}


    
