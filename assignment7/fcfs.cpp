#include <bits/stdc++.h>

using namespace std;

pair<vector<int>, int> fcfs(vector<int> requests, int head) {
    int total_head_movements = 0;
    vector<int> order;

    for(auto req: requests) {
        order.push_back(req);
        total_head_movements+=abs(head - req);
        head = req;
    }

    return {order, total_head_movements};
}