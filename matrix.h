#ifndef MATRIX_H
#define MATRIX_H
class matrix
{
public:
    matrix();
    ~matrix();
    void getmat();
    void sub_mat(matrix m2, matrix m1);
    void add_mat(matrix m2, matrix m1);
    void scaler_mult(int num);
    void mult(matrix m1, matrix m2);
    double det();
    double det(double **z,int p);
    void memory();
    void  solve();
    void I();
protected:

private:
    int r, c;
    double** mat;
    double** elementary;
};
#endif // MATRIX_H