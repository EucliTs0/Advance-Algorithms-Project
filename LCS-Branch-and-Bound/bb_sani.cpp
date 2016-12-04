
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
//#include <boost/container/vector.hpp>



using namespace std;
vector<string> firstTextWords;
vector<string> secondTextWords;
int firstTextMaxWordSize;
int secondTextMaxWordSize;


struct Node{
    unsigned id;
    unsigned parentId;
    unsigned firstIndex;
    unsigned secondIndex;
    unsigned lcsLength;
    bool equal;
    inline bool operator==(const Node& node){
        return firstIndex == node.firstIndex && secondIndex == node.secondIndex && lcsLength == node.lcsLength;
    }
    inline bool operator!=(const Node& node){
        return !((*this)==node);
    }
    inline bool operator>(const Node& node){
        return lcsLength > node.lcsLength || (lcsLength==node.lcsLength && abs((int)(firstIndex-secondIndex))<abs((int)(node.firstIndex-node.secondIndex)));
    }
    Node& operator= (const Node & node){
        firstIndex = node.firstIndex;
        secondIndex = node.secondIndex;
        lcsLength = node.lcsLength;
        id = node.id;
        parentId = node.parentId;
        equal = node.equal;
        return (*this);
    }
   /* Node& operator++ (){
        lcsLength += firstTextWords[firstIndex].size();
        return (*this);
    }*/

};

const unsigned MAX_NUMBER_OF_CHARS = 130;
//const unsigned long MAX_Words = 1000;
unsigned firstChars[MAX_NUMBER_OF_CHARS];
unsigned secondChars[MAX_NUMBER_OF_CHARS];
vector<Node> currentNodes;
unsigned int lastId = 1;
// Defining visitedNodes vector in order to keep visited nodes and cut repeating branches.
vector<Node> visitedNodes;
Node bestNode;
long unsigned numCall = 0;
unsigned upperBound;
unsigned firstTextUB;
unsigned secondTextUB;

void Initialize(Node &node){
    node.id = lastId;
    lastId++;
    node.parentId = 0;
    node.firstIndex = 0;
    node.secondIndex = 0;
    node.lcsLength = 0;
    node.equal = false;
}

void Branch(Node &node,const Node &parent){
    node.id = lastId;
    lastId++;
    node.parentId = parent.id;
    node.firstIndex = parent.firstIndex;
    node.secondIndex = parent.secondIndex;
    node.lcsLength = parent.lcsLength;
    node.equal = false;
}

bool IsAtTheEnd(Node node){
    return node.firstIndex == firstTextWords.size() || node.secondIndex == secondTextWords.size();
}

Node GetCurrentBestOption(){
    Node best = currentNodes[0];
    for (unsigned index = 1; index < currentNodes.size(); index++){
        if (currentNodes[index]>best){
            best = currentNodes[index];
        }
    }
    return best;
}

bool IsRepeated(const Node &node, bool checkCurrent = true){
    if (visitedNodes.size()>0){
        for (unsigned index = 0; index < visitedNodes.size();index++){
            if (visitedNodes[index] == node){
                return true;
            }
        }
    }
    if (currentNodes.size()>0){
        if (checkCurrent){
            for (unsigned index = 0; index < currentNodes.size(); index++){
                if (currentNodes[index] == node){
                    return true;
                }
            }
        }
    }
    return false;
}

bool IsInfeasible(const Node &node){
    long unsigned firstSize = node.firstIndex - node.lcsLength + bestNode.lcsLength;
    long unsigned secondSize = node.secondIndex - node.lcsLength + bestNode.lcsLength;
    bool cond1 = firstSize > firstTextWords.size();
    bool cond2 = secondSize > secondTextWords.size();
    if (cond1 || cond2){
        return true;
    }
    return false;
}

bool NeedsNoSaving(const Node &node){
    return node.firstIndex==0||node.secondIndex==0;
}

void CleanInfeasibles(){
    if (visitedNodes.size() > 0){
        for (unsigned index=0; index < visitedNodes.size(); index++){
            Node node = visitedNodes[index];
            long unsigned firstSize = node.firstIndex - node.lcsLength + bestNode.lcsLength;
            long unsigned secondSize = node.secondIndex - node.lcsLength + bestNode.lcsLength;
            bool cond1 = firstSize > firstTextWords.size();
            bool cond2 = secondSize > secondTextWords.size();
            if (cond1 || cond2){
                visitedNodes[index]=visitedNodes.back();
                visitedNodes.pop_back();
            }
        }

    }
}

