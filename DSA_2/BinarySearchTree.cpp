// Binary search tree implementation

#include <iostream>
#include <time.h>
#include "CSVparser.hpp"

using namespace std;

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

// Internal structure for tree node
struct Node {
    Bid bid;
    Node* left;
    Node* right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a bid
    Node(Bid aBid) :
            Node() {
        bid = aBid;
    }
};

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Bid bid);
    void inOrder(Node* node);
    void postOrder(Node* node);
    void preOrder(Node* node);
    Node* removeNode(Node* node, string bidId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void deleteTree(Node*& root);
    void PostOrder();
    void PreOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    //root is equal to nullptr. Top level to hold the empty tree.
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
    deleteTree(root);
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // call inOrder fuction and pass root. This is the helper function.
    inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    // postOrder root. This is the helper function.
    postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    // preOrder root. This is the helper function.
    preOrder(root);
}

/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {
    // if root equal to null ptr. If tree is empty
    if (root == nullptr) {
        // root is equal to new node bid
        root = new Node(bid);
    }
    // else if root is not empty
    else {
        // add Node root and bid
        addNode(root, bid);
    }
}



/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) {
    // remove node root bidID
    this->removeNode(root, bidId);
}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {
    // set current node equal to root
    Node* currentNode = root;
    // keep looping downwards until bottom reached or matching bidId found
    while (currentNode != nullptr) {
        // if match found, return current bid
        if (currentNode->bid.bidId.compare(bidId) == 0) {
            return currentNode->bid;
        }
        // if bid is smaller than current node then traverse left
        else if (bidId.compare(currentNode->bid.bidId) < 0) {
            currentNode = currentNode->left;
        }
        else {
            // traverse right
            currentNode = currentNode->right;
        }
    }
    // If nothing found, return empty bid
    Bid bid;
    return bid;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {

    // if node is larger then add to left
    if (node != nullptr && node->bid.bidId.compare(bid.bidId) > 0) {
        // if no left node
        if (node->left == nullptr) {
            // this node becomes left
            node->left = new Node(bid);
            return;
        }
        // else recurse down the left node
        else {
            addNode(node->left, bid);
        }
    }
    // else node is larger than add to right
    else if (node != nullptr && node->bid.bidId.compare(bid.bidId) < 0) {
        // if no right node
        if (node->right == nullptr) {
            // this node becomes right
            node->right = new Node(bid);
            return;
        }
        // else recurse down the right node
        else {
            addNode(node->right, bid);
        }
    }
}

/**
 * Remove a bid node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be removed
 */
Node* BinarySearchTree::removeNode(Node* node, string bidId) {
    // If node equal nullptr. Tree is empty
    if (node == nullptr) {
        // already empty, return node
        return node;
    }
    // if bid ID is less than current node bid Id
    else if (bidId.compare(node->bid.bidId) < 0) {
        // traverse left recursively
        node->left = removeNode(node->left, bidId);
    }
    // if bid ID is more than current node bid Id
    else if (bidId.compare(node->bid.bidId) > 0) {
        // traverse right recursively
        node->right = removeNode(node->right, bidId);
    }
    // if bid ID matches
    else {
        // node is a leaf node
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        }
        // node only has a child to the left
        else if (node->left != nullptr && node->right == nullptr) {
            // left child takes over node
            Node* tempNode = node;
            node = node->left;
            delete tempNode;
            tempNode == nullptr;
        }
        // node only has a child to the right
        else if (node->right != nullptr && node->left == nullptr) {
            // right child takes over node
            Node* tempNode = node;
            node = node->right;
            delete tempNode;
            tempNode == nullptr;
        }
        // node has a child to the right and to the left
        else if (node->right != nullptr && node->left != nullptr) {
            // traverse right to find minimum value of left subtree
            Node* tempNode = node->right;
            // while left child is not empty, continue traversing the left side
            while (tempNode->left != nullptr) {
                tempNode = tempNode->left;
            }
            // when minimum is found, copy minimum node data
            node->bid = tempNode->bid;
            // remove node on right side and set equal to minimum node found
            node->right = removeNode(node->right, tempNode->bid.bidId);
        }
    }
    return node;
}

void BinarySearchTree::inOrder(Node* node) {
    // Visit left subtree, then print self, followed by visit right subtree.
    //if node is not equal to null ptr. If node exists...
    if (node != nullptr) {
        //InOrder not left. Visit left subtree.
        inOrder(node->left);
        //output bidID, title, amount, fund
        cout << node->bid.bidId << " : " << node->bid.title << " | " << node->bid.amount << " | " << node->bid.fund << endl;
        //InOder right. Visit right subtree
        inOrder(node->right);
    }
}
void BinarySearchTree::deleteTree(Node*& root) {
    // Delete recursion
    //if node is not equal to null ptr. If node exists...
    if (root != nullptr) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
        root = nullptr;
    }
}

void BinarySearchTree::postOrder(Node* node) {
    // Visit left subtree, then right sub tree, followed by print self
    //if node is not equal to null ptr
    if (node != nullptr) {
        //postOrder left. Visit left subtree.
        postOrder(node->left);
        //postOrder right. Visit right subtree.
        postOrder(node->right);
        //output bidID, title, amount, fund
        cout << node->bid.bidId << " : " << node->bid.title << " | " << node->bid.amount << " | " << node->bid.fund << endl;
    }
}

void BinarySearchTree::preOrder(Node* node) {
    // Print self, then visit left subtree, followed by right subtree
    //if node is not equal to null ptr
    if (node != nullptr) {
        //output bidID, title, amount, fund
        cout << node->bid.bidId << " : " << node->bid.title << " | " << node->bid.amount << " | " << node->bid.fund << endl;
        //preOrder left. Visit left subtree.
        preOrder(node->left);
        //preOrder right. Visit right subtree.
        preOrder(node->right);
    }  
}


// Testing functions

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bst->Insert(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

// Entry point
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98190";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98190";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bst);

            //cout << bst->Size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            ticks = clock();

            bid = bst->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 4:
            bst->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

	return 0;
}
