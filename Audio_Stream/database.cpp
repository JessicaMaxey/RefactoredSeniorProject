#include "database.h"

database::database()
{
}

database::~database()
{
}

int database::callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;
    database * ctx = (database *) NotUsed;

    for(i = 0; i < argc; i++)
    {
        //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

        ctx->database_info.push_back(argv[i]);
        //database_info.push_back(argv[i]);
    }

    printf("\n");

    return 0;
}

int database::ReadFromDatabase(string sql_str)
{
    database_info.clear();

    sqlite3 *db;

    char *zErrMsg = 0;
    int db_handle;

    const char *sql;

    //Open database
    db_handle = sqlite3_open(database_path, &db);

    if( db_handle )
    {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
    }
    else
    {
        fprintf(stderr, "Opened database successfully\n");
    }

    sql = sql_str.c_str();

    //Execute SQL statement
    db_handle = sqlite3_exec(db, sql, callback, this, &zErrMsg);

    if(db_handle != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
    {
        fprintf(stdout, "Database queried successfully\n");
    }

    sqlite3_close(db);
    return 0;
}

void database::GetPlaylistOrMP3(string playlist_selection_num, bool playlist_or_mp3)
{
    string sql_str = "";

    if (playlist_or_mp3 == 0)
    {
            sql_str = "SELECT location FROM mp3 " \
                             "WHERE mp3_pk IN (SELECT mp3_fk FROM mp3_playlists " \
                                              "WHERE playlists_fk = " + playlist_selection_num + ");";
    }
    else
    {
            sql_str = "SELECT location FROM mp3 " \
                             "WHERE mp3_pk = " + playlist_selection_num + ";";
    }

    ReadFromDatabase(sql_str);
    file_locations = database_info;
}

vector<string> database::GetFileLocations()
{
    return file_locations;
}

void database::DisplayMP3InPlaylist(string playlist_pk)
{
    string sql_str = "SELECT mp3_pk, name FROM mp3 " \
                     "WHERE mp3_pk IN (SELECT mp3_fk FROM mp3_playlists " \
                                      "WHERE playlists_fk = " + playlist_pk + ");";
    int count = 1;

    ReadFromDatabase(sql_str);

    for (int i = 0; i < database_info.size(); i++)
    {
        if (i % 2)
        {
            cout << count << "." << database_info[i] << endl;
            count++;
        }
    }
}

void database::DisplayMP3()
{
    string sql_str = "SELECT * FROM mp3;";
    int count = 1;

    ReadFromDatabase(sql_str);

    for (int i = 0; i < database_info.size(); i++)
    {
        if (i % 3 == 1)
        {
            cout << count << "." << database_info[i] << endl;
            count++;
        }
    }
}

void database::DisplayPlaylist()
{
    string sql_str = "SELECT * FROM playlists;";
    int count = 1;

    ReadFromDatabase(sql_str);

    for (int i = 0; i < (database_info.size()); i++)
    {
        if (i % 2)
        {
            cout << count << "." << database_info[i] << endl;
            count++;
        }
    }    
}

void database::DeletePlaylist(string playlist_to_delete)
{
    string sql_str = "DELETE FROM playlists WHERE playlists_pk = " + playlist_to_delete + ";";

    ReadFromDatabase(sql_str);

    sql_str = "";

    sql_str = "DELETE FROM mp3_playlists WHERE playlists_fk = " + playlist_to_delete + ";";

    ReadFromDatabase(sql_str);    
}

void database::DeleteMP3FromPlaylist(string playlist_to_delete)
{
    DisplayMP3InPlaylist(playlist_to_delete);

    string mp3_selection = "";

    vector<string> mp3 = database_info;

    cout << "Select a mp3: ";
    cin >> mp3_selection;
    cout << endl;

    int mp3_selection_num = atoi(mp3_selection.c_str());

    string mp3_to_delete = "";

    int mp3_key = 0;
    int count = 1;
    for (int i = 0; i < (mp3.size()); i++)
    {
        if (i % 2 == 0)
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

    mp3_to_delete = mp3[mp3_key];

    string sql_str = "DELETE FROM mp3_playlists WHERE mp3_fk = " + mp3_to_delete + " AND playlists_fk = " + playlist_to_delete + ";";

    ReadFromDatabase(sql_str);    
}

void database::DeleteMP3(string mp3_to_delete)
{
    string sql_str = "DELETE FROM mp3 WHERE mp3_pk = " + mp3_to_delete + ";";

    ReadFromDatabase(sql_str);

    sql_str = "";

    sql_str = "DELETE FROM mp3_playlists WHERE mp3_fk = " + mp3_to_delete + ";";

    ReadFromDatabase(sql_str);
}

void database::AddToPlaylist(string playlist_adding_to)
{
    DisplayMP3();
    string mp3_selection = "";

    vector<string> mp3 = database_info;

    cout << "Select a mp3: ";
    cin >> mp3_selection;
    cout << endl;

    int mp3_selection_num = atoi(mp3_selection.c_str());

    string mp3_to_add = "";

    int mp3_key = 0;
    int count = 1;
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

    mp3_to_add = mp3[mp3_key];

    string sql_str = "INSERT INTO mp3_playlists (mp3_fk, playlists_fk) VALUES (" + mp3_to_add + " ," + playlist_adding_to + ");";

    ReadFromDatabase(sql_str);
}

void database::EditMP3()
{}

void database::EditMP3OnPlaylist(string playlist_to_edit)
{
    DisplayMP3InPlaylist(playlist_to_edit);

    string mp3_selection = "";
    char* mp3_name;

    vector<string> mp3 = database_info;

    cout << "Select a mp3: ";
    cin >> mp3_selection;
    cout << endl;

    int mp3_selection_num = atoi(mp3_selection.c_str());

    cin.ignore();
    cout << "Enter new name for MP3: ";
    std::cin.getline(mp3_name, 256);
    string new_mp3_name = mp3_name;
    cout << "Hello, " << mp3_name << "!\n";

    string mp3_to_edit = "";

    int mp3_key = 0;
    int count = 1;
    for (int i = 0; i < (mp3.size()); i++)
    {
        if (i % 2 == 0)
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

    mp3_to_edit = mp3[mp3_key];

    string sql_str = "UPDATE mp3 SET name = \"" + new_mp3_name + "\" WHERE mp3_pk = " + mp3_to_edit + ";";

    ReadFromDatabase(sql_str);
}

void database::AddNewMP3InDatabase(string mp3_name, string new_mp3_location)
{
    string sql_str = "INSERT INTO mp3 (name, location) VALUES (\"" + mp3_name + "\" , \"" + new_mp3_location + "\");";

    FileRef file_ref (new_mp3_location.data());
    String title = file_ref.tag()->title();

    if(title == "")
    {
        file_ref.tag()->setTitle(mp3_name);
        file_ref.save();
    }

    ReadFromDatabase(sql_str);
}