#include <bits/stdc++.h>

using namespace std;

const int MAX_SIZE_OF_FILE = 4480;

bool err = false;

class Inode {

public:
    string name;                    //16 bytes
    bool type;                      //1 byte
    int file_size;                  //4 bytes
    char* date_created;             //28 bytes
    char* date_modified;            //28 bytes
    vector<int> direct_block_addr;  //12 bytes
    int index_block_addr = -1;           //4 byte
    vector<int> index_block_contents;
    int blocks_allocated;

    //total 93 byte space is required for the inode

    Inode(string name) {

        //sets the name
        this->name = name;

        if(name.length() > 16) {
            cout << "Illegal File naming" << endl;
            err = true;
        }

        int f = 0;

        string dir_name = "";

        for(char c: name) {
            if(c == '/') f++;
            else if(f == 1) dir_name+=c;
        }

        if(dir_name.length() > 4 && f == 2) {
            cout << "Illegal Directory name" << endl;
            err = true;
        }

        //finds the type (file in root(lvl 1) or file in directory(lvl 2));
        if(f == 2) type = 1;
        else type = 0;

        file_size = 0;
        
        time_t curr_time;
        time(&curr_time);

        date_created = (char*) malloc(28*sizeof(char));
        strcpy(date_created, ctime(&curr_time)); 
        time(&curr_time);
        date_modified = (char *) malloc(28*sizeof(char));
        strcpy(date_modified, ctime(&curr_time));

        for(int i = 0; i<3; i++) direct_block_addr.push_back(-1);
        
        blocks_allocated = 0;
    }
};