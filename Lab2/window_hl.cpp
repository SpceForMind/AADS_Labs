
#include <iostream>
#include <cctype>
using namespace std;

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
    new_node->sublist->next = nullptr;
    new_node->sublist->sublist = nullptr;
    new_node->next = nullptr;
    //add in empty head
    if(*cur == nullptr)
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
    new_node->next = nullptr;
    new_node->atom = atom;
    new_node->sublist = nullptr;
    //add new node in empty head
    if(*cur == nullptr)
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
void filling_list(HList **cur, bool *first_bracket, string &str, int &i)
{

    char c = ' '; //contain currnent alpha
    //if cur character is eof - return
    while(c!= ')' && i < str.length())
    {
	c = str[i];
        while(c == ' ')
        {
            ++i;
	    c = str[i];
        }
        if(*first_bracket)
        {
            *first_bracket = false;
            ++i;
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
            ++i;
            filling_list(&cur_node->sublist, first_bracket, str, i);
        }
        ++i;
    }
}


void replace(HList *hlist, char target, char replacement)
{
    HList *cur = hlist;
    while(cur)
    {
        if(cur->sublist == nullptr)
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
        if(cur->sublist == nullptr)
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
	string str = "(a (b c) d)";
	int i = 0;
	bool first_bracket = true;
	filling_list(&hlist, &first_bracket, str, i);
	shell_print(hlist);

	return 0;
}
