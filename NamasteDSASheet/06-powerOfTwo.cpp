class Solution {
public:
    bool isPowerOfTwo(int n) {
        return n > 0 && (n & (n - 1)) == 0;
    }
};

/*
n   = 8 = 1 0 0 0
n-1 = 7 = 0 1 1 1 AND
          0 0 0 0 = 0
*/