//
// Created by Jacopo on 03/09/2018.
//

#include "Matrice.h"


//Constructor delegation
template<typename t>
Matrice<t>::Matrice(int numRighe, int numColonne) : numRighe(numRighe), numColonne(numColonne),
                                                    elementi(new t[numRighe * numColonne]) {}

template<typename t>
Matrice<t>::Matrice(int numRighe, int numColonne, t *valori) : Matrice(numRighe, numColonne) {
    for (int i = 0; i < numRighe * numColonne; i++) {
        elementi[i] = valori[i];
    }
}

template<typename t>
Matrice<t>::Matrice(const Matrice<t> &matrice) : Matrice(matrice.numRighe, matrice.numColonne) {
    for (int col = 0; col < numColonne; col++) {
        for (int riga = 0; riga < numRighe; riga++) {
            elementi[col + (riga * numColonne)] = matrice.elementi[col + (riga * numColonne)];
        }
    }
}

template<typename t>
Matrice<t>::~Matrice() {
    delete[]elementi;
}

template<typename t>
int Matrice<t>::getNumColonne() const {
    return numColonne;
}

template<typename t>
int Matrice<t>::getNumRighe() const {
    return numRighe;
}

template<typename t>
t Matrice<t>::getElemento(int indiceRiga, int indiceColonna) const throw(out_of_range) {
    if (indiceRiga < 0 || indiceRiga >= numRighe || indiceColonna < 0 || indiceColonna >= numColonne)
        throw out_of_range("Indici non validi");
    return elementi[indiceColonna + (indiceRiga * numColonne)];
}

template<typename t>
Matrice<t> Matrice<t>::getRiga(int indiceRiga) const throw(out_of_range) {
    if (indiceRiga < 0 || indiceRiga >= numRighe)
        throw out_of_range("Indice non valido");
    Matrice<t> output(1, numColonne);
    for (int i = 0; i < numColonne; i++) {
        output(0, i) = (*this)(indiceRiga, i);
    }
    return output;
}

template<typename t>
Matrice<t> Matrice<t>::getColonna(int indiceColonna) const throw(out_of_range) {
    if (indiceColonna < 0 || indiceColonna >= numColonne)
        throw out_of_range("Indice non valido");
    Matrice<t> output(numRighe, 1);
    for (int i = 0; i < numRighe; i++) {
        output(i, 0) = (*this)(i, indiceColonna);
    }
    return output;
}

template<typename t>
void Matrice<t>::setElemento(int indiceRiga, int indiceColonna, const t &elemento) throw(out_of_range) {
    if (indiceRiga < 0 || indiceRiga >= numRighe || indiceColonna < 0 || indiceColonna >= numColonne)
        throw out_of_range("Indici non validi");
    elementi[indiceColonna + (indiceRiga * numColonne)] = elemento;
}

//Assegna ad ogni componente di elementi il valore passato come parametro alla funzione
template<typename t>
void Matrice<t>::setElementi(const t &elemento) {
    for (int i = 0; i < numRighe * numColonne; i++)
        elementi[i] = elemento;
}

template<typename t>
void Matrice<t>::setRiga(int indiceRiga, Matrice<t> riga) throw(out_of_range, invalid_argument) {
    if (indiceRiga < 0 || indiceRiga >= numRighe)
        throw out_of_range("Indice non valido");
    if (numColonne != riga.numColonne || riga.numRighe != 1)
        throw invalid_argument("Matrice di dimensoni non valide");
    for (int i = 0; i < numColonne; i++)
        (*this)(indiceRiga, i) = riga(0, i);
}

template<typename t>
void Matrice<t>::setColonna(int indiceColonna, Matrice<t> colonna) throw(out_of_range, invalid_argument) {
    if (indiceColonna < 0 || indiceColonna >= numColonne)
        throw out_of_range("Indice non valido");
    if (numRighe != colonna.numRighe || colonna.numColonne != 1)
        throw invalid_argument("Matrice di dimensioni non valide");
    for (int i = 0; i < numRighe; i++) {
        (*this)(i, indiceColonna) = colonna(i, 0);
    }
}

