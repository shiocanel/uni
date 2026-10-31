#pragma once
#include "repository.h"
#include "undo.h"
#include <memory>
#include <vector>
#include <algorithm>

class Service {
private:
    Repository& repo;
    vector<unique_ptr<ActiuneUndo>> undoStack;
    vector<unique_ptr<ActiuneUndo>> redoStack;

    void clearRedo() {
        redoStack.clear();
    }

public:
    Service(Repository& repo) : repo{ repo } {}

    vector<Masina> getSortedByNrInmatriculare() {
        auto ans = repo.getAll();
        sort(ans.begin(), ans.end(), [](const Masina& a, const Masina& b) {
            return a.getNrInmatriculare() < b.getNrInmatriculare();
            });
        return ans;
    }

    void modificaAn(int delta) {
        repo.modificaAnTuturor(delta);
        undoStack.push_back(make_unique<UndoAnFabricatie>(repo, delta));
        clearRedo();
    }

    void stergeMasini(const vector<string>& numereInmatriculare) {
        vector<Masina> masiniSterse;
        for (const string& nr : numereInmatriculare) {
            masiniSterse.push_back(repo.getByNrInmatriculare(nr));
            repo.sterge(nr);
        }
        undoStack.push_back(make_unique<UndoSterge>(repo, masiniSterse));
        clearRedo();
    }

    void undo() {
        if (undoStack.empty())
            throw runtime_error("Nu se mai poate face undo!");
        auto actiune = move(undoStack.back());
        undoStack.pop_back();
        actiune->doUndo();
        redoStack.push_back(move(actiune));
    }

    void redo() {
        if (redoStack.empty())
            throw runtime_error("Nu se mai poate face redo!");
        auto actiune = move(redoStack.back());
        redoStack.pop_back();
        actiune->doRedo();
        undoStack.push_back(move(actiune));
    }
};