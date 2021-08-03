#include <iostream>

class Serialize
{
public:
	Serialize() {}
	virtual ~Serialize() {}

	virtual size_t serialize(std::ostream& stream) = 0;
	virtual void deserialize(std::istream& stream) = 0;
};