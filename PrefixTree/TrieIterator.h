#pragma once
#include "StringStack.h"
#include <map>
#include <string>
#include <iterator>
template <class T> class Trie;

template <class T> class TrieIterator 
{
public:
	using value_type = T;
	using value_type_trie = Trie<T>;
	using node = typename value_type_trie::Node;
	TrieIterator(node* start, const std::string& startPos = "", node* end = nullptr) :
		_end(end),
		_trieTrace(startPos),
		_curNode(start)
	{
		if (_curNode->value == nullptr)
		{
			++(*this);
		}
	}
	TrieIterator() :
		_curNode(nullptr)
	{

	}

	virtual ~TrieIterator() = default;
	


	TrieIterator& operator++()
	{
		
			do
			{
				_getNextNode();
			} while (_curNode != nullptr &&_curNode->value.get() == nullptr);
		return *this;
	}

	TrieIterator operator++(int)
	{
		TrieIterator trieIterator(*this);
		++(*this);
		return trieIterator;
	}

	inline bool operator==(const TrieIterator& rhs)
	{
		return _curNode == rhs.getNode();
	}
	inline bool operator!=(const TrieIterator& rhs)
	{
		return !(_curNode == rhs.getNode());
	}

	std::pair<std::string, T&> operator*()
	{
		return  std::pair<std::string, T&>(_trieTrace.getString(), *_curNode->value.get());
	}

	

	value_type * operator->()
	{
		_curNode->value;
	}

	inline const node* getNode() const { return _curNode; };
protected:


	bool _getFirstIndex(unsigned char& index, unsigned char startPos = 0)
	{
		for (unsigned char i = startPos + 1; i < UCHAR_MAX; i++)
		{
			if (_curNode->childs[i].get() != nullptr)
			{
				index = i;
				return true;
			}
		}
		return false;
	}


	bool rise(unsigned char& index)
	{
		if (_curNode->parrent == nullptr)
			return false;
		_curNode = _curNode->parrent;
		while (!_getFirstIndex(index, _trieTrace.top()))
		{
			_trieTrace.pop();
			_curNode = _curNode->parrent;
			if (_curNode == _end)
				return false;
		}
		_trieTrace.pop();
		return true;
	}


	void _getNextNode()
	{
		unsigned char index;

		if (_getFirstIndex(index))
		{
			_curNode = _curNode->childs[index].get();
			_trieTrace.push(index);
			return;
		}
		else if (_curNode->parrent != _end)
		{
			if (rise(index))
			{
				_curNode = _curNode->childs[index].get();
				_trieTrace.push(index);
			}
			else
			{
				_curNode = nullptr;
			}
		}
		else
		{
			_curNode = nullptr;
		}
	}

	
	StringStack _trieTrace;
	node* _curNode;
	node* _end;
};

namespace std {
	template <typename T>
	struct iterator_traits<TrieIterator<T>> {
		using iterator_category =
			std::forward_iterator_tag;
		using value_type = T;
		//using pointer = ...;
		//using reference = ...;
		//using difference_type = ...;
	};
}