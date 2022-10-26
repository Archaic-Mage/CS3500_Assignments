#include <bits/stdc++.h>

using namespace std;

// pair<vector<int>, int> cScan(vector<int> requests, int head, int no_of_cylinders)
// {
//     vector<int> above,below;
//     for(int i=0;i<requests.size();i++)
//     {
//         if(requests[i]>head)
//         above.push_back(requests[i]);
//         else
//         below.push_back(requests[i]);
//     }
//     sort(above.begin(),above.end());
//     above.push_back(no_of_cylinders-1);
//     below.insert(below.begin(),0);
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

pair<vector<int>, int> cScan(vector<int> requests, int head, int no_of_cylinders)
{
    int total_head_movements = 0;
    int distance, cur_track;
    vector<int> left, right;
    vector<int> order;
 
    // appending end values
    // which has to be visited
    // before reversing the direction
    left.push_back(0);
    right.push_back(no_of_cylinders - 1);
 
    // tracks on the left of the
    // head will be serviced when
    // once the head comes back
    // to the beginning (left end).
    for (int i = 0; i < requests.size(); i++) {
        if (requests[i] <= head)
            left.push_back(requests[i]);
        if (requests[i] > head)
            right.push_back(requests[i]);
    }
 
    // sorting left and right vectors
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());
 
    // first service the requests
    // on the right side of the
    // head.
    for (int i = 0; i < right.size(); i++) {
        cur_track = right[i];
        // appending current track to seek sequence
        order.push_back(cur_track);
 
        // calculate absolute distance
        distance = abs(cur_track - head);
 
        // increase the total count
        total_head_movements += distance;
 
        // accessed track is now new head
        head = cur_track;
    }
 
    // once reached the right end
    // jump to the beginning.
    head = 0;
 
    // adding seek count for head returning from 199 to 0
    total_head_movements += (no_of_cylinders - 1);
 
    // Now service the requests again
    // which are left.
    for (int i = 0; i < left.size(); i++) {
        cur_track = left[i];
 
        // appending current track to seek sequence
        order.push_back(cur_track);
 
        // calculate absolute distance
        distance = abs(cur_track - head);
 
        // increase the total count
        total_head_movements += distance;
 
        // accessed track is now the new head
        head = cur_track;
    }
 
    return {order, total_head_movements};
}
