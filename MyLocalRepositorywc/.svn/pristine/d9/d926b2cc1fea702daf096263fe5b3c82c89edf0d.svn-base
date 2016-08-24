
_max7219_init1:

;Teris.c,232 :: 		void max7219_init1()
;Teris.c,234 :: 		Chip_Select = 0;       // SELECT MAX
	BCF        RA2_bit+0, 2
;Teris.c,235 :: 		SPI1_write(0x09);      // BCD mode for digit decoding
	MOVLW      9
	MOVWF      FARG_SPI1_Write_data_+0
	CALL       _SPI1_Write+0
;Teris.c,236 :: 		SPI1_write(0x00);
	CLRF       FARG_SPI1_Write_data_+0
	CALL       _SPI1_Write+0
;Teris.c,237 :: 		Chip_Select = 1;       // DESELECT MAX
	BSF        RA2_bit+0, 2
;Teris.c,239 :: 		Chip_Select = 0;       // SELECT MAX
	BCF        RA2_bit+0, 2
;Teris.c,240 :: 		SPI1_write(0x0A);
	MOVLW      10
	MOVWF      FARG_SPI1_Write_data_+0
	CALL       _SPI1_Write+0
;Teris.c,241 :: 		SPI1_write(0x0F);      // Segment luminosity intensity
	MOVLW      15
	MOVWF      FARG_SPI1_Write_data_+0
	CALL       _SPI1_Write+0
;Teris.c,242 :: 		Chip_Select = 1;       // DESELECT MAX
	BSF        RA2_bit+0, 2
;Teris.c,244 :: 		Chip_Select = 0;       // SELECT MAX
	BCF        RA2_bit+0, 2
;Teris.c,245 :: 		SPI1_write(0x0B);
	MOVLW      11
	MOVWF      FARG_SPI1_Write_data_+0
	CALL       _SPI1_Write+0
;Teris.c,246 :: 		SPI1_write(0x07);      // Display refresh
	MOVLW      7
	MOVWF      FARG_SPI1_Write_data_+0
	CALL       _SPI1_Write+0
;Teris.c,247 :: 		Chip_Select = 1;       // DESELECT MAX
	BSF        RA2_bit+0, 2
;Teris.c,249 :: 		Chip_Select = 0;       // SELECT MAX
	BCF        RA2_bit+0, 2
;Teris.c,250 :: 		SPI1_write(0x0C);
	MOVLW      12
	MOVWF      FARG_SPI1_Write_data_+0
	CALL       _SPI1_Write+0
;Teris.c,251 :: 		SPI1_write(0x01);      // Turn on the display
	MOVLW      1
	MOVWF      FARG_SPI1_Write_data_+0
	CALL       _SPI1_Write+0
;Teris.c,252 :: 		Chip_Select = 1;       // DESELECT MAX
	BSF        RA2_bit+0, 2
;Teris.c,254 :: 		Chip_Select = 0;       // SELECT MAX
	BCF        RA2_bit+0, 2
;Teris.c,255 :: 		SPI1_write(0x00);
	CLRF       FARG_SPI1_Write_data_+0
	CALL       _SPI1_Write+0
;Teris.c,256 :: 		SPI1_write(0xFF);      // No test
	MOVLW      255
	MOVWF      FARG_SPI1_Write_data_+0
	CALL       _SPI1_Write+0
;Teris.c,257 :: 		Chip_Select = 1;       // DESELECT MAX
	BSF        RA2_bit+0, 2
;Teris.c,258 :: 		}
L_end_max7219_init1:
	RETURN
; end of _max7219_init1

_Write_Byte:

;Teris.c,261 :: 		void Write_Byte(unsigned short myColumn, unsigned short myValue)
;Teris.c,263 :: 		Chip_Select = 0;       // select max7219.
	BCF        RA2_bit+0, 2
;Teris.c,264 :: 		SPI1_write(myColumn);  // send myColumn value to max7219 (digit place).
	MOVF       FARG_Write_Byte_myColumn+0, 0
	MOVWF      FARG_SPI1_Write_data_+0
	CALL       _SPI1_Write+0
;Teris.c,265 :: 		SPI1_write(myValue);   // send myValue value to max7219 (digit place).
	MOVF       FARG_Write_Byte_myValue+0, 0
	MOVWF      FARG_SPI1_Write_data_+0
	CALL       _SPI1_Write+0
;Teris.c,266 :: 		Chip_Select = 1;       // deselect max7219.
	BSF        RA2_bit+0, 2
;Teris.c,267 :: 		}
L_end_Write_Byte:
	RETURN
; end of _Write_Byte

_printf_MATRIX7219:

;Teris.c,341 :: 		void printf_MATRIX7219(MATRIX7219* matrix)
;Teris.c,345 :: 		for (col = 0; col < MATRIX88_COLUMN_MAX; col++)
	CLRF       printf_MATRIX7219_col_L0+0
L_printf_MATRIX72190:
	MOVLW      8
	SUBWF      printf_MATRIX7219_col_L0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_printf_MATRIX72191
;Teris.c,347 :: 		Write_Byte(col + 1, matrix->col[col]);
	INCF       printf_MATRIX7219_col_L0+0, 0
	MOVWF      FARG_Write_Byte_myColumn+0
	MOVF       printf_MATRIX7219_col_L0+0, 0
	ADDWF      FARG_printf_MATRIX7219_matrix+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	MOVWF      FARG_Write_Byte_myValue+0
	CALL       _Write_Byte+0
;Teris.c,345 :: 		for (col = 0; col < MATRIX88_COLUMN_MAX; col++)
	INCF       printf_MATRIX7219_col_L0+0, 1
;Teris.c,348 :: 		}
	GOTO       L_printf_MATRIX72190
L_printf_MATRIX72191:
;Teris.c,349 :: 		}
L_end_printf_MATRIX7219:
	RETURN
; end of _printf_MATRIX7219

_MATRIX88_to_MATRIX7219:

;Teris.c,351 :: 		void MATRIX88_to_MATRIX7219(MATRIX88* matrix_88, MATRIX7219* matrix_7219)
;Teris.c,353 :: 		unsigned short mask = 0x80;
	MOVLW      128
	MOVWF      MATRIX88_to_MATRIX7219_mask_L0+0
;Teris.c,355 :: 		for(col = 0; col < MATRIX88_ROW_MAX; col++)
	CLRF       R3+0
L_MATRIX88_to_MATRIX72193:
	MOVLW      8
	SUBWF      R3+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_MATRIX88_to_MATRIX72194
;Teris.c,358 :: 		mask = 0x80;
	MOVLW      128
	MOVWF      MATRIX88_to_MATRIX7219_mask_L0+0
;Teris.c,359 :: 		matrix_7219->col[col] = 0;
	MOVF       R3+0, 0
	ADDWF      FARG_MATRIX88_to_MATRIX7219_matrix_7219+0, 0
	MOVWF      FSR
	CLRF       INDF+0
;Teris.c,360 :: 		for(row = 0; row < MATRIX88_COLUMN_MAX; row++)
	CLRF       R2+0
L_MATRIX88_to_MATRIX72196:
	MOVLW      8
	SUBWF      R2+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_MATRIX88_to_MATRIX72197
;Teris.c,362 :: 		if(matrix_88->cell[row][col] == 1)
	MOVF       R2+0, 0
	MOVWF      R0+0
	RLF        R0+0, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	BCF        R0+0, 0
	MOVF       FARG_MATRIX88_to_MATRIX7219_matrix_88+0, 0
	ADDWF      R0+0, 1
	MOVF       R3+0, 0
	ADDWF      R0+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_MATRIX88_to_MATRIX72199
;Teris.c,364 :: 		matrix_7219->col[col] |= mask;
	MOVF       R3+0, 0
	ADDWF      FARG_MATRIX88_to_MATRIX7219_matrix_7219+0, 0
	MOVWF      R1+0
	MOVF       R1+0, 0
	MOVWF      FSR
	MOVF       MATRIX88_to_MATRIX7219_mask_L0+0, 0
	IORWF      INDF+0, 0
	MOVWF      R0+0
	MOVF       R1+0, 0
	MOVWF      FSR
	MOVF       R0+0, 0
	MOVWF      INDF+0
;Teris.c,365 :: 		}
L_MATRIX88_to_MATRIX72199:
;Teris.c,366 :: 		mask >>= 1;
	RRF        MATRIX88_to_MATRIX7219_mask_L0+0, 1
	BCF        MATRIX88_to_MATRIX7219_mask_L0+0, 7
;Teris.c,360 :: 		for(row = 0; row < MATRIX88_COLUMN_MAX; row++)
	INCF       R2+0, 1
;Teris.c,367 :: 		}
	GOTO       L_MATRIX88_to_MATRIX72196
L_MATRIX88_to_MATRIX72197:
;Teris.c,355 :: 		for(col = 0; col < MATRIX88_ROW_MAX; col++)
	INCF       R3+0, 1
;Teris.c,368 :: 		}
	GOTO       L_MATRIX88_to_MATRIX72193
L_MATRIX88_to_MATRIX72194:
;Teris.c,369 :: 		}
L_end_MATRIX88_to_MATRIX7219:
	RETURN
; end of _MATRIX88_to_MATRIX7219

_printf_MATRIX88:

;Teris.c,393 :: 		void printf_MATRIX88(MATRIX88* matrix_88)
;Teris.c,396 :: 		MATRIX88_to_MATRIX7219(matrix_88, &matrix_7219);
	MOVF       FARG_printf_MATRIX88_matrix_88+0, 0
	MOVWF      FARG_MATRIX88_to_MATRIX7219_matrix_88+0
	MOVLW      printf_MATRIX88_matrix_7219_L0+0
	MOVWF      FARG_MATRIX88_to_MATRIX7219_matrix_7219+0
	CALL       _MATRIX88_to_MATRIX7219+0
;Teris.c,397 :: 		printf_MATRIX7219(&matrix_7219);
	MOVLW      printf_MATRIX88_matrix_7219_L0+0
	MOVWF      FARG_printf_MATRIX7219_matrix+0
	CALL       _printf_MATRIX7219+0
;Teris.c,398 :: 		}
L_end_printf_MATRIX88:
	RETURN
; end of _printf_MATRIX88

_printf_Screen:

;Teris.c,400 :: 		void printf_Screen()
;Teris.c,402 :: 		printf_MATRIX88(&g_matrix88);
	MOVLW      _g_matrix88+0
	MOVWF      FARG_printf_MATRIX88_matrix_88+0
	CALL       _printf_MATRIX88+0
;Teris.c,403 :: 		}
L_end_printf_Screen:
	RETURN
; end of _printf_Screen

_Clear_Matrix:

;Teris.c,405 :: 		void Clear_Matrix(void)
;Teris.c,407 :: 		memset(&g_matrix88, 0, sizeof(MATRIX88));
	MOVLW      _g_matrix88+0
	MOVWF      FARG_memset_p1+0
	CLRF       FARG_memset_character+0
	MOVLW      64
	MOVWF      FARG_memset_n+0
	MOVLW      0
	MOVWF      FARG_memset_n+1
	CALL       _memset+0
;Teris.c,408 :: 		printf_Screen();
	CALL       _printf_Screen+0
;Teris.c,409 :: 		}
L_end_Clear_Matrix:
	RETURN
; end of _Clear_Matrix

_printf_console_MATRIX88:

;Teris.c,433 :: 		void printf_console_MATRIX88(MATRIX88* matrix)
;Teris.c,437 :: 		UART1_Write_Text("<<<<<<<<<<<<<<<<<<<<\r\n");
	MOVLW      ?lstr1_Teris+0
	MOVWF      FARG_UART1_Write_Text_uart_text+0
	CALL       _UART1_Write_Text+0
;Teris.c,438 :: 		for(row = 0; row < MATRIX88_ROW_MAX; row++)
	CLRF       printf_console_MATRIX88_row_L0+0
L_printf_console_MATRIX8810:
	MOVLW      8
	SUBWF      printf_console_MATRIX88_row_L0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_printf_console_MATRIX8811
;Teris.c,440 :: 		for(col = 0; col < MATRIX88_COLUMN_MAX; col++)
	CLRF       printf_console_MATRIX88_col_L0+0
L_printf_console_MATRIX8813:
	MOVLW      8
	SUBWF      printf_console_MATRIX88_col_L0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_printf_console_MATRIX8814
;Teris.c,442 :: 		if(matrix->cell[row][col] == 1)
	MOVF       printf_console_MATRIX88_row_L0+0, 0
	MOVWF      R0+0
	RLF        R0+0, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	BCF        R0+0, 0
	MOVF       FARG_printf_console_MATRIX88_matrix+0, 0
	ADDWF      R0+0, 1
	MOVF       printf_console_MATRIX88_col_L0+0, 0
	ADDWF      R0+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_printf_console_MATRIX8816
;Teris.c,444 :: 		UART1_Write_Text("*");
	MOVLW      ?lstr2_Teris+0
	MOVWF      FARG_UART1_Write_Text_uart_text+0
	CALL       _UART1_Write_Text+0
;Teris.c,445 :: 		}
	GOTO       L_printf_console_MATRIX8817
L_printf_console_MATRIX8816:
;Teris.c,448 :: 		UART1_Write_Text("_");
	MOVLW      ?lstr3_Teris+0
	MOVWF      FARG_UART1_Write_Text_uart_text+0
	CALL       _UART1_Write_Text+0
;Teris.c,449 :: 		}
L_printf_console_MATRIX8817:
;Teris.c,440 :: 		for(col = 0; col < MATRIX88_COLUMN_MAX; col++)
	INCF       printf_console_MATRIX88_col_L0+0, 1
;Teris.c,450 :: 		}
	GOTO       L_printf_console_MATRIX8813
L_printf_console_MATRIX8814:
;Teris.c,451 :: 		UART1_Write_Text("\r\n");
	MOVLW      ?lstr4_Teris+0
	MOVWF      FARG_UART1_Write_Text_uart_text+0
	CALL       _UART1_Write_Text+0
;Teris.c,438 :: 		for(row = 0; row < MATRIX88_ROW_MAX; row++)
	INCF       printf_console_MATRIX88_row_L0+0, 1
;Teris.c,452 :: 		}
	GOTO       L_printf_console_MATRIX8810
L_printf_console_MATRIX8811:
;Teris.c,453 :: 		UART1_Write_Text(">>>>>>>>>>>>>>>>>>>>\r\n");
	MOVLW      ?lstr5_Teris+0
	MOVWF      FARG_UART1_Write_Text_uart_text+0
	CALL       _UART1_Write_Text+0
;Teris.c,454 :: 		}
L_end_printf_console_MATRIX88:
	RETURN
