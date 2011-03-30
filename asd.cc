/**
@file asd.cc

Plik do modyfikacji w ramach cwiczenia z AISDI.
Zawiera niekompletne implementacje metod klasy ListMap,
oraz mape podobna koncepcyjnie do tej z cwicznia 1 (SmallMap)
zaimplementowana w jescze bardziej szczatkowy sposob.
Jest tez prosta funkcja testujaca (void test()), ktora
jest wolana w funkcji main. Mozna w niej zaimplementowac
wlasne testy.
NALEZY ZMODYFIKOWAC I UZUPELNIC CIALA METOD KLASY LISTMAP.

@author
Pawel Cichocki, Michal Nowacki

@date
last revision
- 2006.01.06 Michal Nowacki: wersja polska
- 2005.11.17 Michal Nowacki: constructor
- 2005.11.04 Pawel Cichocki: copied comments from the header
- 2005.11.03 Pawel Cichocki: const_iterator done properly now
- 2005.10.27 Pawel Cichocki: cosmetic changes
- 2005.10.26 Michal Nowacki: removed some method bodies
- 2005.10.25 Pawel Cichocki: wrote it

COPYRIGHT:
Copyright (c) 2005 Instytut Informatyki, Politechnika Warszawska
ALL RIGHTS RESERVED
*******************************************************************************/

#include <assert.h>
#include <algorithm>

#include <iostream>

#if 0
//def _SUNOS
#include "/home/common/dyd/aisdi/liniowe/ListMap.h"
#else
#include "timer.h"
#include "ListMap.h"
#endif

//////////////////////////////////////////////////////////////////////////////
// ListMap and ListMap::iterator methods
//////////////////////////////////////////////////////////////////////////////

ListMap::ListMap()
{
    //first = NULL;
    first = new Node(std::pair<Key,Val>(-1,"Inactive"));
    first->next = first;
    first->prev = first;
};

ListMap::ListMap( const ListMap& m )
{
    first = new Node(std::pair<ListMap::Key,ListMap::Val>(-1,"Inactive"));
    first->next = first;
    first->prev = first;
    if(!m.empty()) {
        iterator i = m.begin();
        //
        do {
            unsafe_insert(i.node->data);
        } while(++i != m.end());
    }
    ///@todo Zaimplementowaæ metode
};

ListMap::~ListMap() {
    clear();
    delete first;
};

// Wstawienie elementu do mapy.
// @returns Para, której komponent bool jest równy true gdy wstawienie zosta³o
//          dokonane, równy false gdy element identyfikowany przez klucz
//          ju¿ istnia³ w mapie. Iterator ustawiony jest na ten wstawiony
//          lub istniej¹cy ju¿ w mapie element.
std::pair<ListMap::iterator, bool> ListMap::insert(const std::pair<Key, Val>& entry)
{
    ///@todo Uzupe³niæ kod
    iterator i;
    for(i=begin(); i!=end(); ++i)
    {
        if(i->first==entry.first)
            return std::make_pair(i, (bool)false);
    }

    return std::make_pair(unsafe_insert(entry), (bool)false);
}

// Wstawienie elementu do mapy.
// Matoda zak³ada, ¿e w mapie nie wystêpuje element identyfikowany przez key
ListMap::iterator ListMap::unsafe_insert(const std::pair<Key, Val>& entry)
{
    ///@todo Uzupe³niæ kod
    Node *newNode;
    newNode = new Node(entry, first, first->prev);
    first->prev->next = newNode;
    first->prev = newNode;
    return iterator(first->prev);
}

// Zwraca iterator addresuj¹cy element w mapie dla którego klucz jest równy
// szukanemu kluczowi lub element za ostatnim gdy szukanego klucza brak w mapie.
ListMap::iterator ListMap::find(const Key& k)
{
    ///@todo Zaimplementowaæ metod
    iterator i = begin();
    for(; i!=end(); i++) {
        if(i->first == k)
            return i;
    }
    return end();
}

ListMap::const_iterator ListMap::find(const Key& k) const
{
    ///@todo Zaimplementowaæ metode
    iterator i = begin();
    for(; i!=end(); i++) {
        if(i->first == k)
            return i;
    }
    return end();
}

// Udostêpnia wartoœæ powi¹zan¹ z kluczem key. Wstawia element do mapy jeœli
// nie istnia³.
// @returns Referencje do wartoœci powi¹zanej z kluczem.
ListMap::Val& ListMap::operator[](const Key& k)
{
    ///@todo Zaimplementowaæ metode
    iterator i;
    i = find(k);
    return i->second;
}

// Sprawdzenie czy mapa jest pusta.
bool ListMap::empty( ) const
{
    return first->next == first;
}

