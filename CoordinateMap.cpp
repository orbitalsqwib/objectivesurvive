//Team members - Lee Quan Sheng and Eugene Long
//Group 8

#include "CoordinateMap.h"
#include "VHashMap.cpp"
#include "Vec2D.h"

template <typename T>
CoordinateMap<T>::CoordinateMap() : VHashMap<Vec2D, T>(144+1) {}
// 144+1 is a square grid 12 tiles wide, the default board size

template <typename T>
CoordinateMap<T>::~CoordinateMap() {
    // Destructor.
}

template <typename T>
int CoordinateMap<T>::hash(Vec2D pos) {
    return ( (int) pos ) % getCapacity();
}

template <typename T>
void CoordinateMap<T>::add(Vec2D key, T val) {
    VHashMap<Vec2D, T>::add(key, val);
}

template <typename T>
void CoordinateMap<T>::remove(Vec2D key) {
    VHashMap<Vec2D, T>::remove(key);
}

template <typename T>
void CoordinateMap<T>::set(Vec2D key, T val) {
    VHashMap<Vec2D, T>::set(key, val);
}

template <typename T>
T* CoordinateMap<T>::get(Vec2D key) {
    return VHashMap<Vec2D, T>::get(key);
}

template <typename T>
bool CoordinateMap<T>::isEmpty() {
    return VHashMap<Vec2D, T>::isEmpty();
}

template <typename T>
int CoordinateMap<T>::getSize() {
    return VHashMap<Vec2D, T>::getSize();
}

template <typename T>
int CoordinateMap<T>::getCapacity() {
    return VHashMap<Vec2D, T>::getCapacity();
}