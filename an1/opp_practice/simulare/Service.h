#pragma once


#include "Repository.h"
#include <algorithm>

class Service {
private:
	Repository& repo;
public:

	/*
	Constrcutor pentru Service
	repo : Repository 
	*/
	Service(Repository& repo) : repo{ repo } {
	}

	/*
	Functie care returneaza toate postarile din repo
	repo.getAll() : vector<Postare>
	*/
	vector<Postare> getAll() {
		return repo.getAll();
	}

	/*
	functie care sorteaza si returneaza dupa creator crescator
	res : vector<Postare>
	*/
	vector<Postare> sortCreatorCresc() {
		vector<Postare> res = getAll();
		sort(res.begin(), res.end(), [&](Postare& a, Postare& b) {
			return a.getCreator() < b.getCreator();
			});

		return res;
	}

	/*
	functie care sorteaza si returneaza dupa creator descrescator
	res : vector<Postare>
	*/
	vector<Postare> sortCreatorDesc() {
		vector<Postare> res = getAll();
		sort(res.begin(), res.end(), [&](Postare& a, Postare& b) {
			return a.getCreator() > b.getCreator();
			});

		return res;
	}

	/*
	functie care sorteaza si returneaza dupa platforma crescator
	res : vector<Postare>
	*/
	vector<Postare> sortPlatformaCresc() {
		vector<Postare> res = getAll();
		sort(res.begin(), res.end(), [&](Postare& a, Postare& b) {
			return a.getPlatforma() < b.getPlatforma();
			});

		return res;
	}

	/*
	functie care sorteaza si returneaza dupa platforma descrescator
	res : vector<Postare>
	*/
	vector<Postare> sortPlatformaDesc() {
		vector<Postare> res = getAll();
		sort(res.begin(), res.end(), [&](Postare& a, Postare& b) {
			return a.getPlatforma() > b.getPlatforma();
			});

		return res;
	}

	/*
	functie care returneaza o descriere dupa tipul de platforma
	ans : string
	*/
	string getDescrierePlatforma(string platforma) {
		string ans = "";
		if (platforma == "TikTok")
			ans = "Platforma pentru videoclipuri scurte si trebduri virale";
		else if (platforma == "Instagram")
			ans = "Platforma pentru reels, stories, si postari vizuale";
		else if (platforma == "Youtube Shorts")
			ans = "Platforma pentru videoclipuri scurte pentru copii";
		else if (platforma == "Twitch")
			ans = "Platforma pentru continut LIVE";
		else
			ans = "?????";

		return ans;
	}
};
