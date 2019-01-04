//
// Created by Jacopo on 02/08/2018.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template<typename T>
class Matrice {
public:
    //Costruttori
    Matrice(int numRighe, int numColonne);

    Matrice(int numRighe, int numColonne, T *valori);

    Matrice(const Matrice<T> &matrice);

    ~Matrice();

    //Metodi getter e setter
    int getNumColonne() const;

    int getNumRighe() const;

    T getElemento(int indiceRiga, int indiceColonna) const throw(out_of_range);

    Matrice<T> getRiga(int indiceRiga) const throw(out_of_range);

    Matrice<T> getColonna(int indiceColonna) const throw(out_of_range);

    void setElemento(int indiceRiga, int indiceColonna, const T &elemento) throw(out_of_range);

    void setElementi(const T &elemento);// setta tutti gli elementi della matrice al valore di elemento
    void setRiga(int indiceRiga, Matrice<T> riga) throw(out_of_range, invalid_argument);

    void setColonna(int indiceColonna, Matrice<T> colonna) throw(out_of_range, invalid_argument);

    //Metodi aggiuntivi
    void inserisciRiga(int posizione, Matrice<T> riga) throw(out_of_range, invalid_argument);

    void inserisciColonna(int posizione, Matrice<T> colonna) throw(out_of_range, invalid_argument);

    void rimuoviRiga(int indiceRiga) throw(out_of_range);

    void rimuoviColonna(int indiceColonna) throw(out_of_range);

    //Override Operatori
    Matrice<T> operator=(const Matrice<T> &matrice);

    Matrice<T> operator+(const Matrice<T> &matrice) const throw(invalid_argument);

    Matrice<T> operator-(const Matrice<T> &matrice) const throw(invalid_argument);

    Matrice<T> operator*(const Matrice<T> &matrice) const throw(invalid_argument);

    Matrice<T> operator*(const T &scalare);//moltiplicazione per scalare
    bool operator==(const Matrice &matrice) const;

    bool operator!=(const Matrice &matrice) const;

    const T &operator()(int indiceRiga, int indiceColonna) const throw(out_of_range);

    T &operator()(int indiceRiga, int indiceColonna) throw(out_of_range);

    Matrice<T> trasposta() const;

    Matrice<T> sottoMatrice(int rigaEsclusa, int colonnaEsclusa) const throw(logic_error, out_of_range);

    T determinante() const throw(logic_error);

    //toString
    string toString() const;

private:
    int numRighe, numColonne;
    T *elementi;
};

#endif //MATRIX_MATRIX_H
