#include <bits/stdc++.h>

using namespace std;

int find_closest(vector<int>& requests,int x)
{
    vector<int> temp = requests;
    for(int i=0;i<requests.size();i++)
    {
        temp[i] = abs(x-requests[i]);
    }

    int it = min_element(temp.begin(),temp.end())-temp.begin(); 
    int val = requests[it];
    requests.erase(it+requests.begin());
    return val;  
}

pair<vector<int>,int> sstf(vector<int> requests, int head)
{

    int curr_head = head;
    int n = requests.size();

    vector<int> order;
    
    for(int i=0;i<n;i++)
    {
        int x = find_closest(requests,curr_head);
        order.push_back(x);
        curr_head = x;
    }

    int total_head_movements = 0;

    for(auto req: order) {
        total_head_movements+=abs(head - req);
        head = req;
    } 

    return {order, total_head_movements};
}