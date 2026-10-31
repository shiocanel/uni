// ex1
/*
functia gaseste si returneaza 2 cele mai mari elemente pozitive
pre: vectorul l primit ca parametru trebuie sa contina cel putin 2 elemente
post: functia returneaza un obiect pair<int, int> unde first este cel mai mare element si second al doilea
cel mai mare element. Daca preconditia nu este respectata atunci functia arunca o exceptie de tipul: std::exception
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <exception>

using namespace std;

std::pair<int, int> f(vector<int> l) {
	
}

void test() {
	bool ok = false;
	try {
		f({1});
	}
	catch (const std::exception& e) {
		ok = true;
	}
	assert(ok == true);

	pair<int, int> ans = f({ 2, 1, -1 });
	assert(ans == make_pair(1, 2));
}






#include <string>

class Meniu {
private:
	int pret;
public:
	Meniu(int pret) : pret{ pret } {}

	virtual string descriere() = 0;
	virtual int getPret() {
		return pret;
	}

	virtual ~Meniu() = default;
};

class CuCafea : public Meniu{
private:
	Meniu* meniu;
public:
	CuCafea(Meniu* meniu) : Meniu(meniu->getPret()), meniu{ meniu } {}

	string descriere() override {
		return meniu->descriere() + " cu cafea";
	}
	int getPret() override {
		return meniu->getPret() + 5;
	}

	~CuCafea() override{
		delete meniu;
	}
};

class CuRacoritoare : public Meniu {
private:
	Meniu* meniu;
public:
	CuRacoritoare(Meniu* meniu) : Meniu(meniu->getPret()), meniu{ meniu } {}

	string descriere() override {
		return meniu->descriere() + " cu racoritoare";
	}

	int getPret() override {
		return meniu->getPret() + 4;
	}

	~CuRacoritoare() override {
		delete meniu;
	}
};

class MicDejun : public Meniu {
private:
	string denumire;
public:
	MicDejun(string denumire, int pret) : Meniu(pret), denumire{ denumire } {}
	string descriere() override {
		return denumire;
	}
};

vector<Meniu*> creeaza() {
	vector<Meniu*> comenzi;

	comenzi.push_back(new CuCafea(new CuRacoritoare(new MicDejun("Omleta", 15))));
	comenzi.push_back(new CuCafea(new MicDejun("Ochiuri", 10)));
	comenzi.push_back(new MicDejun("Omleta", 15));

	return comenzi;
}

void solve() {
	vector<Meniu*> lista = creeaza();

	sort(lista.begin(), lista.end(), [](Meniu* a, Meniu* b)	{
		return a->getPret() > b->getPret();
		});

	for (auto* m : lista)
		cout << m->descriere() << ' ' << m->getPret() << '\n';

	for (auto* m : lista)
		delete m;
}


// ex4

template <typename T>
class Measurements {
private:
	T val;
public:
	Measurements(T val) : val{ val } {}

	Measurements<T>& operator+(const T& x) {
		this->val += x;
		return *this;
	}

	bool operator<(const Measurements<T>& a) const {
		return this->val < a.val();
	}

	T value() const {
		return this->val;
	}
};