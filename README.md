# CS 100 Programming Project

Project Information

Winter 2020

Ashna Chadha, 862152421

Isis Dumas, 862092044


Introduction

The program will print a command prompt, read in a line of commands, and execute the commands using fork, execvp, and waitpid. These steps will execute until an exit command is executed. This program uses a composite pattern. The purpose of this pattern is structural, meaning that it is composed of classes or objects, and the scope of this pattern is class, which means that this pattern applies primarily to classes. An abstract parent Token class is created containing children, OrToken, AndToken, SemicolonToken, and CommentToken. Inputs are taken into the Tokenizer class and stored within a vector. Then, the program searches for tokens within the char vector and creates and returns another vector containing only the tokens. The Token vector then becomes an argument of the Executor class. This class executes the commands using the Token class, which checks to see if the commands and tokens are valid, else it outputs an error.
