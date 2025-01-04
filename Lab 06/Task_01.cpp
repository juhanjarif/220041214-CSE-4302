#include <iostream>
#include <vector>

using namespace std;

class Matrix3D {
private:
    vector<vector<double>> matrix;
    int rows, cols;
    int increment;
    int count;

    double calculateDeterminant(const vector<vector<double>>& mat, int size) const{
        if(size == 1) 
            return mat[0][0];
        if(size == 2) 
            return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
        
        double det = 0;
        int sign = 1;
        for(int i = 0; i < size; i++){
            vector<vector<double>> submat(size - 1, vector<double>(size - 1));
            getSubmatrix(mat, submat, 0, i, size);
            det += sign * mat[0][i] * calculateDeterminant(submat, size - 1);
            sign = -sign;
        }
        return det;
    }

    void getSubmatrix(const vector<vector<double>>& mat, vector<vector<double>>& temp, int skipRow, int skipCol, int size) const {
        int r = 0, c = 0;
        for(int i = 0; i < size; i++){
            if(i != skipRow){
                c = 0;
                for(int j = 0; j < size; j++){
                    if(j != skipCol){
                        temp[r][c] = mat[i][j];
                        c++;
                    }
                }
                r++;
            }
        }
    }

    void getCofactor(vector<vector<double>>& cofactors) const{
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                vector<vector<double>> temp(rows - 1, vector<double>(cols - 1));
                getSubmatrix(matrix, temp, i, j, rows);
                int sign = ((i + j) % 2 == 0) ? 1 : -1;
                cofactors[i][j] = sign * calculateDeterminant(temp, rows - 1);
            }
        }
    }

public:
    Matrix3D(int r, int c, int inc = 1) : rows(r), cols(c), count(0){
        if(inc < 0)
            increment = 1;
        else
            increment = inc;
        matrix = vector<vector<double>>(rows, vector<double>(cols, 0.0));
    }

    ~Matrix3D() {}

    double det() const{
        if (rows != cols)
            return 0.0;
        
        return calculateDeterminant(matrix, rows);
    }

    Matrix3D inverse() const{
        if(rows != cols)
            return *this;
        
        double determinant = det();
        if (determinant == 0)
            return *this;

        vector<vector<double>> cofactors(rows, vector<double>(cols));
        getCofactor(cofactors);

        Matrix3D result(rows, cols);
        for(int i = 0; i < rows; i++){
            for (int j = 0; j < cols; j++)
                result.matrix[j][i] = cofactors[i][j] / determinant;
        }
        return result;
    }

    void setIncrement(int val){
        if(count == 0) {
            if(val < 0)
                return;
            else
                increment = val;
        }
    }

    const vector<vector<double>>& getMatrix() const{
        return matrix;
    }

    void incrementMatrix(){
        for(int i = 0; i < rows; ++i){
            for(int j = 0; j < cols; ++j)
                matrix[i][j] += increment;
        }
        ++count;
    }

    Matrix3D operator+(const Matrix3D& other) const{
        if(rows != other.rows || cols != other.cols)
            return *this;

        Matrix3D result(rows, cols);
        for(int i = 0; i < rows; ++i){
            for(int j = 0; j < cols; ++j)
                result.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
        }
        return result;
    }

    Matrix3D operator-(const Matrix3D& other) const{
        if(rows != other.rows || cols != other.cols)
            return *this;
        
        Matrix3D result(rows, cols);
        for(int r = 0; r < rows; ++r){
            for(int c = 0; c < cols; ++c)
                result.matrix[r][c] = matrix[r][c] - other.matrix[r][c];
        }
        return result;
    }

    Matrix3D operator*(const Matrix3D& other) const{
        if(cols != other.rows)
            return *this;

        Matrix3D result(rows, other.cols);
        for(int i = 0; i < rows; ++i){
            for(int j = 0; j < other.cols; ++j){
                for(int k = 0; k < cols; ++k)
                    result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
            }
        }
        return result;
    }

    bool operator>(const Matrix3D& other) const{
        return det() > other.det();
    }

    bool operator<(const Matrix3D& other) const{
        return det() < other.det();
    }

    bool operator>=(const Matrix3D& other) const{
        return det() >= other.det();
    }

    bool operator<=(const Matrix3D& other) const{
        return det() <= other.det();
    }

    bool operator==(const Matrix3D& other) const{
        return det() == other.det();
    }

    bool operator!=(const Matrix3D& other) const{
        return det() != other.det();
    }
};

int main() {
    Matrix3D mat1(3, 3, 2);
    Matrix3D mat2(3, 3, 3);
    
    mat1.incrementMatrix();
    mat2.incrementMatrix();

    Matrix3D mat3 = mat1 + mat2;

    cout << "Matrix 1 determinant: " << mat1.det() << endl;
    cout << "Matrix 2 determinant: " << mat2.det() << endl;

    if(mat1 > mat2)
        cout << "Matrix 1 has a larger determinant.\n";
    else
        cout << "Matrix 2 has a larger determinant or they are equal.\n";

    return 0;
}
