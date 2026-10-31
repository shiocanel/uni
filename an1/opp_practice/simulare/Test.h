#pragma once
#include <cassert>

#include "Service.h"

/*
functie de test pentru Postare.h
*/
void testPostare() {
	Postare postare(10, "creator", "tipContinut", "platforma");
	assert(postare.getCodPostare() == 10);
	assert(postare.getCreator() == "creator");
	assert(postare.getTipContinut() == "tipContinut");
	assert(postare.getPlatforma() == "platforma");
}

/*
functie de test pentru Repository.h si Serrvice.h
*/
void testRepoService() {
	try {
		Repository repo("dskjndkj.txt");
	}
	catch (...) {
	}

	Repository repo("postari.txt");
	Service service{ repo };

	vector<Postare> res = service.getAll();
	assert(res.size() == 10);


	vector<Postare> aux = service.sortCreatorCresc();
	assert(aux[0].getCreator() == "Ana");

	aux = service.sortCreatorDesc();
	assert(aux[0].getCreator() == "Zandrei");


	aux = service.sortPlatformaCresc();
	assert(aux[0].getPlatforma() == "Instagram");

	aux = service.sortPlatformaDesc();
	assert(aux[0].getPlatforma() == "Youtube Shorts");

	assert(service.getDescrierePlatforma("TikTok") == "Platforma pentru videoclipuri scurte si trebduri virale");
	assert(service.getDescrierePlatforma("Instagram") == "Platforma pentru reels, stories, si postari vizuale");
	assert(service.getDescrierePlatforma("Youtube Shorts") == "Platforma pentru videoclipuri scurte pentru copii");
	assert(service.getDescrierePlatforma("Twitch") == "Platforma pentru continut LIVE");
	assert(service.getDescrierePlatforma("fdjndskjn") == "?????");
}

/*
functie care ruleaza toate testele
*/
void testAll() {
	testPostare();
	testRepoService();
}