template<typename t>
void Matrice<t>::inserisciRiga(int posizione, Matrice<t> riga) throw(out_of_range, invalid_argument) {
    if (posizione < 0 || posizione > numRighe)
        throw out_of_range("Indice non valido");
    if (numColonne != riga.numColonne || riga.numRighe != 1)
        throw invalid_argument("Matrice di dimensioni non valide");
    t *newElementi = new t[++numRighe * numColonne];
    for (int i = 0; i < numRighe * numColonne; i++) {
        int indiceRiga = i / numColonne;
        if (indiceRiga < posizione)
            newElementi[i] = elementi[i];
        else if (indiceRiga == posizione)
            newElementi[i] = riga(0, i % numColonne);
        else
            newElementi[i] = elementi[i - numColonne]; //copio il resto della matrice considerando che i è più lungo
        //di una riga rispetto alla matrice precedente
    }
    delete[](elementi);
    elementi = newElementi;
}

template<typename t>
void Matrice<t>::inserisciColonna(int posizione, Matrice<t> colonna) throw(out_of_range, invalid_argument) {
    if (posizione < 0 || posizione > numColonne)
        throw out_of_range("Indice non valido");
    if (numRighe != colonna.numRighe || colonna.numColonne != 1)
        throw invalid_argument("Matrice di dimensioni non valide");
    t *newElementi = new t[numRighe * ++numColonne];
    for (int i = 0; i < numRighe * numColonne; i++) {
        int indiceRiga = i / numColonne;
        int indiceColonna = i % numColonne;
        if (indiceColonna < posizione)
            newElementi[i] = elementi[i - indiceRiga];// tiene conto che dalla seconda linea in poi i sarà maggiore
            // a causa dell'inserimento
        else if (indiceColonna == posizione)
            newElementi[i] = colonna(indiceRiga, 0);
        else
            newElementi[i] = elementi[i - (indiceRiga +
                                           1)];// tiene conto che oltre a quelli inseriti nelle righe precedenti
        // c'è un elemento inserito nella riga corrente
    }
    delete[](elementi);
    elementi = newElementi;

}

template<typename t>
void Matrice<t>::rimuoviRiga(int indiceRiga) throw(out_of_range) {
    if (indiceRiga < 0 || indiceRiga >= numRighe)
        throw out_of_range("Indice non valido");
    t *newElementi = new t[--numRighe * numColonne];
    for (int i = 0; i < numRighe * numColonne; i++) {
        if (i / numColonne < indiceRiga)
            newElementi[i] = elementi[i];
        else
            newElementi[i] = elementi[i + numColonne];
    }
    delete[](elementi);
    elementi = newElementi;
}

template<typename t>
void Matrice<t>::rimuoviColonna(int indiceColonna) throw(out_of_range) {
    if (indiceColonna < 0 || indiceColonna >= numColonne)
        throw out_of_range("Indice non valido");
    t *newElementi = new t[numRighe * --numColonne];
    for (int i = 0; i < numRighe * numColonne; i++) {
        int indiceRiga = i / numColonne;
        if (i % (numRighe + 1) < indiceColonna)
            newElementi[i] = elementi[i + indiceRiga];
        else
            newElementi[i] = elementi[i + 1 + indiceRiga];//ragionamento analogo al metodo inserisci colonna
    }
    delete[](elementi);
    elementi = newElementi;
}

template<typename t>
Matrice<t> Matrice<t>::operator=(const Matrice<t> &matrice) {
    if (this != &matrice) {
        this->~Matrice();
        numRighe = matrice.numRighe;
        numColonne = matrice.numColonne;
        elementi = new t[numRighe * numColonne];
        for (int i = 0; i < numRighe * numColonne; i++)
            elementi[i] = matrice.elementi[i];
    }
    return *this;
}

template<typename t>
Matrice<t> Matrice<t>::operator+(const Matrice<t> &matrice) const throw(invalid_argument) {
    if (numRighe != matrice.numRighe || numColonne != matrice.numColonne)
        throw invalid_argument("Dimensioni non coerenti");
    Matrice<t> risultato(numRighe, numColonne);
    for (int i = 0; i < numRighe * numColonne; i++) {
        risultato.elementi[i] = elementi[i] + matrice.elementi[i];
    }
    return risultato;
}

template<typename t>
Matrice<t> Matrice<t>::operator-(const Matrice<t> &matrice) const throw(invalid_argument) {
    if (numRighe != matrice.numRighe || numColonne != matrice.numColonne)
        throw invalid_argument("Dimensioni non coerenti");
    Matrice<t> risultato(numRighe, numColonne);
    for (int i = 0; i < numRighe * numColonne; i++) {
        risultato.elementi[i] = elementi[i] - matrice.elementi[i];
    }
    return risultato;
}

