#include <list>
#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include "Graph.h"

//ACCOUNT
//Controls the actual connected list aspect of the account dataset
//Some code was commented out as it was rendered obselete due to the transition from vector storage to map storage

using namespace std;

Account::Account() {
    name={};
    indegree=0;
    //outdegree=0;
}

Account::Account(string a) {
    name=a;
    indegree=0;
    //outdegree=0;
}

Account::Account(string a, string b) {
    name=a;
    inbound.push_back(b);
    indegree=0;
    //outdegree=0;
}

string Account::getName() { return name; }
//list<string> Account::getOutbound() { return outbound; }
list<string> Account::getInbound() { return inbound; }

void Account::setName(string a) {
    name=a;
    return;
}

/* void Account::setOutbound(list<string> a) {
    outbound=a;
    return;
} */

void Account::setInbound(list<string> a) {
    inbound=a;
    return;
}

/* void Account::addToOutbound(string a) {
    //Add to the list, then sanitize the list to ensure duplicates are removed
    outbound.push_back(a);
    outbound.sort();
    outbound.unique();
    return;
} */

void Account::addToInbound(string a) {
    //Add to the list, then sanitize the list to ensure duplicates are removed
    inbound.push_back(a);
    inbound.sort();
    inbound.unique();
    return;
}

void Account::findDegrees() {
    indegree=inbound.size();
    //outdegree=outbound.size();
    return;
}

int Account::getIndegrees() { return indegree; }
//int Account::getOutdegrees() { return outdegree; }


//DATA TREE
//Originally this used a complex system of pointers and vectors to try to build and traverse the tree
//But since the map has both the name of the node and its child nodes it only needs to do map lookups via recursion
//Rendering about fifty lines of code obselete

void traverseDepth(map<string,Account> &accList, string key, int d) {
    //Print the node's name and its depth in the tree
    map<string,Account>::iterator itr = accList.find(key);
    cout << itr->second.getName() << " (" << d << ")" << endl;
    //Iterate through the edge list, and through recursion visit each node down until reaching depth 2
    if (d<2) {
        list<string> lbuffer=itr->second.getInbound();
        for (list<string>::iterator itr2 = lbuffer.begin(); itr2 != lbuffer.end(); itr2++) {
            traverseDepth(accList, *itr2, d+1);
        }
    }
    return;
}