// Zwraca iloœæ elementów w mapie.
ListMap::size_type ListMap::size( ) const
{
    ///@todo Zaimplementowaæ metode
    //assert(0);
    //return 0;
    //return count;
    int j = 0;
    iterator i = begin();
    while(i++ != end()) {
        j++;
    }
    return j;
}

// Zwraza iloœæ elementów skojarzonych z kluczem key.
ListMap::size_type ListMap::count(const Key& _Key) const
{
    ///@todo Zaimplementowaæ meto
    return find(_Key) != end();  // this is not a multimap
}

// Usuwa element z mapy.
// @returns iterator adresuj¹cy pierwszy element za usuwanym.
ListMap::iterator ListMap::erase(ListMap::iterator i)
{
    ///@todo Zaimplementowaæ metode
    if(i!=end()) {
        i.node->next->prev = i.node->prev;
        i.node->prev->next = i.node->next;
        delete(i.node);
        //i->prev->next = i;
    }
    return end();
}

// Usuwa zakres elementów z mapy.
// Zakres jest zdefiniowany poprzez iteratory first i last
// first jest okreœla pierwszy element do usuniêcia, a last okreœla element
// po ostatnim usuniêtym elemencie.
// @returns iterator adresuj¹cy pierwszy element za usuwanym.
ListMap::iterator ListMap::erase(ListMap::iterator f, ListMap::iterator l)
{
    ///@todo Zaimplementowaæ metode
	//test2
	//test3
	iterator i=f;
	for(;i!=l;i++)
		erase(i);
    return i;
}

// Usuwa element z mapy.
// @returns Iloœæ usuniêtych elementów.
//          (nie jest to multimapa, wiêæ mo¿e byæ to wartoœæ 1 lub 0 )
ListMap::size_type ListMap::erase(const Key& key)
{
    ///@todo Zaimplementowaæ metod
    iterator i = find(key);
    if(i == end()) return 0;
    erase(i);
    return 1;
}

// Usuniêcie wszystkich elementów z mapy.
void ListMap::clear( )
{
    ///@todo Zaimplementowaæ meto
    if(first->next == first) {
        return;
    }

    iterator i = begin();

    do {
        erase(i++);
    } while(i!=end());

    return;
}

// Porównanie strukturalne map.
// Czy reprezentacja danych jest identyczna.
// Zwraca true jeœli wewnêtrzne struktury map s¹ identyczne.
bool ListMap::struct_eq(const ListMap& another) const
{
    ///@todo Zaimplementowaæ metode
    if(size() != another.size())
        return false;
    iterator i = begin(),j = another.begin();
    for(; i != end(); ++i,++j) {
        if(i.node->data.first != j.node->data.first) {
            return false;
        }
    }
    return true;
}

// Porównanie informacyjne map.
// Czy informacje trzymane w mapach s¹ identyczne.
// Zwraca true jeœli mapy zwieraj¹ takie same pary klucz-wartoœæ.
bool ListMap::info_eq(const ListMap& another) const
{
    ///@todo Zaimplementowaæ metode
    if(size() != another.size())
        return false;
    iterator i = begin();
    iterator j;
    for(; i!=end(); i++) {
        j = another.find((*i).first);
        if(j == another.end() || (*j).second != (*i).second) {
            return false;
        }
    }
    return true;
}


// preincrementacja
ListMap::const_iterator& ListMap::const_iterator::operator++()
{
    ///@todo Zaimplementowaæ metode
    node = node->next;
    return *this;
}

// postincrementacja
ListMap::const_iterator ListMap::const_iterator::operator++(int)
{
    ///@todo Zaimplementowaæ metode
    const_iterator tmp = *this;
    node = node->next;
    return tmp;
}

ListMap::const_iterator& ListMap::const_iterator::operator--()
{
    ///@todo Zaimplementowaæ metod
    node = node->prev;
    return *this;
}

// postincrementacja
ListMap::const_iterator ListMap::const_iterator::operator--(int)
{
    ///@todo Zaimplementowaæ metode
    const_iterator tmp = *this;
    node = node->prev;
    return tmp;
}

/// Zwraca iterator addresuj¹cy pierwszy element w mapie.
ListMap::iterator ListMap::begin()
{
    ///@todo Zaimplementowaæ metode
    return iterator(first->next);
}

/// Zwraca iterator addresuj¹cy pierwszy element w mapie.
ListMap::const_iterator ListMap::begin() const
{
    ///@todo Zaimplementowaæ metode
    return iterator(first->next);
}

/// Zwraca iterator addresuj¹cy element za ostatnim w mapie.
ListMap::iterator ListMap::end()
{
    ///@todo Zaimplementowaæ metode
    return iterator(first);
}

