/*
 * LSE.h
 *
 *  Created on: 19 de out. de 2022
 *      Author: Administrador
 */

#ifndef LSE_H_
#define LSE_H_

#include "No.h"

class LSE {

private:
	No *cabeca;
	int nElementos;

	bool insereInicioLista(int valor);
	bool insereMeioLista(int pos, int valor);

	int removeInicioLista();
	int removeNaLista(int pos);

public:
	LSE();
	virtual ~LSE();

	bool vazia();
	bool cheia();
	int tamanho();
	int elemento(int pos);
	int posicao (int valor);
	int posicao (int valor, int desloc);
	bool insere (int pos, int valor);
	int remove(int pos);

};

#endif /* LSE_H_ */
