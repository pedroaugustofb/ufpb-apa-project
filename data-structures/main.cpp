#include <iostream>
#include "LSE.h"

using namespace std;

int main() {
	LSE minhaLista;
    bool ret;
    int dado;

    minhaLista = LSE();

    if (minhaLista.vazia() == true)
    	cout << "Lista inicialmente vazia!" << endl;
    else
    	cout << "Lista criada nao estava vazia!" << endl;

    minhaLista.insere(1, 10);
    minhaLista.insere(2, 20);
    minhaLista.insere(3, 30);
    minhaLista.insere(4, 40);

    minhaLista.insere(3, 25);
    minhaLista.insere(5, 35);

    cout << "\nLista apos 1as insercoes" << endl;
    for (int i = 1; i <= minhaLista.tamanho(); i++){
    	dado = minhaLista.elemento(i);
    	cout << (i) << "-esimo elemento da lista = " << dado << endl;
    }

    minhaLista.insere(2, 2000);
    ret = minhaLista.insere(1, 101);
    cout << "Insercao do 101 na posicao 1 = " << ret << endl;

    cout << "\nLista apos 2o grupo de insercoes" << endl;
    for (int i = 1; i <= minhaLista.tamanho(); i++){
        dado = minhaLista.elemento(i);
        cout <<  i << "-esimo elemento da lista = " << dado << endl;
    }

    ret = minhaLista.insere(20, 500);
    cout << "Insercao do 500 na posicao 20 = " << ret << endl;

    cout << "Pos do elemento 10 = " << minhaLista.posicao(10) << endl;
    cout << "Pos do elemento 30 = " << minhaLista.posicao(30) << endl;
    cout << "Pos do elemento 40 = " << minhaLista.posicao(40) << endl;
    cout << "Pos do elemento 15 = " << minhaLista.posicao(15) << endl;

    cout << "Tamanho = " << minhaLista.tamanho() << endl;

    dado = minhaLista.remove(3);
    cout << "\nDado removido = " << dado << "\n\n" << endl;

    cout << "Lista depois da 1a remocao \n" << endl;
    for (int i = 1; i <= minhaLista.tamanho(); i++){
        dado = minhaLista.elemento(i);
        cout << i << "-esimo elemento da lista = " << dado << endl;
    }

    dado = minhaLista.remove(6);
    cout << "\nDado removido = " << dado << "\n" << endl;

    cout << "Lista depois da remocao" << endl;
    for (int i = 0; i < minhaLista.tamanho(); i++){
        dado = minhaLista.elemento(i+1);
        cout << (i+1) << "-esimo elemento da lista = " << dado << endl;
    }

}