/// Zwraca iterator addresuj¹cy element za ostatnim w mapie.
ListMap::const_iterator ListMap::end() const
{
    ///@todo Zaimplementowaæ metode
    return iterator(first);
}

//////////////////////////////////////////////////////////////////////////////
// SmallMap
//////////////////////////////////////////////////////////////////////////////

/// Przyk³ad map'y z implementacj¹ podobn¹ do std::map.
/// To jest jedynie przyk³ad!!!
/// Normalnie implementacja powinna opieraæ siê o drzewo lub tablicê haszuj¹c¹.
template <class Key, class Val>
class SmallMap
{
    std::pair<Key, Val> tab[2];
    int isOcupied[2];
public:

    SmallMap()
    {
        for(unsigned i=0; i<2; ++i)
        {
            isOcupied[i]=0;
        }
    }

    typedef std::pair<Key, Val>* iterator;   ///< Ka¿dy wskaŸnik jest te¿ iteratorem.

    iterator begin() {
        return tab;
    }
    iterator end() {
        return tab+2;
    }

    Val& operator[](const Key& k)
    {
        static Val val;
        for(unsigned i=0; i<2; ++i)
        {
            if(isOcupied[i]&&tab[i].first==k)
                return tab[i].second;
        }
        // create
        for(unsigned i=0; i<2; ++i)
        {
            if(!isOcupied[i])
            {
                tab[i].first=k;
                isOcupied[i]=1;
                return tab[i].second;
            }
        }
        //std::cout<<"Out of space! You should not put more than two Key-Value pairs into the SmallMap.\n";
        std::cerr<<"Out of space! You should not put more than two Key-Value pairs into the SmallMap.\n";
        //assert(0);
        return val;   // Ma³o sensowne, ale to jest tylko przyk³¹d
    }
};


//////////////////////////////////////////////////////////////////////////////
// Testy
//////////////////////////////////////////////////////////////////////////////

/// Funckcja pomocnicza do wypisania elementów.
void print(const std::pair<int, std::string>& p)
{
    std::cout<<p.first<<", "<<p.second<<std::endl;
}

#include <map>

/// Testy u¿ytkownika
void _test()
{
    // A typedef used by the test.
    typedef std::map<int, std::string> TEST_MAP;
    //typedef SmallMap<int, std::string> TEST_MAP;
    //typedef ListMap TEST_MAP;

    std::cout << "Testy uzytkownika" << std::endl;

    TEST_MAP m;
    ListMap l;
    m[2] = "Merry";
    m[4] = "Jane";
    m[8] = "Korwin";
    m[4] = "Magdalena";
    m == m;
    for_each(m.begin(), m.end(), print );
    //system("PAUSE");
}

//////////////////////////////////////////////////////////////////////////////
// main - jest w pliku /home/common/dyd/aisdi/z2/main.cc
//////////////////////////////////////////////////////////////////////////////

//int main()
//{
//   std::cout << "AISDI cwiczenie 2: wchodze do funkcji main." << std::endl;
//   test();
//   // Biblioteka z bardziej rygorystyczna wersja tych testow bedzie udostepniona na nastepnych zajeciach.
//   Test2();
//   //system("PAUSE");
//   return EXIT_SUCCESS;
//}


