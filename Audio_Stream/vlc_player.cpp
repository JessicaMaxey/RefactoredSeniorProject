#include "vlc_player.h"

vlc_player::vlc_player() : vlc_fd(0)
{
}

vlc_player::~vlc_player()
{
}

void vlc_player::InitVLC()
{
    if(pipe(mypipe) == -1)
    {
        fprintf(stderr, "Pipe failed\n");
        exit(-1);
    }
    
    pid_t pid = fork();
    
    if(pid < 0)
    {
        fprintf(stderr, "Fork failed\n");
        exit(-1);
    }
    else if(pid == 0)
    {
        //if child process, we want to read from parent
        if(dup2(mypipe[0], 0)== -1)
        {
            fprintf(stderr, "Failed to read from end of pipe\n");
            exit(-1);
        }
        
        if(close(mypipe[1]) != 0)
        {
            fprintf(stderr, "Failed to close pipe[1]\n");
            exit(-1);
        }
        
        if(execl("/home/jess/Documents/GitRepo/vlc/vlc", "/home/jess/Documents/GitRepo/vlc ", "-I rc", NULL) == -1)
        {
            fprintf(stderr, "Failed to exec");
            exit(-1);
        }
    }
    

    
    /*if parent proces we want to write to child
    if(pid > 0)
    {
        if (dup2(mypipe[1], 1) == -1)
        {
            fprintf(stderr, "Failed to write to end of pipe\n");
        }
    }*/
    
    if(close(mypipe[0]) != 0)
    {
        fprintf(stderr, "Failed to close pipe[1]\n");
        exit(-1);
    }
    
    vlc_fd = fdopen(mypipe[1], "w");
    
}

void vlc_player::Play()
{
    fprintf(vlc_fd, "play \n");
    fflush(vlc_fd);
}

void vlc_player::Pause()
{
    fprintf(vlc_fd, "pause \r");
    fflush(vlc_fd);
}

void vlc_player::Stop()
{
    fprintf(vlc_fd, "stop \n");
    fflush(vlc_fd);
}

void vlc_player::Next()
{
    fprintf(vlc_fd, "next \n");
    fflush(vlc_fd);
}

void vlc_player::Prev()
{
    fprintf(vlc_fd, "prev \n");
    fflush(vlc_fd);
}

void vlc_player::CreatePlaylist(vector<string> file_locations)
{
    //checking to see if something is currently playing
    fprintf(vlc_fd, "is_playing \n");
    fflush(vlc_fd);
    
    //Stops whatever is playing
    fprintf(vlc_fd, "stop \n");
    fflush(vlc_fd);
    
    //Make sure starting with clean playlist
    fprintf(vlc_fd, "clear \n");
    fflush(vlc_fd);
    
    
    for(unsigned int i = 0; i < file_locations.size(); i++)
    {
        const char * char_file_locations = file_locations[i].c_str();
        fprintf(vlc_fd, "enqueue %s\n", char_file_locations);
        fflush(vlc_fd);
    }
}

void vlc_player::AddToPlaylist(string file_location)
{
    const char * char_file_location = file_location.c_str();
    fprintf(vlc_fd, "enqueue %s\n" , char_file_location);
    fflush(vlc_fd);
}

void vlc_player::GetMP3info(string file_path)
{
    FileRef file_ref (file_path.data());
    String artist = file_ref.tag()->artist();
    String title = file_ref.tag()->title();

    int time = file_ref.audioProperties()->length();

    int seconds = time % 60;
    int minutes = (time / 60) % 60;
    int hours = (time / 60 / 60) % 24;

    file_ref.save();

    cout << artist << " " << title << " " << hours << ":" << minutes << ":" << seconds << endl;
}

