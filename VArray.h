//Group 8
//Lee Quan Sheng [S10198298], Eugene Long [S10193060J]

// ! Featured !

// VArray

// A custom Dynamic Array data structure template
// class for general use in the application. It
// sees widespread use within many other Abstract
// Data Types such as BHPriorityQueue and VHashMap

// Its resize function doubles the underlying array
// capacity on hitting the limit.

// This data structure performs similarly to the 
// vector class in C++ on a best effort basis.

#ifndef varray_h
#define varray_h

template <typename T>
class VArray {
friend class Proxy;
private:    
    int size;
    int capacity;
    T* items;

public:
    // Proxy class for [] operators
    class Proxy {
        friend class VArray;
        private:
            VArray& varray;
            int index;
        public:
            // uses an initialisation list to load values into proxy variables before constructor/methods run
            Proxy(VArray& varray, int index) : varray(varray), index(index) {}

            // operators
            operator T() const; // rvalue get
            Proxy& operator=(T value); // set
    };

    VArray();
    VArray(int initialSize, int initialCapacity);
    ~VArray();
    void resize();

    //Adds object to the VArray
    //pre: None
    //Post: None
    void push(T item);
    
    //Adds object at the indicated positon to the VArray
    //pre: None
    //Post: The new item is insert inbetween to the index
    void push(T item, int index);

    //Replace object at the indcated positon to the VArray
    //pre: None
    //Post: The new item is replaced to the index
    void set(T item, int index);

    //Gets object from the VArray
    //pre: None
    //Post: None
    T& get(int index);

    //Remove object from the VArray
    //pre: None
    //Post: The object is removed from the VArray
    void remove(int index);

    //Gets the size of the VArray
    //pre: None
    //Post: None
    int getSize();

    //Gets the capacity of the VArray
    //pre: None
    //Post: None
    int getCapacity();

    //Display object of the VArray
    //pre: None
    //Post: None
    void print();

    // operator methods
    T& operator[](int index) const; // rvalue get
    Proxy operator[](int index); // cast to proxy for other operands
};

#endif