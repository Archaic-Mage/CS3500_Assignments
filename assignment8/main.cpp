#include "inode.cpp"

const int INODE_SIZE = 93;

int getFreeBlock(vector<bool> blocks) {
    int i = 0;
    for(auto b: blocks) {
        if(!b) {
            return i;
        }
        i++;
    }

    cout << "No space available" << endl;
    return -1;
}

void freeBlocks(Inode* to_del, vector<bool> &is_filled) {
    vector<int> blocks(to_del->direct_block_addr);
    blocks.push_back(to_del->index_block_addr);
    for(auto b: to_del->index_block_contents) {
        blocks.push_back(b);
    }

    for(auto b: blocks) {
        if(b != -1) {
            is_filled[b] = false;
        }
    }
}


int main() {

    map<string, Inode*> file_info;
    map<string, int> block_occupied;
    map<string, vector<string>> contents;

    int file_size;
    string disk_file_name;
    int block_size = 128;

    cout << "Enter the Disk File Size: ";
    cin >> file_size;

    int blocks = (file_size*(1 << 10))/128;

    vector<bool> is_filled(blocks, false);

    string command = "start";

    while(command != "exit") {
        cout << "Enter command=> ";
        cin >> command;

        if(command == "load") {
            string file_name;
            cin >> file_name;
            Inode* file = new Inode(file_name); 

            if(err) {
                continue;
            }

            if(file_info.find(file_name) != file_info.end()) {
                cout << "File Already Present" << endl;
            }

            int block_occ = getFreeBlock(is_filled);

            if(block_occ == -1) continue;

            file_info[file_name] = file;

            block_occupied[file_name] = block_occ;
            is_filled[block_occ] = true;

            cout << "File created and loaded" << endl;

        } else if(command == "delete") {
            string file_name;
            cin >> file_name;
            if(file_info.find(file_name) != file_info.end()) {
                Inode* to_del = file_info[file_name];
                file_info.erase(file_name);
                is_filled[block_occupied[file_name]] = false;
                block_occupied.erase(file_name);
                freeBlocks(to_del, is_filled);
                contents.erase(file_name);
                cout << "File successfully deleted" << endl;
            } else {
                cout << "File does not exist" << endl;
                continue;
            }
        } else if(command == "print") {
            string file_name;
            cin >> file_name;
            if(file_info.find(file_name) != file_info.end()) {
                for(auto s: contents[file_name]) {
                    cout << s << endl;
                }
            } else {
                cout << "File does not exist" << endl;
                continue;
            }
        } else if(command == "append") {
            string file_name; 
            cin >> file_name;
            string content;
            cin >> content;

            int byte_occupied = content.length()+1;

            if(file_info.find(file_name) != file_info.end()) {
                Inode* to_change = file_info[file_name];
                if(to_change->file_size+byte_occupied > MAX_SIZE_OF_FILE) {
                    cout << "Segmentation fault" << endl;
                    continue;
                }

                to_change->file_size += byte_occupied;

                int blocks_required = to_change->file_size/128;
                if(to_change->file_size%128) blocks_required++;

                int blocks_to_allocate = blocks_required - to_change->blocks_allocated;
                int j = 1;
                while(j + to_change->blocks_allocated <=3) {
                    if(j > blocks_to_allocate) break;
                    int b = getFreeBlock(is_filled); 
                    is_filled[b] = true;
                    to_change->direct_block_addr[to_change->blocks_allocated+j-1] = b;
                    j++;
                }

                if(j <= blocks_to_allocate) {
                    to_change->index_block_addr = getFreeBlock(is_filled);
                    is_filled[to_change->index_block_addr] = true;
                }
                
                while(j <= blocks_to_allocate) {
                    int b = getFreeBlock(is_filled);
                    to_change->index_block_contents.push_back(b);
                    is_filled[b] = true;
                    j++;
                }

                time_t t;
                time(&t);
                strcpy(to_change->date_modified ,ctime(&t));

                to_change->blocks_allocated = blocks_required;

                contents[file_name].push_back(content);

                cout << "Inserted into the file" << endl;
            } else {
                cout << "File does not exist" << endl;
                continue;
            }
        } else if(command == "display") {
            for(auto files: file_info) {
                cout << files.first << ": " << files.second->file_size << " bytes" <<endl;
            }
        } else if(command == "freespace") {
            int free_blocks = 0;
            for(auto b: is_filled) {
                if(!b) {
                    free_blocks++;
                }
            }
            cout << "Free Blocks: " << free_blocks << endl;
            cout << "Free space: " << free_blocks*128 + block_occupied.size()*(128-93) << " bytes" << endl;
        } else if(command == "printinode") {
            string file_name;
            cin >> file_name;
            if(file_info.find(file_name) != file_info.end()) {
                Inode* inode_info = file_info[file_name];
                cout << "Filename: " << inode_info->name << endl;
                cout << "Size: " << inode_info->file_size << " bytes" <<endl;
                cout << "Date Created: " << inode_info->date_created;
                cout << "Date Last Modified: " << inode_info->date_modified;
                cout << "Direct Block Values: ";
                for(auto b: inode_info->direct_block_addr) if(b != -1) cout << b << " ";
                cout << endl;
                cout << "Index Block is stored in: " <<inode_info->index_block_addr << endl;
                cout << "Index Block contents: ";
                for(auto b: inode_info->index_block_contents) cout << b << " ";
                cout << endl;
            } else {
                cout << "File does not exist" << endl;
                continue;
            }
        } else if(command == "exit") break;
        else {
            cout << "Wrong command" << endl;
        }
        cout << endl;
    }

    return 0;
}