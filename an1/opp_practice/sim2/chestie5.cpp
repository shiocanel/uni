#include <iostream>
#include <string>

using namespace std;

class Channel {
public:
	virtual void send(const string& msg) = 0;
	virtual ~Channel() = default;
};

class FailOver : public Channel {
private:
	Channel* c1;
	Channel* c2;
public:
	FailOver(Channel* c1, Channel* c2) : c1{ c1 }, c2{ c2 } {}

	void send(const string& msg) override {
		try {
			c1->send(msg);
		}
		catch (std::exception e) {
			try {
				c2->send(msg);
			}
			catch (std::exception e) {

			}
		}
	}

	~FailOver() override {
		delete c1;
		delete c2;
	}
};

class Telefon : public Channel {
public:
	Telefon(int nrTel) {}
};

class Fax : public Telefon {
public:
	Fax(int nrTel) : Telefon(nrTel) {}

	void send(const string& msg) override {
		Telefon::send(msg);
		cout << "sending fax" << '\n';
	}
};

class Contact : public Channel {
private:
	Channel* c1;
	Channel* c2;
	Channel* c3;
public:
	Contact(Channel* c1, Channel* c2, Channel* c3) : c1{ c1 }, c2{ c2 }, c3{ c3 } {}

	void sendAlarm(const string& msg) {
	}

	~Contact() override {
		delete c1;
		delete c2;
		delete c3;
	}
};





template <typename T>
class Expresie {
private:
	T val;
	vector<T> istoric;
public:
	Expresie(T x) : val{ x } {
		istoric.push_back(x);
	}

	Expresie operator+(T op) const {
		Expresie copie(*this);

		copie.val += op;
		copie.istoric.push_back(copie.val);

		return copie;
	}

	Expresie operator-(T op) const {
		Expresie copie(*this);

		copie.val += op;
		copie.istoric.push_back(copie.val);

		return copie;
	}

	Expresie& undo() {
		if (istoric.size() > 1) {
			istoric.pop_back();
			val = istoric.back();
		}

		return *this;
	}

};