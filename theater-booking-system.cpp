#include<iostream>
#include<string>
#include<stdlib.h>
#include<vector>

using namespace std;

// Global Variable 
int all_data_user_count = 0;
int MOVIES_COUNT;
const int MOVIE_SEAT_COUNT = 21;
vector<vector<string>> all_data_user; // 2D array for storing the inputted data
vector<vector<string>> MOVIE_SEAT; // 2D array for storing the seats
const int MOVIE_PRICE[5] = {75000, 70000, 65000, 70000, 75000}; // 1D array for storing prices each movies

/*
[ ][ ][ ][ ][ ][ ][ ]
[ ][ ][ ][ ][ ][ ][ ]
[ ][ ][ ][ ][ ][ ][ ]
*/

string all_movies[][3] = {
    {"Dune: Part Two", "15:00 WIB", "202"},
    {"VENOM: The Last Dance", "11:00 WIB", "110"},
    {"Inside Out 2", "13:00 WIB", "96"},
    {"The Fall Guy", "18:00 WIB", "126"},
    {"Deadpool & Wolverine", "20:00 WIB", "128"}
};

struct{
    string main_logo = R"(
 ________            __            ___            __    _             
/_  __/ /  ___ ___ _/ /____ ____  / _ )___  ___  / /__ (_)__  ___ _   
 / / / _ \/ -_) _ `/ __/ -_) __/ / _  / _ \/ _ \/  '_// / _ \/ _ `/   
/_/ /_//_/\__/\_,_/\__/\__/_/   /____/\___/\___/_/\_\/_/_//_/\_, /    
                                                            /___/     
                            system
)";

    string mainmenu_choice = R"(Select your option:
[1]. Request a Member Card
[2]. Book seats at theater
[3]. Print Summary (END)
= )";

    string display_theater = R"(
.-------------------.
|       screen      |
'-------------------'
)";

} Attributes;

void error_attribute(string a){
    cout << "\033[31;49m" << a << "\033[0m";
}

string name_input(){
    string name;
    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, name);
    return name;
}

bool number_validation(string input, int counter = 0, int low = 0, int high = 0){ // counter == 0 only for checking input, counter = 1 adds range checking
    // low <= x <= high --> 5 <= x <= 8
    int temp = 0;
    for(char n : input){
        if(isdigit(n) != true){
            error_attribute("[ERROR] -- Input contains non-integer character. ");
            return false;
        }
        temp++;
    }
    if(counter == 1 && (temp < low || temp > high)){ // Digit count checking (e.g. for telephone)
        error_attribute("[ERROR] -- Input must between " + to_string(low) + "-" + to_string(high) + " digits.");
        return false;
    }
    if(counter == 2 && (low-1 < stoi(input) && stoi(input) < high+1) == false){ //Range count checking
        if(low == high){
            error_attribute("[ERROR] -- Input must be only number " + to_string(low));
            return false;
        }
        error_attribute("[ERROR] -- Input must be from number " + to_string(low) + " to " + to_string(high));
        return false;
    }
    return true;
}

string phone_input(){
    string phone_number;
    while(true){
        cout << "Enter your phone number: ";
        getline(cin, phone_number);
        if(number_validation(phone_number, 1, 7, 13) != true){
            cout << "\n";
            continue;
        }
        else{
            return phone_number;
        }
    }
}

bool member_exist(string choice, int count){
    if(number_validation(choice, 2, 1, count) == true){
        for(int i = 0; i < count; i++){
            if(all_data_user[i][2] == choice){
                return true;
            }
        }
    }
    else{
        return false;
    }
    error_attribute("[ERROR] -- ID not found/exist!");
    return false;
}

void data_initialization(){ // List order of value = [Name, Phone Number, ID]
    string name, phone_number, id; 
    vector<string> userdata;
    name = name_input();
    phone_number = phone_input();
    id = to_string(rand() % 10000);
    userdata.push_back(name);
    userdata.push_back(phone_number);
    userdata.push_back(id);
    cout << "Your ID number is " << id << "." << endl;
    all_data_user.push_back(userdata);
    all_data_user_count++;
}

void launch_movie_count(){
    int array_length = sizeof(all_movies) / sizeof(all_movies[0]); 
    for(int i = 0; i < array_length; i++){
        MOVIES_COUNT++;
    }
    return;
}

void launch_seats(){
    int temp = MOVIE_SEAT_COUNT;
    for(int i = 0; i < MOVIES_COUNT; i++){
        vector<string> seatdata;
        for(int j = 0; j < MOVIE_SEAT_COUNT; j++){
            seatdata.push_back("[ ]");
        }
        MOVIE_SEAT.push_back(seatdata);
    }
}

void display_seats(int chosen_movie){
    cout << Attributes.display_theater;
    for(int j = 0; j < MOVIE_SEAT_COUNT; j++){
        if(j != 0 && j%7 == 0){
            cout << endl;
        }
        cout << MOVIE_SEAT[chosen_movie][j];
    }
}

