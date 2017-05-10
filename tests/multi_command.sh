#!/bin/sh

echo "ls -a; echo hello || mkdir test && echo world" | bin/rshell
# echo "lsd -a; echo hello || mkdir test && echo world" | bin/rshell
# echo "lsd -a; ech hello || mkdi test && ech world" | bin/rshell
#echo "ls -a; echo hello && mkdir test || echo world; git status;" | bin/rshell
#echo "echo hello ; echo world" | bin/rshell
#echo "echo hello || echo world" | bin/rshell 
#echo "echo hello && echo world" | bin/rshell
#echo "echo hello world || git status && ls -a"; | bin/rshell
#echo "echo hello || echo world && git status" | bin/rshell