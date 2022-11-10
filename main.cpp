#include <iostream>
#include <bits/stdc++.h>
#include <vector>

using std::vector;
using std::map;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::stack;

string vt;
string vn;
vector<map<string, vector<string>>> DFAState;
vector<pair<string, string>> extensionEpsilon;
map<pair<int, char>, pair<char, int>> actionMap;
map<pair<int, char>, int> gotoMap;

void showStateStack(const stack<int>& stateStack);

void showChStack(const stack<char>& chStack);

void setVT();

void showVT();

void showVN();

void setVN();

void setActionMap();

void showActionMap();

void setGotoMap();

void showGotoMap();

void setDFAState();

void showDFAState();

void setExtensionEpsilon();

void showExtensionEpsilon();

pair<string, string> separateEpsilon(const string &epsilon);

void analyseProcess();

string formatStr(const string& initialStr);

void errorInf(const string &formatStr, size_t errorLoc);

int main() {
    setVN();
    showVN();
    setVT();
    showVT();
    setExtensionEpsilon();
    showExtensionEpsilon();
    setDFAState();
    showDFAState();
    setActionMap();
    showActionMap();
    setGotoMap();
    showGotoMap();
    analyseProcess();
}

void setDFAState() {
    cout << "please enter the number of DFA: " << endl;
    size_t number;
    cin >> number;
    string inputStr;
    string left;
    string right;
    for (size_t count = 0; count < number; count++) {
        cout << "enter the epsilon in state " << count << ": (enter \'quit\' to end input)" << endl;
        cin >> inputStr;
        map<string, vector<string>> curEpsilons;
        while (inputStr != "quit") {
            pair<string, string> epsilonPair = separateEpsilon(inputStr);
            right = epsilonPair.second;
            left = epsilonPair.first;
            curEpsilons[left].emplace_back(right);
            cin >> inputStr;
        }
        DFAState.emplace_back(curEpsilons);
    }
    cout << "read DFA successfully!" << endl;
}

void showDFAState() {
    cout << "show DFAState as follow: " << endl;
    size_t count = 0;
    for (const auto &map: DFAState) {
        cout << "state " << count << ": " << endl;
        for (const auto &pair: map) {
            for (const auto &str: pair.second) {
                cout << pair.first << " -> " << str << endl;
            }
        }
        count++;
    }
}

void setExtensionEpsilon() {
    cout << "please enter the extension epsilon: (enter \'quit\' to end)" << endl;
    string epsilon;
    cin >> epsilon;
    while (epsilon != "quit") {
        pair<string, string> epsilonPair = separateEpsilon(epsilon);
        extensionEpsilon.emplace_back(epsilonPair);
        cin >> epsilon;
    }
    cout << "read extension epsilon successfully! " << endl;
}

void showExtensionEpsilon() {
    cout << "extensionEpsilon show as follow: " << endl;
    int count = 0;
    for (const auto &pair: extensionEpsilon) {
        cout << count << "\t" << pair.first << " -> " << pair.second << endl;
        count ++;
    }
}

pair<string, string> separateEpsilon(const string &epsilon) {
    size_t eraseLoc = epsilon.find('-');
    pair<string, string> res;
    string left = epsilon;
    string right = epsilon;
    left = left.erase(eraseLoc);
    right = right.erase(0, eraseLoc + 2);
    res.first = left;
    res.second = right;
    return res;
}

void setActionMap() {
    cout << "please enter the pair of action map: (one line one pair,format: 2 / S 9, enter \'0 0 0 0\' to end)"
         << endl;
    int state, number;
    char chVt, opt;
    cin >> state >> chVt >> opt >> number;
    while (!(state == 0 && chVt == '0' && opt == '0' && number == 0)) {
        pair<int, char> leftPair;
        pair<char, int> rightPair;
        leftPair.first = state;
        leftPair.second = chVt;
        rightPair.first = opt;
        rightPair.second = number;
        actionMap[leftPair] = rightPair;
        cin >> state >> chVt >> opt >> number;
    }
    cout << "read actionMap successfully!" << endl;
}

void setGotoMap() {
    cout << "please enter the pair of goto map: (one line one pair,format: 0 E 2, enter \'0 0 0\' to end)" << endl;
    int state, nextState;
    char chVn;
    cin >> state >> chVn >> nextState;
    while (!(state == 0 && chVn == '0' && nextState == 0)) {
        pair<int, char> leftPair(state, chVn);
        gotoMap[leftPair] = nextState;
        cin >> state >> chVn >> nextState;
    }
    cout << "read goto map successfully!" << endl;
}

void setVT() {
    std::cout << "Please enter the number of VT: " << std::endl;
    size_t sizeOfVT;
    std::cin >> sizeOfVT;
    std::cout << "Please enter the vt: (one line one vt)" << std::endl;
    char tempVT;
    for (int i = 0; i < sizeOfVT; i++) {
        std::cin >> tempVT;
        vt.append(1, tempVT);
    }
    std::cout << "Have set the vt successfully!" << std::endl;
}

