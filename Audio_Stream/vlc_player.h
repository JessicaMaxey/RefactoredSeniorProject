#ifndef VLC_PLAYER_H
#define VLC_PLAYER_H

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
using std::string;

#include <vector>
using std::vector;

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <taglib/taglib_export.h>
#include <tstring.h>
#include <fileref.h>
#include <tag.h>
using namespace TagLib;

class vlc_player
{
public:
    vlc_player();
    ~vlc_player();
    void InitVLC();
    void Play();
    void Pause();
    void Stop();
    void Next();
    void Prev();
    void CreatePlaylist(vector<string> file_locations);
    void AddToPlaylist(string file_location); 
    void GetMP3info(string file_path);

private:
    int mypipe[2];
    FILE * vlc_fd;
};



#endif // VLC_PLAYER_H
