
#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

#define OPEN_BRACKET "("
#define CLOSED_BRACKET ")"


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
	first_bracket is var which needed for skip first bracket 
	but not skip second and next, because it require for create sublists
*/
void filling_list(HList **cur, bool *first_bracket, ifstream &fin)
{
	char c = ' '; //contain currnent alpha
	//if cur character is eof - return
	while(c!= ')')
	{
		fin.read(&c, 1);
		while(c == ' ')
		{
			fin.read(&c, 1);
			if(c == EOF || c == '\n')
				return;
		}
		if(*first_bracket)
		{
			*first_bracket = false;
			continue;
		}
		if(isalpha(c))
			append_atom(cur, c);
		//Head not empty
		else if(c == '(')
		{
			append_sublist(cur);
			HList *cur_node = *cur;
			while(cur_node->next)
				cur_node = cur_node->next;
			filling_list(&cur_node->sublist, first_bracket, fin);
		}
	}
}


void replace(HList *hlist, char target, char replacement)
{
	HList *cur = hlist;
	while(cur)
	{
		if(cur->sublist == NULL)
		{
			if(cur->atom == target)
				cur->atom = replacement;
		}
		else if(cur->sublist)
			replace(cur->sublist, target, replacement);
		cur = cur->next;
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


void shell_print(HList *hlist)
{
	cout << "(";
	print_hlist(hlist);
	cout << ")";
	cout << endl;
}


int main()
{
	HList *hlist = NULL;
	bool first_bracket = true;
	ifstream fin("f.txt");
	filling_list(&hlist, &first_bracket, fin);
	shell_print(hlist);
	while(true)
	{	
		char c;
		char target;
		char replacement;
		cout << "Enter target which needed replace: ";
		cin >> target;
		cout << "Enter replacement: ";
		cin >> replacement;
		getchar(); //for read '\n'
		replace(hlist, target, replacement);
		shell_print(hlist);
		cout << "For enter new data type Enter" << endl;
		cout << "For exit type q" << endl;
		cout << ": ";
		cin.get(c);
		if(c == 'q')
			break;
	}

	return 0;
}
