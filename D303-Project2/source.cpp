#include <iostream>
#include <string>
#include "evaluator.h"

using namespace std;

int main()
{
	int answer = 0;
	int answer2 = 0;
	int a = 2;

	int error_test1 = 0;
	int error_test2 = 0;

	try
	{
		evaluator l;
		
		//answer = l.exp_evaluator("3 >= (4-2)");
		//answer2 = l.exp_evaluator("!(4 > 5)");

		//error_test1 = l.exp_evaluator("(3+4))");
		error_test2 = l.exp_evaluator("*");

	}catch(const invalid_argument& ia)
	{
		cerr << "Invalid argument: " << ia.what() << '\n';
	}

	//cout <<--++a;
	cout << answer << endl << answer2 << endl;
	system("pause");
	return 0;
}

//increment formats 
//		ACCEPTABLE									ERRORS
// 											1++2 = ERROR Not enough +
// 1+++2 = 4								+2  =  '                '
// ++2 = 3									++  =  Error expected a digit
// 4-++2 = 1								+++2 = Error operand stack is empty, not enough digits
// 1+++++2 = 5
