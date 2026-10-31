#pragma once
#include <string>

using namespace std;

class Postare {
private:
	int codPostare;
	string creator;
	string tipContinut;
	string platforma;
public:
	/*
	Constuctor pentru Postare
	codPostare : int
	creator : string
	tipContinut : string
	platforma : string
	*/
	Postare(int codPostare, string creator, string tipContinut, string platforma) :
		codPostare{ codPostare }, creator{ creator }, tipContinut{ tipContinut }, platforma{platforma} {
	}

	/*
	functie de geter pentru codPostare
	return: codPostare (int)
	*/
	int getCodPostare() const {
		return codPostare;
	}

	/*
	functie de geter pentru creator
	return: creator (string)
	*/
	string getCreator() const {
		return creator;
	}

	/*
	functie de geter pentru tipContinut
	return: tipContinut (string)
	*/
	string getTipContinut() const {
		return tipContinut;
	}

	/*
	functie de geter pentru platforma
	return: platforma (string)
	*/
	string getPlatforma() const {
		return platforma;
	}
};