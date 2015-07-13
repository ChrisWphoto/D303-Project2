#include <iostream>
#include <cmath>
#include <sstream>
#include <stack>
#include "evaluator.h"
using namespace std;															//** KEY ***************************************
//  | : ||     & : &&      = : ==      n : !=
//  g : >=     l : <=      ~ : negative
const string evaluator::operators = "|&=n>g<l+-*/%^~di!";						//  d : --     i : ++
const int evaluator::precedence[] = { 1, 2, 3, 3, 4, 4, 4, 4, 5, 5, 6, 6, 6, 7, 8, 8, 8, 8 };		/////////////////////////////////////////////////

int evaluator::exp_evaluator(const string expression)
{
	stack<int> operand_stack;
	stack<char> operator_stack;
	bool completed = false;
	bool digit = false;
	char next_char, upcoming;
	istringstream tokens(expression + ' ');//added ending whitespace to help with any issues of missing the last digit on putback 7-13
	//may not be necessary for ending whitespace, but it made my ++2 work.

	//Read from string until empty
	while (++char_idx, tokens >> next_char)
	{

		if (isdigit(next_char)){
			//if it's a digit then replace and take out as int
			tokens.putback(next_char);
			int num;
			tokens >> num;

			if (digit == false)	{ operand_stack.push(num); }
			else { throw Syntax_Error("Error after character @ char: " + std::to_string(char_idx)); }

			digit = true; //now expecting an operator
		}
		else if (next_char == ')')
			throw Syntax_Error("Extra closing parenthesis found @ char: " + std::to_string(char_idx));
		else if (next_char == '(')
		{
			string parentheticalExp = ""; // ADDED BY DR for parentheses case
			int parenthesisCount = 1;
			bool open_parentheses = true;
			char addChar;
			while (open_parentheses && tokens >> addChar)
			{
				if (addChar == '(')
					parenthesisCount++;
				if (addChar == ')' && parenthesisCount == 1)
				{
					parenthesisCount--;
					break;
				}
				if (addChar == ')')
					parenthesisCount--;
				parentheticalExp += addChar;
			}
			if (parenthesisCount != 0)
				throw Syntax_Error("Missing closing parenthesis @ char: " + std::to_string(char_idx));
			operand_stack.push(exp_evaluator(parentheticalExp));
		}
		else{
			//ADDED JW 
			//Check for next character and if its a + or - then take to correct function
			upcoming = tokens.peek();

			switch (upcoming){
			case '+':case '-':
				is_decrement_increment(tokens, next_char, upcoming, operator_stack, operand_stack);
				break;
			case '=':
				if (next_char == '!' || next_char == '>' || next_char == '<' || next_char == '=')
				{
					solveBooleanEquation(next_char, operator_stack, operand_stack, tokens);
					break;
				}
				else
					throw Syntax_Error("Too many operators! Equal sign can only follow !, > or < operators @ char: " + std::to_string(char_idx));
			default:
				//if operator stack is not empty then figure out precedence, 
				//if it is empty then automatically add it
				if (!operator_stack.empty()){
					char top = operator_stack.top();

					//if top is less precedence than next char, add to stack, 
					//else solve the equation until next char is >= to top
					if (Precedence(top) < Precedence(next_char)){
						operator_stack.push(next_char);
					}
					else{
						find_equation(next_char, completed, operator_stack, operand_stack);
					}
				}
				else {
					operator_stack.push(next_char);
				}
			}
			digit = false; //can accept a digit now
		}

	}
	completed = true; //finished stringstream

	//finish equation until all operators are gone
	while (!operator_stack.empty()){
		if (operator_stack.top() == '!')
			solveBooleanEquation(operator_stack.top(), operator_stack, operand_stack, tokens);
		else
			find_equation(operator_stack.top(), completed, operator_stack, operand_stack);
		break;
	}
	return operand_stack.top();
}



