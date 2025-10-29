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
    int itemsAdded = 0; //store the current index for later
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
            itemsAdded++;
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
    string cleanLine = "";
    int woodGathered = 0;
    int shulkersEncountered = 0;
    int rocketsUsedThisPath = 0;
    int travelingCost = 0;
int highestValueIndex = 0;
    if(expeditionFile.is_open()){
        for(int i = 0; i < 4; i++){
            cleanLine = "";
            woodGathered = 0;
            shulkersEncountered = 0;
            rocketsUsedThisPath = 0;
            travelingCost = 0;
            rocketsNeeded = 0;
            //expecting a space somehwere in the input, and put into fortress coordinates
            getline(expeditionFile, readString, ',');
            for(int k = 0; k < readString.length(); k++){
                if(readString[k] == ' '){
                    continue;
                }else
                cleanLine = cleanLine + readString[k];
            }
            fortressX = stoi(cleanLine);
            cleanLine = "";
            getline(expeditionFile, readString, ',');
            for(int k = 0; k < readString.length(); k++){
                if(readString[k] == ' '){
                    continue;
                }
                cleanLine = cleanLine + readString[k];
            }
            fortressZ = stoi(cleanLine);
            cleanLine = "";
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
                cleanLine = cleanLine + readString[j];
            }
            //check for any files with commas at the end of the line
            if(cleanLine[cleanLine.length() - 1] == ','){
                cleanLine = cleanLine.substr(0, cleanLine.length() - 1);
            }
            cout << cleanLine << endl;
            //---------------------------------------------------------------------------
            //extracting data from the clean string, nums are put into the currentInt string
            string currentInt = "";
            //T,4,S,62,R,4,S,2
            for(int j = 0; j < cleanLine.length(); j++){
                //checks whether the current index is an ID
                //sets id to true and continues to program to the next index
                if(cleanLine[j] == 'T'){
                    currentInt = "";
                    isTree = true;
                    continue;
                }
                else if(cleanLine[j] == 'R'){
                    currentInt = "";
                    isRocket = true;
                    continue;
                }
                else if(cleanLine[j] == 'S'){
                    currentInt = "";
                    isShulker = true;
                    continue;
                }
                if(cleanLine[j] == ',' && currentInt == ""){
                    continue;
                }
                if(cleanLine[j] == ',' && currentInt != ""){
                    if(isTree){
                        woodGathered += stoi(currentInt);
                        isTree = false;
                    }else if(isShulker){
                        shulkersEncountered += stoi(currentInt);
                        isShulker = false;
                    }else if(isRocket){
                        rocketsUsedThisPath += stoi(currentInt);
                        isRocket = false;
                    }
                    continue;
                }
                currentInt = currentInt + cleanLine[j];
                if(j == cleanLine.length() - 1){
                    if(isTree){
                        woodGathered += stoi(currentInt);
                        isTree = false;
                    }else if(isShulker){
                        shulkersEncountered += stoi(currentInt);
                        isShulker = false;
                    }else if(isRocket){
                        rocketsUsedThisPath += stoi(currentInt);
                        isRocket = false;
                    }
                    continue;
                }
            }
            travelingCost = abs(playerX - fortressX) + abs(playerZ - fortressZ);
            rocketsNeeded = (travelingCost + rocketsUsedThisPath) * 2;
            int currentPath = i;
            if(rocketsNeeded > totalRockets){
                exploreValue[currentPath] = 0;
            }
            else{
                if(!hasAxe){
                    woodGathered = 0;
                }
                carrotsNeeded = shulkersEncountered * carrotsPerShulker + woodGathered/3;
                
                if(carrotsNeeded > totalCarrots){
                    exploreValue[currentPath] = 0;
                }
                else{
                    exploreValue[currentPath] = -1 * (carrotsNeeded + rocketsNeeded * 2) + (shulkersEncountered * 100 + woodGathered * 5);
                    cout << "\nExpedition " << currentPath + 1 << " details:\n";
                    cout << "  Fortress coords: (" << fortressX << ", " << fortressZ << ")\n";
                    cout << "  Wood gathered: " << woodGathered << endl;
                    cout << "  Shulkers: " << shulkersEncountered << endl;
                    cout << "  Rockets used this path: " << rocketsUsedThisPath << endl;
                    cout << "  Traveling cost: " << travelingCost << endl;
                    cout << "  Rockets needed: " << rocketsNeeded << endl;
                    cout << "  Carrots needed: " << carrotsNeeded << endl;
                    cout << "  Value: " << exploreValue[currentPath] << endl;
                }
            } 
            currentPath++;
        }
            int highestValue = exploreValue[0];
            for(int h = 0; h < 4; h++){
                if (exploreValue[h] > highestValue) {
                    highestValue = exploreValue[h];
                    highestValueIndex = h;
                }
            }   
            cout << "The highest value expedition is path " << highestValueIndex + 1 
            << " with a value of " << highestValue << endl;
    }
    else{
        cout << "Failure to open the file" << endl;
    }
    
    //step 3, i need to extract the values from the best expedition
    
    //    -declare new ifstream variable that will be the best expedition
    ifstream bestExpedition;
    bestExpedition.open(player_expedition_input);

    if(bestExpedition.is_open()){
        //read the line that is dedicated to the best path
        string tempString = "";
        for (int y = 0; y < highestValueIndex; y++) {
            getline(bestExpedition, tempString);
        }

        //if the best expedition is the first line read the first line like normal.
        //copy all code from reading to get all values from best expedition

            cleanLine = "";
            woodGathered = 0;
            shulkersEncountered = 0;
            rocketsUsedThisPath = 0;
            travelingCost = 0;
            rocketsNeeded = 0;
            //expecting a space somehwere in the input, and put into fortress coordinates
            getline(bestExpedition, readString, ',');
            for(int k = 0; k < readString.length(); k++){
                if(readString[k] == ' '){
                    continue;
                }else
                cleanLine = cleanLine + readString[k];
            }
            fortressX = stoi(cleanLine);
            cleanLine = "";
            getline(bestExpedition, readString, ',');
            for(int k = 0; k < readString.length(); k++){
                if(readString[k] == ' '){
                    continue;
                }
                cleanLine = cleanLine + readString[k];
            }
            fortressZ = stoi(cleanLine);
            cleanLine = "";
            //***************************************************************************************/
            //preparing the parsing by removing spaces from the string
            bool isTree = false;
            bool isRocket = false;
            bool isShulker = false;


            getline(bestExpedition, readString);
            for(int j = 0; j < readString.length(); j++){
                //cout << static_cast<int>(readString[j]) << endl;
                if(readString[j] == ' '){
                    continue;
                }
                if(readString[j] == '\r'){
                    continue;
                }
                cleanLine = cleanLine + readString[j];
            }
            //check for any files with commas at the end of the line
            if(cleanLine[cleanLine.length() - 1] == ','){
                cleanLine = cleanLine.substr(0, cleanLine.length() - 1);
            }
            cout << "The best path line is " << cleanLine << endl;
            //---------------------------------------------------------------------------
            //extracting data from the clean string, nums are put into the currentInt string
            string currentInt = "";
            //T,4,S,62,R,4,S,2
            for(int j = 0; j < cleanLine.length(); j++){
                //checks whether the current index is an ID
                //sets id to true and continues to program to the next index
                if(cleanLine[j] == 'T'){
                    currentInt = "";
                    isTree = true;
                    continue;
                }
                else if(cleanLine[j] == 'R'){
                    currentInt = "";
                    isRocket = true;
                    continue;
                }
                else if(cleanLine[j] == 'S'){
                    currentInt = "";
                    isShulker = true;
                    continue;
                }
                if(cleanLine[j] == ',' && currentInt == ""){
                    continue;
                }
                if(cleanLine[j] == ',' && currentInt != ""){
                    if(isTree){
                        woodGathered += stoi(currentInt);
                        isTree = false;
                    }else if(isShulker){
                        shulkersEncountered += stoi(currentInt);
                        isShulker = false;
                    }else if(isRocket){
                        rocketsUsedThisPath += stoi(currentInt);
                        isRocket = false;
                    }
                    continue;
                }
                currentInt = currentInt + cleanLine[j];
                if(j == cleanLine.length() - 1){
                    if(isTree){
                        woodGathered += stoi(currentInt);
                        isTree = false;
                    }else if(isShulker){
                        shulkersEncountered += stoi(currentInt);
                        isShulker = false;
                    }else if(isRocket){
                        rocketsUsedThisPath += stoi(currentInt);
                        isRocket = false;
                    }
                    continue;
                }
            }
    }    
    //next step, make 2 1D arrays that will flatten the 2d arrays making sorting easier because it would be regular bubble sort




    char tempIdArray[27];
    int tempItemAmount[27];
    //add values into these arrays to make the final part simpler.
    for (int i = 0; i < 27; i++) {
        tempIdArray[i] = '~';
        tempItemAmount[i] = 0;
    }
    //input all item from 2d array into these temporary arrays
    int currentTempIndex = 0;
    for(int i = 0; i < 3; i++){ // for loop for 3 rows
        for(int k = 0; k < 9; k++){ // for loop for 9 columns
            tempIdArray[currentTempIndex] = itemList[i][k];
            tempItemAmount[currentTempIndex] = itemAmount[i][k];
            currentTempIndex++;
        }
    }
    // ---------------------- Part 3: Add Expedition Resources to Inventory ----------------------

