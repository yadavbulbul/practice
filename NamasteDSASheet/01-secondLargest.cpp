class Solution {
public:
    int secondHighest(string s) {
        int largest=-1;
        int secondLargest=-1;
        for(char c:s){
            if(isdigit(c) && c-'0'>largest){
                secondLargest=largest;
                largest=c-'0';
            }else if(isdigit(c) && c-'0'<largest && c-'0'>secondLargest){
                secondLargest=c-'0';
            }
        }
        return secondLargest;
    }
};