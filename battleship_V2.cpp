///Input and Output stream///
#include <iostream>  
///Rand () function///
#include <cstdlib>   
///Time () to seed the random generator///
#include <ctime>
//*****************************************//
//Set and map are the TWO associative containers//
//*****************************************//
/// Set container tracks ships///
#include <set>       
/// Map container tracks the board status ///
#include <map> 
//******************************************//
//queue and stack are the TWO conatiner adaptors//
//******************************************//
///Priority queue is used for computer's attack//
#include <queue>
/// Stack container is used for move history ///
#include <stack>    
///********************************/// 
/// For STL algorithms like count ///
///******************************///
#include <algorithm> 
/// The list for the 1 type of sequence ///
////       used for history moves      ////
#include <list>      
/// Inorder to store characters and text ///
#include <string>
/// Inorder to not used STD::COUT ///
/// or to use STD::endl ////
/// This program will use namespace std ///
using namespace std;

// The board of each player will have a 6x6 size grid //
const int GRID_SIZE = 6; 

/// The number of ships a player can place ///
const int SHIP_COUNT = 3;  

// Struct to represent an attack with a priority //
struct Attack {
    
    //Coordinates of the attack //
    int row, col;   
    // There will be 6 rows and 6 columns //
    // creating a 6x6 grid starting at 0 and ending at 5//
    
    /// Priority of the attack ///
    int priority;    
    /// higher priority means it will be attacked first ///

    // Constructor to initialize the attack object
    Attack(int r, int c, int p) : row(r), col(c), priority(p) {}
    
    /// R will represent row ///
    /// C will represent column ///
    /// P will represent priority ///

    /// Comparator to make the priority queue a max-heap ///
    /// highest priority comes first ///
    
    bool operator<(const Attack& other) const {
        return priority < other.priority; 
        // Reverse order for max-heap //
    }
};
/// class board is the ///
/// Core of the project that manages the grid ///
class Board {
/// Private can only be accessed by functions of its own class///
    
private:
    
/// Set to store the positions of the ships ///
    set<pair<int, int>> ships; 
/// Map to store the status of each cell on the board ///
    map<pair<int, int>, char> boardStatus;  
    
/// public can be accessed by all ///
public:
    // Constructor to initialize the board //
    Board() {
        // Initialize the board with water '~' in each cell //
        for (int row = 0; row < GRID_SIZE; ++row) {
            for (int col = 0; col < GRID_SIZE; ++col) {
                boardStatus[{row, col}] = '~';
             // '~' represents water //
                
            }
        }
    }

    // Function to display the board //
    void display(bool isPlayerBoard) {
        
    //Before board a sign of the board game will appear //
    // This will indicate what game the user is playing //
        
        cout << " _     _ _______ ___     _______ _______ __   __ _______   _______ _______     " << endl;
        cout << "| | _ | |       |   |   |       |       |  |_|  |       | |       |       |     " << endl;
        cout << "| || || |    ___|   |   |       |   _   |       |    ___| |_     _|   _   |     " << endl;
        cout << "|       |   |___|   |   |       |  | |  |       |   |___    |   | |  | |  |     " << endl;
        cout << "|       |    ___|   |___|      _|  |_|  |       |    ___|   |   | |  |_|  |     " << endl;
        cout << "|   _   |   |___|       |     |_|       | ||_|| |   |___    |   | |       |     " << endl;
        cout << "|_______|_______|_______|_______|_______|_______|_______|   |___| |_______|     "<< endl;
        cout << " _______ _______ _______ _______ ___     _______   _______ __   __     _______  " <<endl;
        cout << "|  _    |   _   |       |       |   |   |       | |       |  | |  |   |       |"  << endl;
        cout << "| |_|   |  |_|  |_     _|_     _|   |   |    ___| |  _____|  |_|  |   |    _  |"  <<endl;
        cout << "|       |       | |   |   |   | |   |   |   |___  | |_____|       |   |   |_| |"  << endl;
        cout << "|  _   ||       | |   |   |   | |   |___|    ___| |_____  |       |   |    ___|" << endl;
        cout << "| |_|   |   _   | |   |   |   | |       |   |___   _____| |   _   |   |   |    " << endl;
        cout << "|_______|__| |__| |___|   |___| |_______|_______| |_______|__| |__|___|___|    " << endl;
        
        // This are the game rules //
        ///each player must obey the game rules //
        cout << "********************************************************" << endl;
        cout << "                         GAME RULES                     " << endl;
        cout << " 1)Players must place their 3 ships on their ocean grid " <<endl;
        cout << " 2)Players take turns guessing where the opponent's ships" << endl;
        cout <<  "are located" << endl;
        cout << " 3)Hits and misses are noted, and the first player to sink" <<endl;
        cout << "all opponent's ships wins" << endl;
        cout << "********************************************************" <<endl;
        
        // Print the column headers //
        cout << "  " ;
        for (int i = 0; i < GRID_SIZE; i++) cout << i << " " ;
        // Print column numbers //
        cout << endl;

        // Print each row of the board //
        for (int row = 0; row < GRID_SIZE; ++row) {
            cout << row << " "; 
            
            // Print row number
            for (int col = 0; col < GRID_SIZE; ++col) {
                pair<int, int> coord = {row, col};
                if (isPlayerBoard || boardStatus[coord] == 'X' || boardStatus[coord] == 'O') {
                    
                    // If it's the player's board of a hit //
                    // or miss cell, display the status //
                    cout << boardStatus[coord] << " ";
                } else {
                    
                    // If the cell is not called //
                    // meaning there is no miss or hit //
                    
                    // hide the ship locations with '~' //
                    cout << "~ " ; 
                }
            }
            
            cout << endl;
        }
    }

