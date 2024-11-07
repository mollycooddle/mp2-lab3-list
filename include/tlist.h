#pragma once

#include <iostream>
#include <cstdlib>
#include <type_traits>

//	Numbering in [] / get_index:
//	1 element - 0 / first
//	2 element - 1 / 0
//	3 element - 2 / 1
//	4 element - 3 / 2
//	.........

// if we create List size - 3, then size = size + 1(it's first)

using namespace std;

template<typename T>
class List
{
	struct Node {
		T data;
		Node* next;

		Node() : next(nullptr){}

		Node(T value, Node* current) {
			data = value;
			next = current;
		}
	};
	Node* first = nullptr;
public:
	List() : first(nullptr) {}
	
	List(int n, T deflt = T())
	{
		if (n < 0)
			throw "incorrect length of the created List";

		if (n == 0)
			return;

		first = new Node(deflt, nullptr);
		Node* current = first;
		
		for (int i = 0; i < n; i++) {
			Node* tmp = new Node(deflt, nullptr);
			current->next = tmp;
			current = current->next;
		}
	}
	
	List(const List& other) 
	{
		if (!other.first)
			throw "size list = 0";
		
		first = new Node(other.first->data, nullptr);
		Node* current = first;
		Node* occurent = other.first;
		
		/*while (occurent->next) {
			current->next = new Node(occurent->next->next->data, nullptr);
			current = current->next;
			occurent = occurent->next;
		}*/
		for (List<T>::iterator it = other.begin(); it != other.end(); ++it) {
			current->next = new Node(occurent->next->next->data, nullptr);
		}
	}

	List<T>& operator=(const List<T>& other) noexcept
	{
		if (this == &other) {
			return *this;
		}

		clear(first, "ALL");

		Node* current_other = other.first;
		Node** current = &first;

		while (current_other != nullptr) {
			*current = new Node(current_other->data, nullptr);
			current = &((*current)->next);
			current_other = current_other->next;
		}

		return *this;
	}

	~List() {
		clear(first, "ALL");
	}

	//additional method
	bool operator==(const List<T>& other) const noexcept
	{
		Node* current1 = first;
		Node* current2 = other.first;

		while (current1 != nullptr && current2 != nullptr) {
			if (current1->data != current2->data) {
				return false;  
			}
			current1 = current1->next;
			current2 = current2->next;
		}

		if (current1 != nullptr || current2 != nullptr) {
			return false;
		}

		return true;
	}

	//additional method
	bool operator!=(const List<T>& other) const noexcept
	{
		Node* current1 = first;
		Node* current2 = other.first;

		while (current1 != nullptr && current2 != nullptr) {
			if (current1->data == current2->data) {
				return false; 
			}
			current1 = current1->next;
			current2 = current2->next;
		}

		if (current1 != nullptr || current2 != nullptr) {
			return false;
		}

		return true;
	}

	//additional method
	Node* clear(Node* index, string quality = "ONE") {
		if (quality == "ALL") {
			//while (index != nullptr) {
			//	Node* temp = index;
			//	index = index->next;
			//	delete temp;
			//}


			for (List<T>::iterator it = begin(); it != end(); ++it) {
				Node* temp = index;
				index = index->next;
				delete temp;
				return index;
			}
		}
		else if (quality == "ONE") {
			Node* tmp = index->next;
			index->next = tmp->next;
			delete tmp;

			return index;
		}
		else if (quality == "FIRST") {
			Node* tmp = index;
			index = tmp->next;
			delete tmp;

			return index;
		}
		else
			throw "the given number of items cannot be deleted";
	}

	T& operator[] (int index)
	{

		if (index > size())
			throw "negative index at []";

		Node* current = first;

		for (int i = 0; i < index; i++) {
			current = current->next;
		}
		return current->data;
	}

	size_t size() noexcept
	{
		int size = 0;
		Node* current = first;
		//while (current) {
		//	size++;
		//	current = current->next;
		//}

		for (List<T>::iterator it = begin(); it != end(); ++it) {
			size++;
		}

		return size;
	}

	//additional method
	Node* get_index(int index) 
	{

		if (index > size())
			throw "negative index at get_index(Node* prev)";

		Node* tmp = first;
		int k = 0;

		while (k != index) {
			tmp = tmp->next;
			k++;
		}

		return tmp;
	}

	template <class T2>
	Node* insert(T2 value, Node* prev)
	{
		if (!is_same<T, T2>::value)
			throw "different type in insert";

		Node* tmp = new Node;

		tmp->next = prev->next;
		tmp->data = value;
		prev->next = tmp;
		
		return tmp;
	}

	template <class T2>
	Node* insert_front(T2 value)
	{
		if (!is_same<T, T2>::value)
			throw "different type in insert_front";

		Node* tmp = new Node;

		tmp->data = value;
		tmp->next = first;
		first = tmp;

		return tmp;
	}

	Node* erase(Node* prev) noexcept
	{
		clear(prev, "ONE");

		return prev->next;
	}

	Node* erase_front() noexcept
	{
		Node* ind = clear(first, "FIRST");
		first = ind;

		return first;
	}

	Node* find(T value) 
	{
		Node* current = first;
		Node* tmp = nullptr;

		for (List<T>::iterator it = begin(); it != end(); ++it) {
			if (*it == value) {
				tmp = it.get_current();
				break;
			}
		}

		if (tmp == nullptr)
			throw "not find";

		return tmp;
	}

	Node* get_first() noexcept
	{
		return first;
	}

	friend istream& operator>>(istream& istr, List& other) 
	{
		Node* current = other.first;

		while (current) {
			istr >> current->data;
			current = current->next;
		}

		return istr;
	}

	friend ostream& operator<<(ostream& ostr, const List& other)
	{
		Node* current = other.first;
		
		while (current) {
				ostr << current->data << ' ';
				current = current->next;
		}

		return ostr;
	}

	class iterator {
		Node* current;

		explicit iterator(Node* node) : current(node){}
	public:

		friend class List<T>;

		iterator& operator++() 
		{
			current = current->next;
			return *this;
		}

		iterator operator++(int)
		{
			iterator copy = *this;
			current = current->next;
			return copy;
		}

		T& operator*()
		{
			return current->data;
		}

		T* operator->()
		{
			return &(current->data);
		}

		friend bool operator!=(const iterator& it1, const iterator& it2)
		{
			return (it1.current != it2.current);
		}

		friend bool operator==(const iterator& it1, const iterator& it2)
		{
			return (it1.current == it2.current);
		}

		//additional method
		Node* get_current() {
			return current;
		}

		iterator begin();

		iterator end();
	};

	typename List<T>::iterator List<T>::begin() {
		return iterator(first);
	}

	typename List<T>::iterator List<T>::end() {
		return iterator(nullptr);
	}



	//ZADACHA №15
	bool hasCycle() {
		if (first == nullptr || first->next == nullptr)
			return false;

		Node* slow = first;
		Node* fast = first;

		while (fast != nullptr && fast->next != nullptr) {
			slow = slow->next;
			fast = fast->next->next;

			if (slow == fast)
				return true;
		}

		return false;
	}

	List(char ch, int n, T deflt = T())
	{
		if (n < 0)
			throw "incorrect length of the created List";

		if (n == 0)
			return;

		first = new Node(deflt, nullptr);
		Node* current = first;

		for (int i = 0; i < n; i++) {
			Node* tmp = new Node(deflt, nullptr);
			current->next = tmp;
			current = current->next;
			if (current->next == nullptr) {
				current->next = first;
			}
		}
	}
};