void test1()
{
    typedef ListMap TEST_MAP;
    std::cout << "Testy uzytkownika" << std::endl;
    TEST_MAP jedynka, dwojka, trojka;
	struct timeval timeV;
	struct 	timezone timeZ;
	int i;
	ListMap::iterator z;
	timeZ.tz_minuteswest=-60;
	gettimeofday(&timeV,&timeZ);
	srandom(timeV.tv_usec);
 
	std::cout<<"\nWeszam do test";
	//srandom(321872);
	std::cout<<"\nUstawiam ziarno";
	   std::cout<<"\nwypelnilam pierwsza liste";
	   for(i=0;i<30000;i++)
	   dwojka.insert(std::make_pair(random()%2000000,""));
 
	   std::cout<<"\nWypelnilam druga liste";
	   std::cout<<"\nPierwsza lsta ma "<<jedynka.size()<<" elementów";
       std::cout<<"\nDruga lista ma "<<	dwojka.size()<<"elemntów";
       std::cout<<"Trzecia lista ma "<<trojka.size()<<" elementow\n";
	trojka.insert(std::make_pair(4,""));
	std::cout<<"...";
	z=trojka.begin();
	for(z;z!=trojka.end();z++)
	{
		std::cout<<" "<<z->first;
		std::cout<<"\n";
	}
	trojka.insert(std::make_pair(3,""));
	std::cout<<"...";
	z=trojka.begin();
	for(z;z!=trojka.end();z++)
	{
		std::cout<<" "<<z->first;
		std::cout<<"\n";
	}
	trojka.insert(std::make_pair(8,""));
	std::cout<<"...";
	z=trojka.begin();
	for(z;z!=trojka.end();z++)
	{
		std::cout<<" "<<z->first;
		std::cout<<"\n";
	}
	trojka.insert(std::make_pair(10,""));
	std::cout<<"...";
	z=trojka.begin();
	for(z;z!=trojka.end();z++)
	{
		std::cout<<" "<<z->first;
		std::cout<<"\n";
	}
	trojka.insert(std::make_pair(98,""));
	std::cout<<"...";
	z=trojka.begin();
	for(z;z!=trojka.end();z++)
	{
		std::cout<<" "<<z->first<< "/n";
	}
	trojka.insert(std::make_pair(21,""));
	std::cout<<"...";
	z=trojka.begin();
	for(z;z!=trojka.end();z++)
	{
		std::cout<<" "<<z->first;
		std::cout<<"\n";
	}
	trojka.insert(std::make_pair(63,""));
	std::cout<<"...";
	z=trojka.begin();
	for(z;z!=trojka.end();z++)
	{
		std::cout<<" "<<z->first;
		std::cout<<"\n";
 
	}
	trojka.insert(std::make_pair(1,""));
	std::cout<<"...";
	z=trojka.begin();
	for(z;z!=trojka.end();z++)
	{
		std::cout<<" "<<z->first;
		std::cout<<"\n";
	}
	trojka.insert(std::make_pair(3,""));
	std::cout<<"...";
	z=trojka.begin();
	for(z;z!=trojka.end();z++)
	{
		std::cout<<" "<<z->first;
		std::cout<<"\n";
	}
	trojka.insert(std::make_pair(32,""));
	std::cout<<"...";
	z=trojka.begin();
	for(z;z!=trojka.end();z++)
	{
		std::cout<<" "<<z->first;
		std::cout<<"\n";
	}
	trojka.insert(std::make_pair(43,""));
	std::cout<<"...";
	z=trojka.begin();
	for(z;z!=trojka.end();z++)
	{
		std::cout<<" "<<z->first;
		std::cout<<"\n";
	}
	trojka.insert(std::make_pair(84,""));
	std::cout<<"...";
	z=trojka.begin();
	for(z;z!=trojka.end();z++)
	{
		std::cout<<" "<<z->first;
		std::cout<<"\n";
	}
	trojka.insert(std::make_pair(33,""));
	std::cout<<"...";
	z=trojka.begin();
	for(z;z!=trojka.end();z++)
	{
		std::cout<<" "<<z->first;
		std::cout<<"\n";
	}
 
	std::cout<<"1Trzecia lista ma "<<trojka.size()<<" elementow\n";
 
	z=trojka.begin();
	for(z;z!=trojka.end();z++)
	{
		std::cout<<" "<<z->first;
		std::cout<<"\n";
	}
	for(i=0;i<10000;i++)
		trojka.insert(std::make_pair(random()%2000000,""));
	ListMap::iterator l=trojka.find(98);
	ListMap::iterator k=trojka.find(32);
 
	trojka.erase(k,l);
 
	std::cout<<"2Trzecia lista ma "<<trojka.size()<<" elementow\n";
	//trojka.erase(1);
	int t;
	i=10;
	while(i!=0)
	{
		t=dwojka.erase(random()%2000000);
		std::cout<<t<<" ";
		if(t)
		{
			i--;
			std::cout<<"randomalnie usuwam \n";
			continue;
		}
		else
		//	std::cout<<"randomalnie nie usuwam \n";
		continue;
	}
 
	std::cout<<"1Druga lista ma "<<dwojka.size()<<" elementow\n";
	dwojka.clear();
	std::cout<<"2Druga lista ma "<<dwojka.size()<<" elementow\n";
	TEST_MAP czworka(jedynka);
	std::cout<<"Czy mapy 1 i 4 s. identyczne?? "<<czworka.struct_eq(jedynka)<<"\n";
 
	std::cout<<"Czy mapy 1 i 3 s. identyczne?? "<<jedynka.struct_eq(trojka)<<"\n";
 
	int m=20;
	while(m!=0)
	{
		trojka[random()%2000000];
		m--;
		std::cout<<"wstawiam do trojki randomalnie. Mam ju "<< (20-m)<<" eltów\n";
    }
    int g=40;
/*
	m=0;
	while(g!=0)
	{
 
 
		g=g-jedynka.erase(m);
		m++;
		std::cout<<"usuwam z jedynki kolejne elty. Usunelam juz "<< (40-g)<<" eltow\n";
 
	}
*/
	std::cout<<"Pierwsza lista ma "<<jedynka.size()<<" elementow\n";
	std::cout<<"Druga lista ma "<<dwojka.size()<<" elementow\n";
	std::cout<<"Trzecia lista ma "<< trojka.size()<<" elementow\n";
	std::cout<<"Czwarta lista ma "<<czworka.size()<<" elementow\n";
	jedynka.clear();
	dwojka.clear();
	k=trojka.begin();
	for(k;k!=trojka.end();k++)
	{
		std::cout<<" "<<k->first;
	}
	k=trojka.begin();
	l=trojka.end();
 
	trojka.erase(k,l);
}
// }}}
 
