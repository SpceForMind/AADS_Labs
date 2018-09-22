
#include <iostream>
#include <cctype>

using namespace std;

/*
	Hierarchical list
	Type is type of atom
*/
struct HList
{
	char atom;
	struct HList *sublist;	
	struct HList *next;
};

void append_sublist(HList **cur)
{
	//allocate memory for next element which was contain head of sublist
	HList *new_node = new HList;
	new_node->sublist = new HList;
	new_node->sublist->next = NULL;
	new_node->sublist->sublist = NULL;
	new_node->next = NULL;
	//add in empty head
	if(*cur == NULL)
		*cur = new_node;
	else
	{
		HList *cur_node = *cur;
		while(cur_node->next)
			cur_node = cur_node->next;
		cur_node->next = new_node;
	}
}

void  append_atom(HList **cur, char atom)
{
	//crate new node
	HList *new_node = new HList;
	new_node->next = NULL;
	new_node->atom = atom;
	new_node->sublist = NULL;
	//add new node in empty head
	if(*cur == NULL)
		*cur = new_node;
	else
	{
		HList *cur_node = *cur;
		while(cur_node->next)
			cur_node = cur_node->next;
		cur_node->next = new_node;
	}
}


/*
	filling hierarchical list from input stream 
	as (a(bc)d) 
*/
void filling_list(HList **cur)
{
	char c = ' '; //contain currnent alpha
	//if cur character is eof - return
	while(c!= ')')
	{
		cin >> c;
		while(c == ' ')
		{
			cin >> c;
			if(c == EOF || c == '\n')
				return;
		}
		if(isalpha(c))
			append_atom(cur, c);
		//Head not empty
		else if(c == '(' && *cur!= NULL)
		{
			append_sublist(cur);
			HList *cur_node = *cur;
			while(cur_node->next)
				cur_node = cur_node->next;
			filling_list(&cur_node->sublist);
		}
	}
}

void print_hlist(HList *hlist)
{
	HList *cur = hlist;
	while(cur)
	{
		if(cur->sublist == NULL)
			cout << cur->atom << " ";
		else if(cur->sublist)
		{
			cout << "(";
			print_hlist(cur->sublist);
			cout << ")";
		}
		cur = cur->next;
	}
}


int main()
{
	HList *hlist = NULL;
	filling_list(&hlist);
	print_hlist(hlist);
//	cout << hlist;
	return 0;
}
