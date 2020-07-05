#include "node.h"

#include <string>
#include <memory>

using namespace std;

LogicalOperationNode::LogicalOperationNode(
    LogicalOperation t_op, 
    shared_ptr<Node> t_left, 
    shared_ptr<Node> t_right)
    : _op(t_op), _left(t_left), _right(t_right) {}

bool LogicalOperationNode::Evaluate(
    const Date& date, 
    const string& event) const {
    switch (_op) {
        case LogicalOperation::And:
            return _left->Evaluate(date, event) 
            && _right->Evaluate(date, event);
        case LogicalOperation::Or:
            return _left->Evaluate(date, event) 
            || _right->Evaluate(date, event);
        default:
            return false;
    }
}

bool DateComparisonNode::GetComparator(
    const Date& t_date) const {
        switch (_cmp) {
            case Comparison::Less:
                return t_date < _date;
            case Comparison::LessOrEqual:
                return t_date <= _date;
            case Comparison::Greater:
                return t_date > _date;
            case Comparison::GreaterOrEqual:
                return t_date >= _date;
            case Comparison::Equal:
                return t_date == _date;
            case Comparison::NotEqual:
                return t_date != _date;
            default:
                return false;
    }
}

DateComparisonNode::DateComparisonNode(
    const Comparison& t_cmp, 
    const Date& t_date)
    : _cmp(t_cmp), _date(t_date) {}

bool DateComparisonNode::Evaluate(
    const Date& date, 
    const string& event) const {
        return GetComparator(date);
}

EventComparisonNode::EventComparisonNode(
    const Comparison& t_cmp, 
    const std::string& t_event)
        : _cmp(t_cmp), _event(t_event) {}

bool EventComparisonNode::GetComparator(
    const string& t_event) const {
        switch (_cmp) {
            case Comparison::Less:
                return t_event < _event;
            case Comparison::LessOrEqual:
                return t_event <= _event;
            case Comparison::Greater:
                return t_event > _event;
            case Comparison::GreaterOrEqual:
                return t_event >= _event;
            case Comparison::Equal:
                return t_event == _event;
            case Comparison::NotEqual:
                return t_event != _event;
            default:
                return false;
        }
    }

bool EventComparisonNode::Evaluate(
    const Date& date, 
    const string& event) const {
        return GetComparator(event);
}

bool EmptyNode::Evaluate(
    const Date& date, 
    const string& event) const {
        return true;
}