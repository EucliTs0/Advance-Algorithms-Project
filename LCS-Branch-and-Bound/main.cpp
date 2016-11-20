#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

struct Node{
    unsigned int firstIndex;
    unsigned int secondIndex;
    string lcs;
};

// Global Variables:
unsigned upperBound;
const unsigned MAX_NUMBER_OF_CHARS=130;
unsigned firstChars[MAX_NUMBER_OF_CHARS];
unsigned secondChars[MAX_NUMBER_OF_CHARS];
Node bestNode;
string first;
string second;
long unsigned int numCall=0;
vector<Node> currentNodes;

// Defining visitedNodes vector in order to keep visited nodes and cut repeating branches.
vector<Node> visitedNodes;

// Functions:

void Initialize(Node &node){
    node.firstIndex=0;
    node.secondIndex=0;
    node.lcs="";
}


bool IndexHitEnd(Node node){
    return node.firstIndex==first.size()||node.secondIndex==second.size();
}

bool UpperBoundReach(){
    return upperBound==bestNode.lcs.size();
}

bool IsEqual(Node firstNode,Node secondNode){
    return firstNode.firstIndex==secondNode.firstIndex && firstNode.secondIndex==secondNode.secondIndex && firstNode.lcs==secondNode.lcs;
}

vector<Node>::iterator GetCurrentBestOption(){
    vector<Node>::iterator iterator=currentNodes.begin();
    vector<Node>::iterator bestPosition=iterator;
    iterator++;
    while(iterator!=currentNodes.end()){
        Node temp1={bestPosition->firstIndex,bestPosition->secondIndex,bestPosition->lcs};
        Node temp2={iterator->firstIndex,iterator->secondIndex,iterator->lcs};
        if(temp2.lcs.size()>temp1.lcs.size()){
            bestPosition=iterator;
        }
        iterator++;
    }
    return bestPosition;
}

bool IsVisited(Node node){
    vector<Node>::iterator iterator=visitedNodes.begin();
    while(iterator!=visitedNodes.end()){
        Node temp={iterator->firstIndex,iterator->secondIndex,iterator->lcs};
        if(IsEqual(node,temp)){
            return true;
        }
        iterator++;
    }
    return false;
}



bool IsInfeasible(Node node){
    long unsigned firstSize=node.firstIndex-node.lcs.size()+bestNode.lcs.size();
    long unsigned secondSize=node.secondIndex-node.lcs.size()+bestNode.lcs.size();
    bool cond1=firstSize>first.size();
    bool cond2=secondSize>second.size();
    if(cond1||cond2){
        return true;
    }
    return false;
}

void CleanInfeasibles(){
    if(visitedNodes.size()>0){
        vector<Node>::iterator iterator=visitedNodes.begin();
        while(iterator!=visitedNodes.end()){
            Node node={iterator->firstIndex,iterator->secondIndex,iterator->lcs};
            long unsigned firstSize=node.firstIndex-node.lcs.size()+bestNode.lcs.size();
            long unsigned secondSize=node.secondIndex-node.lcs.size()+bestNode.lcs.size();
            bool cond1=firstSize>first.size();
            bool cond2=secondSize>second.size();
            if(cond1||cond2){
                visitedNodes.erase(iterator);
            }
            if(iterator!=visitedNodes.end()){
                iterator++;
            }
        }
    }
}

void RemoveNodeFromCurrent(Node node){
    vector<Node>::iterator iterator=currentNodes.begin();
    while(iterator!=currentNodes.end()){
        Node temp={iterator->firstIndex,iterator->secondIndex,iterator->lcs};
        if(IsEqual(node,temp)){
            currentNodes.erase(iterator);
            return;
        }
        iterator++;
    }
}

void End(){
    currentNodes.clear();
    visitedNodes.clear();
}

void EqualityBranch(Node node){
    Node newNode={node.firstIndex+1,node.secondIndex+1,node.lcs+first[node.firstIndex]};
    currentNodes.push_back(newNode);
    if(bestNode.lcs.size()<newNode.lcs.size()){
        Node temp={bestNode.firstIndex,bestNode.secondIndex,bestNode.lcs};
        bestNode=newNode;
        if(UpperBoundReach()){
            End();
        }else{
            visitedNodes.push_back(temp);
            CleanInfeasibles();
        }
    }
}

