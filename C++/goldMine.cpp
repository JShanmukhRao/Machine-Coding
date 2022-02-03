#include<bits/stdc++.h>
using namespace std;

int helper(vector<vector<int>> v,int row,int col){
    if(row<0 || row>= v.size() || col<0 || col>=v[0].size()){
        return 0;
    }
    int right=helper(v,row,col+1);
    int digoUp=helper(v,row-1,col+1);
    int digoDown=helper(v,row+1,col+1);
    int val=max(right,max(digoUp,digoDown))+v[row][col];
    return val;
}
int main(){

    vector<vector<int>> v={{10, 33, 13, 15},
                  {22, 21, 04, 1},
                  {5, 0, 2, 3},
                  {0, 6, 14, 2}};
    int ans=0;
     
     
    for(int i=0;i<v.size();i++){
        ans=max(ans,helper(v,i,0));
       cout<<"ANSWER "<<ans<<endl;
    }
    
    

}