    // Function to place a ship at a given location //
    bool placeShip(int row, int col) {
        pair<int, int> coord = {row, col};
        
        // Check if the coordinates are within bounds and if the spot is empty //
        
        if (row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE && boardStatus[coord] == '~') {
            ships.insert(coord); 
            
            // Add ship position to the set of ships //
            
            boardStatus[coord] = 'S';  
            // Mark the ship position with 'S' //
            // 'S' for ship //
            return true;  
            // Successfully placed the ship //
        }
        return false;  
        // Invalid placement //
    }
    // This allows for the user to place the game with a computer generated grid //
    // Function to place all ships randomly on the board //
    bool randomPlaceShips(int shipCount) {
        
        int placedShips = 0;
        
        while (placedShips < shipCount) {
            
            int row = rand() % GRID_SIZE;  
            // Random row between 0 and GRID_SIZE-5 //
            // This will allow for any person to change the GRID_SIZE //
            // Without it affecting the game just adding to its complexity //
            int col = rand() % GRID_SIZE;  
            // Random column between 0 and GRID_SIZE-5 //
            if (placeShip(row, col)) {  
             // Attempt to place a ship at the random location //
                ++placedShips;  
             // Increment the count of placed ships //
            }
        }
        return true;  
        // Successfully placed all ships //
    }

    // Function to attack a given location //
    bool attack(int row, int col) {
        
        pair<int, int> coord = {row, col};
        // Check if the coordinates are within bounds //
        
        if (row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE) {
            // If a ship is located at the attack coordinates //
            
            if (ships.count(coord) > 0) {
                boardStatus[coord] = 'X';  
                // Mark as a hit ('X') //
                ships.erase(coord);  
                // Remove the ship from the set //
                return true; 
                // Attack was successful (hit) //
            } else {
                boardStatus[coord] = '-'; 
                // Mark as a miss ('-') //
            }
        }
        return false;  
        // Attack was not successful (miss) //
        
    }

    // Function to check if all ships are sunk //
    bool allShipsSunk() {
        return ships.empty();  
    // If the set of ships s empty, all ships are sunk //
    
    }

    // Count the number of hits ('X') on the board //
    int countHits() const {
        return std::count_if(boardStatus.begin(), boardStatus.end(), [](const auto& entry) {
            return entry.second == 'X';  
            // Count cells with 'X' (hits) //
        });
    }

    // Count the number of misses ('O') on the board //
    int countMisses() const {
        return std::count_if(boardStatus.begin(), boardStatus.end(), [](const auto& entry) {
            return entry.second == 'O';  
            // Count cells with 'O' (misses) //
        });
    }
};
// Class player represents the player and is responsible for the attributes of the player //
class Player {
    
public:
    