void setVN() {
    std::cout << "Please enter the number of VN: " << std::endl;
    size_t sizeOfVN;
    std::cin >> sizeOfVN;
    std::cout << "Please enter the vn: (one line one vn)" << std::endl;
    char tempVT;
    for (int i = 0; i < sizeOfVN; i++) {
        std::cin >> tempVT;
        vn.append(1, tempVT);
    }
    std::cout << "Have set the vn successfully!" << std::endl;
}

void showVT() {
    cout << "show vt as follow: " << endl;
    for (auto ch: vt) {
        cout << ch << " ";
    }
    cout << endl;
}

void showVN() {
    cout << "show vn as follow: " << endl;
    for (auto ch: vn) {
        cout << ch << " ";
    }
    cout << endl;
}

void showActionMap() {
    cout << "show action map as follow: " << endl;
    for (auto pair: actionMap) {
        cout << "< " << pair.first.first << " , " << pair.first.second << " > : " << pair.second.first
             << pair.second.second << endl;
    }
    cout << endl;
}

void showGotoMap() {
    cout << "show goto map as follow: " << endl;
    for(auto pair: gotoMap){
        cout << "< " << pair.first.first << " , " << pair.first.second << " > : " << pair.second << endl;
    }
    cout << endl;
}

void analyseProcess() {
    string initialStr, fStr;
    stack<int> stateStack;
    stack<char> chStack;
    stateStack.push(0);
    cout << "please enter the str you want to analyse: " << endl;
    getchar();
    std::getline(cin,initialStr);
    cout << "initialStr is : " << initialStr << endl;
    fStr = formatStr(initialStr);
    cout << "formatStr is : " << fStr << endl;
    auto it = fStr.begin();
    while(it != fStr.end()){
        cout << endl;
        showStateStack(stateStack);
        showChStack(chStack);
        pair<int, char> currentPair(stateStack.top(), *it);
        cout << "currentPair is :< " << currentPair.first << " , " << currentPair.second << " >" << endl;
        pair<char, int> curOperator = actionMap[currentPair];
        if(curOperator.first != '\0'){
            cout << "curOperator is: " << curOperator.first << curOperator.second << endl;
        }
        else{
            cout << "there is no operation for current Pair in action map! " << endl;
        }
        if(curOperator.first == 'S'){
            stateStack.push(curOperator.second);
            chStack.push(*it);
            it ++;
        }
        else if(curOperator.first == 'R'){
            pair<string, string> curEpsilon = extensionEpsilon[curOperator.second - 1];
            cout << "reduce epsilon: " << curEpsilon.first << "->" <<curEpsilon.second << endl;
            if(curOperator.second == 1){
                cout << "accept this str!" << endl;
                break;
            }
            size_t lenOfEpsilonRight = curEpsilon.second.size();
            for(size_t i = 0; i < lenOfEpsilonRight; i ++){
                stateStack.pop();
                chStack.pop();
            }
            chStack.push(curEpsilon.first[0]);
            pair<int, char> gotoPair(stateStack.top(), chStack.top());
            cout << "current goto pair is : < " << gotoPair.first << " , " << gotoPair.second << " > " << endl;
            int nextState = gotoMap[gotoPair];
            cout << "nextState is : " << nextState << endl;
            if(nextState != 0){
                stateStack.push(nextState);
            }
            else{//goto 空
                cout << " there is no next state for current pair in goto map! " << endl;
                size_t errorLoc = it - fStr.begin();
                errorInf(fStr, errorLoc);
            }
        }
        else{//action 空
            size_t errorLoc = it - fStr.begin();
            errorInf(fStr, errorLoc);
        }
    }
}

string formatStr(const string& initialStr) {
    string res;
    bool haveNum = false;
    for(char ch: initialStr){
        if(!isspace(ch)){
            if(!isdigit(ch)){
                if(haveNum){
                    res.append(1 , 'n');
                    haveNum = false;
                }
                res.append(1 , ch);
            }
            else{
                haveNum = true;
            }
        }
    }
    if(haveNum)
        res.append(1 , 'n');
    res.append(1, '$');
    return res;
}

void errorInf(const string &formatStr, size_t errorLoc) {
    cout << formatStr << endl;
    for(size_t i = 0; i < errorLoc; i ++){
        cout << " ";
    }
    cout << "^" << endl;
    exit(-1);
}

void showStateStack(const stack<int> &stateStack) {
    cout << "state stack show as follow: (left is stack top)" << endl;
    stack<int> tempStack = stateStack;
    while(!tempStack.empty()){
        cout << tempStack.top() << " ";
        tempStack.pop();
    }
    cout << endl;
}

void showChStack(const stack<char> &chStack) {
    cout << "char stack show as follow: (left is stack top)" << endl;
    stack<char> tempStack = chStack;
    while(!tempStack.empty()){
        cout << tempStack.top() << " ";
        tempStack.pop();
    }
    cout << endl;
}