; end of _printf_console_MATRIX88

_is_row_full:

;Teris.c,457 :: 		unsigned short is_row_full(MATRIX88* matrix, unsigned short row)
;Teris.c,460 :: 		for(col = 0; col < MATRIX88_COLUMN_MAX; col++)
	CLRF       R2+0
L_is_row_full18:
	MOVLW      8
	SUBWF      R2+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_is_row_full19
;Teris.c,462 :: 		if(matrix->cell[row][col] == 0)
	MOVF       FARG_is_row_full_row+0, 0
	MOVWF      R0+0
	RLF        R0+0, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	BCF        R0+0, 0
	MOVF       FARG_is_row_full_matrix+0, 0
	ADDWF      R0+0, 1
	MOVF       R2+0, 0
	ADDWF      R0+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	XORLW      0
	BTFSS      STATUS+0, 2
	GOTO       L_is_row_full21
;Teris.c,464 :: 		return 0;
	CLRF       R0+0
	GOTO       L_end_is_row_full
;Teris.c,465 :: 		}
L_is_row_full21:
;Teris.c,460 :: 		for(col = 0; col < MATRIX88_COLUMN_MAX; col++)
	INCF       R2+0, 1
;Teris.c,466 :: 		}
	GOTO       L_is_row_full18
L_is_row_full19:
;Teris.c,467 :: 		return 1;
	MOVLW      1
	MOVWF      R0+0
;Teris.c,468 :: 		}
L_end_is_row_full:
	RETURN
; end of _is_row_full

_delete_row:

;Teris.c,469 :: 		void delete_row(MATRIX88* matrix, unsigned short row)
;Teris.c,472 :: 		for(i = MATRIX88_ROW_MAX - 1; i >= 0; i--)
	MOVLW      7
	MOVWF      delete_row_i_L0+0
L_delete_row22:
	MOVLW      128
	XORWF      delete_row_i_L0+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 0
	GOTO       L_delete_row23
;Teris.c,474 :: 		if(i <= row)
	MOVLW      128
	MOVWF      R0+0
	MOVLW      128
	BTFSC      delete_row_i_L0+0, 7
	MOVLW      127
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__delete_row223
	MOVF       delete_row_i_L0+0, 0
	SUBWF      FARG_delete_row_row+0, 0
L__delete_row223:
	BTFSS      STATUS+0, 0
	GOTO       L_delete_row25
;Teris.c,476 :: 		if(i > 0)
	MOVLW      128
	XORLW      0
	MOVWF      R0+0
	MOVLW      128
	XORWF      delete_row_i_L0+0, 0
	SUBWF      R0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_delete_row26
;Teris.c,484 :: 		memcpy(matrix->cell[i], matrix->cell[i - 1], len);
	MOVLW      3
	MOVWF      R1+0
	MOVF       delete_row_i_L0+0, 0
	MOVWF      R0+0
	MOVF       R1+0, 0
L__delete_row224:
	BTFSC      STATUS+0, 2
	GOTO       L__delete_row225
	RLF        R0+0, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__delete_row224
L__delete_row225:
	MOVF       R0+0, 0
	ADDWF      FARG_delete_row_matrix+0, 0
	MOVWF      FARG_memcpy_d1+0
	MOVLW      1
	SUBWF      delete_row_i_L0+0, 0
	MOVWF      R3+0
	CLRF       R3+1
	BTFSS      STATUS+0, 0
	DECF       R3+1, 1
	MOVLW      0
	BTFSC      delete_row_i_L0+0, 7
	MOVLW      255
	ADDWF      R3+1, 1
	MOVLW      3
	MOVWF      R2+0
	MOVF       R3+0, 0
	MOVWF      R0+0
	MOVF       R3+1, 0
	MOVWF      R0+1
	MOVF       R2+0, 0
L__delete_row226:
	BTFSC      STATUS+0, 2
	GOTO       L__delete_row227
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__delete_row226
L__delete_row227:
	MOVF       R0+0, 0
	ADDWF      FARG_delete_row_matrix+0, 0
	MOVWF      FARG_memcpy_s1+0
	MOVLW      8
	MOVWF      FARG_memcpy_n+0
	MOVLW      0
	MOVWF      FARG_memcpy_n+1
	CALL       _memcpy+0
;Teris.c,485 :: 		}
	GOTO       L_delete_row27
L_delete_row26:
;Teris.c,488 :: 		memset(matrix->cell[i], 0, MATRIX88_COLUMN_MAX*sizeof(unsigned short));
	MOVLW      3
	MOVWF      R1+0
	MOVF       delete_row_i_L0+0, 0
	MOVWF      R0+0
	MOVF       R1+0, 0
L__delete_row228:
	BTFSC      STATUS+0, 2
	GOTO       L__delete_row229
	RLF        R0+0, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__delete_row228
L__delete_row229:
	MOVF       R0+0, 0
	ADDWF      FARG_delete_row_matrix+0, 0
	MOVWF      FARG_memset_p1+0
	CLRF       FARG_memset_character+0
	MOVLW      8
	MOVWF      FARG_memset_n+0
	MOVLW      0
	MOVWF      FARG_memset_n+1
	CALL       _memset+0
;Teris.c,489 :: 		}
L_delete_row27:
;Teris.c,490 :: 		}
L_delete_row25:
;Teris.c,472 :: 		for(i = MATRIX88_ROW_MAX - 1; i >= 0; i--)
	DECF       delete_row_i_L0+0, 1
;Teris.c,491 :: 		}
	GOTO       L_delete_row22
L_delete_row23:
;Teris.c,492 :: 		}
L_end_delete_row:
	RETURN
; end of _delete_row

_delete_matrix:

;Teris.c,493 :: 		unsigned short delete_matrix(MATRIX88* matrix)
;Teris.c,495 :: 		unsigned short count = 0;
	CLRF       delete_matrix_count_L0+0
	MOVLW      7
	MOVWF      delete_matrix_row_L0+0
;Teris.c,497 :: 		while(row >= 0)
L_delete_matrix28:
	MOVLW      128
	XORWF      delete_matrix_row_L0+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 0
	GOTO       L_delete_matrix29
;Teris.c,499 :: 		if(is_row_full(matrix, row))
	MOVF       FARG_delete_matrix_matrix+0, 0
	MOVWF      FARG_is_row_full_matrix+0
	MOVF       delete_matrix_row_L0+0, 0
	MOVWF      FARG_is_row_full_row+0
	CALL       _is_row_full+0
	MOVF       R0+0, 0
	BTFSC      STATUS+0, 2
	GOTO       L_delete_matrix30
;Teris.c,501 :: 		delete_row(matrix, row);
	MOVF       FARG_delete_matrix_matrix+0, 0
	MOVWF      FARG_delete_row_matrix+0
	MOVF       delete_matrix_row_L0+0, 0
	MOVWF      FARG_delete_row_row+0
	CALL       _delete_row+0
;Teris.c,502 :: 		count++;
	INCF       delete_matrix_count_L0+0, 1
;Teris.c,503 :: 		}
	GOTO       L_delete_matrix31
L_delete_matrix30:
;Teris.c,506 :: 		row--;
	DECF       delete_matrix_row_L0+0, 1
;Teris.c,507 :: 		}
L_delete_matrix31:
;Teris.c,508 :: 		}
	GOTO       L_delete_matrix28
L_delete_matrix29:
;Teris.c,513 :: 		return count;
	MOVF       delete_matrix_count_L0+0, 0
	MOVWF      R0+0
;Teris.c,514 :: 		}
L_end_delete_matrix:
	RETURN
; end of _delete_matrix

_is_row_empty:

;Teris.c,515 :: 		unsigned short is_row_empty(MATRIX88* matrix, unsigned short row)
;Teris.c,518 :: 		for(col = 0; col < MATRIX88_COLUMN_MAX; col++)
	CLRF       R2+0
L_is_row_empty32:
	MOVLW      8
	SUBWF      R2+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_is_row_empty33
;Teris.c,520 :: 		if(matrix->cell[row][col] == 1)
	MOVF       FARG_is_row_empty_row+0, 0
	MOVWF      R0+0
	RLF        R0+0, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	BCF        R0+0, 0
	MOVF       FARG_is_row_empty_matrix+0, 0
	ADDWF      R0+0, 1
	MOVF       R2+0, 0
	ADDWF      R0+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_is_row_empty35
;Teris.c,522 :: 		return 0;
	CLRF       R0+0
	GOTO       L_end_is_row_empty
;Teris.c,523 :: 		}
L_is_row_empty35:
;Teris.c,518 :: 		for(col = 0; col < MATRIX88_COLUMN_MAX; col++)
	INCF       R2+0, 1
;Teris.c,524 :: 		}
	GOTO       L_is_row_empty32
L_is_row_empty33:
;Teris.c,525 :: 		return 1;
	MOVLW      1
	MOVWF      R0+0
;Teris.c,526 :: 		}
L_end_is_row_empty:
	RETURN
; end of _is_row_empty

_is_col_empty:

;Teris.c,527 :: 		unsigned short is_col_empty(MATRIX88* matrix, unsigned short col)
;Teris.c,530 :: 		for(row = 0; row < MATRIX88_ROW_MAX; row++)
	CLRF       R2+0
L_is_col_empty36:
	MOVLW      8
	SUBWF      R2+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_is_col_empty37
;Teris.c,532 :: 		if(matrix->cell[row][col] == 1)
	MOVF       R2+0, 0
	MOVWF      R0+0
	RLF        R0+0, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	BCF        R0+0, 0
	MOVF       FARG_is_col_empty_matrix+0, 0
	ADDWF      R0+0, 1
	MOVF       FARG_is_col_empty_col+0, 0
	ADDWF      R0+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_is_col_empty39
;Teris.c,534 :: 		return 0;
	CLRF       R0+0
	GOTO       L_end_is_col_empty
;Teris.c,535 :: 		}
L_is_col_empty39:
;Teris.c,530 :: 		for(row = 0; row < MATRIX88_ROW_MAX; row++)
	INCF       R2+0, 1
;Teris.c,536 :: 		}
	GOTO       L_is_col_empty36
L_is_col_empty37:
;Teris.c,537 :: 		return 1;
	MOVLW      1
	MOVWF      R0+0
;Teris.c,538 :: 		}
L_end_is_col_empty:
	RETURN
; end of _is_col_empty

_hit_land1:

;Teris.c,539 :: 		unsigned short hit_land1(short x, short y, MATRIX44* matrix_44, MATRIX88* matrix_88)
;Teris.c,547 :: 		for(row = MATRIX44_ROW_MAX - 1; row >= 0; row--)
	MOVLW      3
	MOVWF      R5+0
L_hit_land140:
	MOVLW      128
	XORWF      R5+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 0
	GOTO       L_hit_land141
;Teris.c,549 :: 		for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
	CLRF       R6+0
L_hit_land143:
	MOVLW      128
	XORWF      R6+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      4
	SUBWF      R0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_hit_land144
;Teris.c,551 :: 		if(matrix_44->cell[row][col] == 1)
	MOVF       R5+0, 0
	MOVWF      R0+0
	RLF        R0+0, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	BCF        R0+0, 0
	MOVF       FARG_hit_land1_matrix_44+0, 0
	ADDWF      R0+0, 1
	MOVF       R6+0, 0
	ADDWF      R0+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_hit_land146
;Teris.c,553 :: 		if((y + row) >= (MATRIX88_ROW_MAX - 1))
	MOVF       R5+0, 0
	ADDWF      FARG_hit_land1_y+0, 0
	MOVWF      R1+0
	MOVLW      0
	BTFSC      FARG_hit_land1_y+0, 7
	MOVLW      255
	MOVWF      R1+1
	BTFSC      STATUS+0, 0
	INCF       R1+1, 1
	MOVLW      0
	BTFSC      R5+0, 7
	MOVLW      255
	ADDWF      R1+1, 1
	MOVLW      128
	XORWF      R1+1, 0
	MOVWF      R0+0
	MOVLW      128
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__hit_land1234
	MOVLW      7
	SUBWF      R1+0, 0
L__hit_land1234:
	BTFSS      STATUS+0, 0
	GOTO       L_hit_land147
;Teris.c,559 :: 		return 1;
	MOVLW      1
	MOVWF      R0+0
	GOTO       L_end_hit_land1
;Teris.c,560 :: 		}
L_hit_land147:
;Teris.c,562 :: 		if(matrix_88->cell[y + row + 1][x + col] == 1)
	MOVF       R5+0, 0
	ADDWF      FARG_hit_land1_y+0, 0
	MOVWF      R0+0
	MOVLW      0
	BTFSC      FARG_hit_land1_y+0, 7
	MOVLW      255
	MOVWF      R0+1
	BTFSC      STATUS+0, 0
	INCF       R0+1, 1
	MOVLW      0
	BTFSC      R5+0, 7
	MOVLW      255
	ADDWF      R0+1, 1
	MOVF       R0+0, 0
	ADDLW      1
	MOVWF      R3+0
	MOVLW      0
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      R0+1, 0
	MOVWF      R3+1
	MOVLW      3
	MOVWF      R2+0
	MOVF       R3+0, 0
	MOVWF      R0+0
	MOVF       R3+1, 0
	MOVWF      R0+1
	MOVF       R2+0, 0
L__hit_land1235:
	BTFSC      STATUS+0, 2
	GOTO       L__hit_land1236
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__hit_land1235
L__hit_land1236:
	MOVF       R0+0, 0
	ADDWF      FARG_hit_land1_matrix_88+0, 0
	MOVWF      R2+0
	MOVF       R6+0, 0
	ADDWF      FARG_hit_land1_x+0, 0
	MOVWF      R0+0
	MOVLW      0
	BTFSC      FARG_hit_land1_x+0, 7
	MOVLW      255
	MOVWF      R0+1
	BTFSC      STATUS+0, 0
	INCF       R0+1, 1
	MOVLW      0
	BTFSC      R6+0, 7
	MOVLW      255
	ADDWF      R0+1, 1
	MOVF       R0+0, 0
	ADDWF      R2+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_hit_land148
;Teris.c,568 :: 		return 1;
	MOVLW      1
	MOVWF      R0+0
	GOTO       L_end_hit_land1
;Teris.c,569 :: 		}
L_hit_land148:
;Teris.c,570 :: 		}
L_hit_land146:
;Teris.c,549 :: 		for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
	INCF       R6+0, 1
;Teris.c,571 :: 		}
	GOTO       L_hit_land143
L_hit_land144:
;Teris.c,547 :: 		for(row = MATRIX44_ROW_MAX - 1; row >= 0; row--)
	DECF       R5+0, 1
