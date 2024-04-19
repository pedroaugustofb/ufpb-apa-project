/*
 * No.h
 *
 *  Created on: 19 de out. de 2022
 *      Author: Administrador
 */

#ifndef NO_H_
#define NO_H_

class No {

private:
	int conteudo;
	No *prox;

public:
	No();
	virtual ~No();

	int getConteudo();
	No *getProx();

	void setConteudo(int conteudo);
	void setProx(No *prox);


};

#endif /* NO_H_ */
