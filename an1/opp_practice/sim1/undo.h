#pragma once

#include "repository.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual void doRedo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoVarsta : public ActiuneUndo{
private:
	Repository& repo;
	int delta;
public:
	UndoVarsta(Repository& repo, int delta) : repo{ repo }, delta{ delta } {

	}

	void doUndo() override {
		repo.modificaVarstaTuturor(-delta);
	}

	void doRedo() override{
		repo.modificaVarstaTuturor(delta);
	}
};

class UndoSterge : public ActiuneUndo {
private:
	Repository& repo;
	vector<Student> stersi;
public:
	UndoSterge(Repository& rep, const vector<Student>& stersi) : repo{ repo }, stersi{ stersi } {

	}

	void doUndo() override {
		for (const auto& s : stersi) {
			repo.adauga(s);
		}
	}

	void doRedo() override {
		for (const auto& s : stersi) {
			repo.sterge(s.getNrMatrcol());
		}
	}
};