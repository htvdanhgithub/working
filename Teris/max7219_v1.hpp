#include <stdint.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <conio.h>
#include <unistd.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>


using namespace std;

#define MATRIX44_COLUMN_MAX 4
#define MATRIX44_ROW_MAX 4

#define MATRIX88_COLUMN_MAX 8
#define MATRIX88_ROW_MAX 8

#define CHARACTER_MAX 9

typedef struct 
{
    uint8_t start_index;
    uint8_t cur_index;
    uint8_t num;
} CHARACTER_INFO;

typedef struct 
{
    uint8_t  data[MATRIX44_ROW_MAX][MATRIX44_COLUMN_MAX];
} MATRIX44;
typedef struct 
{
    uint8_t  data[MATRIX88_ROW_MAX][MATRIX88_COLUMN_MAX];
} MATRIX88;

typedef struct 
{
    uint8_t  col[MATRIX88_COLUMN_MAX];
} MATRIX7219;

typedef enum
{
    OK,
    GAME_OVER,
    LEFT_OVER_BOUNDARY,
    RIGHT_OVER_BOUNDARY,
    HIT_LAND
};   

CHARACTER_INFO g_char_info[CHARACTER_MAX] =
{
////////I/////////////
{0, 0, 2},
////////s/////////////
{2, 0, 2},
////////back s/////////////
{4, 0, 2},
////////back L/////////////
{6, 0, 4},
////////L/////////////
{10, 0, 4},
////////box/////////////
{14, 0, 1},
////////V/////////////
{15, 0, 4},
////////+/////////////
{19, 0, 1},
////////T/////////////
{20, 0, 4},
};
uint8_t g_char_info_index;
MATRIX44* g_cur_matrix44;
MATRIX44 g_matrix44[] =
{
////////I/////////////
{0,	1,	0,	0,
0,	1,	0,	0,
0,	1,	0,	0,
0,	1,	0,	0},
{0,	0,	0,	0,
1,	1,	1,	1,
0,	0,	0,	0,
0,	0,	0,	0},
////////s/////////////
{0,	1,	1,	0,
1,	1,	0,	0,
0,	0,	0,	0,
0,	0,	0,	0},
{0,	1,	0,	0,
0,	1,	1,	0,
0,	0,	1,	0,
0,	0,	0,	0},
////////back s/////////////
{1,	1,	0,	0,
0,	1,	1,	0,
0,	0,	0,	0,
0,	0,	0,	0},
{0,	1,	0,	0,
1,	1,	0,	0,
1,	0,	0,	0,
0,	0,	0,	0},
////////back L/////////////
{0,	0,	0,	0,
1,	1,	1,	0,
0,	0,	1,	0,
0,	0,	0,	0},
{0,	1,	1,	0,
0,	1,	0,	0,
0,	1,	0,	0,
0,	0,	0,	0},
{1,	0,	0,	0,
1,	1,	1,	0,
0,	0,	0,	0,
0,	0,	0,	0},
{0,	1,	0,	0,
0,	1,	0,	0,
1,	1,	0,	0,
0,	0,	0,	0},
////////L/////////////
{0,	0,	0,	0,
1,	1,	1,	0,
1,	0,	0,	0,
0,	0,	0,	0},
{1,	1,	0,	0,
0,	1,	0,	0,
0,	1,	0,	0,
0,	0,	0,	0},
{0,	0,	1,	0,
1,	1,	1,	0,
0,	0,	0,	0,
0,	0,	0,	0},
{0,	1,	0,	0,
0,	1,	0,	0,
0,	1,	1,	0,
0,	0,	0,	0},
////////box/////////////
{0,	1,	1,	0,
0,	1,	1,	0,
0,	0,	0,	0,
0,	0,	0,	0},
////////V/////////////
{0,	0,	0,	0,
0,	1,	1,	0,
0,	1,	0,	0,
0,	0,	0,	0},
{0,	0,	0,	0,
1,	1,	0,	0,
0,	1,	0,	0,
0,	0,	0,	0},
{0,	1,	0,	0,
1,	1,	0,	0,
0,	0,	0,	0,
0,	0,	0,	0},
{0,	1,	0,	0,
0,	1,	1,	0,
0,	0,	0,	0,
0,	0,	0,	0},
////////+/////////////
{0,	1,	0,	0,
1,	1,	1,	0,
0,	1,	0,	0,
0,	0,	0,	0},
////////T/////////////
{1,	1,	1,	0,
0,	1,	0,	0,
0,	1,	0,	0,
0,	0,	0,	0},
{0,	0,	1,	0,
1,	1,	1,	0,
0,	0,	1,	0,
0,	0,	0,	0},
{0,	1,	0,	0,
0,	1,	0,	0,
1,	1,	1,	0,
0,	0,	0,	0},
{1,	0,	0,	0,
1,	1,	1,	0,
1,	0,	0,	0,
0,	0,	0,	0},
};         
MATRIX88 g_matrix88 = 
{
        0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,
};
MATRIX7219 g_matrix7219;
int8_t cur_x = 2;
int8_t cur_y = 0;    
FILE *fp;

