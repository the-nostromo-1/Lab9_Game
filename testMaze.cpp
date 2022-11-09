// Mikhail Nesterenko
// tests class-based Maze function implementation
// 10/30/2022

#include <iostream>
#include "maze.hpp"

using std::cout;
using std::cin;
using std::endl;

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

// ROOM CLASS FUNCTION DEFINITIONS /////////////////////////////

void Room::pick() {
    x_ = rand() % mazeSize_ + 1;
    y_ = 'a' + rand() % mazeSize_;
}

void Room::print() const {
    cout << x_ << "|" <<  y_ << " ";
}

bool Room::goodDirection(const char direction) const {
    if (direction == 'u' && y_ > 'a' - 1 ) { // Up
        return true; //
    }
    if (direction == 'd' && y_ < 'a' + mazeSize_) { // Down
        return true;
    }
    if (direction == 'l' && x_ > 1) { // Left
        return true;
    }
    if (direction == 'r' && x_ < mazeSize_ + 1) { // Right
        return true;
    }
    return false;
}

const Room Room::createAdjacent(const char adj_room_direction) const {
    Room new_adj_room = *this;

    if (adj_room_direction == 'u') {
        new_adj_room.y_ = y_ - 1;
    }
    if (adj_room_direction == 'd') {
        new_adj_room.y_ = y_ + 1;
    }
    if (adj_room_direction == 'l') {
        new_adj_room.x_ = x_ - 1;
    }
    if (adj_room_direction == 'r') {
        new_adj_room.x_ = x_ + 1;
    }
    return new_adj_room;
}

const Room Room::pickAdjacent() {
    Room picked_room = *this;

    char rand_letters [] = {'u', 'd', 'l' , 'r'};
    char selected_rand_letter = rand_letters[rand() % 4];

    Room picked_adjacent = picked_room;
    picked_adjacent = picked_room.createAdjacent(selected_rand_letter);

    if (picked_adjacent.goodDirection(selected_rand_letter) == true) {
        return picked_adjacent;
    } else {
        cout << "Bad direction" << endl;
        return picked_room;
    }
}

const Room Room::nextMove() const {
    Room current_room = *this;
    
    cout << "Please select a room with (l = left) (r = right) (u = up) (d = down)" << endl;
    char move_selection;
    cin >> move_selection;

    Room next_room_move;
    next_room_move = current_room.createAdjacent(move_selection);
    if (next_room_move.goodDirection(move_selection) == true) {
        return next_room_move;
    } else {
        cout << "Bad direction" << endl;
        return current_room;
    }

}

bool matchRoom(const Room &current_room, const Room &new_room) {
    if (current_room.x_ == new_room.x_ && current_room.y_ == new_room.y_) {
        return true;
    }
    return false;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

// ROOMPAIR CLASS FUNCTION DEFINITIONS /////////////////////////////

bool matchPair(const RoomPair &current_rooms, const RoomPair &new_rooms) {
    if ((matchRoom(current_rooms.one_, new_rooms.one_)) && (matchRoom(current_rooms.two_, new_rooms.two_))) {
        return true;
    }
    return false;
}

void RoomPair::pick() {
    RoomPair::one_.pick();
    RoomPair::two_.pick();
}

void RoomPair::print() const {
    RoomPair::one_.print();
    RoomPair::two_.print();
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

// MAZE CLASS FUNCTION DEFINITIONS /////////////////////////////

void Maze::print() const {
    for (int i = 0; i < numWalls_; ++i) {
        Maze::maze_[i].print();
    }
}

bool Maze::move(const Room& room) {
    RoomPair mouse_movement(getCurrentRoom(), room);
    if (checkMaze(mouse_movement) == -1) {
        currentRoom_ = room;
        return true;
    } else {
        return false;
    }
}

int Maze::checkMaze(const RoomPair& pair) const {
    for (int i = 0; i < numWalls_; ++i) {
        if (matchPair(maze_[i], pair) == true) {
            return i;
        }
    }
    return -1;
}

void Maze::build() {
    int walls_built = 0;
    RoomPair room_wall_built;
    while (walls_built < numWalls_) {
        room_wall_built.pick();
        if (checkMaze(room_wall_built) == -1) {
            maze_[walls_built] = room_wall_built;
            ++walls_built;
        }
    }
}