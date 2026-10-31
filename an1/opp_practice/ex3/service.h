#pragma once


#include "repository.h"

class Service {
private:
	Repository& repo;

	string to_lower(string s) {
		string res;
		for (auto i : s)
			res.push_back(tolower(i));
		return res;
	}

	bool contains(string s, string t) {
		string x = to_lower(s);
		string y = to_lower(t);

		return x.find(y) != string::npos;

	}

public:
	Service(Repository& repo) : repo{ repo } {
	}

	vector<Produs> getAll() {
		return repo.getAll();
	}

	vector<string> getCategorii() {
		set<string> categorii;

		for (Produs& produs : getAll())
			categorii.insert(produs.getCategorie());

		return vector<string>(categorii.begin(), categorii.end());
	}

	vector<Produs> filtrareCategorie(string categorie) {
		if (categorie == "Toate")
			return getAll();

		vector<Produs> ans;
		for (Produs& produs : getAll()) {
			if (produs.getCategorie() == categorie)
				ans.push_back(produs);
		}

		return ans;
	}

	vector<Produs> cautaDenumire(string denumire, vector<Produs> aux) {
		vector<Produs> ans;
		for (Produs produs : aux)
			if (contains(produs.getDenumire(), denumire))
				ans.push_back(produs);

		return ans;
	}

	vector<Produs> cautaSiFiltreaza(string categorie, string denumire) {
		vector<Produs> ans = filtrareCategorie(categorie);
		ans = cautaDenumire(denumire, ans);

		return ans;
	}
};