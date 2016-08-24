#line 1 "D:/Working/working/MyLocalRepositorywc/Teris_16f886_mikroC/mikroC/Teris.c"
#line 42 "D:/Working/working/MyLocalRepositorywc/Teris_16f886_mikroC/mikroC/Teris.c"
typedef struct
{
 unsigned short start_index;
 unsigned short num;
} CHARACTER_INFO;
typedef struct
{
 unsigned short cell[ 4 ][ 4 ];
} MATRIX44;
typedef struct
{
 unsigned short cell[ 8 ][ 8 ];
} MATRIX88;

typedef struct
{
 unsigned short col[ 8 ];
} MATRIX7219;

typedef enum
{
 OK,
 GAME_OVER,
 LEFT_OVER_BOUNDARY,
 RIGHT_OVER_BOUNDARY,
 HIT_LAND
};

const CHARACTER_INFO g_char_info[ 9 ] =
{

{0, 2},

{2, 2},

{4, 2},

{6, 4},

{10, 4},

{14, 1},

{15, 4},

{19, 1},

{20, 4},
};
unsigned short g_char_info_index;
unsigned short g_char_info_sub_index;
char g_debug[12];
MATRIX44 g_cur_matrix44;



 const MATRIX44 g_matrix44[] =

{

{0, 1, 0, 0,
0, 1, 0, 0,
0, 1, 0, 0,
0, 1, 0, 0},
{0, 0, 0, 0,
1, 1, 1, 1,
0, 0, 0, 0,
0, 0, 0, 0},

{0, 1, 1, 0,
1, 1, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0},
{0, 1, 0, 0,
0, 1, 1, 0,
0, 0, 1, 0,
0, 0, 0, 0},

{1, 1, 0, 0,
0, 1, 1, 0,
0, 0, 0, 0,
0, 0, 0, 0},
{0, 1, 0, 0,
1, 1, 0, 0,
1, 0, 0, 0,
0, 0, 0, 0},

{0, 0, 0, 0,
1, 1, 1, 0,
0, 0, 1, 0,
0, 0, 0, 0},
{0, 1, 1, 0,
0, 1, 0, 0,
0, 1, 0, 0,
0, 0, 0, 0},
{1, 0, 0, 0,
1, 1, 1, 0,
0, 0, 0, 0,
0, 0, 0, 0},
{0, 1, 0, 0,
0, 1, 0, 0,
1, 1, 0, 0,
0, 0, 0, 0},

{0, 0, 0, 0,
1, 1, 1, 0,
1, 0, 0, 0,
0, 0, 0, 0},
{1, 1, 0, 0,
0, 1, 0, 0,
0, 1, 0, 0,
0, 0, 0, 0},
{0, 0, 1, 0,
1, 1, 1, 0,
0, 0, 0, 0,
0, 0, 0, 0},
{0, 1, 0, 0,
0, 1, 0, 0,
0, 1, 1, 0,
0, 0, 0, 0},

{0, 1, 1, 0,
0, 1, 1, 0,
0, 0, 0, 0,
0, 0, 0, 0},

{0, 0, 0, 0,
0, 1, 1, 0,
0, 1, 0, 0,
0, 0, 0, 0},
{0, 0, 0, 0,
1, 1, 0, 0,
0, 1, 0, 0,
0, 0, 0, 0},
{0, 1, 0, 0,
1, 1, 0, 0,
0, 0, 0, 0,
0, 0, 0, 0},
{0, 1, 0, 0,
0, 1, 1, 0,
0, 0, 0, 0,
0, 0, 0, 0},

{0, 1, 0, 0,
1, 1, 1, 0,
0, 1, 0, 0,
0, 0, 0, 0},

{1, 1, 1, 0,
0, 1, 0, 0,
0, 1, 0, 0,
0, 0, 0, 0},
{0, 0, 1, 0,
1, 1, 1, 0,
0, 0, 1, 0,
0, 0, 0, 0},
{0, 1, 0, 0,
0, 1, 0, 0,
1, 1, 1, 0,
0, 0, 0, 0},
{1, 0, 0, 0,
1, 1, 1, 0,
1, 0, 0, 0,
0, 0, 0, 0},
};
MATRIX88 g_matrix88 =
{
 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0,
};
short cur_x = 2;
short cur_y = 0;
#line 227 "D:/Working/working/MyLocalRepositorywc/Teris_16f886_mikroC/mikroC/Teris.c"
sbit Chip_Select at RA2_bit;
sbit Chip_Select_Direction at TRISA2_bit;



