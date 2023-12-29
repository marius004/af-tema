#include <vector>
#include <climits>
#include <string>
#include <stack>

using namespace std;

class Solution {
public:
    string shortestSuperstring(vector<string>& words) {
        vector<vector<int>> cost(words.size(), vector<int>(words.size()));
        
        for (int i = 0;i < words.size(); ++i) {
            for (int j = i + 1;j < words.size(); ++j) {
                cost[i][j] = getCost(words[i], words[j]);
                cost[j][i] = getCost(words[j], words[i]);
            }
        }

        vector<vector<int>> dp (1 << words.size(), vector<int>(words.size()));
        vector<vector<int>> path (1 << words.size(), vector<int>(words.size()));

        int last = -1, min = INT_MAX;
        for (int state = 1; state < (1 << words.size()); ++state) {
            for (int i = 0;i < words.size();++i) {
                dp[state][i] = INT_MAX;
            }

            for (int word = 0;word < words.size();++word) {
                if (!(state & (1 << word)))  continue;
                
                int prev = state ^ (1 << word);
                if (prev == 0) { // the path contains only words[word]
                    dp[state][word] = words[word].size();
                } else {
                    for (int end = 0; end < words.size();++end) {
                        if (dp[prev][end] < INT_MAX && dp[prev][end] + cost[end][word] < dp[state][word]) {
                            dp[state][word] = dp[prev][end] + cost[end][word];
                            path[state][word] = end; 
                        }
                    }
                }

                if (state == (1 << words.size()) - 1 && dp[state][word] < min) {
                    min = dp[state][word];
                    last = word;
                }                
            }
        }

        int state = (1 << words.size()) - 1;
        stack<int> pathBuilder; 

        while (state != 0) {
            pathBuilder.push(last); 
            int oldState = state; 
            state = state ^ (1 << last); 
            last = path[oldState][last];
        }

        int prev = pathBuilder.top();
        auto result = words[prev]; 

        pathBuilder.pop();
        while (!pathBuilder.empty()) {
            int curr = pathBuilder.top();
            pathBuilder.pop(); 
            result = result + words[curr].substr(words[curr].length() - cost[prev][curr]);
            prev = curr;
        }

        return result;
    }

    int getCost (string &A, string &B) {
        for(int i = 0; i < A.size(); ++i) {
            auto substr = A.substr(i, A.size());
            if (substr.size() <= B.size() && B.substr(0, substr.size()) == substr) {
                return B.size() - substr.size();
            }
        }
        return B.size();
    }
};