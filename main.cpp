#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;

int main() {
// Variable declarations
bool hasAxe = false;
int rocketsNeeded = 0;
int carrotsNeeded = 0;
int maxRockets = 0;
int maxCarrots = 0;
int carrotsPerShulker = 0;
//Variables for location calculation
int playerX = 0;
int playerZ = 0;
int fortressX = 0;
int fortressZ = 0;
// Player inventory variables
int totalCarrots = 0;
int totalRockets = 0;
int carrotsUsed = 0;
int rocketsUsed = 0;
int numWood = 0;
int numShulker = 0;
int maxShulker = 0;
int maxWood = 0;
// Expedition Variables
string expedition = "";
int bestValue = 0; // used for the current best Value path
// Useful variables but not needed. Comment out if unused.
int row = 0;
int col = 0;
const int STACK_MAX = 64;
// Messages:
string playerPrompt = "Please load your character data. \n";
string playerNotFound = "Erorr: The player file cannot be found. \n";
string explorePrompt = "Please load the exploration path file \n";
// Array Declaration HERE.
char itemList[3][9];
int itemAmount[3][9];
int exploreValue[4];
// File stream variables
ifstream playerInfo;
ifstream expeditionFile;
ofstream outFile;
string fileName = "";
string outfileName = "updatedPlayer.txt";
// YOUR CODE HERE

//part 1 reading from a file and players inventory
string player_inventory_input = " ";
cout << "Please load your character data." << endl;
cin >> player_inventory_input;
playerInfo.open(player_inventory_input);


if(playerInfo.is_open()){
    string temporaryString = " ";
    //--------------------------------------------------------------------------
    //runs if the correct file was opened. 
    //read the first line with the coordinates of the player
    //parse the string to extract player X and Z and move to those variables
    getline(playerInfo, temporaryString);
    playerX = stoi(temporaryString.substr(0, temporaryString.find(' ')));
    playerZ = stoi(temporaryString.substr(temporaryString.find(' ') + 1));
    //cout << playerX << endl;
    //cout << playerZ << endl;
    //--------------------------------------------------------------------------
    //read the second line of the file
    //1 or 0 will dertime axe true or not
    getline(playerInfo, temporaryString);
    if(temporaryString == "0")
        hasAxe = false;
    else
        hasAxe = true;
    //--------------------------------------------------------------------------
    //reading the third row, amount of carrots to defeat shulker, apparently
    getline(playerInfo, temporaryString);
    carrotsNeeded = stoi(temporaryString);
    //--------------------------------------------------------------------------
    //reading all remaining rows in the format (itemID itemAmount)
    char currentItem = ' ';
    int  itemCount = 0;
    int currentRow = 0;
    int currentColumn = 0;

    while(getline(playerInfo, temporaryString)){
        currentItem = temporaryString[0];
        //cout << "Current item is " << currentItem << endl;
        itemCount = stoi(temporaryString.substr(temporaryString.find(' ') + 1));
        //cout << "The item count is " << itemCount << endl;
        //input the character into the correct 2d array index. 
        //cout << "currentRow is " << currentRow << endl;
        //cout << "Current column is " << currentColumn << endl;
        //arrays are itemList and itemAmount

        itemList[currentRow][currentColumn] = currentItem;
        //cout << "item list at current is " << itemList[currentRow][currentColumn] << endl;

        itemAmount[currentRow][currentColumn] = itemCount; 
        //cout << "item amount at current is " << itemAmount[currentRow][currentColumn] << endl << endl;

        //carrot track
        if(itemList[currentRow][currentColumn] == 'C'){
            totalCarrots += itemAmount[currentRow][currentColumn];
            //cout << "total carrots are" << totalCarrots << endl;
        }
        //rocket track
        if(itemList[currentRow][currentColumn] == 'R'){
            totalRockets += itemAmount[currentRow][currentColumn];
            //cout << "total rockets are" << totalRockets << endl;
        }

        if(currentColumn < 8){
            currentColumn++;
        }else{
            currentRow++;
            currentColumn = 0;
        }
    } 
}else{
    cout << "Failure to open player inventory file" << endl;
}

//outer loop for the rows
for(int i = 0; i < 3; i++){
    for(int k = 0; k < 9; k++){
        //cout << itemList[i][k] << " " << itemAmount[i][k] << endl;
    }
}
//cout << "The total carrots are " << totalCarrots << endl;
//cout << "The total rockets are " << totalRockets << endl;

//Part 2----------------------------------------------------------------------
//reading and parsing through a string test
//"T,4,S,12,R,5,T,8,S,3"
string readingTest = "T,2.5,S,1.5,R,3.0"; //12 trees, 15 shulkers, 5 rockets //current error, it is reading each individual index
//fix, current integer as a string and append integer string until a comma is scanned
int tempTreeAmount = 0;
int tempShulkerAmount = 0;
int tempRocketsNeeded = 0;
int currentCommaIndex = readingTest.find(',');
bool isTree = false;
bool isShulker = false;
bool isRocket = false;
string currentInt = "";
for(int i = 0; i < readingTest.length(); i++){
    string currentCharacter = "";
    currentCharacter = readingTest[i];
    
    if(currentCharacter == ","){
        if(currentInt != "" && isTree == true){
            tempTreeAmount += stoi(currentInt);
            isTree = false;
            currentInt = "";
        }
        if(currentInt != "" && isShulker == true){
            tempShulkerAmount += stoi(currentInt);
            isShulker = false;
            currentInt = "";
        }
        if(currentInt != "" && isRocket == true){
            tempRocketsNeeded += stoi(currentInt);
            isRocket = false;
            currentInt = "";
        }
        continue;
    }

    if(currentCharacter == "T"){
        isTree = true;
        continue;
    }   
    if(currentCharacter == "S"){
        isShulker = true;
        continue;
    }
    if(currentCharacter == "R"){
        isRocket = true;
        continue;
    }

    currentInt = currentInt + currentCharacter;

     if(i == readingTest.length()-1){
        if(isTree == true){
            tempTreeAmount += stoi(currentInt);
            isTree = false;
            currentInt = "";
        }
        if(isShulker == true){
            tempShulkerAmount += stoi(currentInt);
            isShulker = false;
            currentInt = "";
        }
        if(isRocket == true){
            tempRocketsNeeded += stoi(currentInt);
            isRocket = false;
            currentInt = "";
        }
     }



}
cout << endl;
cout << "Trees in the way is: " << tempTreeAmount << endl;
cout << "Shulkers amount is: " << tempShulkerAmount << endl;
cout << "Rockets needed is:" << tempRocketsNeeded << endl;
return 0;
}
