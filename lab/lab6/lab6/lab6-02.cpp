#include <iostream>
#include <algorithm>
#include <queue>
#include <unordered_map>

using namespace std;

int find(string start)
{
    // 定义目标状态
    string end = "12345678x";
}

int main()
{
    string c, start;

    for (int i = 0; i < 9; i++)
    {
        cin >> c;
        start += c;
    }

    cout << find(start) << endl;

    return 0;
}