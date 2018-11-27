#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <windows.h>

/* Solution: The value substituted is an incrementing value
             which means it's starts from 1 then continues.

             If the value is less than or equal to 9, therefore
             the value is assigned.

             If  the value substituted exceeded 9, then
             backtrack will happen. The current index( i/row, j/col)
             will be equate to 0 and goes back to the previous index.
             The program will find another value satisfying the condition
             except the current value.

             If no value could be found, then it is assigned to 0 and goes
             back to the previous cell and repeat step until they find a
             cell that can be change into a different value

             Once the second possible value is found, it is assigned and goes
             to the next cell and continues incrementing value starting from 1.

*/
using namespace std;
int backtrack_count;
int backup_num[9][9];
double timedelay;
char display_per_move;
ofstream answer("answers.txt");
ofstream puzzle("puzzle.txt");

void display(int matrix[][9]){
    int i=0,j=0;
    cout<<endl;
    cout<<"    "<<char(218)<<"--------"<<char(194)<<"--------"<<char(194)<<"--------"<<char(191);
    cout<<endl;

    for(int i=0; i<9 ; i++){
        cout<<"   ";
        for(int j=0; j<9 ; j++){
            if(j==0){cout<<" "<<char(179)<<" ";}
            if(matrix[i][j]==0){cout<<char(176)<<" ";}
            else{ cout<<matrix[i][j]<<" ";}
            if((j+1)%3==0){cout<<" "<<char(179)<<" ";}
        }
        cout<<endl;
        if((i+1)%3==0){
                cout<<"    "<<char(195)<<"--------"<<char(197)<<"--------"<<char(197)<<"--------"<<char(180);
                cout<<endl;
        }
    }
}
void display_txt(int matrix[][9]){
    int i=0,j=0;

    answer<<endl;
    answer<<"    "<<char(218)<<"--------"<<char(194)<<"--------"<<char(194)<<"--------"<<char(191);
    answer<<endl;

    for(int i=0; i<9 ; i++){
        answer<<"   ";
        for(int j=0; j<9 ; j++){
            if(j==0){answer<<" "<<char(179)<<" ";}
            if(matrix[i][j]==0){answer<<char(176)<<" ";}
            else{ answer<<matrix[i][j]<<" ";}
            if((j+1)%3==0){answer<<" "<<char(179)<<" ";}
        }
        answer<<endl;
        if((i+1)%3==0){
                answer<<"    "<<char(195)<<"--------"<<char(197)<<"--------"<<char(197)<<"--------"<<char(180);
               answer<<endl;
        }
    }
}
void display_txt_Puzzle(int matrix[][9]){
    int i=0,j=0;

    puzzle<<endl;
    puzzle<<"    "<<"+"<<"--------"<<"+"<<"--------"<<"+"<<"--------"<<"+";
    puzzle<<endl;

    for(int i=0; i<9 ; i++){
        puzzle<<"   ";
        for(int j=0; j<9 ; j++){
            if(j==0){puzzle<<" "<<"|"<<" ";}
            if(matrix[i][j]==0){puzzle<<"x"<<" ";}
            else{ puzzle<<matrix[i][j]<<" ";}
            if((j+1)%3==0){puzzle<<" "<<"|"<<" ";}
        }
        puzzle<<endl;
        if((i+1)%3==0){
                puzzle<<"    "<<"+"<<"--------"<<"+"<<"--------"<<"+"<<"--------"<<"+";
               puzzle<<endl;
        }
    }
}
void display_game(int game[][9]){
    int i=0,j=0;
    cout<<endl;
    cout<<"    "<<char(218)<<"--------"<<char(194)<<"--------"<<char(194)<<"--------"<<char(191);
    cout<<endl;

    for(int i=0; i<9 ; i++){
        cout<<"   ";
        for(int j=0; j<9 ; j++){
            if(j==0){cout<<" "<<char(179)<<" ";}
            if(game[i][j]==0){cout<<char(176)<<" ";}
            else{ cout<<game[i][j]<<" ";}
            if((j+1)%3==0){cout<<" "<<char(179)<<" ";}
        }
        cout<<endl;
        if((i+1)%3==0){
                cout<<"    "<<char(195)<<"--------"<<char(197)<<"--------"<<char(197)<<"--------"<<char(180);
                cout<<endl;
        }
    }
}
void randomizer(int matrix[][9]){
    int row=0, col=0;

    for(int counter=1; counter<=9; counter++){
    int rand_col=rand()%9+0, rand_row=rand()%9+0;
    matrix[rand_row][rand_col]=counter;
    }
}
void backup(int matrix[][9], int game[][9]){
    for(int oucounter=0; oucounter<9; oucounter++){
        for(int incounter=0; incounter<9; incounter++){
            game[oucounter][incounter]=matrix[oucounter][incounter];
        }
    }
}
void remover(int game[][9], int difficulty){

    int rand_col=0, rand_row=0;

    for(int counter=1; counter<=difficulty;){
            rand_col=rand()%9+0;
            rand_row=rand()%9+0;
        if(game[rand_row][rand_col]!=0){
            game[rand_row][rand_col]=0;
            counter++;
            }
    }
}
bool availability(int matrix[][9], int row, int col, int num){
    int row_set =(row/3)*3,
        col_set =(col/3)*3,
        i, j;

    for(i=0; i<9; ++i)
    {
        if (matrix[row][i]==num) return false; //checks if the selected value is the same with all num in same row
        if (matrix[i][col]==num) return false;//checks if the selected value is the same with all num in same col
        if (matrix[row_set+(i%3)][col_set+(i/3)]==num) return false;//checks if the selected value is the same with all num in same set

        /*  i=0 , i%3=0 , i/3=0  , Row=0 , Col=0
            i=1 , i%3=1 , i/3=0  , Row=1 , Col=0
            i=2 , i%3=2 , i/3=0  , Row=2 , Col=0
            i=3 , i%3=0 , i/3=1  , Row=0 , Col=1
            i=4 , i%3=1 , i/3=1  , Row=1 , Col=1
            i=5 , i%3=2 , i/3=1  , Row=2 , Col=1
            i=6 , i%3=0 , i/3=2  , Row=0 , Col=2
            i=7 , i%3=1 , i/3=2  , Row=1 , Col=2
            i=8 , i%3=2 , i/3=2  , Row=2 , Col=2
        */

    }
    return true;
}
bool solve(int matrix[][9], int row, int col){
    int i;

    if(row<9&&col<9){
        if(matrix[row][col] != 0){
            if((col+1)<9) {return solve(matrix, row, col+1);}
            else if((row+1)<9){ return solve(matrix, row+1, 0);}
            else {return true;}
        }
        else{ // if cell is equal to 0
            for(i=0; i<9; i++){

                if(availability(matrix,row,col,i+1))//checks the value available
                {
                    //if value is available, it is assigned
                    matrix[row][col] = i+1;
                        //optional start
                    if(display_per_move=='y'){
                    display(matrix); Sleep(timedelay);
                    system("cls");
                    }
                        //optional end
                    if((col+1)<9){
                        if(solve(matrix,row,col+1)) {return true;}
                        else {matrix[row][col]=0;backtrack_count++;}    //backtrack for column
                    }
                    else if((row+1)<9){
                        if(solve(matrix,row+1,0)) return true;
                        else {matrix[row][col]=0;backtrack_count++;}    //backtrack for row
                    }
                    else {return true;}
                }
            }
        }
        //if the first cell cannot be assigned to any value, it is impossible
        return false; //arrive here if impossible to solve
    }
    else return true; //only arrives here if the last cell was completed
}
int main(){
    system("color 0a");

   /* int matrix[9][9]={{0, 0, 0, 0, 0, 0, 0, 9, 0},
                      {1, 9, 0, 4, 7, 0, 6, 0, 8},
                      {0, 5, 2, 8, 1, 9, 4, 0, 7},
                      {2, 0, 0, 0, 4, 8, 0, 0, 0},
                      {0, 0, 9, 0, 0, 0, 5, 0, 0},
                      {0, 0, 0, 7, 5, 0, 0, 0, 9},
                      {9, 0, 7, 3, 6, 4, 1, 8, 0},
                      {5, 0, 6, 0, 8, 1, 0, 7, 4},
                      {0, 8, 0, 0, 0, 0, 0, 0, 0}};*/
    /*int matrix[9][9]={
		1,0,0,	0,0,7,	0,9,0,
		0,3,0,	0,2,0,	0,0,8,
		0,0,9,	6,0,0,	5,0,0,

		0,0,5,	3,0,0,	9,0,0,
		0,1,0,	0,8,0,	0,0,2,
		6,0,0,	0,0,4,	0,0,0,

		3,0,0,	0,0,0,	0,1,0,
		0,4,0,	0,0,0,	0,0,7,
		0,0,7,	0,0,0,	3,0,0,
	};*/
	/*int matrix[9][9]={
		8,0,0,	0,0,0,	0,0,0,
		0,0,3,	6,0,0,	0,0,0,
		0,7,0,	0,9,0,	2,0,0,

		0,5,0,	0,0,7,	0,0,0,
		0,0,0,	0,4,5,	7,0,0,
		0,0,0,	1,0,0,	0,3,0,

		0,0,1,	0,0,0,	0,6,8,
		0,0,8,	5,0,0,	0,1,0,
		0,9,0,	0,0,0,	4,0,0,
	};*/

int matrix[9][9]={
		0,0,0,	0,0,0,	0,0,0,
		0,0,0,	0,0,0,	0,0,0,
		0,0,0,	0,0,0,	0,0,0,

		0,0,0,	0,0,0,	0,0,0,
		0,0,0,	0,0,0,	0,0,0,
		0,0,0,	0,0,0,	0,0,0,

		0,0,0,	0,0,0,	0,0,0,
		0,0,0,	0,0,0,	0,0,0,
		0,0,0,	0,0,0,	0,0,0,
	};
	int game[9][9]={
		0,0,0,	0,0,0,	0,0,0,
		0,0,0,	0,0,0,	0,0,0,
		0,0,0,	0,0,0,	0,0,0,

		0,0,0,	0,0,0,	0,0,0,
		0,0,0,	0,0,0,	0,0,0,
		0,0,0,	0,0,0,	0,0,0,

		0,0,0,	0,0,0,	0,0,0,
		0,0,0,	0,0,0,	0,0,0,
		0,0,0,	0,0,0,	0,0,0,
	};;
	/*int matrix[9][9]={
		0,7,0,	0,0,6,	0,0,0,
		9,0,0,	0,0,0,	0,4,1,
		0,0,8,	0,0,9,	0,5,0,

		0,9,0,	0,0,7,	0,0,2,
		0,0,3,	0,0,0,	8,0,0,
		4,0,0,	8,0,0,	0,1,0,

		0,8,0,	3,0,0,	9,0,0,
		1,6,0,	0,0,0,	0,0,7,
		0,0,0,	5,0,0,	8,0,0,
	};*/


    srand(time(0));


	randomizer(matrix);
	display(matrix);
	cout<<endl<<"Do you want to display per move(Y/N): ";
	cin>>display_per_move;
    display_per_move=tolower(display_per_move);
	if(display_per_move == 'y'){
        cout<<endl<<"Specifiy Time Delay(ms): ";
        cin>>timedelay;
	}

	clock_t START, END;
	START=clock();


    //for(int i, int<10, i++){

    if(solve(matrix, 0, 0))
    {
        cout<<"\a";
        display(matrix);
        display_txt(matrix);


    }

    else {
        cout<<"No Solution"<<endl;
//        i=11;
    }
    backup(matrix, game);

//}
    END=clock();
    cout<<"No. of backtrack: "<<backtrack_count<<endl;
    cout<<"Time taken: "<<double(END-START)/double(CLOCKS_PER_SEC)*1000<<" ms"<<endl;
    cout<<endl;
    system("pause");
    int difficulty;
cout<<"Enter # of blank space: ";
cin>>difficulty;
system("cls");
    remover(game, difficulty);
    display_game(game);
    display_txt_Puzzle(game);



    cout<<endl; system("pause");
    return 0;
}
