#ifndef TERM
#define TERM

#include <iostream>
#include <cstdlib>
#include <cmath>

typedef int Status;

#define TRUE        1
#define FALSE       0
#define OK          1
#define ERROR       0
#define INFEASIBLE -1
#define OVERFLOW   -2

typedef struct Term {
    double coef;
    int expn;
    Term(double _coef = 0, int _expn = 0) :coef(_coef), expn(_expn) {}
    static Status Display(Term const& t);
} Term;

Status Term::Display(Term const& t) {
    // print coef
    if (t.coef == 0)
        return OK;
    else if (t.coef > 0) {
        if (t.coef != 1 || t.expn == 0)
            std::cout << t.coef;
    }
    else if (t.coef < 0) {
        if (t.coef == -1 && t.expn != 0)
            std::cout << '-';
        else
            std::cout << t.coef;
    }
    //print expn
    if (t.coef != 0) {
        switch (t.expn)
        {
        case 0:
            break;
        case 1:
            std::cout << 'x';
            break;
        default:
            std::cout << "x^" << t.expn;
            break;
        }
    }
    return OK;
}

#endif // !TERM