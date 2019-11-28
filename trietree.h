#ifndef _TRIETREE_H
#define _TRIETREE_H

class trie_tree
{
public:
	int foo;
	
	trie_tree()
	{
		memory_used = 0;
	}
	
	long int get_memory_used(int unit=1)
	{
		return (memory_used/unit);
	};
private:
	long int memory_used;
	int bar;
};

#endif