// {{{
void tes2()
{
    std::cout << "Testy uzytkownika" << std::endl;
    ListMap m; //swieza mapa
    m.insert(std::pair<int,std::string>(1, "Merry"));
    m.insert(std::pair<int,std::string>(3, "Jane"));
    m.insert(std::pair<int,std::string>(2, "Korwin"));
    m.insert(std::pair<int,std::string>(0, "M"));
	std::cout << "wypisuje m\n";
    for(ListMap::iterator i=m.begin(); i!=m.end(); ++i)
    print(*i);
    ListMap n=m; //konstruktor kopiujacy
	std::cout << "wypisuje n\n";
    for(ListMap::iterator i=n.begin(); i!=n.end(); ++i)
    print(*i);
	std::cout << "koniec m\n";
	std::cout << "szuka i wypisuje m[2] \n";
    print(*(m.find(2)));
	std::cout << "szuka i wypisuje m[7] jezeli nie koniec \n";
    if( m.find(7) != m.end() ) print(*(m.find(7))); 
    m.insert(std::pair<int,std::string>(7, "Z"));
	std::cout << "szuka i wypisuje m[7] jezeli nie koniec \n";
    if( m.find(7) != m.end() ) print(*(m.find(7)));
    std::pair<ListMap::iterator, bool> pair = m.insert(std::pair<int,std::string>(3, "A"));
	std::cout << "wypisuje pare \n";
    print(*(pair.first));
	std::cout << "wypisuje element m[1] \n";
    std::cout <<"element 1: "<<m[1]<<std::endl;
	std::cout << "wypisuje element m[8] \n";
    std::cout<<"element 8: "<<m[8]<<std::endl;
	std::cout << "wypisuje m \n";
    for(ListMap::iterator i=m.begin(); i!=m.end(); ++i)
    print(*i);
    std::cout<<std::endl<<"rozmiar: "<<m.size()<<std::endl
    <<"ilosc elementow 3: "<<m.count(3)<<std::endl 
    <<"ilosc elementow 9: "<< m.count(9)<<std::endl;
    ListMap b;
    b.insert(std::pair<int,std::string>(0, "M"));
	std::cout << "wypisuje b \n";
    for(ListMap::iterator i=b.begin(); i!=b.end(); ++i)
    print(*i);
    b.erase(b.find(0));
	std::cout << "wypisuje b \n";
    for(ListMap::iterator i=b.begin(); i!=b.end(); ++i)
    print(*i);
    b.insert(std::pair<int,std::string>(1, "A"));
    b.insert(std::pair<int,std::string>(3, "B"));
	std::cout << "wypisuje b \n";
    for(ListMap::iterator i=b.begin(); i!=b.end(); ++i)
    print(*i);
    int x=b.erase(1);
	std::cout << "wypisuje b \n";
    for(ListMap::iterator i=b.begin(); i!=b.end(); ++i)
    print(*i);
    std::cout<<"ilosc usunietych 1: "<<x<<std::endl;
    m.clear();
    m.insert(std::pair<int,std::string>(1, "Merry"));
    m.insert(std::pair<int,std::string>(3, "Jane"));
    m.insert(std::pair<int,std::string>(2, "Korwin"));
    m.insert(std::pair<int,std::string>(0, "M"));
    m.insert(std::pair<int,std::string>(6, "asd"));
    m.insert(std::pair<int,std::string>(7, "546"));
    m.insert(std::pair<int,std::string>(9, "xxx"));
    m.insert(std::pair<int,std::string>(8, "mju"));
	std::cout << "wypisuje m \n";
    for(ListMap::iterator i=m.begin(); i!=m.end(); ++i)
    print(*i);     
    m.erase(7);
    m.erase(7);
    m.erase(0);
	std::cout << "wypisuje m \n";
    for(ListMap::iterator i=m.begin(); i!=m.end(); ++i)
    print(*i);
    m.erase(m.begin(),m.end());
	std::cout << "wypisuje m po m.erase(m.begin(),m.end()); \n";
    for(ListMap::iterator i=m.begin(); i!=m.end(); ++i)
    print(*i);
	std::cout << "wypisalem m \n";
    b.clear();
    b.insert(std::pair<int,std::string>(5, "E"));
    b.insert(std::pair<int,std::string>(4, "D"));
    b.insert(std::pair<int,std::string>(3, "C"));
    b.insert(std::pair<int,std::string>(2, "B"));
    b.insert(std::pair<int,std::string>(1, "A"));
	std::cout << "wypisuje b \n";
    for(ListMap::iterator i=b.begin(); i!=b.end(); ++i)
    print(*i);
    ListMap::iterator v=b.find(2);
    ListMap::iterator y=b.find(4);
    ListMap::iterator z=b.erase(v,y);
    if(z==b.end()) std::cout<<"TAK\n";
    for(ListMap::iterator i=b.begin(); i!=b.end(); ++i)
    print(*i);
    b.erase(b.end());
    b.insert(std::pair<int,std::string>(3, "C"));
    b.insert(std::pair<int,std::string>(2, "B"));
    v=b.find(4);
    b.erase(v,b.end());
    for(ListMap::iterator i=b.begin(); i!=b.end(); ++i)
    print(*i);
    b.erase(b.end(),b.end());
    m.clear();
    b.clear();
    m.insert(std::pair<int,std::string>(1, "A"));
    b.insert(std::pair<int,std::string>(1, "A"));
    m.insert(std::pair<int,std::string>(2, "C"));
    b.insert(std::pair<int,std::string>(2, "B"));
    if(m.struct_eq(b)) std::cout<<"seq TAK\n"<<std::endl;
    else std::cout<<"seq NIE\n"<<std::endl;
    m.insert(std::pair<int,std::string>(3, "D"));
    b.insert(std::pair<int,std::string>(4, "D"));
    if(m.struct_eq(b)) std::cout<<"seq TAK\n"<<std::endl;
    else std::cout<<"seq NIE\n"<<std::endl;
    m.insert(std::pair<int,std::string>(5, "X"));
    if(m.struct_eq(b)) std::cout<<"seq TAK\n"<<std::endl;
    else std::cout<<"seq NIE\n"<<std::endl;   
    m.clear();
    b.clear();
    m.insert(std::pair<int,std::string>(1, "A"));
    b.insert(std::pair<int,std::string>(1, "A"));
    m.insert(std::pair<int,std::string>(2, "B"));
    b.insert(std::pair<int,std::string>(2, "B"));
    if(m.info_eq(b)) std::cout<<"ieq TAK\n"<<std::endl;
    else std::cout<<"seq NIE\n"<<std::endl;
    m.insert(std::pair<int,std::string>(3, "D"));
    b.insert(std::pair<int,std::string>(4, "E"));
    if(m.info_eq(b)) std::cout<<"ieq TAK\n"<<std::endl;
    else std::cout<<"seq NIE\n"<<std::endl;
}
// }}}
 