void RemoveNodeFromCurrent(const Node &node){
    for (unsigned index = 0; index < currentNodes.size(); index++){
        if (currentNodes[index].id == node.id ){
            currentNodes[index] = currentNodes.back();
            currentNodes.pop_back();
            break;
        }
    }
}

void End(){
    currentNodes.clear();
    visitedNodes.clear();
}

// read files from file and preprocess them.
string GetFileInfo(string fileaddress){
    string line;
    char pause;
    string fileinfo="";
    ifstream input;
    input.open(fileaddress.c_str());
    if (input.is_open()){
        while (getline(input, line))
        {
            fileinfo += line;
        }
        input.close();
    }
    else{
        cout << "File Not Found: " << fileaddress << endl;
        cin >> pause;
        exit(0);
    }
    return fileinfo;
}

void ReadAndPreprocessTexts(){
    string folder = "./";
    string firstFile = folder + "orig_taska.txt";
    string secondFile = folder + "g0pA_taska.txt";
    string firstText = GetFileInfo(firstFile);
    string secondText = GetFileInfo(secondFile);
    cout << "First file's text length: "<<firstText.size() << endl;
    cout << "Second file's text length: " << secondText.size()<<endl;
    double firstTextWordLength=0;
    double secondTextWordLength=0;
    unsigned pointer = 0;
    firstTextMaxWordSize = 0;
    secondTextMaxWordSize = 0;

    while (pointer != firstText.size()){
        bool flag = true;
        string word = "";
        while (pointer != firstText.size() && flag){
            char ascii = firstText[pointer++];
            if (ascii >= 65 && ascii <= 91){
                // Uppers case to Lower case
                ascii += 32;
            }

            if (ascii >= 97 && ascii < 123){
                word += ascii;
            }
            else{
                flag = false;
            }
        }
        if (word.size()>0){
            firstTextWords.push_back(word);
            firstTextWordLength+=word.size();
            if (word.size()>firstTextMaxWordSize){
                firstTextMaxWordSize = word.size();
            }
        }
    }
    firstTextWordLength=firstTextWordLength/firstTextWords.size();
    cout << "\nNumber of Words in First Text: "<<firstTextWords.size() << endl;
    pointer = 0;
    while (pointer != secondText.size()){
        bool flag = true;
        string word = "";
        while (pointer != secondText.size() && flag){
            char ascii = secondText[pointer++];

            if (ascii >= 65 && ascii <= 91){
                // Uppers case to Lower case
                ascii += 32;
            }

            if (ascii >= 97 && ascii < 123){
                word+= ascii;
            }
            else{
                flag = false;
            }
        }
        if (word.size()>0){
            secondTextWords.push_back(word);
            secondTextWordLength+=word.size();
            if (word.size()>secondTextMaxWordSize){
                secondTextMaxWordSize = word.size();
            }
        }
    }
    secondTextWordLength=secondTextWordLength/secondTextWords.size();
    cout << "Number of Words in Second Text: " << secondTextWords.size()<<endl;
    upperBound = 0;
    for (unsigned i = 0; i < MAX_NUMBER_OF_CHARS; i++){
        firstChars[i] = 0;
        secondChars[i] = 0;
    }
    for (unsigned counter = 0; counter < firstText.size(); counter++){
        firstChars[(unsigned)firstText[counter]]++;
    }
    for (unsigned counter = 0; counter < secondText.size(); counter++){
        secondChars[(unsigned)secondText[counter]]++;
    }
    for (unsigned i = 0; i<MAX_NUMBER_OF_CHARS; i++){
        upperBound += firstChars[i]>secondChars[i] ? secondChars[i] : firstChars[i];
    }
    firstTextUB=upperBound/firstTextWordLength;
    secondTextUB=upperBound/secondTextWordLength;
    if(firstTextUB>secondTextUB){
        upperBound=firstTextUB;
    }else{
        upperBound=secondTextUB;
    }
    cout << "\nUpperBound: " << upperBound << endl;
}

