#include <iostream>
#include <string>
#include <iomanip>
#include "evaluator.h"

using namespace std;

int main()

{
	
	int a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15;
	string exp1, exp2, exp3, exp4, exp5, exp6, exp7, exp8, exp9, exp10, exp11, exp12, exp13, exp14, exp15;
	evaluator l1, l2, l3, l4, l5, l6, l7, l8, l9, l10, l11, l12, l13, l14, l15;

	exp1 = "3*-(2+3)";
	exp2 = "-(3+2)";
	exp3 = "(-3)";
	exp4 = "++3*-4";
	exp5 = "(5 >= 1)"; 
	exp6 = "!(3 || 5)"; //anything not 0 is true
	exp7 = "!!3!=1";
	exp8 = "!!(5 >=1)";
	exp9 = "!!!(5 > 1)";
	exp10 = "!!!!(5*1 > 1+1)";
	exp11 = "--1*5";
	

	//testing
	try
	{
		cout << "Evaluating a1" << endl;
		a1 = l1.exp_evaluator(exp1); 
		cout << "Evaluating a2" << endl;
		a2 = l2.exp_evaluator(exp2);
		cout << "Evaluating a3" << endl;
		a3 = l3.exp_evaluator(exp3);
		cout << "Evaluating a4" << endl;
		a4 = l4.exp_evaluator(exp4);
		cout << "Evaluating a5" << endl;
		a5 = l5.exp_evaluator(exp5);
		cout << "Evaluating a6" << endl;
		a6 = l6.exp_evaluator(exp6);
		cout << "Evaluating a7" << endl;
		a7 = l7.exp_evaluator(exp7);
		cout << "Evaluating a8" << endl;
		a8 = l8.exp_evaluator(exp8);
		cout << "Evaluating a9" << endl;
		a9 = l9.exp_evaluator(exp9);
		cout << "Evaluating a10" << endl;
		a10 = l10.exp_evaluator(exp10);
		cout << "Evaluating a11" << endl;
		a11 = l11.exp_evaluator(exp11);


		cout << endl << setw(29) << "<--Testing-->" << endl;
		cout << setw(25) << "Expression" << setw(10) << "Result" << endl;
		cout << setw(25) << exp1 + " " << setw(10) << a1 << endl;
		cout << setw(25) << exp2 + " " << setw(10) << a2 << endl;
		cout << setw(25) << exp3 + " " << setw(10) << a3 << endl;
		cout << setw(25) << exp4 + " " << setw(10) << a4 << endl;
		cout << setw(25) << exp5 + " " << setw(10) << a5 << endl;
		cout << setw(25) << exp6 + " " << setw(10) << a6 << endl;
		cout << setw(25) << exp7 + " " << setw(10) << a7 << endl;
		cout << setw(25) << exp8 + " " << setw(10) << a8 << endl;
		cout << setw(25) << exp9 + " " << setw(10) << a9 << endl;
		cout << setw(25) << exp10 + " " << setw(10) << a10 << endl;
		cout << setw(25) << exp11 + " " << setw(10) << a11 << endl;



	}catch(const invalid_argument& ia)
	{
		cerr << "Invalid argument: " << ia.what() << '\n';
	}

	cout << endl;
	std::system("pause");
	return 0;
}

//increment formats 
//		ACCEPTABLE									ERRORS
// 											1++2 = ERROR Not enough +
// 1+++2 = 4								+2  =  '                '
// ++2 = 3									++  =  Error expected a digit
// 4-++2 = 1								+++2 = Error operand stack is empty, not enough digits
// 1+++++2 = 5