void max7219_init1()
{
 Chip_Select = 0;
 SPI1_write(0x09);
 SPI1_write(0x00);
 Chip_Select = 1;

 Chip_Select = 0;
 SPI1_write(0x0A);
 SPI1_write(0x0F);
 Chip_Select = 1;

 Chip_Select = 0;
 SPI1_write(0x0B);
 SPI1_write(0x07);
 Chip_Select = 1;

 Chip_Select = 0;
 SPI1_write(0x0C);
 SPI1_write(0x01);
 Chip_Select = 1;

 Chip_Select = 0;
 SPI1_write(0x00);
 SPI1_write(0xFF);
 Chip_Select = 1;
}


void Write_Byte(unsigned short myColumn, unsigned short myValue)
{
 Chip_Select = 0;
 SPI1_write(myColumn);
 SPI1_write(myValue);
 Chip_Select = 1;
}
#line 341 "D:/Working/working/MyLocalRepositorywc/Teris_16f886_mikroC/mikroC/Teris.c"
void printf_MATRIX7219(MATRIX7219* matrix)
{
 unsigned short col;

 for (col = 0; col <  8 ; col++)
 {
 Write_Byte(col + 1, matrix->col[col]);
 }
}

void MATRIX88_to_MATRIX7219(MATRIX88* matrix_88, MATRIX7219* matrix_7219)
{
 unsigned short mask = 0x80;
 unsigned short col;
 for(col = 0; col <  8 ; col++)
 {
 unsigned short row;
 mask = 0x80;
 matrix_7219->col[col] = 0;
 for(row = 0; row <  8 ; row++)
 {
 if(matrix_88->cell[row][col] == 1)
 {
 matrix_7219->col[col] |= mask;
 }
 mask >>= 1;
 }
 }
}
#line 393 "D:/Working/working/MyLocalRepositorywc/Teris_16f886_mikroC/mikroC/Teris.c"
void printf_MATRIX88(MATRIX88* matrix_88)
{
 MATRIX7219 matrix_7219;
 MATRIX88_to_MATRIX7219(matrix_88, &matrix_7219);
 printf_MATRIX7219(&matrix_7219);
}

void printf_Screen()
{
 printf_MATRIX88(&g_matrix88);
}

void Clear_Matrix(void)
{
 memset(&g_matrix88, 0, sizeof(MATRIX88));
 printf_Screen();
}
#line 433 "D:/Working/working/MyLocalRepositorywc/Teris_16f886_mikroC/mikroC/Teris.c"
void printf_console_MATRIX88(MATRIX88* matrix)
{
 unsigned short row;
 unsigned short col;
 UART1_Write_Text("<<<<<<<<<<<<<<<<<<<<\r\n");
 for(row = 0; row <  8 ; row++)
 {
 for(col = 0; col <  8 ; col++)
 {
 if(matrix->cell[row][col] == 1)
 {
 UART1_Write_Text("*");
 }
 else
 {
 UART1_Write_Text("_");
 }
 }
 UART1_Write_Text("\r\n");
 }
 UART1_Write_Text(">>>>>>>>>>>>>>>>>>>>\r\n");
}