;Teris.c,572 :: 		}
	GOTO       L_hit_land140
L_hit_land141:
;Teris.c,577 :: 		return 0;
	CLRF       R0+0
;Teris.c,578 :: 		}
L_end_hit_land1:
	RETURN
; end of _hit_land1

_is_valid:

;Teris.c,579 :: 		unsigned short is_valid(short x, short y, MATRIX44* matrix_44, MATRIX88* matrix_88)
;Teris.c,587 :: 		for(row = MATRIX44_ROW_MAX - 1; row >= 0; row--)
	MOVLW      3
	MOVWF      R5+0
L_is_valid49:
	MOVLW      128
	XORWF      R5+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 0
	GOTO       L_is_valid50
;Teris.c,589 :: 		for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
	CLRF       R6+0
L_is_valid52:
	MOVLW      128
	XORWF      R6+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      4
	SUBWF      R0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_is_valid53
;Teris.c,591 :: 		if(matrix_44->cell[row][col] == 1)
	MOVF       R5+0, 0
	MOVWF      R0+0
	RLF        R0+0, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	BCF        R0+0, 0
	MOVF       FARG_is_valid_matrix_44+0, 0
	ADDWF      R0+0, 1
	MOVF       R6+0, 0
	ADDWF      R0+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_is_valid55
;Teris.c,593 :: 		if(matrix_88->cell[y + row][x + col] == 1)
	MOVF       R5+0, 0
	ADDWF      FARG_is_valid_y+0, 0
	MOVWF      R3+0
	MOVLW      0
	BTFSC      FARG_is_valid_y+0, 7
	MOVLW      255
	MOVWF      R3+1
	BTFSC      STATUS+0, 0
	INCF       R3+1, 1
	MOVLW      0
	BTFSC      R5+0, 7
	MOVLW      255
	ADDWF      R3+1, 1
	MOVLW      3
	MOVWF      R2+0
	MOVF       R3+0, 0
	MOVWF      R0+0
	MOVF       R3+1, 0
	MOVWF      R0+1
	MOVF       R2+0, 0
L__is_valid238:
	BTFSC      STATUS+0, 2
	GOTO       L__is_valid239
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__is_valid238
L__is_valid239:
	MOVF       R0+0, 0
	ADDWF      FARG_is_valid_matrix_88+0, 0
	MOVWF      R2+0
	MOVF       R6+0, 0
	ADDWF      FARG_is_valid_x+0, 0
	MOVWF      R0+0
	MOVLW      0
	BTFSC      FARG_is_valid_x+0, 7
	MOVLW      255
	MOVWF      R0+1
	BTFSC      STATUS+0, 0
	INCF       R0+1, 1
	MOVLW      0
	BTFSC      R6+0, 7
	MOVLW      255
	ADDWF      R0+1, 1
	MOVF       R0+0, 0
	ADDWF      R2+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_is_valid56
;Teris.c,599 :: 		return 0;
	CLRF       R0+0
	GOTO       L_end_is_valid
;Teris.c,600 :: 		}
L_is_valid56:
;Teris.c,602 :: 		if(( x + col < 0) || (x + col >= MATRIX88_COLUMN_MAX))
	MOVF       R6+0, 0
	ADDWF      FARG_is_valid_x+0, 0
	MOVWF      R1+0
	MOVLW      0
	BTFSC      FARG_is_valid_x+0, 7
	MOVLW      255
	MOVWF      R1+1
	BTFSC      STATUS+0, 0
	INCF       R1+1, 1
	MOVLW      0
	BTFSC      R6+0, 7
	MOVLW      255
	ADDWF      R1+1, 1
	MOVLW      128
	XORWF      R1+1, 0
	MOVWF      R0+0
	MOVLW      128
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__is_valid240
	MOVLW      0
	SUBWF      R1+0, 0
L__is_valid240:
	BTFSS      STATUS+0, 0
	GOTO       L__is_valid208
	MOVF       R6+0, 0
	ADDWF      FARG_is_valid_x+0, 0
	MOVWF      R1+0
	MOVLW      0
	BTFSC      FARG_is_valid_x+0, 7
	MOVLW      255
	MOVWF      R1+1
	BTFSC      STATUS+0, 0
	INCF       R1+1, 1
	MOVLW      0
	BTFSC      R6+0, 7
	MOVLW      255
	ADDWF      R1+1, 1
	MOVLW      128
	XORWF      R1+1, 0
	MOVWF      R0+0
	MOVLW      128
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__is_valid241
	MOVLW      8
	SUBWF      R1+0, 0
L__is_valid241:
	BTFSC      STATUS+0, 0
	GOTO       L__is_valid208
	GOTO       L_is_valid59
L__is_valid208:
;Teris.c,608 :: 		return 0;
	CLRF       R0+0
	GOTO       L_end_is_valid
;Teris.c,609 :: 		}
L_is_valid59:
;Teris.c,610 :: 		if((y + row) > (MATRIX88_ROW_MAX - 1))
	MOVF       R5+0, 0
	ADDWF      FARG_is_valid_y+0, 0
	MOVWF      R1+0
	MOVLW      0
	BTFSC      FARG_is_valid_y+0, 7
	MOVLW      255
	MOVWF      R1+1
	BTFSC      STATUS+0, 0
	INCF       R1+1, 1
	MOVLW      0
	BTFSC      R5+0, 7
	MOVLW      255
	ADDWF      R1+1, 1
	MOVLW      128
	MOVWF      R0+0
	MOVLW      128
	XORWF      R1+1, 0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__is_valid242
	MOVF       R1+0, 0
	SUBLW      7
L__is_valid242:
	BTFSC      STATUS+0, 0
	GOTO       L_is_valid60
;Teris.c,616 :: 		return 0;
	CLRF       R0+0
	GOTO       L_end_is_valid
;Teris.c,617 :: 		}
L_is_valid60:
;Teris.c,618 :: 		}
L_is_valid55:
;Teris.c,589 :: 		for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
	INCF       R6+0, 1
;Teris.c,619 :: 		}
	GOTO       L_is_valid52
L_is_valid53:
;Teris.c,587 :: 		for(row = MATRIX44_ROW_MAX - 1; row >= 0; row--)
	DECF       R5+0, 1
;Teris.c,620 :: 		}
	GOTO       L_is_valid49
L_is_valid50:
;Teris.c,625 :: 		return 1;
	MOVLW      1
	MOVWF      R0+0
;Teris.c,626 :: 		}
L_end_is_valid:
	RETURN
; end of _is_valid

_is_left_boundary:

;Teris.c,627 :: 		unsigned short is_left_boundary(short x, MATRIX44* matrix_44, MATRIX88* matrix_88)
;Teris.c,631 :: 		for(row = MATRIX44_ROW_MAX - 1; row >= 0; row--)
	MOVLW      3
	MOVWF      R3+0
L_is_left_boundary61:
	MOVLW      128
	XORWF      R3+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 0
	GOTO       L_is_left_boundary62
;Teris.c,633 :: 		for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
	CLRF       R4+0
L_is_left_boundary64:
	MOVLW      128
	XORWF      R4+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      4
	SUBWF      R0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_is_left_boundary65
;Teris.c,635 :: 		if(matrix_44->cell[row][col] == 1)
	MOVF       R3+0, 0
	MOVWF      R0+0
	RLF        R0+0, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	BCF        R0+0, 0
	MOVF       FARG_is_left_boundary_matrix_44+0, 0
	ADDWF      R0+0, 1
	MOVF       R4+0, 0
	ADDWF      R0+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_is_left_boundary67
;Teris.c,637 :: 		if( x + col < 0)
	MOVF       R4+0, 0
	ADDWF      FARG_is_left_boundary_x+0, 0
	MOVWF      R1+0
	MOVLW      0
	BTFSC      FARG_is_left_boundary_x+0, 7
	MOVLW      255
	MOVWF      R1+1
	BTFSC      STATUS+0, 0
	INCF       R1+1, 1
	MOVLW      0
	BTFSC      R4+0, 7
	MOVLW      255
	ADDWF      R1+1, 1
	MOVLW      128
	XORWF      R1+1, 0
	MOVWF      R0+0
	MOVLW      128
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__is_left_boundary244
	MOVLW      0
	SUBWF      R1+0, 0
L__is_left_boundary244:
	BTFSC      STATUS+0, 0
	GOTO       L_is_left_boundary68
;Teris.c,643 :: 		return LEFT_OVER_BOUNDARY;
	MOVLW      2
	MOVWF      R0+0
	GOTO       L_end_is_left_boundary
;Teris.c,644 :: 		}
L_is_left_boundary68:
;Teris.c,645 :: 		}
L_is_left_boundary67:
;Teris.c,633 :: 		for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
	INCF       R4+0, 1
;Teris.c,646 :: 		}
	GOTO       L_is_left_boundary64
L_is_left_boundary65:
;Teris.c,631 :: 		for(row = MATRIX44_ROW_MAX - 1; row >= 0; row--)
	DECF       R3+0, 1
;Teris.c,647 :: 		}
	GOTO       L_is_left_boundary61
L_is_left_boundary62:
;Teris.c,648 :: 		return OK;
	CLRF       R0+0
;Teris.c,649 :: 		}
L_end_is_left_boundary:
	RETURN
; end of _is_left_boundary

_is_right_boundary:

;Teris.c,650 :: 		unsigned short is_right_boundary(short x, MATRIX44* matrix_44, MATRIX88* matrix_88)
;Teris.c,654 :: 		for(row = MATRIX44_ROW_MAX - 1; row >= 0; row--)
	MOVLW      3
	MOVWF      R3+0
L_is_right_boundary69:
	MOVLW      128
	XORWF      R3+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 0
	GOTO       L_is_right_boundary70
;Teris.c,656 :: 		for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
	CLRF       R4+0
L_is_right_boundary72:
	MOVLW      128
	XORWF      R4+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      4
	SUBWF      R0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_is_right_boundary73
;Teris.c,658 :: 		if(matrix_44->cell[row][col] == 1)
	MOVF       R3+0, 0
	MOVWF      R0+0
	RLF        R0+0, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	BCF        R0+0, 0
	MOVF       FARG_is_right_boundary_matrix_44+0, 0
	ADDWF      R0+0, 1
	MOVF       R4+0, 0
	ADDWF      R0+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_is_right_boundary75
;Teris.c,660 :: 		if(x + col > MATRIX88_COLUMN_MAX - 1)
	MOVF       R4+0, 0
	ADDWF      FARG_is_right_boundary_x+0, 0
	MOVWF      R1+0
	MOVLW      0
	BTFSC      FARG_is_right_boundary_x+0, 7
	MOVLW      255
	MOVWF      R1+1
	BTFSC      STATUS+0, 0
	INCF       R1+1, 1
	MOVLW      0
	BTFSC      R4+0, 7
	MOVLW      255
	ADDWF      R1+1, 1
	MOVLW      128
	MOVWF      R0+0
	MOVLW      128
	XORWF      R1+1, 0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__is_right_boundary246
	MOVF       R1+0, 0
	SUBLW      7
L__is_right_boundary246:
	BTFSC      STATUS+0, 0
	GOTO       L_is_right_boundary76
;Teris.c,666 :: 		return RIGHT_OVER_BOUNDARY;
	MOVLW      3
	MOVWF      R0+0
	GOTO       L_end_is_right_boundary
;Teris.c,667 :: 		}
L_is_right_boundary76:
;Teris.c,668 :: 		}
L_is_right_boundary75:
;Teris.c,656 :: 		for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
	INCF       R4+0, 1
;Teris.c,669 :: 		}
	GOTO       L_is_right_boundary72
L_is_right_boundary73:
;Teris.c,654 :: 		for(row = MATRIX44_ROW_MAX - 1; row >= 0; row--)
	DECF       R3+0, 1
;Teris.c,670 :: 		}
	GOTO       L_is_right_boundary69
L_is_right_boundary70:
;Teris.c,671 :: 		return OK;
	CLRF       R0+0
;Teris.c,672 :: 		}
L_end_is_right_boundary:
	RETURN
; end of _is_right_boundary

_fall_off:

;Teris.c,673 :: 		unsigned short fall_off(short x, short y, MATRIX44* matrix_44, MATRIX88* matrix_88)
;Teris.c,675 :: 		while(1)
L_fall_off77:
;Teris.c,679 :: 		for(row = MATRIX44_ROW_MAX - 1; row >= 0; row--)
	MOVLW      3
	MOVWF      R5+0
L_fall_off79:
	MOVLW      128
	XORWF      R5+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 0
	GOTO       L_fall_off80
;Teris.c,681 :: 		for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
	CLRF       R6+0
L_fall_off82:
	MOVLW      128
	XORWF      R6+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      4
	SUBWF      R0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_fall_off83
;Teris.c,683 :: 		if(matrix_44->cell[row][col] == 1)
	MOVF       R5+0, 0
	MOVWF      R0+0
	RLF        R0+0, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	BCF        R0+0, 0
	MOVF       FARG_fall_off_matrix_44+0, 0
	ADDWF      R0+0, 1
	MOVF       R6+0, 0
	ADDWF      R0+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_fall_off85
;Teris.c,685 :: 		if(matrix_88->cell[y + row + 1][x + col] == 1)
	MOVF       R5+0, 0
	ADDWF      FARG_fall_off_y+0, 0
	MOVWF      R0+0
	MOVLW      0
	BTFSC      FARG_fall_off_y+0, 7
	MOVLW      255
	MOVWF      R0+1
	BTFSC      STATUS+0, 0
	INCF       R0+1, 1
	MOVLW      0
	BTFSC      R5+0, 7
	MOVLW      255
	ADDWF      R0+1, 1
	MOVF       R0+0, 0
	ADDLW      1
	MOVWF      R3+0
	MOVLW      0
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      R0+1, 0
	MOVWF      R3+1
	MOVLW      3
	MOVWF      R2+0
	MOVF       R3+0, 0
	MOVWF      R0+0
	MOVF       R3+1, 0
	MOVWF      R0+1
	MOVF       R2+0, 0
L__fall_off248:
	BTFSC      STATUS+0, 2
	GOTO       L__fall_off249
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__fall_off248
L__fall_off249:
	MOVF       R0+0, 0
	ADDWF      FARG_fall_off_matrix_88+0, 0
	MOVWF      R2+0
	MOVF       R6+0, 0
	ADDWF      FARG_fall_off_x+0, 0
	MOVWF      R0+0
	MOVLW      0
	BTFSC      FARG_fall_off_x+0, 7
	MOVLW      255
	MOVWF      R0+1
	BTFSC      STATUS+0, 0
	INCF       R0+1, 1
	MOVLW      0
	BTFSC      R6+0, 7
	MOVLW      255
	ADDWF      R0+1, 1
	MOVF       R0+0, 0
	ADDWF      R2+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_fall_off86
