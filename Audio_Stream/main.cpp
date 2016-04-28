#include <stdio.h>
#include <unistd.h>
#include <string>
#include <queue>
using std::queue;

#include <vector>
using std::vector;

#include "vlc_player.h"
#include "socket_creator.h"
//#include "Nano.h"
#include "database.h"

enum command_vals
{
    PLAY,
    PAUSE,
    NEXT,
    PREVIOUS,
    STOP,
    SELECT,
    MENU,
    EXIT,
    TEST,
};

struct Commands
{
  enum{NEW_SONG, START, PAUSE, STOP, SET_TIME} command_type;
  string song_name;
  float time;
}; 

struct LEDCommands
{
    enum{RAINBOW, SHIFT, FADE, RED, PURPLE, BLUE, TEAL, GREEN, YELLOW, STOP} command_type;
    int speed;

};

queue<string> input;
queue<LEDCommands> led_command_queue;
const int NUM_BUTTONS = 5;

vlc_player player;

database db;
//Nano nano;

void LEDMenu();
void MP3Menu();
void PlaylistMenu();
void Menu();
void TestButton();


int main(int argc, char **argv)
{
    bool done = false;
    socket_creator socket;
    
    socket.InitSocket();
    player.InitVLC();
    
    while(done == false)
    {
        player.Play();
    
        //nano.LEDONandOFF(socket.GetData());
        sleep(0);
        
        string user_input;

        cin >> user_input;

        input.push(user_input);

        string command = "";
        const string commands [] = {"play", "pause", "next", "previous", "stop", "select", "menu", "exit", "test"};
        int command_num = 0;


        while(input.size() == 0)
        {
            sleep(0);
        }

        command = input.front();
        input.pop();

        for (int i = 0; i < (sizeof(commands)/ sizeof(string)); i++)
        {
            if(!done)
            {
                command_num = i;

                if (command == commands[i])
                    break;
            }
        }

        switch (command_num)
        {
            case PLAY:
                player.Play();
                break;
            case PAUSE:
                player.Pause();
                break;
            case NEXT:
                player.Next();
                break;
            case PREVIOUS:
                player.Prev();
                break;
            case STOP:
                player.Stop();
                break;
            case SELECT:
                break;
            case MENU:
                Menu();
                break;
            case TEST:
                //TestButton();
                break;
            case EXIT:
                done = true;
                break;
            default:
                break;

        }
    }
    
    return 0;
}

