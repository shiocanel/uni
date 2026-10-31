#pragma once
#include <vector>
#include <fstream>
#include <sstream>

#include "Postare.h"

using namespace std;

class Repository {
private:
	vector<Postare> postari;

	/*
	functie care citeste dintr-un fisier
	fileName : string;
	*/
	void readFromFile(string fileName) {
		ifstream fin(fileName);
		if (!fin.is_open())
			throw runtime_error("Nu s-a deschis fisierul");

		string line;
		while (getline(fin, line)) {
			string codPostare, creator, tipContinut, platforma;
			stringstream ss(line);

			getline(ss, codPostare, ';');
			getline(ss, creator, ';');
			getline(ss, tipContinut, ';');
			getline(ss, platforma, ';');

			Postare postare(stoi(codPostare), creator, tipContinut, platforma);
			postari.push_back(postare);
		}
	}
public:
	/*
	Constructor pentru Repository
	fileName : string
	*/
	Repository(string fileName) {
		readFromFile(fileName);
	}

	/*
	functie care returneaza toate postarile
	postari : vector<>
	*/
	vector<Postare> getAll() {
		return postari;
	}
};
