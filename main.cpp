/*Name: Ahmed Abdel Ghany, NSHE ID: 2001445844, Cs 302 Assignment 9
 *description:  
 *Input: file name
 *Output: all paths from start to final destination*/


/*Algorithm: reading thr file that has street names,
  using hasg map toconstruct adjacency list, stack to decide,
  the order of the streets, function gat paths decide hom many,
  pathes and if there is a path or no using graph and nodesinpaths*/

#include <iostream>
#include <unistd.h>
#include <cmath>
#include <cstdlib>
#include <string> 
#include "hashMap.h"
#include "adjacency.h"
#include "myStack.h"
#include <iomanip>
#include <fstream>

bool getPaths ( string current , string finalDestination ,
	hashMap < string , vertex <string > > graph ,
	hashMap <string , bool >& nodesInPath ,
	myStack <string >& recStack , int& pathNo );

int main(){


	fstream infile;
    string file, start, end, street1, street2;
    
    cout<<endl;
    while(true){
        
        cout << "Last one ): ";
        cin>> file;

        infile.open(file);

        if (infile.is_open())
            break;
    } 

    infile>> start>>end;

    cout<<endl;
    hashMap<string, vertex<string> > adjList;
    
    while(true){

        infile>>street1>>street2;

        if (infile.eof())
            break;

        adjList[street1].addEdge(street2);
    }

 	infile.close();   
    hashMap<string, bool> nodesPaths;
    myStack <string> rec;
    int num = 0;
    
    getPaths(start, end, adjList, nodesPaths, rec, num);
    
    cout<<endl;
	return 0;
}

bool getPaths ( string current , string finalDestination ,
hashMap < string , vertex <string > > graph ,
hashMap <string , bool >& nodesInPath ,
myStack <string >& recStack , int& pathNo ){

    if ( current == finalDestination){
        
        pathNo++;
        cout << "Path " << pathNo<< " : ";

        myStack <string> stack1 (recStack);
        myStack <string> stack2;

        while(!stack1.isEmpty()){

            stack2.push(stack1.top());
            stack1.pop();
        }
        
        // print paths found
        while(!stack2.isEmpty()){

            cout<< stack2.top() << " <=> ";
            stack2.pop();
        }
        cout<< finalDestination<<endl;
        return true;
    }
    
    nodesInPath [current] = true;
    recStack.push(current);
    
    for ( string v : graph[current]){
        
        if (nodesInPath[v] == true)
            continue;
        
        for ( string v2 : graph[v])
            if ( v2 == current)
                goto label;
        
        continue;

    label:
        getPaths(v, finalDestination, graph, nodesInPath, recStack, pathNo);
    
    }
    recStack.pop();
    nodesInPath[current] = false;
    return pathNo > 0;
}
