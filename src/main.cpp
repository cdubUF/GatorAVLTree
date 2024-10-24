#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <regex>
using namespace std;
/* Note:
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope.
*/

class BST
{
    private:
        struct TreeNode
        {
            int height;
            string ID;
            string name;
            TreeNode *left;
            TreeNode *right;
            TreeNode(){
                height = 0;
                left = nullptr;
                right= nullptr;
            }
            TreeNode(string name, string ID){
                this->name = name;
                this->ID = ID;
                height = 0;
                left = nullptr;
                right= nullptr;
            }
        };

        TreeNode* root = nullptr;
        BST::TreeNode* helperInsert(TreeNode* helpRoot, string name, string ID);
        void helperRemoveID(TreeNode* &helpRoot, string ID);
        void helperInorder(TreeNode* helpRoot, vector<string>& returnVec);
        void helperPreorder(TreeNode* helpRoot, vector<string>& returnVec);
        void helperPostorder(TreeNode* helpRoot, vector<string>& returnVec);
        BST::TreeNode* helperRotateRight(TreeNode* helpRoot);
        BST::TreeNode* helperRotateLeft(TreeNode* helpRoot);
        void helperRemoveNth (TreeNode* &helpRoot, int n, int& count, bool& removed);
        void helperSearchID(TreeNode* helpRoot, string ID, string& returnString); // return first name
        void helperSearchName(TreeNode* helpRoot, string name, vector<string>& returnVec); // returns ID's with name passed in
        int checkHeight(TreeNode* helpRoot); // check height, 0 index
        void updateHeight(TreeNode* helpRoot); // updates height
    public:
        int levelCount();
        void rotateLeft();
        void rotateRight();
        void printSearchID(string ID);
        void printSearchName(string name);
        void printInorder();
        void printPreorder();
        void printPostorder();
        void printLevelCount();
        void removeNth(int n);
        vector<string> inorder();
        vector<string> preorder();
        vector<string> postorder();
        string searchID(string ID);
        vector<string> searchName(string name);
        void insert(string name, string ID);
        void remove(string ID);
};

// rotational functions ( not done)
BST::TreeNode* BST::helperRotateRight(BST::TreeNode* helpRoot) {
    // from lecture feb 5th
    BST::TreeNode* grandchild = helpRoot->left->right;
    BST::TreeNode* newParent = helpRoot->left;
    newParent->right = helpRoot;
    helpRoot->left = grandchild;
    return newParent;
}

BST::TreeNode* BST::helperRotateLeft(BST::TreeNode* helpRoot) {
    // from lecture feb 5th
    BST::TreeNode* grandchild = helpRoot->right->left;
    BST::TreeNode* newParent = helpRoot->right;
    newParent->left = helpRoot;
    helpRoot->right = grandchild;
    return newParent;
}

// functions for height checking and update (not done)

int BST::checkHeight(BST::TreeNode *helpRoot) {
    if (helpRoot == nullptr){
        return 0;
    }
    queue<TreeNode*> q;
    int count = 1;
    q.push(helpRoot);

    while(!q.empty()){
        TreeNode* curr = q.front();
        q.pop();
        if(curr->left != nullptr){
            q.push(curr->left);
            count ++;
        }
        else if (curr->right != nullptr){
            q.push(curr->right);
            count ++;
        }
    }
    return count;
}

void BST::updateHeight(BST::TreeNode *helpRoot) {
    // lecture code from feb7th
    helpRoot->height = 1 + max((helpRoot->right == nullptr ? 0 : helpRoot->right->height), (helpRoot->left == nullptr ? 0 : helpRoot->left->height));
}

// remove functions (done

void BST::helperRemoveID(BST::TreeNode* &helpRoot, string ID) {
    if (helpRoot == nullptr){
        return;
    }
    if(ID.compare(helpRoot->ID) < 0){
        helperRemoveID(helpRoot->left, ID);
    }
    else if(ID.compare(helpRoot->ID) > 0){
        helperRemoveID(helpRoot->right, ID);
    }
    else{ // id matches, now we remove
        // case 1 no children!
        if(helpRoot->left == nullptr && helpRoot->right == nullptr){
            delete helpRoot;
            helpRoot = nullptr;
        }
        // case 3 two children
        else if (helpRoot->left != nullptr && helpRoot->right != nullptr){
                BST::TreeNode* curr = helpRoot->left;
                while(curr->right != nullptr){
                    curr = curr->right;
                }
                helpRoot->ID = curr->ID;
                helpRoot->name = curr->name;
                helperRemoveID(helpRoot->left, curr->ID);
        }
        // case 2 one child
        else{
            BST::TreeNode* child = (helpRoot->left != nullptr) ? helpRoot->left : helpRoot->right;
            BST::TreeNode* currentNode = helpRoot;
            helpRoot = child;
            delete currentNode;
        }
    }

}

