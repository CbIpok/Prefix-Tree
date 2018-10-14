#include "pch.h"

#include "../PrefixTree/Trie.h";
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
using namespace std;

class PoolTesting : public ::testing::Test {
public:
	virtual void SetUp(void) {
		_CrtMemCheckpoint(&startup);
	}
	virtual void TearDown(void) {
		_CrtMemState teardown, diff;
		_CrtMemCheckpoint(&teardown);
		ASSERT_EQ(0, _CrtMemDifference(&diff, &startup, &teardown)) << "Memory leaks detected";
	}
	_CrtMemState startup;
};

TEST_F(PoolTesting, Clear)
{
	
	Trie<char> trie;
	ifstream f("test.txt");
	ASSERT_TRUE(f);
	while (!f.eof())
	{
		std::string buf;
		f >> buf;
		trie[buf];
	}
	trie.clear();
}

TEST_F(PoolTesting, SubTrie)
{
	Trie<int> trie;
	for (size_t i = 0; i < 1000; i++)
	{
		trie[to_string(i)] = i;
	}
	auto subTrie = trie.GetSubTrie("50");
}

TEST(Trie, Insert)
{
	Trie<int> trie;
	trie.insert("test", 123);
	ASSERT_TRUE(trie["test"]==123);
}

TEST(Trie, InsertByOperator)
{
	Trie<int> trie;
	trie["test"] = 123;
	ASSERT_TRUE(trie["test"] == 123);
}

TEST(Trie, Size)
{
	Trie<int> trie;
	for (size_t i = 0; i < 1000; i++)
	{
		ASSERT_TRUE(trie.size() == i);
		trie[to_string(i)] = i;
	}
	for (size_t i = 0; i < 1000; i++)
	{
		trie.erase(to_string(i));
		ASSERT_TRUE(trie.size() == 999 - i);
	}
}

TEST(Trie, Erase)
{
	Trie<int> trie;
	map<string, int> mTree;
	for (size_t i = 0; i < 1000; i++)
	{
		ASSERT_TRUE(trie.size() == i);
		trie[to_string(i)] = i;
		mTree[to_string(i)] = i;
	}
	mTree.erase("500");
	trie.erase("500");
	for (const auto& i : trie)
	{
		mTree[i.first] = i.second;
	}
}

TEST(Trie, Swap)
{
	Trie<int> trie;
	Trie<int> trie2;
	for (size_t i = 0; i < 1000; i++)
	{
		ASSERT_TRUE(trie.size() == i);
		trie[to_string(i)] = i;
	}
	ostringstream sstream1;
	for (auto& i : trie)
	{
		sstream1 << i.first << " "<<i.second<<endl;
	}
	ostringstream sstream2;
	trie.swap(trie2);
	for (auto& i : trie2)
	{
		sstream2 << i.first << " " << i.second << endl;
	}
	ASSERT_TRUE(sstream1.str() == sstream2.str());
}

TEST(Trie, Clear)
{
	Trie<int> trie;
	for (size_t i = 0; i < 1000; i++)
	{
		trie[to_string(i)] = i;
	}
	trie.clear();
	for (const auto& i : trie)
	{
		ASSERT_TRUE(false);
	}
	ASSERT_TRUE(trie.size() == 0);
}

TEST(Trie, FindCorrect)
{
	Trie<int> trie;
	for (size_t i = 0; i < 1000; i++)
	{
		trie[to_string(i)] = i;
	}
	auto it = trie.find("100");
	ASSERT_TRUE((*it).second == 100);
}

TEST(Trie, FindUnCorrect)
{
	Trie<int> trie;
	for (size_t i = 0; i < 1000; i++)
	{
		trie[to_string(i)] = i;
	}
	try
	{
		auto it = trie.find("10000");
		ASSERT_TRUE(false);
	}
	catch (const std::out_of_range&)
	{
		
	}
		
}

TEST(Trie, SubTrie)
{
	Trie<int> trie;
	map<string, int> mTree;
	for (size_t i = 0; i < 1000; i++)
	{
		std::string key = to_string(i);
		if (key.substr(0,2) == "10")
		{
			mTree[key] = i;
		}
		trie[to_string(i)] = i;
	}
	auto subTrie = trie.GetSubTrie("10");
	map<string, int> mTree2;
	for (auto& i : subTrie)
	{
		mTree2[i.first] = i.second;
	}
	ASSERT_TRUE(mTree == mTree2);
}