/*void LEDMenu()
{
    static std::thread ledThread(LEDThreadCommand);
    LEDCommands led_cmd;
    Nano n;

    string selection = "";

    cout << "Please select one of the following options:" << endl;
    cout << "1. Fade Rainbow" << endl;
    cout << "2. Color Shift" << endl;
    cout << "3. Fade On and Off" << endl;
    cout << "4. Red" << endl;
    cout << "5. Purple" << endl;
    cout << "6. Blue" << endl;
    cout << "7. Teal" << endl;
    cout << "8. Green" << endl;
    cout << "9. Yellow" << endl;
    cout << "10. Stop" << endl;
    cout << "11. Exit" << endl;
    cout << "Selection: ";

    cin >> selection;
    cout << endl;

    int selection_num = atoi(selection.c_str());

    if(selection_num < 4)
    {

        string speed = "";

        cout << "Please select a speed 1-5:" << endl;
        cout << "Speed: ";

        cin >> speed;
        cout << endl;

        led_cmd.speed = atoi(speed.c_str());
    }

    switch(selection_num)
    {
        case 1:
            cout << "Fade Rainbow selected" << endl;
            accesslock.lock();
            led_cmd.command_type = LEDCommands::RAINBOW;
            led_command_queue.emplace(led_cmd);
            accesslock.unlock();
            break;
        case 2:
            cout << "Color Shift selected" << endl;
            accesslock.lock();
            led_cmd.command_type = LEDCommands::SHIFT;
            led_command_queue.emplace(led_cmd);
            accesslock.unlock();
            break;
        case 3:
            cout << "Fade On and Off selected" << endl;
            accesslock.lock();
            led_cmd.command_type = LEDCommands::FADE;
            led_command_queue.emplace(led_cmd);
            accesslock.unlock();
            break;
        case 4:
            cout << "Red selected" << endl;
            accesslock.lock();
            led_cmd.command_type = LEDCommands::RED;
            led_command_queue.emplace(led_cmd);
            accesslock.unlock();
            break;
        case 5:
            cout << "Purple selected" << endl;
            accesslock.lock();
            led_cmd.command_type = LEDCommands::PURPLE;
            led_command_queue.emplace(led_cmd);
            accesslock.unlock();
            break;
        case 6:
            cout << "Blue selected" << endl;
            accesslock.lock();
            led_cmd.command_type = LEDCommands::BLUE;
            led_command_queue.emplace(led_cmd);
            accesslock.unlock();
            break;
        case 7:
            cout << "Teal selected" << endl;
            accesslock.lock();
            led_cmd.command_type = LEDCommands::TEAL;
            led_command_queue.emplace(led_cmd);
            accesslock.unlock();
            break;
        case 8:
            cout << "Green selected" << endl;
            accesslock.lock();
            led_cmd.command_type = LEDCommands::GREEN;
            led_command_queue.emplace(led_cmd);
            accesslock.unlock();
            break;
        case 9:
            cout << "Yellow selected" << endl;
            accesslock.lock();
            led_cmd.command_type = LEDCommands::YELLOW;
            led_command_queue.emplace(led_cmd);
            accesslock.unlock();
            break;
        case 10:
            cout << "Turning leds off" << endl;
            accesslock.lock();
            led_cmd.command_type = LEDCommands::STOP;
            led_command_queue.emplace(led_cmd);
            accesslock.unlock();
            n.LEDallOFF();
            cout << "thread ended" << endl;
            break;
        default:
            break;
    }
}*/

void MP3Menu()
{
   string selection = "";

    cout << "Please select one of the following options:" << endl;
    cout << "1. MP3 options" << endl;
    //cout << "2. Add new MP3s" << endl;
    cout << "3. Exit" << endl;
    cout << "Selection: ";

    cin >> selection;
    cout << endl;

    int selection_num = atoi(selection.c_str());

    switch(selection_num)
    {
        case 1:
            {

                selection = "";

                cout << "Select one of the following mp3 options:" << endl;
                cout << "1. Play a MP3" << endl;
                cout << "2. Edit a MP3" << endl;
                cout << "3. Delete a MP3" << endl;
                cout << "4. Add to currently playing" << endl;
                cout << "5. Exit" << endl;
                cout << "Selection: ";

                cin >> selection;
                cout << endl;

                db.DisplayMP3();

                vector<string> mp3 = db.database_info;

                string mp3_selection = "";

                cout << "Select a mp3: ";
                cin >> mp3_selection;
                cout << endl;

                int mp3_selection_num = atoi(mp3_selection.c_str());

                selection_num = 0;

                selection_num = atoi(selection.c_str());

                int mp3_key = 0;
                int mp3_file_location = 0;
                int count = 1;
                
                //gets the file location from the vector 
                for (int i = 0; i < (mp3.size()); i++)
                {
                    if (i % 3 == 2)
                    {
                        if (count == mp3_selection_num)
                        {
                            mp3_file_location = i;
                            break;
                        }
                        else
                            count++;
                    }
                }
                
                //Gets the pk for the mp3 in the vector, corrisponds with pk in database
                count = 1;
                for (int i = 0; i < (mp3.size()); i++)
                {
                    if (i % 3 == 0)
                    {
                        if (count == mp3_selection_num)
                        {
                            mp3_key = i;
                            break;
                        }
                        else
                            count++;
                    }
                }

                switch(selection_num)
                {
                    case 1:
                        fprintf(stdout, "MP3 Menu Playing\n");
                        player.AddToPlaylist(mp3[mp3_file_location]);
                        player.Play();
                        break;
                    case 2:
                        break;
                    case 3:
                        db.DeleteMP3(mp3[mp3_key]);
                        break;
                    case 4:
                        player.AddToPlaylist(mp3[mp3_file_location]);
                        break;
                    case 5:
                        break;
                    default:
                        break;

                }
            }
            break;
        case 2:
            //db.AddNewMP3();
            break;
        case 3:
            break;
        default:
            break;
    }
}

