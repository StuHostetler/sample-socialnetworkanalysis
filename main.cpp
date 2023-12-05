//include libraries that your code uses
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> 
#include <map>
//#include "Project3a.h"
#include "Graph.h"

using namespace std;

///////////////// Before submitting your code
//1) uncomment this part since zyBooks use it.
/* int main(int argc, const char* argv[]) {
    if (argc != 2)
    {
        std::cout << "./project3 inputFile" << std::endl;
        return EXIT_FAILURE;
    }
    string inputFileName = argv[1]; */
    
///////////////////// uncomment above befofre submitting on zyBooks /////////////////
//2) Comment the next 2 lines below
int main(void) {
    string inputFileName = "input7.txt";    //Do NOT change the name "inputFileName" since used above

    //Add your code //

    //Orignally I used a vector to hold the account list and a tree to map out the connections from the node of greatest influence
    //Not suprizingly on the large dataset test it would hang
    //So the vector was scrapped entirely and instead a map was used to hold the entries

    //A significant chunk of the project was redone just to set up the map

    //SETUP
    //vector<Account> accList;
    map<string,Account> accList;
    string sbuffer1, sbuffer2;
    ifstream finput;
    Account* abuffer;
    list<string> lbuffer;
    bool next=false;
    finput.open(inputFileName);

    //START FILLING THE LIST
    while (!finput.eof()) {
        finput >> sbuffer1 >> sbuffer2;
        //Sanitize inputs
        for (auto& cha : sbuffer1) { cha = tolower(cha); } 
        for (auto& cha : sbuffer2) { cha = tolower(cha); } 
        
        if (accList.find(sbuffer1)==accList.end()) {
            //Can't find the entry, which means it doesn't exist and needs to be created
            abuffer = new Account(sbuffer1, sbuffer2);
            accList[sbuffer1] = *abuffer;
        }
        else {
            //It exists, add to the entry's inbound list
            accList[sbuffer1].addToInbound(sbuffer2);
        }

        if (finput.peek() == -1) { break; } 
        //Again there's input files with rogue endlines that require this catch
    }
    finput.close();

    //SECOND PASS ON THE LIST, ADD REMAINING ACCOUNTS THAT ARE BEING FOLLOWED BUT HAVE NO FOLLOWERS
    //These entries will only appear on the tree if the root or near root accounts are following them
    finput.open(inputFileName);
    while (!finput.eof()) {
        finput >> sbuffer1 >> sbuffer2;
        //Sanitize inputs
        for (auto& cha : sbuffer2) { cha = tolower(cha); } 

        if (accList.find(sbuffer2)==accList.end()) {
            //Create the empty account if it doesn't exist
            //Doesn't matter if we end up with an attempt to add a duplicate node since the map will disreguard it
            abuffer = new Account(sbuffer2);
            accList[sbuffer2] = *abuffer;
        }

        if (finput.peek() == -1) { break; } 
        //Again there's input files with rogue endlines that require this catch
    }
    finput.close();

    //FIND THE ROOT NODE ACCORDING TO THE HIGHEST IN-DEGREE FACTOR, ALPHABETICAL ORDER BREAKING TIES
    string root_node={};

    //Calculate the degree factor and then check if it's the biggest one so far
    //Since the list is ordered we only need to find the first instance of an entry being larger
    for (map<string,Account>::iterator itr = accList.begin(); itr!=accList.end(); itr++) { 
        itr->second.findDegrees();
        if (root_node.empty() || itr->second.getIndegrees() > accList[root_node].getIndegrees()) {
            root_node=itr->first;
        }
    }

    //PRINT FIRST OUTPUT LINE
    cout << "The root user is " << accList[root_node].getName() << ", with in-degree centrality of " << accList[root_node].getIndegrees() << "." << endl <<
        "There are " << accList.size() << " users in the social network." << endl;

    //TRAVEL THE 'TREE' USING THE MAP AND COLLECT EVERY FOLLOW CONNECTION 2 DEGREES FROM THE ROOT
    traverseDepth(accList, root_node, 0);

    //DEBUG CODE
    /*int count=1;
     for (map<string,Account>::iterator itr = accList.begin(); itr!=accList.end(); itr++) {
        lbuffer=itr->second.getInbound();
        cout << count << ": " << itr->first << " / " << itr->second.getName() << endl << "Out: ";
        for (list<string>::iterator itr2 = lbuffer.begin(); itr2 != lbuffer.end(); itr2++) {
            cout << *itr2 << " ";
        }
        cout << endl << "Factor: " << itr->second.getIndegrees() << endl << endl;
        count++;
    } */  


   return 0;   
}