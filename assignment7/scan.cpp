#include <bits/stdc++.h>

using namespace std;

pair<vector<int>, int> scan(vector<int> requests, int head)
{
    vector<int> below,above;

    for(int i=0;i<requests.size();i++)
    {
        if(requests[i]<head)
        below.push_back(requests[i]);
        else
        above.push_back(requests[i]);
    }

    sort(below.begin(),below.end(),greater<int>());
    below.push_back(0);

    sort(above.begin(),above.end());

    vector<int> order(below);
    
    int total_head_movements = 0;
    
    order.insert(order.end(), above.begin(), above.end());

    for(auto req: order) {
        total_head_movements+=abs(head - req);
        head = req;
    } 
    
    return {order, total_head_movements};
}


