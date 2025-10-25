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

















return 0;
}