;Teris.c,691 :: 		return y;
	MOVF       FARG_fall_off_y+0, 0
	MOVWF      R0+0
	GOTO       L_end_fall_off
;Teris.c,692 :: 		}
L_fall_off86:
;Teris.c,693 :: 		if((y + row) >= (MATRIX88_ROW_MAX - 1))
	MOVF       R5+0, 0
	ADDWF      FARG_fall_off_y+0, 0
	MOVWF      R1+0
	MOVLW      0
	BTFSC      FARG_fall_off_y+0, 7
	MOVLW      255
	MOVWF      R1+1
	BTFSC      STATUS+0, 0
	INCF       R1+1, 1
	MOVLW      0
	BTFSC      R5+0, 7
	MOVLW      255
	ADDWF      R1+1, 1
	MOVLW      128
	XORWF      R1+1, 0
	MOVWF      R0+0
	MOVLW      128
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__fall_off250
	MOVLW      7
	SUBWF      R1+0, 0
L__fall_off250:
	BTFSS      STATUS+0, 0
	GOTO       L_fall_off87
;Teris.c,699 :: 		return y;
	MOVF       FARG_fall_off_y+0, 0
	MOVWF      R0+0
	GOTO       L_end_fall_off
;Teris.c,700 :: 		}
L_fall_off87:
;Teris.c,701 :: 		}
L_fall_off85:
;Teris.c,681 :: 		for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
	INCF       R6+0, 1
;Teris.c,702 :: 		}
	GOTO       L_fall_off82
L_fall_off83:
;Teris.c,679 :: 		for(row = MATRIX44_ROW_MAX - 1; row >= 0; row--)
	DECF       R5+0, 1
;Teris.c,703 :: 		}
	GOTO       L_fall_off79
L_fall_off80:
;Teris.c,704 :: 		y++;
	INCF       FARG_fall_off_y+0, 1
;Teris.c,705 :: 		}
	GOTO       L_fall_off77
;Teris.c,706 :: 		}
L_end_fall_off:
	RETURN
; end of _fall_off

_clear:

;Teris.c,707 :: 		void clear(short x, short y, MATRIX44* matrix_44, MATRIX88* matrix_88)
;Teris.c,711 :: 		for(row = 0; row < MATRIX44_ROW_MAX; row++)
	CLRF       R5+0
L_clear88:
	MOVLW      4
	SUBWF      R5+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_clear89
;Teris.c,713 :: 		for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
	CLRF       R6+0
L_clear91:
	MOVLW      4
	SUBWF      R6+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_clear92
;Teris.c,715 :: 		if(matrix_44->cell[row][col] == 1)
	MOVF       R5+0, 0
	MOVWF      R0+0
	RLF        R0+0, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	BCF        R0+0, 0
	MOVF       FARG_clear_matrix_44+0, 0
	ADDWF      R0+0, 1
	MOVF       R6+0, 0
	ADDWF      R0+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_clear94
;Teris.c,717 :: 		matrix_88->cell[y + row][x + col] = 0;
	MOVF       R5+0, 0
	ADDWF      FARG_clear_y+0, 0
	MOVWF      R3+0
	MOVLW      0
	BTFSC      FARG_clear_y+0, 7
	MOVLW      255
	MOVWF      R3+1
	BTFSC      STATUS+0, 0
	INCF       R3+1, 1
	MOVLW      3
	MOVWF      R2+0
	MOVF       R3+0, 0
	MOVWF      R0+0
	MOVF       R3+1, 0
	MOVWF      R0+1
	MOVF       R2+0, 0
L__clear252:
	BTFSC      STATUS+0, 2
	GOTO       L__clear253
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__clear252
L__clear253:
	MOVF       R0+0, 0
	ADDWF      FARG_clear_matrix_88+0, 0
	MOVWF      R2+0
	MOVF       R6+0, 0
	ADDWF      FARG_clear_x+0, 0
	MOVWF      R0+0
	MOVLW      0
	BTFSC      FARG_clear_x+0, 7
	MOVLW      255
	MOVWF      R0+1
	BTFSC      STATUS+0, 0
	INCF       R0+1, 1
	MOVF       R0+0, 0
	ADDWF      R2+0, 0
	MOVWF      FSR
	CLRF       INDF+0
;Teris.c,718 :: 		}
L_clear94:
;Teris.c,713 :: 		for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
	INCF       R6+0, 1
;Teris.c,719 :: 		}
	GOTO       L_clear91
L_clear92:
;Teris.c,711 :: 		for(row = 0; row < MATRIX44_ROW_MAX; row++)
	INCF       R5+0, 1
;Teris.c,720 :: 		}
	GOTO       L_clear88
L_clear89:
;Teris.c,721 :: 		}
L_end_clear:
	RETURN
; end of _clear

_merge:

;Teris.c,722 :: 		void merge(short x, short y, MATRIX44* matrix_44, MATRIX88* matrix_88)
;Teris.c,726 :: 		for(row = 0; row < MATRIX44_ROW_MAX; row++)
	CLRF       R5+0
L_merge95:
	MOVLW      4
	SUBWF      R5+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_merge96
;Teris.c,728 :: 		for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
	CLRF       R6+0
L_merge98:
	MOVLW      4
	SUBWF      R6+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_merge99
;Teris.c,730 :: 		if(matrix_44->cell[row][col] == 1)
	MOVF       R5+0, 0
	MOVWF      R0+0
	RLF        R0+0, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	BCF        R0+0, 0
	MOVF       FARG_merge_matrix_44+0, 0
	ADDWF      R0+0, 1
	MOVF       R6+0, 0
	ADDWF      R0+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_merge101
;Teris.c,732 :: 		matrix_88->cell[y + row][x + col] = 1;
	MOVF       R5+0, 0
	ADDWF      FARG_merge_y+0, 0
	MOVWF      R3+0
	MOVLW      0
	BTFSC      FARG_merge_y+0, 7
	MOVLW      255
	MOVWF      R3+1
	BTFSC      STATUS+0, 0
	INCF       R3+1, 1
	MOVLW      3
	MOVWF      R2+0
	MOVF       R3+0, 0
	MOVWF      R0+0
	MOVF       R3+1, 0
	MOVWF      R0+1
	MOVF       R2+0, 0
L__merge255:
	BTFSC      STATUS+0, 2
	GOTO       L__merge256
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__merge255
L__merge256:
	MOVF       R0+0, 0
	ADDWF      FARG_merge_matrix_88+0, 0
	MOVWF      R2+0
	MOVF       R6+0, 0
	ADDWF      FARG_merge_x+0, 0
	MOVWF      R0+0
	MOVLW      0
	BTFSC      FARG_merge_x+0, 7
	MOVLW      255
	MOVWF      R0+1
	BTFSC      STATUS+0, 0
	INCF       R0+1, 1
	MOVF       R0+0, 0
	ADDWF      R2+0, 0
	MOVWF      FSR
	MOVLW      1
	MOVWF      INDF+0
;Teris.c,733 :: 		}
L_merge101:
;Teris.c,728 :: 		for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
	INCF       R6+0, 1
;Teris.c,734 :: 		}
	GOTO       L_merge98
L_merge99:
;Teris.c,726 :: 		for(row = 0; row < MATRIX44_ROW_MAX; row++)
	INCF       R5+0, 1
;Teris.c,735 :: 		}
	GOTO       L_merge95
L_merge96:
;Teris.c,736 :: 		}
L_end_merge:
	RETURN
; end of _merge

_merge1:

;Teris.c,737 :: 		void merge1(short x, short y, MATRIX44* matrix_44, MATRIX88* matrix88_in, MATRIX88* matrix88_out)
;Teris.c,748 :: 		memcpy(matrix88_out, matrix88_in, len);
	MOVF       FARG_merge1_matrix88_out+0, 0
	MOVWF      FARG_memcpy_d1+0
	MOVF       FARG_merge1_matrix88_in+0, 0
	MOVWF      FARG_memcpy_s1+0
	MOVLW      64
	MOVWF      FARG_memcpy_n+0
	MOVLW      0
	MOVWF      FARG_memcpy_n+1
	CALL       _memcpy+0
;Teris.c,750 :: 		for(row = 0; row < MATRIX44_ROW_MAX; row++)
	CLRF       merge1_row_L0+0
L_merge1102:
	MOVLW      4
	SUBWF      merge1_row_L0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_merge1103
;Teris.c,752 :: 		for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
	CLRF       merge1_col_L0+0
L_merge1105:
	MOVLW      4
	SUBWF      merge1_col_L0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_merge1106
;Teris.c,754 :: 		if(matrix_44->cell[row][col] == 1)
	MOVF       merge1_row_L0+0, 0
	MOVWF      R0+0
	RLF        R0+0, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	BCF        R0+0, 0
	MOVF       FARG_merge1_matrix_44+0, 0
	ADDWF      R0+0, 1
	MOVF       merge1_col_L0+0, 0
	ADDWF      R0+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_merge1108
;Teris.c,756 :: 		matrix88_out->cell[y + row][x + col] = 1;
	MOVF       merge1_row_L0+0, 0
	ADDWF      FARG_merge1_y+0, 0
	MOVWF      R3+0
	MOVLW      0
	BTFSC      FARG_merge1_y+0, 7
	MOVLW      255
	MOVWF      R3+1
	BTFSC      STATUS+0, 0
	INCF       R3+1, 1
	MOVLW      3
	MOVWF      R2+0
	MOVF       R3+0, 0
	MOVWF      R0+0
	MOVF       R3+1, 0
	MOVWF      R0+1
	MOVF       R2+0, 0
L__merge1258:
	BTFSC      STATUS+0, 2
	GOTO       L__merge1259
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__merge1258
L__merge1259:
	MOVF       R0+0, 0
	ADDWF      FARG_merge1_matrix88_out+0, 0
	MOVWF      R2+0
	MOVF       merge1_col_L0+0, 0
	ADDWF      FARG_merge1_x+0, 0
	MOVWF      R0+0
	MOVLW      0
	BTFSC      FARG_merge1_x+0, 7
	MOVLW      255
	MOVWF      R0+1
	BTFSC      STATUS+0, 0
	INCF       R0+1, 1
	MOVF       R0+0, 0
	ADDWF      R2+0, 0
	MOVWF      FSR
	MOVLW      1
	MOVWF      INDF+0
;Teris.c,757 :: 		}
L_merge1108:
;Teris.c,752 :: 		for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
	INCF       merge1_col_L0+0, 1
;Teris.c,758 :: 		}
	GOTO       L_merge1105
L_merge1106:
;Teris.c,750 :: 		for(row = 0; row < MATRIX44_ROW_MAX; row++)
	INCF       merge1_row_L0+0, 1
;Teris.c,759 :: 		}
	GOTO       L_merge1102
L_merge1103:
;Teris.c,760 :: 		}
L_end_merge1:
	RETURN
; end of _merge1

_evaluate:

;Teris.c,761 :: 		unsigned int evaluate(MATRIX88* matrix)
;Teris.c,763 :: 		unsigned int risk = 0;
	CLRF       evaluate_risk_L0+0
	CLRF       evaluate_risk_L0+1
	MOVLW      255
	MOVWF      evaluate_full_L0+0
;Teris.c,767 :: 		for(col = 0; col < MATRIX88_COLUMN_MAX; col++)
	CLRF       R2+0
L_evaluate109:
	MOVLW      8
	SUBWF      R2+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_evaluate110
;Teris.c,769 :: 		full = 0xFF;
	MOVLW      255
	MOVWF      evaluate_full_L0+0
;Teris.c,770 :: 		for(row = MATRIX88_ROW_MAX - 1; row >= 0; row--)
	MOVLW      7
	MOVWF      R3+0
L_evaluate112:
	MOVLW      128
	XORWF      R3+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 0
	GOTO       L_evaluate113
;Teris.c,772 :: 		if(full == 0xFF)
	MOVF       evaluate_full_L0+0, 0
	XORLW      255
	BTFSS      STATUS+0, 2
	GOTO       L_evaluate115
;Teris.c,774 :: 		full = matrix->cell[row][col];
	MOVLW      3
	MOVWF      R1+0
	MOVF       R3+0, 0
	MOVWF      R0+0
	MOVF       R1+0, 0
L__evaluate261:
	BTFSC      STATUS+0, 2
	GOTO       L__evaluate262
	RLF        R0+0, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__evaluate261
L__evaluate262:
	MOVF       FARG_evaluate_matrix+0, 0
	ADDWF      R0+0, 1
	MOVF       R2+0, 0
	ADDWF      R0+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	MOVWF      evaluate_full_L0+0
;Teris.c,775 :: 		}
	GOTO       L_evaluate116
L_evaluate115:
;Teris.c,778 :: 		if(matrix->cell[row][col] == 1)
	MOVLW      3
	MOVWF      R1+0
	MOVF       R3+0, 0
	MOVWF      R0+0
	MOVF       R1+0, 0
L__evaluate263:
	BTFSC      STATUS+0, 2
	GOTO       L__evaluate264
	RLF        R0+0, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__evaluate263
L__evaluate264:
	MOVF       FARG_evaluate_matrix+0, 0
	ADDWF      R0+0, 1
	MOVF       R2+0, 0
	ADDWF      R0+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_evaluate117
;Teris.c,780 :: 		if(full == 0)
	MOVF       evaluate_full_L0+0, 0
	XORLW      0
	BTFSS      STATUS+0, 2
	GOTO       L_evaluate118
;Teris.c,782 :: 		risk++;
	INCF       evaluate_risk_L0+0, 1
	BTFSC      STATUS+0, 2
	INCF       evaluate_risk_L0+1, 1
;Teris.c,783 :: 		}
L_evaluate118:
;Teris.c,784 :: 		}
L_evaluate117:
;Teris.c,785 :: 		full = matrix->cell[row][col];
	MOVLW      3
	MOVWF      R1+0
	MOVF       R3+0, 0
	MOVWF      R0+0
	MOVF       R1+0, 0
L__evaluate265:
	BTFSC      STATUS+0, 2
	GOTO       L__evaluate266
	RLF        R0+0, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__evaluate265
L__evaluate266:
	MOVF       FARG_evaluate_matrix+0, 0
	ADDWF      R0+0, 1
	MOVF       R2+0, 0
	ADDWF      R0+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	MOVWF      evaluate_full_L0+0
;Teris.c,786 :: 		}
L_evaluate116:
;Teris.c,770 :: 		for(row = MATRIX88_ROW_MAX - 1; row >= 0; row--)
	DECF       R3+0, 1