void BST::helperRemoveNth(BST::TreeNode* &helpRoot, int n, int& count, bool& removed) {
    if (helpRoot == nullptr || removed){
        return;
    }

    helperRemoveNth(helpRoot->left, n, count, removed);

    if(count == n && !removed){
        helperRemoveID(helpRoot, helpRoot->ID);
        removed = true;
        return;
    }

    count++;
    helperRemoveNth(helpRoot->right, n, count, removed);
}

// traversal helper functions preorder, inorder, postorder (done)
void BST::helperInorder(BST::TreeNode* helpRoot, vector<string>& returnVec)
{
    if(helpRoot == nullptr) {

    }
    else
    {
        helperInorder(helpRoot->left, returnVec);
        returnVec.push_back(helpRoot->name);
        helperInorder(helpRoot->right, returnVec);

    }
}

void BST::helperPreorder(BST::TreeNode *helpRoot, vector<string> &returnVec) {
    if(helpRoot == nullptr) {

    }

    else
    {
        returnVec.push_back(helpRoot->name);
        helperPreorder(helpRoot->left, returnVec);
        helperPreorder(helpRoot->right, returnVec);
    }
}

void BST::helperPostorder(BST::TreeNode *helpRoot, vector<string> &returnVec) {
    if(helpRoot == nullptr) {

    }
    else
    {
        helperPostorder(helpRoot->left, returnVec);
        helperPostorder(helpRoot->right, returnVec);
        returnVec.push_back(helpRoot->name);
    }
}

// helper insert (not done)
BST::TreeNode* BST::helperInsert(TreeNode* helpRoot, string name, string ID)
{
    if (helpRoot == nullptr)
        return new TreeNode(name, ID);
    else if (ID.compare(helpRoot->ID) < 0)
        helpRoot->left = helperInsert(helpRoot->left, name, ID);
    else
        helpRoot->right = helperInsert(helpRoot->right, name, ID);

    // update height ( code from Feb 7th lecture )
//    helpRoot->height = 1 + max((helpRoot->right == nullptr ? 0 : helpRoot->right->height), (helpRoot->left == nullptr ? 0 : helpRoot->left->height));
      updateHeight(helpRoot);

    // if tree is right heavy
    if(checkHeight(helpRoot->left) - checkHeight(helpRoot->right) == -2){
        // check if right's subtree is left heavy
        if(checkHeight(helpRoot->right->left) - checkHeight(helpRoot->right->right) == 1){
            // perform  Right-Left Rotation
            // RightLeft()
            helpRoot = helperRotateRight(helpRoot);
            helpRoot = helperRotateLeft(helpRoot);
            // update height
            updateHeight(helpRoot);
        }
        else{
            // perform left rotation
            helpRoot = helperRotateLeft(helpRoot);
            // update height
            updateHeight(helpRoot);
        }
    }
    else if (checkHeight(helpRoot->left) - checkHeight(helpRoot->right) == 2){
        if(checkHeight(helpRoot->left->left) - checkHeight(helpRoot->left->right) == -1){
            // perform  Left-Right Rotation
            // LeftRight()
            helpRoot->left = helperRotateLeft(helpRoot->left);
            helpRoot = helperRotateRight(helpRoot);
            // update height
            updateHeight(helpRoot);
        }
        else{
            // perform Right rotation
            helpRoot = helperRotateRight(helpRoot);
            // update height
            updateHeight(helpRoot);
        }
    }
    return helpRoot;
}

// helper search functions (done)

void BST::helperSearchID(BST::TreeNode* helpRoot, string ID, string& returnString) {
    returnString = "unsuccessful";
    if (helpRoot != nullptr){
        if (helpRoot->ID == ID){
            returnString = helpRoot->name;
            return;
        }
        else if (ID.compare(helpRoot->ID) < 0){
            helperSearchID(helpRoot->left, ID, returnString);
        }
        else {
            helperSearchID(helpRoot->right, ID, returnString);
        }
    }
}

void BST::helperSearchName(BST::TreeNode *helpRoot, string name, vector<string>& returnVec) {
    if (helpRoot != nullptr){
        if (helpRoot->name == name){
            returnVec.push_back(helpRoot->ID);
        }
            helperSearchName(helpRoot->left, name, returnVec);
            helperSearchName(helpRoot->right, name, returnVec);
    }
}

// main functions


vector <string> BST::searchName(string name) {
    vector<string> returnVec;
    helperSearchName(this->root, name, returnVec);
    return returnVec;
}
string BST::searchID(string ID) {
    string returnString;
    helperSearchID(this->root, ID, returnString);
    return returnString;
}
vector<string> BST::inorder()
{
    vector<string> returnVec;
    helperInorder(this->root, returnVec);
    return returnVec;
}

vector<string> BST::preorder() {
    vector<string> returnVec;
    helperPreorder(this->root, returnVec);
    return returnVec;
}

vector<string> BST::postorder() {
    vector<string> returnVec;
    helperPostorder(this->root, returnVec);
    return returnVec;
}

int BST::levelCount() {
    return checkHeight(this->root);
}



