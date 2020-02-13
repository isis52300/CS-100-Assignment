#ifndef __EXECUTOR_H__
#define __EXECUTOR_H__

class Executor {
	public:
    
        Executor();
    
		void parse();
		void execute();
		void ls();
		void mkdir();
		void echo();
		void exit();
		void error();
	
	protected:
		
};

#endif //__EXECUTOR_H__