    // Player's board //
    Board board; 
    // Player's name //
    string name; 
    // List to store the of moves //
    list<pair<int, int>> moveHistory;  
    // Set to track previous attack //
    // This avoids repeat //
    set<pair<int, int>> previousAttacks;  
    
    // Flag to check if the player is a computer //
    bool isComputer; 
    
    // Priority queue to store attacks with priority //
    priority_queue<Attack> attackQueue;  

    // Constructor to initialize the player //
    Player(string playerName, bool computer = false) : name(playerName), isComputer(computer) {}

    // Function to place ships on the board //
    void placeShips(bool random = false) {
        if (random) {
            board.randomPlaceShips(SHIP_COUNT); 
            
    // Place ships randomly if random flag is true //
        } else {
            board.display(true); 
        // Displays board to the player //
            int placedShips = 0;
            
        // Continue placing ships until the required number of ships is placed //
            while (placedShips < SHIP_COUNT) {
                int row, col;
                cout << "Enter row and column to place ship #" << placedShips + 1 << ": " << endl;
                cin >> row >> col;

        // If ship is placed successfully, increment placedShips count //
                if (board.placeShip(row, col)) {
                    ++placedShips;
                    board.display(true);  
        // Display updated board //
                }
                else {
                    cout << "Invalid position! Try again." << endl;
                    // If placement fails //
                }
            }
        }
    }

    // Function to take a turn and attack the opponent //
    bool takeTurn(Player& opponent) {
        int row, col;
        // If the player is a computer //
        if (isComputer) { 
            do {
            // Randomly select a row //
                row = rand() % GRID_SIZE; 
            // Randomly select column //
                col = rand() % GRID_SIZE; 
            // This will ensure that there are no repeats of attacks //
            } while (previousAttacks.count({row, col})); 
            
            // Randomly assign a priority for attack //
            // One of the container adaptors //
            int priority = rand() % 100; 
            // Push the attack into the queue with priority //
            attackQueue.push(Attack(row, col, priority));  
            // Get the attack with the highest priority //
            Attack attack = attackQueue.top(); 
            // Remove the attack after using it //
            attackQueue.pop();  
            // Displays to user which coordinate the computer attacked //
            // Creates suspends if ship was near//
            cout << name << " attacks (" << attack.row << ", " << attack.col << ") with priority " << attack.priority << endl;
            // Tracks the attack of the computer //
            previousAttacks.insert({attack.row, attack.col}); 
        } 
        else {  
            
            // If the player is the user //
            cout << name << ", enter row and column to attack: " << endl;
            cin >> row >> col;
        }

        moveHistory.push_back({row, col}); 
        // Add the move to the history //
        
        if (opponent.board.attack(row, col)) { 
        // If the attack hits a ship //
            cout << "HIT!" << endl;
            opponent.board.display(false); 
        // Display opponent's board (hidden ships) //
            return opponent.board.allShipsSunk(); 
            // Check if all ships are sunk //
        } 
        else {
            cout << "miss. D:" << endl;  
            // If the attack misses
        }
        return false;  
          // Game is not over yet
    }

    // Function to display the move history of the player
    void displayMoveHistory() {
        
        cout << name << "'s Move History:" << endl;
        for (const auto& move : moveHistory) {  
            // Iterate over the move history
            cout << "Row: " << move.first << ", Col: " << move.second << endl; 
            // Display each move
        }
    }

    // Function to display the hit and miss counts
    void displayHitMissCount() {
        
        cout << "Hits: " << board.countHits() << endl; 
        // Display the number of hits
        cout << "Misses: " << board.countMisses() << endl; 
        // Display the number of misses
    }
};
///This is the new section added into the previous version ///
/// Node structure for binary tree ///

struct Node {
    /// Player's name ///
    string playerName;
    /// Player's score ///
    int score; 
    /// Pointer to left child node ///
    Node* left;
    /// Pointer to right child node ///
    Node* right;
    
    /// constructor to initalize a new node with a player's name and score ///
    Node(string name, int sc) : playerName(name), score(sc), left(nullptr), right(nullptr) {}
};

// Binary Tree class to handle the leaderboard ///
class BinaryTree {
private:
/// The root of the tree ///
    Node* root;

