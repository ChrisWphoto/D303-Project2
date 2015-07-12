#ifndef EVALUATOR_H
#define EVALUATOR_H
#include <string>
#include <iostream>
#include <sstream>
#include <stack>
using namespace std;

class evaluator
{
public:
	evaluator()	{exp = "";}

	evaluator(string expression){
		exp = expression;
	}
	int Precedence(char op) const {
      return precedence[operators.find(op)];
    }

	int exp_evaluator(const string expression);
	int solve(int, int, char);
	void find_equation(char top, bool completed);


private:
	string exp;
	static const string operators;
	static const int precedence[];
	stack<int> operand_stack;
	stack<char> operator_stack;
};


#endif