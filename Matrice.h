//
// Created by Jacopo on 02/08/2018.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template<typename t>
class Matrice {
private:
    int numRighe, numColonne;
    t *elementi;
public:
    //Costruttori
    Matrice(int numRighe, int numColonne);

    Matrice(int numRighe, int numColonne, t *valori);

    Matrice(const Matrice<t> &matrice);

    ~Matrice();

    //Metodi getter e setter
    int getNumColonne() const;

    int getNumRighe() const;

    t getElemento(int indiceRiga, int indiceColonna) const throw(out_of_range);

    Matrice<t> getRiga(int indiceRiga) const throw(out_of_range);

    Matrice<t> getColonna(int indiceColonna) const throw(out_of_range);

    void setElemento(int indiceRiga, int indiceColonna, const t &elemento) throw(out_of_range);

    void setElementi(const t &elemento);// setta tutti gli elementi della matrice al valore di elemento
    void setRiga(int indiceRiga, Matrice<t> riga) throw(out_of_range, invalid_argument);

    void setColonna(int indiceColonna, Matrice<t> colonna) throw(out_of_range, invalid_argument);

    //Metodi aggiuntivi
    void inserisciRiga(int posizione, Matrice<t> riga) throw(out_of_range, invalid_argument);

    void inserisciColonna(int posizione, Matrice<t> colonna) throw(out_of_range, invalid_argument);

    void rimuoviRiga(int indiceRiga) throw(out_of_range);

    void rimuoviColonna(int indiceColonna) throw(out_of_range);

    //Override Operatori
    Matrice<t> operator=(const Matrice<t> &matrice);

    Matrice<t> operator+(const Matrice<t> &matrice) const throw(invalid_argument);

    Matrice<t> operator-(const Matrice<t> &matrice) const throw(invalid_argument);

    Matrice<t> operator*(const Matrice<t> &matrice) const throw(invalid_argument);

    Matrice<t> operator*(const t &scalare);//moltiplicazione per scalare
    bool operator==(const Matrice &matrice) const;

    bool operator!=(const Matrice &matrice) const;

    const t &operator()(int indiceRiga, int indiceColonna) const throw(out_of_range);

    t &operator()(int indiceRiga, int indiceColonna) throw(out_of_range);

    Matrice<t> trasposta() const;

    Matrice<t> sottoMatrice(int rigaEsclusa, int colonnaEsclusa) const throw(logic_error, out_of_range);

    t determinante() const throw(logic_error);

    //toString
    string toString() const;
};

#endif //MATRIX_MATRIX_H
