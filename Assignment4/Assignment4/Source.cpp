//HW4: Implement a generic bag using template
//Due: Oct. 23 (Monday) at 11:59pm

#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;
template <class T> class ThreeD {
public:
	T ht;
	T wid;
	T dep;
	ThreeD() { ht = wid = dep = 0; }
	ThreeD(T i) { ht = wid = dep = i; }
	ThreeD(T a, T b, T c) { ht = a; wid = b; dep = c; }

	template <class T> friend	ostream & operator<<(ostream &s, const ThreeD<T> &t);
};
template <class T> class node {
public:
	T value;
	node<T> * next;
	node<T>() { next = nullptr; }
	node<T>(T v) { value = v; next = nullptr; }
};
template <class T> class linked_list {
public:
	int num_nodes;
	node<T> * head;
	linked_list() { num_nodes = 0; head = nullptr; }
	~linked_list();//destructor
	linked_list(const linked_list &L); //copy constructor
	linked_list(linked_list &&L); //move constructor
	void operator=(linked_list &L);//left reference operator=
	void operator=(linked_list &&L); //right reference operator=
	void push_front(T v);//You need to implement this part.
};

template <class X>
class item {
public:
	X value;
	item<X> *next;
	item<X> *previous;
	item(X v) { value = v; next = nullptr; previous = nullptr; }
};

template <class X>
class bag {
public:
	item<X> *last;
	item<X> *first;
	int num_items;
	int size() { return num_items; }
	void show_bag();//Print all items in the bag
	bag() { last = nullptr; first = nullptr; num_items = 0; } //default constructor for bag class
	bag(const bag &B); //copy constructor
	bag(bag &&B); //move constructor
	void operator=(bag &B);//left reference operator=
	void operator=(bag &&B); //right reference operator=
	void push_back(X v);  //insert an item with value v to the back of the bag
	void push_front(X v); //insert an item with value v to the front of the bag
	void pop_back(); //delete the last item in the bag
	void pop_front(); //delete the first item in the bag
	X &operator[](int i); //Access bag item with index. 
	X front() {  //it returns the value of the first item in the bag.
				 //In real applicaitons, we need to check if the bag is empty.  We are skipping this here.
		return first->value;
	}
	X back() { //it returns the value of the last item in the bag
			   //In real applicaitons, we need to check if the bag is empty.  We are skipping this here.

		return last->value;
	}
	void clear(); //Delete all items in the bag
	~bag();//destructor

};
template<class T>
linked_list<T>::~linked_list()  //destructor
{
	node<T> *newNode=new node<T>;
	while (head != nullptr) {
		newNode = head->next;
		delete head;
		head = newNode;
	}
}
template<class T>
linked_list<T>::linked_list(const linked_list & L)  //copy constructor
{
	num_nodes = L.num_nodes;
	head = nullptr;
	for (int i = 0; i < num_nodes; i++) {
		node<T> * p = new node<T>();
		p->next = head;
		head = p;
	}
	node<T> * p1 = head;
	node<T> * p2 = L.head;
	while (p2 != nullptr) {
		p1->value = p2->value;
		p1 = p1->next;
		p2 = p2->next;
	}
}
template<class T>
linked_list<T>::linked_list(linked_list && L) //move constructor
{
	num_nodes = L.num_nodes;
	head = L.head;
	L.head = nullptr;
}
template<class T>
void linked_list<T>::operator=(linked_list & L) //left reference operator=
{
	num_nodes = L.num_nodes;
	head = nullptr;
	for (int i = 0; i < num_nodes; i++) {
		node<T> * p = new node<T>();
		p->next = head;
		head = p;
	}
	node<T> * p1 = head;
	node<T> * p2 = L.head;
	while (p2 != nullptr) {
		p1->value = p2->value;
		p1 = p1->next;
		p2 = p2->next;
	}
}
template<class T>
void linked_list<T>::operator=(linked_list && L)   //right reference operator=
{
	num_nodes = L.num_nodes;
	head = L.head;
	L.head = nullptr;
}
template<class T>
void linked_list<T>::push_front(T v) {
	node<T> *newNode = new node<T>(v);
	num_nodes++;
	if (head == nullptr) {
		head = newNode;
		return;
	}
	newNode->next = head;
	head = newNode;
    
} 
template<class X> void bag<X>::push_front(X v) {
	item<X> *i = new item<X>(v);
	if(num_items==0){ //check for empty bag 
		first = i;
		last = i;
		num_items++;
		return;
	}
	num_items++;
	first->previous = i;
	i->next = first;
	first = i;
}

