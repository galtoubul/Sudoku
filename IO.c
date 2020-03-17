
#include "IO.h"

int loadPuzzle(char* filePath, Game* game){

    FILE *fPointer;
    char* line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    int counter = 0;
    fPointer = fopen(filePath,"r");

    if(fPointer == NULL){
        printf("Error: file open failed\n");
        return 1;
    }

    //loads first 2 lines of the file to get size or row and col.
    int m = 0;
    int n = 0;
    if(fscanf(fPointer,"%d %d", &m,&n) != 2){
        printf("Error: invalid Sudoku size parameters\n");
        return 1;
    }
    game->boxCol = n;
    game->boxRow = m;
    game->rows = m*n;
    game->columns = m*n;
    game->size = game->rows*game->columns;

    createEmptyBoard(game);
    m = 0;
    n = 0;

    //read file line by line, iterate through game board and add the values correctly.
    read = getline(&line, &len, fPointer);
    while ((read = getline(&line, &len, fPointer)) != -1 && counter < game->size ) {
        char* token = strtok(line, " \t");
        while(token != NULL && strcmp(token,"\n") != 0){
            char* temp = (char*)malloc(sizeof(char));
            if (temp == NULL) {
                return 0;
            }
            if(n == game->columns){
                n = 0;
                m++;
            }
            temp = strncpy(temp,token,2);
            if(!isNumber(temp) || !validateCell(atoi(temp),game->rows)){
                printf("Error: the value has been loaded is not valid\n");
                return 0;
            }
            game->currBoard[m][n] = atoi(temp);
            if(NULL != strrchr(token,'.')){
                game->fixedCellsBoard[m][n] = 1;
            }
            free(temp);
            token = strtok(NULL," ");
            n++;
            counter++;
        }
    }
    fclose(fPointer);
    return 1;

}


int savePuzzle(char* filePath, Game* game, bool editMode){

    FILE* output;
    int i = 0;
    int j = 0;
    output = fopen(filePath,"wt");
    if(output == NULL){
        printf("Error: Can't modify or save to this file\n");
        return 1;
    }

    fprintf(output,"%d %d\n",game->rows,game->columns);

    for(i = 0; i < game->rows; i++){
        for(j = 0; j < game->columns; j++){
            fprintf(output,"%d",game->currBoard[i][j]);
            if(editMode && game->currBoard[i][j] != 0){
                fprintf(output,".");
            }
            fprintf(output, " ");
        }
        fprintf(output, "\n");
    }
    fflush(output);
    fclose(output);
    return 1;

}

bool isNumber(char *input)
{
    int j;
    int size = 2;

    if(strlen(input) == 1){
        size = 1;
    }
    if(strstr(input,"\n") != NULL){
        size = 1;
    }
    for(j = 0; j < size; j++){
        if((input[j] > 47 && input[j] < 58) || input[j] == '.'){
            continue;
        }
        return false;
    }
    return true;
}
