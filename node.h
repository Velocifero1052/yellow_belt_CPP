//
// Created by Rakhmon Radjabov on 30/05/23.
//

#ifndef YELLOW_BELT_CPP_NODE_H
#define YELLOW_BELT_CPP_NODE_H

#include "date.h"

struct Node {
    virtual bool Evaluate() const = 0;
};

struct Value : public Node {
    Value(Date date);
    bool Evaluate() const override;
private:
    const Date _value;
};

struct Op : public Node {
    Op(char value)
            : precedence([value] {
        if (value == '*') {
            return 2;
        } else {
            return 1;
        }
    }()),
              _op(value) {}

    const uint8_t precedence;

    bool Evaluate() const override {
        return false;
    }

    void SetLeft(std::shared_ptr<Node> node) { _left = node; }
    void SetRight(std::shared_ptr<Node> node) { _right = node; }

private:
    const char _op;
    std::shared_ptr<const Node> _left, _right;
};

#endif //YELLOW_BELT_CPP_NODE_H