template<class X> void bag<X>::push_back(X v) {
	item<X> *i = new item<X>(v);
	if (num_items == 0) { //check for empty bag 
		first = i;
		last = i;
		num_items++;
		return;
	}
	num_items++;
	last->next = i;
	i->previous = last;
	last = i;

}
template<class X> bag<X>::~bag() {
	item<X> *temp;
	while (first != nullptr) {
		temp = first;
		first = first->next;
		delete temp;
	}
	 first=nullptr;
}


template<class X> void bag<X>::pop_back() {
	if (num_items == 0) {
		cout << "empty bag";
		return;
	}
	num_items--;
	item<X> *temp;
	if (num_items == 1) {
		free(first);
		first = nullptr;
		last = nullptr;
	}
	temp = last;
	last = last->previous;
	last->next = nullptr;
	free(temp);
}
template<class X> void bag<X>::pop_front() {
	if (num_items == 0) {
		cout << "empty bag";
		return;
	}
	num_items--;
	item<X> *temp;
	if (num_items == 1) {
		free(first);
		first = nullptr;
		last = nullptr;
		return;
	}
	temp = first;
	first = first->next;
	first->previous = nullptr;
	free(temp);
}

template<class X> void bag<X>::show_bag() {
	// You need to implement this.
	if (num_items == 0) {
		cout << "empty bag";
		return;
	}
	if (num_items == 1) {
		cout << first->value<<" ";
		return;
	}
	item<X> *temp = first;
	while (temp!= nullptr) {
		cout << temp->value<<" ";
		temp = temp->next;
	}

}

template<class X>
bag<X>::bag(const bag & B) //copy constructor
{
	num_items = B.num_items;
	last = nullptr;
	first = nullptr;
	for (int i = 0; i < num_items; i++) {
		item<X> *i = new item<X>
		if (last == nullptr) {
			first = i;
		}
		else {
			i->previous = last;
			last->next = i;
		}
		last = i;
	}
	item<X> * i1 = first;
	item<X> * i2 = B.first;
	while (i2 != nullptr) {
		i1->value = i2->value;
		i1 = i1->next;
		i2 = i2->next;
	}
}

template<class X>
bag<X>::bag(bag && B) //move constructor
{
	num_nodes = B.num_nodes;
	first= B.first;
	B.first = nullptr;
	last = B.last;
	B.last = nullptr;
}

template<class X>
void bag<X>::operator=(bag & B) //left reference operator=
{
	num_items = B.num_items;
	last = nullptr;
	first = nullptr;
	for (int i = 0; i < num_items; i++) {
		item<X> *i = new item<X>
			if (last == nullptr) {
				first = i;
			}
			else {
				i->previous = last;
				last->next = i;
			}
			last = i;
	}
	item<X> * i1 = first;
	item<X> * i2 = B.first;
	while (i2 != nullptr) {
		i1->value = i2->value;
		i1 = i1->next;
		i2 = i2->next;
	}
}

template<class X>
void bag<X>::operator=(bag && B)//right reference operator=
{
	num_nodes = B.num_nodes;
	first = B.first;
	B.first = nullptr;
	last = B.last;
	B.last = nullptr;
}


