#ifndef Graph_h
#define Graph_h

#include <list>
#include <string>

using namespace std;
//If that line isn't here the project won't compile

class Account {
public:
    Account();
    Account(string a);
    Account(string a, string b);
    string getName();
    //list<string> getOutbound();
    list<string> getInbound();
    void setName(string a);
    //void setOutbound(list<string> a);
    void setInbound(list<string> a);
    //void addToOutbound(string a);
    void addToInbound(string a);
    void findDegrees();
    int getIndegrees();
    //int getOutdegrees();
private:
    string name;
    //list<string> outbound;
    list<string> inbound;
    int indegree;
    //int outdegree;
};

void traverseDepth(map<string,Account> &accList, string key, int d);

#endif