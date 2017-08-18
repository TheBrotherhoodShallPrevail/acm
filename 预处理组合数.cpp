// 预处理组合数，C(n,m)表示从n个数中选m个数
// 复杂度O(n^2)

for (int i=0;i<=n;i++){
    for (int j=0;j<=i;j++){
        if (j==0||i==j){
            C[i][j]=1;
        }
        else{
            C[i][j]=C[i-1][j-1]+C[i-1][j];
        }
    }
}