void PlaylistMenu()
{
    string selection = "";

    cout << "Please select one of the following options:" << endl;
    cout << "1. Display playlists" << endl;
    //cout << "2. Create new playlist" << endl;
    cout << "3. Exit" << endl;
    cout << "Selection: ";

    cin >> selection;
    cout << endl;

    int selection_num = atoi(selection.c_str());

    switch(selection_num)
    {
        case 1:
            {
                //Displays the playlists in the database
                db.DisplayPlaylist();
                vector<string> playlist = db.database_info;

                string playlist_selection = "";

                cout << "Select a playlist: ";
                cin >> playlist_selection;
                cout << endl;

                int playlist_selection_num = atoi(playlist_selection.c_str());


                selection = "";

                cout << "Select one of the following playlist options:" << endl;
                cout << "1. Play playlist" << endl;
                cout << "2. Add MP3s to playlist" << endl;
                cout << "3. Edit MP3s on playlist" << endl;
                cout << "4. Delete MP3s on playlist" << endl;
                cout << "5. Delete this playlist" << endl;
                cout << "6. Exit" << endl;
                cout << "Selection: ";

                cin >> selection;
                cout << endl;

                selection_num = 0;

                selection_num = atoi(selection.c_str());


                int playlist_key = 0;
                int count = 1;
                for (int i = 0; i < (playlist.size()); i++)
                {
                    if (i % 2 == 0)
                    {
                        if (count == playlist_selection_num)
                        {
                            playlist_key = i;
                            break;
                        }
                        else
                            count++;
                    }
                }

                switch(selection_num)
                {
                    //need to add function that will loop through the play list file locations
                    //and add them to a vlc play list to play
                    case 1:
                    {
                        db.GetPlaylistOrMP3(playlist[playlist_key], 0);
                        vector<string> file_locations = db.GetFileLocations();
                        player.CreatePlaylist(file_locations);
                        player.Play();
                        //PlayPlaylist(playlist[playlist_key], 0);
                    }
                        break;
                    case 2:
                        db.AddToPlaylist(playlist[playlist_key]);
                        break;
                    case 3:
                        //EditMP3OnPlaylist(playlist[playlist_key]);
                        break;
                    case 4:
                        db.DeleteMP3FromPlaylist(playlist[playlist_key]);
                        break;
                    case 5:
                        db.DeletePlaylist(playlist[playlist_key]);
                        break;
                    default:
                        break;

                }
            }
            break;
        case 2:
            break;
        default:
            break;
    }
}

void Menu()
{
    string selection = "";

    cout << "Please select one of the following options:" << endl;
    cout << "1. Playlist menu" << endl;
    cout << "2. MP3 menu" << endl;
    cout << "3. LED menu" << endl;
    cout << "4. Exit" << endl;
    cout << "Selection: ";


    cin >> selection;
    cout << endl;

    int selection_num = atoi(selection.c_str());

    switch(selection_num)
    {
        case 1:
            PlaylistMenu();
            break;
        case 2:
            MP3Menu();
            break;
        case 3:
            //LEDMenu();
            break;
        case 4:
            break;
        default:
            break;
    }

}

/*void TestButton()
{
    Nano n;
    bool pressed = true;
    int i;

    while(1)
    {
        for (i = 0; i < NUM_BUTTONS; i++)
        {
            pressed = n.CheckButtons(i);

            if(pressed == false)
            {
                cout << "Button " << i << " is being pressed." << endl;
                break;
            }
        }
    }

}
*/