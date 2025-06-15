#include "Tag.h"

Tag::Tag(const QString& name, double value, int address, const QString& type, QObject* parent)
    : QObject(parent), m_name(name), m_value(value), m_address(address), m_type(type)
{}

QString Tag::name() const {
    return m_name;
}

int Tag::address() const {
    return m_address;
}

QString Tag::type() const {
    return m_type;
}

double Tag::value() const {
    return m_value;
}

void Tag::setValue(double newValue) {
    if (!qFuzzyCompare(m_value, newValue)) {
        m_value = newValue;
        emit valueChanged();
    }
}
