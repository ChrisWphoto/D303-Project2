#include <iostream>
#include <string>
#include "evaluator.h"

using namespace std;

int main()
{
	int answer = 0;
	int a = 2;

	try
	{
		evaluator l;
		answer = l.exp_evaluator("++++2-5*3^2");
	}catch(const invalid_argument& ia)
	{
		cerr << "Invalid argument: " << ia.what() << '\n';
	}

	cout <<--++a;
	return 0;
}

//increment formats 
//		ACCEPTABLE									ERRORS
// 											1++2 = ERROR Not enough +
// 1+++2 = 4								+2  =  '                '
// ++2 = 3									++  =  Error expected a digit
// 4-++2 = 1								+++2 = Error operand stack is empty, not enough digits
// 1+++++2 = 5
