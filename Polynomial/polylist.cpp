#include "polylist.h"

// Constructors
PolyList::PolyList(PolyList const& other) {
    head = new PNode(*other.head);
    tail = head->next;
    len = other.len;
}

// Destructor
PolyList::~PolyList() {
    while (head) {
        tail = head;
        head = head->next;
        delete tail;
    }
}

Status PolyList::Push(PolyList& PL, int n) {
    Function f = new PNode(n);
    f->next = PL.tail;
    PL.head->next = f;
    PL.tail = f;
    PL.len++;
    return OK;
}

Function& PolyList::GetFunction(PolyList const& PL, int pos) {
    int i = 0;
    Function f = PL.head;
    while (i++ < pos && f->next != NULL)
        f = f->next;
    return f;
}

Status PolyList::Display(PolyList const& PL, int i) {
    if (i <= 0 || i > PL.len) return ERROR;
    Polynomial::Display(GetFunction(PL, i)->data);
    return OK;
}

Status PolyList::DisplayAll(PolyList const& PL) {
    Function f = PL.tail;
    int i = 1;
    while (f != NULL) {
        std::cout << "f" << i++ << "(x) = "; Polynomial::Display(f->data); std::cout << '\n';
        f = f->next;
    }
    return OK;
}

Function PolyList::Add(Function const& f, Function const& g) {
    Function res = new PNode();
    res->data = Polynomial::Add(f->data, g->data);
    return res;
}

Function PolyList::Sub(Function const& f, Function const& g) {
    Function res = new PNode();
    res->data = Polynomial::Sub(f->data, g->data);
    return res;
}

Function PolyList::Mul(Function const& f, Function const& g) {
    Function res = new PNode();
    res->data = Polynomial::Mul(f->data, g->data);
    return res;
}

Status PolyList::Delete(PolyList& PL, int pos, Polynomial& p) {
    if (pos <= 0 || pos > PL.len) return ERROR;
    Function f = GetFunction(PL, pos - 1);
    Function tmp = f->next;
    f = f->next->next;
    p = tmp->data;
    delete tmp;
    PL.tail = PL.head->next;
    PL.len--;
    return OK;
}

double PolyList::Calculate(PolyList const& PL, int i, int x, Function& f) {
    if (i <= 0 || i > PL.len) return 0;
    f = GetFunction(PL, i);
    return Polynomial::Image(f->data,x);
}

Function PolyList::Derivative(PolyList const& PL, int i, Function& f) {
    if (i <= 0 || i > PL.len) return ERROR;
    f = GetFunction(PL, i);
    return new PNode(Polynomial::Derivative(f->data));
}