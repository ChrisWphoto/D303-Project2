#include <iostream>
#include <sstream>
#include <stack>
#include "evaluator.h"
																				//** KEY ***************************************
using namespace std;															//  | : ||     & : &&      = : ==      n : !=
																				//  g : >=     l : <=      ~ : negative
const string evaluator::operators = "|&=n>g<l+-*/%^~di!";						//  d : --     i : ++
const int evaluator::precedence[] = {1,2,3,3,4,4,4,4,5,5,6,6,6,7,8,8,8,8};		/////////////////////////////////////////////////
//3-5-2*6+5*5
int evaluator::exp_evaluator(const string expression)
	{
		bool completed = false;
		bool digit = false;
		char next_char, upcoming;
		istringstream tokens(expression);
		//Read from string until empty
		while(tokens>>next_char)
		{ 
			if(isdigit(next_char)){ //if it's a digit then replace and take out as int
				tokens.putback(next_char);
				int num;
				tokens>>num;
				if (digit == false)	{ operand_stack.push(num); }
				else { 
					//error gott figure out how to terminate program
					cout << "ERROR After character '" << num << "' expecting an operator, received a digit";
					return 0;
				}
				
				digit = true; //now expecting an operator
			}
			else{

				//ADDED JW 
				//Check for next character and if its a + or - then take to correct function
				upcoming = tokens.peek();
				switch (upcoming){
				case '+':
					is_increment(tokens, next_char);
					tokens >> next_char;
					break;
				case '-':
					is_decrement(tokens, next_char);
					tokens >> next_char;
					break;
				default:
					if (!operator_stack.empty()){
						char top = operator_stack.top();
						if (Precedence(top) < Precedence(next_char)){
							operator_stack.push(next_char);
						}
						else{
							find_equation(next_char, completed);
						}
					}
					else {
						operator_stack.push(next_char);
					}
				}
				digit = false; //can accept a digit now
			}

		}
		completed = true;
		while(!operator_stack.empty()){
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
			{break;}
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
	case '%':
		answer = lhs % rhs;
		break;
	}

	return answer;
}


void evaluator::is_increment(istringstream& tokens, char next_char)
{
	//need to verify that its not 3++2 but 3+++2 works
	int count = 0;
	char upcoming;
	do
	{
		operator_stack.push(next_char);
		tokens>>next_char;
		upcoming = tokens.peek();
		count++;

	} while (next_char == '+');
	if (isdigit(next_char))
	{
		tokens.putback(next_char);
		int num;
		tokens >> num;
		operand_stack.push(num);
		int temp;
		for (int i = 0; i < count / 2; i++)
		{
			operator_stack.pop();
			operator_stack.pop();
			//Probably need to check the two that were popped to see if they were both '+'

			temp = operand_stack.top();
			operand_stack.pop();
			temp++;
			operand_stack.push(temp);
		}
	}
	else
	{
		cout << "ERROR!";
		system("pause");
	}
}
void evaluator::is_decrement(istringstream& tokens, char next_char)
{
	//not finished
	int count = 0;
	char upcoming = tokens.peek();

	do
	{
		operator_stack.push(next_char);
		tokens >> next_char;
		upcoming = tokens.peek();
		count++;

	} while (next_char == '-');
	if (isdigit(next_char))
	{
		tokens.putback(next_char);
		int num;
		tokens >> num;
		operand_stack.push(num);
		int temp;
		for (int i = 0; i < count / 2; i++)
		{
			operator_stack.pop();
			operator_stack.pop();
			//Probably need to check the two that were popped to see if they were both '+'

			temp = operand_stack.top();
			operand_stack.pop();
			temp--;
			operand_stack.push(temp);
		}
	}

}
void evaluator::is_bool(istringstream& is, char next_char)
{
	//?
}
