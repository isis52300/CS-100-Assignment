#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <vector>

using namespace std;

void Execute(string executable) {
    
    cout << "Executing " << executable;
    
}

void ForkIt() {
    
    pid_t pid = fork();
    int status;
    
    if (pid == 0) { //This is the child
        
        Execute("echo");
        cout << endl;
        
    }
    else if (pid > 0) { //This is the parent
        
        waitpid(pid, &status, 0);
        Execute("ls");
        cout << endl;
        
    }
    else { //The forking has failed
        
        cout << "The forking failed";
        exit(1);
        
    }
    
}

vector<string> Tokenizer(string userInput) {
    
    vector<string> token;
    string currWord = "";
    
    for (unsigned i = 0; i < userInput.size(); ++i) {
        
        if (userInput.at(i) == ' ') {
            if (currWord == "echo" || currWord == "ls") {
                token.push_back(currWord);
            }
            currWord = "";
        }
        else {
            currWord += userInput.at(i);
        }
        
    }
    
    return token;
}

int main() {
    
    vector<string> tokens = Tokenizer("echo hello world");
    vector<string> tokenAddOn = Tokenizer("ls -a");
    
    for (unsigned i = 0; i < tokenAddOn.size(); ++i) {
        tokens.push_back(tokenAddOn.at(i));
    }
    
    //Used for unit testing 
     for (unsigned i = 0; i < tokens.size(); ++i) {
         cout << tokens.at(i) << endl;
     }
                        
     ForkIt();
                                
     char *args[] = {"echo", "hello", "world"};
     execvp(args[0],args);
                                            
     return 0;
}
    
