#pragma once
#include <map>
#include<memory>
#include <string>
#include <vector>
#include "TrieIterator.h"
#include "SubTrie.h"
#include <iostream>
#include <iterator>

template <class T> class Trie
{
public:

	typedef TrieIterator<T> iterator;
	typedef TrieIterator<const T> const_iterator;

	typedef T value_type;
	typedef std::string key_type;

	struct Node
	{
		Node(Node* parrent = nullptr)
		{
			for (auto& i : childs)
			{
				i = nullptr;
			}
			this->parrent = parrent;
			value.reset(nullptr);
		}
		std::unique_ptr<value_type> value;
		std::unique_ptr<Node> childs[256];
		Node* parrent;
	};

	Trie(std::shared_ptr<Node> node)
	{
		_trie = std::shared_ptr<Node>(node);
	}

	Trie()
	{

		_trie = std::make_shared<Node>();
		_trie.get()->parrent = nullptr;

	}

	template <class InputIterator> Trie(InputIterator first, InputIterator last)
	{
		Trie<typename std::iterator_traits<InputIterator>::value_type> trie;
		_trie = std::make_shared<Node>();
		_trie.get()->parrent = nullptr;
		trie.insert(first, last);
	}


	//Trie(const Trie<T> & trie);
	virtual ~Trie()
	{

	}


	iterator begin()
	{
		return iterator(_trie.get());
	}

	const_iterator begin() const
	{
		return const_iterator(_trie.get());
	}

	iterator end()
	{
		return iterator();
	}

	const_iterator end() const
	{
		return const_iterator(_trie.get());
	}


	inline bool empty() const
	{
		return size() == 0;
	}

	inline size_t size() const
	{
		return _size;
	}

	const value_type& operator[] (const key_type& k) const
	{
		return _getNode(k).first.value;
	}

	value_type& operator[] (const key_type& k)
	{
		auto findResult = _getNode(k);
		Node& node = findResult.first;
		if (node.value.get() == nullptr)
		{
			node.value.reset(new value_type);
		}
		if (findResult.second)
		{
			_size++;
		}
		return *node.value.get();
	}

	std::pair<iterator, bool> insert(const key_type& k, const value_type& val)
	{
		auto node = _getNode(k);
		if (node.second)
			_size++;
		node.first.value = std::make_unique<value_type>(val);
		return std::pair<iterator, bool>(iterator(&node.first, k), node.second);
	}


	

	template <class InputIterator> void insert(InputIterator first, InputIterator last)
	{
		for (; first != last; first++)
		{
			insert((*first).first, (*first).second);
		}
	}

	//удаление
	void erase(iterator position)
	{
		erase((*position).first);
	}

	size_t erase(const key_type& k)
	{
		if (!_findNode(k))
		{
			return 0;
		}
		else
		{
			delete(_getNode(k).first.value.release());
			_getNode(k).first.value.reset(nullptr);
			_size--;
			return 1;
		}

	}

	void erase(iterator first, iterator last)
	{
		for (; (first != last) && (first != end()); first++)
		{
			erase((*first).first);
		}
	}

	void swap(Trie& trie)
	{
		std::swap(*this, trie);
	}

	void clear()
	{
		
		_trie.reset(new Node());
		_trie.get()->parrent = nullptr;
		_size = 0;
	}

	//найти элемент

	iterator find(const key_type& k)
	{
		if (!_findNode(k))
		{
			throw std::out_of_range("cant find " + k);
		}
		return iterator(&_getNode(k).first, k);
	}


	SubTrie<T> GetSubTrie(const key_type & subKey)// получить subtree
	{
		if (!_findNode(subKey))
		{
			throw std::out_of_range("cant find " + subKey);
		}
		return SubTrie<T>(_trie, subKey);
	}

	inline Node* getMainNode() { return _trie.get(); };



protected:
	size_t _size = 0;

	std::shared_ptr<Node> _trie;

	std::pair<Node&, bool> _getNode(const key_type& k)
	{
		Node* curNode = _trie.get();
		bool isCreated = false;
		for (size_t i = 0; i < k.size(); i++)
		{
			unsigned char index = (k.at(i));
			if (curNode->childs[index].get() != nullptr)
			{
				curNode = curNode->childs[index].get();
			}
			else
			{
				curNode->childs[index].reset(new Node(curNode));
				curNode = curNode->childs[index].get();
				isCreated = true;
			}
		}

		return std::pair<Node&, bool>(*curNode, isCreated);
	}

	bool _findNode(const key_type& k)
	{
		Node* curNode = _trie.get();
		for (size_t i = 0; i < k.size(); i++)
		{
			unsigned char index = (k.at(i));
			if (curNode->childs[index].get() != nullptr)
			{
				curNode = curNode->childs[index].get();
			}
			else
			{
				return false;
			}
		}
		return curNode->value.get() != nullptr;
	}


};