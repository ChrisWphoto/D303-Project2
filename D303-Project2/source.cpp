#include <iostream>
#include <string>
#include "evaluator.h"

using namespace std;

int main()
{
	int answer;
	evaluator l("3+4*5/4-3");
	answer = l.exp_evaluator("4/2+5*7*5-4");


	cout << "+: " << l.Precedence('+') << endl <<
		"-: " << l.Precedence('-') <<endl <<
		"*: " << l.Precedence('*') <<endl <<
		"/: " << l.Precedence('/');
	return 0;
}