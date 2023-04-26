//
// Created by Legion on 4/26/2023.
//

#ifndef YELLOW_BELT_CPP_MATRIX_H
#define YELLOW_BELT_CPP_MATRIX_H
#include <iostream>
#include <vector>

class Matrix{
public:

    Matrix() {

    }

    Matrix(int row_num_, int col_num_){
        if(row_num_ < 0 || col_num_ < 0)
            throw std::out_of_range("");
        row_num = row_num_;
        col_num = col_num_;
        if(row_num == 0) {
            col_num = 0;
            return;
        }else if(col_num == 0){
            row_num = 0;
            return;
        }
        a = std::vector<std::vector<int>>(row_num);
        for(auto& elem: a){
            elem = std::vector<int>(col_num);
        }

    }

    void Reset(int row_num_, int col_num_){
        if(row_num_ < 0 || col_num_ < 0)
            throw std::out_of_range("");
        row_num = row_num_;
        col_num = col_num_;
        a.assign(row_num_, std::vector<int>(col_num_, 0));
    }
    int At(int row_num_, int col_num_) const {
        if(row_num_ < 0 || col_num_ < 0 || row_num_ >= row_num || col_num_ >= col_num)
            throw std::out_of_range("");
        return a[row_num_][col_num_];
    }

    int& At(int row_num_, int col_num_){
        if(row_num_ < 0 || col_num_ < 0 || row_num_ >= row_num || col_num_ >= col_num)
            throw std::out_of_range("");
        return a[row_num_][col_num_];
    }

    int GetNumRows() const {
        return row_num;
    }

    int GetNumColumns() const {
        return col_num;
    }

private:
    vector<std::vector<int>> a;
    int col_num = 0;
    int row_num = 0;
};

std::ostream& operator<<(std::ostream& stream, const Matrix& matrix) {
    stream << matrix.GetNumRows() << " " << matrix.GetNumColumns() << '\n';
    bool first;
    for(int i = 0; i < matrix.GetNumRows(); i++){
        first = true;
        for(int j = 0; j < matrix.GetNumColumns(); j++){
            if(first){
                stream << matrix.At(i, j);
                first = false;
            }else{
                stream << " " << matrix.At(i, j);
            }
        }
        stream << '\n';
    }
    return stream;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs){
    if(lhs.GetNumRows()!= rhs.GetNumRows() || lhs.GetNumColumns() != rhs.GetNumColumns())
        throw std::invalid_argument("");

    Matrix res(rhs.GetNumRows(), rhs.GetNumColumns());

    for(int i = 0; i < rhs.GetNumRows(); i++){
        for(int j = 0; j < rhs.GetNumColumns(); j++){
            res.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
        }
    }
    return res;
}

std::istream& operator>>(std::istream& stream, Matrix& matrix) {

    int col_num_;
    int row_num_;
    stream >> row_num_ >> col_num_;

    matrix.Reset(row_num_, col_num_);
    for(int i = 0; i < row_num_; i++){
        for(int j = 0; j < col_num_; j++){
            stream >> matrix.At(i, j);
        }
    }

    return stream;
}

bool operator==(const Matrix& lhs, const Matrix& rhs){
    if(lhs.GetNumRows() != rhs.GetNumRows() || lhs.GetNumColumns() != rhs.GetNumColumns())
        return false;
    for(int i = 0; i < rhs.GetNumRows(); i++){
        for(int j = 0; j < rhs.GetNumColumns(); j++){
            if(rhs.At(i, j) != lhs.At(i, j))
                return false;
        }
    }

    return true;
}

#endif //YELLOW_BELT_CPP_MATRIX_H
