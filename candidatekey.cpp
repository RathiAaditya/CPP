#include <bits/stdc++.h>
#define pb push_back
using namespace std;
map<char, bool> m;
map<char, bool> m1;
string s; // enter the attributes
unordered_set<string> st;
vector<string> ans;
vector<string> candidate;
vector<string> attribute;
string presentrhs;
string essential;
string nonprime;
bool compare(string &s1, string &s2)
{
    return s1.size() < s2.size();
}
string unique(string str)
{
    sort(str.begin(), str.end());
    str.erase(std::unique(str.begin(), str.end()), str.end());
    return str;
}
class CandidateKey
{
private:
    vector<string> lhs;
    vector<string> rhs;
    int numberOfElements;

public:
    CandidateKey(int x)
    {
        numberOfElements = x;
    }
    void setlhs(string s)
    {
        lhs.pb(s);
    }
    void setrhs(string s)
    {
        rhs.pb(s);
    }
    void rhsconcat()
    {
        string x = "";
        for (auto i : rhs)
        {
            x += i;
        }
        x = unique(x);
        presentrhs = x;
    }
    string comparewith(string left, string right)
    {
        string p = "";
        int m = left.length();
        int n = right.length();
        int i = 0, j = 0;
        while (i < m && j < n)
        {
            if (left[i] == right[j])
            {
                p = p + left[i];
                i++, j++;
            }
            else if (left[i] < right[j])
            {
                i++;
            }
            else
                j++;
        }
        // cout << p << endl;
        return p;
    }
    bool is2NF()
    {
        bool var = true;
        for (int i = 0; i < lhs.size(); i++)
        {
            for (auto j : candidate)
            {
                if (j != lhs[i] && check(j, lhs[i]))
                {
                    if (!checkempty(nonprime, rhs[i]))
                        return false;
                }
            }
        }
        return true;
    }
    bool checkempty(string s, string t)
    {
        string p = "";
        int m = s.length();
        int n = t.length();
        int i = 0, j = 0;
        while (i < m && j < n)
        {
            if (s[i] == t[j])
            {
                p = p + s[i];
                i++, j++;
            }
            else if (s[i] < t[j])
            {
                i++;
            }
            else
                j++;
        }
        return p.empty();
    }
    bool check(string s, string t)
    {
        string p = "";
        int m = s.length();
        int n = t.length();
        int i = 0, j = 0;
        while (i < m && j < n)
        {
            if (s[i] == t[j])
            {
                p = p + s[i];
                i++, j++;
            }
            else if (s[i] < t[j])
            {
                i++;
            }
            else
                j++;
        }
        return t == p;
    }
    string find(string presentrhs, string s)
    {
        string p = "";
        int m = presentrhs.length();
        int n = s.length();
        int i = 0, j = 0;
        while (i < m && j < n)
        {
            if (presentrhs[i] == s[j])
                i++, j++;
            else
            {
                p = p + s[j];
                j++;
            }
        }
        while (j < n)
        {
            p = p + s[j];
            j++;
        }
        return p;
    }
    void run()
    {
        for (auto i : essential)
        {
            m[i] = true;
        }
    }
    bool runit(string str)
    {
        for (auto i : s)
            cout << m1[i] << endl;
        for (auto i : str)
        {
            m1[i] = true;
        }
        string prev = str;
        string current = "";
        while (prev != current)
        {
            current = "";
            for (int i = 0; i < numberOfElements; i++)
            {
                bool var = true;
                for (auto j : lhs[i])
                {
                    var = var * m1[j];
                }
                if (var == true)
                {
                    for (auto l : rhs[i])
                    {
                        m1[l] = true;
                    }
                }
            }
            for (auto i : lhs)
            {
                for (auto j : i)
                    if (m1[j])
                        current += j;
            }
            for (auto i : rhs)
            {
                for (auto j : i)
                    if (m1[j])
                        current += j;
            }
            current = unique(current);
            // cout << current << endl;
            if (current == s or prev == current)
            {
                for (auto i : s)
                    m1[i] = false;
                break;
            }
            prev = current;
            current = "";
        }
        for (auto i : s)
            m[i] = false;
        if (s == current)
        {
            cout << "OM" << endl;
            return true;
        }
        else
        {
            cout << "Ded" << endl;
            return false;
        }
        // cout << current << endl;
    }
    void runloop(string str)
    {
        string temp = comparewith(str, essential);

        if (temp != essential)
            return;
        // for (auto i : s)
        //     cout << m[i] << endl;
        for (auto i : str)
        {
            m[i] = true;
        }
        string prev = unique(str + essential);
        string current = essential;
        while (true)
        {
            current = prev;
            for (int i = 0; i < numberOfElements; i++)
            {
                bool var = true;
                for (auto j : lhs[i])
                {
                    var = var * m[j];
                }
                if (var == true)
                {
                    for (auto l : rhs[i])
                    {
                        m[l] = true;
                    }
                }
            }
            for (auto i : lhs)
            {
                for (auto j : i)
                    if (m[j])
                        current += j;
            }
            for (auto i : rhs)
            {
                for (auto j : i)
                    if (m[j])
                        current += j;
            }
            current = unique(current);
            // cout << str << " " << current << endl;
            if (current == s or prev == current)
            {
                if (s == current)
                    ans.pb(str);
                for (auto i : s)
                    m[i] = false;
                return;
            }

            prev = current;

            // for (auto i : s)
            //     m[i] = false;
            // cout << current << endl;
        }
    }
    void printSubsequence(string input, string output)
    {
        if (input.empty())
        {
            runloop(output);
        }
        printSubsequence(input.substr(1), output + input[0]);
        printSubsequence(input.substr(1), output);
    }
};
string getString(char x)
{
    string s(1, x);
    return s;
}
void subsequence(string str)
{

    // Iterate over the entire string
    for (int i = 0; i < str.length(); i++)
    {

        // Iterate from the end of the string
        // to generate substrings
        for (int j = str.length(); j > i; j--)
        {
            string sub_str = str.substr(i, j);
            st.insert(sub_str);

            // Drop kth character in the substring
            // and if its not in the set then recur
            for (int k = 1; k < sub_str.length(); k++)
            {
                string sb = sub_str;

                // Drop character from the string
                sb.erase(sb.begin() + k);
                subsequence(sb);
            }
        }
    }
}

