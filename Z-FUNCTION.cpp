#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;


std::vector<int> compute_z_function(const std::string& s) {
    int n = s.size();
    int L, R = 0;

    vector<int> Z(n, 0);
    for (int i = 1; i < n; ++i){
        if (i > R){
            L = R = i;
            while(R < n && s[R] == s[R - L]){
                ++R;
            }
            Z[i] = R - L;
            --R;
            
        }
        else{
            int k = i - L; // Симметричное значение относитель L
            if (Z[k] < R - i + 1){
                Z[i] = Z[k];
            }
            else{
                L = i;
                while(R < n && s[R] == s[R - L]){
                    ++R;
                }
                Z[i] = R - L;
                --R;
                
            }
        }

    }
    return Z;
}
int main(){
    string s = "abacaba";
    vector<int> ans = compute_z_function(s);
    for (int i = 0; i < ans.size(); ++i){
        cout << ans[i];
    }
}   