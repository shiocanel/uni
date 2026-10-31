#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Mancare {
private:
	int pret;
public:
	Mancare(int pret) : pret{ pret } {}

	virtual string descriere() = 0;
	virtual int getPret() {
		return pret;
	}

	virtual ~Mancare() = default;
};

class Burger : public Mancare {
private:
	string denumire;
public:
	Burger(string denumire, int pret) : Mancare(pret), denumire { denumire } {}

	string descriere() override {
		return denumire;
	}
};

class CuSos : public Mancare {
private:
	Mancare* mancare;
public:
	CuSos(Mancare* mancare) : Mancare(mancare->getPret()), mancare{ mancare } {}

	string descriere() override {
		return mancare->descriere() + " cu sos";
	}

	int getPret() override {
		return mancare->getPret() + 2;
	}
};

class CuCartof : public Mancare {
private:
	Mancare* mancare;
public:
	CuCartof(Mancare* mancare) : Mancare(mancare->getPret()), mancare{ mancare } {}

	string descriere() override {
		return mancare->descriere() + " cu cartof";
	}

	int getPret() override {
		return mancare->getPret() + 3;
	}
};

vector<Mancare*> creeaza() {
	vector<Mancare*> res;
	res.push_back(new Burger("McPuisor", 10));
	res.push_back(new CuCartof(new CuSos(new Burger("BigTasty", 10))));
	res.push_back(new CuCartof(new Burger("Booster", 20)));

	return res;
}

#include <algorithm>

void solve() {
	vector<Mancare*> lista = creeaza();

	sort(lista.begin(), lista.end(), [](Mancare* a, Mancare* b) {
		return a->getPret() > b->getPret();
		});

	for (Mancare* x : lista)
		cout << x->descriere() << ' ' << x->getPret() << '\n';

	for (Mancare* x : lista)
		delete x;
}















template <typename T>
class Sesiune {
private:
	vector<string>* partecipanti;
public:
	Sesiune(vector<string>* p) : partecipanti{ p } {}

	Seisune& operator+(const string& nume) {
		if (partecipanti)
			partecipanti->push_back(nume);
		return *this;
	}

	auto begin() const {
		return partecipanti->begin();
	}
	auto end() const {
		return partecipanti->end();
	}

	vector<string> select(const string& subsir) {
		vector<string> res;
		if (partecipanti) {
			for (const auto& nume : *partecipanti)
				if (nume.find(subsir) != string::npos)
					res.push_back(nume);
		}
		return res;
	}
};

template <typename T>
class Conferinta {
private:
	map<string, vector<string>> date_tracks;
public:
	Sesiune track(const string& nume) {
		return sesiune(&date_tracks[nume]);
	}
};
