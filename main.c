#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define newline() printf("\n")
#define WIDTH 50
#define HEIGHT 25
#define DEAD_SYMBOL '-'
#define ALIVE_SYMBOL '#'
#define BARRIER 'o'



/*Rules for Life:
    Any live cell with fewer than two live neighbors dies, as if by underpopulation.
    Any live cell with two or three live neighbors lives on to the next generation.
    Any live cell with more than three live neighbors dies, as if by overpopulation.
    Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
*/
typedef enum {dead_state, alive_state} state;
typedef struct cell{
    char symbol;
    state current_state;
    state next_state;
    int alive_neighbours;
} cell;

cell grid[HEIGHT][WIDTH];


void initialize_grid();
void print_grid();
void set_initial_alive_cells();
void count_alive_neighbours();
void calculate_next_state();
void update_grid();
void simulate();


int main(){

    initialize_grid();
    print_grid();
    set_initial_alive_cells();
    simulate();

    newline();
    printf("\nEND of PROGRAM");
    return 0;
}
void simulate(){
    int i;
    for(i = 0; i < 100; i++){
        sleep(1);
        calculate_next_state();
        update_grid();
        print_grid();
    }
}
void calculate_next_state(){
    int i, j, number_of_neighbours;
    state current_state;

    for(i = 0; i < HEIGHT; i++){
        for(j = 0; j < WIDTH; j++){
            number_of_neighbours = grid[i][j].alive_neighbours;
            current_state = grid[i][j].current_state;
            if(current_state == dead_state && number_of_neighbours == 3){
                grid[i][j].next_state = alive_state;
            } else if(current_state == alive_state){
                if(number_of_neighbours < 2  || number_of_neighbours > 3) grid[i][j].next_state = dead_state;
                else grid[i][j].next_state = alive_state;
            }
        }
    }
}
void count_alive_neighbours(){
    int i, j, count;
    for(i = 0; i < HEIGHT; i++){
        for(j = 0; j < WIDTH; j++){
            count = 0;
            if(i + 1 < HEIGHT){
                if(grid[i][j].current_state == alive_state) count++;
            }
            if(i - 1 >= 0){
                if(grid[i][j].current_state == alive_state) count++;
            }
            if(j + 1 < WIDTH){
                if(grid[i][j].current_state == alive_state) count++;
            }
            if(j - 1 >= 0){
                if(grid[i][j].current_state == alive_state) count++;
            }
            grid[i][j].alive_neighbours = count;
        }
    }

}
void set_initial_alive_cells(){
    int i, j, option;

    do{
        printf("Enter the row number: ");
        scanf("%d", &i);
        printf("Enter the column number: ");
        scanf("%d", &j);

        grid[i][j].current_state = alive_state;
        grid[i][j].symbol = ALIVE_SYMBOL;

        print_grid();
        printf("\nDo you want introduce one more alive cell?\n");
        printf("1. Yes\n2. No\n");
        scanf("%d", &option);
    }while(option == 1);
}
void print_grid(){
    int i, j;

    system("clear");

    for(i = 0; i < WIDTH + 2; i++) printf("%c", BARRIER);
    newline();
    for(i = 0; i < HEIGHT; i++){
        printf("%c", BARRIER);
        for(j = 0; j < WIDTH; j++){
            printf("%c", grid[i][j].symbol);
        }
        printf("%c", BARRIER);
        newline();
    }
    for(i = 0; i < WIDTH + 2; i++) printf("%c", BARRIER);
    newline();
}
void initialize_grid(){
    int i, j;
    for(i = 0; i < HEIGHT; i++){
        for(j = 0; j < WIDTH; j++){
            grid[i][j].symbol = DEAD_SYMBOL;
            grid[i][j].current_state = dead_state;
            grid[i][j].next_state = dead_state;
            grid[i][j].alive_neighbours = 0;
        }
    }
}
void update_grid(){
    int i, j;
    for(i = 0; i < HEIGHT; i++){
        for(j = 0; j < WIDTH; j++){
            grid[i][j].current_state = grid[i][j].next_state;
            if(grid[i][j].current_state == dead_state) grid[i][j].symbol = DEAD_SYMBOL;
            if(grid[i][j].current_state == alive_state) grid[i][j].symbol = ALIVE_SYMBOL;
        }
    }
}