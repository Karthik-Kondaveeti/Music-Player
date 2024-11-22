#include<bits/stdc++.h>
using namespace std;

class Song {
public:
    string title;
    Song* next;
    Song* prev;

    // Constructor
    Song(string t) : title(t), next(NULL), prev(NULL) {}
};

class Playlist {
private:
    Song* head;
    Song* tail;
    Song* current;

public:
    // Constructor
    Playlist() : head(NULL), tail(NULL), current(NULL) {}

    // Add a song to the end of the playlist
    void addSong(const string& title) {
        Song* newSong = new Song(title);
        if (!head) {
            head = tail = newSong;
        } else {
            tail->next = newSong;
            newSong->prev = tail;
            tail = newSong;
        }
        if (!current) {
            current = head;
        }
    }

    // Remove the current song
    void removeCurrentSong() {
        if (!current) {
            cout << "Playlist is empty or no song selected!" << endl;
            return;
        }

        if (current == head && current == tail) {  // Only one song in the list
            delete current;
            head = tail = current = NULL;
        } else if (current == head) {  // Current is the first song
            head = head->next;
            head->prev = NULL;
            delete current;
            current = head;
        } else if (current == tail) {  // Current is the last song
            tail = tail->prev;
            tail->next = NULL;
            delete current;
            current = tail;
        } else {  // Current is in the middle
            Song* temp = current;
            current->prev->next = current->next;
            current->next->prev = current->prev;
            current = current->next;
            delete temp;
        }
    }

    // Play the current song
    void playCurrentSong() {
        if (current) {
            cout << "Playing: " << current->title << endl;
        } else {
            cout << "Playlist is empty!" << endl;
        }
    }

    // Move to the next song
    void nextSong() {
        if (current && current->next) {
            current = current->next;
            playCurrentSong();
        } else {
            cout << "You're at the end of the playlist!" << endl;
        }
    }

    // Move to the previous song
    void prevSong() {
        if (current && current->prev) {
            current = current->prev;
            playCurrentSong();
        } else {
            cout << "You're at the beginning of the playlist!" << endl;
        }
    }

    // Display the playlist
    void displayPlaylist() {
        if (!head) {
            cout << "Playlist is empty!" << endl;
            return;
        }

        Song* temp = head;
        while (temp) {
            cout << temp->title;
            if(temp == current)cout<<"  <------Playing";
            cout<<endl;
            temp = temp->next;
        }
    }

    ~Playlist() {
        while (head) {
            Song* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    Playlist myPlaylist;

    myPlaylist.addSong("Song 1");
    myPlaylist.addSong("Song 2");
    myPlaylist.addSong("Song 3");
    myPlaylist.addSong("Song 4");

    myPlaylist.displayPlaylist();

    myPlaylist.playCurrentSong();
    myPlaylist.nextSong();
    myPlaylist.nextSong();
    myPlaylist.prevSong();

    myPlaylist.removeCurrentSong();
    myPlaylist.displayPlaylist();

    myPlaylist.nextSong();
    myPlaylist.nextSong();

    return 0;
}