;Teris.c,787 :: 		}
	GOTO       L_evaluate112
L_evaluate113:
;Teris.c,767 :: 		for(col = 0; col < MATRIX88_COLUMN_MAX; col++)
	INCF       R2+0, 1
;Teris.c,788 :: 		}
	GOTO       L_evaluate109
L_evaluate110:
;Teris.c,794 :: 		return risk;
	MOVF       evaluate_risk_L0+0, 0
	MOVWF      R0+0
	MOVF       evaluate_risk_L0+1, 0
	MOVWF      R0+1
;Teris.c,795 :: 		}
L_end_evaluate:
	RETURN
; end of _evaluate

_char_info_index_rand:

;Teris.c,796 :: 		unsigned short char_info_index_rand()
;Teris.c,798 :: 		return (unsigned short)(rand()%CHARACTER_MAX);
	CALL       _rand+0
	MOVLW      9
	MOVWF      R4+0
	MOVLW      0
	MOVWF      R4+1
	CALL       _Div_16x16_S+0
	MOVF       R8+0, 0
	MOVWF      R0+0
	MOVF       R8+1, 0
	MOVWF      R0+1
;Teris.c,799 :: 		}
L_end_char_info_index_rand:
	RETURN
; end of _char_info_index_rand

_left_most:

;Teris.c,800 :: 		short left_most(short x, MATRIX44* matrix_44, MATRIX88* matrix_88)
;Teris.c,802 :: 		while(1)
L_left_most119:
;Teris.c,804 :: 		if(is_left_boundary(x, matrix_44, matrix_88) == LEFT_OVER_BOUNDARY)
	MOVF       FARG_left_most_x+0, 0
	MOVWF      FARG_is_left_boundary_x+0
	MOVF       FARG_left_most_matrix_44+0, 0
	MOVWF      FARG_is_left_boundary_matrix_44+0
	MOVF       FARG_left_most_matrix_88+0, 0
	MOVWF      FARG_is_left_boundary_matrix_88+0
	CALL       _is_left_boundary+0
	MOVF       R0+0, 0
	XORLW      2
	BTFSS      STATUS+0, 2
	GOTO       L_left_most121
;Teris.c,810 :: 		return x + 1;
	INCF       FARG_left_most_x+0, 0
	MOVWF      R0+0
	GOTO       L_end_left_most
;Teris.c,811 :: 		}
L_left_most121:
;Teris.c,812 :: 		x--;
	DECF       FARG_left_most_x+0, 1
;Teris.c,813 :: 		}
	GOTO       L_left_most119
;Teris.c,814 :: 		}
L_end_left_most:
	RETURN
; end of _left_most

_right_most:

;Teris.c,815 :: 		short right_most(short x, MATRIX44* matrix_44, MATRIX88* matrix_88)
;Teris.c,817 :: 		while(1)
L_right_most122:
;Teris.c,819 :: 		if(is_right_boundary(x, matrix_44, matrix_88) == RIGHT_OVER_BOUNDARY)
	MOVF       FARG_right_most_x+0, 0
	MOVWF      FARG_is_right_boundary_x+0
	MOVF       FARG_right_most_matrix_44+0, 0
	MOVWF      FARG_is_right_boundary_matrix_44+0
	MOVF       FARG_right_most_matrix_88+0, 0
	MOVWF      FARG_is_right_boundary_matrix_88+0
	CALL       _is_right_boundary+0
	MOVF       R0+0, 0
	XORLW      3
	BTFSS      STATUS+0, 2
	GOTO       L_right_most124
;Teris.c,825 :: 		return x - 1;
	DECF       FARG_right_most_x+0, 0
	MOVWF      R0+0
	GOTO       L_end_right_most
;Teris.c,826 :: 		}
L_right_most124:
;Teris.c,827 :: 		x++;
	INCF       FARG_right_most_x+0, 1
;Teris.c,828 :: 		}
	GOTO       L_right_most122
;Teris.c,829 :: 		}
L_end_right_most:
	RETURN
; end of _right_most

_get_high:

;Teris.c,830 :: 		unsigned short get_high(MATRIX88* matrix)
;Teris.c,833 :: 		for(row = MATRIX88_ROW_MAX - 1; row >= 0; row--)
	MOVLW      7
	MOVWF      get_high_row_L0+0
L_get_high125:
	MOVLW      128
	XORWF      get_high_row_L0+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 0
	GOTO       L_get_high126
;Teris.c,835 :: 		if(is_row_empty(matrix, row) == 1)
	MOVF       FARG_get_high_matrix+0, 0
	MOVWF      FARG_is_row_empty_matrix+0
	MOVF       get_high_row_L0+0, 0
	MOVWF      FARG_is_row_empty_row+0
	CALL       _is_row_empty+0
	MOVF       R0+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_get_high128
;Teris.c,841 :: 		return (unsigned short)(MATRIX88_ROW_MAX - row - 1);
	MOVF       get_high_row_L0+0, 0
	SUBLW      8
	MOVWF      R0+0
	DECF       R0+0, 1
	GOTO       L_end_get_high
;Teris.c,842 :: 		}
L_get_high128:
;Teris.c,833 :: 		for(row = MATRIX88_ROW_MAX - 1; row >= 0; row--)
	DECF       get_high_row_L0+0, 1
;Teris.c,843 :: 		}
	GOTO       L_get_high125
L_get_high126:
;Teris.c,844 :: 		return MATRIX88_ROW_MAX;
	MOVLW      8
	MOVWF      R0+0
;Teris.c,845 :: 		}
L_end_get_high:
	RETURN
; end of _get_high

_get_high_after_merge:

;Teris.c,846 :: 		unsigned short get_high_after_merge(short y, MATRIX44* matrix)
;Teris.c,850 :: 		for(row = 0; row < MATRIX44_ROW_MAX; row++)
	CLRF       R2+0
L_get_high_after_merge129:
	MOVLW      128
	XORWF      R2+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      4
	SUBWF      R0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_get_high_after_merge130
;Teris.c,852 :: 		for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
	CLRF       R3+0
L_get_high_after_merge132:
	MOVLW      128
	XORWF      R3+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      4
	SUBWF      R0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_get_high_after_merge133
;Teris.c,854 :: 		if(matrix->cell[row][col] == 1)
	MOVF       R2+0, 0
	MOVWF      R0+0
	RLF        R0+0, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	BCF        R0+0, 0
	MOVF       FARG_get_high_after_merge_matrix+0, 0
	ADDWF      R0+0, 1
	MOVF       R3+0, 0
	ADDWF      R0+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_get_high_after_merge135
;Teris.c,860 :: 		return (unsigned short)(MATRIX88_ROW_MAX - y - row);
	MOVF       FARG_get_high_after_merge_y+0, 0
	SUBLW      8
	MOVWF      R0+0
	MOVF       R2+0, 0
	SUBWF      R0+0, 1
	GOTO       L_end_get_high_after_merge
;Teris.c,861 :: 		}
L_get_high_after_merge135:
;Teris.c,852 :: 		for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
	INCF       R3+0, 1
;Teris.c,862 :: 		}
	GOTO       L_get_high_after_merge132
L_get_high_after_merge133:
;Teris.c,850 :: 		for(row = 0; row < MATRIX44_ROW_MAX; row++)
	INCF       R2+0, 1
;Teris.c,863 :: 		}
	GOTO       L_get_high_after_merge129
L_get_high_after_merge130:
;Teris.c,864 :: 		}
L_end_get_high_after_merge:
	RETURN
; end of _get_high_after_merge

_get_holes_after_merge:

;Teris.c,865 :: 		unsigned short get_holes_after_merge(MATRIX88* matrix)
;Teris.c,867 :: 		short start = -1;
	MOVLW      255
	MOVWF      get_holes_after_merge_start_L0+0
	MOVLW      255
	MOVWF      get_holes_after_merge_stop_L0+0
	CLRF       get_holes_after_merge_num_hole_L0+0
;Teris.c,872 :: 		for(col = 0; col < MATRIX88_COLUMN_MAX; col++)
	CLRF       R5+0
L_get_holes_after_merge136:
	MOVLW      128
	XORWF      R5+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      8
	SUBWF      R0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_get_holes_after_merge137
;Teris.c,874 :: 		start = stop = -1;
	MOVLW      255
	MOVWF      get_holes_after_merge_stop_L0+0
	MOVLW      255
	MOVWF      get_holes_after_merge_start_L0+0
;Teris.c,875 :: 		for(row = 0; row < MATRIX88_ROW_MAX; row++)
	CLRF       R6+0
L_get_holes_after_merge139:
	MOVLW      128
	XORWF      R6+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      8
	SUBWF      R0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_get_holes_after_merge140
;Teris.c,877 :: 		if(col == 0)
	MOVF       R5+0, 0
	XORLW      0
	BTFSS      STATUS+0, 2
	GOTO       L_get_holes_after_merge142
;Teris.c,879 :: 		if((matrix->cell[row][col] == 0) && (matrix->cell[row][col + 1] == 1))
	MOVLW      3
	MOVWF      R1+0
	MOVF       R6+0, 0
	MOVWF      R0+0
	MOVF       R1+0, 0
L__get_holes_after_merge273:
	BTFSC      STATUS+0, 2
	GOTO       L__get_holes_after_merge274
	RLF        R0+0, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__get_holes_after_merge273
L__get_holes_after_merge274:
	MOVF       FARG_get_holes_after_merge_matrix+0, 0
	ADDWF      R0+0, 1
	MOVF       R5+0, 0
	ADDWF      R0+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	XORLW      0
	BTFSS      STATUS+0, 2
	GOTO       L_get_holes_after_merge145
	MOVLW      3
	MOVWF      R1+0
	MOVF       R6+0, 0
	MOVWF      R0+0
	MOVF       R1+0, 0
L__get_holes_after_merge275:
	BTFSC      STATUS+0, 2
	GOTO       L__get_holes_after_merge276
	RLF        R0+0, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__get_holes_after_merge275
L__get_holes_after_merge276:
	MOVF       R0+0, 0
	ADDWF      FARG_get_holes_after_merge_matrix+0, 0
	MOVWF      R2+0
	MOVF       R5+0, 0
	ADDLW      1
	MOVWF      R0+0
	CLRF       R0+1
	BTFSC      STATUS+0, 0
	INCF       R0+1, 1
	MOVLW      0
	BTFSC      R5+0, 7
	MOVLW      255
	ADDWF      R0+1, 1
	MOVF       R0+0, 0
	ADDWF      R2+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_get_holes_after_merge145
L__get_holes_after_merge212:
;Teris.c,881 :: 		if(start == -1)
	MOVF       get_holes_after_merge_start_L0+0, 0
	XORLW      255
	BTFSS      STATUS+0, 2
	GOTO       L_get_holes_after_merge146
;Teris.c,883 :: 		start = row;
	MOVF       R6+0, 0
	MOVWF      get_holes_after_merge_start_L0+0
;Teris.c,884 :: 		}
L_get_holes_after_merge146:
;Teris.c,885 :: 		}
L_get_holes_after_merge145:
;Teris.c,886 :: 		}
	GOTO       L_get_holes_after_merge147
L_get_holes_after_merge142:
;Teris.c,887 :: 		else if(col == MATRIX88_COLUMN_MAX - 1)
	MOVF       R5+0, 0
	XORLW      7
	BTFSS      STATUS+0, 2
	GOTO       L_get_holes_after_merge148
;Teris.c,889 :: 		if((matrix->cell[row][col] == 0) && (matrix->cell[row][col - 1] == 1))
	MOVLW      3
	MOVWF      R1+0
	MOVF       R6+0, 0
	MOVWF      R0+0
	MOVF       R1+0, 0
L__get_holes_after_merge277:
	BTFSC      STATUS+0, 2
	GOTO       L__get_holes_after_merge278
	RLF        R0+0, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__get_holes_after_merge277
L__get_holes_after_merge278:
	MOVF       FARG_get_holes_after_merge_matrix+0, 0
	ADDWF      R0+0, 1
	MOVF       R5+0, 0
	ADDWF      R0+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	XORLW      0
	BTFSS      STATUS+0, 2
	GOTO       L_get_holes_after_merge151
	MOVLW      3
	MOVWF      R1+0
	MOVF       R6+0, 0
	MOVWF      R0+0
	MOVF       R1+0, 0
L__get_holes_after_merge279:
	BTFSC      STATUS+0, 2
	GOTO       L__get_holes_after_merge280
	RLF        R0+0, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__get_holes_after_merge279
L__get_holes_after_merge280:
	MOVF       R0+0, 0
	ADDWF      FARG_get_holes_after_merge_matrix+0, 0
	MOVWF      R2+0
	MOVLW      1
	SUBWF      R5+0, 0
	MOVWF      R0+0
	CLRF       R0+1
	BTFSS      STATUS+0, 0
	DECF       R0+1, 1
	MOVLW      0
	BTFSC      R5+0, 7
	MOVLW      255
	ADDWF      R0+1, 1
	MOVF       R0+0, 0
	ADDWF      R2+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_get_holes_after_merge151
L__get_holes_after_merge211:
;Teris.c,891 :: 		if(start == -1)
	MOVF       get_holes_after_merge_start_L0+0, 0
	XORLW      255
	BTFSS      STATUS+0, 2
	GOTO       L_get_holes_after_merge152
;Teris.c,893 :: 		start = row;
	MOVF       R6+0, 0
	MOVWF      get_holes_after_merge_start_L0+0
;Teris.c,894 :: 		}
L_get_holes_after_merge152:
;Teris.c,895 :: 		}
L_get_holes_after_merge151:
;Teris.c,896 :: 		}
	GOTO       L_get_holes_after_merge153
L_get_holes_after_merge148:
;Teris.c,899 :: 		if((matrix->cell[row][col] == 0) && (matrix->cell[row][col - 1] == 1) && (matrix->cell[row][col + 1] == 1))
	MOVLW      3
	MOVWF      R1+0
	MOVF       R6+0, 0
	MOVWF      R0+0
	MOVF       R1+0, 0
L__get_holes_after_merge281:
	BTFSC      STATUS+0, 2
	GOTO       L__get_holes_after_merge282
	RLF        R0+0, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__get_holes_after_merge281
L__get_holes_after_merge282:
	MOVF       FARG_get_holes_after_merge_matrix+0, 0
	ADDWF      R0+0, 1
	MOVF       R5+0, 0
	ADDWF      R0+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	XORLW      0
	BTFSS      STATUS+0, 2
	GOTO       L_get_holes_after_merge156
	MOVLW      3
	MOVWF      R1+0
	MOVF       R6+0, 0
	MOVWF      R0+0
	MOVF       R1+0, 0
