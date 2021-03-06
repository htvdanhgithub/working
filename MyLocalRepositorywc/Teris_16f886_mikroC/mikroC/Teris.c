/*
'*******************************************************************************
'  Project name: PIC16F876A & MAX7219 For 8x8 LED Display
'  Description:
'          Trough the current experiment we wish to succed the next task:
'          Display on 8x8 Led matrix, the alphabet. The sequence between letters,
'          will have one second delay.
'  Written by:
'          Mark &
'          Aureliu Raducu Macovei, 2011.
'  Test configuration:
'    MCU:                        PIC16F876A;
'    Test.Board:                 WB-106 Breadboard 2420 dots;
'    SW:                         MikroC PRO for PIC 2011 (version v4.60);
'  Configuration Word:
'    Oscillator:                 HS (8Mhz)on pins 9 and 10;
'    Watchdog Timer:             OFF;
'    Power up Timer:             OFF;
'    Browun Out Detect:          ON;
'    Low Voltage Program:        Disabled;
'    Data EE Read Protect:       OFF;
'    Flash Program Write:        Write Protection OFF;
'    Background Debug:           Disabled;
'    Code Protect:               OFF
'*******************************************************************************
 */

//#define WINDOW_BASE

#ifdef WINDOW_BASE
using namespace std;
#endif

#define MATRIX44_COLUMN_MAX 4
#define MATRIX44_ROW_MAX 4

#define MATRIX88_COLUMN_MAX 8
#define MATRIX88_ROW_MAX 8

#define CHARACTER_MAX 9

typedef struct
{
    unsigned short start_index;
    unsigned short num;
} CHARACTER_INFO;
typedef struct
{
    unsigned short cell[MATRIX44_ROW_MAX][MATRIX44_COLUMN_MAX];
} MATRIX44;
typedef struct
{
    unsigned short cell[MATRIX88_ROW_MAX][MATRIX88_COLUMN_MAX];
} MATRIX88;

typedef struct
{
    unsigned short col[MATRIX88_COLUMN_MAX];
} MATRIX7219;

typedef enum
{
    OK,
    GAME_OVER,
    LEFT_OVER_BOUNDARY,
    RIGHT_OVER_BOUNDARY,
    HIT_LAND
};

const CHARACTER_INFO g_char_info[CHARACTER_MAX] =
{
////////I/////////////
{0, 2},
////////s/////////////
{2, 2},
////////back s/////////////
{4, 2},
////////back L/////////////
{6, 4},
////////L/////////////
{10, 4},
////////box/////////////
{14, 1},
////////V/////////////
{15, 4},
////////+/////////////
{19, 1},
////////T/////////////
{20, 4},
};
unsigned short g_char_info_index = 0;
unsigned short g_char_info_sub_index = 0;
char g_debug[10];

#define GET_CUR_MAXTRIX44  &g_matrix44[g_char_info[g_char_info_index].start_index + g_char_info_sub_index]
#define GET_TEMP_MAXTRIX44 &g_matrix44[g_char_info[g_char_info_index].start_index + tem_sub_index]

#ifdef WINDOW_BASE
MATRIX44 g_matrix44[] =
#else
    const MATRIX44 g_matrix44[] =
#endif
{
////////I/////////////
{0,    1,    0,    0,
0,    1,    0,    0,
0,    1,    0,    0,
0,    1,    0,    0},
{0,    0,    0,    0,
1,    1,    1,    1,
0,    0,    0,    0,
0,    0,    0,    0},
////////s/////////////
{0,    1,    1,    0,
1,    1,    0,    0,
0,    0,    0,    0,
0,    0,    0,    0},
{0,    1,    0,    0,
0,    1,    1,    0,
0,    0,    1,    0,
0,    0,    0,    0},
////////back s/////////////
{1,    1,    0,    0,
0,    1,    1,    0,
0,    0,    0,    0,
0,    0,    0,    0},
{0,    1,    0,    0,
1,    1,    0,    0,
1,    0,    0,    0,
0,    0,    0,    0},
////////back L/////////////
{0,    0,    0,    0,
1,    1,    1,    0,
0,    0,    1,    0,
0,    0,    0,    0},
{0,    1,    1,    0,
0,    1,    0,    0,
0,    1,    0,    0,
0,    0,    0,    0},
{1,    0,    0,    0,
1,    1,    1,    0,
0,    0,    0,    0,
0,    0,    0,    0},
{0,    1,    0,    0,
0,    1,    0,    0,
1,    1,    0,    0,
0,    0,    0,    0},
////////L/////////////
{0,    0,    0,    0,
1,    1,    1,    0,
1,    0,    0,    0,
0,    0,    0,    0},
{1,    1,    0,    0,
0,    1,    0,    0,
0,    1,    0,    0,
0,    0,    0,    0},
{0,    0,    1,    0,
1,    1,    1,    0,
0,    0,    0,    0,
0,    0,    0,    0},
{0,    1,    0,    0,
0,    1,    0,    0,
0,    1,    1,    0,
0,    0,    0,    0},
////////box/////////////
{0,    1,    1,    0,
0,    1,    1,    0,
0,    0,    0,    0,
0,    0,    0,    0},
////////V/////////////
{0,    0,    0,    0,
0,    1,    1,    0,
0,    1,    0,    0,
0,    0,    0,    0},
{0,    0,    0,    0,
1,    1,    0,    0,
0,    1,    0,    0,
0,    0,    0,    0},
{0,    1,    0,    0,
1,    1,    0,    0,
0,    0,    0,    0,
0,    0,    0,    0},
{0,    1,    0,    0,
0,    1,    1,    0,
0,    0,    0,    0,
0,    0,    0,    0},
////////+/////////////
{0,    1,    0,    0,
1,    1,    1,    0,
0,    1,    0,    0,
0,    0,    0,    0},
////////T/////////////
{1,    1,    1,    0,
0,    1,    0,    0,
0,    1,    0,    0,
0,    0,    0,    0},
{0,    0,    1,    0,
1,    1,    1,    0,
0,    0,    1,    0,
0,    0,    0,    0},
{0,    1,    0,    0,
0,    1,    0,    0,
1,    1,    1,    0,
0,    0,    0,    0},
{1,    0,    0,    0,
1,    1,    1,    0,
1,    0,    0,    0,
0,    0,    0,    0},
};
MATRIX88 g_matrix88 =
{
        0,    0,    0,    0,    0,    0,    0,    0,
        0,    0,    0,    0,    0,    0,    0,    0,
        0,    0,    0,    0,    0,    0,    0,    0,
        0,    0,    0,    0,    0,    0,    1,    0,
        0,    0,    1,    0,    1,    0,    1,    0,
        0,    1,    1,    0,    1,    0,    1,    0,
        0,    1,    1,    0,    1,    0,    1,    0,
        0,    1,    1,    1,    1,    1,    1,    0,
};
short cur_x = 2;
short cur_y = 0;

