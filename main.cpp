#include <iostream>
#include <string>
#include "sqlite3.h"
using namespace std;

/* Program name: Database Connection and Callbacks
*  Author: Lauren Davis
*  Date last updated: 5/8/2026
* Purpose: This program opens a connection to the Chinook database. For each album a track listing will be shown and each album will appear in the results once. If the connection doesn't open successfully an error message will print and end the program, if it opens successfully, a success message will print when it.
*/


// Forward declaration
int callback(void *data, int argc, char **argv, char **azColName);

struct AlbumState {
    int lastAlbumId = -1;
};

int callback(void *data, int argc, char **argv, char **azColName) {
    AlbumState *state = static_cast<AlbumState *>(data);

    int albumId = stoi(argv[0]);        // AlbumId
    string albumTitle = argv[1];        // Album Title
    string trackName = argv[2];         // Track Name
    string artistName = argv[3];        // Artist Name

    // Print album header once
    if (albumId != state->lastAlbumId) {
        state->lastAlbumId = albumId;
        cout << "\nAlbum: " << albumTitle
             << " (ID: " << albumId << ")"
             << " - Artist: " << artistName << endl;
    }

    // Print track
    cout << "  - " << trackName << endl;

    return 0;
}

int main() {
    sqlite3 *db;
    int rc;

    rc = sqlite3_open("chinook.db", &db);

    if (rc != SQLITE_OK) {
        cout << "Error in connection: unable to open database file" << endl;
        cout << sqlite3_errmsg(db) << endl;
        return 1;
    }

    cout << "Database opened successfully!" << endl;

    const char *sql =
        "SELECT Album.AlbumId, Album.Title, Track.Name, Artist.Name "
        "FROM Album "
        "JOIN Track ON Track.AlbumId = Album.AlbumId "
        "JOIN Artist ON Album.ArtistId = Artist.ArtistId "
        "ORDER BY Album.AlbumId;";

    AlbumState state;
    char *errMsg = nullptr;

    rc = sqlite3_exec(db, sql, callback, &state, &errMsg);

    if (rc != SQLITE_OK) {
        cout << "SQL error: " << errMsg << endl;
        sqlite3_free(errMsg);
    }

    sqlite3_close(db);

    return 0;
}
