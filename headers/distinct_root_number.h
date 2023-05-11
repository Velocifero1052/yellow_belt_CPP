//
// Created by comme on 5/10/2023.
//
#pragma once
#ifndef YELLOW_BELT_CPP_DISTINCT_ROOT_NUMBER_H
#define YELLOW_BELT_CPP_DISTINCT_ROOT_NUMBER_H

#include "test_framework.h"

int GetDistinctRealRootCount(double a, double b, double c) {
    if(a != 0.0 && b != 0.0) {
        double under_root_expression = b * b - 4 * a * c;
        if (under_root_expression < 0.0) {
            return 0;
        } else if (under_root_expression == 0.0) {
            return 1;
        } else {
            return 2;
        }
    }else if(a == 0.0 && b != 0.0 && c != 0.0){
        return 1;
    }else if(a != 0.0 && c == 0.0 || a == 0.0 && b != 0.0){
        return 1;
    }else if(a != 0.0 && -c / a >= 0.0){
        return 2;
    }else{
        return 0;
    }
}

void test_roots_count(){
    AssertEqual(GetDistinctRealRootCount(2, 1, 2), 0, "negative under root expression");
    AssertEqual(GetDistinctRealRootCount(2,4,2), 1, "zero under root expression has one root");
    AssertEqual(GetDistinctRealRootCount(1, 4, 1), 2, "normal square equation");
    AssertEqual(GetDistinctRealRootCount(1, 0, 0), 1, "one variable only");
    AssertEqual(GetDistinctRealRootCount(0, 1, 0), 1, "linear equation");
    AssertEqual(GetDistinctRealRootCount(0.1, -1, 1), 2, "two roots");
    AssertEqual(GetDistinctRealRootCount(0, 0, 1), 0, "no variables no roots");
}

#endif //YELLOW_BELT_CPP_DISTINCT_ROOT_NUMBER_H
