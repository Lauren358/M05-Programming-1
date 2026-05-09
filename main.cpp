#include <iostream>
#include <string>
#include "sqlite3.h"
using namespace std;

/* Program name: Database Connection and Callbacks
*  Author: Lauren Davis
*  Date last updated: 5/8/2026
* Purpose: This program opens a connection to the Chinook database. For each album a track listing will be shown and each album will appear in the results once. If the connection doesn't open successfully an error message will print and end the program, if it opens successfully, a success message will print when it.
*/

//note AI was used to aid in ensuring the connection to database code was correct. The code was throughly looked over by human eye.


int callback(void *data, int argc, char **argv, char **azColName);

//structure remembers last album that was printed and prints the album name once without repitition
struct AlbumState {
    int lastAlbumId = -1;
};

int callback(void *data, int argc, char **argv, char **azColName) {
    AlbumState *state = static_cast<AlbumState *>(data);

    int albumId = stoi(argv[0]);        // AlbumId
    string albumTitle = argv[1];        // Album Title
    string trackName = argv[2];         // Track Name
    string artistName = argv[3];        // Artist Name

    // Print album once
    if (albumId != state->lastAlbumId) {
        state->lastAlbumId = albumId;
        
    //Print out ID, album name, artist
        cout << "\nAlbumId: " << albumId
             << "\nAlbum: " << albumTitle
             << "\nArtist: " << artistName << endl;
    }

    // Print track
    cout << "\nTracks: " << trackName << endl;

    return 0;
}

int main() {
    sqlite3 *db;
    int ret;
//returns code from sql database
    ret = sqlite3_open("chinook.db", &db);
//if the database does not connect the error message will show 
    if (ret != SQLITE_OK) {
        cout << "Error in connection: unable to open database file" << endl;
        cout << sqlite3_errmsg(db) << endl;
        return 1;
    }

    cout << "Database opened successfully!" << endl;

    const char *sql =
        "SELECT al.AlbumId, al.Title, t.Name, art.Name "
        "FROM albums "
        "JOIN tracks ON t.AlbumId = al.AlbumId "
        "JOIN artists ON al.ArtistId = art.ArtistId "
        "ORDER BY al.AlbumId;";

    AlbumState state;
    char *errMsg = nullptr;

    ret = sqlite3_exec(db, sql, callback, &state, &errMsg);
//if the database does not connect the error message will show 
    if (ret != SQLITE_OK) {
        cout << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
    }
//closes database to not corrupt it
    sqlite3_close(db);

    return 0;
}