int main()
{

    cin >> s;
    s = unique(s);
    for (auto i : s)
        attribute.pb(getString(i));
    // for (auto i : s)
    //     cout << i << " ";
    int n;
    cin >> n;

    // Number of functional dependencies
    CandidateKey ck(n);

    while (n--)
    {
        string left;
        cin >> left;
        left = unique(left);
        // cout << left << endl;
        string right;
        cin >> right;
        right = unique(right);
        ck.setlhs(left);
        ck.setrhs(right);
    }
    ck.rhsconcat();
    essential = ck.find(presentrhs, s);
    // for (auto i : essential)
    //     cout << i << endl;

    nonprime = ck.find(essential, s);
    // for (auto i : nonprime)
    //     cout << i << endl;
    // ck.run();
    subsequence(s);
    /*
    for (auto i : st)
        cout << i << endl;
        */
    for (auto i : st)
        ck.runloop(i);
    sort(ans.begin(), ans.end(), compare);
    cout << "Ans" << endl;
    for (auto i : ans)
        cout << i << endl;
    string temp;

    candidate.pb(ans[0]);
    for (int i = 1; i < ans.size(); i++)
    {
        bool var = false;
        for (auto j : candidate)
        {
            var = var or ck.check(ans[i], j);
            // cout<<var<<endl;
        }
        if (!var)
        {
            candidate.pb(ans[i]);
            // cout<<ans[i]<<" Adding this"<<endl;
        }
    }
    // cout << ck.check("BCDEF", "CD") << endl;
    // cout << ans.size() << endl;
    // cout << store << endl;
    // for (int i = 1; i < ans.size(); i++)
    // {
    //     temp = ck.comparewith(store, ans[i]);
    //     if (temp.empty())
    //     {
    //         candidate.pb(store);
    //         store = ans[i];
    //     }
    //     else
    //     {
    //         store = temp;
    //     }
    // }
    // candidate.pb(temp);
    // ck.runit("B");
    cout << "Candid" << endl;
    for (auto i : candidate)
        cout << i << endl;

    /*ck.generateStrings(s);
      ck.runloop();
      cout << nonprime << endl;
      cout << essential << endl;
     */
    return 0;
}
//  sort(ans.begin(), ans.end());

//     if (ans.size() == 1 or ans.size() == 2)
//         for (auto i : ans)
//         {
//             cout << i << endl;
//             return 0;
//         }
// while (i < ans.size() && j < ans.size())
//     {
//         string e = ans[i];
//         string f = ans[j];
//         string d = comparewith(ans[i], ans[j]);
//         if (e.length() < f.length())
//         {
//             if (d == e.length())
//             {
//                 j++;
//             }
//         }
//         if (e.length() > f.length())
//         {
//             if (d == f.length())
//             {
//                 i = j;
//                 j++;
//             }
//         }
//         if (e.length() == f.length())
//         {
//             if (d.empty())
//             {
//                 candidate.pb(ans[i]);
//                 candidate.pb(ans[j]);
//                 i = j;
//                 j++;
//             }
//             else if (runit(d))
//             {
//                 candidate.pb(d);
//                 j = i;
//                 j++;
//             }
//         }
//     }
