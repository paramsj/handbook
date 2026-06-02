/**
 * Author: Simon Lindholm
 * Date: 2016-10-08
 * License: CC0
 * Source: me
 * Description: Matrix Exponentiation
 * Time: 
 * Usage:
 * Status: stress-tested a bit
 */


const int N = 105;
struct Matrix {
    int mat[N][N];
};

Matrix matMul(Matrix a,Matrix b) {
    Matrix ans = {0};

    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            for(int k=0;k<N;k++) {
                ans.mat[i][j] = (ans.mat[i][j] + (a.mat[i][k]*b.mat[k][j])%MOD)%MOD;
            }
        }
    }
    return ans;
}

Matrix matPow(Matrix a,int b,int MOD) {
    Matrix res = {0};

    for(int i=0;i<N;i++) {
        res.mat[i][i] = 1;
    }

    while(b) {
        if(b%2) {
            res = matMul(res,a);
        }
        b = b/2;
        a = matMul(a,a);
    }

    return res;
}

void solve() {
    int n,m,k;
    cin>>n>>m>>k;

    Matrix a = {0};
    for(int i=0;i<m;i++) {
        int x,y,w;
        cin>>x>>y>>w;
        x--;
        y--;

        a.mat[x][y] = w;
    }

    Matrix res = matPow(a,k,MOD);
    cout<<res.mat[0][n-1]<<endl;
}