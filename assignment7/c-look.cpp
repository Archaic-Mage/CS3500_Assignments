#include <bits/stdc++.h>

using namespace std;

// pair<vector<int>, int> cLook(vector<int> requests, int head) {
//     vector<int> above,below;
//     for(int i=0;i<requests.size();i++)
//     {
//         if(requests[i]>head)
//         above.push_back(requests[i]);
//         else
//         below.push_back(requests[i]);
//     }
//     sort(above.begin(),above.end());
//     sort(below.begin(),below.end());

//     vector<int> order(above);
//     int total_head_movements = 0;

//     order.insert(order.end(), below.begin(), below.end());
//     for(auto req: order) {
//         total_head_movements+=abs(head - req);
//         head = req;
//     }   

//     return {order, total_head_movements};
// }

pair<vector<int>, int> cLook(vector<int> requests, int head)
{
    int total_head_movements = 0;
    int distance, cur_track;
    vector<int> left, right;
    vector<int> order;
 
    // Tracks on the left of the
    // head will be serviced when
    // once the head comes back
    // to the beginning (left end)
    for (int i = 0; i < requests.size(); i++) {
        if (requests[i] <= head)
            left.push_back(requests[i]);
        if (requests[i] > head)
            right.push_back(requests[i]);
    }
 
    // Sorting left and right vectors
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());
 
    // First service the requests
    // on the right side of the
    // head
    for (int i = 0; i < right.size(); i++) {
        cur_track = right[i];
 
        // Appending current track to seek sequence
        order.push_back(cur_track);
 
        // Calculate absolute distance
        distance = abs(cur_track - head);
 
        // Increase the total count
        total_head_movements += distance;
 
        // Accessed track is now new head
        head = cur_track;
    }
 
    // Once reached the right end
    // jump to the last track that
    // is needed to be serviced in
    // left direction
    total_head_movements += abs(head - left[0]);
    head = left[0];
 
    // Now service the requests again
    // which are left
    for (int i = 0; i < left.size(); i++) {
        cur_track = left[i];
 
        // Appending current track to seek sequence
        order.push_back(cur_track);
 
        // Calculate absolute distance
        distance = abs(cur_track - head);
 
        // Increase the total count
        total_head_movements += distance;
 
        // Accessed track is now the new head
        head = cur_track;
    }
 
    return {order, total_head_movements};
}