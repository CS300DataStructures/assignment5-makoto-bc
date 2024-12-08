#include <sstream>
#include "../file.h"

extern "C" int LLVMFuzzerTestOneInput(const char* data, size_t size) {
	std::stringstream ss(std::string(data, size));
	try {
		readLines(ss);
	} catch (const InvalidFile&) {}
	return 0;
}
