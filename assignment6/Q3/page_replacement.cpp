/* 

    Author: Soham Tripathy
    CS3500: Assignment 6
    Topic: Page Replacement Policy

*/

#include <bits/stdc++.h>

using namespace std;

class PageFrame {
    int max_page_frame_size;
    int page_faults;
    map<int,int> page_index;
    vector<pair<int, int>> frame;
    vector<int> replacement;

public:
    PageFrame() {
        cout << "Page-frame Size: ";
        cin >> max_page_frame_size;
        page_faults = 0;
    }

    int findNext(vector<int> sequence, int i) {
        int to_find= sequence[i];
        for(int j = i+1; j<sequence.size(); j++) {
            if(sequence[j] == to_find) return j-i;
        }

        return (sequence.size()-i);
    }

    void fifo(vector<int> sequence) {
        for(int i = 0; i<sequence.size(); i++) {
            if(!page_index.count(sequence[i])) {
                int index = frame.size();
                if(index < max_page_frame_size) {
                    frame.push_back({sequence[i], 0});
                    page_index[sequence[i]] = index;
                } else {
                    page_index.erase(frame[0].first);
                    frame.erase(frame.begin());
                    frame.push_back({sequence[i], 0});
                    page_index[sequence[i]] = index;
                }
                page_faults++;
                for(auto page: frame) {
                    cout << page.first << " ";
                }
                cout << '\n';
            } else cout << "No page fault\n";
        }

        cout << endl;

        cout << "Total number of page faults = " << page_faults << endl;
    }

    void optimal(vector<int> sequence) {
        for(int i = 0; i<sequence.size(); i++) {
            int next_seq = findNext(sequence, i);
            if(!page_index.count(sequence[i])) {
                int index = frame.size();
                if(index < max_page_frame_size) {
                    frame.push_back({sequence[i], next_seq});
                    replacement.push_back(sequence[i]);
                    page_index[sequence[i]] = index;
                } else {
                    int to_remove = 0;
                    int j = 0;
                    int max_distance = 0;
                    for(auto page: frame) {
                        if(page.second > max_distance) {
                            to_remove = j;
                            max_distance = page.second;
                        }
                        j++;
                    }
                    page_index.erase(frame[to_remove].first);
                    frame[to_remove] = {sequence[i], next_seq};
                    page_index[sequence[i]] = to_remove;
                }
                page_faults++;
                for(auto page: frame) {
                    cout << page.first << " ";
                }
                cout << '\n';
            } else {
                int next_seq = findNext(sequence, i);
                frame[page_index[sequence[i]]].second = next_seq;
                cout << "No page fault\n";
            }
        }

        cout << endl;

        cout << "Total number of page faults = " << page_faults << endl;
    }

    void lru(vector<int> sequence) {
        for(int i = 0; i<sequence.size(); i++) {
            if(!page_index.count(sequence[i])) {
                int index = frame.size();
                if(index < max_page_frame_size) {
                    frame.push_back({sequence[i], 0});
                    replacement.push_back(sequence[i]);
                    page_index[sequence[i]] = index;
                } else {
                    int to_remove = replacement[0];
                    int j = page_index[to_remove];
                    frame[j] = {sequence[i], 0};
                    replacement.erase(replacement.begin());
                    replacement.push_back(sequence[i]);
                    page_index.erase(to_remove);
                    page_index[sequence[i]] = j;
                }
                page_faults++;
                for(auto page: frame) {
                    cout << page.first << " ";
                }
                cout << '\n';
            } else {
                int index = 0;
                for(auto page: replacement) {
                    if(page == sequence[i]) break;
                    index++;
                }
                replacement.erase(replacement.begin() + index);
                replacement.push_back(sequence[i]);
                cout << "No page fault\n";
            }
        }

        cout << endl;

        cout << "Total number of page faults = " << page_faults << endl;
    }
};


int main() {

    int sequence_length;
    cout << "Enter Sequence Length: ";
    cin >> sequence_length;

    vector<int> sequence;
    cout << "Enter Sequence: ";
    for(int i = 0; i<sequence_length; i++) {
        int page_number;
        cin >> page_number;
        sequence.push_back(page_number);
    }

    PageFrame page_frame = PageFrame();

    cout << endl;
    cout << "FIFO: 1\n";
    cout << "Optimal: 2\n";
    cout << "LRU: 3\n";
    cout << endl;

    int replacement_policy;
    cout << "Enter Page replacement strategy: ";
    cin >> replacement_policy;
    cout << endl;

    if(replacement_policy == 1) page_frame.fifo(sequence);
    else if(replacement_policy == 2) page_frame.optimal(sequence);
    else if(replacement_policy == 3) page_frame.lru(sequence);
    else cout << "invalid replacement policy";

    return 0;
}