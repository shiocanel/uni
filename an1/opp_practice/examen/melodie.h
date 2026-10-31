#pragma once
#include <string>

using namespace std;

class Melodie {
private:
    int id;
    string titlu;
    string artist;
    int rank;

public:
    /*
    constructor clasei Melodie
    */
    Melodie(int id, string titlu, string artist, int rank) : id{ id }, titlu{ titlu }, artist{ artist }, rank{ rank } {}

    int getId() const { 
        /*
        getter pentru id
        return: id (int)
        */

        return id; 
    }
    string getTitlu() const { 
        /*
        getter pentru titlu
        return: titlu (string)
        */

        return titlu; 
    }
    string getArtist() const {
        /*
        getter pentru artist
        return: artist (string)
        */

        return artist; 
    }
    int getRank() const { 
        /*
        getter pentru rank
        return: rank (int)
        */

        return rank; 
    }

    void setTitlu(const string& titluNou) { 
        /*
        setter pentru titlu
        pre: titluNou (string)
        post: seteaza tilu la valoarea tiluNou
        */
        
        titlu = titluNou; 
    }
    void setRank(int rankNou) { 
        /*
        stter pentru rank
        pre: rankNou (int)
        post: seteaza rank la valoarea rankNou
        */
        rank = rankNou; 
    }
};