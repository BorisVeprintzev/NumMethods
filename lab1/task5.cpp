// Made by Max Bronnikov

#include <vector>
#include <iostream>
#include "matrix.h"
#include <cmath>

using namespace std;

void ave(){
    cout << "============================================================" << endl;
    cout << "|                    LABORATORY WORK №1                    |" << endl;
    cout << "|                    NUMERICAL METHODS                     |" << endl;
    cout << "|                         Task №5                          |" << endl;
    cout << "|                       Variant №4                         |" << endl;
    cout << "|                                                          |" << endl;
    cout << "|                                Student: Bronnikov M.A.   |" << endl;
    cout << "|                                   Date: 24.02.2020       |" << endl;
    cout << "|                                                          |" << endl;
    cout << "|                                                          |" << endl;
    cout << "|                       Moscow, 2020                       |" << endl;
    cout << "============================================================" << endl;
}

void print_statement(const Matrix& A, double alfa){
    cout << "============================================================" << endl;
    cout << "|                      EXERCSICE:                          |" << endl;
    cout << "============================================================" << endl;
    cout << "|  We need to find values of matrix using QR separation.   |" << endl;
    cout << "============================================================" << endl;
    cout << "Matrix:" << endl;
    cout << A << endl;
    cout << "Accuracy: " << alfa << endl;
    cout << "=============================================================" << endl;
}

void bye(){
    cout << "============================================================" << endl;
    cout << "|                         EXIT                             |" << endl;
    cout << "============================================================" << endl;
}


void matrix_init(Matrix& A){
    A = Matrix(3, 3);
    A[0][0] = 8.0;
    A[0][1] = 2.0;
    A[0][2] = -1.0;

    A[1][0] = 2.0;
    A[1][1] = -5.0;
    A[1][2] = -8.0;

    A[2][0] = -1.0;
    A[2][1] = -8.0;
    A[2][2] = -5.0;
}


void print_vector_x(const vector<double>& x){
    for(unsigned i = 0; i < x.size(); ++i){
        cout << 'l' << i + 1 << " = " << x[i] << " ";
    }
    cout << endl;
}

void print_solution(const vector<double>& x, int itter){
    cout << "============================================================" << endl;
    cout << "|                      ANSWER:                             |" << endl;
    cout << "============================================================" << endl;
    cout << "Values:" << endl;
    print_vector_x(x);
    cout << "============================================================" << endl;
    cout << "Itterations: " << itter << endl;
    cout << "============================================================" << endl;
}

int rotate_method(const Matrix& A, Matrix& U, vector<double>& x, double alfa){
    if(!A.is_simmetric()){
        throw "Matrix not simmteric! Wrong!";
    }

    Matrix U_k(A.get_n(), A.get_m()), A_k = A;
    int i_max = 0, j_max = 0, itter = 0;
    double v_max = 0.0, fitta = 0.0, check = 0.0;

    U = Matrix(A.get_n(), A.get_m());
    U.make_ones();
    x.resize(A.get_m());

    do{
        U_k.make_ones();

        // search max elem in matrix: 
        v_max = 0.0;
        i_max = j_max = 0;
        for(int i = 0; i < A_k.get_n(); ++i){
            for(int j = i + 1; j < A_k.get_m(); ++j){
                if(v_max < abs(A_k[i][j])){
                    v_max = abs(A_k[i][j]);
                    i_max = i;
                    j_max = j;
                }
            }
        }

        // create U:
        fitta = A_k[i_max][i_max] == A_k[j_max][j_max] ? 
                M_PI_4 : 
                atan(2 * A_k[i_max][j_max] / (A_k[i_max][i_max] - A_k[j_max][j_max])) / 2;

        U_k[i_max][j_max] = -sin(fitta);
        U_k[i_max][i_max] = cos(fitta);
        U_k[j_max][j_max] = cos(fitta);
        U_k[j_max][i_max] = sin(fitta);

        // multiply:
        // U for vectors
        U = U * U_k;

        // A_k for values:
        A_k = A_k * U_k;
        U_k.transpose();
        A_k = U_k * A_k;
        

        // commpute check:
        check = 0.0;
        for(int i = 0; i < A_k.get_n(); ++i){
            for(int j = i + 1; j < A_k.get_m(); ++j){
                check += A_k[i][j] * A_k[i][j];
            }
        }
        check = sqrt(check);
        ++itter;
    }while(check > alfa);

    for(int i = 0; i < A_k.get_n(); ++i){
        x[i] = A_k[i][i];
    }

    return itter;
}


int main(){
    ave();

    Matrix A, U;
    vector<double> x;
    double accuracy = 0.01;

    matrix_init(A);
    print_statement(A, accuracy);
    
    //rotate:
    cout << "Rotate Method:" << endl;
    int itter = rotate_method(A, U, x, accuracy);
    print_solution(x, U, itter);
    bye();

    return 0;
}