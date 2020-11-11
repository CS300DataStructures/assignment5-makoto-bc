#ifndef ASSIGNMENT_5__OPTIONAL_H_
#define ASSIGNMENT_5__OPTIONAL_H_

#include <stdexcept>
#include <ostream>

template<class T>
class Option {
public:
	Option()
		: _valid(false) {}

	Option(T value)
		: _valid(true)
		, _value(std::move(value)) {}

	T& value() {
		return const_cast<T&>(const_cast<const Option*>(this)->value());
	}

	const T& value() const {
		if (!_valid) {
			throw std::runtime_error("does not contain a value");
		}

		return _value;
	}

	bool hasValue() const {
		return _valid;
	}

	bool operator==(const Option& rhs) const {
		return _valid == rhs._valid ||
			_value == rhs._value;
	}
private:
	bool _valid;
	T _value;
};

#endif //ASSIGNMENT_5__OPTIONAL_H_
