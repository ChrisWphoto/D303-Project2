#include <iostream>
#include <sstream>
#include <stack>
#include "evaluator.h"

using namespace std;

const string evaluator::operators = "|&=n>g<l+-*/%^~di!";
const int evaluator::precedence[] = {1,2,3,3,4,4,4,4,5,5,6,6,6,7,8,8,8,8};
//3-5-2*6+5*5
int evaluator::exp_evaluator(const string expression)
	{
		bool completed = false;
		char oper,next_char;;
		istringstream tokens(expression);
		while(tokens>>next_char)
		{
			if(isdigit(next_char))
			{
				tokens.putback(next_char);
				int num;
				tokens>>num;
				operand_stack.push(num);
			}
			else 
			{
				if(!operator_stack.empty())
				{
					char top = operator_stack.top();
					if(Precedence(top) < Precedence(next_char))
					{
						operator_stack.push(next_char);
					}
					else
					{
						find_equation(next_char,completed);

					}
				}
				else
				{
					operator_stack.push(next_char);
				}
			}

		}
		completed = true;
		while(!operator_stack.empty())
		{
			find_equation(operator_stack.top(), completed);
		}
		return operand_stack.top();
	}



void evaluator::find_equation(char oper, bool completed)
{
	int lhs, rhs, answer;
	char top;
	top = operator_stack.top();

	while(!(Precedence(top) < Precedence(oper)))
	{
		rhs = operand_stack.top();
		operand_stack.pop();
		lhs = operand_stack.top();
		operand_stack.pop();
		operator_stack.pop();
		answer = solve(lhs,rhs,top);
		operand_stack.push(answer);
		if(operator_stack.empty())
			{	break;}
		top = operator_stack.top();
	}
	if(!completed)
		operator_stack.push(oper);
}

int evaluator::solve(int lhs, int rhs, char oper)
{
	int answer=0;

	switch(oper)
	{
	case '+':
		answer = lhs + rhs;
		break;
	case '-':
		answer = lhs - rhs;
		break;
	case '/':
		answer = lhs / rhs;
		break;
	case '*':
		answer = lhs * rhs;
		break;
	}

	return answer;
}

