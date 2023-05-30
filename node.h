//
// Created by Rakhmon Radjabov on 30/05/23.
//

#ifndef YELLOW_BELT_CPP_NODE_H
#define YELLOW_BELT_CPP_NODE_H

#include "date.h"
#include <string>

using std::string;

class Node {
public:
    virtual bool Evaluate(Date date, string str) const = 0;
};

class DateComparisonNode : public Node {
    DateComparisonNode(Date date);
    bool Evaluate(Date date, string str) const override;
private:
    const Date _value;
};




#endif //YELLOW_BELT_CPP_NODE_H
