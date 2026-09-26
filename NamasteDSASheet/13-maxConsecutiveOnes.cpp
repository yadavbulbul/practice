class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int maxi = 0;
        int counter = 0;
        for(int i=0;i<nums.size();i++){
            if(nums[i]==1){
                counter++;
            }
            else{
                maxi=max(maxi,counter);
                counter=0;
            }
        }
        maxi=max(maxi,counter);
        return maxi;
    }
};

