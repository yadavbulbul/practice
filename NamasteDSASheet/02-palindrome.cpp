class Solution {
public:
    bool isPalindrome(int x) {
        string s = to_string(x);
        int i=0;
        int j=s.size()-1;
        while(i<=j){
            if(s[i]!=s[j]){
                return false;
            }
            i++;
            j--;
        }
        return true;


    }
};

/*
without string


class Solution {
public:
    bool isPalindrome(int x) {
        if(x<0){
            return false;
        }
        long long res = 0;
        int num =x;
        while(num!=0){
            res=res*10 + num % 10;
            num/=10;
        }

        return res==x;
    }
};


*/