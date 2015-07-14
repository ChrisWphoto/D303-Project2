#include <iostream>
#include <string>
#include <iomanip>
#include "evaluator.h"

using namespace std;

int main()
{
	int answer = 0;
	int answer2 = 0;
	int answer3 = 0;
	int answer4 = 0;
	int answer5 = 0;
	int answer6 = 0;
	int answer7 = 0;
	int answer8 = 0;
	int answer9 = 0;
	int answer10 = 0;
	int answer11 = 0;
	int answer12 = 0;

	int error_test1 = 0;
	int error_test2 = 0;

	try
	{
		//redeclaring eval object because I want index of error to be correct if reported 
		evaluator l;
		answer = l.exp_evaluator("!(2 > 1) || (3 < 4)");
		evaluator l1;
		answer2 = l1.exp_evaluator("(4 >= 3) && !(2 == 2)");
		/*
		evaluator l2;
		answer3 = l2.exp_evaluator("1==4");
		evaluator l3;
		answer4 = l3.exp_evaluator("!(4 > -5)");
		evaluator l5;
		answer5 = l5.exp_evaluator("1+2*3");
		evaluator l6;
		answer6 = l6.exp_evaluator("++++2-5*(3^2)");

		evaluator lNegative;
		answer7 = lNegative.exp_evaluator("-2+2^2*3");
		evaluator lNegative2;
		answer8 = lNegative2.exp_evaluator("-2");
		evaluator lNegative3;
		answer9 = lNegative3.exp_evaluator("2*-(3*2)");
		
		
		evaluator lError, lError2;
		error_test1 = lError.exp_evaluator("(3+4))");
		//error_test2 = lError2.exp_evaluator("*");
		*/
	}catch(const invalid_argument& ia)
	{
		cerr << "Invalid argument: " << ia.what() << '\n';
	}

	//Table for testing
	cout << answer << endl << answer2 << endl;
	/*
	cout << endl << setw(27)<< "<--Testing-->" << endl;
	cout << setw(20) << "Expression" << setw(10) << "Result" << endl; 
	cout << setw(20) << "1+2*3" << setw(10) << answer << endl;
	cout << setw(20) << "2+2^2*3" << setw(10) << answer2 << endl;
	cout << setw(20) << "1==2" << setw(10) << answer3 << endl;
	cout << setw(20) << "!(4 > -5)" << setw(10) << answer4 << endl;
	cout << setw(20) << "++++2-5*(3^2)" << setw(10) << answer6 << endl;
	cout << setw(20) << "-2+2^2*3" << setw(10) << answer7 << endl;
	cout << setw(20) << "-2" << setw(10) << answer8 << endl;
	cout << setw(20) << "2*-(3*2)" << setw(10) << answer9 << endl;
	*/
	cout << endl;
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
