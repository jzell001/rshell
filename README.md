<h1>
<p>CS100</p>
<p>Assignment 2</p>
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
<ol>
<li>g++ main.cpp Base.cpp</li>

<li>make clean; make</li>
</ol>

<h2>
----------------------
Summary / Intro
----------------------
</h2>

When executed, this program simulate the basic commands of the bash terminal 
using the fork(), execvp(), and wait()/waitpid() sys() calls in C++. It begins
by prompting the user with the usual '$' prompt to enter commands. It then 
takes in arguments from the user and exectutes them in a left-to-right fashion.

To exit the terminal, the user simply types 'exit' to revert back tot he main
terminal.
    
<h2>
-------------------------
Class Specific Details
-------------------------
</h2>

There are six classes that are implemented in this program, a base class 
named 'Base', a 'Parse' and 'Cmd' class and three connector classes, giving 
a listing of classes as: 
<ul>
<li>Base</li>
<li>Parse</li>
<li>Cmd</li>
<li>Both</li>
<li>Or</li>
<li>And</li>
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
It first checks if the string has a ';' on the very end.  If it does, it
is removed from the string.  Next it looks for the last connector (;, ||,
&&) in the string.  When found it saves the connector's index and it's 
type (if it's ;, ||, &&).  It uses this information to then split the
string into two strings called leftText and rightText. LeftText contains
everything to the left of the connector while rightText contains everything
to it's right.  'processText' then creates a point to an And, Or, or Both
object based off the connector it found and constructs it using both the
leftText and rightText as its parameters. It then will call the 'execute'
on the newly created pointer object.  Additionally if Parse is constructed
with a single command it will bypass all of the above and instead 
immediately create a Cmd pointer called 'c' that points to a Cmd object that
is constructed with that singular command.  It then calls 'tokenize' and
'execute' on pointer object c.

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
execute one or both of their childre.

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

<h2>
-------------------------
Bugs
-------------------------
</h2>

<ul>
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
 
<li>The code was tested on the following commands:
<ul>
<li>ls</li>
<li>mkdir</li>
<li>echo</li>
<li>rm</li>
<li>rmdir</li>
</ul>
</li>
</ul>
