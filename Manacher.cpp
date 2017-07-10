#include <vector>
#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

//Manacher算法求最长回文子串
//接口: string Manacher(string s)
//输入: string s
//输出: s的最长回文子串

string Manacher(string s) {
    // Insert '#'
    string t = "$#";
    for (int i = 0; i < s.size(); ++i) {
        t += s[i];
        t += "#";
    }
    // Process t
    vector<int> p(t.size(), 0);
    int mx = 0, id = 0, resLen = 0, resCenter = 0;
    for (int i = 1; i < t.size(); ++i) {
        p[i] = mx > i ? min(p[2 * id - i], mx - i) : 1;
        while (t[i + p[i]] == t[i - p[i]]) ++p[i];
        if (mx < i + p[i]) {
            mx = i + p[i];
            id = i;
        }
        if (resLen < p[i]) {
            resLen = p[i];
            resCenter = i;
        }
    }
    return s.substr((resCenter - resLen) / 2, resLen - 1);
}

//HDU 3068
int main() {
    string s;
    while (cin >> s)
    {
        string tt = Manacher(s);
        printf("%d\n", tt.size());
    }
}
