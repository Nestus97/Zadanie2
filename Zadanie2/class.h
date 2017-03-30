#ifndef CLASSH
#define CLASSH

#include <iostream>

using namespace std;

class Element;

class List
{
    string name;
    Element* firstElement; //wskazanie na pierwszy element listy
    Element* lastElement; //wskazanie na ostatni element listy
    int howMany; //ilosc elementow
public:
    List(string n="NieNadano"); //konstruktor
    ~List(); // destruktor
    friend class Element; //zaprzyjaznione z klasa Element
    string getName(); //zwraca nazwe listy
    Element* takeFirstElement(); //zwraca pierwszy element listy
    Element* takeLastElement(); //zwraca ostatni element listy
    int listSize(); //zwraca dlugosc listy
    void addElem(int id, int val); //dodanie elementu na konkretne miejsce
    void deleteValue(int val); //usuwanie konkretnej wartosci
    void deleteRange(int minVal, int maxVal); //usuwanie elementow o danym zakresie wartosci
    void deleteId(int id); //usuwa element o konkretnym id
    void deleteRepeated(); //usuwa powtarzajace sie wartosci
    Element* findId(int id); // znajduje element o okreslonym id
    void changeFirstElement(Element* first=NULL); //zmienia pierwszy Element
    void changeLastElement(Element* last=NULL); //zmienia ostatni Element
    friend void showAllLists(vector<List> &all);//pokazuje listy
    void nullFirstLast();
    void zeroHowMany();
    void addHowMany(int i);
    void operator=(List ls);
    Element* operator[](int id);
    friend ostream& operator<<(ostream& out, List* some);
    friend bool operator==(List first, List second);
    friend void operator+(List &first, List &second); //ZAKLADA, ZE OBIE LISTY NIE SA ZEROWE!!!
    friend void operator-(List &first, List &second);
};

class Element
{
    int index;
    int value;
    Element* next;
    Element* prev;
public:
    //Element(Element* toCopy); //ten konstruktor do kopiowania
    Element(int id=0, int val=0); //ten konstruktor do dodawania
    ~Element(); // destruktor
    friend class List;//zaprzyjaznione z klasa List
    Element* takeNext(); //
    Element* takePrev(); //
    int takeValue(); // zwraca wartosc Elementu
    int takeId(); // zwraca indeks Elementu
    void idUp();//zwieksza id wszystkich kolejnych elementow
    void idDown();//zmiejsza id wszystkich kolejnych elementow
    void changePrev(Element* p);//zmienia poprzedniego
    void changeNext(Element* n);//zmienia nastepnego
    void insertThere(Element* el);//wstawia element "w to miejsce"
    void popIt(); //wywolane przez delete - usuwa konkretny element
    friend void showElem(Element* el);//pokazuje element
    friend void showList(List* some);//pokazuje cala wybrana liste (wszystkie elementy)

    friend bool operator==(List first, List second); // porownuje listy - rowne jak kazdy element rowny i tyle samo ich
    friend void operator+(List &first, List &second); //ZAKLADA, ZE OBIE LISTY NIE SA ZEROWE!!!!!!!!!!!!!!!!
    friend void operator-(List &first, List &second);
};
#endif
