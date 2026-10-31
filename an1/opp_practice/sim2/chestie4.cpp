#include <iostream>
#include <vector>

using namespace std;

class Transformer {
public:
	virtual void transform(vector<int>& nrs) = 0;

	virtual ~Transformer() = default;
};

class Composite : public Transformer {
private:
	Transformer* t1;
	Transformer* t2;
public:
	Composite(Transformer* t1, Transformer* t2) : t1{ t1 }, t2{ t2 } {}

	void transform(vector<int>& nrs) override {
		t1->transform(nrs);
		t2->transform(nrs);
	}

	~Composite() override {
		delete t1;
		delete t2;
	}
};

class Adder : public Transformer {
protected:
	int cat;
public:
	Adder(int cat) : cat{ cat } {}

	void transform(vector<int>& nrs) {
		for (auto& x : nrs)
			x += cat;
	}
};

class Nuller : public Adder {
public:
	Nuller(int c) : Adder(c) {}

	void transform(vector<int>& nrs) override {
		for (auto& x : nrs) {
			if (x + cat < 10)
				x = 0;
			else
				x += cat;
		}
	}
};

class Swapper : public Transformer {
public:
	void transform(vector<int>& nrs) override {
		for (int i = 0; i < nrs.size() - 1; i += 2)
			swap(nrs[i], nrs[i + 1]);
	}
};

class Numbers : public Transformer {
private:
	Transformer* t;
	vector<int> nrs;
public:
	Numbers(Transformer* t) : t{ t } {}

	void add(int x) {
		
	}

	~Numbers() {
		delete t;
	}
};







class Examen {
private:
	string nume;
	string ora;
public:
	Examen(string nume, string ora) : nume{ nume }, ora{ ora } {}

	string getDescriere() {
		return nume + " " + ora;
	}
};

template <typename T>
class ToDo {
private:
	vector<T> list;
public:
	ToDo& operator<<(const T& obj) {
		list.push_back(obj);
		return *this;
	}

	void printToDoList(ostream& out) {
		out << "De facut: \n";
		for (const auto& x : list)
			out << x.getDescriere() << '\n';
	}
};