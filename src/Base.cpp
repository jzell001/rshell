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

// #include <sys/types.h>
#include <sys/stat.h>
// #include <unistd.h>

//parse.v2 
#include <algorithm>

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

bool Parse::pathFinder(const char* path, char flg) {
    
    // create a buffer, pathname, and flag
    struct stat buf;
    const char *pathname = path;
    char flag = flg;
    
    // open a status using pathname and buffer
    stat(pathname, &buf);
    string t = "true";
    string f = "false";
    
    // check if a file or a directory
    if(flag == 'e') {
        if ( S_ISREG(buf.st_mode) || S_ISDIR(buf.st_mode) ) {
            cout << "(True)" << endl;
            return true;
        }
        else {
            cout << "(False)" << endl;
            return false;
        }
    }
    // check if a file or a directory and is a file
    else if(flag == 'f') {
        if ( S_ISREG(buf.st_mode) || S_ISDIR(buf.st_mode) ) {
            if (S_ISREG(buf.st_mode)) {
                cout << "(True)" << endl;
                return true;
            }
            else {
                cout << "(False)" << endl;
                return false;
            }
        }
        else {
            cout << "(False)" << endl;
            return false;
        }
    }
    // check if a file or a directory and is a directory
    else if(flag == 'd') {
        if (S_ISREG(buf.st_mode) || S_ISDIR(buf.st_mode)) {
            if (S_ISDIR(buf.st_mode)) {
                cout << "(True)" << endl;
                return true;
            }
            else {
                cout << "(False)" << endl;
                return false;
            }
        }
        else {
            cout << "(False)" << endl;
            return false;
        }
    }
    else {
        cout << "no flag" << endl;
        return false;
    }
    
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
    bool foundParenthesis = false;
    bool validParenthesisOrder = true;
    bool test = false;
    bool validTest = false;
    int foundFParenthesis = -1;
    int foundBParenthesis = -1;
    int correctNumParenthesis = 0;
    int nestedCount = 0;
    string pUserInput = "";
    char * limitedUserInput = new char[userInputLength+1];
    strcpy(limitedUserInput, userInput.c_str());
    int lFoundSemiColon = -1;
    int lFoundOr = -1;
    int lFoundAnd = -1;
    string token1 = "";
    char flagg = ' ';
    
    
    // get rid of any ';'s at the end of the command
    if( (userInputLength - 1) == firstSemiColon) {
        userInput = userInput.substr(0 , userInput.rfind(";"));
    }
    
    // look for instances of "(" or ")"
    foundFParenthesis = userInput.rfind("(");
    foundBParenthesis = userInput.rfind(")");
    
    // set parenthesis flag
    if( foundFParenthesis != -1 || foundBParenthesis != -1) {
        foundParenthesis = true;
    }
    
    // make sure there's valid number of parenthesis
    if(foundParenthesis == true) {
        char * tempStr = new char[userInputLength+1];
        strcpy(tempStr, userInput.c_str());
        for(int p=0; p < userInputLength; p++) {
            if(tempStr[p] == '(') {
                correctNumParenthesis++;
                if(correctNumParenthesis > nestedCount) {
                    nestedCount = correctNumParenthesis;
                }
            }
            if(tempStr[p] == ')') {
                correctNumParenthesis--;
            }
            
            // limit where rfind() can search
            if(correctNumParenthesis == 0) {
                limitedUserInput[p] = tempStr[p]; 
            }
            else {
                limitedUserInput[p] = ' ';
            }
            
            if(correctNumParenthesis < 0) {
                validParenthesisOrder = false;
            }
        }
        
        // make sure command is in a valid format
        if(correctNumParenthesis == 0) {
            //validParenthesisCount = true;
        }
        // exit current command is there is an incorrect number of parenthesis
        else {
            //validParenthesisCount = false;
            cout << "bash: syntax error near unexpected token `)'" << endl;
            return;
        }
        // exit current command if the parenthesis are in an incorrect order
        if(validParenthesisOrder == false) {
            cout << "bash: Incorrect order of parenthesis" << endl;
            //cout << "bash: syntax error near unexpected token `)'" << endl;
            return;
        }
    }
    
    //create temp string for further processing
    string pLimitedUserInput(limitedUserInput);
    
    // look for instances of ";", "||", "&&"
    foundSemiColon = userInput.rfind(";");
    foundOr = userInput.rfind("||");
    foundAnd = userInput.rfind("&&");
     
    // limited look for instances of ";", "||", "&&
    if(foundParenthesis == true) {
        lFoundSemiColon = pLimitedUserInput.rfind(";");
        lFoundOr = pLimitedUserInput.rfind("||");
        lFoundAnd = pLimitedUserInput.rfind("&&");
    }

    // single command with no parenthesis (also looks for test syntax)
    if(foundSemiColon == -1 && foundAnd == -1 && foundOr == -1) {
        
        // not parenthesis
        if(foundParenthesis == false) {
            
            // creates Cmd object and runs tokenize
            Cmd* c = new Cmd(userInput);
            c->tokenize();
            
            // searches for test function argm index 0
            if(!strcmp(c->argm[0],"test") || !strcmp(c->argm[0],"[")  ) {
                validTest = false;
                test = true;
                
                // makes sure '[' ends with a ']'
                if(!strcmp(c->argm[0],"[")) {
                
                    // finds length of argm array
                    int counter = 0;
                    while(c->argm[counter] != NULL) {
                        counter++;
                    }
                    
                    // checks if last token is a ']' string
                    if(strcmp(c->argm[counter-1],"]") ) {
                        cout << "bash: [: missing `]'" << endl;
                        validTest = false;
                    }
                    // run test normally
                    else {
                        validTest = true;
                    }
                }
                // else its checking the other syntax which is always true
                else {
                    validTest = true;
                }
            }
            // no test syntax detected - run command normally
            else {
                if(test == false) {
                    c->execute();
                }
            }
            
            // run custom test()
            if(validTest == true) {
                // looks for any flags passed in
                token1 = c->argm[1];
                token1 = token1.substr(0,1);
                const char * token1Compare = token1.c_str();
                
                // compares flag to e/f/d/other
                if(!strcmp(token1Compare,"-" )) {
                    
                    flagg = ' ';
                    
                    // sets flag based on contents of token1
                    if(!strcmp(c->argm[1],"-e" )) {
                        flagg = 'e';
                    }
                    else if(!strcmp(c->argm[1],"-f" )) {
                        flagg = 'f';
                    }
                    else if(!strcmp(c->argm[1],"-d" )) {
                        flagg = 'd';
                    }
                    else {
                        cout << "bash: invalid flag" << endl;
                        validTest = false;
                    }
                    
                        if(validTest == true) {
                            bool check1 = pathFinder(c->argm[2],flagg );
                            setCheck(check1);
                        }
                        else {
                            bool invalidFlag = false;
                            setCheck(invalidFlag);
                        }

                }
                
                else {
                        flagg = 'e';
                        bool check2 = pathFinder(c->argm[1],flagg );
                        setCheck(check2);
                }
            }
        }
    }
    
    // multiple commands with no parenthesis
    else {
        // with no parenthesis
        if(foundParenthesis == false) {
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
    
    /////////////////////////////////////////////////////////////////////////
    
    // single command surrounded by parenthesis
    if(lFoundSemiColon == -1 && lFoundAnd == -1 && lFoundOr == -1) {
        // single commands with parenthesis
        if(foundParenthesis == true) {
 
            //temp holding variabel
            string uI = userInput;
            
            //remove first instance of '('
            int foundFirstParenthesis = uI.find("(");
            uI.erase(foundFirstParenthesis,1);
            
            //remove last instance of ')'
            int foundLastParenthesis = uI.rfind(")");
            uI.erase(foundLastParenthesis,1);

            Parse * p = new Parse(uI);
            p->processText();
        }
        
    }
    
    // multiple commands
    else {
        // no parentheis
        if(foundParenthesis == false) {
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
        
        // with parenthesis
        if(foundParenthesis == true) {
            // find index and type of first connector
            if(lFoundSemiColon != -1) {
                firstConIndex = foundSemiColon;
                firstConType = ";";
            }
            if(lFoundOr != -1 && firstConIndex < lFoundOr) {
                firstConIndex = lFoundOr;
                firstConType = "||";
            }
            if(lFoundAnd != -1 && firstConIndex < lFoundAnd) {
                firstConIndex = lFoundAnd;
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
        int errCode = errno;
        
        // error output for invalid commands
        cout << "bash: " << commandName << ": command not found" << endl;
        
        exit(errCode);
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
                //perror("execvp failed");
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
    
    // process left command
    Parse * leftCommand = new Parse(l);
    leftCommand->processText();
    
    // process right command
    Parse * rightCommand = new Parse(r);
    rightCommand->processText();
    
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
    
    // process left command
    Parse * leftCommand = new Parse(l);
    leftCommand->processText();
    
    // if lsuccess is false, process r
    if(getCheck() == false) {
        Parse * rightCommand = new Parse(r);
        rightCommand->processText();
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
    
    // if lsuccess is true, process r
    if(getCheck() == true) {
        Parse * rightCommand = new Parse(r);
        rightCommand->processText();
    }
}


    