// Step 1: Determine the starting index in the 1D inventory array
//         - Use the last filled slot from the player’s current inventory
//         - This will be where new items from the expedition begin
cout << endl << shulkersEncountered << endl;
cout << woodGathered << endl;
cout << "Current index outside the loop is " << itemsAdded << endl;
// Step 2: Check if any shulkers were gathered(shulkerEncountered variable for shulker shells amount)
//the current index that i need to insert to is 11 as an example of one line. 
//there are 11 items in the list, the max index that has an item is 10 and index 11 is the first index with no value

     if(shulkersEncountered > 0){
        cout << "Current index in the loop is " << itemsAdded << endl;
        while(itemsAdded < 27){
            if(shulkersEncountered <= 64){
                cout << "Shulker encountered is less than 64" << endl;
                tempIdArray[itemsAdded] = 'S';
                tempItemAmount[itemsAdded] = shulkersEncountered;
                itemsAdded++;
                break;
            }else{
                //if the shulkers is greater than 64 set the current index stack equal to 64
                cout << "Shulkers is more than 64" << endl;
                tempIdArray[itemsAdded] = 'S';
                tempItemAmount[itemsAdded] = 64;
                //subtract 64 from the amount of shulkers encountered
                shulkersEncountered -= 64;
                //increase the index tally
                itemsAdded++;
                //continue the loop to check and see if the next index of shulker is less than 64. 
                continue;
            }
        }
    }
    
    if(woodGathered > 0){
        while(itemsAdded < 27){
            if(woodGathered <= 64){
                cout << "Trees gathered is less than 64" << endl;
                tempIdArray[itemsAdded] = 'W';
                tempItemAmount[itemsAdded] = woodGathered;
                itemsAdded++;
                break;
            }else{
                tempIdArray[itemsAdded] = 'W';
                tempItemAmount[itemsAdded] = 64;
                //subtract 64 from the amount of wood gathered
                woodGathered -= 64;
                //increase the index tally
                itemsAdded++;
                //continue the loop to check and see if the next index of shulker is less than 64. 
                cout << "Trees is more than 64" << endl;
                continue;
            }
        }
    }
    //adding a tilde to the array after the position the position is called 
    while(itemsAdded < 27){
        tempIdArray[itemsAdded] = '~';
        tempItemAmount[itemsAdded] = 0;
        itemsAdded++;
    }

    // ----- TEST: Print inventory after adding items -----
    for(int i = 0; i < 27; i++){
        cout << tempIdArray[i] << ", " << tempItemAmount[i] << endl;
    }

    return 0;







    //todo- when the expedition returns a zero and the expedition is not possible and every single expedition is not possible
    // do not grab the resources from the file into the array. only fill the array with expedition values when the expedition is possible.
}
