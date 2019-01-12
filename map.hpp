/**
 * implement a container like std::map
 */
#ifndef SJTU_MAP_HPP
#define SJTU_MAP_HPP

// only for std::less<T>
#include <functional>
#include <iostream>
#include <cstddef>
#include "utility.hpp"
#include "exceptions.hpp"

namespace sjtu {

template<
	class Key,
	class T,
	class Compare = std::less<Key>
> class map {
public:
	/**
	 * the internal type of data.
	 * it should have a default constructor, a copy constructor.
	 * You can use sjtu::map as value_type by typedef.
	 */
	typedef pair<const Key, T> value_type;
	/**
	 * see BidirectionalIterator at CppReference for help.
	 *
	 * if there is anything wrong throw invalid_iterator.
	 *     like it = map.beginNode(); --it;
	 *       or it = map.endNode(); ++endNode();
	 */
	struct node{
		value_type *data;
		int height, size;
		node *left, *right, *prev, *next;

		node(value_type *d = NULL, int h = 1, int s = 1, node *l = NULL, node *r = NULL, node *p = NULL, node *n = NULL){
			if(d == NULL){
				data = d;
			}
			else{
				data = new value_type(*d);
			}
			height = h;
			size = s;
			left = l;
			right = r;
			prev = p;
			next = n;
		}
		~node(){
			delete data;
		}
	};

	class const_iterator;
	class iterator {
		friend class map;
		friend class const_iterator;
	private:
		/**
		 * TODO add data members
		 *   just add whatever you want.
		 */
		node *nodePoint;
		const map *mapId;
	public:
		iterator() {
			nodePoint = NULL;
			mapId = NULL;
		}

		iterator(node *po, map *m){
			nodePoint = po;
			mapId = m;
		}

		iterator(const iterator &other) {
			nodePoint = other.nodePoint;
			mapId = other.mapId;
		}

		iterator(const const_iterator &other){
			nodePoint = other.nodePoint;
			mapId = other.mapId;
		}

		iterator &operator = (const iterator &other){
			if(this == &other){
				return *this;
			}
			nodePoint = other.nodePoint;
			mapId = other.mapId;
			return *this;
		}
		/**
		 * return a new iterator which pointer n-next elements
		 *   even if there are not enough elements, just return the answer.
		 * as well as operator-
		 */
		/**
		 * TODO iter++
		 */
		iterator operator++(int) {
			iterator iterNow(*this);
			++(*this);
			return iterNow;
		}
		/**
		 * TODO ++iter
		 */
		iterator & operator++() {
			if(nodePoint == NULL){
				throw invalid_iterator();
			}
			nodePoint = nodePoint -> next;
			if(nodePoint == NULL){
				throw invalid_iterator();
			}
			return *this;
		}
		/**
		 * TODO iter--
		 */
		iterator operator--(int) {
			iterator iterNow = *this;
			--(*this);
			return iterNow;
		}
		/**
		 * TODO --iter
		 */
		iterator & operator--() {
			if(nodePoint == NULL){
				throw invalid_iterator();
			}
			nodePoint = nodePoint -> prev;
			if(nodePoint == NULL){
				throw invalid_iterator();
			}
			return *this;
		}
		/**
		 * a operator to check whether two iterators are same (pointing to the same memory).
		 */
		value_type & operator*() const {
			return *(nodePoint -> data);

		}
		bool operator==(const iterator &rhs) const {
			return (nodePoint == rhs.nodePoint);
		}
		bool operator==(const const_iterator &rhs) const {
			return (nodePoint == rhs.nodePoint);
		}
		/**
		 * some other operator for iterator.
		 */
		bool operator!=(const iterator &rhs) const {
			return (nodePoint != rhs.nodePoint);
		}
		bool operator!=(const const_iterator &rhs) const {
			return (nodePoint != rhs.nodePoint);
		}

		/**
		 * for the support of it->first. 
		 * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
		 */
		value_type* operator->() const noexcept {
			return nodePoint -> data;
		}
	};
	class const_iterator {
		friend map;
		friend class iterator;
		// it should has similar member method as iterator.
		//  and it should be able to construct from an iterator.
	private:
		// data members.
		node *nodePoint;
		const map *mapId;

	public:
		const_iterator() {
			nodePoint = NULL;
			mapId = NULL;
		}
		const_iterator(node *p, const map *m){
			nodePoint = p;
			mapId = m;
		}
		const_iterator(const const_iterator &other) {
			nodePoint = other.nodePoint;
			mapId = other.mapId;
		}
		const_iterator(const iterator &other) {
			nodePoint = other.nodePoint;
			mapId = other.mapId;
		}

		const_iterator &operator = (const const_iterator &other){
			if(this == &other){
				return *this;
			}
			nodePoint = other.nodePoint;
			mapId = other.mapId;
			return *this;
		}
		/**
		 * return a new iterator which pointer n-next elements
		 *   even if there are not enough elements, just return the answer.
		 * as well as operator-
		 */
		/**
		 * TODO iter++
		 */
		const_iterator operator++(int) {
			const_iterator iterNow = *this;
			++(*this);
			return iterNow;
		}
		/**
		 * TODO ++iter
		 */
		const_iterator & operator++() {
			if(nodePoint == NULL){
				throw invalid_iterator();
			}
			nodePoint = nodePoint -> next;
			if(nodePoint == NULL){
				throw invalid_iterator();
			}
			return *this;
		}
		/**
		 * TODO iter--
		 */
		const_iterator operator--(int) {
			const_iterator iterNow = *this;
			--(*this);
			return iterNow;
		}
		/**
		 * TODO --iter
		 */
		const_iterator & operator--() {
			if(nodePoint == NULL){
				throw invalid_iterator();
			}
			nodePoint = nodePoint -> prev;
			if(nodePoint == NULL){
				throw invalid_iterator();
			}
			return *this;
		}
		/**
		 * a operator to check whether two iterators are same (pointing to the same memory).
		 */
		const value_type & operator*() const {
			return *(nodePoint -> data);

		}
		bool operator==(const iterator &rhs) const {
			return (nodePoint == rhs.nodePoint);
		}
		bool operator==(const const_iterator &rhs) const {
			return (nodePoint == rhs.nodePoint);
		}
		/**
		 * some other operator for iterator.
		 */
		bool operator!=(const iterator &rhs) const {
			return (nodePoint != rhs.nodePoint);
		}
		bool operator!=(const const_iterator &rhs) const {
			return (nodePoint != rhs.nodePoint);
		}

		/**
		 * for the support of it->first. 
		 * See <http://kelvinh.github.io/blog/2013/11/20/overloading-of-member-access-operator-dash-greater-than-symbol-in-cpp/> for help.
		 */
		const value_type* operator->() const noexcept {
			return nodePoint -> data;
		}

			// And other methods in iterator.
			// And other methods in iterator.
			// And other methods in iterator.

	};
	/**
	 * TODO two constructors
	 */
	
	node *head;
	node *beginNode;
	node *endNode;
	Compare cmp;
	
	map() {
		head = NULL;
		endNode = new node;
		beginNode = endNode;
	}
	map(const map &other) {
		if(other.head == NULL){
			endNode = new node;
			beginNode = endNode;
			head = NULL;
			return;
		}
		//std::cout << "copy map " << std::endl;
		head = new node;
		head -> data = new value_type(*(other.head -> data));
		head -> size = other.head -> size;
		head -> height = other.head -> height;
		endNode = new node;
		copyNode(head, other.head);
		node *tmpNode = NULL;
		makeSort(head, tmpNode);
		tmpNode -> next = endNode;
		endNode -> prev = tmpNode; 
	}
	/**
	 * TODO assignment operator
	 */
	map & operator=(const map &other) {
		if(this == &other){
			return *this;
		}
		clear();
		if(other.head == NULL){
			return *this;
		}
		head = new node;
		head -> data = new value_type(*(other.head -> data));
		head -> size = other.head -> size;
		head -> height = other.head -> height;
		copyNode(head, other.head);
		node *tmpNode = NULL;
		makeSort(head, tmpNode);
		tmpNode -> next = endNode;
		endNode -> prev = tmpNode; 
		return *this;
	}
	/**
	 * TODO Destructors
	 */
	~map() {
		//std::cout << "~map" << std::endl;
		clear();
		delete endNode;
	}
	/**
	 * TODO
	 * access specified element with bounds checking
	 * Returns a reference to the mapped value of the element with key equivalent to key.
	 * If no such element exists, an exception of type `index_out_of_bound'
	 */
	
	T & at(const Key &key) {
		node *p = findNode(key);
		if(p == NULL){
			throw index_out_of_bound();
		}
		return p -> data -> second;
	}
		
	const T & at(const Key &key) const {
		node *p = findNode(key);
		if(p == NULL){
			throw index_out_of_bound();
		}
		return p -> data -> second;
	}	
	/**
	 * TODO
	 * access specified element 
	 * Returns a reference to the value that is mapped to a key equivalent to key,
	 *   performing an insertion if such key does not already exist.
	 */
	T & operator[](const Key &key) {
		node *p = insert(pair<Key, T>(key, T())).first.nodePoint;
		return (p -> data -> second);
	}
	/**
	 * behave like at() throw index_out_of_bound if such key does not exist.
	 */
	const T & operator[](const Key &key) const {
		return at(key);
	}
	/**
	 * return a iterator to the beginNodening
	 */
	iterator begin() {
		return iterator(beginNode, this);
	}
	const_iterator cbegin() const {
		return const_iterator(beginNode, this);
	}
	/**
	 * return a iterator to the endNode
	 * in fact, it returns past-the-endNode.
	 */
	iterator end() {
		return iterator(endNode, this);
	}
	const_iterator cend() const {
		return const_iterator(endNode, this);
	}
	/**
	 * checks whether the container is empty
	 * return true if empty, otherwise false.
	 */
	bool empty() const {
		return head == NULL;
	}
	/**
	 * returns the number of elements.
	 */
	size_t size() const {
		if(head == NULL){
			return 0;
		}
		else{
			return head -> size;
		}
	}
	/**
	 * clears the contents
	 */
	void clear() {
		clearNode(head);
		delete endNode;
		endNode = new node;
		beginNode = endNode;
		head = NULL;

	}
	
	void clearNode(node *t){		
		if(t == NULL){
			return;
		}
		clearNode(t -> left);
		clearNode(t -> right);

		delete t;

	}
	/**
	 * insert an element.
	 * return a pair, the first of the pair is
	 *   the iterator to the new element (or the element that prevented the insertion), 
	 *   the second one is true if insert successfully, or false.
	 */
	pair<iterator, bool> insert(const value_type &value) {
		node *p = findNode(value.first);
		if(p != NULL){
			return pair<iterator, bool>(iterator(p, this), false);
		}
		p = insertNode(value, head);
		if(head -> size == 1){
			head -> next = endNode;
			endNode -> prev = head;
			beginNode = head;
		}
		return pair<iterator, bool>(iterator(p, this), true);
	}

	node* insertNode(const value_type &value, node *&t){
		node *tmp;
		if(t == NULL){
			t = new node;
			t -> data = new value_type(value);
			return t;
		}
		else{
			if(cmp(value.first, t -> data -> first)){
				int flag = 0;
				if(t -> left == NULL){
					flag = 1;
				}
				tmp = insertNode(value, t -> left);
				if(flag == 1){
					tmp -> next = t;
					tmp -> prev = t -> prev;
					t -> prev = tmp;
					
					if(tmp -> prev == NULL){
						beginNode = tmp;
					}
					else{
						tmp -> prev -> next = tmp;
					}
				}

				t -> height = maxx(high(t -> left), high(t -> right)) + 1;
				t -> size = calSize(t -> left) + calSize(t -> right) + 1;

				if(high(t -> left) - high(t -> right) == 2){
					if(cmp(value.first, t -> left -> data -> first)){
						LL(t);
					}
					else{
						LR(t);
					}
				}
				return tmp;
			}
			else{	
				int flag = 0;
				if(t -> right == NULL){
					flag = 1;
				}	

				tmp = insertNode(value, t -> right);
				if(flag == 1){
					tmp -> prev = t;
					tmp -> next = t -> next;
					t -> next = tmp;
					tmp -> next -> prev = tmp;
				}

				t -> height = maxx(high(t -> left), high(t -> right)) + 1;
				t -> size = calSize(t -> left) + calSize(t -> right) + 1;

				if(high(t -> right) - high(t -> left) == 2){
					if(cmp(value.first, t -> right -> data -> first)){
						RL(t);
					}
					else{
						RR(t);
					}
				}
				return tmp;
			}

		}

	}
	/**
	 * erase the element at pos.
	 *
	 * throw if pos pointed to a bad element (pos == this->endNode() || pos points an element out of this)
	 */
	void erase(iterator pos) {
		//std::cout << "erase" << std::endl;
		if(pos.mapId != this){
			throw invalid_iterator();
		}
		if(pos.nodePoint == NULL){
			throw invalid_iterator();
		}
		if(pos.nodePoint -> data == NULL){
			throw invalid_iterator();
		}
		remove(pos.nodePoint, head);
	}

	void remove(node *obj, node *&t){
		if(t == NULL){
			//std::cout << "NULL" << std::endl;
			return;
		}
		
		if(cmp(obj -> data -> first, t -> data -> first)){
			remove(obj, t -> left);
			if(high(t -> right) - high(t -> left) == 2){
				if(t -> right -> left != NULL && high(t -> right -> left) > high(t -> right -> right)){
					RL(t);
				}
				else{
					RR(t);
				}
			}
		}
		else{
			if(cmp(t -> data -> first, obj -> data -> first)){
				remove(obj, t -> right);
                if(high(t -> left) - high(t -> right) == 2 ){
                    if(t -> left -> right != NULL && high(t -> left -> right) > high(t -> left -> left)){
                        LR(t);
                    }
                    else{
                        LL(t);
                    }
				}
			}
			else{
				if(t -> left != NULL && t -> right != NULL){
					//std::cout << "l != NULL  R != NULL" << std::endl;
					node *exNode = t -> next;
					int temp;
					temp = t -> height;
					t -> height = exNode -> height;
					exNode -> height = temp;

					temp = t -> size;
					t -> size = exNode -> size;
					exNode -> size = temp;

					node *tmp;
					if(exNode != t -> right){
						tmp = t -> right;
						while(tmp -> left != exNode){
							tmp = tmp -> left;
						}
						tmp -> left = t;
						tmp = exNode -> right;
						exNode -> right = t -> right;
						t -> right = tmp;
						exNode -> left = t -> left;
						t -> left = NULL;
					}
					else{
						//std::cout << "shan you" << std::endl;
						t -> right = exNode -> right;
						exNode -> left = t -> left;
						exNode -> right = t;
						t -> left = NULL;
					}

					tmp = t;
					t = exNode;
					exNode = tmp;
					remove(exNode, t -> right);
					t -> height = maxx(high(t -> left), high(t -> right)) + 1;
					t -> size = calSize(t -> left) + calSize(t -> right) + 1;
					if(high(t -> left) - high(t -> right) == 2 ){
						if(t -> left -> right != NULL && high(t -> left -> right) > high(t -> left -> left)){
							LR(t);
						}
						else{
							LL(t);
						}

					}
				}
				else{
					//std::cout << "shan" << std::endl;
					node *p = t;
					if(t == beginNode){
						beginNode = beginNode -> next;
						beginNode -> prev = NULL;
					}
					else{
						t -> prev -> next = t -> next;
						t -> next -> prev = t -> prev;
					}
					if(t -> left == NULL && t -> right == NULL){
						//std::cout << "shan only jiedian" << std::endl;
						delete p;
						t = NULL;
						return;
					}
					
					if(t -> left != NULL){
						//std::cout << "l" << std::endl;
						t = t -> left;
					}
					else{
						//std::cout << "R" << std::endl;
						t = t -> right;
					}
					delete p;
					
				}
			}
		}
		t -> height = maxx(high(t -> left), high(t -> right)) + 1;
		t -> size = calSize(t -> left) + calSize(t -> right) + 1;
	}
	/**
	 * Returns the number of elements with key 
	 *   that compares equivalent to the specified argument,
	 *   which is either 1 or 0 
	 *     since this container does not allow duplicates.
	 * The default method of check the equivalence is !(a < b || b > a)
	 */
	size_t count(const Key &key) const {
		
		if(findNode(key) == NULL){
			return 0;
		}
		else{
			return 1;
		}
	}
	/**
	 * Finds an element with key equivalent to key.
	 * key value of the element to search for.
	 * Iterator to an element with key equivalent to key.
	 *   If no such element is found, past-the-endNode (see endNode()) iterator is returned.
	 */
	iterator find(const Key &key) {
		node *p = findNode(key);
		if(p == NULL){
			return end();
		}
		return iterator(p, this);
	}
	const_iterator find(const Key &key) const {
		node *p = findNode(key);
		if(p == NULL){
			return cend();
		}
		return const_iterator(p, this);
	}



	void copyNode(node *now, node * obj){
		if(obj -> left != NULL){
			now -> left = new node;
			now -> left -> data = new value_type(*(obj -> left -> data));
			now -> left -> height = obj -> left -> height;
			now -> left -> size = obj -> left -> size;
			copyNode(now -> left, obj -> left);
		}
		if(obj -> right != NULL){
			now -> right = new node;
			now -> right -> data = new value_type(*(obj -> right -> data));
			now -> right -> height = obj -> right -> height;
			now -> right -> size = obj -> right -> size;
			copyNode(now -> right, obj -> right);
		}
	}

	void makeSort(node *now, node *&tmp){
		if(now -> left != NULL){
			makeSort(now -> left, tmp);
		}
		if(tmp == NULL){
			beginNode = now;
		}
		now -> prev = tmp;
		if(tmp != NULL){
			tmp -> next = now;
		}
		tmp = now;
		if(now -> right != NULL){
			makeSort(now -> right, tmp);
		}
	}

	node *findNode(const Key &x) const{
		return findNode(x, head);
	}

	node *findNode(const Key &x, node *t) const {
		if(t == NULL){
			return NULL;
		}
		if(cmp(t -> data -> first, x)){
			return findNode(x, t -> right);
		}
		else{
			if(cmp(x, t -> data -> first)){
				return findNode(x, t -> left);
			}
			else{
				return t;
			}
		}
		
	}

	int high(node *t){
		if(t == NULL){
			return 0;
		}
		else{
			return t -> height;
		}
	}

	int calSize(node *t){
		if(t == NULL){
			return 0;
		}
		else{
			return t -> size;
		}
	}

	int maxx(int a, int b){
		if(a > b){
			return a;
		}
		else{
			return b;
		}
	}

	void LL(node *&t){
		//std::cout << "LL" << std::endl;
		node *t1 = t -> left;
		t -> left = t1 -> right;
		t1 -> right = t;
		t -> height = maxx(high(t -> left), high(t -> right)) + 1;
		t -> size = calSize(t -> left) + calSize(t -> right) + 1;
		t1 -> height = maxx(high(t1 -> left), high(t -> right)) + 1;
		t1 -> size = calSize(t1 -> left) + calSize(t1 -> right) + 1;
		t = t1;

	}

	void RR(node *&t){
		//std::cout << "RR" << std::endl;
		node *t1 = t -> right;
		t -> right = t1 -> left;
		t1 -> left = t;
		t -> height = maxx(high(t -> left), high(t -> right)) + 1;
		t -> size = calSize(t -> left) + calSize(t -> right) + 1;
		t1 -> height = maxx(high(t1 -> left), high(t -> right)) + 1;
		t1 -> size = calSize(t1 -> left) + calSize(t1 -> right) + 1;
		t = t1;
	}

	void LR(node *&t){
		RR(t -> left);
		LL(t);
	}

	void RL(node *&t){
		LL(t -> right);
		RR(t);
	}

};

}

#endif
