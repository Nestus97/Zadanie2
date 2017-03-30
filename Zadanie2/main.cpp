#include <iostream>
#include <vector>
#include <cstdlib>
#include "class.h"

using namespace std;

void listMenu(vector<List> &all);
void elementMenu(vector<List> &all, List* some);

void showList(List* some)
{
    Element* el = some->takeFirstElement();
    while(el!=NULL)
    {
        showElem(el);
        el=el->next;
    }
}

void mainMenu(vector<List> &all)
{
    string name;
    int decision;
    while(true)
    {
        cout<<endl;
        cout<<"_________________________________________________"<<endl;
        cout<<"|Co Chcialbys zrobic? Wpisz i zatwierdz:         |"<<endl;
        cout<<"| 1 - by dodac nowa liste                        |"<<endl;
        cout<<"| 2 - by zobaczyc spis list i dodatkowe opcje    |"<<endl;
        cout<<"| 0 - by zakonczyc program                       |"<<endl;
        cout<<"|________________________________________________|"<<endl;
        cin>>decision;
        switch(decision)
        {
        case 1:
            cout<<"Podaj nazwe listy, ktora chcesz stworzyc: ";
            cin>>name;
            all.push_back(*new List(name));
        break;
        case 2:
            showAllLists(all);
            listMenu(all);
            break;
        case 0:
            exit(0);
        break;
        default:
            cout<<"Wprowadziles nieistniejace polecenie - sprobuj ponownie!";
        break;
        }
    }
}

void listMenu(vector<List> &all)
{
    int decision;
    int listSize;
    int id1, id2;
    string name;
    while(true)
    {
        cout<<"_________________________________________________"<<endl;
        cout<<"| Co chcesz zrobic z listami?:                   |"<<endl;
        cout<<"| 1 - by wybrac liste i zarzadzac jej elementami |"<<endl;
        cout<<"| 2 - by dodac dwie listy                        |"<<endl;
        cout<<"| 3 - by odjac dwie listy                        |"<<endl;
        cout<<"| 4 - by porownac dwie listy                     |"<<endl;
        cout<<"| 0 - by wrocic do Menu Glownego                 |"<<endl;
        cout<<"|________________________________________________|"<<endl;
        cout<<"Co chcialbys zrobic: "<<endl;
        cin>>decision;
        showAllLists(all);
        switch(decision)
        {
        case 1:
            cout<<"Ktora lista Ciebie interesuje?: ";
            cin>>decision;
            elementMenu(all, &all[decision]);
        break;
        case 2:
            cout<<"Podaj id jednej listy: ";
            cin>>id1;
            cout<<"Podaj id drugiej listy: ";
            cin>>id2;
            all[id1]+all[id2];
        break;
        case 3:
            cout<<"Podaj id jednej listy: ";
            cin>>id1;
            cout<<"Podaj id drugiej listy: ";
            cin>>id2;
            all[id1]-all[id2];
        break;
        case 4:
            cout<<"Podaj id jednej listy: ";
            cin>>id1;
            cout<<"Podaj id drugiej listy: ";
            cin>>id2;
            if(all[id1]==all[id2]) cout<<"Te listy sa rowne!"<<endl;
            else cout<<"Te listy NIE sa rowne!"<<endl;
        break;
        case 0:
            mainMenu(all);
        break;
        default:
            cout<<"Wprowadziles nieistniejace polecenie - sprobuj ponownie!";
        break;
        }
    }

}

