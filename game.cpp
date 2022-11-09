//
// Lab 9 Game using classes with functions prototyped by Dr. Nesterenko
// David J Tinley
// 11/08/22
//

#include <iostream>
#include "maze.hpp"
#include "testMaze.cpp"

using std::cout;
using std::cin;
using std::endl;

int main() { // Main Game loop
    srand(time(nullptr));

    Maze new_maze;

    Room mouse;
    mouse.makeStartRoom();
    cout << "The mouse is in ";
    mouse.print();
    cout << endl;

    Room cheese_room;
    cheese_room.makeCheeseRoom();
    cout << "Cheese room is ";
    cheese_room.print();
    cout << endl;
    
    new_maze.build();

    char see_walls;
    cout << "Do you want to see the walls? y or n?" << endl;
    cin >> see_walls; // ask user if they want to see the walls

    if (see_walls == 'y') {
        new_maze.print();
        cout << endl;
    }
    
    int number_of_tries = 0;
    while (matchRoom(mouse, cheese_room) == false) {
        cout << "Current Mouse position: ";
        mouse.print();
        cout << endl;
        if (number_of_tries >= 5) { // Give user ability to quit
            cout << "Would you like to keep playing?" << endl;
            cout << "Enter 'y' or 'n'" << endl;
            char user_reply;
            cin >> user_reply;
            if (user_reply == 'y') {
                number_of_tries = 0;
                cout << "Keep trying" << endl;
                continue;
            } else {
                cout << "Good Bye" << endl;
                return 0;
            }
        }
        Room new_mouse_move = mouse.nextMove();
        if (matchRoom(new_mouse_move, mouse) == true) {
            ++number_of_tries;
            continue;
        } else {
            if (new_maze.move(new_mouse_move)) {
            cout << "Move successful" << endl;
            } else {
                ++number_of_tries;
                cout << "Move failed" << endl;
            }
        }
        mouse = new_maze.getCurrentRoom();
    }
    return 0;
}