//
//  main.cpp
//  Paranoia Targeting Algorithm
//
//  Created by Mac J on 12/24/24.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <random>

using namespace std;

struct Player {
    string timestamp, name, email, roomNumber;
    string target;
    
    void readPlayer(ifstream& inputFile) {
        getline(inputFile, timestamp, ',');
        getline(inputFile, name, ',');
        getline(inputFile, email, ',');
        getline(inputFile, roomNumber);
    }
    
    void writePlayer(ofstream& output) {
        output << left << setw(25) << name;
        output << left << setw(20) << roomNumber << endl;
    }
    
    void printPlayer(ostream& output) {
        output << left << setw(25) << name;
        output << left << setw(20) << roomNumber << endl;
    }
    
    bool operator<(const Player& other) const {
        return name < other.name;
    }
    
};

int main() {
    vector<Player> players;
    ifstream inputFile;
    ofstream outputFile;
    int playerCount;                    // 81 players
    string buffer;
    
    cout << "Enter number of players: ";
    cin >> playerCount;
    cout << endl << endl;
    
    inputFile.open("players.txt");
    assert(inputFile);
    
    getline(inputFile, buffer);
    for (int i = 0; i < playerCount; i++) {
        Player newPlayer;
        newPlayer.readPlayer(inputFile);
        players.push_back(newPlayer);
    }
    
    inputFile.close();
    
    sort(players.begin(), players.end());  // sort based off name
    
    outputFile.open("targetSheet.txt");
    assert(outputFile);
    
    for (unsigned int i = 0; i < players.size(); i++) {
        players[i].printPlayer(cout);
        players[i].writePlayer(outputFile);
    }
    
    srand(static_cast<unsigned int>(time(0)));
    shuffle(players.begin(), players.end(), default_random_engine(rand()));
    
    for (unsigned int i = 0; i < players.size(); i++) {
        if (players[i % players.size()].roomNumber ==
            players[(i + 1) % players.size()].roomNumber) {
            shuffle(players.begin(), players.end(), default_random_engine(rand()));
        }
    }
    
    cout << endl << endl;
    for (unsigned int i = 0; i < players.size(); i++) {
        cout << left << setw(25) << players[i].name
             << setw(10) << players[i].roomNumber
             << setw(10) << " --> "
             << setw(10) << players[(i + 1) % players.size()].roomNumber
             << setw(10) << players[(i + 1) % players.size()].name
             << endl;
    }
    
    return 0;
}
