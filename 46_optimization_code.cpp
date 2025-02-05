 #include<bits/stdc++.h>
using namespace std;

int main()
  {
    freopen("input09.txt", "r", stdin);
    freopen("46_optimization_output[09]", "w", stdout);
    long long x_min = INT_MAX, x_max = INT_MIN, y_min = INT_MAX, y_max = INT_MIN;
    int n;
    cin >> n;
    vector<vector<long long>> crystals;
    long long max_crys_pt = LLONG_MIN;
    long long max_crys_pt_x, max_crys_pt_y;
    for(int i = 1;i <= n;i++)
      {
        long long x, y, c;
        cin >> x >> y >> c;
        if(c > max_crys_pt)
          {
            max_crys_pt = c;
            max_crys_pt_x = x;
            max_crys_pt_y = y;
          }
        x_max = max(x_max, x);
        x_min = min(x_min, x);
        y_max = max(y_max, y);
        y_min = min(y_min, y);
        crystals.push_back({x, y, c});
      }
    x_max = min(x_max, 10000LL);
    x_min = max(x_min, 0LL);
    y_max = min(y_max, 10000LL);
    y_min = max(y_min, 0LL);
    if(x_max < 10000)
      x_max++;
    if(x_min > 0)
      x_min--;
    if(y_max < 10000)
      y_max++;
    if(y_min > 0)
      y_min--;
    int m;
    cin >> m;
    vector<vector<long long>> voids;
    for(int i = 1;i <= m;i++)
      {
        long long x, y, c_;
        cin >> x >> y >> c_;
        voids.push_back({x, y, c_});
      }
    
    //Points
    pair<long long, long long> p1 = {x_min, y_min};
    pair<long long, long long> p2 = {x_min, y_max};
    pair<long long, long long> p3 = {x_max, y_max};
    pair<long long, long long> p4 = {x_max, y_min};

    long long score = 0;
    for(int i = 0;i < n;i++)
      {
        long long x, y, c;
        x = crystals[i][0];
        y = crystals[i][1];
        c = crystals[i][2];
        if(x_min < x && x < x_max && y_min < y && y < y_max)
          score += c;
      }

    for(int i = 0;i < m;i++)
      {
        long long x, y, c_;
        x = voids[i][0];
        y = voids[i][1];
        c_ = voids[i][2];
        if(x_min < x && x < x_max && y_min < y && y < y_max)
          score -= c_;
      }

    if(score < 0)
      {
        score = max_crys_pt;
        p1 = {max_crys_pt_x - 1, max_crys_pt_y - 1};
        p2 = {max_crys_pt_x - 1, max_crys_pt_y + 1};
        p3 = {max_crys_pt_x + 1, max_crys_pt_y + 1};
        p4 = {max_crys_pt_x + 1, max_crys_pt_y - 1};
      }

    cout << score << "\n";
    cout << "4, 4\n";
    //Edges
    cout << "(" << p1.first << ", " << p1.second << "), " << "(" << p2.first << ", " << p2.second << ")\n";
    cout << "(" << p2.first << ", " << p2.second << "), " << "(" << p3.first << ", " << p3.second << ")\n";
    cout << "(" << p3.first << ", " << p3.second << "), " << "(" << p4.first << ", " << p4.second << ")\n";
    cout << "(" << p4.first << ", " << p4.second << "), " << "(" << p1.first << ", " << p1.second << ")\n";
  }