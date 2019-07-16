#include <stdio.h>
#include <stdlib.h>

// Declare printSudoku function
void printSudoku(int***);
// Declare solveSudoku function
/*  
int solveSudoku(int***);
int column(int***,int,int,int);
int row(int***, int, int, int);
int square(int***, int, int );
int StillZero(int***);
int legal(int***, int, int, int, int);
*/
//Helper functions. You can define any functions that can help your solve the problem

int column (int *** blocks, int b, int c, int num){

    if(b%3 == 0){  // b is block statement, so it keeps track of which block we are in.
        b=0;   //look at it as a nieghborhood divided by walls, this is neighborhood of 0 it has three people [0,3,6]
    }
    else if ( b%3 == 1){
        b=1;       //this is in hood 1, right in the middle of both 0 and 2, it is hood of 1 with people [1,4,7]
    }
    else{
        b=2;   //2 is the last hood, the last three boxes from hood 2, people [2,5,8]
    }

    for( b; b<9; b+=3){ //b is our blocksection we 
        for( int r =0; r<3; r++){ //r is row, in a sense it really just tells hey which column you want to check
            if(  *(*(*(blocks+ b)+r)+c)   == num  ){ //c doesnt change for a resaon that it should always be 0
                return 1;  // in array notation blocks[b][r][c]  b tells neighborhood, r tells which column to check, c stays zero so column isnt going to switch
            } 
        }
    }

    return 0;
}

int row (int *** blocks, int b, int r, int num){
   if (b<3){
       b=0;
for( int i=b; i<3; i++){ // i is b to tell neighborhood
         for(int j =0; j<3; j++) {
                 if(   *(*(*(blocks+i)+r)+j)  == num  ){   
                 return 1;
                                                }

    
                                }
                            }

   }
     else if(b>=3 && b<6){
       b=3;
     for( int i=b; i<6; i++){ // i is b to tell neighborhood
         for(int j =0; j<3; j++) {
                 if(   *(*(*(blocks+i)+r)+j)  == num  ){   
                 return 1;
                                                }
                                }
                            }
                        }    

   else if (b>=6 && b<9){
       b=6;
         for( int i=b; i<9; i++){ // i is b to tell neighborhood
            for(int j =0; j<3; j++) {
                if(   *(*(*(blocks+i)+r)+j)  == num  ){   
                            return 1;
                                                } 
                                    }
                                }
                        }
return 0;
}




int square(int *** blocks, int b, int num){

    for(int r = 0; r< 3; r++){
        for(int c = 0; c<3; c++){
            if(  *(*(*(blocks+b)+r)+c) == num  ){
                return 1;
            }

        }
    }
return 0;
}


int StillZero(int*** blocks){
    int a =0, b=0, c =0, d=0;
   
    for(a=0; a<9; a++){
        for(b=0; b<3; b++){
            for(c=0; c<3; c++){

                d = *(*(*(blocks+a)+b)+c);
                if(d == 0){
                    return 0;
                }

            }
        }
    }
    return 1;
}


int legal(int ***blocks, int b, int r, int c, int num){

    if(!column(blocks, b, c, num) && !row(blocks, b, r,num) && !square(blocks, b, num)   ){
        return 1;
    }
   else{
       return 0;
   }
    }
    









/*
The main program reads a text file containing the block values of the Sudoku grid.
It then saves each 3x3 block into a 2D array. The Sudoku grid is composed of 9 3x3 blocks.
DO NOT MODIFY THE MAIN FUNTION!!!
*/
int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <file name>\n", argv[0]);
		return 2;
	}
    int i, j;
    FILE *fptr;
    int ***blocks = (int***)malloc(9 * sizeof(int**));

    // Open file for reading
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open File!\n");
        return 0;
    }

	// Read 9x9 blocks into 2D arrays
    for(i=0; i<9; i++)
    {
        *(blocks+i) = (int**)malloc(3 * sizeof(int*));
        printf("Reading numbers in block %d... \n", i+1);
        for(j=0; j<3; j++)
        {
            *(*(blocks+i)+j) = (int*)malloc(3 * sizeof(int));

                fscanf(fptr, "%d %d %d", *(*(blocks+i)+j), *(*(blocks+i)+j)+1, *(*(blocks+i)+j)+2);
                printf("%d %d %d\n", *(*(*(blocks+i)+j)), *(*(*(blocks+i)+j)+1), *(*(*(blocks+i)+j)+2));
        }
    }
	
	// Print out original Sudoku grid
    printf("Printing Sudoku before being solved:\n");
    printSudoku(blocks);

	// Call solveSudoku and print out result
    printf("\nSolving Sudoku...\n\n");
    if(solveSudoku(blocks)){
        printf("Sudoku solved!\n");
        printSudoku(blocks);
    }
    else
        printf("This Sudoku cannot be solved!\n");

    return 0;
}


void printSudoku(int*** arr){
	// This function will print out the complete Sudoku grid (arr). It must produce the output in the SAME format as the samples in the instructions. 	
	int i =0, j = 0;
    for(i =0; i < 9; i++){

        for(j=0; j<3; j++){ 
           // printf("meme");
          //  printf("%d %d %d\n", *(*(*(arr+i)+j)), *(*(*(arr+i)+j)+1), *(*(*(arr+i)+j)+2));

    printf("%d %d %d |" , *(*(*(arr+i)+j)), *(*(*(arr+i)+j)+1), *(*(*(arr+i)+j)+2)); 
            printf("%d %d %d |" , *(*(*(arr+i+1)+j)), *(*(*(arr+i+1)+j)+1), *(*(*(arr+i+1)+j)+2));
            printf("%d %d %d |\n", *(*(*(arr+i+2)+j)), *(*(*(arr +i+2)+j)+1), *(*(*(arr +i+2)+j)+2));


        }
        printf("---------------------\n");

  i = i+ 2;
    }


	// Your implementation here
    printf("\n");
	
}
int solveSudoku(int*** blocks){
	// This is the function to solve the Sudoku (blocks). Feel free to use any helper functions.
	// YOU MUST NOT USE ANY ARRAY NOTATION ([])!
	
	//Your implementation here
//Solve(blocks, 0,0,0);

  //  printf("%d", column(blocks,8,2,8));
   //printf("%d\n", row(blocks,3,0,4));
   // printf("%d", *(*(*(blocks+3)+0)+9));
   //printf("%d", square(blocks,8,7));

	

if(StillZero(blocks)){
    return 1;
}

    for(int sq =0; sq <9; sq++){
        for(int r=0; r<3; r++){
            for(int c=0; c<3; c++){
                if( *(*(*(blocks+sq)+r)+c) == 0 ){

                    for(int num =1; num<=9; num++){
                     

                if(legal(blocks, sq, r,c,num)){
                    *(*(*(blocks+sq)+r)+c) =num;
                    if(solveSudoku(blocks)){
                        return 1;
                    }
                }
                
                }
                *(*(*(blocks+sq)+r)+c)=0;
                return 0;
                }
            }
        }
    }
        
    return 1;

	
}
