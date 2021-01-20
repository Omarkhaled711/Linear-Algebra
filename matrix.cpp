#include "matrix.h"
#include <iostream>

using namespace std;
matrix::matrix()
{
    cout << endl<<"Please enter the matrix dimensions(note:Enter an augmented matrix if you want to solve a system of linear equations)"<<endl;
    cin >> r;
    cin >> c;
    cout << endl << "Enter the numbers" << endl;
    mat = new double* [r];
    elementary = new double* [r];
    for (int i = 0; i < r; i++) {
        mat[i] = new double[c];
        elementary[i] = new double[r];
    }
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++)
            cin >> mat[i][j];
    }
}
void matrix::getmat() {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
}
void matrix::sub_mat(matrix m2, matrix m1) {
    if (m1.r == m2.r && m1.c == m2.c) {
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++)
                mat[i][j] = m2.mat[i][j] - m1.mat[i][j];
        }
        cout << "The solution is.." << endl;
        getmat();
    }
    else
        cout << "Dimensions error";
}
void matrix::add_mat(matrix m2, matrix m1) {
    if (m1.r == m2.r && m1.c == m2.c) {
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++)
                mat[i][j] = m2.mat[i][j] + m1.mat[i][j];
        }
        cout << "The solution is.." << endl;
        getmat();
    }
    else
        cout << "Dimensions error";
}
void matrix::scaler_mult(int num) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++)
            mat[i][j] = num * mat[i][j];
    }
    cout << "The solution is.." << endl;
    getmat();
}

void matrix::mult(matrix m1, matrix m2) {
    if (m1.c == m2.r) {
        double** mat1;
        mat1 = new double* [m1.r];
        for (int i = 0; i < m1.r; i++)
            mat1[i] = new double[m2.c];
        float sum = 0.0;
        for (int i = 0; i < m1.r; i++) {
            for (int j = 0; j < m2.c; j++) {
                for (int k = 0; k < m1.c; k++) {
                    sum += m1.mat[i][k] * m2.mat[k][j];
                }
                mat1[i][j] = sum;
                sum = 0;
            }
        }
        cout << "The solution is.." << endl;
        for (int i = 0; i < m1.r; i++) {
            for (int j = 0; j < m2.c; j++)
                cout << mat1[i][j] << " ";
            cout << endl;
        }
        for (int i = 0; i < m1.r; i++)
            delete[]mat1[i];
        delete[]mat1;

    }
    else
        cout << "Dimensions error" << endl;

}


double matrix::det() {
    if (r == c) {
        if (r == 1)
        {
            return mat[0][0];
        }
        else if (r == 2)
        {
            return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
        }
        else if (r == 3) {
            return (mat[0][0] * (mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2])) - (mat[0][1] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0])) + (mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]));
        }
        else {
            double sum = 0;
            double** z;
            z = new double* [r];
            for (int i = 0; i < r; i++)
                z[i] = new double[r];
            sum= det(mat, r);
            for (int i = 0; i < r; i++)
                delete[] z[i];
            delete[] z;
            return sum;
        }
    }
    else {
        cout << "Error..Please enter an NxN matrix"<<endl;
        return false;
    }
}

double matrix::det(double** z, int p) {
    double sum = 0, product;
    if(p == 3) {
        sum=(z[0][0] * (z[1][1] * z[2][2] - z[2][1] * z[1][2])) - (z[0][1] * (z[1][0] * z[2][2] - z[1][2] * z[2][0])) + (z[0][2] * (z[1][0] * z[2][1] - z[1][1] * z[2][0]));
    }
    else {
        int sign = 1, n ,row;
        double** inner,member;
        inner = new double* [p-1];
        for (int i = 0; i < p-1; i++)
            inner[i] = new double[p-1];
        for (int i = 0; i < p; i++) {
            row=0;
            n = 0;
            for (int j = 0; j < p; j++) {
                for (int k = 0; k < p; k++) {
                    member = z[j][k];
                    if ((j == 0 ) || (k == i));
                    else {
                        inner[row][n] = member;
                        n = n + 1;
                        if (n == p - 1) {
                            n = 0;
                            row += 1;
                        }
                    }
                }
            }
            product = sign * z[0][i] * det(inner, p - 1);
            sum += product;
            sign = sign * -1;
        }
        for (int i = 0; i < p-1; i++)
            delete[] inner[i];
        delete[] inner;
    }
    return sum;
}
void matrix::memory() {
    for (int i = 0; i < r; i++) {
        delete[] mat[i];
        delete[]elementary[i];
    }
    delete [] mat;
    delete[]elementary;
}
void matrix::I()
{
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < r; j++) {
            if (i == j)
                elementary[i][j] = 1;
            else
                elementary[i][j] = 0;
        }
    }
}
void matrix::solve()
{
    int cl;
    if (r + 1 < c) {
        cout << "The equations don't have a unique solution" << endl;
    }
    else {
        cl = c;
        c = r;
        if (det() == 0) {
            cout << "The equations don't have a unique solution" << endl;
        }
        else {
            I();
            double** mat1;
            mat1 = new double* [r];
            for (int i = 0; i < r; i++)
                mat1[i] = new double[cl];
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < cl; j++)
                    mat1[i][j] = mat[i][j];
            }
            
            //making sure not to divide by zero by interchanging rows
            for (int j = 0; j < r; j++) {
                if (mat[j][j] == 0) {
                    for (int k = 0; k < r; k++) {
                        if (mat[k][j] != 0 ) {
                            for (int i = 0; i < cl; i++) {
                                mat[j][i] = mat1[k][i];
                                mat[k][i] = mat1[j][i];
                            }
                            for (int i = 0; i < cl; i++) {
                                mat1[j][i] = mat[j][i];
                                mat1[k][i] = mat[k][i];
                            }
                            k = r;
                        }
                    }
                }
            }
            for (int i = 0; i < r; i++) {
                for (int z = 0; z < r; z++) {
                    for (int j = 0; j < cl; j++)
                        mat[z][j] = mat1[z][j]; //saving all changes in the matrix
                }
                for (int j = 0; j < cl; j++){
                    mat1[i][j] = (mat[i][j] / mat[i][i]);
                    if (j < r)
                        elementary[i][j] = (elementary[i][j] / mat[i][i]);
                }
                for (int k = 0; k < r; k++) {
                    for (int j = 0; j < cl; j++) {
                        if (k == i);
                        else {
                            mat1[k][j] = (mat1[i][j] * -1 * mat[k][i]) + mat1[k][j];
                            if (j < r)
                                elementary[k][j] = (elementary[i][j] * -1 * mat[k][i]) + elementary[k][j];
                        }

                    }
                }

            }
            for (int i = 0; i < r; i++) {
                cout << "X" << i + 1 << " = " << mat1[i][cl - 1] << endl;
            }
            cout << "The inverse matrix is.." << endl;
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < r; j++)
                    cout << elementary[i][j] << " ";
                cout << endl;
            }
            for (int i = 0; i < r; i++)
                delete[]mat1[i];
            delete[]mat1;
        }
    }
}



matrix::~matrix()
{
}