int display_movies_list(){
    string movie_choice;
    while(true){
        cout << endl;
        for(int i = 0; i < MOVIES_COUNT; i++){
            cout << "\tMOVIE NAME \t: " << all_movies[i][0] << endl;
            cout << "[" << i+1 << "]\tStart Time \t: " << all_movies[i][1] << endl;
            cout << "\tDuration \t: " << all_movies[i][2] << " minutes"<< endl;
            cout << "\tPrice per seat @ " << MOVIE_PRICE[i] << endl;
            cout << "\t- - - - - - - - - - - - - - - - -\t" << endl;
        }
        cout << "Choose the desired movie = ";
        getline(cin, movie_choice);
        if(number_validation(movie_choice, 2, 1, MOVIES_COUNT) == true){
            break;
        }
    }
    return stoi(movie_choice);
}

void modify_seat(int movie_choice, int choice){
    while(true){
        display_seats(movie_choice);
        string seat_position, temp;
        string seat_reserved;
        cout << endl << endl << "Choose a seat to be modify (1-21) = ";
        getline(cin, seat_position);
        if(number_validation(seat_position, 2, 1, 21) != true){
            continue;
        }
        seat_reserved = "[" + to_string(choice) + "]";
        if(MOVIE_SEAT[movie_choice][stoi(seat_position)-1] == "[ ]"){
            MOVIE_SEAT[movie_choice][stoi(seat_position)-1] = seat_reserved;
        }
        else if(MOVIE_SEAT[movie_choice][stoi(seat_position)-1] == seat_reserved){
            MOVIE_SEAT[movie_choice][stoi(seat_position)-1] = "[ ]";
        }
        else{
            error_attribute("[ERROR] -- This seat has been taken");
            cout << endl;
        }
        display_seats(movie_choice);
        cout << endl << endl << "Modify again? (Y/N) = ";
        getline(cin, temp);
        if(temp == "N" || temp == "n"){
            return;
        }
    }
}

void book_seats(){
    string user_choice, temp;
    string seat_book_count;
    while(true){
        if(all_data_user_count == 0){
            error_attribute("[ERROR] -- No member ID registered in the system!");
            return;
        }
        int count = all_data_user.size();
        cout << endl << "Choose your member ID!" << endl;
        for(int i = 0; i < count; i++){
            cout << "[" << i+1 << "] " << all_data_user[i][2] << endl;
        }
        cout << "= ";
        cin.ignore();
        getline(cin, user_choice);
        if(number_validation(user_choice, 2, 1, count) != true){
            return;
        }
        while(true){
            int movie_choice = display_movies_list()-1;
            modify_seat(movie_choice, stoi(user_choice));
            cout << "Do you wanna book another movie again? (Y/N) = ";
            getline(cin, temp);
            if(temp == "N" || temp == "n"){
                return;
            }
        }
    }
}

void data_summary(){
    string seat_match;
    int total = 0, subtotal = 0, movie_integer = 0, money_counter = 0;
    if(all_data_user.size() == 0){
        error_attribute("[ERROR] -- No member data inputted.");
        return;
    }
    cout << endl<< endl << "SEAT BOOK REPORT" << endl;
    for(int i = 0; i < all_data_user_count; i++){
        cout << endl;
        cout << "Member ID [" << i+1 << "]\t: " << all_data_user[i][2] << endl;;
        cout << "Name\t\t: " << all_data_user[i][0] << endl;
        cout << "Phone Number \t: " << all_data_user[i][1] << endl;
        for(vector<string> j : MOVIE_SEAT){
            seat_match = "[" + to_string(i+1) + "]";
            cout << "--------------------------------\n";
            cout << "Movie Book for " << all_movies[movie_integer][0] << ": ";
            for(int k = 0; k < MOVIE_SEAT_COUNT; k++){
                if(MOVIE_SEAT[movie_integer][k] == seat_match){
                    cout << endl << "- Seat " << k+1; 
                    money_counter++;
                }
            }
            movie_integer++;
            if(money_counter == 0){
                cout << "None" << endl;
                continue;
            }
            else{
                subtotal = (money_counter * MOVIE_PRICE[movie_integer-1]);
                total += subtotal;
                cout << endl << "Subtotal for the movie: " << subtotal << endl;
                money_counter = 0;
            }
        }
        movie_integer = 0;
        cout << endl << "|-|-|-|-|-|-|-|-|-|-|-|-|" << endl;
    }
    cout << endl << " -- The total of the booked seats = " << total << " -- " << endl;
}

int main(){

    string choice;
    srand(time(0));

    launch_movie_count();
    launch_seats();

    while(true){
        cout << Attributes.main_logo;
        cout << Attributes.mainmenu_choice;
        cin >> choice;
        if(number_validation(choice, 2, 1, 3) != true){
            continue;
        }
        if(choice == "1"){
            data_initialization();
        }
        else if(choice == "2"){
            book_seats();
        }
        else{
            data_summary();
            break;
        }
    }
    cout << endl << "\033[0m" << "Program Terminated"<< "\033[0m";
    return 0;
}