L__get_holes_after_merge283:
	BTFSC      STATUS+0, 2
	GOTO       L__get_holes_after_merge284
	RLF        R0+0, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__get_holes_after_merge283
L__get_holes_after_merge284:
	MOVF       R0+0, 0
	ADDWF      FARG_get_holes_after_merge_matrix+0, 0
	MOVWF      R2+0
	MOVLW      1
	SUBWF      R5+0, 0
	MOVWF      R0+0
	CLRF       R0+1
	BTFSS      STATUS+0, 0
	DECF       R0+1, 1
	MOVLW      0
	BTFSC      R5+0, 7
	MOVLW      255
	ADDWF      R0+1, 1
	MOVF       R0+0, 0
	ADDWF      R2+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_get_holes_after_merge156
	MOVLW      3
	MOVWF      R1+0
	MOVF       R6+0, 0
	MOVWF      R0+0
	MOVF       R1+0, 0
L__get_holes_after_merge285:
	BTFSC      STATUS+0, 2
	GOTO       L__get_holes_after_merge286
	RLF        R0+0, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__get_holes_after_merge285
L__get_holes_after_merge286:
	MOVF       R0+0, 0
	ADDWF      FARG_get_holes_after_merge_matrix+0, 0
	MOVWF      R2+0
	MOVF       R5+0, 0
	ADDLW      1
	MOVWF      R0+0
	CLRF       R0+1
	BTFSC      STATUS+0, 0
	INCF       R0+1, 1
	MOVLW      0
	BTFSC      R5+0, 7
	MOVLW      255
	ADDWF      R0+1, 1
	MOVF       R0+0, 0
	ADDWF      R2+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_get_holes_after_merge156
L__get_holes_after_merge210:
;Teris.c,901 :: 		if(start == -1)
	MOVF       get_holes_after_merge_start_L0+0, 0
	XORLW      255
	BTFSS      STATUS+0, 2
	GOTO       L_get_holes_after_merge157
;Teris.c,903 :: 		start = row;
	MOVF       R6+0, 0
	MOVWF      get_holes_after_merge_start_L0+0
;Teris.c,904 :: 		}
L_get_holes_after_merge157:
;Teris.c,905 :: 		}
L_get_holes_after_merge156:
;Teris.c,906 :: 		}
L_get_holes_after_merge153:
L_get_holes_after_merge147:
;Teris.c,907 :: 		if(start >= 0)
	MOVLW      128
	XORWF      get_holes_after_merge_start_L0+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 0
	GOTO       L_get_holes_after_merge158
;Teris.c,909 :: 		if(row == MATRIX88_ROW_MAX - 1)
	MOVF       R6+0, 0
	XORLW      7
	BTFSS      STATUS+0, 2
	GOTO       L_get_holes_after_merge159
;Teris.c,911 :: 		if(stop == -1)
	MOVF       get_holes_after_merge_stop_L0+0, 0
	XORLW      255
	BTFSS      STATUS+0, 2
	GOTO       L_get_holes_after_merge160
;Teris.c,913 :: 		stop = MATRIX88_ROW_MAX;
	MOVLW      8
	MOVWF      get_holes_after_merge_stop_L0+0
;Teris.c,914 :: 		}
L_get_holes_after_merge160:
;Teris.c,915 :: 		}
	GOTO       L_get_holes_after_merge161
L_get_holes_after_merge159:
;Teris.c,916 :: 		else if(matrix->cell[row + 1][col] == 1)
	MOVF       R6+0, 0
	ADDLW      1
	MOVWF      R3+0
	CLRF       R3+1
	BTFSC      STATUS+0, 0
	INCF       R3+1, 1
	MOVLW      0
	BTFSC      R6+0, 7
	MOVLW      255
	ADDWF      R3+1, 1
	MOVLW      3
	MOVWF      R2+0
	MOVF       R3+0, 0
	MOVWF      R0+0
	MOVF       R3+1, 0
	MOVWF      R0+1
	MOVF       R2+0, 0
L__get_holes_after_merge287:
	BTFSC      STATUS+0, 2
	GOTO       L__get_holes_after_merge288
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__get_holes_after_merge287
L__get_holes_after_merge288:
	MOVF       FARG_get_holes_after_merge_matrix+0, 0
	ADDWF      R0+0, 1
	MOVF       R5+0, 0
	ADDWF      R0+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_get_holes_after_merge162
;Teris.c,918 :: 		if(stop == -1)
	MOVF       get_holes_after_merge_stop_L0+0, 0
	XORLW      255
	BTFSS      STATUS+0, 2
	GOTO       L_get_holes_after_merge163
;Teris.c,920 :: 		stop = row + 1;
	INCF       R6+0, 0
	MOVWF      get_holes_after_merge_stop_L0+0
;Teris.c,921 :: 		}
L_get_holes_after_merge163:
;Teris.c,922 :: 		}
L_get_holes_after_merge162:
L_get_holes_after_merge161:
;Teris.c,923 :: 		}
L_get_holes_after_merge158:
;Teris.c,875 :: 		for(row = 0; row < MATRIX88_ROW_MAX; row++)
	INCF       R6+0, 1
;Teris.c,925 :: 		}
	GOTO       L_get_holes_after_merge139
L_get_holes_after_merge140:
;Teris.c,926 :: 		if((start >= 0) && (stop >= 0) && (stop - start >= 3))
	MOVLW      128
	XORWF      get_holes_after_merge_start_L0+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 0
	GOTO       L_get_holes_after_merge166
	MOVLW      128
	XORWF      get_holes_after_merge_stop_L0+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 0
	GOTO       L_get_holes_after_merge166
	MOVF       get_holes_after_merge_start_L0+0, 0
	SUBWF      get_holes_after_merge_stop_L0+0, 0
	MOVWF      R1+0
	CLRF       R1+1
	BTFSS      STATUS+0, 0
	DECF       R1+1, 1
	MOVLW      0
	BTFSC      get_holes_after_merge_stop_L0+0, 7
	MOVLW      255
	ADDWF      R1+1, 1
	MOVLW      1
	BTFSS      get_holes_after_merge_start_L0+0, 7
	MOVLW      0
	ADDWF      R1+1, 1
	MOVLW      128
	XORWF      R1+1, 0
	MOVWF      R0+0
	MOVLW      128
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__get_holes_after_merge289
	MOVLW      3
	SUBWF      R1+0, 0
L__get_holes_after_merge289:
	BTFSS      STATUS+0, 0
	GOTO       L_get_holes_after_merge166
L__get_holes_after_merge209:
;Teris.c,932 :: 		num_hole++;
	INCF       get_holes_after_merge_num_hole_L0+0, 1
;Teris.c,933 :: 		}
L_get_holes_after_merge166:
;Teris.c,872 :: 		for(col = 0; col < MATRIX88_COLUMN_MAX; col++)
	INCF       R5+0, 1
;Teris.c,934 :: 		}
	GOTO       L_get_holes_after_merge136
L_get_holes_after_merge137:
;Teris.c,939 :: 		return num_hole;
	MOVF       get_holes_after_merge_num_hole_L0+0, 0
	MOVWF      R0+0
;Teris.c,940 :: 		}
L_end_get_holes_after_merge:
	RETURN
; end of _get_holes_after_merge

_find_best_solution:

;Teris.c,941 :: 		unsigned short find_best_solution()
;Teris.c,947 :: 		short temp_pre_x = 0xFF, tem_pre_sub_index = 0xFF;
	MOVLW      255
	MOVWF      find_best_solution_temp_pre_x_L0+0
	MOVLW      255
	MOVWF      find_best_solution_tem_pre_sub_index_L0+0
	MOVLW      255
	MOVWF      find_best_solution_temp_pre_risk_L0+0
	MOVLW      255
	MOVWF      find_best_solution_temp_pre_risk_L0+1
	CLRF       find_best_solution_temp_pre_count_L0+0
	MOVLW      255
	MOVWF      find_best_solution_temp_pre_high_L0+0
	MOVLW      255
	MOVWF      find_best_solution_temp_pre_hole_L0+0
	CLRF       find_best_solution_res_L0+0
;Teris.c,964 :: 		for(tem_sub_index = 0; tem_sub_index < g_char_info[g_char_info_index].num; tem_sub_index++)
	CLRF       find_best_solution_tem_sub_index_L0+0
L_find_best_solution167:
	MOVF       _g_char_info_index+0, 0
	MOVWF      R0+0
	CLRF       R0+1
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	MOVLW      _g_char_info+0
	ADDWF      R0+0, 1
	MOVLW      hi_addr(_g_char_info+0)
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      R0+1, 1
	INCF       R0+0, 1
	BTFSC      STATUS+0, 2
	INCF       R0+1, 1
	MOVF       R0+0, 0
	MOVWF      ___DoICPAddr+0
	MOVF       R0+1, 0
	MOVWF      ___DoICPAddr+1
	CALL       _____DoICP+0
	MOVWF      R1+0
	MOVF       R1+0, 0
	SUBWF      find_best_solution_tem_sub_index_L0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_find_best_solution168
;Teris.c,967 :: 		temp_cur_matrix44 = g_matrix44[g_char_info[g_char_info_index].start_index + tem_sub_index];
	MOVF       _g_char_info_index+0, 0
	MOVWF      R0+0
	CLRF       R0+1
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	MOVLW      _g_char_info+0
	ADDWF      R0+0, 1
	MOVLW      hi_addr(_g_char_info+0)
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      R0+1, 1
	MOVF       R0+0, 0
	MOVWF      ___DoICPAddr+0
	MOVF       R0+1, 0
	MOVWF      ___DoICPAddr+1
	CALL       _____DoICP+0
	MOVWF      R0+0
	MOVF       find_best_solution_tem_sub_index_L0+0, 0
	ADDWF      R0+0, 0
	MOVWF      R3+0
	CLRF       R3+1
	BTFSC      STATUS+0, 0
	INCF       R3+1, 1
	MOVLW      4
	MOVWF      R2+0
	MOVF       R3+0, 0
	MOVWF      R0+0
	MOVF       R3+1, 0
	MOVWF      R0+1
	MOVF       R2+0, 0
L__find_best_solution291:
	BTFSC      STATUS+0, 2
	GOTO       L__find_best_solution292
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__find_best_solution291
L__find_best_solution292:
	MOVF       R0+0, 0
	ADDLW      _g_matrix44+0
	MOVWF      ___DoICPAddr+0
	MOVLW      hi_addr(_g_matrix44+0)
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      R0+1, 0
	MOVWF      ___DoICPAddr+1
	MOVLW      16
	MOVWF      R2+0
	MOVLW      find_best_solution_temp_cur_matrix44_L0+0
	MOVWF      R1+0
L_find_best_solution170:
	CALL       _____DoICP+0
	MOVWF      R0+0
	MOVF       R1+0, 0
	MOVWF      FSR
	MOVF       R0+0, 0
	MOVWF      INDF+0
	INCF       R1+0, 1
	INCF       ___DoICPAddr+0, 1
	BTFSC      STATUS+0, 2
	INCF       ___DoICPAddr+1, 1
	DECF       R2+0, 1
	BTFSS      STATUS+0, 2
	GOTO       L_find_best_solution170
;Teris.c,968 :: 		left_most_index = left_most(cur_x, &temp_cur_matrix44, &g_matrix88);
	MOVF       _cur_x+0, 0
	MOVWF      FARG_left_most_x+0
	MOVLW      find_best_solution_temp_cur_matrix44_L0+0
	MOVWF      FARG_left_most_matrix_44+0
	MOVLW      _g_matrix88+0
	MOVWF      FARG_left_most_matrix_88+0
	CALL       _left_most+0
	MOVF       R0+0, 0
	MOVWF      find_best_solution_left_most_index_L0+0
;Teris.c,969 :: 		right_most_index = right_most(cur_x, &temp_cur_matrix44, &g_matrix88);
	MOVF       _cur_x+0, 0
	MOVWF      FARG_right_most_x+0
	MOVLW      find_best_solution_temp_cur_matrix44_L0+0
	MOVWF      FARG_right_most_matrix_44+0
	MOVLW      _g_matrix88+0
	MOVWF      FARG_right_most_matrix_88+0
	CALL       _right_most+0
	MOVF       R0+0, 0
	MOVWF      find_best_solution_right_most_index_L0+0
;Teris.c,971 :: 		for(temp_x = left_most_index; temp_x <= right_most_index; temp_x++)
	MOVF       find_best_solution_left_most_index_L0+0, 0
	MOVWF      find_best_solution_temp_x_L1+0
L_find_best_solution171:
	MOVLW      128
	XORWF      find_best_solution_right_most_index_L0+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORWF      find_best_solution_temp_x_L1+0, 0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 0
	GOTO       L_find_best_solution172
;Teris.c,973 :: 		temp_y = fall_off(temp_x, cur_y, &temp_cur_matrix44, &g_matrix88);
	MOVF       find_best_solution_temp_x_L1+0, 0
	MOVWF      FARG_fall_off_x+0
	MOVF       _cur_y+0, 0
	MOVWF      FARG_fall_off_y+0
	MOVLW      find_best_solution_temp_cur_matrix44_L0+0
	MOVWF      FARG_fall_off_matrix_44+0
	MOVLW      _g_matrix88+0
	MOVWF      FARG_fall_off_matrix_88+0
	CALL       _fall_off+0
	MOVF       R0+0, 0
	MOVWF      find_best_solution_temp_y_L0+0
;Teris.c,979 :: 		if(is_valid(temp_x, temp_y, &temp_cur_matrix44, &g_matrix88) == 0)
	MOVF       find_best_solution_temp_x_L1+0, 0
	MOVWF      FARG_is_valid_x+0
	MOVF       R0+0, 0
	MOVWF      FARG_is_valid_y+0
	MOVLW      find_best_solution_temp_cur_matrix44_L0+0
	MOVWF      FARG_is_valid_matrix_44+0
	MOVLW      _g_matrix88+0
	MOVWF      FARG_is_valid_matrix_88+0
	CALL       _is_valid+0
	MOVF       R0+0, 0
	XORLW      0
	BTFSS      STATUS+0, 2
	GOTO       L_find_best_solution174
;Teris.c,981 :: 		continue;
	GOTO       L_find_best_solution173
;Teris.c,982 :: 		}
L_find_best_solution174:
;Teris.c,983 :: 		res = 1;
	MOVLW      1
	MOVWF      find_best_solution_res_L0+0