void BST::insert(string name, string ID)
{
    this->root = helperInsert(this->root, name, ID);

}
  // rotational functions for main function
void BST::rotateRight() {
    helperRotateRight(this->root);
}

void BST::rotateLeft() {
    helperRotateLeft(this->root);
}


  // printing function

void BST::printInorder() {
    vector<string> printVec = inorder();
    for(int i = 0; i < printVec.size(); i++){
        if (i == printVec.size() - 1){
            cout << printVec[i];
        }
        else {
            cout << printVec[i] << ", ";
        }
    }
    cout << endl;
}

void BST::printPreorder() {
    vector<string> printVec = preorder();
    for(int i = 0; i < printVec.size(); i++){
        if (i == printVec.size() - 1){
            cout << printVec[i];
        }
        else {
            cout << printVec[i] << ", ";
        }
    }
    cout << endl;
}

void BST::printPostorder() {
    vector<string> printVec = postorder();
    for(int i = 0; i < printVec.size(); i++){
        if (i == printVec.size() - 1){
            cout << printVec[i];
        }
        else {
            cout << printVec[i] << ", ";
        }
    }
    cout << endl;
}

void BST::printLevelCount() {
    cout << levelCount() << endl;
}

void BST::printSearchID(string ID) {
    string returnString = searchID(ID);
    cout << returnString << endl;
}

void BST::printSearchName(string name) {
    vector<string> printVec = searchName(name);
    if (printVec.size() == 0){
        cout << "unsuccessful" << endl;
    }
    else{
        for (int i = 0; i < printVec.size(); i++) {
            cout << printVec[i] << endl;
        }
    }
}

void BST::remove(string ID) {
    if (searchID(ID) == "unsuccessful") {
        cout << "unsuccessful" << endl;
    }
    else{
        helperRemoveID(this->root, ID);
        cout << "successful" << endl;
    }
}

void BST::removeNth(int n) {
    int count = 0;
    bool removed = false;
    helperRemoveNth(this->root, n, count, removed);
    if (removed){
        cout << "successful" << endl;
    }
    else{
        cout << "unsuccessful" << endl;
    }
}

// validate Functions
// found on online GBD
bool validInsert(string command, string& ID, string& name) {

    regex findInsert = regex("^insert\\s+\"([a-zA-Z]+)\"\\s+(\\d{8})$");
    smatch matches;
    bool isInsert = regex_match(command, matches, findInsert);

    if (isInsert) {
        name = matches[1].str();
        ID = matches[2].str();
        return true;
    } else {
        return false;
    }
}

bool validRemove(string command, string& ID){
    regex findRemove = regex("remove\\s+(\\d{8})$");
    smatch matches;
    bool isRemove = regex_match(command, matches, findRemove);

    if (isRemove){
        if (matches.size() == 2){
            ID = matches[1].str();
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

bool validSearchID(string command, string& ID){
    regex findSearchID = regex("^search\\s+(\\d{8})$");
    smatch matches;
    bool isSearchID = regex_match(command, matches, findSearchID);

    if (isSearchID){
        if (matches.size() == 2){
            ID = matches[1].str();
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}
bool validSearchName(string command, string& name){
    regex findSearchname = regex("^search\\s+\"([a-zA-Z]+)\"");
    smatch matches;
    bool isSearchname = regex_match(command, matches, findSearchname);

    if (isSearchname){
        if (matches.size() == 2){
            name = matches[1].str();
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}
bool validRemoveInorder(string command, int& n){
    regex findRemoveInorder = regex("^removeInorder\\s+(\\d{1})$");
    smatch matches;
    bool isRemoveInorder = regex_match(command, matches, findRemoveInorder);

    if (isRemoveInorder){
        if (matches.size() == 2){
            n = stoi(matches[1].str());
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}
//int main(int argc, char * argv[]){
//    BST myBST;
//    int lines = 0;
//    cin >> lines;
//    cin.ignore();
//    string command, ID, name;
//    int n;
//    for (int i = 0; i < lines; i++){
//        getline(cin, command);
//        if (validInsert(command, ID, name)){
//            myBST.insert(name, ID);
//            cout << "successful" << endl;
//        }
//        else if(validRemove(command, ID)){
//            myBST.remove(ID);
//        }
//        else if(validSearchID(command, ID)){
//            myBST.printSearchID(ID);
//        }
//        else if(validSearchName(command, name)){
//            myBST.printSearchName(name);
//        }
//        else if(command == "printInorder"){
//            myBST.printInorder();
//        }
//        else if(command == "printPreorder"){
//            myBST.printPreorder();
//        }
//        else if(command == "printPostorder"){
//            myBST.printPostorder();
//        }
//        else if(command == "printLevelCount"){
//            myBST.printLevelCount();
//        }
//        else if(validRemoveInorder(command, n)){
//            myBST.removeNth(n);
//        }
//        else{
//            cout << "unsuccessful" << endl;
//        }
//    }
//	return 0;
//}

