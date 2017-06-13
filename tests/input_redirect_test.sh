#!/bin/sh

# tests for <

echo "cat < eIF.txt | tr A-Z a-z | tee nOF1 | tr a-z A-z > nOF2" | bin/rshell 
#echo "sort < list_of_names.txt" | bin/rshell 
#echo "cat < testfile.txt" | bin/rshell
#echo "cat < testfile.txt > newTestFile.txt" | bin/rshell
#echo "sort < list_of_schools.txt > sorted_list.txt" | bin/rshell
#echo ""


#echo "cat < ls -a; echo hello || mkdir test && echo world | wc -l" | bin/rshell
#echo "cat < (ls -a; echo hello) || mkdir test && echo world | wc -l" | bin/rshell
#echo "cat < (ls -a; echo hello) || (mkdir test && echo world) | wc -l" | bin/rshell
#echo "cat < ls -a; echo hello || (mkdir test && echo world) | wc -l" | bin/rshell
#echo "cat < ((ls -a; echo hello) || mkdir test && echo world) | wc -l" | bin/rshell
#echo "cat < (ls -a; echo hello) || mkdir test && echo world) | wc -l" | bin/rshell

#echo "cat < ls -a; echo hello && mkdir test || echo world; git status; | wc -l" | bin/rshell
#echo "cat < (ls -a; echo hello) && (mkdir test || echo world; git status;) | wc -l" | bin/rshell
#echo "cat < (ls -a; echo hello) && (mkdir test || echo world; git status); | wc -l" | bin/rshell
#echo "cat < (ls -a); echo hello && (mkdir test || echo world; git status;) | wc -l" | bin/rshell

#echo "cat < echo hello ; echo world | wc -l" | bin/rshell
#echo "cat < (echo hello ; echo world) | wc -l" | bin/rshell
#echo "cat < (echo hello; echo world) | wc -l" | bin/rshell
#echo "cat < ((echo hello; echo world | wc -l" | bin/rshell
#echo "cat < echo hello; echo world)) | wc -l" | bin/rshell
#echo "cat < (echo hello; echo world | wc -l" | bin/rshell
#echo "cat < echo hello; echo world) | wc -l" | bin/rshell

#echo "cat < echo hello || echo world | wc -l" | bin/rshell 
#echo "cat < (echo hello || echo world) | wc -l" | bin/rshell 
#echo "cat < (echo hello) || (echo world) | wc -l" | bin/rshell 
#echo "cat < (echo hello || echo world | wc -l" | bin/rshell 
#echo "echo hello || echo world) | wc -l" | bin/rshell 
#echo "cat < ((echo hello || echo world) | wc -l" | bin/rshell 
#echo "cat < ((echo hello || echo world)) | wc -l" | bin/rshell 
#echo "cat < (echo hello || echo world)) | wc -l" | bin/rshell 