void evaluator::find_equation(char oper, bool completed, stack<char>& operator_stack, stack<int>& operand_stack)
{
	int lhs, rhs, answer;
	char top;
	//if operator stack is empty throw error
	if (operator_stack.empty())
		throw Syntax_Error("The operator stack is empty, not enough operators to complete equation @ char: " + std::to_string(char_idx));

	top = operator_stack.top();

	while (!(Precedence(top) < Precedence(oper)))
	{
		//if operand stack is empty, throw error
		if (operand_stack.empty())
			throw Syntax_Error("The operand stack is empty, too many operators, not enough operands @ char: " + std::to_string(char_idx));
		rhs = operand_stack.top();
		operand_stack.pop();
		//if operand stack is empty throw error
		if (operand_stack.empty())
			throw Syntax_Error("The operand stack is empty, too many operators, not enough operands @ char: " + std::to_string(char_idx));
		lhs = operand_stack.top();
		operand_stack.pop();
		operator_stack.pop();
		if (top == '!' || top == '>' || top == '<')
			answer = solveBoolean(lhs, rhs, top, false); // Last parameter will be true only if the next operator is an equals sign
		else
			answer = solve(lhs, rhs, top);
		operand_stack.push(answer);
		if (operator_stack.empty())
		{
			break;
		}
		top = operator_stack.top();
	}
	if (!completed)//add the operator back onto the stack before returning
		operator_stack.push(oper);

}
bool evaluator::solveBooleanEquation(char oper, stack<char>& operator_stack, stack<int>& operand_stack, istringstream& tokens)
{
	int lhs, rhs;;

	string exp = "";
	char next;
	tokens >> next;
	while (tokens >> next)
	{
		exp += next;
	}
	if (exp == "" && !operand_stack.empty())
	{
		rhs = operand_stack.top();
		operand_stack.pop();
	}
	else
		rhs = exp_evaluator(exp);

	if (operand_stack.empty() && oper == '!')
	{
		lhs = 0;
		operand_stack.push(solveBoolean(lhs, rhs, oper, false));
	}
	else if (operand_stack.empty())
		throw Syntax_Error("The operand stack is empty, too many operators, not enough operands @ char: " + std::to_string(char_idx));
	else
	{
		lhs = operand_stack.top();
		operand_stack.pop();
		operand_stack.push(solveBoolean(lhs, rhs, oper, true));
	}
}
bool evaluator::solveBoolean(int lhs, int rhs, char oper, bool twoOpers) // added by DR
{
	bool answer = false;

	switch (oper)
	{
	case '!':
		if (twoOpers)
			answer = (lhs != rhs);
		else
			answer = !rhs;
		break;
	case '>':
		if (twoOpers)
			answer = (lhs >= rhs);
		else
			answer = (lhs > rhs);
		break;
	case '<':
		if (twoOpers)
			answer = (lhs <= rhs);
		else
			answer = (lhs < rhs);
		break;
	case '=':
		if (twoOpers)
			answer = (lhs == rhs);
		else
			throw Syntax_Error("Cannot have single equals sign @ char: " + std::to_string(char_idx));
		break;
	}

	return answer;
}

int evaluator::solve(int lhs, int rhs, char oper)
{
	int answer = 0;

	switch (oper)
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
	case '^':
		answer = pow(static_cast<double>(lhs), static_cast<double>(rhs));
		break;
	}

	return answer;
}


void evaluator::is_decrement_increment(istringstream& tokens, char next_char, char lookfor, stack<char>& operator_stack, stack<int>& operand_stack)
{
	int count = 0;
	char original;
	original = next_char;


	do
	{
		operator_stack.push(next_char);
		tokens >> next_char;
		count++;

	} while (next_char == lookfor && !(tokens.eof())); //continues until all '+' are gone, or stream is finished

	//checks that it's not 1++2 or just ++2 also can see if its format is similar to -++2
	if (count % 2 != 1 && !operand_stack.empty() && original == lookfor)
		throw Syntax_Error("Not enough '+' operators to increment @ char: " + std::to_string(char_idx));


	if (isdigit(next_char))
	{
		int num;
		tokens.putback(next_char);

		tokens >> num;
		operand_stack.push(num);
		char first, second;
		int temp;
		for (int i = 0; i < count / 2; i++)
		{
			if (operator_stack.empty())
				throw Syntax_Error("The operator stack is empty, cannot increment/decrement @ char: " + std::to_string(char_idx));
			first = operator_stack.top();
			operator_stack.pop();
			if (operator_stack.empty())
				throw Syntax_Error("The operator stack is empty, cannot increment/decrement @ char: " + std::to_string(char_idx));
			second = operator_stack.top();
			operator_stack.pop();
			//check the two that were popped to see if they were both '-'
			if (first != lookfor || second != lookfor)
				throw Syntax_Error("Expected '++', did not receive it");
			if (operand_stack.empty())
				throw Syntax_Error("The operand stack is empty, cannot increment/decrement without a digit! @ char: " + std::to_string(char_idx));
			temp = operand_stack.top();
			operand_stack.pop();
			if (lookfor == '+')
				temp++;
			else
				temp--;
			operand_stack.push(temp);
		}
	}
	else
	{
		throw Syntax_Error("Expected a digit, did not receive it @ char: " + std::to_string(char_idx));
	}
}
void evaluator::is_bool(istringstream& is, char next_char)
{
	//?
}
