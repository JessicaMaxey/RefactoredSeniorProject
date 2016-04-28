#ifndef DATABASE_H
#define DATABASE_H

#include <stdlib.h>
#include <sqlite3.h>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <string>
using std::string;

#include <string.h>

#include <vector>
using std::vector;

#include <taglib/taglib_export.h>
#include <tstring.h>
#include <fileref.h>
#include <tag.h>
using namespace TagLib;

class database
{
public:
    database();
    ~database();
    int ReadFromDatabase(string sql_str);
    static int callback(void * NotUsed, int argc, char ** argv, char ** azColName);
    void GetPlaylistOrMP3(string playlist_selection_num, bool playlist_or_mp3);
    vector<string> GetFileLocations();
    void DisplayMP3InPlaylist(string playlist_pk);
    void DisplayMP3();
    void DisplayPlaylist();
    void DeletePlaylist(string playlist_t_delete);
    void DeleteMP3FromPlaylist(string playlist_to_delete);
    void DeleteMP3(string mp3_to_delete);
    void AddToPlaylist(string playlist_adding_to);
    void EditMP3();
    void EditMP3OnPlaylist(string playlist_to_edit);
    void AddNewMP3InDatabase(string mp3_name, string new_mp3_location);
    
    vector<string> database_info;
    vector<string> file_locations;
    
private:
    const char * database_path = "/home/jess/Documents/MusicDatabase/musicdb";

};

#endif // DATABASE_H
