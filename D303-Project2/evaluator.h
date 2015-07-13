#ifndef EVALUATOR_H
#define EVALUATOR_H
#include <string>
#include <iostream>
#include <sstream>
#include <stack>
#include "Syntax Error.h"
using namespace std;

class evaluator
{
public:
	evaluator()	{  }

	int Precedence(char op) const {
      return precedence[operators.find(op)];
    }

	int exp_evaluator(const string expression);
	int solve(int, int, char);
	void find_equation(char top, bool completed, stack<char>& operator_stack, stack<int>& operand_stack);
	void is_decrement_increment(istringstream&, char, char, stack<char>& operator_stack, stack<int>& operand_stack);
	void is_bool(istringstream& , char );


private:
	static const string operators;
	static const int precedence[];
	
};


#endif
