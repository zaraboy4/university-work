#ifndef _LINKED_LIST_HPP
#define _LINKED_LIST_HPP



/*	        
	 ___________
	|/|  |
	|_____|_____|
	 data   next
*/
template <typename T>
struct LinkedListElement {
	T data;
	LinkedListElement<T>* next;
};

//    LinkedList
template <typename T>
class LinkedList;

//    
template <typename T>
class LinkedListIterator {
	//           
	using LLE = LinkedListElement<T>;
	using I = LinkedListIterator<T>;

	//       
	friend LinkedList<T>;

	//      ptr  
	LLE* ptr;
public:
	//        
	LinkedListIterator(LLE* pos = nullptr) : ptr(pos) {}

	//        
	I next() const {
		//      
		if (!valid()) {
			//     
			return *this;
		}
		//    ,        
		return I(ptr->next);
	}

	//    (         )
	bool valid() const {
		return ptr != nullptr;
	}

	//          
	T const& getConst() const {
		return ptr->data;
	}

	T& get() const {
		return ptr->data;
	}

	//  
	// it <=> it.valid();
	operator bool() const {
		return valid();
	}

	// ++it
	I& operator++() {
		return (*this = next());
	}

	// it++
	I operator++(int) {
		I saved = *this;
		++(*this);
		return saved;
	}

    I& operator+=(unsigned int n) {
        for (int i = 0; i < n; ++i) {
            ++(*this);
        }
        return *this;
    }

	// *it = 3;
	T& operator*() {
		return get();
	}

	// T data = *it;
	T const& operator*() const {
		return getConst();
	}
	//   
	// it1 == it2
	bool operator==(I const& it) const {
		return ptr == it.ptr;
	}

	// it1 != it2
	bool operator!=(I const& it) const {
		return !(*this == it);
	}
};

//     
template <typename T>
class LinkedList {
public:
	//   I    LinkedListIterator<T>
	using I = LinkedListIterator<T>;
	using Type = T;

private:
	using LLE = LinkedListElement<T>;

	//       
	LLE* front, * back;

    void del();
public:
	//   ,
    I begin() const { return I(front); }
    I end() const { return I(); }    
    I last() const { return I(back); }    

	LinkedList() : front(nullptr), back(nullptr) {}
    ~LinkedList() { del(); }
    bool empty() const { return !front && !back; }
    bool insertBack(const T& el) { return insertAfter(last(), el); }
    bool insertAfter(const I& it, const T& el) {
        if (empty()) {
            front = back = new LLE { el, nullptr };
            return true;
        }
        if (!it) return false;
        it.ptr->next = new LLE { el, it.ptr->next };
        if (back == it.ptr) {
            back = back->next;
        }
        return true;
    }
	unsigned int InsertAfterNInterval(I& it, unsigned int n, const T& el) {
        unsigned int cnt = 0;
        n += 1;
        while (it) {
            insertAfter(it, el);
            ++cnt;
            it += n;
        }
        return cnt;
    }

};

template <class T>
void LinkedList<T>::del() {
    LLE* toDel;
    while (front) {
        toDel = front;
        front = front->next;
        delete toDel;
    }
    back = front;
}

#endif