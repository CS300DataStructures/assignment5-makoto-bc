#ifndef ASSIGNMENT_5__UPC_H_
#define ASSIGNMENT_5__UPC_H_

#include "Option.h"
#include <ostream>
#include <fstream>

/**
 * Represents a UPC.
 */
class UPC {
public:
	UPC()
		: _n(static_cast<unsigned long long>(-1)) {}

	explicit UPC(unsigned long long number)
		: _n(number) {}

	explicit UPC(long number)
		: _n(static_cast<unsigned long long>(number)) {}

	/**
	 * @param file Stream to read from
	 * @return The UPC if input was valid, otherwise none
	 */
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
