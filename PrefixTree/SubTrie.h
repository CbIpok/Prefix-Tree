#pragma once
#include "TrieIterator.h"
#include <string>


template <class T> class SubTrie final : public Trie<T>
{
public:
	using node = typename Trie<T>::Node;
	typedef TrieIterator<T> iterator;
	typedef TrieIterator<const T> const_iterator;

	typedef T value_type;
	typedef std::string key_type;
	SubTrie(const std::shared_ptr<node>& tnode, std::string startPos) :
		_startPos(startPos),
		Trie<T>(tnode)
	{

	}

	iterator begin()
	{
		node* begin = &(this->_getNode(_startPos).first);
		node* end = begin->parrent;
		return iterator(begin, _startPos, end);
	}


	SubTrie<T> GetSubTrie(const key_type & subKey) = delete;
	std::pair<iterator, bool> insert(const key_type& k, const value_type& val) = delete;
	template <class InputIterator> void insert(InputIterator first, InputIterator last) = delete;
	void erase(iterator position) = delete;
	size_t erase(const key_type& k) = delete;
	void erase(iterator first, iterator last) = delete;
	void clear() = delete;

	size_t size() const
	{
		size_t size = 0;
		for (const auto& i : this)
		{
			size++;
		}
		return size;
	}
private:
	std::string _startPos;
};