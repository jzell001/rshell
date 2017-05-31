#!/bin/sh

echo "echo hello world #echo comment" | bin/rshell
#echo "echo hello world || git status && ls -a; #echo comment" | bin/rshell
#echo "ls -a; #comment echo world; git status " | bin/rshell
#echo "ls -a; echo hello && mkdir test && echo world;#echo comment" | bin/rshell
#echo "echo hello || echo world && git status#echo comment" | bin/rshell