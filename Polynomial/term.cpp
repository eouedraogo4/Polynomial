#include "term.h"

Term::Term() : _coef(0), _expn(0) {}

Term::Term(double coef, int expn) :_coef(coef), _expn(expn) {}

Term::Term(Term const& other) : _coef(other.coef()), _expn(other.expn()) {}

Status Term::Display(std::ostream& out) const {
    // print coef
    if (_coef == 0)
        return OK;
    else if (_coef > 0) {
        if (_coef != 1 || _expn == 0)
            out << _coef;
    }
    else if (_coef < 0) {
        if (_coef == -1 && _expn != 0)
            out << '-';
        else
            out << _coef;
    }
    //print expn
    if (_coef != 0) {
        switch (_expn)
        {
        case 0:
            break;
        case 1:
            out << 'x';
            break;
        default:
            out << "x^" << _expn;
            break;
        }
    }
    return OK;
}

double Term::value(int x) const {
    return _coef*std::pow(x,_expn);
}

Term Term::Derivative() const {
    return Term(coef() * expn(), expn() - 1);
}

Term& Term::operator=(Term const& other) {
    _coef = other.coef();
    _expn = other.expn();
    return *this;
}

Term& Term::operator*=(Term const& other) {
    _coef *= other.coef();
    _expn += other.expn();
    return *this;
}

std::ostream& operator<<(std::ostream& out, Term const& t) {
    t.Display(out);
    return out;
}

Term operator-(Term const& t) {
    return Term(-t.coef(), t.expn());
}

Term operator*(Term const& a, Term const& b) {
    Term result(a);
    result *= b;
    return result;
}