<h1>
<p>CS100</p>
<p>Assignment 4</p>
<p>Jason Zellmer</p>
<p>Duran Hughes</p>
</h1>

<h2>
----------------------
Files
----------------------
</h2>

<ul>
<li>main.cpp</li>
<li>Base.cpp</li>
<li>Base.h</li>
<li>makefile</li>
</ul>

<h2>
----------------------
Command Line Arguments
----------------------
</h2>
g++ main.cpp Base.cpp
<ol>
<li>cd rshell</li>
<li>make clean; make</li>
<li>cd bin</li>
<li>./rshell</li>
</ol>

<h2>
----------------------
Summary / Intro
----------------------
</h2>

When executed, this program simulate the basic commands of the bash terminal 
using the fork(), execvp(), wait()/waitpid(), dup(), and dup2() sys() calls in 
C++. In addition, it is able to recognize precedence operations created by using
parentheses in command arguments. It also implements the 'test' function that
is typically utilized in the terminal to verify if path file/directories exist.
Finally, it implements the redirection/pipe commands '<', '>', '>>', and '|'.
It begins by prompting the user with the usual '$' prompt to enter commands. 
It then takes in arguments from the user and exectutes them in a left-to-right 
fashion.

To exit the terminal, the user simply types 'exit' to revert back to the main
terminal.
    
<h2>
-------------------------
Class Specific Details
-------------------------
</h2>

There are multiple classes that are implemented in this program, a base class 
named 'Base', a 'Parse' and 'Cmd' class and multiple connector classes, giving 
a listing of classes as: 
<ul>
<li>Base</li>
<li>Parse</li>
<li>Cmd</li>
<li>Both</li>
<li>Or</li>
<li>And</li>
<li>Pipe</li>
<li>Redirect1</li>
<li>Redirect2</li>
</ul>

<h3>Base:</h3>
The main objective for the Base class is to set up the interface that the 
other classes utilize. In addition, it has a data member 'value' that is
used in the connector classes (And, Or, Both) to determine if it should
execute the left/right childs depending on their respective conditions.

