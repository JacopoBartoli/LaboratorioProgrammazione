//
// Created by Jacopo on 11/09/2018.
//

#include "gtest/gtest.h"
#include "../Matrice.cpp"

TEST(Matrix, Constructor) {
    const int defValue = 11;
    Matrice<int> m(3, 6);
    m.setElementi(defValue);
    ASSERT_EQ(m.getNumRighe(), 3);
    ASSERT_EQ(m.getNumColonne(), 6);
    ASSERT_EQ(m.getElemento(1, 1), defValue);
    ASSERT_EQ(m.getElemento(2, 3), defValue);
}

TEST(Matrix, Operators) {
    Matrice<int> m1(4, 3), m2(3, 2), m3(4, 3), m4(4, 3), m5(4, 2);
    m1.setElementi(0);
    m2.setElementi(1);
    m3.setElementi(0);
    m4.setElementi(0);
    m5.setElementi(0);
    m1.setElemento(3, 2, 4);
    m3.setElemento(3, 2, 4);

    // operator ==
    ASSERT_EQ(m1, m3);

    // operator !=
    ASSERT_NE(m1, m2);
    m3.setElemento(1, 1, 1);
    ASSERT_NE(m1, m3);

    // operator =
    m1 = m3;
    ASSERT_EQ(m1, m3);

    // operator -
    ASSERT_EQ(m1 - m3, m4);
    ASSERT_THROW(m1 - m2, std::invalid_argument);

    // operator +
    m4.setElemento(3, 2, 8);
    m4.setElemento(1, 1, 2);
    ASSERT_EQ(m1 + m3, m4);
    ASSERT_THROW(m1 + m2, std::invalid_argument);

    // operator * (scalar)
    m4.setElemento(3, 2, 20);
    m4.setElemento(1, 1, 5);
    ASSERT_EQ(m1 * 5, m4);

// operator *
    ASSERT_THROW(m1 * m3, std::invalid_argument);
    m2.setElemento(2, 1, 2);
    m5.setElemento(1, 0, 1);
    m5.setElemento(1, 1, 1);
    m5.setElemento(3, 0, 4);
    m5.setElemento(3, 1, 8);
    ASSERT_EQ(m1 * m2, m5);

    // operator ()
    ASSERT_EQ(m1.getElemento(3, 1), m1(3, 1));
    ASSERT_THROW(m1(3, 3), std::out_of_range);
    m1(1, 2) = 12;
    ASSERT_EQ(m1(1, 2), 12);


}

TEST(Matrix, Transpose) {
    Matrice<float> mat(3, 2);
    mat.setElementi(0);
    mat.setElemento(1, 1, 1);
    mat.setElemento(2, 1, 3);
    Matrice<float> trMat = mat.trasposta();

    ASSERT_EQ(trMat.getNumRighe(), 2);
    ASSERT_EQ(trMat.getNumColonne(), 3);
    ASSERT_EQ(trMat.getElemento(0, 0), 0);
    ASSERT_EQ(trMat.getElemento(1, 1), 1);
    ASSERT_EQ(trMat.getElemento(1, 2), 3);
}

TEST(Matrix, SubMatrix) {
    Matrice<int> mat(4, 3);
    mat.setElementi(1);
    mat.setElemento(0, 0, 0);
    mat.setElemento(2, 0, 3);
    mat.setElemento(1, 1, 4);
    mat.setElemento(3, 2, 5);

    Matrice<int> subMat = mat.sottoMatrice(2, 1);
    ASSERT_EQ(subMat.getElemento(0, 0), 0);
    ASSERT_EQ(subMat.getElemento(1, 1), 1);
    ASSERT_EQ(subMat.getElemento(2, 1), 5);
}

TEST(Matrix, Determinant) {
    Matrice<int> errMat(1, 2);
    ASSERT_THROW(errMat.determinante(), std::logic_error);

    Matrice<int> mat(3, 3);
    mat.setElementi(1);
    mat.setElemento(0, 0, 3);
    mat.setElemento(1, 1, 4);
    mat.setElemento(1, 2, 6);
    mat.setElemento(2, 1, 9);
    ASSERT_EQ(mat.determinante(), -140);
}

TEST(Matrix, RowsAndColumns) {
    //inserisci riga
    Matrice<int> m(2, 3);
    m.setElementi(0);
    int riga[3] = {1, 1, 1};
    m.inserisciRiga(0, Matrice<int>(1, 3, riga));
    ASSERT_EQ(m.getNumRighe(), 3);
    ASSERT_EQ(m(0, 1), 1);

    //setRiga
    riga[1] = 5;
    m.setRiga(1, Matrice<int>(1, 3, riga));
    ASSERT_EQ(m(1, 1), 5);

    //getRiga
    m(0, 1) = 13;
    Matrice<int> mat = m.getRiga(0);
    ASSERT_EQ(mat.getNumColonne(), 3);
    ASSERT_EQ(mat(0, 1), 13);

    //rimuoviRiga
    m.rimuoviRiga(0);
    ASSERT_EQ(m(0, 1), 5);

    //inserisciColonna
    Matrice<int> m2(2, 3);
    m2.setElementi(0);
    int colonna[2] = {5, 7};
    m2.inserisciColonna(2, Matrice<int>(2, 1, colonna));
    ASSERT_EQ(m2(1, 2), 7);
    ASSERT_EQ(m2.getNumColonne(), 4);

    //setColonna
    colonna[0] = 3;
    m2.setColonna(0, Matrice<int>(2, 1, colonna));
    ASSERT_EQ(m2(0, 0), 3);

    //getColonna
    m2(1, 2) = 5;
    Matrice<int> mat2 = m2.getColonna(2);
    ASSERT_EQ(mat2.getNumRighe(), 2);
    ASSERT_EQ(mat2(1, 0), 5);

    //rimuoviColonna
    m2(0, 2) = 8;
    m2.rimuoviColonna(1);
    ASSERT_EQ(m2(0, 1), 8);
}
TEST(Matrix, toString){
    Matrice<int> m1(2,3),m2(2,3),m3(3,1);
    m1.setElementi(0);
    m2.setElementi(1);
    m3.setElementi(0);
    ASSERT_NE(m1.toString(),m2.toString());
    ASSERT_NE(m1.toString(),m3.toString());
    m2.setElementi(0);
    ASSERT_EQ(m1.toString(),m2.toString());


}

