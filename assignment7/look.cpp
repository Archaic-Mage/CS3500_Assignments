#include <bits/stdc++.h>

using namespace std;

pair<vector<int>, int> look(vector<int> requests, int head)
{
    vector<int> above,below;

    for(int i=0;i<requests.size();i++)
    {
        if(requests[i]>head)
            above.push_back(requests[i]);
        else
            below.push_back(requests[i]);
    }
    sort(above.begin(),above.end());
    sort(below.begin(),below.end(),greater<int>());

    vector<int> order(above);
    
    int total_head_movements = 0;

    order.insert(order.end(), below.begin(), below.end());

    for(auto req: order) {
        total_head_movements+=abs(head - req);
        head = req;
    }

    return {order, total_head_movements};
    
}