;Teris.c,984 :: 		merge1(temp_x, temp_y, &temp_cur_matrix44, &g_matrix88, &temp_matrix88);
	MOVF       find_best_solution_temp_x_L1+0, 0
	MOVWF      FARG_merge1_x+0
	MOVF       find_best_solution_temp_y_L0+0, 0
	MOVWF      FARG_merge1_y+0
	MOVLW      find_best_solution_temp_cur_matrix44_L0+0
	MOVWF      FARG_merge1_matrix_44+0
	MOVLW      _g_matrix88+0
	MOVWF      FARG_merge1_matrix88_in+0
	MOVLW      find_best_solution_temp_matrix88_L0+0
	MOVWF      FARG_merge1_matrix88_out+0
	CALL       _merge1+0
;Teris.c,985 :: 		temp_count = delete_matrix(&temp_matrix88);
	MOVLW      find_best_solution_temp_matrix88_L0+0
	MOVWF      FARG_delete_matrix_matrix+0
	CALL       _delete_matrix+0
	MOVF       R0+0, 0
	MOVWF      find_best_solution_temp_count_L0+0
;Teris.c,986 :: 		temp_risk = evaluate(&temp_matrix88);
	MOVLW      find_best_solution_temp_matrix88_L0+0
	MOVWF      FARG_evaluate_matrix+0
	CALL       _evaluate+0
	MOVF       R0+0, 0
	MOVWF      find_best_solution_temp_risk_L0+0
	MOVF       R0+1, 0
	MOVWF      find_best_solution_temp_risk_L0+1
;Teris.c,987 :: 		temp_high = get_high_after_merge(temp_y, &temp_cur_matrix44);
	MOVF       find_best_solution_temp_y_L0+0, 0
	MOVWF      FARG_get_high_after_merge_y+0
	MOVLW      find_best_solution_temp_cur_matrix44_L0+0
	MOVWF      FARG_get_high_after_merge_matrix+0
	CALL       _get_high_after_merge+0
	MOVF       R0+0, 0
	MOVWF      find_best_solution_temp_high_L0+0
;Teris.c,988 :: 		temp_hole = get_holes_after_merge(&temp_matrix88);
	MOVLW      find_best_solution_temp_matrix88_L0+0
	MOVWF      FARG_get_holes_after_merge_matrix+0
	CALL       _get_holes_after_merge+0
	MOVF       R0+0, 0
	MOVWF      find_best_solution_temp_hole_L0+0
;Teris.c,993 :: 		if(temp_count > temp_pre_count)
	MOVF       find_best_solution_temp_count_L0+0, 0
	SUBWF      find_best_solution_temp_pre_count_L0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_find_best_solution175
;Teris.c,999 :: 		temp_pre_count = temp_count;
	MOVF       find_best_solution_temp_count_L0+0, 0
	MOVWF      find_best_solution_temp_pre_count_L0+0
;Teris.c,1000 :: 		temp_pre_risk = temp_risk;
	MOVF       find_best_solution_temp_risk_L0+0, 0
	MOVWF      find_best_solution_temp_pre_risk_L0+0
	MOVF       find_best_solution_temp_risk_L0+1, 0
	MOVWF      find_best_solution_temp_pre_risk_L0+1
;Teris.c,1001 :: 		temp_pre_high = temp_high;
	MOVF       find_best_solution_temp_high_L0+0, 0
	MOVWF      find_best_solution_temp_pre_high_L0+0
;Teris.c,1002 :: 		temp_pre_hole = temp_hole;
	MOVF       find_best_solution_temp_hole_L0+0, 0
	MOVWF      find_best_solution_temp_pre_hole_L0+0
;Teris.c,1003 :: 		tem_pre_sub_index = tem_sub_index;
	MOVF       find_best_solution_tem_sub_index_L0+0, 0
	MOVWF      find_best_solution_tem_pre_sub_index_L0+0
;Teris.c,1004 :: 		temp_pre_x = temp_x;
	MOVF       find_best_solution_temp_x_L1+0, 0
	MOVWF      find_best_solution_temp_pre_x_L0+0
;Teris.c,1005 :: 		}
	GOTO       L_find_best_solution176
L_find_best_solution175:
;Teris.c,1006 :: 		else if(temp_count == temp_pre_count)
	MOVF       find_best_solution_temp_count_L0+0, 0
	XORWF      find_best_solution_temp_pre_count_L0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L_find_best_solution177
;Teris.c,1008 :: 		if(get_high(&g_matrix88) <= MATRIX88_ROW_MAX/2 + 1)
	MOVLW      _g_matrix88+0
	MOVWF      FARG_get_high_matrix+0
	CALL       _get_high+0
	MOVF       R0+0, 0
	SUBLW      5
	BTFSS      STATUS+0, 0
	GOTO       L_find_best_solution178
;Teris.c,1016 :: 		if(temp_risk < temp_pre_risk)
	MOVF       find_best_solution_temp_pre_risk_L0+1, 0
	SUBWF      find_best_solution_temp_risk_L0+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__find_best_solution293
	MOVF       find_best_solution_temp_pre_risk_L0+0, 0
	SUBWF      find_best_solution_temp_risk_L0+0, 0
L__find_best_solution293:
	BTFSC      STATUS+0, 0
	GOTO       L_find_best_solution179
;Teris.c,1022 :: 		temp_pre_count = temp_count;
	MOVF       find_best_solution_temp_count_L0+0, 0
	MOVWF      find_best_solution_temp_pre_count_L0+0
;Teris.c,1023 :: 		temp_pre_risk = temp_risk;
	MOVF       find_best_solution_temp_risk_L0+0, 0
	MOVWF      find_best_solution_temp_pre_risk_L0+0
	MOVF       find_best_solution_temp_risk_L0+1, 0
	MOVWF      find_best_solution_temp_pre_risk_L0+1
;Teris.c,1024 :: 		temp_pre_high = temp_high;
	MOVF       find_best_solution_temp_high_L0+0, 0
	MOVWF      find_best_solution_temp_pre_high_L0+0
;Teris.c,1025 :: 		temp_pre_hole = temp_hole;
	MOVF       find_best_solution_temp_hole_L0+0, 0
	MOVWF      find_best_solution_temp_pre_hole_L0+0
;Teris.c,1026 :: 		tem_pre_sub_index = tem_sub_index;
	MOVF       find_best_solution_tem_sub_index_L0+0, 0
	MOVWF      find_best_solution_tem_pre_sub_index_L0+0
;Teris.c,1027 :: 		temp_pre_x = temp_x;
	MOVF       find_best_solution_temp_x_L1+0, 0
	MOVWF      find_best_solution_temp_pre_x_L0+0
;Teris.c,1028 :: 		}
	GOTO       L_find_best_solution180
L_find_best_solution179:
;Teris.c,1029 :: 		else if(temp_risk == temp_pre_risk)
	MOVF       find_best_solution_temp_risk_L0+1, 0
	XORWF      find_best_solution_temp_pre_risk_L0+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__find_best_solution294
	MOVF       find_best_solution_temp_pre_risk_L0+0, 0
	XORWF      find_best_solution_temp_risk_L0+0, 0
L__find_best_solution294:
	BTFSS      STATUS+0, 2
	GOTO       L_find_best_solution181
;Teris.c,1035 :: 		if(temp_high < temp_pre_high)
	MOVF       find_best_solution_temp_pre_high_L0+0, 0
	SUBWF      find_best_solution_temp_high_L0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_find_best_solution182
;Teris.c,1041 :: 		temp_pre_count = temp_count;
	MOVF       find_best_solution_temp_count_L0+0, 0
	MOVWF      find_best_solution_temp_pre_count_L0+0
;Teris.c,1042 :: 		temp_pre_risk = temp_risk;
	MOVF       find_best_solution_temp_risk_L0+0, 0
	MOVWF      find_best_solution_temp_pre_risk_L0+0
	MOVF       find_best_solution_temp_risk_L0+1, 0
	MOVWF      find_best_solution_temp_pre_risk_L0+1
;Teris.c,1043 :: 		temp_pre_high = temp_high;
	MOVF       find_best_solution_temp_high_L0+0, 0
	MOVWF      find_best_solution_temp_pre_high_L0+0
;Teris.c,1044 :: 		temp_pre_hole = temp_hole;
	MOVF       find_best_solution_temp_hole_L0+0, 0
	MOVWF      find_best_solution_temp_pre_hole_L0+0
;Teris.c,1045 :: 		tem_pre_sub_index = tem_sub_index;
	MOVF       find_best_solution_tem_sub_index_L0+0, 0
	MOVWF      find_best_solution_tem_pre_sub_index_L0+0
;Teris.c,1046 :: 		temp_pre_x = temp_x;
	MOVF       find_best_solution_temp_x_L1+0, 0
	MOVWF      find_best_solution_temp_pre_x_L0+0
;Teris.c,1047 :: 		}
	GOTO       L_find_best_solution183
L_find_best_solution182:
;Teris.c,1048 :: 		else if(temp_high == temp_pre_high)
	MOVF       find_best_solution_temp_high_L0+0, 0
	XORWF      find_best_solution_temp_pre_high_L0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L_find_best_solution184
;Teris.c,1054 :: 		if(temp_hole < temp_pre_hole)
	MOVF       find_best_solution_temp_pre_hole_L0+0, 0
	SUBWF      find_best_solution_temp_hole_L0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_find_best_solution185
;Teris.c,1060 :: 		temp_pre_count = temp_count;
	MOVF       find_best_solution_temp_count_L0+0, 0
	MOVWF      find_best_solution_temp_pre_count_L0+0
;Teris.c,1061 :: 		temp_pre_risk = temp_risk;
	MOVF       find_best_solution_temp_risk_L0+0, 0
	MOVWF      find_best_solution_temp_pre_risk_L0+0
	MOVF       find_best_solution_temp_risk_L0+1, 0
	MOVWF      find_best_solution_temp_pre_risk_L0+1
;Teris.c,1062 :: 		temp_pre_high = temp_high;
	MOVF       find_best_solution_temp_high_L0+0, 0
	MOVWF      find_best_solution_temp_pre_high_L0+0
;Teris.c,1063 :: 		temp_pre_hole = temp_hole;
	MOVF       find_best_solution_temp_hole_L0+0, 0
	MOVWF      find_best_solution_temp_pre_hole_L0+0
;Teris.c,1064 :: 		tem_pre_sub_index = tem_sub_index;
	MOVF       find_best_solution_tem_sub_index_L0+0, 0
	MOVWF      find_best_solution_tem_pre_sub_index_L0+0
;Teris.c,1065 :: 		temp_pre_x = temp_x;
	MOVF       find_best_solution_temp_x_L1+0, 0
	MOVWF      find_best_solution_temp_pre_x_L0+0
;Teris.c,1066 :: 		}
L_find_best_solution185:
;Teris.c,1068 :: 		}
L_find_best_solution184:
L_find_best_solution183:
;Teris.c,1070 :: 		}
L_find_best_solution181:
L_find_best_solution180:
;Teris.c,1071 :: 		}
	GOTO       L_find_best_solution186
L_find_best_solution178:
;Teris.c,1079 :: 		if(temp_high < temp_pre_high)
	MOVF       find_best_solution_temp_pre_high_L0+0, 0
	SUBWF      find_best_solution_temp_high_L0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_find_best_solution187
;Teris.c,1085 :: 		temp_pre_count = temp_count;
	MOVF       find_best_solution_temp_count_L0+0, 0
	MOVWF      find_best_solution_temp_pre_count_L0+0
;Teris.c,1086 :: 		temp_pre_risk = temp_risk;
	MOVF       find_best_solution_temp_risk_L0+0, 0
	MOVWF      find_best_solution_temp_pre_risk_L0+0
	MOVF       find_best_solution_temp_risk_L0+1, 0
	MOVWF      find_best_solution_temp_pre_risk_L0+1
;Teris.c,1087 :: 		temp_pre_high = temp_high;
	MOVF       find_best_solution_temp_high_L0+0, 0
	MOVWF      find_best_solution_temp_pre_high_L0+0
;Teris.c,1088 :: 		temp_pre_hole = temp_hole;
	MOVF       find_best_solution_temp_hole_L0+0, 0
	MOVWF      find_best_solution_temp_pre_hole_L0+0
;Teris.c,1089 :: 		tem_pre_sub_index = tem_sub_index;
	MOVF       find_best_solution_tem_sub_index_L0+0, 0
	MOVWF      find_best_solution_tem_pre_sub_index_L0+0
;Teris.c,1090 :: 		temp_pre_x = temp_x;
	MOVF       find_best_solution_temp_x_L1+0, 0
	MOVWF      find_best_solution_temp_pre_x_L0+0
;Teris.c,1091 :: 		}
	GOTO       L_find_best_solution188
L_find_best_solution187:
;Teris.c,1092 :: 		else if(temp_high == temp_pre_high)
	MOVF       find_best_solution_temp_high_L0+0, 0
	XORWF      find_best_solution_temp_pre_high_L0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L_find_best_solution189
;Teris.c,1098 :: 		if(temp_hole < temp_pre_hole)
	MOVF       find_best_solution_temp_pre_hole_L0+0, 0
	SUBWF      find_best_solution_temp_hole_L0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_find_best_solution190
;Teris.c,1104 :: 		temp_pre_count = temp_count;
	MOVF       find_best_solution_temp_count_L0+0, 0
	MOVWF      find_best_solution_temp_pre_count_L0+0
;Teris.c,1105 :: 		temp_pre_risk = temp_risk;
	MOVF       find_best_solution_temp_risk_L0+0, 0
	MOVWF      find_best_solution_temp_pre_risk_L0+0
	MOVF       find_best_solution_temp_risk_L0+1, 0
	MOVWF      find_best_solution_temp_pre_risk_L0+1
;Teris.c,1106 :: 		temp_pre_high = temp_high;
	MOVF       find_best_solution_temp_high_L0+0, 0
	MOVWF      find_best_solution_temp_pre_high_L0+0
;Teris.c,1107 :: 		temp_pre_hole = temp_hole;
	MOVF       find_best_solution_temp_hole_L0+0, 0
	MOVWF      find_best_solution_temp_pre_hole_L0+0
;Teris.c,1108 :: 		tem_pre_sub_index = tem_sub_index;
	MOVF       find_best_solution_tem_sub_index_L0+0, 0
	MOVWF      find_best_solution_tem_pre_sub_index_L0+0
;Teris.c,1109 :: 		temp_pre_x = temp_x;
	MOVF       find_best_solution_temp_x_L1+0, 0
	MOVWF      find_best_solution_temp_pre_x_L0+0
;Teris.c,1110 :: 		}
	GOTO       L_find_best_solution191
L_find_best_solution190:
;Teris.c,1111 :: 		else if(temp_hole == temp_pre_hole)
	MOVF       find_best_solution_temp_hole_L0+0, 0
	XORWF      find_best_solution_temp_pre_hole_L0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L_find_best_solution192