    /// recursive function to insert a node ///
    /// one of the requirements of the project 2 ///
    
    void insert(Node*& node, const string& playerName, int score) {
        /// if node is empty, create a new one ///
        ///program will create a new one with the player's name and score///
        
        
        if (node == nullptr) {
            node = new Node(playerName, score);
        /// The higher score will go to the left ///
        } else if (score > node->score) {
            insert(node->left, playerName, score);  
        } else {
        /// Lower scores will go to the right ///  
            insert(node->right, playerName, score); 
            
        }
    }

    // Helper function to perform in-order traversal (to display leaderboard)
    void inorder(Node* node) const {
        
        if (node != nullptr) {
        /// first go to left child ///
            inorder(node->left);
        /// print the node's data ///
            cout << node->playerName << " - Score: " << node->score << endl;
        /// Then, to the right child ///
            inorder(node->right); 
        }
    }

public:
    BinaryTree() : root(nullptr) {}

    // Insert a player's score into the leaderboard
    void insert(const string& playerName, int score) {
       
        insert(root, playerName, score);
    }

    // Display the leaderboard in descending order
    void displayLeaderboard() const {
        
        /// wanted to create a banner for the leader board ///
        
        cout <<" ______  _________________________       _______ _______ _     _________________ " << endl;        
        cout <<"(  ___ )(  ___  )__   __(__   __) |     (  ____ (  ____ | |    ||__   __(  ____ )" << endl;        
        cout <<"| (   ) | (   ) |  ) (     ) (  | (     | (    (| (    || )   ( |  ) (  | (    )|" << endl;       
        cout <<"| (__/ /| (___) |  | |     | |  | |     | (__   | (_____| (___) |  | |  | (____)|" << endl;       
        cout <<"|  __ ( |  ___  |  | |     | |  | |     |  __)  (_____  |  ___  |  | |  |  _____)" << endl;     
        cout <<"| (   ||| (   ) |  | |     | |  | |     | (           ) | (   ) |  | |  | (      " << endl;       
        cout <<"| )___) | )   ( |  | |     | |  | (____/| (____//|____) | )   ( ___) (__| )      " << endl;            
        cout <<"|_/ (__/|/     ||  )_(     )_(  (_______(_______|_______|/     \\_______|/       " << endl;       
                                                                              
        cout<<" _       _______ _______ ______  _______ _______ ______  _______ _______ _______ ______"<<endl; 
        cout<<"( )     (  ____ (  ___  (  __  |(  ____ (  ____ (  ___ )(  ___  (  ___  (  ____ (  __  |"<<endl;
        cout<<"| (     | (    (| (   ) | (  )  | (    || (    )| (   ) | (   ) | (   ) | (    )| (  )  )"<<endl;
        cout<<"| |     | (__   | (___) | |   ) | (__   | (____)| (__/ /| |   | | (___) | (____)| |   ) |"<<endl;
        cout<<"| |     |  __)  |  ___  | |   | |  __)  |     __|  __ ( | |   | |  ___  |     __| |   | |"<<endl;
        cout<<"| |     | (     | (   ) | |   ) | (     | (( (  | (  ( )| |   | | (   ) | () (  | |   ) |"<<endl;
        cout<<"| (____/| (____/| )   ( | (__/  | (____/| ) ( )_| )___) | (___) | )   ( | ) ) (_| (__/  )"<<endl;
        cout<<"(_______(_______|/     |(______/(_______|/   (__|/ (___/(_______|/     (|/   )__(______/ "<<endl;
        
        cout << "(Descending Order):" <<endl;       
        
        inorder(root);
    }
};

