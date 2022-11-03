#include <string>
#include <cstdlib>
#include <iostream>
#include <cctype>
using namespace std;

template <class type1, class type2>
class hashMap
{
public:
	const int MAX_ELEMENTS;
	hashMap(int = 10);
	hashMap(const hashMap<type1, type2>&);
	const hashMap<type1, type2>& operator=(hashMap<type1, type2>);
	~hashMap();
	type2& operator[](std::string);
private:
	int hashFunction(std::string) const;
	void resize(int);

	struct node
	{
		type1 key;
		type2 value;
		node * next;
		node * prev;
	};

	struct list
	{
		node * head;
		node * middleElement;
		int amount;
	};
	
	int filledEntries;
	int tableSize;

	list * table;
};

/*function_identifier: intialize variables
*paarmeters: none
*return value:none */
template <class type1, class type2>
hashMap<type1, type2>::hashMap(int init) : MAX_ELEMENTS(10)
{
    tableSize = init;
    filledEntries = 0;
    table = new list[tableSize];
    
    for ( int i =0; i < tableSize; i++)
        table[i] = {NULL, NULL, 0};
}

/*function_identifier: copy constructor
*paarmeters: copy 
*return value: none */
template <class type1, class type2>
hashMap<type1, type2>::hashMap(const hashMap<type1, type2>& copy) : MAX_ELEMENTS(10)
{

    tableSize = copy.tableSize;
    filledEntries = copy.filledEntries;
    table = new list[tableSize];
    

    for ( int i=0; i < tableSize; i++){
        
        table[i].middleElement = NULL;
        node * n = copy.table[i].head;
        node ** ptr = &table[i].head;
        node * prev = NULL;
        
        while (n){
            // node copy set n->next to NULL
            node * c = new node;
            *ptr = c;           
            
            if ( n == copy.table[i].middleElement)
                table[i].middleElement = c; 
            
            c->key = n->key;
            c->value = n->value;
            c->prev = prev;
            
            ptr = &c->next;
            n = n->next;
        }
        *ptr = NULL;

        table[i].amount = copy.table[i].amount;
    }        
}


/*function_identifier: assignment operator
*paarmeters: rhs
*return value:none */
template <class type1, class type2>
const hashMap<type1, type2>& hashMap<type1, type2>::operator=(hashMap<type1, type2> rhs)
{
	std::swap(*this, rhs);
	return *this;
}

/*function_identifier: destructor 
*paarmeters: none
*return value: none*/
template <class type1, class type2>
hashMap<type1, type2>::~hashMap()
{
    for ( int i=0; i < tableSize; i++){
        
        node * ptr = table[i].head;
        
        while (ptr != NULL){
    
            node * delPtr = ptr;
            ptr = ptr->next;
            delete delPtr;
        }
    }
    delete[] table;
}

/*function_identifier: find key or create new entry and return the value with a matching key 
*paarmeters: key
*return value: value*/
template <class type1, class type2>
type2& hashMap<type1, type2>::operator[](std::string key)
{

    if ( filledEntries * 2 >= tableSize)
        resize(tableSize * 2);
    

    int index = hashFunction(key);

    while(true){
        if ( table[index].amount == MAX_ELEMENTS){
            index = (index +1) % tableSize;
            continue;
        }        


        node * prev = NULL;

        for (node * n = table[index].head; n != NULL ; n= n->next){
            if ( n->key == key)
                return n->value;
            
            prev = n;
        }
        
        //create and set newNode
        node * newNode = new node;
        newNode->next = NULL;
        newNode->prev = prev;
        newNode->key = key;
        newNode->value = type2();
        
        if ( prev)
            prev->next = newNode;

        table[index].amount++;
        // move middle element right and left
      
        if ( table[index].amount == 1)
            table[index].head = table[index].middleElement = newNode;   
    /*
        if ( table[index].amount % 2 == 0)    
            table[index].middleElement = table[index].middleElement->next;
        */
        if ( table[index].amount == MAX_ELEMENTS)
            filledEntries++;
    
        return newNode->value;
    }     
    
}

/*function_identifier: add up all ASCII values in key and mods the sum by tableSize
*paarmeters: key
*return value: value */
template <class type1, class type2>
int hashMap<type1, type2>::hashFunction(std::string key) const
{
    return ( tolower(key[0]) - 'a') % tableSize;
}

/*function_identifier: remap the entries 
*paarmeters: amt
*return value: none */
template <class type1, class type2>
void hashMap<type1, type2>::resize(int amt)
{
	list * oldTable = table;
	int oldSize = tableSize;
	tableSize += amt;
	filledEntries = 0;
	table = new list[tableSize];

	for (int i = 0; i < tableSize; i++)
	{
		table[i].head = NULL;
		table[i].middleElement = NULL;
		table[i].amount = 0;
	}

	node * it;

	//goes through each table entry of the oldTable (obsolete table)
	//and maps them to an element of the new table and stores the same
	//value into the location where it's found in the new table
	for (int i = 0; i < oldSize; i++)
		for (it = oldTable[i].head; it != NULL; it = it->next)
			(*this)[it->key] = it->value;


	//Deallocate old table
	for (int i = 0; i < oldSize; i++)
	{
		node * del1, * del2;
		del1 = oldTable[i].head;

		while (del1 != NULL)
		{
			del2 = del1->next;
			delete del1;
			del1 = del2;
		}
	}
	delete [] oldTable;
}
