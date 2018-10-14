#include <iostream>
#include "Trie.h"
#include "TrieIterator.h"
#include <fstream>
#include <istream>
#include <queue>
using namespace std;

int main()
{
	Trie<int> trie;
	for (size_t i = 0; i < 1000; i++)
	{
		trie[to_string(i)] = i;
	}
	Trie<int> trie2;
	trie2.insert(trie.begin(), trie.end());


}