int main() {
    srand(static_cast<unsigned>(time(0)));  
    // Seed the random number generator with the current time //
    
    char restartChoice;  
    // Variable to store user's choice for restarting the game //
    
    BinaryTree leaderboard;  // Create a BinaryTree object for the leader board
    
    // Start the game loop //
    do {
        Player player1("Player 1"); 
        // Create Player 1 //
        Player player2("Computer", true); 
         
        // changing computer to alternative name on line that states "Player 1" will change name throughout //
        // Create Player 2 (the computer) //
        // Created a computer opponent in order for there to be //
        // one user input  //
        // which allow for people to play alone //

        player1.placeShips(false); 
        // Player 1 places ships manually //
        player2.placeShips(true);  
        // Player 2 (the computer) places ships randomly //

        bool gameOver = false; 
        // Flag to track if the game is over //
        while (!gameOver) {  
            // Keep playing until one player wins //
            
            // Player 1 takes a turn //
            if (player1.takeTurn(player2)) {
                
                cout << "********************" << endl;
                cout << "*  " << player1.name << " WINS!  *" << endl;  
                cout << "********************" << endl;
                // Player 1 wins //
                
                gameOver = true;  
                // End the game //
                /// Insert the score into the leader board //
                
                leaderboard.insert(player1.name, player1.board.countHits()); 
                // a big banner to express to user a big celebration //
                
              cout<<" _______  _______  _        _______  _______  _______ _________ _______ " <<endl;
              cout<<"(  ____ )(  ___  )( (    /|(  ____ |(  ____ )(  ___  )|__   __/(  ____ |" <<endl;
              cout<<"| (    |/| (   ) ||  |  ( || (    |/| (    )|| (   ) |   ) (   | (    |/" <<endl;
              cout<<"| |      | |   | ||   | | || |      | (____)|| (___) |   | |   | (_____ " <<endl;
              cout<<"| |      | |   | ||  _ |  | |   ___ |     __)|  ___  |   | |   (_____  )" <<endl;             
              cout<<"| |      | |   | || | |   || |  |_ )| (| (   | (   ) |   | |         ) |" <<endl;
              cout<<"| (____/)| (___) || )  |  || (___) || ) | |__| )   ( |   | |   /|____) |" <<endl;
              cout<<"(_______/(_______)|/    )_)(_______)|/   |__/|/     ||   )_(   |_______)" <<endl;
                                                                        
            }
            else if (player2.takeTurn(player1)) {
                
                cout << "********************" << endl;
                //Player 2 (computer) wins //
                cout << "*  " << player2.name  << " WINS!  *" << endl;  
                cout << "********************" << endl;
                gameOver = true;  
                // End the game
                
                /// Inserts the score into the leaderboard ///
                leaderboard.insert(player2.name, player2.board.countHits()); 

                cout <<" __      _ _                 " << endl;       
                cout <<"/ _|    (_) |                " << endl;      
              cout << "| |_ __ _ _| |_   _ _ __ ___  " << endl;
              cout << "|  _/ _` | | | | | | '__/ _ | " << endl;
              cout << "| || (_| | | | |_| | | |  __/ " << endl;
              cout << "|_| -__,_|_|_|-__,_|_|  -___| " << endl;
            }
        }
       
        // Display final move histories //
        // bars placed for organization//
        // Provides better focus for user //
        cout << "**************************" << endl;
        player1.displayMoveHistory();
     
        player2.displayMoveHistory();
        cout << "**************************" << endl;
        cout << "__________________________" << endl;
        // Display hit/miss counts //
        
        cout << "**************************" << endl;
        cout << "Player 1's HIT/MISS count" << endl;
        /// had to reverse the order of the display the correct HIT_MISS_Count //
        /// last minute addition //
        /// program reads user as player 2 in display hit miss count //
        /// output will display normal to user but will need alternating by programmer //
    
        player2.displayHitMissCount();
     
        cout << player2.name << "'s HIT/MISS count" << endl; 
        player1.displayHitMissCount();
        // read comment above to see why player 1 is displayed //
        // Updated to display player2's name //
        // This for convenience if name change is decided later on //
        
        cout << "**************************" << endl;
        
        cout << "________________________________________" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Do you want to restart the game? (y/n): " << endl;
        cout << "----------------------------------------" << endl; 
        cout << "_______________________________________" << endl;
        cin >> restartChoice;
        ///Ask if the user wants to restart the game ///
        /// Lines used for organization ///
       

    } while (restartChoice == 'y' || restartChoice == 'Y');  
    /// Continue the loop if 'y' or 'Y' is entered ///
    /// if no is entered the leader board will be displayed //

   // Display the leaderboard at the end of the session
    cout << "***********************************"<< endl;
    cout << "***********************************" << endl; 
    
   /// These lines are just for organization ///
    leaderboard.displayLeaderboard();

    return 0; 
    // End of the program
}
