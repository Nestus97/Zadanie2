#include <iostream>
#include <vector>
#include "class.h"

using namespace std;

List::List(string n)
{
    name=n;
    firstElement=NULL;
    lastElement=NULL;
    howMany=0;
}

List::~List()
{

}

string List::getName()
{
    return name;
}

int List::listSize()
{
    return howMany;
}

Element* List::takeFirstElement()
{
    return firstElement;
}

Element* List::takeLastElement()
{
    return lastElement;
}

Element::Element(int id, int val)
{
    index=id;
    value=val;
    next=NULL;
    prev=NULL;
}

void Element::changePrev(Element* p)
{
    prev=p;
}

void Element::changeNext(Element* n)
{
    next=n;
}

void Element::idUp()
{
    index++;
    if(next!=NULL)
    {
        next->idUp();
    }
}

void Element::idDown()
{
    index--;
    if(next!=NULL)
    {
        next->idDown();
    }
}

Element* List::findId(int id)
{
    Element* tmp = firstElement;
    while(tmp!=NULL && tmp->index!=id)
    {
        tmp=tmp->next;
    }
    if(tmp==NULL)
    {
        return NULL;
    }
    return tmp;
}

void Element::insertThere(Element* el)
{
    if(prev!=NULL)
    {
        prev->changeNext(el);
    }
    el->changeNext(this);
    el->changePrev(prev);
    changePrev(el);
    idUp();
}

void List::addElem(int id, int val)
{
    if(id>howMany || id<0)
    {
        return;
    }
    Element* el = new Element(id, val);
    if(id==0)
    {
        if(firstElement!=NULL)
        {
            firstElement->idUp();
            firstElement->changePrev(el);
        }
        else
        {
            lastElement=el;
        }
        el->changeNext(firstElement);
        firstElement=el;
    }
    else if(id!=howMany)
    {
        Element* tmp = findId(id);
        tmp->insertThere(el);
    }
    else
    {
        Element* tmp = lastElement;
        tmp->changeNext(el);
        el->changePrev(tmp);
        lastElement=el;
    }
    howMany++;
}

void List::deleteId(int id)
{
    if(id>=howMany) return;
    Element* el = findId(id);
    if(id==0)
    {
        firstElement=firstElement->next;
    }
    if(id==howMany-1)
    {
        lastElement=lastElement->prev;
    }
    el->popIt();
    delete(el);
    howMany--;
}
void Element::popIt()
{
    idDown();
    if(prev!=NULL)
    {
        prev->changeNext(next);
    }
    if(next!=NULL)
    {
        next->changePrev(prev);
    }
}

int Element::takeValue()
{
    return value;
}

int Element::takeId()
{
    return index;
}

void List::deleteValue(int val)
{
    if(firstElement==NULL) return;
    int value;
    int id;
    Element* el = firstElement;
    Element* tmp;
    while(el!=NULL)
    {
        id = el->takeId();
        value = el->takeValue();
        tmp=el->takeNext();
        if(value==val)
        {
            if(id==0)
            {
                firstElement=firstElement->next;
            }
            if(id==howMany-1)
            {
                lastElement=lastElement->prev;
            }
            el->popIt();
            delete(el);
            howMany--;
        }
        el=tmp;
    }
}

void List::deleteRange(int minVal, int maxVal)
{
    if(firstElement==NULL) return;
    int value;
    int id;
    Element* el = firstElement;
    Element*tmp;
    while(el!=NULL)
    {
        id = el->takeId();
        value = el->takeValue();
        tmp=el->takeNext();
        if((value>=minVal)&&(value<=maxVal))
        {
            if(id==0)
            {
                firstElement=firstElement->next;
            }
            if(id==howMany-1)
            {
                lastElement=lastElement->prev;
            }
            el->popIt();
            delete(el);
            howMany--;
        }
        el=tmp;
    }
}

void List::deleteRepeated()
{
    if(firstElement==NULL) return;
    int val1, val2;
    int id;
    Element* el1 = firstElement;
    Element* el2;
    Element* tmp;
    while(el1!=NULL)
    {
        val1 = el1->takeValue();
        el2 = el1->takeNext();
        while(el2!=NULL)
        {
            tmp=el2->takeNext();
            val2 = el2->takeValue();
            id = el2->takeId();
            if(val2==val1)
            {
                if(id==howMany-1)
                {
                    lastElement=lastElement->prev;
                }
                el2->popIt();
                delete(el2);
                howMany--;
            }
            el2=tmp;
        }
        el1=el1->takeNext();
    }
}

Element::~Element()
{

}

Element* Element::takeNext()
{
    return next;
}

Element* Element::takePrev()
{
    return prev;
}

void showElem(Element* el)
{
    if(el==NULL) return;
    cout<<el->index<<". "<<el->value<<endl;
}

void showAllLists(vector<List> &all)
{
    cout<<"Listy, ktore stworzyles:"<<endl;
    for(int i=0; i<(int)all.size(); i++)
    {
        cout<<i<<". "<< all[i].getName()<<endl;
    }
}

bool operator==(List first, List second)
{
    if(first.howMany!=second.howMany) return false; //jesli maja rozne rozmiary to wiadomo, ze nie sa rowne
    Element* el1 = first.firstElement;  // tu i nizej zaczynamy przegladac listy od pierwszego elementu
    Element* el2 = second.firstElement; // jak linijke wyzej
    int val1, val2;

    while(el1!=NULL)
    {
        val1 = el1->takeValue();
        val2 = el2->takeValue();
        if(val1!=val2) return false;
        el1 = el1->takeNext();
        el2 = el2->takeNext();
    }
    return true;
}

void List::changeFirstElement(Element* first)
{
    firstElement=first;
}

void List::changeLastElement(Element* last)
{
    lastElement=last;
}

void List::nullFirstLast()
{
    firstElement=NULL;
    lastElement=NULL;
}

void operator+(List &first, List &second) // pierwsza jest dluzsza o dlugosc drugiej, druga jest pusta
{
    int listSize = first.listSize();
    Element* one;
    Element* two;
    two=second.takeFirstElement();
    for(int i=0;i<listSize;i++)
    {
        two->idUp();
    }
    int aSize = second.listSize();
    one=first.takeLastElement();
    two=second.takeFirstElement();
    one->changeNext(two);
    two=second.takeLastElement();
    first.changeLastElement(two);
    first.addHowMany(aSize);
    second.nullFirstLast();

    second.zeroHowMany();
}

void operator-(List &first, List &second)
{
    Element* two;
    int val;
    two=second.takeFirstElement();
    while(two!=NULL)
    {
        val=two->takeValue();
        first.deleteValue(val);
        two=two->takeNext();
    }
}

Element* List::operator[](int id)
{
    return findId(id);
}

void List::operator=(List ls)
{
    Element* el = ls.firstElement;
    while(el!=NULL)
    {
        addElem(el->index, el->value);
        el=el->next;
    }

}
ostream& operator<<(ostream& out, List* some)
{
out << some->getName() <<endl;
return out;
}

void List::zeroHowMany()
{
    howMany=0;
}

void List::addHowMany(int i)
{
    howMany=howMany+i;
}
