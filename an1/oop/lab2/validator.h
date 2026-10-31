#ifndef VALIDATOR_H
#define VALIDATOR_H

/*
 * verifica daca datele furnizate pentru un produs sunt corecte conform regulilor de business.
 * pre: id, name, model, producer, price, quantity - datele ce urmeaza a fi validate.
 * post: returneaza 1 daca toate datele sunt valide, sau 0 daca cel putin un parametru este invalid.
 */
int validateProduct(int id, char* name, char* model, char* producer, double price, int quantity);

#endif // !VALIDATOR_H
