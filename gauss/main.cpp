#include <iostream>

using namespace std;

const int N = 50;

void simpleGauss(double A[][N], int n){

    double M[N] = {0};
    int i, j, k;
    double prob;

      for (i=0; i<n; i++) {                    
        for (k=i+1; k<n; k++) {
            if (A[i][i] < A[k][i])
                for (j=0; j<=n; j++){
                    prob = A[i][j];
                    A[i][j] = A[k][j];
                    A[k][j] = prob;
                }
        }    
      } 


    for (i=0; i<n-1; i++) {            
        for (k=i+1; k<n; k++) {
                prob = -(A[k][i]/A[i][i]);
                for (j=0; j<=n; j++){
                    A[k][j] += prob*A[i][j]; 
                }   
            }
    } 
    
    for (i=n-1; i>=0; i--) {                        
        M[i] = A[i][n];                
        for (j=i+1; j<n; j++) {
            if (j != i) {                                              
                M[i] -= A[i][j] * M[j];
            }
        }
        M[i] = M[i]/A[i][i];            
    }

    cout << "Printing the answers: " << endl;
    for(int p = 0; p < n; p++) {
        cout << "x"<< p+1 << " = " << M[p] << " " << endl;
    }

}




int main(){
    int n = 0;
    cin >> n;
    double A[N][N];
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n+1; ++j){
            cin >> A[i][j];
        }
    }


    simpleGauss(A, n);

}