#ifndef __TOKEN_H__
#define __TOKEN_H__

class Token {
	public:
		virtual void check() = 0;
    virtual void Token() = 0;
    virtual void execute() = 0;
    virtual bool isValid() = 0;

	protected:

};

#endif //__TOKEN_H__
