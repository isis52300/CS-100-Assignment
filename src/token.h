#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Token {
	public:
    Token();
    virtual void execute() = 0;
    virtual bool isValid() = 0;

	protected:

};

#endif //__TOKEN_H__
