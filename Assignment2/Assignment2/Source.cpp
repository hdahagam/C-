//HW2: Sparse Vector Operations Using Linked List structures
//Due: 11:59PM, Friday, September 22

//Implement the following member functions for class my_vector:
//add_node
//operator+
//operator*



#include <iostream>
#include <fstream>
using namespace std;

ofstream out("data1.txt");
class node {
public:
	int value;
	int position;
	node * next;
	node() { value = -9999; position = -1; next = nullptr; }
	node(int i, int j) { value = i; position = j; next = nullptr; }
};

class my_vector {
public:
	int size;
	int num_nodes; //number of non-zero elements
	node * head;
	my_vector() { size = num_nodes = 0; head = nullptr; }

	void add_node(int v, int p); //add a new node with value v and position p;
								 //if a node at position p already exists, update its value to v

	void make_random_vector(int s, int n, int k);
	//set the value of size  to s;
	//randomly create n nodes in -(k-1) to k-1

	my_vector operator+(my_vector V); //vector addition

	int operator*(my_vector V);//inner product

	void print();
};

int my_vector::operator* (my_vector V)
{
	my_vector temp;
	int product = 0;
	//You need to complete the implementation.
	node *iter1 = this->head;
	node *iter2 = V.head;
	while ((iter1 != nullptr) && (iter2 != nullptr))
	{
		if (iter1->position == iter2->position)
		{
			product += (iter1->value)*(iter2->value);
			iter1 = iter1->next;
			iter2 = iter2->next;
		}
		else if (iter1->position < iter2->position)
		{
			iter1 = iter1->next;
		}
		else
		{
			iter2 = iter2->next;
		}
	}

	return product;
}
void my_vector::make_random_vector(int s, int n, int k) {
	size = s;
	for (int i = 0; i < n; i++) {
		int p = rand() % s;
		int v = rand() % (2 * k - 1) - (k - 1);
		add_node(v, p);
	}
}

void my_vector::add_node(int v, int p)
{
	size++;
	if (v == 0)
		return;
	node *newNode = new node(v, p);
	num_nodes++;

	// empty vector
	if (head == nullptr)
	{
		head = newNode;
		return;
	}
	//vector with elements
	node *lead = head, *trail = nullptr;
	while (lead != nullptr)
	{
		//checking if the same position already exists 
		if (newNode->position == lead->position)
		{
			lead->value = newNode->value;
			return;
		}
		if (lead->position > newNode->position)
		{
			//checking if lead is the head
			if (lead == head)
			{
				newNode->next = lead;
				head = newNode;
				return;
			}
			// Inserting somewhere in the vector
			trail->next = newNode;
			newNode->next = lead;
			return;
		}
		trail = lead;
		lead = lead->next;
	}
	// Adding node at the end
	trail->next = newNode;
}

void my_vector::print() {
	out << endl;
	node * p = head;
	while (p != nullptr) {
		out << p->value << " " << p->position << "  ";
		p = p->next;
	}
	out << endl;
}

my_vector my_vector::operator+(my_vector V) {
	my_vector temp;
	//You need to complete the implementation.
	node *iter1 = this->head;
	node *iter2 = V.head;
	while ((iter1 != nullptr) && (iter2 != nullptr))
	{
		if (iter1->position == iter2->position)
		{
			temp.add_node(iter1->value + iter2->value, iter1->position);
			iter1 = iter1->next;
			iter2 = iter2->next;
		}
		else if (iter1->position < iter2->position)
		{
			temp.add_node(iter1->value, iter1->position);
			iter1 = iter1->next;
		}
		else
		{
			temp.add_node(iter2->value, iter2->position);
			iter2 = iter2->next;
		}
	}
	while (iter1 != nullptr)
	{
		temp.add_node(iter1->value, iter1->position);
		iter1 = iter1->next;
	}
	while (iter2 != nullptr)
	{
		temp.add_node(iter2->value, iter2->position);
		iter2 = iter2->next;
	}
	return temp;

}
int main() {

	my_vector V1, V2, V3;
	V1.make_random_vector(30, 8, 10);
	out << "Vector 1 " << endl;
	V1.print();
	V2.make_random_vector(30, 6, 10);
	out << "Vector 2 " << endl;
	V2.print();
	out << "Vector 3 : SUM " << endl;
	V3 = V1 + V2;
	V3.print();
	int inner_product = V1 * V2;
	out << "PRODUCT:" << inner_product << endl;
	out.close();
	return 0;

}
