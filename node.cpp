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
        case LogicalOperation::AND:
            return _left->Evaluate(date, event) 
            && _right->Evaluate(date, event);
        case LogicalOperation::OR:
            return _left->Evaluate(date, event) 
            || _right->Evaluate(date, event);
        default:
            break;
    }
}

bool DataComparisonNode::GetComparator(
    const Date& t_date) const {
        switch (_cmp) {
            case Comparison::Less:
                return _date < t_date;
            case Comparison::LessOrEqual:
                return _date <= t_date;
            case Comparison::Greater:
                return _date > t_date;
            case Comparison::GreaterOrEqual:
                return _date >= t_date;
            case Comparison::Equal:
                return _date == t_date;
            case Comparison::NotEqual:
                return _date != t_date;
            default:
                break;
    }
}

DataComparisonNode::DataComparisonNode(
    const Comparison& t_cmp, 
    const Date& t_date)
    : _cmp(t_cmp), _date(t_date) {}

bool DataComparisonNode::Evaluate(
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
                return _event < t_event;
            case Comparison::LessOrEqual:
                return _event <= t_event;
            case Comparison::Greater:
                return _event > t_event;
            case Comparison::GreaterOrEqual:
                return _event >= t_event;
            case Comparison::Equal:
                return _event == t_event;
            case Comparison::NotEqual:
                return _event != t_event;
            default:
                break;
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