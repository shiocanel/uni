#pragma once

template <typename T>
class IteratorVector;

template <typename T>
class VectorDinamic {
private:
    int cp;
    int dim;
    T* elems;

    void resize() {
        cp *= 2;
        T* aux = new T[cp];
        for (int i = 0; i < dim; i++) {
            aux[i] = elems[i];
        }
        delete[] elems;
        elems = aux;
    }

public:
    VectorDinamic() : cp{ 2 }, dim{ 0 }, elems{ new T[2] } {}

    VectorDinamic(const VectorDinamic& ot) : cp{ ot.cp }, dim{ ot.dim }, elems{ new T[ot.cp] } {
        for (int i = 0; i < dim; i++) {
            elems[i] = ot.elems[i];
        }
    }

    VectorDinamic& operator=(const VectorDinamic& ot) {
        if (this == &ot) 
            return *this;
        
        delete[] elems;
        cp = ot.cp;
        dim = ot.dim;
        elems = new T[cp];
        for (int i = 0; i < dim; i++) {
            elems[i] = ot.elems[i];
        }
        return *this;
    }

    ~VectorDinamic() {
        delete[] elems;
    }

    void push_back(const T& el) {
        if (dim == cp) 
            resize();
        elems[dim++] = el;
    }

    void erase(int pos) {
        if (pos < 0 || pos >= dim) 
            return;
        
        for (int i = pos; i < dim - 1; i++) {
            elems[i] = elems[i + 1];
        }
        
        dim--;
    }

    T& operator[](int pos) const {
        return elems[pos];
    }

    int size() const {
        return dim;
    }

    IteratorVector<T> begin() const {
        return IteratorVector<T>(*this);
    }

    IteratorVector<T> end() const {
        return IteratorVector<T>(*this, dim);
    }
};

template <typename T>
class IteratorVector {
private:
    const VectorDinamic<T>& vec;
    int poz;

public:
    IteratorVector(const VectorDinamic<T>& v) noexcept : vec{ v }, poz{ 0 } {}
    IteratorVector(const VectorDinamic<T>& v, int p) noexcept : vec{ v }, poz{ p } {}

    bool operator!=(const IteratorVector& ot) noexcept { 
        return poz != ot.poz; 
    }
    
    void operator++() noexcept { 
        poz++; 
    }

    T& operator*() { 
        return vec[poz]; 
    }
};