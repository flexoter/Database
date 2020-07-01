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
    And,
    Or
};

class Node {

    public:
        virtual bool Evaluate(
            const Date&, 
            const std::string&) const = 0;

};

class LogicalOperationNode : public Node {

    public:
        LogicalOperationNode(LogicalOperation, 
        std::shared_ptr<Node>, std::shared_ptr<Node>);
        bool Evaluate(
            const Date&, 
            const std::string&) const override;

    private:
        const LogicalOperation _op;
        const std::shared_ptr<Node> _left;
        const std::shared_ptr<Node> _right;

};

class DateComparisonNode : public Node {

    public:
        DateComparisonNode(const Comparison&, const Date&);
        bool Evaluate(
            const Date&, 
            const std::string&) const override;
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
            const std::string&) const override;
        bool GetComparator(const std::string&) const;

    private:
        const Comparison _cmp;
        const std::string _event{""};
};

class EmptyNode : public Node {

    public:
        bool Evaluate(
            const Date&, 
            const std::string&) const override;

};

#endif /*H_NODE*/