void elementMenu(vector<List> &all, List* some)
{
    int decision;
    int value;
    int id;
    int mini;
    int maxi;
    cout<<"Oto cala lista:"<<endl;
    showList(some);

    while(true)
    {
        cout<<"______________________________________________"<<endl;
        cout<<"| Co chcesz z nia zrobic?:                    |"<<endl;
        cout<<"| 1 - dodac element na poczatek               |"<<endl;
        cout<<"| 2 - dodac element po indeksie (w srodek)    |"<<endl;
        cout<<"| 3 - usunac element o okreslonym indeksie    |"<<endl;
        cout<<"| 4 - usunac element o okreslonej wartosci    |"<<endl;
        cout<<"| 5 - usunac zakres wartosci                  |"<<endl;
        cout<<"| 6 - usunac elementy powtarzajace sie        |"<<endl;
        cout<<"| 7 - sprawdz wielkosc listy                  |"<<endl;
        cout<<"| 8 - pobierz element z listy []              |"<<endl;
        cout<<"| 9 - przypomnij w jakiej jestem liscie       |"<<endl;
        cout<<"| 0 - wrocic do wyboru list                   |"<<endl;
        cout<<"|_____________________________________________|"<<endl;
        showList(some);
        cout<<"Co chcialbys zrobic?: ";
        cin>>decision;
        switch(decision)
        {
        case 1:
            cout<<"Podaj wartosc: ";
            cin>>value;
            some->addElem(0,value);
            showList(some);
        break;
        case 2:
            cout<<"Podaj wartosc: ";
            cin>>value;
            cout<<"Podaj indeks: ";
            cin>>id;
            some->addElem(id,value);
        break;
        case 3:
            cout<<"Podaj indeks: ";
            cin>>id;
            some->deleteId(id);
        break;
        case 4:
            cout<<"Podaj wartosc: ";
            cin>>value;
            some->deleteValue(value);
        break;
        case 5:
            cout<<"Podaj przedzial dolny: ";
            cin>>mini;
            cout<<"Podaj przedzial gorny: ";
            cin>>maxi;
            some->deleteRange(mini,maxi);
        break;
        case 6:
            some->deleteRepeated();
        break;
        case 7:
            value=some->listSize();
            cout<<"Wielkosc listy: "<<value<<endl;
        break;
        case 8:
            cout<<"Ktory element (id): ";
            cin>>id;
            Element* el;
            el=(*some)[id];
            value = el->takeValue();
            cout<<"Ten element ma wartosc: "<<value<<endl;
        break;
        case 9:
            cout<<"Jestes w liscie: "<<some;
        break;
        case 0:
            listMenu(all);
        break;
        default:
           cout<<"Wprowadziles nieistniejace polecenie - sprobuj ponownie!";
        break;
        }
    }
}

void tests()
{
    // OPERATOR <<
    string name = "Operator<<SPRAWNY";
    cout<<"TESTY:"<<endl;
    //sprawdzanie przyrownania
    List* some = new List(name);
    cout<<some;
    some->addElem(0,3);
    List* another = new List();
    another->addElem(0,3);
    if(*some==*another) cout<<"Przyrownywanie list SPRAWNE"<<endl;
    else cout<<"Przyrownywanie list ZAWIODLO"<<endl;
    //sprawdzanie kopiowania
    List* lis = some;
    if(*lis==*some) cout<<"Kopiowanie list SPRAWNE"<<endl;
    else cout<<"Kopiowanie list ZAWIODLO"<<endl;
    //sprawdzanie dodawania
    int value;
    Element* el;
    el=some->takeFirstElement();
    value=el->takeValue();
    if(value==3)
    {
        cout<<"Dodawanie elementow do listy SPRAWNE"<<endl;
    }
    else cout <<"Dodawanie elementow do listy ZAWIODLO"<<endl;
    //sprawdzanie usuwania
    some->deleteId(0);
    el=some->takeFirstElement();
    if(el==NULL) cout<<"Usuwanie elementow z listy SPRAWNE"<<endl;
    else cout<<"Usuwanie elementow z listy ZAWIODLO"<<endl;
    //sprawdzanie usuwanie powtarzajacych sie elementow
    for(int i=0; i<5; i++)
    {
        some->addElem(0,3);
    }
    some->deleteRepeated();
    value=some->listSize();
    if(value==1) cout<<"Usuwanie elementow powtarzajacych sie SPRAWNE"<<endl;
    else cout<<"Usuwanie elementow powtarzajacych sie ZAWIODLO"<<endl;
    //wskaznik na ostatni element listy
    some->addElem(1,2);
    el=some->takeLastElement();
    value=el->takeValue();
    if(value==2) cout<<"Przesuwanie wskaznika na ostatni Element SPRAWNE"<<endl;
    else cout<<"Przesuwanie wskaznika na ostatni Element ZAWIODLO"<<endl;
    cout<<"__________________________________________________________"<<endl<<endl;
}

int main()
{
    tests();
    vector<List> all; //stworzenie wektora list o nazwie "all"
    cout<<"Witaj w programie, ktory w jakis tam sposob stara sie obslugiwac listy dwukierunkowe wedlug zadanych wymogow"<<endl;
    mainMenu(all);
    return 0;
}
