#pragma once
#include <string>

class StringStack final
{
public:

	StringStack(const std::string& startPos = "") :
		_string(startPos)
	{

	}
	inline char top() {
		return _string.back();
	}

	inline void pop() {
		_string.erase(_string.begin() + _string.length() - 1);
	};

	inline void push(char toPush) {
		_string.push_back(toPush);
	}

	const std::string& getString() {
		return _string;
	}


private:
	std::string _string;
};
