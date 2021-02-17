#include <iostream>
#include <fstream>

using namespace std;

#define MAX 5
#define CHEZ_PRICE 0.129 
#define WATER_PRICE 1.461
#define HEATING_PRICE 85.07
#define MINUTE_PRICE 0.132


double* gauss_and_divide_by_prices(double A[4][MAX], int n, double M[4]){
    int i, j, k;
    double prob;

      for (i=0; i<n; i++) {                    
        for (k=i+1; k<n; k++) {
            if (abs(A[i][i]) < abs(A[k][i]))
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

    M[0] = CHEZ_PRICE / M[0];
    M[1] = WATER_PRICE / M[1];
    M[2] = HEATING_PRICE / M[2];
    M[3] = MINUTE_PRICE / M[3];

    return M;
}

void read_file_and_sort(double A[][MAX], string file_name){ //reading file and fixing the last line
int k = 0;
int i = 0;
double number;
ifstream input = ifstream(file_name);
    if(input.is_open()){
        while(input >> number){
            if(k == 4){
                i++;
                k = 0;
                A[i][k] = number;
            }
            A[i][k] = number;
            k++;
            
            if(i == 3 && k == 4){
               break;
            }
        }
        i = 0;
        while(input >> number){
            if(i < 4){
                A[i][4] = number;
                i++;
            }
        }

        input.close();
    }else{
        cout << "Oops, can't open this file..." << endl;
        return;
    }
}

void print_matrix(double A[][MAX]){

    cout << "Printing matrix:" << endl;
    for(int i = 0; i < 4; i++){
		for(int k = 0; k < MAX; k++){
			cout << A[i][k] << " ";
		}
		cout << endl;
	}
    cout << endl;
}

void copy_matrix(double A[][MAX], double B[][MAX]){ //where to copy, what to copy
    for (int i = 0 ; i < 4; i++){
        for (int k = 0 ; k < MAX; k++){
            A[i][k] = B[i][k];
        }
    }
}

void find_real_prices(double A[][MAX]){
    int i = 0;

    for(i = 0; i < 4; i++){
        A[i][0] *= CHEZ_PRICE;
    }
    for(i = 0; i < 4; i++){
        A[i][1] *= WATER_PRICE;
    }

    for(i = 0; i < 4; i++){
        A[i][2] *= HEATING_PRICE;
    }

    for(i = 0; i < 4; i++){
        A[i][3] *= MINUTE_PRICE;
    }
    // The sum 
    for(i = 0; i < 4; i++){
        A[i][4] = A[i][0] + A[i][1] + A[i][2] + A[i][3];
    }
}

void their_prices(double A[][MAX], double *koef){
    int i = 0;

    for(i = 0; i < 4; i++){
        A[i][0] *= koef[0];
    }
    
    for(i = 0; i < 4; i++){
        A[i][1] *= koef[1];
    }

    for(i = 0; i < 4; i++){
        A[i][2] *= koef[2];
    }

    for(i = 0; i < 4; i++){
        A[i][3] *= koef[3];
    }
}


void fooler(string file_name) {
    double A[4][5] = {0}; //calc with normal prices
    double B[4][5] = {0}; //calculations with the higher price
    double C[5][4] = {0}; //final answer
    double koef[4] = {0};
    int i = 0;
    int k = 0;

    //reading the file and making the last row to column
    read_file_and_sort(A, file_name);

    //second matrix for backup with same values
    copy_matrix(B, A);
    
    //print_matrix(A);  just tests printing the matrix
    //print_matrix(B);

    // Gauss method + dividing the result of gauss to the real prices and returning new array with the result
    gauss_and_divide_by_prices(B, 4, koef); 

    // Copy the maxtrix to keep the file patern
    copy_matrix(B, A);
    
    // Calculating the real prices - ((numbers)*(normal prices))
    find_real_prices(A);

    // Setting the final matrix 
    for(i = 0; i < 4; i++){
        C[0][i] = B[i][4] - A[i][4];
    }

    // To keep the file patern
    copy_matrix(A, B);

    // Calculating the fake prices
    their_prices(B, koef);


    // Finishing the final matrix
    for(i = 1; i < 5; i++){
        for(k = 0; k < 4; k++){
            C[i][k] = A[i-1][k] - B[i-1][k]; 
        }
    }

    // The final output
    for(i = 0; i < 5; i++){
		for(k = 0; k < 4; k++){
			cout << C[i][k] << " ";
		}
		cout << endl;
	}
}


int main(int agrc, char* argv[]){
    fooler(argv[1]);

}