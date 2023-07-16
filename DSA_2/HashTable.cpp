// Hash Table Assignment

#include <algorithm>
#include <climits>
#include <iostream>
#include <string> // atoi
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

const unsigned int DEFAULT_SIZE = 179;

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

/**
 * Define a class containing data members and methods to
 * implement a hash table with chaining.
 */
class HashTable {

private:
    // Define structures to hold bids
    struct Node {
        Bid bid;
        unsigned int key;
        Node *next;

        // default constructor
        Node() {
            key = UINT_MAX; // Denotes empty since initialization
            next = nullptr;
        }

        // initialize with a bid
        Node(Bid aBid) : Node() {
            bid = aBid;
        }

        // initialize with a bid and a key
        Node(Bid aBid, unsigned int aKey) : Node(aBid) {
            key = aKey;
        }
    };

    // List to represent chain in each bucket
    vector<Node> nodes;

    unsigned int tableSize = DEFAULT_SIZE;

    unsigned int hash(int key);

public:
    HashTable();
    HashTable(unsigned int size);
    virtual ~HashTable();
    void Insert(Bid bid);
    void PrintAll();
    void Remove(string bidId);
    Bid Search(string bidId);
};

/**
 * Default constructor
 */
HashTable::HashTable() {
    // Initalize node structure by resizing tableSize
    nodes.resize(tableSize);
}

/**
 * Constructor for specifying size of the table
 * Use to improve efficiency of hashing algorithm
 * by reducing collisions without wasting memory.
 */
HashTable::HashTable(unsigned int size) {
    // invoke local tableSize to size with this->
    this->tableSize = size;
    // resize nodes size
    nodes.resize(tableSize);
}


/**
 * Destructor
 */
HashTable::~HashTable() {
    // erase nodes beginning, utilizing begin vector function
    nodes.erase(nodes.begin());
}

/**
 * Calculate the hash value of a given key.
 * Note that key is specifically defined as
 * unsigned int to prevent undefined results
 * of a negative list index.
 *
 * @param key The key to hash
 * @return The calculated hash
 */
unsigned int HashTable::hash(int key) {
    return key % tableSize;
}

/**
 * Insert a bid
 *
 * @param bid The bid to insert
 */
void HashTable::Insert(Bid bid) {
    // create the key for the given bid. Hash function takes int so we must convert using atoi.
    unsigned key = hash(atoi(bid.bidId.c_str()));
    // retrieve node using key
    Node* previousNode = &(nodes.at(key));

    if (previousNode == nullptr) {
        // assign this node to the key position
        Node* newNode = new Node(bid, key);
        // insert this node to the node vector
        nodes.insert(nodes.begin() + key, (*newNode));
    }
    // else if node is not used
    else if (previousNode->key == UINT_MAX) {
        // assign old node key to UNIT_MAX, set to key, set old node to bid and old node next to null pointer
        previousNode->key = key;
        previousNode->bid = bid;
        previousNode->next = nullptr;
    }
    // else find the next open node
    else {
        // add new newNode to end because of collision
        while (previousNode->next != nullptr) {
            previousNode = previousNode->next;
        }
        previousNode->next = new Node(bid, key);
    }
}

/**
 * Print all bids
 */
void HashTable::PrintAll() {
    // for node begin to end iterate
    for (auto i = nodes.begin(); i != nodes.end(); ++i)
    {
        //if key not equal to UINT_MAx
        if (i->key != UINT_MAX)
        {
            // output key, bidID, title, amount and fund
            cout << "Key " << i->key << ": " << i->bid.bidId << " | " << i->bid.title << " | " << i->bid.amount << " | " << i->bid.fund << endl;
            // node is equal to next iter
            Node* node = i->next;
            // while node not equal to nullptr
            while (node != nullptr) {
                // output key, bidID, title, amount and fund
                cout << "Key " << i->key << ": " << i->bid.bidId << " | " << i->bid.title << " | " << i->bid.amount << " | " << i->bid.fund << endl;
                // node is equal to next node
                node = node->next;
            }
        }    
    }
}

/**
 * Remove a bid
 *
 * @param bidId The bid id to search for
 */
void HashTable::Remove(string bidId) {
    // set key equal to hash atoi bidID cstring
    unsigned int key = hash(atoi(bidId.c_str()));
    // retrieve node using key
    Node* node = &(nodes.at(key));
    // if node is not empty
    if (node->key != UINT_MAX) {
        // if bid id matches
        if (node->bid.bidId.compare(bidId) == 0) {
            cout << "Remove top nodes for " << bidId << endl;
            // if the pointer to the next node is null, meaning this is the only item in the chain
            if (node->next == nullptr) {
                // set the key to empty and return from function
                node->key == UINT_MAX;
                return;
            } 
            else {
                // otherwise skip this node
                nodes.at(key) = *(node->next);
                return;
            }
        }
        // iterating through chain to find the matching node
        else {
            Node* current = node->next;
            Node* previous = node;
            // if current node is not empty
            while (current != nullptr) {
                // and if current nodes bid ID matches id argument
                if (current->bid.bidId.compare(bidId) == 0) {
                    // delete node
                    previous->next = current->next;
                    delete current;
                    current = nullptr;
                    return;
                }
                // progress pointers
                previous = current;
                current = current->next;
            }
        }
        
    }
}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid HashTable::Search(string bidId) {
    Bid bid;

    // create the key for the given bid
    unsigned int key = hash(atoi(bidId.c_str()));
    Node* node = &(nodes.at(key));

    // If node is not empty and the bidId matches
    if (node != nullptr && node->key != UINT_MAX && node->bid.bidId.compare(bidId) == 0) {
        // return bid
        return node->bid;
    }
    // if no entry found for the key
    if (node == nullptr || node->key == UINT_MAX) {
        // return bid
        return bid;
    }
    // while node not null
    while (node != nullptr) {
        // if the current node matches, return it
        if (node->key != UINT_MAX && node->bid.bidId.compare(bidId) == 0) {
            return node->bid;
        }
        //otherwise keep traversing the list
        node = node->next;
    }

    return bid;
}

//============================================================================
// Static methods used for testing
//============================================================================

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
void loadBids(string csvPath, HashTable* hashTable) {
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
            hashTable->Insert(bid);
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

// Entry Point
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98002"; //98109
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98002"; //98109
    }

    // Define a timer variable
    clock_t ticks;

    // Define a hash table to hold all the bids
    HashTable* bidTable;

    Bid bid;
    bidTable = new HashTable();
    
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
            loadBids(csvPath, bidTable);

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bidTable->PrintAll();
            break;

        case 3:
            ticks = clock();

            bid = bidTable->Search(bidKey);

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
            bidTable->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
