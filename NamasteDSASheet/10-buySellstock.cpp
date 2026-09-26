class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int tempmin = prices[0];
        int profit=0;
        for(int i=1;i<prices.size();i++){
            profit = max(profit,prices[i]-tempmin);
            tempmin=min(tempmin,prices[i]);
        }
        return profit;
    }
};


