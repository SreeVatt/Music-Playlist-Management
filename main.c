#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

// Define a structure to represent a song
struct Song {
    char songName[100];
    char singer[100];
    char musicDirector[100];
    struct Song* next;
    struct Song* prev;
};

struct Song* head = NULL;
struct Song* tail = NULL;

// Function to add a song to the playlist
void addSong(char songName[], char singer[], char musicDirector[]) {
    struct Song* newSong = (struct Song*)malloc(sizeof(struct Song));
    strcpy(newSong->songName, songName);
    strcpy(newSong->singer, singer);
    strcpy(newSong->musicDirector, musicDirector);
    newSong->next = NULL;

    if (head == NULL) {
        newSong->prev = NULL;
        head = tail = newSong;
    } else {
        tail->next = newSong;
        newSong->prev = tail;
        tail = newSong;
    }
}

// Function to print the playlist with node values
void printPlaylist() {
    if (head == NULL) {
        printf("Playlist is empty.\n");
        return;
    }

    struct Song* current = head;
    printf("Playlist:\n");
    while (current != NULL) {
        printf("Song: %s, Singer: %s, Music Director: %s\n", current->songName, current->singer, current->musicDirector);
        current = current->next;
    }
}

// Function to remove a song from the playlist
void removeSong(char songName[]) {
    struct Song* current = head;
    while (current != NULL) {
        if (strcmp(current->songName, songName) == 0) {
            if (current == head) {
                head = current->next;
                if (head != NULL) {
                    head->prev = NULL;
                }
            } else if (current == tail) {
                tail = current->prev;
                tail->next = NULL;
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            free(current);
            printf("Song '%s' removed from the playlist.\n", songName);
            return;
        }
        current = current->next;
    }
    printf("Song '%s' not found in the playlist.\n", songName);
}

// Function to shuffle the playlist (rearrange the order of songs)
void shufflePlaylist() {
    if (head == NULL || head->next == NULL) {
        return; // No need to shuffle if there are 0 or 1 songs
    }

    struct Song* temp = NULL;
    struct Song* current = head;
    int count = 0;

    // Count the number of songs in the playlist
    while (current != NULL) {
        count++;
        current = current->next;
    }

    // Perform Fisher-Yates shuffle
    current = head;
    while (count > 0) {
        int rand_index = rand() % count;
        for (int i = 0; i < rand_index; i++) {
            current = current->next;
        }

        // Swap the current song with the last song
        temp = current;
        current = tail;
        tail = temp;

        count--;
    }
}

int main() {
    // Sample data: Add songs to the playlist
    addSong("Song1", "Singer1", "Composer1");
    addSong("Song2", "Singer2", "Composer2");
    addSong("Song3", "Singer3", "Composer3");
    addSong("Song4", "Singer4",  "Composer4");

    // Print the initial playlist 
    printPlaylist();   

    // Shuffle the playlist 
    shufflePlaylist();
    printf("\nPlaylist after shuffling:\n");  
    printPlaylist();

    // Remove a song from the playlist
    removeSong("Song2"); 
    printf("\nPlaylist after removing 'Song2':\n");
    printPlaylist();

    return 0;
}