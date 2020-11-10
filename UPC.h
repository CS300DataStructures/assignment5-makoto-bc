#ifndef ASSIGNMENT_5__UPC_H_
#define ASSIGNMENT_5__UPC_H_

#include <ostream>

class UPC {
public:
	explicit UPC(unsigned long long number)
		: _n(number) {}

	friend std::ostream& operator<<(std::ostream& os, const UPC& upc) {
		return os << upc._n;
	}

private:
	unsigned long long _n;
};

#endif //ASSIGNMENT_5__UPC_H_
