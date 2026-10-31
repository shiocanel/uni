#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Smoothy {
private:
    int pret;
public:
    Smoothy(int pret) : pret{ pret } {}
    virtual int getPret() {
        return pret;
    }

    virtual string descriere() = 0; // pur virtuala
    virtual ~Smoothy() = default;
};

class DecoratorSmoothy : public Smoothy {
protected:
    Smoothy* smoothy;
public:
    DecoratorSmoothy(Smoothy* smoothy) : Smoothy(smoothy->getPret()), smoothy{ smoothy } {} // asa iei functia de la parinte

    int getPret() override { // o suprascrii
        return smoothy->getPret();
    }
    string descriere() override {
        return smoothy->descriere();
    }
    ~DecoratorSmoothy() override {
        delete smoothy;
    }
};

class SmoothyCuFrisca : public DecoratorSmoothy {
public:
    SmoothyCuFrisca(Smoothy* smoothy) : DecoratorSmoothy(smoothy) {}
    int getPret() override {
        return DecoratorSmoothy::getPret() + 2;
    }
    string descriere() override {
        return DecoratorSmoothy::descriere() + " cu frisca!";
    }
};

class BasicSmoothy : public Smoothy {
private:
    string nume;
public:
    BasicSmoothy(string nume, int pret) : Smoothy(pret), nume{ nume } {};
    string descriere() override {
        return nume;
    }
};

class SmoothyCuUmbreluta : public DecoratorSmoothy {
public:
    SmoothyCuUmbreluta(Smoothy* smoothy) : DecoratorSmoothy(smoothy) {}
    int getPret() override {
        return DecoratorSmoothy::getPret() + 3;
    }
    string descriere() override {
        return DecoratorSmoothy::descriere() + " cu umbreluta!";
    }
};

vector<Smoothy*> creeazaLista() {
    vector<Smoothy*> lista;

    lista.push_back(new SmoothyCuFrisca(new SmoothyCuUmbreluta(new BasicSmoothy("kivi", 10))));
    lista.push_back(new SmoothyCuFrisca(new BasicSmoothy("capsuni", 20)));
    lista.push_back(new BasicSmoothy("kivi", 5));

    return lista;
}

void solve() {
    vector<Smoothy*> bauturi = creeazaLista();

    sort(bauturi.begin(), bauturi.end(), [](Smoothy* a, Smoothy* b) {
        return a->descriere() < b->descriere();
        });

    for (auto* s : bauturi)
        cout << s->descriere() << " " << s->getPret() << " RON\n";

    for (auto* s : bauturi)
        delete s;
}









template <typename T>
class Geanta {
private:
    string proprietar;
    vector<T> obiecte;
public:
    Geanta(string proprietar) : proprietar{ proprietar } {}

    Geanta<T>& operator+(const T& element) {
        obiecte.push_back(element);
        return *this;
    }

    auto begin() const {
        return obiecte.begin();
    }

    auto end() const {
        return obiecte.end();
    }
};