unsigned short is_row_full(MATRIX88* matrix, unsigned short row)
{
 unsigned short col;
 for(col = 0; col <  8 ; col++)
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
 for(i =  8  - 1; i >= 0; i--)
 {
 if(i <= row)
 {
 if(i > 0)
 {



 int len;

 len =  8 *sizeof(unsigned short);
 memcpy(matrix->cell[i], matrix->cell[i - 1], len);
 }
 else
 {
 memset(matrix->cell[i], 0,  8 *sizeof(unsigned short));
 }
 }
 }
}
unsigned short delete_matrix(MATRIX88* matrix)
{
 unsigned short count = 0;
 short row =  8  - 1;
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




 return count;
}
unsigned short is_row_empty(MATRIX88* matrix, unsigned short row)
{
 unsigned short col;
 for(col = 0; col <  8 ; col++)
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
 for(row = 0; row <  8 ; row++)
 {
 if(matrix->cell[row][col] == 1)
 {
 return 0;
 }
 }
 return 1;
}
unsigned short hit_land1(short x, short y, MATRIX44* matrix_44, MATRIX88* matrix_88)
{




 short row;
 short col;
 for(row =  4  - 1; row >= 0; row--)
 {
 for(col = 0; col <  4 ; col++)
 {
 if(matrix_44->cell[row][col] == 1)
 {
 if((y + row) >= ( 8  - 1))
 {




 return 1;
 }

 if(matrix_88->cell[y + row + 1][x + col] == 1)
 {




 return 1;
 }
 }
 }
 }




 return 0;
}
unsigned short is_valid(short x, short y, MATRIX44* matrix_44, MATRIX88* matrix_88)
{




 short row;
 short col;
 for(row =  4  - 1; row >= 0; row--)
 {
 for(col = 0; col <  4 ; col++)
 {
 if(matrix_44->cell[row][col] == 1)
 {
 if(matrix_88->cell[y + row][x + col] == 1)
 {




 return 0;
 }

 if(( x + col < 0) || (x + col >=  8 ))
 {




 return 0;
 }
 if((y + row) > ( 8  - 1))
 {




 return 0;
 }
 }
 }
 }




 return 1;
}
unsigned short is_left_boundary(short x, MATRIX44* matrix_44, MATRIX88* matrix_88)
{
 short row;
 short col;
 for(row =  4  - 1; row >= 0; row--)
 {
 for(col = 0; col <  4 ; col++)
 {
 if(matrix_44->cell[row][col] == 1)
 {
 if( x + col < 0)
 {




 return LEFT_OVER_BOUNDARY;
 }
 }
 }
 }
 return OK;
}
unsigned short is_right_boundary(short x, MATRIX44* matrix_44, MATRIX88* matrix_88)
{
 short row;
 short col;
 for(row =  4  - 1; row >= 0; row--)
 {
 for(col = 0; col <  4 ; col++)
 {
 if(matrix_44->cell[row][col] == 1)
 {
 if(x + col >  8  - 1)
 {




 return RIGHT_OVER_BOUNDARY;
 }
 }
 }
 }
 return OK;
}
unsigned short fall_off(short x, short y, MATRIX44* matrix_44, MATRIX88* matrix_88)
{
 while(1)
 {
 short row;
 short col;
 for(row =  4  - 1; row >= 0; row--)
 {
 for(col = 0; col <  4 ; col++)
 {
 if(matrix_44->cell[row][col] == 1)
 {
 if(matrix_88->cell[y + row + 1][x + col] == 1)
 {




 return y;
 }
 if((y + row) >= ( 8  - 1))
 {




 return y;
 }
 }
 }
 }
 y++;
 }
}
void clear(short x, short y, MATRIX44* matrix_44, MATRIX88* matrix_88)
{
 unsigned short row;
 unsigned short col;
 for(row = 0; row <  4 ; row++)
 {
 for(col = 0; col <  4 ; col++)
 {
 if(matrix_44->cell[row][col] == 1)
 {
 matrix_88->cell[y + row][x + col] = 0;
 }
 }
 }
}
void merge(short x, short y, MATRIX44* matrix_44, MATRIX88* matrix_88)
{
 unsigned short row;
 unsigned short col;
 for(row = 0; row <  4 ; row++)
 {
 for(col = 0; col <  4 ; col++)
 {
 if(matrix_44->cell[row][col] == 1)
 {
 matrix_88->cell[y + row][x + col] = 1;
 }
 }
 }
}
void merge1(short x, short y, MATRIX44* matrix_44, MATRIX88* matrix88_in, MATRIX88* matrix88_out)
{



 int len;

 unsigned short row;
 unsigned short col;

 len = sizeof(MATRIX88);
 memcpy(matrix88_out, matrix88_in, len);

 for(row = 0; row <  4 ; row++)
 {
 for(col = 0; col <  4 ; col++)
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
 for(col = 0; col <  8 ; col++)
 {
 full = 0xFF;
 for(row =  8  - 1; row >= 0; row--)
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





 return risk;
}
unsigned short char_info_index_rand()
{
 return (unsigned short)(rand()% 9 );
}
short left_most(short x, MATRIX44* matrix_44, MATRIX88* matrix_88)
{
 while(1)
 {
 if(is_left_boundary(x, matrix_44, matrix_88) == LEFT_OVER_BOUNDARY)
 {




 return x + 1;
 }
 x--;
 }
}
short right_most(short x, MATRIX44* matrix_44, MATRIX88* matrix_88)
{
 while(1)
 {
 if(is_right_boundary(x, matrix_44, matrix_88) == RIGHT_OVER_BOUNDARY)
 {




 return x - 1;
 }
 x++;
 }
}
unsigned short get_high(MATRIX88* matrix)
{
 short row;
 for(row =  8  - 1; row >= 0; row--)
 {
 if(is_row_empty(matrix, row) == 1)
 {




 return (unsigned short)( 8  - row - 1);
 }
 }
 return  8 ;
}
unsigned short get_high_after_merge(short y, MATRIX44* matrix)
{
 short row;
 short col;
 for(row = 0; row <  4 ; row++)
 {
 for(col = 0; col <  4 ; col++)
 {
 if(matrix->cell[row][col] == 1)
 {




 return (unsigned short)( 8  - y - row);
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
 for(col = 0; col <  8 ; col++)
 {
 start = stop = -1;
 for(row = 0; row <  8 ; row++)
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
 else if(col ==  8  - 1)
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
 if(row ==  8  - 1)
 {
 if(stop == -1)
 {
 stop =  8 ;
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




 num_hole++;
 }
 }




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
 MATRIX44 temp_cur_matrix44;
 MATRIX88 temp_matrix88;
 unsigned short res = 0;
 short left_most_index, right_most_index;





 unsigned short tem_sub_index;
 for(tem_sub_index = 0; tem_sub_index < g_char_info[g_char_info_index].num; tem_sub_index++)
 {
 short temp_x;
 temp_cur_matrix44 = g_matrix44[g_char_info[g_char_info_index].start_index + tem_sub_index];
 left_most_index = left_most(cur_x, &temp_cur_matrix44, &g_matrix88);
 right_most_index = right_most(cur_x, &temp_cur_matrix44, &g_matrix88);

 for(temp_x = left_most_index; temp_x <= right_most_index; temp_x++)
 {
 temp_y = fall_off(temp_x, cur_y, &temp_cur_matrix44, &g_matrix88);





 if(is_valid(temp_x, temp_y, &temp_cur_matrix44, &g_matrix88) == 0)
 {
 continue;
 }
 res = 1;
 merge1(temp_x, temp_y, &temp_cur_matrix44, &g_matrix88, &temp_matrix88);
 temp_count = delete_matrix(&temp_matrix88);
 temp_risk = evaluate(&temp_matrix88);
 temp_high = get_high_after_merge(temp_y, &temp_cur_matrix44);
 temp_hole = get_holes_after_merge(&temp_matrix88);




 if(temp_count > temp_pre_count)
 {




 temp_pre_count = temp_count;
 temp_pre_risk = temp_risk;
 temp_pre_high = temp_high;
 temp_pre_hole = temp_hole;
 tem_pre_sub_index = tem_sub_index;
 temp_pre_x = temp_x;
 }
 else if(temp_count == temp_pre_count)
 {
 if(get_high(&g_matrix88) <=  8 /2 + 1)
 {






 if(temp_risk < temp_pre_risk)
 {




 temp_pre_count = temp_count;
 temp_pre_risk = temp_risk;
 temp_pre_high = temp_high;
 temp_pre_hole = temp_hole;
 tem_pre_sub_index = tem_sub_index;
 temp_pre_x = temp_x;
 }
 else if(temp_risk == temp_pre_risk)
 {




 if(temp_high < temp_pre_high)
 {




 temp_pre_count = temp_count;
 temp_pre_risk = temp_risk;
 temp_pre_high = temp_high;
 temp_pre_hole = temp_hole;
 tem_pre_sub_index = tem_sub_index;
 temp_pre_x = temp_x;
 }
 else if(temp_high == temp_pre_high)
 {




 if(temp_hole < temp_pre_hole)
 {




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





 if(temp_high < temp_pre_high)
 {




 temp_pre_count = temp_count;
 temp_pre_risk = temp_risk;
 temp_pre_high = temp_high;
 temp_pre_hole = temp_hole;
 tem_pre_sub_index = tem_sub_index;
 temp_pre_x = temp_x;
 }
 else if(temp_high == temp_pre_high)
 {




 if(temp_hole < temp_pre_hole)
 {




 temp_pre_count = temp_count;
 temp_pre_risk = temp_risk;
 temp_pre_high = temp_high;
 temp_pre_hole = temp_hole;
 tem_pre_sub_index = tem_sub_index;
 temp_pre_x = temp_x;
 }
 else if(temp_hole == temp_pre_hole)
 {




 if(temp_risk < temp_pre_risk)
 {




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






 }
 }
 if(res == 1)
 {
 g_char_info_sub_index = tem_pre_sub_index;
 cur_x = temp_pre_x;







 }
 else
 {




 }
 return res;
}
#line 1246 "D:/Working/working/MyLocalRepositorywc/Teris_16f886_mikroC/mikroC/Teris.c"
int main()
{
 unsigned short hit_res;
#line 1273 "D:/Working/working/MyLocalRepositorywc/Teris_16f886_mikroC/mikroC/Teris.c"
 Chip_Select_Direction = 0;
 SPI1_init();

 max7219_init1();
 srand(0);

 UART1_Init(9600);

__start:
 printf_console_MATRIX88(&g_matrix88);
 printf_Screen();
 Delay_ms(1000);



 while(1)
 {
 cur_y = 0;
 cur_x = 2, cur_y = 0;
 g_char_info_index = 0;




 sprintl(g_debug, "%d\r\n", g_char_info_index);
 UART1_Write_Text(g_debug);

 if(find_best_solution() == 0)
 {



 UART1_Write_Text("GAME OVER!!!\r\n");

 goto __start;
 }
 g_cur_matrix44 = g_matrix44[g_char_info[g_char_info_index].start_index + g_char_info_sub_index];
 while(1)
 {
 hit_res = hit_land1(cur_x, cur_y, &g_cur_matrix44, &g_matrix88);



 sprinti(g_debug, "hit_res = %d\r\n", hit_res);
 UART1_Write_Text(g_debug);

 merge(cur_x, cur_y, &g_cur_matrix44, &g_matrix88);
 if(hit_res == 1)
 {
 printf_Screen();



 Delay_ms(100);

 delete_matrix(&g_matrix88);
 }



 UART1_Write_Text("printf_console_MATRIX88\r\n");

 printf_console_MATRIX88(&g_matrix88);
 printf_Screen();
 if(hit_res == 0)
 {
 clear(cur_x, cur_y, &g_cur_matrix44, &g_matrix88);
 }
 else
 {
 break;
 }



 Delay_ms(1000);

 cur_y++;
 }
 }
__exit:






 return 0;

}