template<typename t>
Matrice<t> Matrice<t>::operator*(const Matrice<t> &matrice) const throw(invalid_argument) {
    if (numColonne != matrice.numRighe)
        throw invalid_argument("Dimensioni non coerenti");

    Matrice<t> risultato(numRighe, matrice.numColonne);
    risultato.setElementi(0);
    for (int riga = 0; riga < numRighe; riga++) {
        for (int colonna = 0; colonna < matrice.numColonne; colonna++) {
            for (int i = 0; i < numColonne; i++) {
                risultato.elementi[colonna + riga * matrice.numColonne] +=
                        elementi[i + riga * numColonne] * matrice.elementi[colonna + i * matrice.numColonne];
            }
        }
    }
    return risultato;
}

template<typename t>
Matrice<t> Matrice<t>::operator*(const t &scalare) {
    Matrice<t> risultato(numRighe, numColonne);
    for (int i = 0; i < numRighe * numColonne; i++)
        risultato.elementi[i] = elementi[i] * scalare;
    return risultato;
}

template<typename t>
bool Matrice<t>::operator==(const Matrice &matrice) const {
    if (numRighe != matrice.numRighe || numColonne != matrice.numColonne)
        return false;
    for (int i = 0; i < numColonne * numRighe; i++) {
        if (elementi[i] != matrice.elementi[i])
            return false;
    }
    return true;
}

template<typename t>
bool Matrice<t>::operator!=(const Matrice &matrice) const {
    return !(*this == matrice);
}

template<typename t>
const t &Matrice<t>::operator()(int indiceRiga, int indiceColonna) const throw(out_of_range) {
    if (indiceRiga < 0 || indiceRiga >= numRighe || indiceColonna < 0 || indiceColonna >= numColonne)
        throw out_of_range("Indici non validi");
    return elementi[indiceColonna + indiceRiga * numColonne];
}

template<typename t>
t &Matrice<t>::operator()(int indiceRiga, int indiceColonna) throw(out_of_range) {
    if (indiceRiga < 0 || indiceRiga >= numRighe || indiceColonna < 0 || indiceColonna >= numColonne)
        throw out_of_range("Indici non validi");
    return elementi[indiceColonna + indiceRiga * numColonne];
}

template<typename t>
Matrice<t> Matrice<t>::trasposta() const {
    Matrice<t> risultato(numColonne, numRighe);
    for (int riga = 0; riga < numRighe; riga++)
        for (int colonna = 0; colonna < numColonne; colonna++)
            risultato.elementi[riga + colonna * numRighe] = elementi[colonna + riga * numColonne];
    return risultato;
}

template<typename t>
Matrice<t> Matrice<t>::sottoMatrice(int rigaEsclusa, int colonnaEsclusa) const throw(logic_error, out_of_range) {
    if (numRighe <= 1 || numColonne <= 1)
        throw logic_error("Matrice troppo piccola");
    if (rigaEsclusa < 0 || rigaEsclusa >= numRighe || colonnaEsclusa < 0 || colonnaEsclusa >= numColonne)
        throw out_of_range("Indici non validi");
    Matrice<t> risultato(numRighe - 1, numColonne - 1);
    for (int colonna = 0; colonna < numColonne; colonna++) {
        if (colonna == colonnaEsclusa)
            continue;
        for (int riga = 0; riga < numRighe; riga++) {
            if (riga == rigaEsclusa)
                continue;
            int indice = (colonna > colonnaEsclusa ? colonna - 1 : colonna) +
                         (riga > rigaEsclusa ? riga - 1 : riga) * risultato.numColonne;
            risultato.elementi[indice] = elementi[colonna + riga * numColonne];
        }
    }
    return risultato;
}

template<typename t>
t Matrice<t>::determinante() const throw(logic_error) {
    if (numRighe != numColonne)
        throw logic_error("Matrice non quadrata");
    if (numRighe == 2)
        return elementi[0] * elementi[3] - elementi[1] * elementi[2];
    t determinante = 0;
    for (int colonna = 0; colonna < numColonne; colonna++)
        determinante += elementi[colonna] * sottoMatrice(0, colonna).determinante() * (colonna % 2 == 0 ? 1 : -1);
    return determinante;
}

template<typename t>
string Matrice<t>::toString() const {
    string stringa = "Matrice di" + to_string(numRighe) + "righe e " + to_string(numColonne) + " colonne\n";
    for (int riga = 0; riga < numRighe; riga++) {
        stringa += "\t";
        for (int colonna = 0; colonna < numColonne; colonna++)
            stringa += " " + to_string(elementi[colonna + riga * numColonne]);
        stringa += "\n";
    }
    return stringa;
}


