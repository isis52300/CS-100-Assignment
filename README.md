# CS 100 Programming Project

Project Information

Winter 2020

Ashna Chadha, 862152421

Isis Dumas, 862092044


# Introduction

The program will print a command prompt, read in a line of commands, and execute the commands using fork, execvp, and waitpid. These steps will execute until an exit command is executed. This program uses a composite pattern. The purpose of this pattern is structural, meaning that it is composed of classes or objects, and the scope of this pattern is class, which means that this pattern applies primarily to classes. An abstract parent Token class is created containing children, OrToken, AndToken, SemicolonToken, and CommentToken. Inputs are taken into the Tokenizer class and stored within a vector. Then, the program searches for tokens within the char vector and creates and returns another vector containing only the tokens. The Token vector then becomes an argument of the Executor class. This class executes the commands using the Token class, which checks to see if the commands and tokens are valid, else it outputs an error.

# Diagram
See images/ folder.

# Classes

**Token**

This is the abstract parent class that contains the Token children/subclasses for different types of tokens. It uses a virtual void check() function to check if the surrounding commands (left and right) are valid and determines if the input can be executed or not.

* **OrToken**

  Child class for the or (||) token.

  check() looks at both left and right of ||. Three possibilities:

  Left is valid, ignore right, do left
  
  Left is invalid, right valid, do right

  Left is invalid, right is invalid, error

* **AndToken**

  Child class for the and (&&) token. 
  
  check() looks at both left and right of &&.
  
  Both left and right have to be valid, otherwise error
  
* **SemicolonToken**

  Child class for the semicolon (;) token.
  
  check() moves to the next command after ;
  
* **CommentToken**

  Child class for the comment (#) token. 
  
  check() ignores everything to the right of the #

**Executor**

This class is a single executor class to execute commands based on the tokens stored in the vector in the Tokenizer class. It has one vector that contains all tokens that the user enters.

* Data

  table<Token *>
  
* Functions

  * execute()

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

  * makeTokenVector()
  
    * Takes in input and stores in a char vector, then finds tokens and stores those in a Token vector and returns it

# Prototypes/Research

See prototype/ directory.

# Development and Testing Roadmap

1. [Develop a Directory object](https://github.com/cs100/assignment-team-blue/issues/1) so that if the user wants to make a new directory or see the directories that are already made, that information can be stored there

    1. This will have a vector of all of the directories that the user created as well as the hidden directories that the user can use
  
1. [Make the Execute class](https://github.com/cs100/assignment-team-blue/issues/2) so that it can execute commands based on the tokens that were passed through  

    1. This class will have different functions to execute different executables 
  
    1. It will also have a function that outputs error messages if the user inputs executables that does not exist or input incorrectly  
  
1. [Create the Token class and its virtual functions](https://github.com/cs100/assignment-team-blue/issues/3) to build be able to have a baseline for the subclasses 

1. [Make the Token subclasses](https://github.com/cs100/assignment-team-blue/issues/4) that include (||), (&&), (;), and (#) so you know how to execute the different executables, such as ls and mkdir
