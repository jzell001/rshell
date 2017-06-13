#!/bin/sh

# tests for |

echo "echo hello world" | bin/rshell
#echo "echo hello world;" | bin/rshell
#echo "ls -a" | bin/rshell
#echo "git status" | bin/rshell
#echo "mkdir test" | bin/rshell
#echo "cat < eIF.txt | tr A-Z a-z | tee nOF1 | tr a-z A-z > nOF2" | bin/rshell 

#echo "cat whatever.txt | less" | bin/rshell
#echo "ls -al | grep '^d'" | bin/rshell
#echo "ps aux | wc -l" | bin/rshell
#echo "ls -l | grep " Jun " | wc -l" | bin/rshell
#echo "ps aux | grep test | wc -l" | bin/rshell


#echo "echo A && echo B || echo C && echo D | wc -l" | bin/rshell
#echo "(echo A && echo B) || (echo C && echo D) | wc -l" | bin/rshell

#echo "ls -a; echo hello || mkdir test && echo world | wc -l" | bin/rshell
#echo "(ls -a; echo hello) || mkdir test && echo world | wc -l" | bin/rshell
#echo "(ls -a; echo hello) || (mkdir test && echo world) | wc -l" | bin/rshell
#echo "ls -a; echo hello || (mkdir test && echo world) | wc -l" | bin/rshell
#echo "((ls -a; echo hello) || mkdir test && echo world) | wc -l" | bin/rshell
#echo "(ls -a; echo hello) || mkdir test && echo world) | wc -l" | bin/rshell

#echo "ls -a; echo hello && mkdir test || echo world; git status; | wc -l" | bin/rshell
#echo "(ls -a; echo hello) && (mkdir test || echo world; git status;) | wc -l" | bin/rshell
#echo "(ls -a; echo hello) && (mkdir test || echo world; git status); | wc -l" | bin/rshell
#echo "(ls -a); echo hello && (mkdir test || echo world; git status;) | wc -l" | bin/rshell

#echo "echo hello ; echo world | wc -l" | bin/rshell
#echo "(echo hello ; echo world) | wc -l" | bin/rshell
#echo "(echo hello; echo world) | wc -l" | bin/rshell
#echo "((echo hello; echo world | wc -l" | bin/rshell
#echo "echo hello; echo world)) | wc -l" | bin/rshell
#echo "(echo hello; echo world | wc -l" | bin/rshell
#echo "echo hello; echo world) | wc -l" | bin/rshell

#echo "echo hello || echo world | wc -l" | bin/rshell 
#echo "(echo hello || echo world) | wc -l" | bin/rshell 
#echo "(echo hello) || (echo world) | wc -l" | bin/rshell 
#echo "(echo hello || echo world | wc -l" | bin/rshell 
#echo "echo hello || echo world) | wc -l" | bin/rshell 
#echo "((echo hello || echo world) | wc -l" | bin/rshell 
#echo "((echo hello || echo world)) | wc -l" | bin/rshell 
#echo "(echo hello || echo world)) | wc -l" | bin/rshell 
