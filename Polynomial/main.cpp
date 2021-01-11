#include "polylist.h"

using namespace std;

Status Menu() {
	cout <<
		"**********OPERATIONS**********\n"
		"*****1.    menu          *****\n"
		"*****2.    create        *****\n"
		"*****3.    display       *****\n"
		"*****4.    display all   *****\n"
		"*****5.    add           *****\n"
		"*****6.    sub           *****\n"
		"*****7.    delete        *****\n"
		"*****8.    mul           *****\n"
		"*****9.    calculate     *****\n"
		"*****10.   derivative    *****\n"
		"**********OPERATIONS**********\n"
		;
	return OK;
}

void main() {
	PolyList PL;
	Function f = new PNode(), g = new PNode();
	int choice = 1, i, j, x;

	while (true) {
		switch (choice)
		{
		case 1: // Menu
			Menu();
			break;
		case 2: //Create
			cout << "Create\nNumber of terms : ";
			cin >> i;
			PolyList::Push(PL,i);
			break;
		case 3: //Display
			cout << "Display\nEnter function number : ";
			cin >> i;
			PolyList::Display(PL,i);
			break;
		case 4: //Display All
			cout << "DisplayAll\n";
			PolyList::DisplayAll(PL);
			break;
		case 5: //Add
			cout << "Add\nEnter functions (ex: 1 2)\n";
			cin >> i >> j;
			f = PolyList::GetFunction(PL, i); g = PolyList::GetFunction(PL, j);
			cout << "("; Polynomial::Display(f->data); 
			cout << ")+("; Polynomial::Display(g->data); 
			cout << ") = "; Polynomial::Display(Polynomial::Add(f->data, g->data)); cout << '\n';
			break;
		case 6: //Sub
			cout << "Sub\nEnter functions (ex: 1 2)\n";
			cin >> i >> j;
			f = PolyList::GetFunction(PL, i); g = PolyList::GetFunction(PL, j);
			cout << "("; Polynomial::Display(f->data);
			cout << ")-("; Polynomial::Display(g->data);
			cout << ") = "; Polynomial::Display(Polynomial::Sub(f->data, g->data)); cout << '\n';
			break;
		case 7: // Delete
			cout << "Delete\nEnter the functions to delete : ";
			cin >> i;
			if (PolyList::Delete(PL, i, f->data) == OK) {
				cout << "f(x) = "; Polynomial::Display(f->data); cout << "    Delete Successfully\n";
			}
			else
				cout << "Not found\n";
			break;
		case 8: //Mul
			cout << "Mul\nEnter functions (ex: 1 2)\n";
			cin >> i >> j;
			f = PolyList::GetFunction(PL, i); g = PolyList::GetFunction(PL, j);
			cout << "("; Polynomial::Display(f->data);
			cout << ")*("; Polynomial::Display(g->data);
			cout << ") = "; Polynomial::Display(Polynomial::Mul(f->data, g->data)); cout << '\n';
			break;
		case 9: //Calculate
			cout << "Calculate\nEnter function number then x (ex 1 0)\n";
			cin >> i >> x;
			f = PolyList::GetFunction(PL, i);
			cout << "f(x) = "; Polynomial::Display(f->data);
			cout << "\nf(" << x << ") = " << Polynomial::Value(f->data, x) << '\n';
			break;
		case 10: //Derivative
			cout << "Derivative\nEnter function number : \n";
			cin >> i;
			f = PolyList::GetFunction(PL, i);
			cout << "f(x) = "; Polynomial::Display(f->data); 
			cout << "\nf'(x) = "; Polynomial::Display(Polynomial::Derivative(f->data)); cout << '\n';
			break;
		default:
			break;
		}

		if (choice != 1)
			cout << "\nreturn Menu ( 1 )\n";
		cin >> choice;
	}
}