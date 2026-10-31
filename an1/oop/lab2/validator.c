#include "validator.h"
#include <string.h>

/*
 * verifica daca datele furnizate pentru un produs sunt corecte conform regulilor de business.
 * pre: id, name, model, producer, price, quantity - datele ce urmeaza a fi validate.
 * post: returneaza 1 daca toate datele sunt valide, sau 0 daca cel putin un parametru este invalid.
 */
int validateProduct(int id, char* name, char* model, char* producer, double price, int quantity) {
	if (id < 0) 
		return -1;
	if (name == NULL || strlen(name) == 0) 
		return -1;
	if (model == NULL || strlen(model) == 0) 
		return -1;
	if (producer == NULL || strlen(producer) == 0) 
		return -1;
	if (price <= 0) 
		return -1;
	if (quantity < 0) 
		return -1;

	return 1;
}
