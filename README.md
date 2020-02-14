# CS 100 Programming Project

Project Information

Winter 2020

Ashna Chadha, 862152421

Isis Dumas, 862092044


# Introduction

The program will print a command prompt, read in a line of commands, and execute the commands using *fork*, *execvp*, and *waitpid*. These steps will execute until an exit command is entered. This program uses a composite pattern. The purpose of this pattern is structural, meaning that it is composed of classes or objects, and the scope of this pattern is class, which means that this pattern applies primarily to classes. An abstract parent Token class is created containing children, OrToken, AndToken, LsToken, MkdirToken, EchoToken, and ExitToken. Inputs are taken into the Executor class and stored within a tree in the Tokenizer class. After the tree is created, the Executor class goes through the tree and executes everything. 

# Diagram
See [images/](https://github.com/cs100/assignment-team-blue/tree/master/images) folder.

# Classes

**Token**

This is the abstract parent class that contains the Token children/subclasses for different types of tokens. It uses a virtual void execute() function to check if the surrounding commands (left and right) are valid and determines if the input can be executed or not.

* **OrToken**

  Child class for the or (||) token.

  void execute() looks at both left and right of ||. Three possibilities:

  Left is valid, ignore right, do left
  
  Left is invalid, right valid, do right

  Left is invalid, right is invalid, error
  
  bool isValid() returns true if valid 

* **AndToken**

  Child class for the and (&&) token. 
  
  void execute() looks at both left and right of &&.
  
  Both left and right have to be valid, otherwise error
  
  bool isValid() returns true if valid
  
* **LsToken**
  
  Child class for the ls command token.
   
  void execute() 
  
  bool isValid() returns true if valid
  
* **MkdirToken**

  Child class for the mkdir command token.
  
  void execute()
  
  bool isValid() returns true if valid
  
* **EchoToken**

  Child class for the echo command token.
  
  void execute() outputs the argument
  
  bool isValid() returns true if valid
  
* **ExitToken**

  Child class for the exit command token.
  
  void execute() exits from the shell.
  
  bool isValid() returns true if valid

**Executor**

This class is a single executor class to execute commands based on the tokens stored in the vector in the Tokenizer class. It has one vector that contains all tokens that the user enters.

* Data

  table<Token *>
  
* Functions

  * Executor()
  
    * Constructor calls functions from other classes

  * void parse()
  
    * Parses through the commands and arguments entered in the shell
  
  * void execute()

    * Executes the commands after looking at the tokens in the table vector
    
    * Outputs $ after each command is executed to prompt again
    
  * ls()
  
    * Executes the ls command (lists all the directories and hidden directories)
    
  * mkdir()
  
    * Makes a new directory
    
  * echo()
  
    * Prints out whatever is after the echo command until it hits a token or the end
    
  * exit()
  
    * Exits from the shell
    
  * error()
  
    * Prints an error when a command entered by the user is not found

**Tokenizer**

This class takes the input from the user and stores it in a char vector. Then, it looks for tokens in the char vector and stores those tokens in a Token vector and returns it. 

* Data

  * line<char *>
  
  * table<Token *>
  
* Functions

  * Tokenizer()
  
    * Constructor
  
  * Token* tokenize(vector<string> userInput)
  
    * Takes in input and checks for the tokens #, ;, &&, and ||, including the command tokens.

# Prototypes/Research

See [prototype/](https://github.com/cs100/assignment-team-blue/tree/master/prototype) directory.

I found that when you fork an action, it can be tricky to get the right commands to run or output to the user in the way you want. While the _waitpid()_ function is useful to help fix this problem, we still need some practice with it to ensure we get the desired result. I also found that the _execvp()_ function requires a file to execute with and that detail was not in my mind when trying to design the code for the shell, so there may be changes to our original design to help with this. 

After testing out how a normal shell reacts to different connectors, I found that when running one connector that works and one that doesn’t, an error message is printed on one line and the executer runs correctly on the next line. This will be useful to know when setting up our shell so that we can ensure that the results come out correctly. I also noticed that when running “ls -a”, the files, directories, and hidden directories are all printed out in alphabetical order, regardless of whether they are hidden or not (or if they have “.” in front of them or not). Also, the directories are output to the user from top to bottom instead of from left to right when using “ls -a” while “ls” outputs from left to right. If we are to output the hidden directories in the same matter, then our code will have to be more detailed than expected and include a lot more features. Also, I have not tested what would happen if there are multiple spaces after an executable or between some other words, like if the user types in “echo yes I love    spaces.” If we have to take this into account, then there will be some adjustments to out code to accommodate for such a feature.

# Development and Testing Roadmap

1. [Develop a Directory object](https://github.com/cs100/assignment-team-blue/issues/1) so that if the user wants to make a new directory or see the directories that are already made, that information can be stored there

    1. This will have a vector of all of the directories that the user created as well as the hidden directories that the user can use
  
1. [Make the Execute class](https://github.com/cs100/assignment-team-blue/issues/2) so that it can execute commands based on the tokens that were passed through  

    1. This class will have different functions to execute different executables 
  
    1. It will also have a function that outputs error messages if the user inputs executables that does not exist or input incorrectly  
  
1. [Create the Token class and its virtual functions](https://github.com/cs100/assignment-team-blue/issues/3) to build be able to have a baseline for the subclasses 

1. [Make the Token subclasses](https://github.com/cs100/assignment-team-blue/issues/4) that include (||), (&&), (;), and (#) so you know how to execute the different executables, such as ls and mkdir