#ifdef WINDOW_BASE
FILE *fp;
#endif


// Serial 8x8 Matrix Display connections.
sbit Chip_Select at RA2_bit;
sbit Chip_Select_Direction at TRISA2_bit;
// End Serial 8x8 Matrix Display connections.

void Cus_UART1_Write_Text_Item(char * UART_text)
{
	while (UART1_Tx_Idle() == 0);
	UART1_Write_Text(UART_text);
}
void Cus_UART1_Write_Item(char UART_data)
{
	while (UART1_Tx_Idle() == 0);
	UART1_Write(UART_data);
}
void Cus_UART1_Write_Text(char * lable, char * UART_text)
{
	Cus_UART1_Write_Text_Item(lable);
	Cus_UART1_Write_Text_Item(":");
	Cus_UART1_Write_Text_Item(UART_text);
	Cus_UART1_Write_Text_Item("\r\n");
}
void Cus_UART1_Write_Int(char * lable, int UART_data)
{
	char text[10];
	Cus_UART1_Write_Text_Item(lable);
	Cus_UART1_Write_Text_Item(":");
	IntToStr(UART_data, text);
	Cus_UART1_Write_Text_Item(text);
	Cus_UART1_Write_Text_Item("\r\n");
}
// Here we set the configuration of max7219.
void max7219_init1()
{
    Chip_Select = 0;       // SELECT MAX
    SPI1_write(0x09);      // BCD mode for digit decoding
    SPI1_write(0x00);
    Chip_Select = 1;       // DESELECT MAX

    Chip_Select = 0;       // SELECT MAX
    SPI1_write(0x0A);
    SPI1_write(0x0F);      // Segment luminosity intensity
    Chip_Select = 1;       // DESELECT MAX

    Chip_Select = 0;       // SELECT MAX
    SPI1_write(0x0B);
    SPI1_write(0x07);      // Display refresh
    Chip_Select = 1;       // DESELECT MAX

    Chip_Select = 0;       // SELECT MAX
    SPI1_write(0x0C);
    SPI1_write(0x01);      // Turn on the display
    Chip_Select = 1;       // DESELECT MAX

    Chip_Select = 0;       // SELECT MAX
    SPI1_write(0x00);
    SPI1_write(0xFF);      // No test
    Chip_Select = 1;       // DESELECT MAX
}

// This is write Byte function.
void Write_Byte(unsigned short myColumn, unsigned short myValue)
{
    Chip_Select = 0;       // select max7219.
    SPI1_write(myColumn);  // send myColumn value to max7219 (digit place).
    SPI1_write(myValue);   // send myValue value to max7219 (digit place).
    Chip_Select = 1;       // deselect max7219.
}

