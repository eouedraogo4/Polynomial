#ifndef POLYLIST
#define POLYLIST

#include "polynomial.h"

/*------------------PNode------------------*/
typedef struct PNode {
    Polynomial data;
    struct PNode* next;
    PNode(int n = 0, PNode* _next = NULL) : data(n), next(_next) {}
    PNode(Polynomial _data, PNode* _next = NULL) :data(_data), next(_next) {}
    PNode(PNode const& other) {
        data = other.data;
        next = other.next == NULL ? NULL : new PNode(*other.next);
    }
}PNode, * Function;
/*------------------PolyList------------------*/
class PolyList {
public:
    // Constructors
    PolyList() : head(new PNode()), tail(NULL), len(0) {}
    PolyList(PolyList const& other);

    // Destructor
    ~PolyList();

	// Push(Create)
    static Status Push(PolyList& PL, int n);

    //Delete
    static Status Delete(PolyList& PL, int i, Polynomial& p);

    //get
    static Function& GetFunction(PolyList const& PL, int pos);

    //Display
    static Status Display(PolyList const& PL, int i);
    static Status DisplayAll(PolyList const& PL);

private:
    Function head, tail;
    int len;
};

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

Status PolyList::Delete(PolyList& PL, int pos, Polynomial& p) {
    if (pos <= 0 || pos > PL.len) return ERROR;
    Function f = GetFunction(PL, pos - 1);
    Function tmp = f->next;
    f->next = f->next->next;
    p = *new Polynomial(tmp->data);
    delete tmp;
    PL.tail = PL.head->next;
    PL.len--;
    return OK;
}

#endif // !POLYLIST