#ifndef ASSIGNMENT_5__UPC_H_
#define ASSIGNMENT_5__UPC_H_

#include "Option.h"
#include <ostream>
#include <fstream>

class UPC {
public:
	UPC()
		: _n(static_cast<unsigned long long>(-1)) {}

	explicit UPC(unsigned long long number)
		: _n(number) {}

	static Option<UPC> read(std::istream& file) {
		unsigned long long n = 0;
		file >> n;
		if (file.fail()) {
			return {};
		}
		return {UPC(n)};
	}

	friend std::ostream& operator<<(std::ostream& os, const UPC& upc) {
		return os << upc._n;
	}

	bool operator==(const UPC& rhs) const {
		return _n == rhs._n;
	}

	bool operator!=(const UPC& rhs) const {
		return !(rhs == *this);
	}

	bool operator<(const UPC& rhs) const {
		return _n < rhs._n;
	}

	bool operator>(const UPC& rhs) const {
		return rhs < *this;
	}

	bool operator<=(const UPC& rhs) const {
		return !(rhs < *this);
	}

	bool operator>=(const UPC& rhs) const {
		return !(*this < rhs);
	}

private:
	unsigned long long _n;
};

#endif //ASSIGNMENT_5__UPC_H_