void printf_MATRIX44(int8_t x, int8_t y, const MATRIX44* matrix)
{
    fprintf(fp, "<<<<<<<<<<<<<<<<<<<<MATRIX44\n");
    for(int8_t row = 0; row < MATRIX88_ROW_MAX; row++)
    {
        for(int8_t col = 0; col < MATRIX88_COLUMN_MAX; col++)
        {
            if((row - y >= 0) && (row - y < MATRIX44_ROW_MAX)
            && (col - x >= 0) && (col - x < MATRIX44_COLUMN_MAX)
            && (matrix->data[row - y][col - x] == 1))
            {
                fprintf(fp, "X");
            }
            else
            {
                fprintf(fp, "_");
            }
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, ">>>>>>>>>>>>>>>>>>>>\n");
}
void printf_cur_MATRIX44(int8_t x, int8_t y)
{
    MATRIX44* matrix = &g_matrix44[g_char_info[g_char_info_index].start_index + g_char_info[g_char_info_index].cur_index];
    printf_MATRIX44(x, y, matrix);
}
MATRIX44* get_MATRIX44(uint8_t index, uint8_t sub_index)
{
    return &g_matrix44[g_char_info[index].start_index + sub_index];
}
void printf_all_MATRIX44()
{
	MATRIX44* matrix;
    fprintf(fp, "printf_all_MATRIX44 size = %d\n", CHARACTER_MAX);
    for(uint8_t index = 0; index < CHARACTER_MAX; index++)
    {
        for(uint8_t sub_index = 0; sub_index < g_char_info[index].num; sub_index++)
        {
            fprintf(fp, "printfMATRIX44 index = %d, sub_index = %d\n", index, sub_index);
        	matrix = get_MATRIX44(index, sub_index);
            printf_MATRIX44(0, 0, matrix);
        }
    }            
}     
void printf_MATRIX88(const MATRIX88* matrix)
{
    fprintf(fp, "<<<<<<<<<<<<<<<<<<<<MATRIX88\n");
    for(uint8_t row = 0; row < MATRIX88_ROW_MAX; row++)
    {
        for(uint8_t col = 0; col < MATRIX88_COLUMN_MAX; col++)
        {
            if(matrix->data[row][col] == 1)
            {
                fprintf(fp, "X");
            }
            else
            {
                fprintf(fp, "_");
            }
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, ">>>>>>>>>>>>>>>>>>>>\n");
}
void printf_console_MATRIX88(const MATRIX88* matrix)
{
    printf("<<<<<<<<<<<<<<<<<<<<\n");
    for(uint8_t row = 0; row < MATRIX88_ROW_MAX; row++)
    {
        for(uint8_t col = 0; col < MATRIX88_COLUMN_MAX; col++)
        {
            if(matrix->data[row][col] == 1)
            {
                printf("*");
            }
            else
            {
                printf("_");
            }
        }
        printf("\n");
    }
    printf(">>>>>>>>>>>>>>>>>>>>\n");
}
void printf_MATRIX7219(const MATRIX7219* matrix)
{
    uint8_t mask = 0x80;

    fprintf(fp, "<<<<<<<<<<<<<<<<<<<<\n");
    for(uint8_t row = 0; row < MATRIX88_ROW_MAX; row++)
    {
        for(uint8_t col = 0; col < MATRIX88_COLUMN_MAX; col++)
        {
            if((matrix->col[col] & mask) > 0)
            {
                fprintf(fp, "*");
            }
            else
            {
                fprintf(fp, "_");
            }
        }
        fprintf(fp, "\n");
        mask >>= 1;
    }
    fprintf(fp, ">>>>>>>>>>>>>>>>>>>>\n");
}
void MATRIX88_to_MATRIX7219(const MATRIX88* matrix88, MATRIX7219* matrix7219)
{
    uint8_t mask = 0x80;

    for(uint8_t col = 0; col < MATRIX88_ROW_MAX; col++)
    {
        mask = 0x80;
        matrix7219->col[col] = 0;
        for(uint8_t row = 0; row < MATRIX88_COLUMN_MAX; row++)
        {
            if(matrix88->data[row][col] == 1)
            {
                matrix7219->col[col] |= mask;
            }
            mask >>= 1;
        }
    }
}
uint8_t is_row_full(const MATRIX88* matrix, uint8_t row)
{
    for(uint8_t col = 0; col < MATRIX88_COLUMN_MAX; col++)
    {
        if(matrix->data[row][col] == 0)
        {
            return 0;
        }
    }
    return 1;
}
void delete_row(MATRIX88* matrix, uint8_t row)
{
    for(int8_t i = MATRIX88_ROW_MAX - 1; i >= 0; i--)
    {
        if(i <= row)
        {
            if(i > 0)
            {
                memcpy(matrix->data[i], matrix->data[i - 1], MATRIX88_COLUMN_MAX*sizeof(uint8_t));
            }
            else
            {
                memset(matrix->data[i], 0, MATRIX88_COLUMN_MAX*sizeof(uint8_t));
            }
        }
    }     
}
uint8_t delete_matrix(MATRIX88* matrix)
{
    uint8_t count = 0;
    int8_t row = MATRIX88_ROW_MAX - 1;
    while(row >= 0)
    {
        if(is_row_full(matrix, row))
        {
            delete_row(matrix, row);
            count++;
        }
        else
        {
            row--;            
        }
    }     
    fprintf(fp, "delete_matrix count = %d\n", count);
    return count;
}
uint8_t is_row_empty(const MATRIX88* matrix, uint8_t row)
{
    for(uint8_t col = 0; col < MATRIX88_COLUMN_MAX; col++)
    {
        if(matrix->data[row][col] == 1)
        {
            return 0;
        }
    }
    return 1;
}
uint8_t is_col_empty(const MATRIX88* matrix, uint8_t col)
{
    for(uint8_t row = 0; row < MATRIX88_ROW_MAX; row++)
    {
        if(matrix->data[row][col] == 1)
        {
            return 0;
        }
    }
    return 1;
}
void test_is_row_full(const MATRIX88* matrix)
{
    for(uint8_t row = 0; row < MATRIX88_ROW_MAX; row++)
    {
        fprintf(fp, "row[%d] is %s\n", row, is_row_full(matrix, row) == 0 ? "not full" : "full");
    }
}
void test_is_row_empty(const MATRIX88* matrix)
{
    for(uint8_t row = 0; row < MATRIX88_ROW_MAX; row++)
    {
        fprintf(fp, "row[%d] is %s\n", row, is_row_empty(matrix, row) == 0 ? "not empty" : "empty");
    }
}
void test_is_col_empty(const MATRIX88* matrix)
{
    for(uint8_t col = 0; col < MATRIX88_COLUMN_MAX; col++)
    {
        fprintf(fp, "col[%d] is %s\n", col, is_col_empty(matrix, col) == 0 ? "not empty" : "empty");
    }
}
uint8_t hit_land(int8_t x, int8_t y, const MATRIX44* matrix44, const MATRIX88* matrix88)
{
    fprintf(fp, "==============hit_land============\n");
    for(int8_t row = MATRIX44_ROW_MAX - 1; row >= 0; row--)
    {
        for(int8_t col = 0; col < MATRIX44_COLUMN_MAX; col++)
        {
            if(matrix44->data[row][col] == 1)
            {
                if((y + row) >= (MATRIX88_ROW_MAX - 1))
                {
                    fprintf(fp, "hit1 row = %d, col = %d\n", row, col);
                    return 1;
                }    

                if(matrix88->data[y + row + 1][x + col] == 1)
                {
                    fprintf(fp, "hit2 row = %d, col = %d\n", row, col);
                    return 1;
                }    
            }                             
        }            
    } 
    fprintf(fp, "not hit\n");
    return 0;
} 
void test_hit_land()
{
    int8_t x = 5, y = 6;
    MATRIX44* matrix44 = get_MATRIX44(1, 0);
    MATRIX88 matrix88 =
    {
            0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,
            0,  1,  0,  1,  0,  0,  0,  0,
            1,  0,  0,  1,  0,  0,  0,  0,
            1,  1,  0,  1,  0,  0,  0,  0,
            1,  1,  0,  1,  0,  0,  0,  0,
            1,  1,  0,  0,  1,  0,  0,  0,
    };
    printf_MATRIX44(x, y, matrix44);
    printf_MATRIX88(&matrix88);
    hit_land(x, y, matrix44, &matrix88);
}
uint8_t is_valid(int8_t x, int8_t y, const MATRIX44* matrix44, const MATRIX88* matrix88)
{
    fprintf(fp, "==============is_valid============\n");
    for(int8_t row = MATRIX44_ROW_MAX - 1; row >= 0; row--)
    {
        for(int8_t col = 0; col < MATRIX44_COLUMN_MAX; col++)
        {
            if(matrix44->data[row][col] == 1)
            {
                if(matrix88->data[y + row][x + col] == 1)
                {
                    fprintf(fp, "not valid1 row = %d, col = %d\n", row, col);
                    return 0;
                }

                if(( x + col < 0) || (x + col >= MATRIX88_COLUMN_MAX))
                {
                    fprintf(fp, "not valid2 row = %d, col = %d\n", row, col);
                    return 0;
                }
                if((y + row) > (MATRIX88_ROW_MAX - 1))
                {
                    fprintf(fp, "not valid3 row = %d, col = %d\n", row, col);
                    return 0;
                }
            }
        }
    }
    fprintf(fp, "valid\n");
    return 1;
}
void test_is_valid()
{
    int8_t x = 5, y = 7;
    MATRIX44* matrix44 = get_MATRIX44(1, 0);
    MATRIX88 matrix88 =
    {
            0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,
            0,  1,  0,  1,  0,  0,  0,  0,
            1,  0,  0,  1,  0,  0,  0,  0,
            1,  1,  0,  1,  0,  0,  0,  0,
            1,  1,  0,  1,  0,  0,  0,  0,
            1,  1,  0,  0,  1,  0,  0,  0,
    };
    printf_MATRIX44(x, y, matrix44);
    printf_MATRIX88(&matrix88);
    is_valid(x, y, matrix44, &matrix88);
}
uint8_t is_left_boundary(int8_t x, const MATRIX44* matrix44, const MATRIX88* matrix88)
{
    //    fprintf(fp, "is_in_bound x = %d, y = %d\n", x, y);
    for(int8_t row = MATRIX44_ROW_MAX - 1; row >= 0; row--)
    {
        //        fprintf(fp, "row = %d\n", row);
        for(int8_t col = 0; col < MATRIX44_COLUMN_MAX; col++)
        {
            if(matrix44->data[row][col] == 1)
            {
                if( x + col < 0)
                {
                    //                    fprintf(fp, "LEFT_OVER_BOUNDARY\n");
                    return LEFT_OVER_BOUNDARY;
                }    
            }                             
        }            
    } 
    return OK;
}     
uint8_t is_right_boundary(int8_t x, const MATRIX44* matrix44, const MATRIX88* matrix88)
{
    //    fprintf(fp, "is_in_bound x = %d, y = %d\n", x, y);
    for(int8_t row = MATRIX44_ROW_MAX - 1; row >= 0; row--)
    {
        //        fprintf(fp, "row = %d\n", row);
        for(int8_t col = 0; col < MATRIX44_COLUMN_MAX; col++)
        {
            if(matrix44->data[row][col] == 1)
            {
                if(x + col > MATRIX88_COLUMN_MAX - 1)
                {
                    //                     fprintf(fp, "x = %d, col = %d, sum = %d\n", x, col, x + col);
                    //                    fprintf(fp, "RIGHT_OVER_BOUNDARY\n");
                    return RIGHT_OVER_BOUNDARY;
                }    
            }                             
        }            
    } 
    return OK;
}     
uint8_t fall_off(int8_t x, int8_t y, const MATRIX44* matrix44, const MATRIX88* matrix88)
{
    while(1)
    {
        for(int8_t row = MATRIX44_ROW_MAX - 1; row >= 0; row--)
        {
            for(int8_t col = 0; col < MATRIX44_COLUMN_MAX; col++)
            {
                if(matrix44->data[row][col] == 1)
                {
                    if(matrix88->data[y + row + 1][x + col] == 1)
                    {
                        fprintf(fp, "fall_off1 x = %d, y = %d\n", x, y);
                        return y;
                    }    
                    if((y + row) >= (MATRIX88_ROW_MAX - 1))
                    {
                        fprintf(fp, "fall_off2 x = %d, y = %d\n", x, y);
                        return y;
                    }  
                }                             
            }            
        } 
        y++;
    }
} 
void clear(int8_t x, int8_t y, const MATRIX44* matrix44, MATRIX88* matrix88)
{
    for(uint8_t row = 0; row < MATRIX44_ROW_MAX; row++)
    {
        for(uint8_t col = 0; col < MATRIX44_COLUMN_MAX; col++)
        {
            if(matrix44->data[row][col] == 1)
            {
                matrix88->data[y + row][x + col] = 0;                         
            }                             
        }            
    }            
}     
void merge(int8_t x, int8_t y, const MATRIX44* matrix44, MATRIX88* matrix88)
{
    for(uint8_t row = 0; row < MATRIX44_ROW_MAX; row++)
    {
        for(uint8_t col = 0; col < MATRIX44_COLUMN_MAX; col++)
        {
            if(matrix44->data[row][col] == 1)
            {
                //                fprintf(fp, "x = %d, y = %d, row = %d, col = %d, y + row = %d, x + col = %d\n", x, y, row, col, y + row, x + col);
                matrix88->data[y + row][x + col] = 1;                         
            }                             
        }            
    }            
}     
void merge1(int8_t x, int8_t y, const MATRIX44* matrix44, const MATRIX88* matrix88_in, MATRIX88* matrix88_out)
{
    memcpy(matrix88_out, matrix88_in, sizeof(MATRIX88));

    for(uint8_t row = 0; row < MATRIX44_ROW_MAX; row++)
    {
        for(uint8_t col = 0; col < MATRIX44_COLUMN_MAX; col++)
        {
            if(matrix44->data[row][col] == 1)
            {
                matrix88_out->data[y + row][x + col] = 1;                         
            }                             
        }            
    }            
}     
uint16_t evaluate2(const MATRIX88* matrix)
{
    uint16_t risk = 0;
    uint8_t empty_count;
    //    fprintf(fp, "<<<<<<<<<<<<<<<<<<<<\n");
    for(int8_t row = MATRIX88_ROW_MAX - 1; row >= 0; row--)
    {
        empty_count = 0;
        for(uint8_t col = 0; col < MATRIX88_COLUMN_MAX; col++)
        {
            if(matrix->data[row][col] == 0)
            {
                empty_count++;
            }
        }
        risk += empty_count*(row + 1);
    }
    fprintf(fp, "risk = %d\n", risk);
    return risk;
}

uint16_t evaluate1(const MATRIX88* matrix)
{
    uint16_t risk = 0;
    uint8_t risk_row_temp[MATRIX88_ROW_MAX];
    uint8_t risk_temp[MATRIX88_ROW_MAX];
    uint8_t risk_temp_count;
    uint8_t full;
    //    fprintf(fp, "<<<<<<<<<<<<<<<<<<<<\n");
    for(uint8_t col = 0; col < MATRIX88_COLUMN_MAX; col++)
    {
        full = 1;
        risk_temp_count = 0;
        memset(risk_temp, 0, sizeof(risk_temp));
        memset(risk_row_temp, 0, sizeof(risk_row_temp));
        for(int8_t row = MATRIX88_ROW_MAX - 1; row >= 0; row--)
        {
            if(matrix->data[row][col] == 1)
            {
                for(uint8_t i = 0; i < risk_temp_count; i++)
                {
                    risk_temp[i] += risk_row_temp[i];
                }
            }
            else
            {
                if(full == 1)
                {
                    risk_row_temp[risk_temp_count] = row;
                    risk_temp_count++;
                }
            }
            full = matrix->data[row][col];
        }
        //        fprintf(fp, "col = %d, risk_temp_count = %d\n", col, risk_temp_count);
        for(uint8_t i = 0; i < risk_temp_count; i++)
        {
            //         fprintf(fp, "risk_temp[%d] = %d\n", i, risk_temp[i]);
            risk += risk_temp[i];
        }            
    }
    fprintf(fp, "risk = %d\n", risk);
    return risk;
}
uint16_t evaluate(const MATRIX88* matrix)
{
    uint16_t risk = 0;
    uint8_t full = 0xFF;
    for(uint8_t col = 0; col < MATRIX88_COLUMN_MAX; col++)
    {
        full = 0xFF;
        for(int8_t row = MATRIX88_ROW_MAX - 1; row >= 0; row--)
        {
            if(full == 0xFF)
            {
                full = matrix->data[row][col];
            }
            else
            {
                if(matrix->data[row][col] == 1)
                {
                    if(full == 0)
                    {
                        risk++;
                    }
                }
                full = matrix->data[row][col];
            }
        }
    }
    fprintf(fp, "risk = %d\n", risk);

    return risk;
}
uint8_t char_info_index_rand()
{
    return rand()%CHARACTER_MAX;
}
int8_t left_most(int8_t x, const MATRIX44* matrix44, const MATRIX88* matrix88)
{
    while(1)
    {
        if(is_left_boundary(x, matrix44, matrix88) == LEFT_OVER_BOUNDARY)
        {
            fprintf(fp, "left_most = %d\n", x + 1);
            return x + 1;
        }
        x--;
    } 
}    
int8_t right_most(int8_t x, const MATRIX44* matrix44, const MATRIX88* matrix88)
{
    while(1)
    {
        if(is_right_boundary(x, matrix44, matrix88) == RIGHT_OVER_BOUNDARY)
        {
            fprintf(fp, "right_most = %d\n", x - 1);
            return x - 1;
        }
        x++;
    } 
}    
uint8_t get_high(MATRIX88* matrix)
{
    for(int8_t row = MATRIX88_ROW_MAX - 1; row >= 0; row--)
    {
        if(is_row_empty(matrix, row) == 1)
        {
            fprintf(fp, "get_high height = %d\n", MATRIX88_ROW_MAX - row - 1);
            return (uint8_t)(MATRIX88_ROW_MAX - row - 1);
        }
    } 
    return MATRIX88_ROW_MAX;    
}
uint8_t get_high_after_merge(int8_t y, MATRIX44* matrix)
{
    for(int8_t row = 0; row < MATRIX44_ROW_MAX; row++)
    {
        for(int8_t col = 0; col < MATRIX44_COLUMN_MAX; col++)
        {
        	if(matrix->data[row][col] == 1)
        	{
                fprintf(fp, "get_high_after_merge y = %d, row = %d, height = %d\n", y, row, MATRIX88_ROW_MAX - y - row);
                return (uint8_t)(MATRIX88_ROW_MAX - y - row);
        	}
        }
    }
}
uint8_t find_best_solution()
{
    fprintf(fp, "==============find_best_solution============\n");
    int8_t temp_pre_x = 0xFF, tem_pre_sub_index = 0xFF;
    uint16_t temp_pre_risk = 0xFFFF;
    int8_t temp_y;
    uint16_t temp_risk;
    uint8_t temp_count, temp_pre_count = 0;
    uint8_t temp_high, temp_pre_high = 0xFF;
    MATRIX44* temp_cur_matrix44 = NULL;
    MATRIX88 temp_matrix88;
    uint8_t res = 0;
    int8_t left_most_index, right_most_index;

    fprintf(fp, "g_char_info_index = (%d), num = %d\n", g_char_info_index, g_char_info[g_char_info_index].num);
    for(uint8_t tem_sub_index = 0; tem_sub_index < g_char_info[g_char_info_index].num; tem_sub_index++)
    {
        temp_cur_matrix44 = &g_matrix44[g_char_info[g_char_info_index].start_index + tem_sub_index];
        left_most_index = left_most(cur_x, temp_cur_matrix44, &g_matrix88);
        right_most_index = right_most(cur_x, temp_cur_matrix44, &g_matrix88);

        for(int8_t temp_x = left_most_index; temp_x <= right_most_index; temp_x++)
        {
            temp_y = fall_off(temp_x, cur_y, temp_cur_matrix44, &g_matrix88); 
            printf_MATRIX44(temp_x, temp_y, temp_cur_matrix44);
            printf_MATRIX88(&g_matrix88);
            if(is_valid(temp_x, temp_y, temp_cur_matrix44, &g_matrix88) == 0)
            {
                continue;
            }
            res = 1;
            merge1(temp_x, temp_y, temp_cur_matrix44, &g_matrix88, &temp_matrix88); 
            temp_count = delete_matrix(&temp_matrix88);    
            temp_risk = evaluate(&temp_matrix88);
            temp_high = get_high_after_merge(temp_y, temp_cur_matrix44);
            printf_MATRIX88(&temp_matrix88);
            if(temp_count > temp_pre_count)
            {
                fprintf(fp, "temp_count(%d) > temp_pre_count(%d)\n", temp_count, temp_pre_count);
                temp_pre_count = temp_count;
                temp_pre_risk = temp_risk;
                temp_pre_high = temp_high;
                tem_pre_sub_index = tem_sub_index;
                temp_pre_x = temp_x;
            }
            else if(temp_count == temp_pre_count)
            {
                if(get_high(&g_matrix88) <= MATRIX88_ROW_MAX/2 + 1)
                {
                    fprintf(fp, "height <= (%d)\n", MATRIX88_ROW_MAX/2 + 1);

                    fprintf(fp, "temp_count(%d) == temp_pre_count(%d)\n", temp_count, temp_pre_count);
                    if(temp_risk < temp_pre_risk)
                    {
                        fprintf(fp, "temp_risk(%d) < temp_pre_risk(%d)\n", temp_risk, temp_pre_risk);
                        temp_pre_count = temp_count;
                        temp_pre_risk = temp_risk;
                        temp_pre_high = temp_high;
                        tem_pre_sub_index = tem_sub_index;
                        temp_pre_x = temp_x;
                    }
                    else if(temp_risk == temp_pre_risk)
                    {
                        fprintf(fp, "temp_risk(%d) == temp_pre_risk(%d)\n", temp_risk, temp_pre_risk);
                        if(temp_high < temp_pre_high)
                        {
                            fprintf(fp, "temp_high(%d) < temp_pre_high(%d)\n", temp_high, temp_pre_high);
                            temp_pre_count = temp_count;
                            temp_pre_risk = temp_risk;
                            temp_pre_high = temp_high;
                            tem_pre_sub_index = tem_sub_index;
                            temp_pre_x = temp_x;
                        }
                    }
                }
                else
                {
                    fprintf(fp, "WARNING height > (%d)\n", MATRIX88_ROW_MAX/2 + 1);
                    fprintf(fp, "temp_high = %d, temp_pre_high = %d\n", temp_high, temp_pre_high);
                    if(temp_high < temp_pre_high)
                    {
                        fprintf(fp, "temp_high(%d) < temp_pre_high(%d)\n", temp_high, temp_pre_high);
                        temp_pre_count = temp_count;
                        temp_pre_risk = temp_risk;
                        temp_pre_high = temp_high;
                        tem_pre_sub_index = tem_sub_index;
                        temp_pre_x = temp_x;
                    }
                    else if(temp_high == temp_pre_high)
                    {
                        fprintf(fp, "temp_high(%d) < temp_pre_high(%d)\n", temp_high, temp_pre_high);
                        if(temp_risk < temp_pre_risk)
                        {
                            fprintf(fp, "temp_risk(%d) < temp_pre_risk(%d)\n", temp_risk, temp_pre_risk);
                            temp_pre_count = temp_count;
                            temp_pre_risk = temp_risk;
                            temp_pre_high = temp_high;
                            tem_pre_sub_index = tem_sub_index;
                            temp_pre_x = temp_x;
                        }
                    }
                }
            }
            fprintf(fp, "sub_index = %d, temp_pre_x = %d, temp_pre_count = %d, temp_pre_risk = %d, temp_pre_high = %d\n", tem_pre_sub_index, temp_pre_x, temp_pre_count, temp_pre_risk, temp_pre_high);
            //			system("PAUSE");
        }
    } 
    if(res == 1)
    {
        g_char_info[g_char_info_index].cur_index = tem_pre_sub_index;
        cur_x = temp_pre_x;
        printf_cur_MATRIX44(cur_x, cur_y);

        fprintf(fp, "chosen sub_index = %d, temp_pre_x = %d, temp_pre_count = %d, temp_pre_risk = %d, temp_pre_high = %d\n", tem_pre_sub_index, temp_pre_x, temp_pre_count, temp_pre_risk, temp_pre_high);
    }
    else
    {
        fprintf(fp, "GAME OVER!!!\n");
    }
    //	g_cur_matrix44 = &g_matrix44[g_char_info[g_char_info_index].start_index + g_char_info[g_char_info_index].cur_index];
    //	printf_MATRIX88(&g_matrix88);
    system("PAUSE");
    return res;
}
void test_find_best_solution()
{
    g_char_info_index = 1;
    find_best_solution();
}
int main(int argc, char *argv[])
{
    //////////////////////////////////////////////
    fp = fopen("debug.txt", "w");
    if(fp==NULL)
    {
        fprintf(fp, "File Not Found");
        exit(-1);
    }

    //////////////////////////////////////////////
    //    printf_MATRIX44(&g_matrix44[0]);
//    printf_MATRIX88(&g_matrix88);
    //	get_high(&g_matrix88);
    //    delete_matrix(&g_matrix88);
    //    printf_MATRIX88(&g_matrix88);
    //    evaluate(&g_matrix88);
    //      g_char_info_index = 8;
    //      find_best_solution();
    //        printf_MATRIX88(&g_matrix88);
//    test_find_best_solution();
//    printf_all_MATRIX44();
//    goto __exit;
    uint8_t hit_res;
    srand(time(NULL));

    while(1)
    {
        cur_y = 0;
        cur_x = 2, cur_y = 0;
        g_char_info_index = char_info_index_rand();

        fprintf(fp, "g_char_info_index = %d\n", g_char_info_index);
        if(find_best_solution() == 0)
        {
            printf("GAME OVER!!!\n");
            goto __exit;
        }
        g_cur_matrix44 = &g_matrix44[g_char_info[g_char_info_index].start_index + g_char_info[g_char_info_index].cur_index];
        while(1)
        {
            hit_res = hit_land(cur_x, cur_y, g_cur_matrix44, &g_matrix88);
            fprintf(fp, "hit_res = %d\n", hit_res);
            merge(cur_x, cur_y, g_cur_matrix44, &g_matrix88);
            if(hit_res == 1)
            {
                delete_matrix(&g_matrix88);
            }
            fprintf(fp, "printf_console_MATRIX88\n");
            printf_console_MATRIX88(&g_matrix88);
            printf_MATRIX88(&g_matrix88);
            if(hit_res == 0)
            {
                clear(cur_x, cur_y, g_cur_matrix44, &g_matrix88);
            }
            else
            {
                break;
            }
            Sleep(1000);
            cur_y++;
        }
    }
    __exit:
    fclose(fp);
    system("PAUSE");
    return EXIT_SUCCESS;
}