//{{{
void test3()
{
    //typedef std::map<int, std::string> TEST_MAP;
    //typedef SmallMap<int, std::string> TEST_MAP;
    typedef ListMap TEST_MAP;
//    CCount::count = 0;
    std::cout << "      Program testujacy" << std::endl;
    TEST_MAP object;
    std::pair<int, std::string> a(1, "lukasz");
    std::pair<int, std::string> b(2, "robert");
    std::pair<int, std::string> c(3, "tomek");
    std::pair<int, std::string> d(4, "agata");
    std::pair<int, std::string> e(5, "michal");
    std::pair<int, std::string> f(6, "ania");
    object.insert(a);
    object.insert(b);
    object.insert(c);
    object.insert(d);
    object.insert(e);
    object.insert(f);
    if (object.insert(a).second == false) std::cout << "Wstawianie drugiego takiego samego elementu...   [ok]" << std::endl;
    TEST_MAP::const_iterator i;
    for (i = object.begin(); i != object.end(); ++i);
    if (i == object.end()) std::cout << "Przechodzenie iteratorem ++iterator...   [ok]" << std::endl;
    if ((object.find(1) != i) && (object.find(2) != i) && (object.find(3) != i) && (object.find(4) != i) && (object.find(5) != i) && (object.find(6) != i) &&
    (object.find(0) == i)) std::cout << "Sprawdzanie dzialania funkcji find...   [ok]" << std::endl;
    if (object[1] == "lukasz") std::cout << "Operator[]...   [ok]" << std::endl;
    if (object.size() == 6) std::cout << "Sprawdzanie dzialania funkcji size...   [ok]" << std::endl;
    if ((object.count(6) == 1) && (object.count(0) == 0)) std::cout << "Sprawdzanie dzialania funkcji count...   [ok]" << std::endl;
    //object.erase(object.find(1));
    //object.erase(object.find(6));
    //object.erase(object.find(4));
    TEST_MAP copy(object);
////
    if ((copy.struct_eq(object)) && (copy.info_eq(object))) std::cout << "Sprawdzanie dzialania funkcji struct_eq i info_eq dla poprawnych...   [ok]" << std::endl;
    copy.clear();
////
    if (!((copy.struct_eq(object)) && (copy.info_eq(object)))) std::cout << "Sprawdzanie dzialania funkcji struct_eq i info_eq dla niepoprawnych...   [ok]" << std::endl;
    copy.insert(a);
    copy.insert(f);
    copy.insert(b);
    copy.insert(c);
    copy.insert(d);
    copy.insert(e);
////
    if (copy.info_eq(object)) std::cout << "Sprawdzanie dzialania funkcji info_eq dla poprawnych...   [ok]" << std::endl;
////
    if (!copy.struct_eq(object)) std::cout << "Sprawdzanie dzialania funkcji struct_eq dla poprawnych...   [ok]" << std::endl;
    std::cout << copy.size() << std::endl;
    copy.erase(copy.find(2));
    std::cout << copy.size() << std::endl;
    for (i = copy.begin(); i != copy.end(); ++i);
    copy.erase(copy.find(1));
    std::cout << copy.size() << std::endl;
    for (i = copy.begin(); i != copy.end(); ++i);
//
    copy.erase(copy.find(99));
    std::cout << copy.size() << std::endl;
    for (i = copy.begin(); i != copy.end(); ++i);
    copy.erase(6);
    std::cout << copy.size() << std::endl;
    for (i = copy.begin(); i != copy.end(); ++i);
    copy.erase(78);
    std::cout << copy.size() << std::endl;
    for (i = copy.begin(); i != copy.end(); ++i);
    copy.clear();
    copy.insert(a);
    copy.insert(b);
    copy.insert(c);
    copy.insert(d);
    copy.insert(e);
    copy.insert(f);
    i = copy.find(6);
    TEST_MAP::iterator j = copy.find(1);
//
    copy.erase(i,j);
    std::cout << copy.size() << std::endl;
    for (i = copy.begin(); i != copy.end(); ++i);
    i = copy.find(1);
//
    copy.erase(i,i);
    std::cout << copy.size() << std::endl;
    for (i = copy.begin(); i != copy.end(); ++i);
 
    std::cout << "NOWE" << std::endl;
    object.clear();
    copy.clear();
    copy.insert(a);
    copy.insert(b);
    copy.insert(c);
    copy.insert(d);
    copy.insert(e);
    copy.insert(f);
    object.insert(a);
    object.insert(b);
    object.insert(c);
    object.insert(d);
    object.insert(e);
    object.insert(f);
    copy.erase(copy.find(4));
    if (copy.erase(6) == 0) std::cout << "qrwa" << std::endl;;
    copy.erase(1);
//
    copy.erase(copy.find(3), copy.erase(copy.end()));
    if (copy.size() == 1) std::cout << "Operacja ok:)" << std::endl;
    else for_each(copy.begin(), copy.end(), print );
    copy.erase(2);
    if (copy.size() == 0) std::cout << "Operacja2 ok:)" << std::endl;
    else for_each(copy.begin(), copy.end(), print );
//
    copy.erase(copy.find(0));
    for (i = object.begin(); i != object.end(); i++);
    object.clear();
    object.insert(a);
    object.insert(b);
    object.insert(c);
    object.insert(d);
    object.insert(e);
    object.insert(f);
    TEST_MAP copy2(object);
////
    if ((copy2.struct_eq(object)) && (copy2.info_eq(object))) std::cout << "Kopiowanie kolejnosc...   [ok]" << std::endl;
////
    else for_each(copy2.begin(), copy2.end(), print );
    std::cout << "END" << std::endl;
}
//}}}
 
