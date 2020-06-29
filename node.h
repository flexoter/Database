#ifndef H_NODE
#define H_NODE

#include "date.h"

#include <string>
#include <memory>

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum class LogicalOperation {
    AND,
    OR
};

class Node {

    public:
        virtual bool Evaluate(
            const Date&, 
            const string&) const = 0;

};

class LogicalOperationNode : public Node {

    public:
        LogicalOperationNode(LogicalOperation, 
        shared_ptr<Node>, shared_ptr<Node>);
        bool Evaluate(
            const Date&, 
            const string&) const override;

    private:
        const LogicalOperation _op;
        const shared_ptr<Node> _left;
        const shared_ptr<Node> _right;

};

class DataComparisonNode : public Node {

    public:
        DataComparisonNode(const Comparison&, const Date&);
        bool Evaluate(
            const Date&, 
            const string&) const override;
        bool GetComparator(const Date&) const;

    private:
        const Comparison _cmp;
        const Date _date;
};

class EventComparisonNode : public Node {

    public:
        EventComparisonNode(const Comparison&, const std::string&);
        bool Evaluate(
            const Date&, 
            const string&) const override;
        bool GetComparator(const std::string&) const;

    private:
        const Comparison _cmp;
        const std::string _event{""};
};

class EmptyNode : public Node {

    public:
        bool Evaluate(
            const Date&, 
            const string&) const override;

};


#endif /*H_NODE*/