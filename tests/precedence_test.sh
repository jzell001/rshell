#!/bin/sh

#echo "echo A && echo B || echo C && echo D" | bin/rshell
#echo "(echo A && echo B) || (echo C && echo D)" | bin/rshell

#echo "ls -a; echo hello || mkdir test && echo world" | bin/rshell
#echo "(ls -a; echo hello) || mkdir test && echo world" | bin/rshell
#echo "(ls -a; echo hello) || (mkdir test && echo world)" | bin/rshell
#echo "ls -a; echo hello || (mkdir test && echo world)" | bin/rshell
#echo "((ls -a; echo hello) || mkdir test && echo world)" | bin/rshell
#echo "(ls -a; echo hello) || mkdir test && echo world)" | bin/rshell

#echo "ls -a; echo hello && mkdir test || echo world; git status;" | bin/rshell
#echo "(ls -a; echo hello) && (mkdir test || echo world; git status;)" | bin/rshell
#echo "(ls -a; echo hello) && (mkdir test || echo world; git status);" | bin/rshell
#echo "(ls -a); echo hello && (mkdir test || echo world; git status;)" | bin/rshell

#echo "echo hello ; echo world" | bin/rshell
#echo "(echo hello ; echo world)" | bin/rshell
#echo "(echo hello; echo world)" | bin/rshell
#echo "((echo hello; echo world" | bin/rshell
#echo "echo hello; echo world))" | bin/rshell
#echo "(echo hello; echo world" | bin/rshell
#echo "echo hello; echo world)" | bin/rshell

#echo "echo hello || echo world" | bin/rshell 
#echo "(echo hello || echo world)" | bin/rshell 
#echo "(echo hello) || (echo world)" | bin/rshell 
#echo "(echo hello || echo world" | bin/rshell 
#echo "echo hello || echo world)" | bin/rshell 
#echo "((echo hello || echo world)" | bin/rshell 
#echo "((echo hello || echo world))" | bin/rshell 
#echo "(echo hello || echo world))" | bin/rshell 

#echo "echo hello world || git status && ls -a"; | bin/rshell
#echo "(echo hello world) || (git status && ls -a";) | bin/rshell
#echo "(echo hello world) || (git status && ls -a"); | bin/rshell
#echo "(echo hello world || (git status && ls -a";)) | bin/rshell
#echo "(echo hello world || (git status && ls -a");) | bin/rshell

