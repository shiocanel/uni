#pragma once
#include <algorithm>

#include "undo.h"

class Service {
private:
	Repository& repo;
	vector<unique_ptr<ActiuneUndo>> undoStack;
	vector<unique_ptr<ActiuneUndo>> redoStack;

	void clearRedo() {
		redoStack.clear();
	}
public:
	Service(Repository& repo) : repo{ repo } {

	}

	vector<Student> getSortedByVarsta() {
		auto ans = repo.getAll();
		sort(ans.begin(), ans.end(), [](const Student& a, const Student& b) {
			return a.getVarsta() < b.getVarsta();
			});

		return ans;
	}

	void modificaVarsta(int delta) {
		repo.modificaVarstaTuturor(delta);
		undoStack.push_back(make_unique<UndoVarsta>(repo, delta));
		clearRedo();
	}

	void stergeStudenti(const vector<int>& nrMatricole) {
		vector<Student> studentiStersi;
		for (int nr : nrMatricole) {
			studentiStersi.push_back(repo.getByNr(nr));
			repo.sterge(nr);
		}

		undoStack.push_back(make_unique<UndoSterge>(repo, studentiStersi));
		clearRedo();
	}

	void undo() {
		if (undoStack.empty())
			throw runtime_error("Nu se mai poate face undo");

		auto actiune = move(undoStack.back());
		undoStack.pop_back();
		actiune->doUndo();
		redoStack.push_back(move(actiune));
	}

	void redo() {
		if (redoStack.empty())
			throw runtime_error("Nu se mai poaate face redo");

		auto actiune = move(redoStack.back());
		redoStack.pop_back();
		actiune->doRedo();
		undoStack.push_back(move(actiune));
	}
};