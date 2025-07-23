#include <bits/stdc++.h>
#pragma GCC target ("avx2")
#pragma GCC optimize ("O3")
#pragma GCC optimize ("unroll-loops")

using namespace std;
using ll = long long;

struct dataPoint 
{
    int originalX;
    int originalY;
    ll weight;
};

// Reading input points: crystals (positive) and mines (negative)
vector<dataPoint> readInput() 
{
    int numCrystals, numMines;
    cin >> numCrystals >> numMines;
    int totalPoints = numCrystals + numMines;
    vector<dataPoint> points;
    points.reserve(totalPoints);

    for (int i = 0; i < numCrystals; ++i) 
    {
        int x, y;
        ll value;
        cin >> x >> y >> value;
        points.push_back({x, y, value});
    }

    for (int i = 0; i < numMines; ++i) 
    {
        int x, y;
        ll penalty;
        cin >> x >> y >> penalty;
        points.push_back({x, y, -penalty});
    }

    return points;
}

// Coordinate compression for X and Y values
pair<vector<int>, vector<int>> compressCoordinates(vector<dataPoint>& points) 
{
    vector<int> xValues, yValues;
    xValues.reserve(points.size());
    yValues.reserve(points.size());

    for(auto& p: points) 
    {
        xValues.push_back(p.originalX);
        yValues.push_back(p.originalY);
    }

    sort(xValues.begin(), xValues.end());
    xValues.erase(unique(xValues.begin(), xValues.end()), xValues.end());

    sort(yValues.begin(), yValues.end());
    yValues.erase(unique(yValues.begin(), yValues.end()), yValues.end());

    return {xValues, yValues};
}

// Building the mapping from compressed X index to list of (compressed Y, weight)
vector<vector<pair<int,ll>>> groupPointsByX(vector<dataPoint>& points, vector<int>& compressedX, vector<int>& compressedY) 
{
    int xCount = compressedX.size();
    vector<vector<pair<int,ll>>> pointsByX(xCount);

    for (auto& p: points) 
    {
        int cx = lower_bound(compressedX.begin(), compressedX.end(), p.originalX) - compressedX.begin();
        int cy = lower_bound(compressedY.begin(), compressedY.end(), p.originalY) - compressedY.begin();
        pointsByX[cx].emplace_back(cy, p.weight);
    }

    return pointsByX;
}

struct Rectangle 
{
    ll bestScore;
    int leftX, rightX;
    int bottomY, topY;
};

Rectangle Kadane_2D(vector<vector<pair<int,ll>>>& pointsByX, int yCount) 
{
    ll bestScore = LLONG_MIN;
    Rectangle result{bestScore, 0, 0, 0, 0};

    vector<ll> columnSum(yCount, 0LL);

    int xCount = pointsByX.size();
    for(int left = 0; left < xCount; ++left) 
    {
        fill(columnSum.begin(), columnSum.end(), 0LL);

        for(int right = left; right < xCount; ++right) 
        {
            // accumulating weights for column 'right'
            for(auto& pr: pointsByX[right]) 
            {
                columnSum[pr.first] += pr.second;
            }

            // 1D Kadane scan on columnSum
            ll currentSum = 0;
            int tempStart = 0;
            for(int y = 0; y < yCount; ++y) 
            {
                if(currentSum <= 0) 
                {
                    currentSum = columnSum[y];
                    tempStart = y;
                } 

                else 
                {
                    currentSum += columnSum[y];
                }

                if(currentSum > result.bestScore) 
                {
                    result.bestScore = currentSum;
                    result.leftX = left;
                    result.rightX = right;
                    result.bottomY = tempStart;
                    result.topY = y;
                }
            }
        }
    }

    return result;
}

// Outputting the result: score and de-compressed rectangle corners
void outputResult(Rectangle& res, vector<int>& compressedX, vector<int>& compressedY) 
{
    cout << res.bestScore << "\n";
    cout << compressedX[res.leftX] << " " << compressedY[res.bottomY] << "\n";
    cout << compressedX[res.leftX] << " " << compressedY[res.topY]    << "\n";
    cout << compressedX[res.rightX]<< " " << compressedY[res.topY]    << "\n";
    cout << compressedX[res.rightX]<< " " << compressedY[res.bottomY]<< "\n";
}

int main() 
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    auto points = readInput();

    auto [compressedX, compressedY] = compressCoordinates(points);
    auto pointsByX = groupPointsByX(points, compressedX, compressedY);

    Rectangle bestRect = Kadane_2D(pointsByX, compressedY.size());
    outputResult(bestRect, compressedX, compressedY);
    
    return 0;
}