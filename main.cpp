#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;

int main() {
    // ---------------------- VARIABLE DECLARATIONS ----------------------
    // Player tool and inventory settings
    bool hasAxe = false;
    int rocketsNeeded = 0;
    int carrotsNeeded = 0; // number of carrots needed to defeat a shulker
    int maxRockets = 0;
    int maxCarrots = 0;
    int carrotsPerShulker = 0;

    // Player and fortress coordinates
    int playerX = 0;
    int playerZ = 0;
    int fortressX = 0;
    int fortressZ = 0;

    // Inventory tracking
    int totalCarrots = 0;
    int totalRockets = 0;
    int carrotsUsed = 0;
    int rocketsUsed = 0;
    int numWood = 0;
    int numShulker = 0;
    int maxShulker = 0;
    int maxWood = 0;

    // Constant representing the max items per stack
    const int STACK_MAX = 64;

    // 2D arrays to hold player items and their quantities
    char itemList[3][9];
    int itemAmount[3][9];

    // Each path’s value (used later in expedition section)
    int exploreValue[4];

    // File stream variables for input/output
    ifstream playerInfo;      // input file for player data
    ifstream expeditionFile;  // input file for expedition data
    ofstream outFile;         // output file for updated player data

    // File names
    string fileName = "";
    string outfileName = "updatedPlayer.txt";

    // ---------------------- PART 1: READ PLAYER INVENTORY FILE ----------------------
    string player_inventory_input = " ";
    cout << "Please load your character data." << endl;
    cin >> player_inventory_input;
    playerInfo.open(player_inventory_input);

    // Check if player file opened successfully
    if (playerInfo.is_open()) {
        string temporaryString = " ";

        // --- Read Line 1: Player coordinates (X Z) ---
        getline(playerInfo, temporaryString);
        playerX = stoi(temporaryString.substr(0, temporaryString.find(' ')));        // extract X
        playerZ = stoi(temporaryString.substr(temporaryString.find(' ') + 1));      // extract Z
        // Example: "100 250" → playerX = 100, playerZ = 250

        // --- Read Line 2: Whether the player has an axe ---
        getline(playerInfo, temporaryString);
        if (temporaryString == "0")
            hasAxe = false;
        else
            hasAxe = true;
        // "1" means has axe, "0" means does not have axe

        // --- Read Line 3: Carrots needed per shulker ---
        getline(playerInfo, temporaryString);
        carrotsPerShulker = stoi(temporaryString); // e.g., "3" → each shulker takes 3 carrots

        // --- Remaining lines: inventory data in format "ItemID ItemAmount" ---
        char currentItem = ' ';
        int itemCount = 0;
        int currentRow = 0;
        int currentColumn = 0;

        // Each line might look like: "C 12" (12 carrots), "R 8" (8 rockets)
        while (getline(playerInfo, temporaryString)) {
            currentItem = temporaryString[0]; // the first character is the item ID
            itemCount = stoi(temporaryString.substr(temporaryString.find(' ') + 1)); // extract quantity

            // Store item and count into 2D inventory arrays
            itemList[currentRow][currentColumn] = currentItem;
            itemAmount[currentRow][currentColumn] = itemCount;

            // Track total carrots and rockets for convenience
            if (itemList[currentRow][currentColumn] == 'C') {
                totalCarrots += itemAmount[currentRow][currentColumn];
            }
            if (itemList[currentRow][currentColumn] == 'R') {
                totalRockets += itemAmount[currentRow][currentColumn];
            }

            // Move to the next column/row position in 3x9 grid
            if (currentColumn < 8) {
                currentColumn++;
            } else {
                currentRow++;
                currentColumn = 0;
            }
        }
    } else {
        cout << "Failure to open player inventory file" << endl;
    }
    
    // ---------------------- PART 2: STRING PARSING TEST ----------------------
    //ask the user to open the file
    string player_expedition_input = " ";
    cout << "Please load your expedition data" << endl;
    cin >> player_expedition_input;
    expeditionFile.open(player_expedition_input);
    
    //if statement that checks if the file opened succesfully
    //all of this is to get the formula and value to compare to the other paths
    //all stored variables are temporary and they will be removed for the next path
    string readString = "";
    string concatenatedString = "";
    int treesEncountered = 0;
    int shulkersEncountered = 0;
    int rocketsUsedThisPath = 0;

    if(expeditionFile.is_open()){
        for(int i = 0; i < 4; i++){
            concatenatedString = "";
            treesEncountered = 0;
            shulkersEncountered = 0;
            rocketsUsedThisPath = 0;
            //expecting a space somehwere in the input, and put into fortress coordinates
            getline(expeditionFile, readString, ',');
            for(int k = 0; k < readString.length(); k++){
                if(readString[k] == ' '){
                    continue;
                }else
                concatenatedString = concatenatedString + readString[k];
            }
            fortressX = stoi(concatenatedString);
            cout << fortressX << endl;
            concatenatedString = "";
            getline(expeditionFile, readString, ',');
            for(int k = 0; k < readString.length(); k++){
                if(readString[k] == ' '){
                    continue;
                }
                concatenatedString = concatenatedString + readString[k];
            }
            fortressZ = stoi(concatenatedString);
            cout << fortressZ << endl;
            concatenatedString = "";
            //***************************************************************************************/
            //preparing the parsing by removing spaces from the string
            bool isTree = false;
            bool isRocket = false;
            bool isShulker = false;

            getline(expeditionFile, readString);
            for(int j = 0; j < readString.length(); j++){
                //cout << static_cast<int>(readString[j]) << endl;
                if(readString[j] == ' '){
                    continue;
                }
                if(readString[j] == '\r'){
                    continue;
                }
                concatenatedString = concatenatedString + readString[j];
                //cout << concatenatedString << endl; 
            }
            if(concatenatedString[concatenatedString.length() - 1] == ','){
                concatenatedString = concatenatedString.substr(0, concatenatedString.length() - 1);
            }
            cout << concatenatedString << endl;
            //cout << concatenatedString.length() << endl;
        

            
            
        }
    }
    else{
        cout << "Failure to open the file" << endl;
    }
    return 0;
}