;Teris.c,1117 :: 		if(temp_risk < temp_pre_risk)
	MOVF       find_best_solution_temp_pre_risk_L0+1, 0
	SUBWF      find_best_solution_temp_risk_L0+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__find_best_solution295
	MOVF       find_best_solution_temp_pre_risk_L0+0, 0
	SUBWF      find_best_solution_temp_risk_L0+0, 0
L__find_best_solution295:
	BTFSC      STATUS+0, 0
	GOTO       L_find_best_solution193
;Teris.c,1123 :: 		temp_pre_count = temp_count;
	MOVF       find_best_solution_temp_count_L0+0, 0
	MOVWF      find_best_solution_temp_pre_count_L0+0
;Teris.c,1124 :: 		temp_pre_risk = temp_risk;
	MOVF       find_best_solution_temp_risk_L0+0, 0
	MOVWF      find_best_solution_temp_pre_risk_L0+0
	MOVF       find_best_solution_temp_risk_L0+1, 0
	MOVWF      find_best_solution_temp_pre_risk_L0+1
;Teris.c,1125 :: 		temp_pre_high = temp_high;
	MOVF       find_best_solution_temp_high_L0+0, 0
	MOVWF      find_best_solution_temp_pre_high_L0+0
;Teris.c,1126 :: 		temp_pre_hole = temp_hole;
	MOVF       find_best_solution_temp_hole_L0+0, 0
	MOVWF      find_best_solution_temp_pre_hole_L0+0
;Teris.c,1127 :: 		tem_pre_sub_index = tem_sub_index;
	MOVF       find_best_solution_tem_sub_index_L0+0, 0
	MOVWF      find_best_solution_tem_pre_sub_index_L0+0
;Teris.c,1128 :: 		temp_pre_x = temp_x;
	MOVF       find_best_solution_temp_x_L1+0, 0
	MOVWF      find_best_solution_temp_pre_x_L0+0
;Teris.c,1129 :: 		}
L_find_best_solution193:
;Teris.c,1130 :: 		}
L_find_best_solution192:
L_find_best_solution191:
;Teris.c,1131 :: 		}
L_find_best_solution189:
L_find_best_solution188:
;Teris.c,1132 :: 		}
L_find_best_solution186:
;Teris.c,1133 :: 		}
L_find_best_solution177:
L_find_best_solution176:
;Teris.c,1140 :: 		}
L_find_best_solution173:
;Teris.c,971 :: 		for(temp_x = left_most_index; temp_x <= right_most_index; temp_x++)
	INCF       find_best_solution_temp_x_L1+0, 1
;Teris.c,1140 :: 		}
	GOTO       L_find_best_solution171
L_find_best_solution172:
;Teris.c,964 :: 		for(tem_sub_index = 0; tem_sub_index < g_char_info[g_char_info_index].num; tem_sub_index++)
	INCF       find_best_solution_tem_sub_index_L0+0, 1
;Teris.c,1141 :: 		}
	GOTO       L_find_best_solution167
L_find_best_solution168:
;Teris.c,1142 :: 		if(res == 1)
	MOVF       find_best_solution_res_L0+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_find_best_solution194
;Teris.c,1144 :: 		g_char_info_sub_index = tem_pre_sub_index;
	MOVF       find_best_solution_tem_pre_sub_index_L0+0, 0
	MOVWF      _g_char_info_sub_index+0
;Teris.c,1145 :: 		cur_x = temp_pre_x;
	MOVF       find_best_solution_temp_pre_x_L0+0, 0
	MOVWF      _cur_x+0
;Teris.c,1153 :: 		}
	GOTO       L_find_best_solution195
L_find_best_solution194:
;Teris.c,1160 :: 		}
L_find_best_solution195:
;Teris.c,1161 :: 		return res;
	MOVF       find_best_solution_res_L0+0, 0
	MOVWF      R0+0
;Teris.c,1162 :: 		}
L_end_find_best_solution:
	RETURN
; end of _find_best_solution

_main:

;Teris.c,1246 :: 		int main()
;Teris.c,1273 :: 		Chip_Select_Direction = 0;    // Set RA2 pin as output.
	BCF        TRISA2_bit+0, 2
;Teris.c,1274 :: 		SPI1_init();                  // Initialize SPI1 module.
	CALL       _SPI1_Init+0
;Teris.c,1276 :: 		max7219_init1(); // initialize  max7219.
	CALL       _max7219_init1+0
;Teris.c,1277 :: 		srand(0);
	CLRF       FARG_srand_x+0
	CLRF       FARG_srand_x+1
	CALL       _srand+0
;Teris.c,1279 :: 		UART1_Init(9600);
	MOVLW      129
	MOVWF      SPBRG+0
	BSF        TXSTA+0, 2
	CALL       _UART1_Init+0
;Teris.c,1281 :: 		__start:
___main___start:
;Teris.c,1282 :: 		printf_console_MATRIX88(&g_matrix88);
	MOVLW      _g_matrix88+0
	MOVWF      FARG_printf_console_MATRIX88_matrix+0
	CALL       _printf_console_MATRIX88+0
;Teris.c,1283 :: 		printf_Screen();
	CALL       _printf_Screen+0
;Teris.c,1284 :: 		Delay_ms(1000);
	MOVLW      26
	MOVWF      R11+0
	MOVLW      94
	MOVWF      R12+0
	MOVLW      110
	MOVWF      R13+0
L_main196:
	DECFSZ     R13+0, 1
	GOTO       L_main196
	DECFSZ     R12+0, 1
	GOTO       L_main196
	DECFSZ     R11+0, 1
	GOTO       L_main196
	NOP
;Teris.c,1288 :: 		while(1)
L_main197:
;Teris.c,1290 :: 		cur_y = 0;
	CLRF       _cur_y+0
;Teris.c,1291 :: 		cur_x = 2, cur_y = 0;
	MOVLW      2
	MOVWF      _cur_x+0
	CLRF       _cur_y+0
;Teris.c,1292 :: 		g_char_info_index = 0;//char_info_index_rand();
	CLRF       _g_char_info_index+0
;Teris.c,1297 :: 		sprintl(g_debug, "%d\r\n", g_char_info_index);
	MOVLW      _g_debug+0
	MOVWF      FARG_sprintl_wh+0
	MOVLW      ?lstr_6_Teris+0
	MOVWF      FARG_sprintl_f+0
	MOVLW      hi_addr(?lstr_6_Teris+0)
	MOVWF      FARG_sprintl_f+1
	CLRF       FARG_sprintl_wh+3
	CALL       _sprintl+0
;Teris.c,1298 :: 		UART1_Write_Text(g_debug);
	MOVLW      _g_debug+0
	MOVWF      FARG_UART1_Write_Text_uart_text+0
	CALL       _UART1_Write_Text+0
;Teris.c,1300 :: 		if(find_best_solution() == 0)
	CALL       _find_best_solution+0
	MOVF       R0+0, 0
	XORLW      0
	BTFSS      STATUS+0, 2
	GOTO       L_main199
;Teris.c,1305 :: 		UART1_Write_Text("GAME OVER!!!\r\n");
	MOVLW      ?lstr7_Teris+0
	MOVWF      FARG_UART1_Write_Text_uart_text+0
	CALL       _UART1_Write_Text+0
;Teris.c,1307 :: 		goto __start;
	GOTO       ___main___start
;Teris.c,1308 :: 		}
L_main199:
;Teris.c,1309 :: 		g_cur_matrix44 = g_matrix44[g_char_info[g_char_info_index].start_index + g_char_info_sub_index];
	MOVF       _g_char_info_index+0, 0
	MOVWF      R0+0
	CLRF       R0+1
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	MOVLW      _g_char_info+0
	ADDWF      R0+0, 1
	MOVLW      hi_addr(_g_char_info+0)
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      R0+1, 1
	MOVF       R0+0, 0
	MOVWF      ___DoICPAddr+0
	MOVF       R0+1, 0
	MOVWF      ___DoICPAddr+1
	CALL       _____DoICP+0
	MOVWF      R0+0
	MOVF       _g_char_info_sub_index+0, 0
	ADDWF      R0+0, 0
	MOVWF      R3+0
	CLRF       R3+1
	BTFSC      STATUS+0, 0
	INCF       R3+1, 1
	MOVLW      4
	MOVWF      R2+0
	MOVF       R3+0, 0
	MOVWF      R0+0
	MOVF       R3+1, 0
	MOVWF      R0+1
	MOVF       R2+0, 0
L__main297:
	BTFSC      STATUS+0, 2
	GOTO       L__main298
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__main297
L__main298:
	MOVF       R0+0, 0
	ADDLW      _g_matrix44+0
	MOVWF      ___DoICPAddr+0
	MOVLW      hi_addr(_g_matrix44+0)
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      R0+1, 0
	MOVWF      ___DoICPAddr+1
	MOVLW      16
	MOVWF      R2+0
	MOVLW      _g_cur_matrix44+0
	MOVWF      R1+0
L_main200:
	CALL       _____DoICP+0
	MOVWF      R0+0
	MOVF       R1+0, 0
	MOVWF      FSR
	MOVF       R0+0, 0
	MOVWF      INDF+0
	INCF       R1+0, 1
	INCF       ___DoICPAddr+0, 1
	BTFSC      STATUS+0, 2
	INCF       ___DoICPAddr+1, 1
	DECF       R2+0, 1
	BTFSS      STATUS+0, 2
	GOTO       L_main200
;Teris.c,1310 :: 		while(1)
L_main201:
;Teris.c,1312 :: 		hit_res = hit_land1(cur_x, cur_y, &g_cur_matrix44, &g_matrix88);
	MOVF       _cur_x+0, 0
	MOVWF      FARG_hit_land1_x+0
	MOVF       _cur_y+0, 0
	MOVWF      FARG_hit_land1_y+0
	MOVLW      _g_cur_matrix44+0
	MOVWF      FARG_hit_land1_matrix_44+0
	MOVLW      _g_matrix88+0
	MOVWF      FARG_hit_land1_matrix_88+0
	CALL       _hit_land1+0
	MOVF       R0+0, 0
	MOVWF      main_hit_res_L0+0
;Teris.c,1316 :: 		sprinti(g_debug, "hit_res = %d\r\n", hit_res);
	MOVLW      _g_debug+0
	MOVWF      FARG_sprinti_wh+0
	MOVLW      ?lstr_8_Teris+0
	MOVWF      FARG_sprinti_f+0
	MOVLW      hi_addr(?lstr_8_Teris+0)
	MOVWF      FARG_sprinti_f+1
	MOVF       R0+0, 0
	MOVWF      FARG_sprinti_wh+3
	CALL       _sprinti+0
;Teris.c,1317 :: 		UART1_Write_Text(g_debug);
	MOVLW      _g_debug+0
	MOVWF      FARG_UART1_Write_Text_uart_text+0
	CALL       _UART1_Write_Text+0
;Teris.c,1319 :: 		merge(cur_x, cur_y, &g_cur_matrix44, &g_matrix88);
	MOVF       _cur_x+0, 0
	MOVWF      FARG_merge_x+0
	MOVF       _cur_y+0, 0
	MOVWF      FARG_merge_y+0
	MOVLW      _g_cur_matrix44+0
	MOVWF      FARG_merge_matrix_44+0
	MOVLW      _g_matrix88+0
	MOVWF      FARG_merge_matrix_88+0
	CALL       _merge+0
;Teris.c,1320 :: 		if(hit_res == 1)
	MOVF       main_hit_res_L0+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_main203
;Teris.c,1322 :: 		printf_Screen();
	CALL       _printf_Screen+0
;Teris.c,1326 :: 		Delay_ms(100);
	MOVLW      3
	MOVWF      R11+0
	MOVLW      138
	MOVWF      R12+0
	MOVLW      85
	MOVWF      R13+0
L_main204:
	DECFSZ     R13+0, 1
	GOTO       L_main204
	DECFSZ     R12+0, 1
	GOTO       L_main204
	DECFSZ     R11+0, 1
	GOTO       L_main204
	NOP
	NOP
;Teris.c,1328 :: 		delete_matrix(&g_matrix88);
	MOVLW      _g_matrix88+0
	MOVWF      FARG_delete_matrix_matrix+0
	CALL       _delete_matrix+0
;Teris.c,1329 :: 		}
L_main203:
;Teris.c,1333 :: 		UART1_Write_Text("printf_console_MATRIX88\r\n");
	MOVLW      ?lstr9_Teris+0
	MOVWF      FARG_UART1_Write_Text_uart_text+0
	CALL       _UART1_Write_Text+0
;Teris.c,1335 :: 		printf_console_MATRIX88(&g_matrix88);
	MOVLW      _g_matrix88+0
	MOVWF      FARG_printf_console_MATRIX88_matrix+0
	CALL       _printf_console_MATRIX88+0
;Teris.c,1336 :: 		printf_Screen();
	CALL       _printf_Screen+0
;Teris.c,1337 :: 		if(hit_res == 0)
	MOVF       main_hit_res_L0+0, 0
	XORLW      0
	BTFSS      STATUS+0, 2
	GOTO       L_main205
;Teris.c,1339 :: 		clear(cur_x, cur_y, &g_cur_matrix44, &g_matrix88);
	MOVF       _cur_x+0, 0
	MOVWF      FARG_clear_x+0
	MOVF       _cur_y+0, 0
	MOVWF      FARG_clear_y+0
	MOVLW      _g_cur_matrix44+0
	MOVWF      FARG_clear_matrix_44+0
	MOVLW      _g_matrix88+0
	MOVWF      FARG_clear_matrix_88+0
	CALL       _clear+0
;Teris.c,1340 :: 		}
	GOTO       L_main206
L_main205:
;Teris.c,1343 :: 		break;
	GOTO       L_main202
;Teris.c,1344 :: 		}
L_main206:
;Teris.c,1348 :: 		Delay_ms(1000);
	MOVLW      26
	MOVWF      R11+0
	MOVLW      94
	MOVWF      R12+0
	MOVLW      110
	MOVWF      R13+0
L_main207:
	DECFSZ     R13+0, 1
	GOTO       L_main207
	DECFSZ     R12+0, 1
	GOTO       L_main207
	DECFSZ     R11+0, 1
	GOTO       L_main207
	NOP
;Teris.c,1350 :: 		cur_y++;
	INCF       _cur_y+0, 1
;Teris.c,1351 :: 		}
	GOTO       L_main201
L_main202:
;Teris.c,1352 :: 		}
	GOTO       L_main197
;Teris.c,1362 :: 		}
L_end_main:
	GOTO       $+0
; end of _main