Node FindNode(const unsigned id){
    for (unsigned index = 0; index < visitedNodes.size(); ++index){
        if (visitedNodes[index].id == id){
            Node node= visitedNodes[index];
            return node;
        }
    }
}

void PrintLCS(){
    //cout<<"\nfirstIndex: "<<best.firstIndex<<"\nsecondIndex: "<<best.secondIndex<<endl;
    string lcs = "";
    Node node = bestNode;
    vector<string> words;
    while (node.parentId != 0){
        if (node.equal){
            words.push_back(firstTextWords[node.firstIndex]);
        }
        node = FindNode(node.parentId);

        //bestNode = { iterator->id, iterator->parentId, iterator->firstIndex, iterator->secondIndex, iterator->lcsLength, iterator->equal };
    }
    if (node.equal){
        words.push_back(firstTextWords[node.firstIndex]);
    }
    unsigned length = words.size();
    //cout << lcs << endl;
    for (unsigned i = words.size()-1; i >0 ; i--){
        lcs += words[i] + " ";
    }
    cout << "LCS= \"" << lcs << "\"" << endl;
    cout << "\nLCS Length: " << lcs.size() << endl;
    cout << "\nSize of Visited Pool: " << visitedNodes.size() << endl;
    cout << "\nNumber of Calls to LCS Function: " << numCall << endl;
}

void Check(Node &node){
    if (IsAtTheEnd(node)){
        //End of Branch, Terminating This Branch and moving current node to visitedOnes.
        RemoveNodeFromCurrent(node);
        visitedNodes.push_back(node);
    }
    else{
        if (firstTextWords[node.firstIndex] == secondTextWords[node.secondIndex]){
            node.lcsLength++;
            node.equal = true;
        }
        else{
            node.equal = false;
        }
        if (node > bestNode){
            Node temp = bestNode;
            bestNode = node;
            CleanInfeasibles();
            if (upperBound == bestNode.lcsLength){
                PrintLCS();
                End();
            }
            else{
                if (!IsRepeated(temp)){
                    visitedNodes.push_back(temp);
                }
            }
        }
        if (!IsRepeated(node) && !IsInfeasible(node)){
            currentNodes.push_back(node);
        }
    }
}

void EqualityBranch(Node node){
    Node newNode;
    Branch(newNode, node);
    newNode.firstIndex++;
    newNode.secondIndex++;
    Check(newNode);
}

void InEqualityBranch(Node node){
    Node newNode1;
    Node newNode2;
    Branch(newNode1, node);
    Branch(newNode2, node);
    newNode1.firstIndex++;
    newNode2.secondIndex++;
    Check(newNode1);
    Check(newNode2);
}

void LCS(Node node){
    numCall++;
    if (IsAtTheEnd(node)){
        //End of Branch, Terminating This Branch and moving current node to visitedOnes.
        RemoveNodeFromCurrent(node);
        visitedNodes.push_back(node);
    }
    else{
        if (node.equal){
            EqualityBranch(node);
        }
        else{
            InEqualityBranch(node);
        }
        // Moving node from current to visited
        RemoveNodeFromCurrent(node);
        if (bestNode.id!=node.id && !IsRepeated(node, false) && !NeedsNoSaving(node)){
            visitedNodes.push_back(node);
        }
    }
}

void CalculateLCS(){
    Initialize(bestNode);
    if (firstTextWords[bestNode.firstIndex] == secondTextWords[bestNode.secondIndex]){
        bestNode.lcsLength++;
        bestNode.equal = true;
    }
    else{
        bestNode.equal = false;
    }
    Node node = { bestNode.id, bestNode.parentId, bestNode.firstIndex, bestNode.secondIndex, bestNode.lcsLength, bestNode.equal };

    LCS(node);
    while(currentNodes.size() > 0){
        Node node = GetCurrentBestOption();
        PrintLCS();
        LCS(node);
    }
}

int main(){
    char ans='n';
    do{
        ReadAndPreprocessTexts();
        CalculateLCS();
        cout << "\nDo you wish to continue(y/n)? ";
        cin >> ans;
    } while (ans=='y' || ans=='Y');
    return 0;
}
