#include<iostream>
#include<string>

using namespace std;

const int arrayDimension = 3; //for the tictactoe size e.g : arrayDimension = 3 (equals to 3x3 size)
const int playerNumber = 2;
const int totalArrayNum = arrayDimension*arrayDimension;
int currentPlayer = 2; // as a counter for changing players
int cubeArray[arrayDimension][arrayDimension][arrayDimension];
int arrayCoordinates[3];
int player1Input[totalArrayNum][3];
int player2Input[totalArrayNum][3];
string dummyInput;

struct{
    string mainlogo = R"(  _______          _____ _   _____       _____         
 |__ /   \   ___  |_   _(_)_|_   _|_ _ _|_   _|__  ___ 
  |_ \ |) | |___|   | | | / _|| |/ _` / _|| |/ _ \/ -_)
 |___/___/          |_| |_\__||_|\__,_\__||_|\___/\___|
                                                       )";
    string instructions = R"(
Welcome to our 3D-TicTacToe, where it will test your spatial intelligence in a
form of 3D game. 
    
    The Instructions are:
    1. Player 1 starts first
    2. Players will input their dimension, and the x and y of the dimension
    3. The cycle continues until there's a win condition and program terminates
    
Enjoy :)
press enter to proceed
    )";
} attributes;

bool number_validation(string inputNumber, int min = 0, int max = 0){
    for(char i : inputNumber){
        if(isdigit(i) == false){
            cout << "Not a valid input, try again" << endl;
            return false;
        }
    }
    if(min != 0 || max != 0){
        if(stoi(inputNumber) > max || min > stoi(inputNumber)){
            cout << "Input must be from " << min << " to " << max << endl;
            return false;
        }
    }
    return true;
}

void playerSwap(int *currentPlayer){
    if(*currentPlayer == 1){
        *currentPlayer = 2;
    }
    else if(*currentPlayer == 2){
        *currentPlayer = 1;
    }
    cout << "Player " << *currentPlayer << " turn" << endl;
}

void arrayFill(int array[arrayDimension][arrayDimension][arrayDimension]){ /*
    change counter to 1 for first time filling array */
    for(int i = 0; i < arrayDimension; i++){
        for(int j = 0; j < arrayDimension; j++){
            for(int k = 0; k < arrayDimension; k++){
                array[i][j][k] = 0;
            }
        }
    }
}

bool coordinateValidation(int array[], int player){
    int xPos = array[0];
    int yPos = array[1];
    int zPos = array[2];
    int currentPos = cubeArray[xPos][yPos][zPos];
    if(currentPos == player){
        cout << "You've already put your mark on the coordinate" << endl;
        return false;
    }
    else if(currentPos == 0){
        cubeArray[xPos][yPos][zPos] = player;
        return true;
    }
    else{
        cout << "Another player has put a mark on the coordinate" << endl;
        return false;
    }
}

void askCoordinates(){
    string x, y, z;
    while(true){
        while(true){
            cout << "Enter your desired dimension = " << endl;
            getline(cin, x);
            if(number_validation(x, 1, arrayDimension) == false){
                continue;
            }
            break;
        }
        while(true){
            cout << "Enter your row position in the dimension (1-"<< arrayDimension << ")= " << endl;
            getline(cin, y);
            if(number_validation(y, 1, arrayDimension) == false){
                continue;
            }
            break;
        }
        while(true){
            cout << "Enter your column position in the dimension (1-" << arrayDimension << ") = " << endl;
            getline(cin, z);
            if(number_validation(z, 1, arrayDimension) == false){
                continue;
            }
            break;
        }
        arrayCoordinates[0] = stoi(x)-1;
        arrayCoordinates[1] = stoi(y)-1;
        arrayCoordinates[2] = stoi(z)-1;

        if(coordinateValidation(arrayCoordinates, currentPlayer) == false){
            continue;
        }

        break;   
    }
}

void printArray(int array[arrayDimension][arrayDimension][arrayDimension]){
    cout << endl;
    for(int i = 0; i < arrayDimension; i++){
        for(int j = 0; j < arrayDimension; j++){
            for(int k = 0; k < arrayDimension; k++){
                cout << array[i][j][k] << "  ";
            }
            if(j == 1){
                cout << "| Dimension " << i+1 << endl;
                continue;
            }

            cout << "|" << endl;
        }
        cout << endl;
    }
}

void printArrayModified(int array[arrayDimension][arrayDimension][arrayDimension]){
    cout << endl;
    for(int i = 0; i < arrayDimension; i++){
        for(int j = 0; j < arrayDimension; j++){
            for(int k = 0; k < arrayDimension; k++){
                cout << array[j][i][k] << " ";
            }
            cout << " |  ";
        }
        cout << endl;
    }
    cout << "D1        D2        D3" << endl;
}

void arrayModify(int array[arrayDimension][arrayDimension][arrayDimension], int player = 0){
    if(player == 0){
        arrayFill(array);
        return;
    }
    int xPos = arrayCoordinates[0];
    int yPos = arrayCoordinates[1];
    int zPos = arrayCoordinates[2];

}

bool checkCompletion(int array[arrayDimension][arrayDimension][arrayDimension], int player){
    for(int z = 0; z < arrayDimension; z++){ // Check rows in each plane
        for(int x = 0; x < arrayDimension; x++){
            bool win = true;
            for(int y = 0; y < arrayDimension; y++){
                if(array[x][y][z] != player){
                    win = false;
                    break;
                }
            }
            if(win){
                return true;
            } 
        }
    }
    for(int z = 0; z < arrayDimension; z++){ // Check columns in each plane
        for(int y = 0; y < arrayDimension; y++){
            bool win = true;
            for(int x = 0; x < arrayDimension; x++){
                if(array[x][y][z] != player){
                    win = false;
                    break;
                }
            }
            if(win){
                return true;
            } 
        }
    }
    for(int y = 0; y < arrayDimension; y++){ // Check depths in each plane
        for(int x = 0; x < arrayDimension; x++){
            bool win = true;
            for(int z = 0; z < arrayDimension; z++){
                if(array[x][y][z] != player){
                    win = false;
                    break;
                }
            }
            if(win){ 
                return true;
            }
        }
    }
    for(int z = 0; z < arrayDimension; z++){ // Check diagonals in each plane
        bool win = true; // main diagon
        for(int i = 0; i < arrayDimension; i++){
            if(array[i][i][z] != player){
                win = false;
                break;
            }
        }
        if(win){ 
            return true;
        }
        win = true; // Anti-diagon
        for(int i = 0; i < arrayDimension; i++){
            if(array[i][arrayDimension - 1 - i][z] != player){
                win = false;
                break;
            }
        }
        if(win){ 
            return true;
        }
    }
    for(int x = 0; x < arrayDimension; x++){ // Check 3D columns
        for(int y = 0; y < arrayDimension; y++){
            bool win = true;
            for(int z = 0; z < arrayDimension; z++){
                if(array[x][y][z] != player){
                    win = false;
                    break;
                }
            }
            if(win){ 
                return true;
            }
        }
    }
    bool win = true; // Check 3D space diagon, main diagon
    for(int i = 0; i < arrayDimension; i++){
        if(array[i][i][i] != player){
            win = false;
            break;
        }
    }
    if(win){ 
        return true;
    }
    win = true; // Opposite diagon
    for(int i = 0; i < arrayDimension; i++){
        if(array[i][i][arrayDimension-1-i] != player){
            win = false;
            break;
        }
    }
    if(win){ 
        return true;
    }
    win = true; // Anti-diagon 1
    for(int i = 0; i < arrayDimension; i++){
        if(array[i][arrayDimension - 1 - i][i] != player){
            win = false;
            break;
        }
    }
    if(win){ 
        return true;
    }
    win = true; // Anti-diagon
    for(int i = 0; i < arrayDimension; i++){
        if(array[arrayDimension - 1 - i][i][i] != player){
            win = false;
            break;
        }
    }
    if(win){ 
        return true;
    }
    return false;
}


int main(){
    cout << attributes.mainlogo << endl;
    cout << attributes.instructions << endl;
    getline(cin, dummyInput);
    string coordinateInput;
    arrayModify(cubeArray);
    printArrayModified(cubeArray);
    cout << endl;
    while(true){
        playerSwap(&currentPlayer);
        askCoordinates();
        arrayModify(cubeArray, currentPlayer);
        printArrayModified(cubeArray);
        cout << endl;
        if(checkCompletion(cubeArray, currentPlayer)){
            cout << "Player " << currentPlayer << " wins!" << endl;
            break;
        }
    }
    return 0;
}