template<class X> X& bag<X>::operator[](int i) {
	//In real application, we need to check if index i is in the valid range, we are skipping it here.
	//We assume that is is in the valid range
	item<X> *temp = first;
	while (i != 0) {
		temp = temp->next;
		i--;
	}
	return temp->value;
}

template<class X> void bag<X>::clear() {
	if (num_items == 0){
		return;
	}
	
	if (num_items == 1){
		num_items--;
		free(first);
		first = nullptr;
		last = nullptr;
		return;
	}
	item<X> *temp;
	while (first != nullptr) {
		num_items--;
		temp = first;
		first = first->next;
		free(temp);	
	}
}

template <class T> ostream & operator<<(ostream &s, const ThreeD<T> &t) {//ostream & operator<<(ostream &s, ThreeD t) will also work.
	s << "( " << t.ht << ", " << t.wid << ", " << t.dep << " )";
	return s;
}



template <class T> ostream & operator<<(ostream &s, const linked_list<T> &L) {
	node<T> * p = L.head;
	while (p != nullptr) {
		s << p->value << " ";
		p = p->next;
	}
	return s;
}

int main() {
	bag<double> bag_d;
	bag_d.push_back(5.5);
	bag_d.push_back(6.6);
	bag_d.push_front(4.4);
	bag_d.push_front(3.3);
	bag_d.pop_front();
	bag_d.pop_back();
	bag_d.show_bag();
	cout << endl;

	bag<int> bag_i;
	bag_i.push_back(5);
	bag_i.push_back(6);
	bag_i.push_front(4);
	bag_i.push_front(3);
	bag_i.pop_front();
	bag_i.pop_back();
	bag_i.show_bag();

	ThreeD<int> td3(3), td4(4), td5(5), td6(6), td7(100, 200, 300);
	bag<ThreeD<int>> bag_3D;
	bag_3D.push_back(td5);
	bag_3D.push_back(td6);
	bag_3D.push_front(td4);
	bag_3D.push_front(td3);
	bag_3D.pop_front();
	bag_3D.pop_back();
	bag_3D.show_bag();
	cout << "\nfront = " << bag_3D.front() << "  back = " << bag_3D.back();
	cout << "\n" << bag_3D[0] << " " << bag_3D[1] << "\n";
	bag_3D[1] = td7;
	cout << "\n" << bag_3D[0] << " " << bag_3D[1] << "\n";
	bag_3D.clear();
	bag_3D.show_bag();
	cout << "\nsize = " << bag_3D.size();
	linked_list<string>ls_1;
	ls_1.push_front("David");
	ls_1.push_front("John");
	ls_1.push_front("Pat");
	ls_1.push_front("Ben");
	ls_1.push_front("Jeff");
	cout << endl;
	cout << ls_1 << endl;

	linked_list<string>ls_2;
	ls_2.push_front("Wendy");
	ls_2.push_front("Mary");
	ls_2.push_front("Nancy");
	ls_2.push_front("Jennifer");
	cout << endl;
	cout << ls_2 << endl;
	bag<linked_list<string>> bag_string;
	bag_string.push_back(ls_1);
	bag_string.push_back(ls_2);
	bag_string.show_bag();
	cout << endl;
	cout << bag_string[1];

	ThreeD<double> t10(3.2, 7.4, 8.9), t11(5.6, 7.7, 2.987), t12(4.6, 7.5, 3.1416), t13(55.6, 66.8, 333.45);
	linked_list<ThreeD<double>> LTD1;
	LTD1.push_front(t10);
	LTD1.push_front(t11);
	linked_list<ThreeD<double>> LTD2;
	LTD2.push_front(t13);
	LTD2.push_front(t12);
	LTD2.push_front(t10);
	LTD2.push_front(t11);

	bag<linked_list<ThreeD<double> > > BLTD;
	BLTD.push_back(LTD1);
	BLTD.push_back(LTD2);
	cout << endl;
	BLTD.show_bag();
	getchar();
	getchar();
}

