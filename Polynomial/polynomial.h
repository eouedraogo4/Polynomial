#ifndef POLYNOMIAL
#define POLYNOMIAL

#include "term.h"

/*------------------LNode------------------*/
typedef struct LNode {
    Term data;
    struct LNode* next;
    LNode(double _coef = 0, int _expn = 0, LNode* _next = NULL) 
        : data(Term(_coef, _expn)), next(_next) {}
    LNode(LNode const& other) {
        data = other.data;
        next = other.next == NULL ? NULL : new LNode(*other.next);
    }
}LNode, * Link;


/*------------------Polynomial------------------*/
class Polynomial {
public:
    // Constructors
    Polynomial(int n = 0);
    Polynomial(Polynomial const& other);

    // Destructor
    ~Polynomial();

    // Push
    static Status Push(Polynomial &P, double coef, int expn);

    //Display
    static Status Display(Polynomial const& P);

    //operations
    static Polynomial Add(Polynomial const& a, Polynomial const& b);      // return a + b
    static Polynomial Sub(Polynomial const& a, Polynomial const& b);      // return a - b
    static Polynomial Mul(Polynomial const& a, Polynomial const& b); // return a * b

    // Sort
    static Status MergeSort(Link& L);                                // Sort a Link List
    static Status FrontBackSplit(Link L, Link& front, Link& back);   // split L LinkList in the middle
    static Link SortedMerge(Link a, Link b);                         // merge two sorted list

    //simplify
    static Status Simplify(Polynomial& P);

    //
    static double Value(Polynomial const& P, double x); // calculate f(x)
    static Polynomial Derivative(Polynomial const& P);  // return f'(x)
    static Polynomial Inverse(Polynomial const& P);     // -f(x)

private:
    Link head, tail;
    int len;

};


Polynomial::Polynomial(int n) : head(new LNode()), tail(NULL), len(0) {
    if (n > 0)
        std::cout << "Enter terms ( coef exp )\n";
    while (n-- > 0) {
        double coef; int expn;
        std::cin >> coef >> expn;
        Push(*this, coef, expn);
    }
    Simplify(*this);
}

Polynomial::Polynomial(Polynomial const& other) {
    head = new LNode(*other.head);
    tail = head->next;
    len = other.len;
}

Polynomial::~Polynomial() {
    while (head) {
        tail = head;
        head = head->next;
        delete tail;
    }
}

Status Polynomial::Push(Polynomial& P, double coef, int exp) {
    Link L = new LNode(coef, exp);
    L->next = P.tail;
    P.head->next = L;
    P.tail = L;
    P.len++;
    return OK;
}

Status Polynomial::Display(Polynomial const& P) {
    Polynomial tmp(P);
    Simplify(tmp);    
    if (!tmp.head || !tmp.tail) {
        std::cout << "0";
        return OK;
    }
    Term::Display(tmp.tail->data); //first term
    while (tmp.tail->next != NULL) {
        if (tmp.tail->next->data.coef > 0)
            std::cout << '+';
        Term::Display(tmp.tail->next->data);
        tmp.tail = tmp.tail->next;
    }
    return OK;
}

Polynomial Polynomial::Add(Polynomial const& a, Polynomial const& b) {
    Polynomial* ia = new Polynomial(a), * ib = new Polynomial(b), * res = new  Polynomial();
    //merge
    MergeSort(ia->tail); MergeSort(ib->tail);
    res->tail = SortedMerge(ia->tail, ib->tail);
    res->head->next = res->tail;
    res->len = ia->len + ib->len;
    //simplify
    Simplify(*res);
    return *res;
}

Polynomial Polynomial::Sub(Polynomial const& a, Polynomial const& b) {
    return Add(a, Inverse(b));
}

Polynomial Polynomial::Mul(Polynomial const& a, Polynomial const& b) {
    Polynomial* res = new Polynomial();
    Link ia = a.tail, ib = b.tail;
    for (Link ia = a.tail; ia != NULL; ia = ia->next)
        for (Link ib = b.tail; ib != NULL; ib = ib->next)
            Push(*res, ia->data.coef * ib->data.coef, ia->data.expn + ib->data.expn);
    Simplify(*res);
    return *res;
}


Status Polynomial::MergeSort(Link& L) {
    Link head = L;
    // basic conditons: 0 ou 1 element
    if (head == NULL || head->next == NULL)
        return OK;

    // split List
    Link front, back;
    FrontBackSplit(head, front, back);

    // Sort the two halve parts recursively
    MergeSort(front);
    MergeSort(back);

    // merge the sorted parts
    L = SortedMerge(front, back);
    return OK;
}

Status Polynomial::FrontBackSplit(Link L, Link& front, Link& back) {
    Link slow = L;
    Link fast = slow->next;

    // when fast will be a the end of the list slow will be at the middle
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    // spliting
    front = L;
    back = slow->next;
    slow->next = NULL;
    return OK;
}

Link Polynomial::SortedMerge(Link a, Link b) {
    Link L = NULL;
    // basic conditions
    if (a == NULL)
        return b;
    else if (b == NULL)
        return a;

    // compare and sort recursively
    if (a->data.expn < b->data.expn) {
        L = a;
        L->next = SortedMerge(a->next, b);
    }
    else {
        L = b;
        L->next = SortedMerge(a, b->next);
    }
    return L;
}

Status Polynomial::Simplify(Polynomial& P) {
    if (!P.head || !P.tail) return OK;

    // sorting list
    MergeSort(P.tail);
    P.head->next = P.tail;

    //simplify
    Link p = P.head;
    while (p->next != NULL) {
        if (p->next->data.coef == 0) {
            Link tmp = p->next;
            p->next = p->next->next;
            delete tmp;
            P.len--;
        }
        else if (p->next->next != NULL && p->next->data.expn == p->next->next->data.expn) {
            p->next->next->data.coef += p->next->data.coef;
            p->next->data.coef = 0;
        }
        else {
            p = p->next;
        }
    }
    P.tail = P.head->next;
    return OK;
}

double Polynomial::Value(Polynomial const& P, double x) {
    double result = 0;
    Link p = P.tail;
    while (p != NULL) {
        result += p->data.coef * std::pow(x, p->data.expn);
        p = p->next;
    }
    return result;
}

Polynomial Polynomial::Derivative(Polynomial const& P) {
    Polynomial result(P);
    while (result.tail != NULL) {
        result.tail->data.coef *= result.tail->data.expn;
        result.tail->data.expn--;
        result.tail = result.tail->next;
    }
    result.tail = result.head->next;
    return result;
}

Polynomial Polynomial::Inverse(Polynomial const& P) {
    Polynomial* res = new Polynomial(P);
    while (res->tail != NULL) {
        res->tail->data.coef *= -1;
        res->tail = res->tail->next;
    }
    res->tail = res->head->next;
    return *res;
}

#endif // !POLYNOMIAL