//{{{
void test()
{
    //typedef std::map<int, std::string> TEST_MAP;
    typedef ListMap TEST_MAP;
//    CCount::count = 0;
    std::cout << "Testy uzytkownika" << std::endl;
 
    TEST_MAP m;
    std::pair<int, std::string> a(1, "lukasz");
    std::pair<int, std::string> b(2, "robert");
    std::pair<int, std::string> c(3, "tomek");
    std::pair<int, std::string> d(4, "agata");
    std::pair<int, std::string> e(5, "michal");
    std::pair<int, std::string> f(6, "ania");
    m.insert(a);
    m.insert(b);
    m.insert(c);
    m.insert(d);
    m.insert(e);
    m.insert(f);
    if (m.insert(a).second == false) std::cout << "Wstawianie drugiego takiego samego elementu...   [ok]" << std::endl;
    TEST_MAP::const_iterator i;
    for (i = m.begin(); i != m.end(); ++i);
    if (i == m.end()) std::cout << "Przechodzenie iteratorem ++iterator...   [ok]" << std::endl;
    if ((m.find(1) != i) && (m.find(2) != i) && (m.find(3) != i) && (m.find(4) != i) && (m.find(5) != i) && (m.find(6) != i) &&
    (m.find(0) == i)) std::cout << "Sprawdzanie dzialania funkcji find...   [ok]" << std::endl;
    if (m[1] == "lukasz") std::cout << "Operator[]...   [ok]" << std::endl;
    if (m.size() == 6) std::cout << "Sprawdzanie dzialania funkcji size...   [ok]" << std::endl;
    if ((m.count(6) == 1) && (m.count(0) == 0)) std::cout << "Sprawdzanie dzialania funkcji count...   [ok]" << std::endl;
    //m.erase(m.find(1));
    //m.erase(m.find(6));
    //m.erase(m.find(4));
    TEST_MAP n(m);
////
    if ((n.struct_eq(m)) && (n.info_eq(m))) std::cout << "Sprawdzanie dzialania funkcji struct_eq i info_eq dla poprawnych...   [ok]" << std::endl;
    n.clear();
////
    if (!((n.struct_eq(m)) && (n.info_eq(m)))) std::cout << "Sprawdzanie dzialania funkcji struct_eq i info_eq dla niepoprawnych...   [ok]" << std::endl;
    n.insert(a);
    n.insert(f);
    n.insert(b);
    n.insert(c);
    n.insert(d);
    n.insert(e);
////
    if (n.info_eq(m)) std::cout << "Sprawdzanie dzialania funkcji info_eq dla poprawnych...   [ok]" << std::endl;
////
    if (!n.struct_eq(m)) std::cout << "Sprawdzanie dzialania funkcji struct_eq dla poprawnych...   [ok]" << std::endl;
    std::cout << n.size() << std::endl;
    n.erase(n.find(2));
    std::cout << n.size() << std::endl;
    for (i = n.begin(); i != n.end(); ++i);
    n.erase(n.find(1));
    std::cout << n.size() << std::endl;
    for (i = n.begin(); i != n.end(); ++i);
//
    n.erase(n.find(99));
    std::cout << n.size() << std::endl;
    for (i = n.begin(); i != n.end(); ++i);
    n.erase(6);
    std::cout << n.size() << std::endl;
    for (i = n.begin(); i != n.end(); ++i);
    n.erase(78);
    std::cout << n.size() << std::endl;
    for (i = n.begin(); i != n.end(); ++i);
    n.clear();
    n.insert(a);
    n.insert(b);
    n.insert(c);
    n.insert(d);
    n.insert(e);
    n.insert(f);
    i = n.find(6);
    TEST_MAP::iterator j = n.find(1);
//
    n.erase(i,j);
    std::cout << n.size() << std::endl;
    for (i = n.begin(); i != n.end(); ++i);
    i = n.find(1);
//
    n.erase(i,i);
    std::cout << n.size() << std::endl;
    for (i = n.begin(); i != n.end(); ++i);
 
    std::cout << "NOWE" << std::endl;
    m.clear();
    n.clear();
    n.insert(a);
    n.insert(b);
    n.insert(c);
    n.insert(d);
    n.insert(e);
    n.insert(f);
    m.insert(a);
    m.insert(b);
    m.insert(c);
    m.insert(d);
    m.insert(e);
    m.insert(f);
    n.erase(n.find(4));
    if (n.erase(6) == 0) std::cout << "qrwa" << std::endl;;
    n.erase(1);
//
    n.erase(n.find(3), n.erase(n.end()));
    if (n.size() == 1) std::cout << "Operacja ok:)" << std::endl;
    else for_each(n.begin(), n.end(), print );
    n.erase(2);
    if (n.size() == 0) std::cout << "Operacja2 ok:)" << std::endl;
    else for_each(n.begin(), n.end(), print );
//
    n.erase(n.find(0));
    for (i = m.begin(); i != m.end(); i++);
    m.clear();
    m.insert(a);
    m.insert(b);
    m.insert(c);
    m.insert(d);
    m.insert(e);
    m.insert(f);
    TEST_MAP n2(m);
////
    if ((n2.struct_eq(m)) && (n2.info_eq(m))) std::cout << "Kopiowanie kolejnosc...   [ok]" << std::endl;
////
    else for_each(n2.begin(), n2.end(), print );
    std::cout << "END" << std::endl;
}