<h3>Parse:</h3>
Parse is constucted with a single string that contains the commands it 
is to parse through and assigns it to it's userInput string.The Parse class
has 1 function called 'processText'.  The 'processText' function is void
and takes in no arguments.  It works on string contained in it's userInput.
It first checks for parentheses in the string and keeps track of the number of 
open '(' and closed ')' parentheses. This is done not only to be able to
recognize sub-arguments within a string, but also as a check to verify that
arguments are being passed/entered correctly. It then checks if the string has 
a ';' on the very end.  If it does, it is removed from the string.  Next it 
looks for the last connector (;, ||, &&, >, >>) in the string.  When found it saves 
the connector's index and it's type (if it's ;, ||, &&, >, >>).  It uses this 
information to then split the string into two strings called leftText and 
rightText. LeftText contains everything to the left of the connector while 
rightText contains everything to it's right. 'processText' then creates a point 
to an And, Or, or Both object based off the connector it found and constructs 
it using both the leftText and rightText as its parameters. It then will call 
the 'execute' on the newly created pointer object. Additionally if Parse is 
constructed with a single command it will bypass all of the above and instead 
immediately create a Cmd pointer called 'c' that points to a Cmd object that
is constructed with that singular command.  It then calls 'tokenize' and
'execute' on pointer object c. An additional function was added to parse to
verify if a path exists as a regular file or a directory when the 'test' 
function (or it's equivalent brackets '[ ]') is called. Prior to execute being
called, it verifies if tokenized arguments have the 'test' command or their
equivalent brackets. If they exist, it then checks for the flags required to
check if a path exists ('e' flag), if the path exists and is a regular file
('f' flag), and if the path exists and is a directory ('d' flag). By default, 
if a flag is not entered, the 'e' flag is implemented. Once this flag is 
verified, it utilzes the stat() function along with the S_ISREG and S_ISDIR
functions to verify the path exists as directed above. It then returns true 
(which is '1' or above for c++) or false (which is '0' for c++) for each 
respective case. In addtion, in prints '(True)' or '(False)' for each 
respective case. This can then be used in combination with the other connectors 
if requested. Note: the 'test' command in linux returns 0 for true and 1 for
false, which is the opposite of what is required in c++. This is because the
'test' command in linux works by using the sys calls described elsewhere in 
this file, which require a 0 when an operation executed without error and a 
non-zero when an error occurred. While in c++, to verify that a path exists
using created 'test' function, true is 1 and false is 0.  Additionally parse 
will check single commands to see if they contain the input redirection symbol,
'<'.  If it finds '<' it strips it from command's string before executing and 
in that fashion it correctly handles input redirection.

<h3>Cmd:</h3>
The Cmd class has two functions, 'tokenize' and 'execute'. Tokenize is
responsible for taking a string of a command and it's potential arguments
and converting it into an array of char pointers with the the command as 
the first element and any arguments as the remaining elements. Execute for
the Cmd class takes in the array of char pointers created by the tokenize
function and sends them to the execvp() sys() call. It does this by 
creating a copy of the current process image using the fork() sys() call
and then telling the parent process to wait for the child process to
terminate until moving to the parent process. Inside the parent process, 
there is an if/else statement that is used to set the 'value' from the 
Base class that the connectors utilize in determine if they should 
execute one or both of their children.

<h3>Connector Classes:</h3>
The connector classes all take in two arguments. They each assume the left
argument is a collection (or a leaf node of Cmd class) and the right 
argument is a leaf node of Cmd class. They each have a decision tree of
two nodes and they make their respective decisions based on their name.

<h3>And:</h3>
The And class has a left and a right child and executes the right child 
only if the left child executes correctly.

<h3>Or:</h3>
The Or class has a left and a right child and executes the right child 
only if the left child did not execute correctly.

<h3>Both:</h3>
The Both class has a left and a right child and always executes both the 
left and right children.

<h3>Pipe:</h3>
The pipe class has a left and a right child and always executes both the
left and right children.  However before it excutes either it first forks.
In the child process it redirects output destined for the terminal to one end
of our pipe.  Then it executes the right command and exits the child process.
In the parent process it redirects input from the pipe to the right command
before calling execute.  In this fashion input from the left child is piped
to the right child.

<h3>Redirect1 ('>'):</h3>
This class has a left and a right child and takes the left child and redirects
the output of the left child to the file name in the right child, overwriting
the contents of the file if the file already exists, creating the file if it
does not exist.

<h3>Redirect2 ('>>'):</h3>
This class has a left and a right child and takes the left child and redirects
the output of the left child to the file name in the right child, appending
the contents of the file if the file already exists, creating the file if it
does not exist.



<h2>
-------------------------
Bugs
-------------------------
</h2>

<ul>

<li>There was an issue at some point with the two redirection commands '>' and 
'>>' not talking to each other. It seems to be fixed now, but just the issue 
was, if a file was created using the '>' command, then trying to append
to that file using the '>>' command would result in creating a new file by the 
same name. If a file was created using the 'touch' command, it could be appended
using the '>>' command correctly. However, if the '>' command was then called
on the same file, a new file would be created with the same name. Again, this
issue seems to be resolved, but was an issue prior final modifications.</li>
From Assignment 3 and prior:
<li>There is still an issue running the 'test' commands as we were not able 
to correct it from Assignment 3, so any commands using 'test' may not perform
correctly</li>
From Assignment 2 and prior:
<li>The array of command and arguments used in the tokenize function is hard 
 coded to be of lenght 1024, and is not dynamically allocated. This was 
 done with the idea that the user will most likely not need an array of 
 command and arguments longer than 1024 elements.</li>
 <li>When tested using scripts an extra dollar sign ($) is printed
 to the terminal.  This does not occur if the program is run normally with a 
 user manually entering the input instead of through the use of scripts.</li>
 <li>rshell throws out an logic error code if user enters a single command 
 (ex: echo hello) and ends it with an "||" or "&&".  Does not occure in the
 case of ending a command with a ";"</li>
 <li>we are unable to implement perror() for our execvp system call.  When it 
 was implemented perror("execvp failed") would cause it to output "exevcp
 failed: Success" to the terminal.  As a result we implement our own version
 of perror that will notify the user when a execvp has failed to run.  Our
 version outputs "bash: -command-: command not found" to the terminal.</li>
 
</ul>