#ifdef WINDOW_BASE
void printf_console_MATRIX44(short x, short y, const MATRIX44* matrix)
{
    fprintf(fp, "<<<<<<<<<<<<<<<<<<<<MATRIX44\n");
    for(short row = 0; row < MATRIX88_ROW_MAX; row++)
    {
        for(short col = 0; col < MATRIX88_COLUMN_MAX; col++)
        {
            if((row - y >= 0) && (row - y < MATRIX44_ROW_MAX)
                    && (col - x >= 0) && (col - x < MATRIX44_COLUMN_MAX)
                    && (matrix->cell[row - y][col - x] == 1))
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
#else
void printf_console_MATRIX44(short x, short y, const MATRIX44* matrix)
{
    short row;
    short col;
    Cus_UART1_Write_Text_Item("<<<<<<<<<<<<<<<<<<<<MATRIX44\r\n");
    for(row = 0; row < MATRIX88_ROW_MAX; row++)
    {
        for(col = 0; col < MATRIX88_COLUMN_MAX; col++)
        {
            if((row - y >= 0) && (row - y < MATRIX44_ROW_MAX)
                    && (col - x >= 0) && (col - x < MATRIX44_COLUMN_MAX)
                    && (matrix->cell[row - y][col - x] == 1))
            {
                Cus_UART1_Write_Text_Item("*");
            }
            else
            {
                Cus_UART1_Write_Text_Item("_");
            }
        }
        Cus_UART1_Write_Text_Item("\r\n");
    }
    Cus_UART1_Write_Text_Item(">>>>>>>>>>>>>>>>>>>>\r\n");
}
#endif

void printf_console_cur_MATRIX44(short x, short y)
{
    printf_console_MATRIX44(x, y, GET_CUR_MAXTRIX44);
}
#ifdef WINDOW_BASE
MATRIX44* get_MATRIX44(unsigned short index, unsigned short sub_index)
{
    return &g_matrix44[g_char_info[index].start_index + sub_index];
}
void printf_all_MATRIX44()
{
    MATRIX44* matrix;
    fprintf(fp, "printf_all_MATRIX44 size = %d\n", CHARACTER_MAX);
    for(unsigned short index = 0; index < CHARACTER_MAX; index++)
    {
        for(unsigned short sub_index = 0; sub_index < g_char_info[index].num; sub_index++)
        {
            fprintf(fp, "printfMATRIX44 index = %d, sub_index = %d\n", index, sub_index);
            matrix = get_MATRIX44(index, sub_index);
            printf_console_MATRIX44(0, 0, matrix);
        }
    }
}
#endif
#ifdef WINDOW_BASE
void printf_MATRIX7219(const MATRIX7219* matrix)
{
    unsigned short mask = 0x80;

    fprintf(fp, "<<<<<<<<<<<<<<<<<<<<\n");
    for(unsigned short row = 0; row < MATRIX88_ROW_MAX; row++)
    {
        for(unsigned short col = 0; col < MATRIX88_COLUMN_MAX; col++)
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
#else
void printf_MATRIX7219(MATRIX7219* matrix)
{
//    unsigned short col;
//
//    for (col = 0; col < MATRIX88_COLUMN_MAX; col++)
//    {
//        Write_Byte(col + 1, matrix->col[col]);
//    }
}
#endif
void MATRIX88_to_MATRIX7219(MATRIX88* matrix_88, MATRIX7219* matrix_7219)
{
    unsigned short mask = 0x80;
    unsigned short col;
    for(col = 0; col < MATRIX88_ROW_MAX; col++)
    {
        unsigned short row;
        mask = 0x80;
        matrix_7219->col[col] = 0;
        for(row = 0; row < MATRIX88_COLUMN_MAX; row++)
        {
            if(matrix_88->cell[row][col] == 1)
            {
                matrix_7219->col[col] |= mask;
            }
            mask >>= 1;
        }
    }
}

#ifdef WINDOW_BASE
void printf_MATRIX88(const MATRIX88* matrix)
{
    fprintf(fp, "<<<<<<<<<<<<<<<<<<<<MATRIX88\n");
    for(unsigned short row = 0; row < MATRIX88_ROW_MAX; row++)
    {
        for(unsigned short col = 0; col < MATRIX88_COLUMN_MAX; col++)
        {
            if(matrix->cell[row][col] == 1)
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
#else
void printf_MATRIX88(MATRIX88* matrix_88)
{
    MATRIX7219 matrix_7219;
    MATRIX88_to_MATRIX7219(matrix_88, &matrix_7219);
    printf_MATRIX7219(&matrix_7219);
}
#endif
void printf_Screen()
{
//    printf_MATRIX88(&g_matrix88);
}
// This is clear matrix function.
void Clear_Matrix(void)
{
    memset(&g_matrix88, 0, sizeof(MATRIX88));
    printf_Screen();
}

#ifdef WINDOW_BASE
void printf_console_MATRIX88(const MATRIX88* matrix)
{
    printf("<<<<<<<<<<<<<<<<<<<<\n");
    for(unsigned short row = 0; row < MATRIX88_ROW_MAX; row++)
    {
        for(unsigned short col = 0; col < MATRIX88_COLUMN_MAX; col++)
        {
            if(matrix->cell[row][col] == 1)
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
#else
void printf_console_MATRIX88(char* lable, MATRIX88* matrix)
{
    unsigned short row;
    unsigned short col;

    Cus_UART1_Write_Text_Item(lable);
    Cus_UART1_Write_Text_Item(":");
    Cus_UART1_Write_Text_Item("<<<<<<<<<<<<<<<<<<<<\r\n");
    for(row = 0; row < MATRIX88_ROW_MAX; row++)
    {
        for(col = 0; col < MATRIX88_COLUMN_MAX; col++)
        {
            if(matrix->cell[row][col] == 1)
            {
                Cus_UART1_Write_Text_Item("*");
            }
            else
            {
                Cus_UART1_Write_Text_Item("_");
            }
        }
        Cus_UART1_Write_Text_Item("\r\n");
    }
    Cus_UART1_Write_Text_Item(">>>>>>>>>>>>>>>>>>>>\r\n");
}

#endif
unsigned short is_row_full(MATRIX88* matrix, unsigned short row)
{
    unsigned short col;
    for(col = 0; col < MATRIX88_COLUMN_MAX; col++)
    {
        if(matrix->cell[row][col] == 0)
        {
            return 0;
        }
    }
    return 1;
}
void delete_row(MATRIX88* matrix, unsigned short row)
{
    short i;
    for(i = MATRIX88_ROW_MAX - 1; i >= 0; i--)
    {
        if(i <= row)
        {
            if(i > 0)
            {
#ifdef WINDOW_BASE
                size_t len;
#else
                int len;
#endif
                len = MATRIX88_COLUMN_MAX*sizeof(unsigned short);
                memcpy(matrix->cell[i], matrix->cell[i - 1], len);
            }
            else
            {
                memset(matrix->cell[i], 0, MATRIX88_COLUMN_MAX*sizeof(unsigned short));
            }
        }
    }
}
unsigned short delete_matrix(MATRIX88* matrix)
{
    unsigned short count = 0;
    short row = MATRIX88_ROW_MAX - 1;
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
#ifdef WINDOW_BASE
    fprintf(fp, "delete_matrix count = %d\n", count);
#else
#endif
    return count;
}
unsigned short is_row_empty(MATRIX88* matrix, unsigned short row)
{
    unsigned short col;
    for(col = 0; col < MATRIX88_COLUMN_MAX; col++)
    {
        if(matrix->cell[row][col] == 1)
        {
            return 0;
        }
    }
    return 1;
}
unsigned short is_col_empty(MATRIX88* matrix, unsigned short col)
{
    unsigned short row;
    for(row = 0; row < MATRIX88_ROW_MAX; row++)
    {
        if(matrix->cell[row][col] == 1)
        {
            return 0;
        }
    }
    return 1;
}
unsigned short hit_land1(short x, short y, const MATRIX44* matrix_44, MATRIX88* matrix_88)
{
#ifdef WINDOW_BASE
    fprintf(fp, "==============hit_land1============\n");
#else
#endif
    short row;
    short col;
    for(row = MATRIX44_ROW_MAX - 1; row >= 0; row--)
    {
        for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
        {
            if(matrix_44->cell[row][col] == 1)
            {
                if((y + row) >= (MATRIX88_ROW_MAX - 1))
                {
#ifdef WINDOW_BASE
                    fprintf(fp, "hit1 row = %d, col = %d\n", row, col);
#else
#endif
                    return 1;
                }

                if(matrix_88->cell[y + row + 1][x + col] == 1)
                {
#ifdef WINDOW_BASE
                    fprintf(fp, "hit2 row = %d, col = %d\n", row, col);
#else
#endif
                    return 1;
                }
            }
        }
    }
#ifdef WINDOW_BASE
    fprintf(fp, "not hit\n");
#else
#endif
    return 0;
}
unsigned short is_valid(short x, short y, const MATRIX44* matrix_44, MATRIX88* matrix_88)
{
#ifdef WINDOW_BASE
    fprintf(fp, "==============is_valid============\n");
#else
#endif
    short row;
    short col;
    for(row = MATRIX44_ROW_MAX - 1; row >= 0; row--)
    {
        for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
        {
            if(matrix_44->cell[row][col] == 1)
            {
                if(matrix_88->cell[y + row][x + col] == 1)
                {
#ifdef WINDOW_BASE
                    fprintf(fp, "not valid1 row = %d, col = %d\n", row, col);
#else
#endif
                    return 0;
                }

                if(( x + col < 0) || (x + col >= MATRIX88_COLUMN_MAX))
                {
#ifdef WINDOW_BASE
                    fprintf(fp, "not valid2 row = %d, col = %d\n", row, col);
#else
#endif
                    return 0;
                }
                if((y + row) > (MATRIX88_ROW_MAX - 1))
                {
#ifdef WINDOW_BASE
                    fprintf(fp, "not valid3 row = %d, col = %d\n", row, col);
#else
#endif
                    return 0;
                }
            }
        }
    }
#ifdef WINDOW_BASE
    fprintf(fp, "valid\n");
#else
#endif
    return 1;
}
unsigned short is_left_boundary(short x, const MATRIX44* matrix_44, MATRIX88* matrix_88)
{
    short row;
    short col;
    for(row = MATRIX44_ROW_MAX - 1; row >= 0; row--)
    {
        for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
        {
            if(matrix_44->cell[row][col] == 1)
            {
                if( x + col < 0)
                {
#ifdef WINDOW_BASE
                    fprintf(fp, "LEFT_OVER_BOUNDARY\n");
#else
#endif
                    return LEFT_OVER_BOUNDARY;
                }
            }
        }
    }
    return OK;
}
unsigned short is_right_boundary(short x, const MATRIX44* matrix_44, MATRIX88* matrix_88)
{
    short row;
    short col;
    for(row = MATRIX44_ROW_MAX - 1; row >= 0; row--)
    {
        for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
        {
            if(matrix_44->cell[row][col] == 1)
            {
                if(x + col > MATRIX88_COLUMN_MAX - 1)
                {
#ifdef WINDOW_BASE
                    fprintf(fp, "RIGHT_OVER_BOUNDARY\n");
#else
#endif
                    return RIGHT_OVER_BOUNDARY;
                }
            }
        }
    }
    return OK;
}
unsigned short fall_off(short x, short y, const MATRIX44* matrix_44, MATRIX88* matrix_88)
{
    while(1)
    {
        short row;
        short col;
        for(row = MATRIX44_ROW_MAX - 1; row >= 0; row--)
        {
            for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
            {
                if(matrix_44->cell[row][col] == 1)
                {
                    if(matrix_88->cell[y + row + 1][x + col] == 1)
                    {
#ifdef WINDOW_BASE
                        fprintf(fp, "fall_off1 x = %d, y = %d\n", x, y);
#else
#endif
                        return y;
                    }
                    if((y + row) >= (MATRIX88_ROW_MAX - 1))
                    {
#ifdef WINDOW_BASE
                        fprintf(fp, "fall_off2 x = %d, y = %d\n", x, y);
#else
#endif
                        return y;
                    }
                }
            }
        }
        y++;
    }
}
void clear(short x, short y, const MATRIX44* matrix_44, MATRIX88* matrix_88)
{
    unsigned short row;
    unsigned short col;
    for(row = 0; row < MATRIX44_ROW_MAX; row++)
    {
        for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
        {
            if(matrix_44->cell[row][col] == 1)
            {
                matrix_88->cell[y + row][x + col] = 0;
            }
        }
    }
}
void merge(short x, short y, const MATRIX44* matrix_44, MATRIX88* matrix_88)
{
    unsigned short row;
    unsigned short col;
    for(row = 0; row < MATRIX44_ROW_MAX; row++)
    {
        for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
        {
            if(matrix_44->cell[row][col] == 1)
            {
                matrix_88->cell[y + row][x + col] = 1;
            }
        }
    }
}
void merge1(short x, short y, const MATRIX44* matrix_44, MATRIX88* matrix88_in, MATRIX88* matrix88_out)
{
#ifdef WINDOW_BASE
    size_t len;
#else
    int len;
#endif
    unsigned short row;
    unsigned short col;

    len = sizeof(MATRIX88);
    memcpy(matrix88_out, matrix88_in, len);

    for(row = 0; row < MATRIX44_ROW_MAX; row++)
    {
        for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
        {
            if(matrix_44->cell[row][col] == 1)
            {
                matrix88_out->cell[y + row][x + col] = 1;
            }
        }
    }
}
unsigned int evaluate(MATRIX88* matrix)
{
    unsigned int risk = 0;
    unsigned short full = 0xFF;
    unsigned short col;
    short row;
    for(col = 0; col < MATRIX88_COLUMN_MAX; col++)
    {
        full = 0xFF;
        for(row = MATRIX88_ROW_MAX - 1; row >= 0; row--)
        {
            if(full == 0xFF)
            {
                full = matrix->cell[row][col];
            }
            else
            {
                if(matrix->cell[row][col] == 1)
                {
                    if(full == 0)
                    {
                        risk++;
                    }
                }
                full = matrix->cell[row][col];
            }
        }
    }
#ifdef WINDOW_BASE
    fprintf(fp, "risk = %d\n", risk);
#else
#endif

    return risk;
}
unsigned short char_info_index_rand()
{
    return (unsigned short)(rand()%CHARACTER_MAX);
}
short left_most(short x, const MATRIX44* matrix_44, MATRIX88* matrix_88)
{
    while(1)
    {
        if(is_left_boundary(x, matrix_44, matrix_88) == LEFT_OVER_BOUNDARY)
        {
#ifdef WINDOW_BASE
            fprintf(fp, "left_most = %d\n", x + 1);
#else
#endif
            return x + 1;
        }
        x--;
    }
}
short right_most(short x, const MATRIX44* matrix_44, MATRIX88* matrix_88)
{
    while(1)
    {
        if(is_right_boundary(x, matrix_44, matrix_88) == RIGHT_OVER_BOUNDARY)
        {
#ifdef WINDOW_BASE
            fprintf(fp, "right_most = %d\n", x - 1);
#else
#endif
            return x - 1;
        }
        x++;
    }
}
unsigned short get_high(MATRIX88* matrix)
{
    short row;
    for(row = MATRIX88_ROW_MAX - 1; row >= 0; row--)
    {
        if(is_row_empty(matrix, row) == 1)
        {
#ifdef WINDOW_BASE
            fprintf(fp, "get_high height = %d\n", MATRIX88_ROW_MAX - row - 1);
#else
#endif
            return (unsigned short)(MATRIX88_ROW_MAX - row - 1);
        }
    }
    return MATRIX88_ROW_MAX;
}
unsigned short get_high_after_merge(short y, const MATRIX44* matrix)
{
    short row;
    short col;
    for(row = 0; row < MATRIX44_ROW_MAX; row++)
    {
        for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
        {
            if(matrix->cell[row][col] == 1)
            {
#ifdef WINDOW_BASE
                fprintf(fp, "get_high_after_merge y = %d, row = %d, height = %d\n", y, row, MATRIX88_ROW_MAX - y - row);
#else
#endif
                return (unsigned short)(MATRIX88_ROW_MAX - y - row);
            }
        }
    }
}
unsigned short get_holes_after_merge(MATRIX88* matrix)
{
    short start = -1;
    short stop = -1;
    unsigned short num_hole = 0;
    short col;
    short row;
    for(col = 0; col < MATRIX88_COLUMN_MAX; col++)
    {
        start = stop = -1;
        for(row = 0; row < MATRIX88_ROW_MAX; row++)
        {
            if(col == 0)
            {
                if((matrix->cell[row][col] == 0) && (matrix->cell[row][col + 1] == 1))
                {
                    if(start == -1)
                    {
                        start = row;
                    }
                }
            }
            else if(col == MATRIX88_COLUMN_MAX - 1)
            {
                if((matrix->cell[row][col] == 0) && (matrix->cell[row][col - 1] == 1))
                {
                    if(start == -1)
                    {
                        start = row;
                    }
                }
            }
            else
            {
                if((matrix->cell[row][col] == 0) && (matrix->cell[row][col - 1] == 1) && (matrix->cell[row][col + 1] == 1))
                {
                    if(start == -1)
                    {
                        start = row;
                    }
                }
            }
            if(start >= 0)
            {
                if(row == MATRIX88_ROW_MAX - 1)
                {
                    if(stop == -1)
                    {
                        stop = MATRIX88_ROW_MAX;
                    }
                }
                else if(matrix->cell[row + 1][col] == 1)
                {
                    if(stop == -1)
                    {
                        stop = row + 1;
                    }
                }
            }

        }
        if((start >= 0) && (stop >= 0) && (stop - start >= 3))
        {
#ifdef WINDOW_BASE
            fprintf(fp, "col = %d, start = %d, stop = %d\n", col, start, stop);
#else
#endif
            num_hole++;
        }
    }
#ifdef WINDOW_BASE
    fprintf(fp, "num_hole = (%d)\n", num_hole);
#else
#endif
    return num_hole;
}
unsigned short find_best_solution()
{
    short temp_pre_x = 0xFF, tem_pre_sub_index = 0xFF;
    unsigned int temp_pre_risk = 0xFFFF;
    short temp_y;
    unsigned int temp_risk;
    unsigned short temp_count, temp_pre_count = 0;
    unsigned short temp_high, temp_pre_high = 0xFF;
    unsigned short temp_hole, temp_pre_hole = 0xFF;
    MATRIX88 temp_matrix88;
    unsigned short res = 0;
    short left_most_index, right_most_index;
    unsigned short tem_sub_index;

#ifdef WINDOW_BASE
    fprintf(fp, "==============find_best_solution============\n");
#else
//    Cus_UART1_Write_Text_Item("==============find_best_solution============\r\n");
    //    Cus_UART1_Write(10);
    //    Cus_UART1_Write(13);
        printf_console_MATRIX88("8", &g_matrix88);

#endif
#ifdef WINDOW_BASE
    fprintf(fp, "g_char_info_index = (%d), num = %d\n", g_char_info_index, g_char_info[g_char_info_index].num);
#else
        Cus_UART1_Write_Int("index", g_char_info_index);
#endif
    for(tem_sub_index = 0; tem_sub_index < g_char_info[g_char_info_index].num; tem_sub_index++)
    {
        short temp_x;
        left_most_index = left_most(cur_x, GET_TEMP_MAXTRIX44, &g_matrix88);
        right_most_index = right_most(cur_x, GET_TEMP_MAXTRIX44, &g_matrix88);

        for(temp_x = left_most_index; temp_x <= right_most_index; temp_x++)
        {
            temp_y = fall_off(temp_x, cur_y, GET_TEMP_MAXTRIX44, &g_matrix88);
            Cus_UART1_Write_Text_Item("2:");
            printf_console_MATRIX44(temp_x, temp_y, GET_TEMP_MAXTRIX44);
            printf_console_MATRIX88("2", &g_matrix88);
            printf_Screen();
            if(is_valid(temp_x, temp_y, GET_TEMP_MAXTRIX44, &g_matrix88) == 0)
            {
                continue;
            }
            res = 1;
            merge1(temp_x, temp_y, GET_TEMP_MAXTRIX44, &g_matrix88, &temp_matrix88);
            temp_count = delete_matrix(&temp_matrix88);
            temp_risk = evaluate(&temp_matrix88);
            temp_high = get_high_after_merge(temp_y, GET_TEMP_MAXTRIX44);
            temp_hole = get_holes_after_merge(&temp_matrix88);
#ifdef WINDOW_BASE
            printf_MATRIX88(&temp_matrix88);
#else
            printf_console_MATRIX88("3", &temp_matrix88);
#endif
            if(temp_count > temp_pre_count)
            {
#ifdef WINDOW_BASE
                fprintf(fp, "temp_count(%d) > temp_pre_count(%d)\n", temp_count, temp_pre_count);
#else
#endif
                temp_pre_count = temp_count;
                temp_pre_risk = temp_risk;
                temp_pre_high = temp_high;
                temp_pre_hole = temp_hole;
                tem_pre_sub_index = tem_sub_index;
                temp_pre_x = temp_x;
            }
            else if(temp_count == temp_pre_count)
            {
                if(get_high(&g_matrix88) <= MATRIX88_ROW_MAX/2 + 1)
                {
#ifdef WINDOW_BASE
                    fprintf(fp, "height <= (%d)\n", MATRIX88_ROW_MAX/2 + 1);

                    fprintf(fp, "temp_count(%d) == temp_pre_count(%d)\n", temp_count, temp_pre_count);
#else
#endif
                    if(temp_risk < temp_pre_risk)
                    {
#ifdef WINDOW_BASE
                        fprintf(fp, "temp_risk(%d) < temp_pre_risk(%d)\n", temp_risk, temp_pre_risk);
#else
#endif
                        temp_pre_count = temp_count;
                        temp_pre_risk = temp_risk;
                        temp_pre_high = temp_high;
                        temp_pre_hole = temp_hole;
                        tem_pre_sub_index = tem_sub_index;
                        temp_pre_x = temp_x;
                    }
                    else if(temp_risk == temp_pre_risk)
                    {
#ifdef WINDOW_BASE
                        fprintf(fp, "temp_risk(%d) == temp_pre_risk(%d)\n", temp_risk, temp_pre_risk);
#else
#endif
                        if(temp_high < temp_pre_high)
                        {
#ifdef WINDOW_BASE
                            fprintf(fp, "temp_high(%d) < temp_pre_high(%d)\n", temp_high, temp_pre_high);
#else
#endif
                            temp_pre_count = temp_count;
                            temp_pre_risk = temp_risk;
                            temp_pre_high = temp_high;
                            temp_pre_hole = temp_hole;
                            tem_pre_sub_index = tem_sub_index;
                            temp_pre_x = temp_x;
                        }
                        else if(temp_high == temp_pre_high)
                        {
#ifdef WINDOW_BASE
                            fprintf(fp, "temp_high(%d) == temp_pre_high(%d)\n", temp_high, temp_pre_high);
#else
#endif
                            if(temp_hole < temp_pre_hole)
                            {
#ifdef WINDOW_BASE
                                fprintf(fp, "temp_hole(%d) < temp_pre_hole(%d)\n", temp_hole, temp_pre_hole);
#else
#endif
                                temp_pre_count = temp_count;
                                temp_pre_risk = temp_risk;
                                temp_pre_high = temp_high;
                                temp_pre_hole = temp_hole;
                                tem_pre_sub_index = tem_sub_index;
                                temp_pre_x = temp_x;
                            }

                        }

                    }
                }
                else
                {
#ifdef WINDOW_BASE
                    fprintf(fp, "WARNING height > (%d)\n", MATRIX88_ROW_MAX/2 + 1);
                    fprintf(fp, "temp_high = %d, temp_pre_high = %d\n", temp_high, temp_pre_high);
#else
#endif
                    if(temp_high < temp_pre_high)
                    {
#ifdef WINDOW_BASE
                        fprintf(fp, "temp_high(%d) < temp_pre_high(%d)\n", temp_high, temp_pre_high);
#else
#endif
                        temp_pre_count = temp_count;
                        temp_pre_risk = temp_risk;
                        temp_pre_high = temp_high;
                        temp_pre_hole = temp_hole;
                        tem_pre_sub_index = tem_sub_index;
                        temp_pre_x = temp_x;
                    }
                    else if(temp_high == temp_pre_high)
                    {
#ifdef WINDOW_BASE
                        fprintf(fp, "temp_high(%d) == temp_pre_high(%d)\n", temp_high, temp_pre_high);
#else
#endif
                        if(temp_hole < temp_pre_hole)
                        {
#ifdef WINDOW_BASE
                            fprintf(fp, "temp_hole(%d) < temp_pre_hole(%d)\n", temp_hole, temp_pre_hole);
#else
#endif
                            temp_pre_count = temp_count;
                            temp_pre_risk = temp_risk;
                            temp_pre_high = temp_high;
                            temp_pre_hole = temp_hole;
                            tem_pre_sub_index = tem_sub_index;
                            temp_pre_x = temp_x;
                        }
                        else if(temp_hole == temp_pre_hole)
                        {
#ifdef WINDOW_BASE
                            fprintf(fp, "temp_hole(%d) == temp_pre_hole(%d)\n", temp_hole, temp_pre_hole);
#else
#endif
                            if(temp_risk < temp_pre_risk)
                            {
#ifdef WINDOW_BASE
                                fprintf(fp, "temp_risk(%d) < temp_pre_risk(%d)\n", temp_risk, temp_pre_risk);
#else
#endif
                                temp_pre_count = temp_count;
                                temp_pre_risk = temp_risk;
                                temp_pre_high = temp_high;
                                temp_pre_hole = temp_hole;
                                tem_pre_sub_index = tem_sub_index;
                                temp_pre_x = temp_x;
                            }
                        }
                    }
                }
            }
#ifdef WINDOW_BASE
            fprintf(fp, "sub_index = %d, temp_pre_x = %d, temp_pre_count = %d, temp_pre_risk = %d, temp_pre_high = %d, temp_hole = %d\n",
                    tem_pre_sub_index, temp_pre_x, temp_pre_count, temp_pre_risk, temp_pre_high, temp_hole);
            //            system("PAUSE");
#else
#endif
        }
    }
    if(res == 1)
    {
        g_char_info_sub_index = tem_pre_sub_index;
        cur_x = temp_pre_x;
        Cus_UART1_Write_Text_Item("4:");
        printf_console_cur_MATRIX44(cur_x, cur_y);
        printf_console_MATRIX88("4", &temp_matrix88);
#ifdef WINDOW_BASE

        fprintf(fp, "chosen sub_index = %d, temp_pre_x = %d, temp_pre_count = %d, temp_pre_risk = %d, temp_pre_high = %d, temp_pre_hole = %d\n",
                tem_pre_sub_index, temp_pre_x, temp_pre_count, temp_pre_risk, temp_pre_high, temp_pre_hole);
#else
#endif
    }
    else
    {
#ifdef WINDOW_BASE
        fprintf(fp, "GAME OVER!!!\n");
#else
        Cus_UART1_Write_Text_Item("GAME OVER!!!\r\n");
#endif
    }
    return res;
}
#ifdef WINDOW_BASE
void test_is_row_full(const MATRIX88* matrix)
{
    for(unsigned short row = 0; row < MATRIX88_ROW_MAX; row++)
    {
        fprintf(fp, "row[%d] is %s\n", row, is_row_full(matrix, row) == 0 ? "not full" : "full");
    }
}
void test_is_row_empty(const MATRIX88* matrix)
{
    for(unsigned short row = 0; row < MATRIX88_ROW_MAX; row++)
    {
        fprintf(fp, "row[%d] is %s\n", row, is_row_empty(matrix, row) == 0 ? "not empty" : "empty");
    }
}
void test_is_col_empty(const MATRIX88* matrix)
{
    for(unsigned short col = 0; col < MATRIX88_COLUMN_MAX; col++)
    {
        fprintf(fp, "col[%d] is %s\n", col, is_col_empty(matrix, col) == 0 ? "not empty" : "empty");
    }
}
void test_hit_land()
{
    short x = 5, y = 6;
    MATRIX44* matrix_44 = get_MATRIX44(1, 0);
    MATRIX88 matrix_88 =
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
    printf_console_MATRIX44(x, y, matrix_44);
    printf_MATRIX88(&matrix_88);
    hit_land1(x, y, matrix_44, &matrix_88);
}
void test_is_valid()
{
    short x = 5, y = 7;
    MATRIX44* matrix_44 = get_MATRIX44(1, 0);
    MATRIX88 matrix_88 =
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
    printf_console_MATRIX44(x, y, matrix_44);
    printf_MATRIX88(&matrix_88);
    is_valid(x, y, matrix_44, &matrix_88);
}
void test_find_best_solution()
{
    g_char_info_index = 1;
    find_best_solution();
}
void test_get_holes_after_merge()
{
    MATRIX88 matrix_88 =
    {
            0,    0,    0,    0,    0,    0,    0,    0,
            0,    0,    0,    0,    0,    0,    0,    0,
            0,    0,    0,    0,    0,    0,    0,    0,
            0,    0,    0,    0,    0,    0,    1,    0,
            0,    0,    1,    0,    1,    0,    1,    0,
            0,    1,    1,    0,    1,    0,    1,    0,
            0,    1,    1,    0,    1,    0,    1,    0,
            0,    1,    1,    1,    1,    1,    1,    0,
    };
    printf_MATRIX88(&matrix_88);
    get_holes_after_merge(&matrix_88);
}
#endif
void test()
{
    printf_console_MATRIX88("8", &g_matrix88);
}
// Here we have the main function.
int main()
{
    unsigned short hit_res;
#ifdef WINDOW_BASE
    //////////////////////////////////////////////
    fp = fopen("debug.txt", "w");
    if(fp==NULL)
    {
        fprintf(fp, "File Not Found");
        exit(-1);
    }

    //////////////////////////////////////////////
    //    (&g_matrix44[0]);
    //    printf_Screen();
    //    get_high(&g_matrix88);
    //    delete_matrix(&g_matrix88);
    //    printf_Screen();printf_console_MATRIX44
    //    evaluate(&g_matrix88);
    //      g_char_info_index = 8;
    //      find_best_solution();
    //        printf_Screen();
    //    test_get_holes_after_merge();
    //    printf_all_MATRIX44();
    //    goto __exit;
    srand(time(NULL));
#else
    Chip_Select_Direction = 0;    // Set RA2 pin as output.
//    SPI1_init();                  // Initialize SPI1 module.
//
//    max7219_init1(); // initialize  max7219.
    srand(0);

    UART1_Init(9600);
    Delay_ms(1000);
#endif
    __start:
//    printf_Screen();
//    printf_console_MATRIX88("5", &g_matrix88);
    //    Delay_ms(1000);
    /*Cus_UART1_Write_Text("Hello\r\n");
//    Cus_UART1_Write(10);
//    Cus_UART1_Write(13);
//    sprinti(g_debug, "%X", 65);
    IntToStr(65, g_debug);
    Cus_UART1_Write_Text(g_debug);
    Cus_UART1_Write(10);
    Cus_UART1_Write(13);*/
    g_char_info_index = 7;
    g_char_info_sub_index = 0;
    //    Cus_UART1_Write_Text("index:");
    //    IntToStr(g_char_info_index, g_debug);
    //    Cus_UART1_Write_Text(g_debug);
    //    Cus_UART1_Write(10);
    //    Cus_UART1_Write(13);
    //
    //    Cus_UART1_Write_Text("sub index:");
    //    IntToStr(g_char_info_sub_index, g_debug);
    //    Cus_UART1_Write_Text(g_debug);
    //    Cus_UART1_Write(10);
    //    Cus_UART1_Write(13);
    //    printf_console_cur_MATRIX44(cur_x, cur_y);
    //    find_best_solution();
//    printf_console_MATRIX88("7", &g_matrix88);

    find_best_solution();
//    test();
    printf_console_MATRIX88("6", &g_matrix88);
        while(1)
        {
            Delay_ms(100);
        }
//    while(1)
//    {
//        cur_y = 0;
//        cur_x = 2, cur_y = 0;
//        g_char_info_index = char_info_index_rand();
//
//#ifdef WINDOW_BASE
//        fprintf(fp, "g_char_info_index = %d\n", g_char_info_index);
//#else
////        Cus_UART1_Write_Text("g_char_info_index:");
////        IntToStr(g_char_info_index, g_debug);
////        Cus_UART1_Write_Text(g_debug);
////        Cus_UART1_Write(10);
////        Cus_UART1_Write(13);
//#endif
//        if(find_best_solution() == 0)
//        {
//#ifdef WINDOW_BASE
//            printf("GAME OVER!!!\n");
//#else
//            Cus_UART1_Write_Text("GAME OVER!!!\r\n");
//#endif
//            goto __start;
//        }
//        while(1)
//        {
//            hit_res = hit_land1(cur_x, cur_y, GET_CUR_MAXTRIX44, &g_matrix88);
//#ifdef WINDOW_BASE
//            fprintf(fp, "hit_res = %d\n", hit_res);
//#else
////            Cus_UART1_Write_Text("hit_res:");
////            IntToStr(hit_res, g_debug);
////            Cus_UART1_Write_Text(g_debug);
////            Cus_UART1_Write(10);
////            Cus_UART1_Write(13);
//#endif
//            merge(cur_x, cur_y, GET_CUR_MAXTRIX44, &g_matrix88);
//            if(hit_res == 1)
//            {
//                printf_Screen();
//#ifdef WINDOW_BASE
//                Sleep(100);
//#else
//                Delay_ms(100);
//#endif
//                delete_matrix(&g_matrix88);
//            }
//#ifdef WINDOW_BASE
//            fprintf(fp, "printf_console_MATRIX88\n");
//#else
//            //            Cus_UART1_Write_Text("printf_console_MATRIX88\r\n");
//#endif
//            Cus_UART1_Write_Text("1:");
//            printf_console_MATRIX88(&g_matrix88);
//            printf_Screen();
//            if(hit_res == 0)
//            {
//                clear(cur_x, cur_y, GET_CUR_MAXTRIX44, &g_matrix88);
//            }
//            else
//            {
//                break;
//            }
//#ifdef WINDOW_BASE
//            Sleep(1000);
//#else
//            Delay_ms(1000);
//#endif
//            cur_y++;
//        }
//    }
//    __exit:
//
//#ifdef WINDOW_BASE
//    fclose(fp);
//    system("PAUSE");
//    return EXIT_SUCCESS;
//#else
//    return 0;
//#endif
}