void InEqualityBranch(Node node){
    Node newNode1={node.firstIndex+1,node.secondIndex,node.lcs};
    Node newNode2={node.firstIndex,node.secondIndex+1,node.lcs};
    if(!IsInfeasible(newNode1)){
        currentNodes.push_back(newNode1);
    }
    if(!IsInfeasible(newNode2)){
        currentNodes.push_back(newNode2);
    }
}

void LCS(Node node){
    if(!IsVisited(node)){
        numCall++;
        if(IndexHitEnd(node)){
            //End of Branch, Terminating This Branch and moving current node to visitedOnes.
            RemoveNodeFromCurrent(node);
            visitedNodes.push_back(node);
        }else{
            if(first[node.firstIndex]==second[node.secondIndex]){
                EqualityBranch(node);
            }else{
                InEqualityBranch(node);
            }
            // Moving node from current to visited
            RemoveNodeFromCurrent(node);
            if(!IsEqual(bestNode,node)){
                visitedNodes.push_back(node);
            }
        }
    }else{
        // Remove from current pool:
        RemoveNodeFromCurrent(node);
    }
}

void PrintCurrentNodes(){
    vector<Node>::iterator iterator=currentNodes.begin();
    while(iterator!=currentNodes.end()){
        Node node={iterator->firstIndex,iterator->secondIndex,iterator->lcs};
        cout<<"\nGozine: "<<setw(7)<<node.lcs<<" , i="<<setw(3)<<node.firstIndex<<" , j="<<setw(3)<<node.secondIndex<<" , lcsSize: "<<node.lcs.size();
        iterator++;
    }
    cout<<endl;
}

void PrintVisitedNodes(){
    vector<Node>::iterator iterator=visitedNodes.begin();
    while(iterator!=visitedNodes.end()){
        Node node={iterator->firstIndex,iterator->secondIndex,iterator->lcs};
        cout<<"\nGozine: "<<setw(7)<<node.lcs<<" , i="<<setw(3)<<node.firstIndex<<" , j="<<setw(3)<<node.secondIndex<<" , lcsSize: "<<node.lcs.size();
        iterator++;
    }
    cout<<endl;
}

void PrintLCS(){
    //cout<<"\nfirstIndex: "<<best.firstIndex<<"\nsecondIndex: "<<best.secondIndex<<endl;
    cout<<"\n\nLCS: "<<bestNode.lcs<<endl;
    cout<<"\nUpperBound: "<<upperBound;
    cout<<"\nSize of Visited Pool: "<<visitedNodes.size()<<endl;
    cout<<"\nSize of First String: "<<first.size()<<" , Size of Second String: "<<second.size()<<endl;
    cout<<"\nNumber of Calls to LCS Function: "<<numCall<<endl;
}

void CalculateUpperBound(){
    upperBound=0;
    for(unsigned i=0;i<MAX_NUMBER_OF_CHARS;i++){
        firstChars[i]=0;
        secondChars[i]=0;
    }
    for(unsigned counter=0;counter<first.size();counter++){
        firstChars[(unsigned)first[counter]]++;
    }
    for(unsigned counter=0;counter<second.size();counter++){
        secondChars[(unsigned)second[counter]]++;
    }
    for(unsigned i=0;i<MAX_NUMBER_OF_CHARS;i++){
        upperBound+=firstChars[i]>secondChars[i]?secondChars[i]:firstChars[i];
    }
}

void CalculateLCS(){
    Initialize(bestNode);
    currentNodes.push_back(bestNode);
    while(currentNodes.size()>0){
        vector<Node>::iterator bestPosition=GetCurrentBestOption();
        Node node={bestPosition->firstIndex,bestPosition->secondIndex,bestPosition->lcs};
        LCS(node);
        //PrintCurrentNodes();
    }
}

void GetStrings(){
    cout<<"\nPlease Enter First String: ";
    cin>>first;
    cout<<"\nPlease Enter Second String: ";
    cin>>second;
}

int main()
{
    char answer='y';
    do{
        GetStrings();
        CalculateUpperBound();
        CalculateLCS();
        PrintLCS();
        cout<<"\n'Y' To Exit, Anything Else To Continue : ";
        cin>>answer;
    }while(answer!='Y' && answer!='y');
    return 0;
}

