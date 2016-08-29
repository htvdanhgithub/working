
_Cus_UART1_Write_Text_Item:

;Teris.c,234 :: 		void Cus_UART1_Write_Text_Item(char * UART_text)
;Teris.c,236 :: 		while (UART1_Tx_Idle() == 0);
L_Cus_UART1_Write_Text_Item0:
	CALL       _UART1_Tx_Idle+0
	MOVF       R0+0, 0
	XORLW      0
	BTFSS      STATUS+0, 2
	GOTO       L_Cus_UART1_Write_Text_Item1
	GOTO       L_Cus_UART1_Write_Text_Item0
L_Cus_UART1_Write_Text_Item1:
;Teris.c,237 :: 		UART1_Write_Text(UART_text);
	MOVF       FARG_Cus_UART1_Write_Text_Item_UART_text+0, 0
	MOVWF      FARG_UART1_Write_Text_uart_text+0
	CALL       _UART1_Write_Text+0
;Teris.c,238 :: 		}
L_end_Cus_UART1_Write_Text_Item:
	RETURN
; end of _Cus_UART1_Write_Text_Item

_Cus_UART1_Write_Item:

;Teris.c,239 :: 		void Cus_UART1_Write_Item(char UART_data)
;Teris.c,241 :: 		while (UART1_Tx_Idle() == 0);
L_Cus_UART1_Write_Item2:
	CALL       _UART1_Tx_Idle+0
	MOVF       R0+0, 0
	XORLW      0
	BTFSS      STATUS+0, 2
	GOTO       L_Cus_UART1_Write_Item3
	GOTO       L_Cus_UART1_Write_Item2
L_Cus_UART1_Write_Item3:
;Teris.c,242 :: 		UART1_Write(UART_data);
	MOVF       FARG_Cus_UART1_Write_Item_UART_data+0, 0
	MOVWF      FARG_UART1_Write_data_+0
	CALL       _UART1_Write+0
;Teris.c,243 :: 		}
L_end_Cus_UART1_Write_Item:
	RETURN
; end of _Cus_UART1_Write_Item

_Cus_UART1_Write_Text:

;Teris.c,244 :: 		void Cus_UART1_Write_Text(char * lable, char * UART_text)
;Teris.c,246 :: 		Cus_UART1_Write_Text_Item(lable);
	MOVF       FARG_Cus_UART1_Write_Text_lable+0, 0
	MOVWF      FARG_Cus_UART1_Write_Text_Item_UART_text+0
	CALL       _Cus_UART1_Write_Text_Item+0
;Teris.c,247 :: 		Cus_UART1_Write_Text_Item(":");
	MOVLW      ?lstr1_Teris+0
	MOVWF      FARG_Cus_UART1_Write_Text_Item_UART_text+0
	CALL       _Cus_UART1_Write_Text_Item+0
;Teris.c,248 :: 		Cus_UART1_Write_Text_Item(UART_text);
	MOVF       FARG_Cus_UART1_Write_Text_UART_text+0, 0
	MOVWF      FARG_Cus_UART1_Write_Text_Item_UART_text+0
	CALL       _Cus_UART1_Write_Text_Item+0
;Teris.c,249 :: 		Cus_UART1_Write_Text_Item("\r\n");
	MOVLW      ?lstr2_Teris+0
	MOVWF      FARG_Cus_UART1_Write_Text_Item_UART_text+0
	CALL       _Cus_UART1_Write_Text_Item+0
;Teris.c,250 :: 		}
L_end_Cus_UART1_Write_Text:
	RETURN
; end of _Cus_UART1_Write_Text

_Cus_UART1_Write_Int:

;Teris.c,251 :: 		void Cus_UART1_Write_Int(char * lable, int UART_data)
;Teris.c,254 :: 		Cus_UART1_Write_Text_Item(lable);
	MOVF       FARG_Cus_UART1_Write_Int_lable+0, 0
	MOVWF      FARG_Cus_UART1_Write_Text_Item_UART_text+0
	CALL       _Cus_UART1_Write_Text_Item+0
;Teris.c,255 :: 		Cus_UART1_Write_Text_Item(":");
	MOVLW      ?lstr3_Teris+0
	MOVWF      FARG_Cus_UART1_Write_Text_Item_UART_text+0
	CALL       _Cus_UART1_Write_Text_Item+0
;Teris.c,256 :: 		IntToStr(UART_data, text);
	MOVF       FARG_Cus_UART1_Write_Int_UART_data+0, 0
	MOVWF      FARG_IntToStr_input+0
	MOVF       FARG_Cus_UART1_Write_Int_UART_data+1, 0
	MOVWF      FARG_IntToStr_input+1
	MOVLW      Cus_UART1_Write_Int_text_L0+0
	MOVWF      FARG_IntToStr_output+0
	CALL       _IntToStr+0
;Teris.c,257 :: 		Cus_UART1_Write_Text_Item(text);
	MOVLW      Cus_UART1_Write_Int_text_L0+0
	MOVWF      FARG_Cus_UART1_Write_Text_Item_UART_text+0
	CALL       _Cus_UART1_Write_Text_Item+0
;Teris.c,258 :: 		Cus_UART1_Write_Text_Item("\r\n");
	MOVLW      ?lstr4_Teris+0
	MOVWF      FARG_Cus_UART1_Write_Text_Item_UART_text+0
	CALL       _Cus_UART1_Write_Text_Item+0
;Teris.c,259 :: 		}
L_end_Cus_UART1_Write_Int:
	RETURN
; end of _Cus_UART1_Write_Int

_max7219_init1:

;Teris.c,261 :: 		void max7219_init1()
;Teris.c,263 :: 		Chip_Select = 0;       // SELECT MAX
	BCF        RA2_bit+0, 2
;Teris.c,264 :: 		SPI1_write(0x09);      // BCD mode for digit decoding
	MOVLW      9
	MOVWF      FARG_SPI1_Write_data_+0
	CALL       _SPI1_Write+0
;Teris.c,265 :: 		SPI1_write(0x00);
	CLRF       FARG_SPI1_Write_data_+0
	CALL       _SPI1_Write+0
;Teris.c,266 :: 		Chip_Select = 1;       // DESELECT MAX
	BSF        RA2_bit+0, 2
;Teris.c,268 :: 		Chip_Select = 0;       // SELECT MAX
	BCF        RA2_bit+0, 2
;Teris.c,269 :: 		SPI1_write(0x0A);
	MOVLW      10
	MOVWF      FARG_SPI1_Write_data_+0
	CALL       _SPI1_Write+0
;Teris.c,270 :: 		SPI1_write(0x0F);      // Segment luminosity intensity
	MOVLW      15
	MOVWF      FARG_SPI1_Write_data_+0
	CALL       _SPI1_Write+0
;Teris.c,271 :: 		Chip_Select = 1;       // DESELECT MAX
	BSF        RA2_bit+0, 2
;Teris.c,273 :: 		Chip_Select = 0;       // SELECT MAX
	BCF        RA2_bit+0, 2
;Teris.c,274 :: 		SPI1_write(0x0B);
	MOVLW      11
	MOVWF      FARG_SPI1_Write_data_+0
	CALL       _SPI1_Write+0
;Teris.c,275 :: 		SPI1_write(0x07);      // Display refresh
	MOVLW      7
	MOVWF      FARG_SPI1_Write_data_+0
	CALL       _SPI1_Write+0
;Teris.c,276 :: 		Chip_Select = 1;       // DESELECT MAX
	BSF        RA2_bit+0, 2
;Teris.c,278 :: 		Chip_Select = 0;       // SELECT MAX
	BCF        RA2_bit+0, 2
;Teris.c,279 :: 		SPI1_write(0x0C);
	MOVLW      12
	MOVWF      FARG_SPI1_Write_data_+0
	CALL       _SPI1_Write+0
;Teris.c,280 :: 		SPI1_write(0x01);      // Turn on the display
	MOVLW      1
	MOVWF      FARG_SPI1_Write_data_+0
	CALL       _SPI1_Write+0
;Teris.c,281 :: 		Chip_Select = 1;       // DESELECT MAX
	BSF        RA2_bit+0, 2
;Teris.c,283 :: 		Chip_Select = 0;       // SELECT MAX
	BCF        RA2_bit+0, 2
;Teris.c,284 :: 		SPI1_write(0x00);
	CLRF       FARG_SPI1_Write_data_+0
	CALL       _SPI1_Write+0
;Teris.c,285 :: 		SPI1_write(0xFF);      // No test
	MOVLW      255
	MOVWF      FARG_SPI1_Write_data_+0
	CALL       _SPI1_Write+0
;Teris.c,286 :: 		Chip_Select = 1;       // DESELECT MAX
	BSF        RA2_bit+0, 2
;Teris.c,287 :: 		}
L_end_max7219_init1:
	RETURN
; end of _max7219_init1

_Write_Byte:

;Teris.c,290 :: 		void Write_Byte(unsigned short myColumn, unsigned short myValue)
;Teris.c,292 :: 		Chip_Select = 0;       // select max7219.
	BCF        RA2_bit+0, 2
;Teris.c,293 :: 		SPI1_write(myColumn);  // send myColumn value to max7219 (digit place).
	MOVF       FARG_Write_Byte_myColumn+0, 0
	MOVWF      FARG_SPI1_Write_data_+0
	CALL       _SPI1_Write+0
;Teris.c,294 :: 		SPI1_write(myValue);   // send myValue value to max7219 (digit place).
	MOVF       FARG_Write_Byte_myValue+0, 0
	MOVWF      FARG_SPI1_Write_data_+0
	CALL       _SPI1_Write+0
;Teris.c,295 :: 		Chip_Select = 1;       // deselect max7219.
	BSF        RA2_bit+0, 2
;Teris.c,296 :: 		}
L_end_Write_Byte:
	RETURN
; end of _Write_Byte

_printf_console_MATRIX44:

;Teris.c,322 :: 		void printf_console_MATRIX44(short x, short y, const MATRIX44* matrix)
;Teris.c,326 :: 		Cus_UART1_Write_Text_Item("<<<<<<<<<<<<<<<<<<<<MATRIX44\r\n");
	MOVLW      ?lstr5_Teris+0
	MOVWF      FARG_Cus_UART1_Write_Text_Item_UART_text+0
	CALL       _Cus_UART1_Write_Text_Item+0
;Teris.c,327 :: 		for(row = 0; row < MATRIX88_ROW_MAX; row++)
	CLRF       printf_console_MATRIX44_row_L0+0
L_printf_console_MATRIX444:
	MOVLW      128
	XORWF      printf_console_MATRIX44_row_L0+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      8
	SUBWF      R0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_printf_console_MATRIX445
;Teris.c,329 :: 		for(col = 0; col < MATRIX88_COLUMN_MAX; col++)
	CLRF       printf_console_MATRIX44_col_L0+0
L_printf_console_MATRIX447:
	MOVLW      128
	XORWF      printf_console_MATRIX44_col_L0+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      8
	SUBWF      R0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_printf_console_MATRIX448
;Teris.c,331 :: 		if((row - y >= 0) && (row - y < MATRIX44_ROW_MAX)
	MOVF       FARG_printf_console_MATRIX44_y+0, 0
	SUBWF      printf_console_MATRIX44_row_L0+0, 0
	MOVWF      R1+0
	CLRF       R1+1
	BTFSS      STATUS+0, 0
	DECF       R1+1, 1
	MOVLW      0
	BTFSC      printf_console_MATRIX44_row_L0+0, 7
	MOVLW      255
	ADDWF      R1+1, 1
	MOVLW      1
	BTFSS      FARG_printf_console_MATRIX44_y+0, 7
	MOVLW      0
	ADDWF      R1+1, 1
	MOVLW      128
	XORWF      R1+1, 0
	MOVWF      R0+0
	MOVLW      128
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__printf_console_MATRIX44223
	MOVLW      0
	SUBWF      R1+0, 0
L__printf_console_MATRIX44223:
	BTFSS      STATUS+0, 0
	GOTO       L_printf_console_MATRIX4412
	MOVF       FARG_printf_console_MATRIX44_y+0, 0
	SUBWF      printf_console_MATRIX44_row_L0+0, 0
	MOVWF      R1+0
	CLRF       R1+1
	BTFSS      STATUS+0, 0
	DECF       R1+1, 1
	MOVLW      0
	BTFSC      printf_console_MATRIX44_row_L0+0, 7
	MOVLW      255
	ADDWF      R1+1, 1
	MOVLW      1
	BTFSS      FARG_printf_console_MATRIX44_y+0, 7
	MOVLW      0
	ADDWF      R1+1, 1
	MOVLW      128
	XORWF      R1+1, 0
	MOVWF      R0+0
	MOVLW      128
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__printf_console_MATRIX44224
	MOVLW      4
	SUBWF      R1+0, 0
L__printf_console_MATRIX44224:
	BTFSC      STATUS+0, 0
	GOTO       L_printf_console_MATRIX4412
;Teris.c,332 :: 		&& (col - x >= 0) && (col - x < MATRIX44_COLUMN_MAX)
	MOVF       FARG_printf_console_MATRIX44_x+0, 0
	SUBWF      printf_console_MATRIX44_col_L0+0, 0
	MOVWF      R1+0
	CLRF       R1+1
	BTFSS      STATUS+0, 0
	DECF       R1+1, 1
	MOVLW      0
	BTFSC      printf_console_MATRIX44_col_L0+0, 7
	MOVLW      255
	ADDWF      R1+1, 1
	MOVLW      1
	BTFSS      FARG_printf_console_MATRIX44_x+0, 7
	MOVLW      0
	ADDWF      R1+1, 1
	MOVLW      128
	XORWF      R1+1, 0
	MOVWF      R0+0
	MOVLW      128
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__printf_console_MATRIX44225
	MOVLW      0
	SUBWF      R1+0, 0
L__printf_console_MATRIX44225:
	BTFSS      STATUS+0, 0
	GOTO       L_printf_console_MATRIX4412
	MOVF       FARG_printf_console_MATRIX44_x+0, 0
	SUBWF      printf_console_MATRIX44_col_L0+0, 0
	MOVWF      R1+0
	CLRF       R1+1
	BTFSS      STATUS+0, 0
	DECF       R1+1, 1
	MOVLW      0
	BTFSC      printf_console_MATRIX44_col_L0+0, 7
	MOVLW      255
	ADDWF      R1+1, 1
	MOVLW      1
	BTFSS      FARG_printf_console_MATRIX44_x+0, 7
	MOVLW      0
	ADDWF      R1+1, 1
	MOVLW      128
	XORWF      R1+1, 0
	MOVWF      R0+0
	MOVLW      128
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__printf_console_MATRIX44226
	MOVLW      4
	SUBWF      R1+0, 0
L__printf_console_MATRIX44226:
	BTFSC      STATUS+0, 0
	GOTO       L_printf_console_MATRIX4412
;Teris.c,333 :: 		&& (matrix->cell[row - y][col - x] == 1))
	MOVF       FARG_printf_console_MATRIX44_y+0, 0
	SUBWF      printf_console_MATRIX44_row_L0+0, 0
	MOVWF      R3+0
	CLRF       R3+1
	BTFSS      STATUS+0, 0
	DECF       R3+1, 1
	MOVLW      0
	BTFSC      printf_console_MATRIX44_row_L0+0, 7
	MOVLW      255
	ADDWF      R3+1, 1
	MOVLW      1
	BTFSS      FARG_printf_console_MATRIX44_y+0, 7
	MOVLW      0
	ADDWF      R3+1, 1
	MOVF       R3+0, 0
	MOVWF      R0+0
	MOVF       R3+1, 0
	MOVWF      R0+1
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	MOVF       R0+0, 0
	ADDWF      FARG_printf_console_MATRIX44_matrix+0, 0
	MOVWF      R2+0
	MOVF       FARG_printf_console_MATRIX44_matrix+1, 0
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      R0+1, 0
	MOVWF      R2+1
	MOVF       FARG_printf_console_MATRIX44_x+0, 0
	SUBWF      printf_console_MATRIX44_col_L0+0, 0
	MOVWF      R0+0
	CLRF       R0+1
	BTFSS      STATUS+0, 0
	DECF       R0+1, 1
	MOVLW      0
	BTFSC      printf_console_MATRIX44_col_L0+0, 7
	MOVLW      255
	ADDWF      R0+1, 1
	MOVLW      1
	BTFSS      FARG_printf_console_MATRIX44_x+0, 7
	MOVLW      0
	ADDWF      R0+1, 1
	MOVF       R2+0, 0
	ADDWF      R0+0, 1
	MOVF       R2+1, 0
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      R0+1, 1
	MOVF       R0+0, 0
	MOVWF      ___DoICPAddr+0
	MOVF       R0+1, 0
	MOVWF      ___DoICPAddr+1
	CALL       _____DoICP+0
	MOVWF      R1+0
	MOVF       R1+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_printf_console_MATRIX4412
L__printf_console_MATRIX44210:
;Teris.c,335 :: 		Cus_UART1_Write_Text_Item("*");
	MOVLW      ?lstr6_Teris+0
	MOVWF      FARG_Cus_UART1_Write_Text_Item_UART_text+0
	CALL       _Cus_UART1_Write_Text_Item+0
;Teris.c,336 :: 		}
	GOTO       L_printf_console_MATRIX4413
L_printf_console_MATRIX4412:
;Teris.c,339 :: 		Cus_UART1_Write_Text_Item("_");
	MOVLW      ?lstr7_Teris+0
	MOVWF      FARG_Cus_UART1_Write_Text_Item_UART_text+0
	CALL       _Cus_UART1_Write_Text_Item+0
;Teris.c,340 :: 		}
L_printf_console_MATRIX4413:
;Teris.c,329 :: 		for(col = 0; col < MATRIX88_COLUMN_MAX; col++)
	INCF       printf_console_MATRIX44_col_L0+0, 1
;Teris.c,341 :: 		}
	GOTO       L_printf_console_MATRIX447
L_printf_console_MATRIX448:
;Teris.c,342 :: 		Cus_UART1_Write_Text_Item("\r\n");
	MOVLW      ?lstr8_Teris+0
	MOVWF      FARG_Cus_UART1_Write_Text_Item_UART_text+0
	CALL       _Cus_UART1_Write_Text_Item+0
;Teris.c,327 :: 		for(row = 0; row < MATRIX88_ROW_MAX; row++)
	INCF       printf_console_MATRIX44_row_L0+0, 1
;Teris.c,343 :: 		}
	GOTO       L_printf_console_MATRIX444
L_printf_console_MATRIX445:
;Teris.c,344 :: 		Cus_UART1_Write_Text_Item(">>>>>>>>>>>>>>>>>>>>\r\n");
	MOVLW      ?lstr9_Teris+0
	MOVWF      FARG_Cus_UART1_Write_Text_Item_UART_text+0
	CALL       _Cus_UART1_Write_Text_Item+0
;Teris.c,345 :: 		}
L_end_printf_console_MATRIX44:
	RETURN
; end of _printf_console_MATRIX44

_printf_console_cur_MATRIX44:

;Teris.c,348 :: 		void printf_console_cur_MATRIX44(short x, short y)
;Teris.c,350 :: 		printf_console_MATRIX44(x, y, GET_CUR_MAXTRIX44);
	MOVF       FARG_printf_console_cur_MATRIX44_x+0, 0
	MOVWF      FARG_printf_console_MATRIX44_x+0
	MOVF       FARG_printf_console_cur_MATRIX44_y+0, 0
	MOVWF      FARG_printf_console_MATRIX44_y+0
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
L__printf_console_cur_MATRIX44228:
	BTFSC      STATUS+0, 2
	GOTO       L__printf_console_cur_MATRIX44229
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__printf_console_cur_MATRIX44228
L__printf_console_cur_MATRIX44229:
	MOVF       R0+0, 0
	ADDLW      _g_matrix44+0
	MOVWF      FARG_printf_console_MATRIX44_matrix+0
	MOVLW      hi_addr(_g_matrix44+0)
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      R0+1, 0
	MOVWF      FARG_printf_console_MATRIX44_matrix+1
	CALL       _printf_console_MATRIX44+0
;Teris.c,351 :: 		}
L_end_printf_console_cur_MATRIX44:
	RETURN
; end of _printf_console_cur_MATRIX44

_printf_MATRIX7219:

;Teris.c,397 :: 		void printf_MATRIX7219(MATRIX7219* matrix)
;Teris.c,405 :: 		}
L_end_printf_MATRIX7219:
	RETURN
; end of _printf_MATRIX7219

_MATRIX88_to_MATRIX7219:

;Teris.c,407 :: 		void MATRIX88_to_MATRIX7219(MATRIX88* matrix_88, MATRIX7219* matrix_7219)
;Teris.c,409 :: 		unsigned short mask = 0x80;
	MOVLW      128
	MOVWF      MATRIX88_to_MATRIX7219_mask_L0+0
;Teris.c,411 :: 		for(col = 0; col < MATRIX88_ROW_MAX; col++)
	CLRF       R3+0
L_MATRIX88_to_MATRIX721914:
	MOVLW      8
	SUBWF      R3+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_MATRIX88_to_MATRIX721915
;Teris.c,414 :: 		mask = 0x80;
	MOVLW      128
	MOVWF      MATRIX88_to_MATRIX7219_mask_L0+0
;Teris.c,415 :: 		matrix_7219->col[col] = 0;
	MOVF       R3+0, 0
	ADDWF      FARG_MATRIX88_to_MATRIX7219_matrix_7219+0, 0
	MOVWF      FSR
	CLRF       INDF+0
;Teris.c,416 :: 		for(row = 0; row < MATRIX88_COLUMN_MAX; row++)
	CLRF       R2+0
L_MATRIX88_to_MATRIX721917:
	MOVLW      8
	SUBWF      R2+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_MATRIX88_to_MATRIX721918
;Teris.c,418 :: 		if(matrix_88->cell[row][col] == 1)
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
	GOTO       L_MATRIX88_to_MATRIX721920
;Teris.c,420 :: 		matrix_7219->col[col] |= mask;
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
;Teris.c,421 :: 		}
L_MATRIX88_to_MATRIX721920:
;Teris.c,422 :: 		mask >>= 1;
	RRF        MATRIX88_to_MATRIX7219_mask_L0+0, 1
	BCF        MATRIX88_to_MATRIX7219_mask_L0+0, 7
;Teris.c,416 :: 		for(row = 0; row < MATRIX88_COLUMN_MAX; row++)
	INCF       R2+0, 1
;Teris.c,423 :: 		}
	GOTO       L_MATRIX88_to_MATRIX721917
L_MATRIX88_to_MATRIX721918:
;Teris.c,411 :: 		for(col = 0; col < MATRIX88_ROW_MAX; col++)
	INCF       R3+0, 1
;Teris.c,424 :: 		}
	GOTO       L_MATRIX88_to_MATRIX721914
L_MATRIX88_to_MATRIX721915:
;Teris.c,425 :: 		}
L_end_MATRIX88_to_MATRIX7219:
	RETURN
; end of _MATRIX88_to_MATRIX7219

_printf_MATRIX88:

;Teris.c,449 :: 		void printf_MATRIX88(MATRIX88* matrix_88)
;Teris.c,452 :: 		MATRIX88_to_MATRIX7219(matrix_88, &matrix_7219);
	MOVF       FARG_printf_MATRIX88_matrix_88+0, 0
	MOVWF      FARG_MATRIX88_to_MATRIX7219_matrix_88+0
	MOVLW      printf_MATRIX88_matrix_7219_L0+0
	MOVWF      FARG_MATRIX88_to_MATRIX7219_matrix_7219+0
	CALL       _MATRIX88_to_MATRIX7219+0
;Teris.c,453 :: 		printf_MATRIX7219(&matrix_7219);
	MOVLW      printf_MATRIX88_matrix_7219_L0+0
	MOVWF      FARG_printf_MATRIX7219_matrix+0
	CALL       _printf_MATRIX7219+0
;Teris.c,454 :: 		}
L_end_printf_MATRIX88:
	RETURN
; end of _printf_MATRIX88

_printf_Screen:

;Teris.c,456 :: 		void printf_Screen()
;Teris.c,459 :: 		}
L_end_printf_Screen:
	RETURN
; end of _printf_Screen

_Clear_Matrix:

;Teris.c,461 :: 		void Clear_Matrix(void)
;Teris.c,463 :: 		memset(&g_matrix88, 0, sizeof(MATRIX88));
	MOVLW      _g_matrix88+0
	MOVWF      FARG_memset_p1+0
	CLRF       FARG_memset_character+0
	MOVLW      64
	MOVWF      FARG_memset_n+0
	MOVLW      0
	MOVWF      FARG_memset_n+1
	CALL       _memset+0
;Teris.c,464 :: 		printf_Screen();
	CALL       _printf_Screen+0
;Teris.c,465 :: 		}
L_end_Clear_Matrix:
	RETURN
; end of _Clear_Matrix

_printf_console_MATRIX88:

;Teris.c,489 :: 		void printf_console_MATRIX88(char* lable, MATRIX88* matrix)
;Teris.c,494 :: 		Cus_UART1_Write_Text_Item(lable);
	MOVF       FARG_printf_console_MATRIX88_lable+0, 0
	MOVWF      FARG_Cus_UART1_Write_Text_Item_UART_text+0
	CALL       _Cus_UART1_Write_Text_Item+0
;Teris.c,495 :: 		Cus_UART1_Write_Text_Item(":");
	MOVLW      ?lstr10_Teris+0
	MOVWF      FARG_Cus_UART1_Write_Text_Item_UART_text+0
	CALL       _Cus_UART1_Write_Text_Item+0
;Teris.c,496 :: 		Cus_UART1_Write_Text_Item("<<<<<<<<<<<<<<<<<<<<\r\n");
	MOVLW      ?lstr11_Teris+0
	MOVWF      FARG_Cus_UART1_Write_Text_Item_UART_text+0
	CALL       _Cus_UART1_Write_Text_Item+0
;Teris.c,497 :: 		for(row = 0; row < MATRIX88_ROW_MAX; row++)
	CLRF       printf_console_MATRIX88_row_L0+0
L_printf_console_MATRIX8821:
	MOVLW      8
	SUBWF      printf_console_MATRIX88_row_L0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_printf_console_MATRIX8822
;Teris.c,499 :: 		for(col = 0; col < MATRIX88_COLUMN_MAX; col++)
	CLRF       printf_console_MATRIX88_col_L0+0
L_printf_console_MATRIX8824:
	MOVLW      8
	SUBWF      printf_console_MATRIX88_col_L0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_printf_console_MATRIX8825
;Teris.c,501 :: 		if(matrix->cell[row][col] == 1)
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
	GOTO       L_printf_console_MATRIX8827
;Teris.c,503 :: 		Cus_UART1_Write_Text_Item("*");
	MOVLW      ?lstr12_Teris+0
	MOVWF      FARG_Cus_UART1_Write_Text_Item_UART_text+0
	CALL       _Cus_UART1_Write_Text_Item+0
;Teris.c,504 :: 		}
	GOTO       L_printf_console_MATRIX8828
L_printf_console_MATRIX8827:
;Teris.c,507 :: 		Cus_UART1_Write_Text_Item("_");
	MOVLW      ?lstr13_Teris+0
	MOVWF      FARG_Cus_UART1_Write_Text_Item_UART_text+0
	CALL       _Cus_UART1_Write_Text_Item+0
;Teris.c,508 :: 		}
L_printf_console_MATRIX8828:
;Teris.c,499 :: 		for(col = 0; col < MATRIX88_COLUMN_MAX; col++)
	INCF       printf_console_MATRIX88_col_L0+0, 1
;Teris.c,509 :: 		}
	GOTO       L_printf_console_MATRIX8824
L_printf_console_MATRIX8825:
;Teris.c,510 :: 		Cus_UART1_Write_Text_Item("\r\n");
	MOVLW      ?lstr14_Teris+0
	MOVWF      FARG_Cus_UART1_Write_Text_Item_UART_text+0
	CALL       _Cus_UART1_Write_Text_Item+0
;Teris.c,497 :: 		for(row = 0; row < MATRIX88_ROW_MAX; row++)
	INCF       printf_console_MATRIX88_row_L0+0, 1
;Teris.c,511 :: 		}
	GOTO       L_printf_console_MATRIX8821
L_printf_console_MATRIX8822:
;Teris.c,512 :: 		Cus_UART1_Write_Text_Item(">>>>>>>>>>>>>>>>>>>>\r\n");
	MOVLW      ?lstr15_Teris+0
	MOVWF      FARG_Cus_UART1_Write_Text_Item_UART_text+0
	CALL       _Cus_UART1_Write_Text_Item+0
;Teris.c,513 :: 		}
L_end_printf_console_MATRIX88:
	RETURN
; end of _printf_console_MATRIX88

_is_row_full:

;Teris.c,516 :: 		unsigned short is_row_full(MATRIX88* matrix, unsigned short row)
;Teris.c,519 :: 		for(col = 0; col < MATRIX88_COLUMN_MAX; col++)
	CLRF       R2+0
L_is_row_full29:
	MOVLW      8
	SUBWF      R2+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_is_row_full30
;Teris.c,521 :: 		if(matrix->cell[row][col] == 0)
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
	GOTO       L_is_row_full32
;Teris.c,523 :: 		return 0;
	CLRF       R0+0
	GOTO       L_end_is_row_full
;Teris.c,524 :: 		}
L_is_row_full32:
;Teris.c,519 :: 		for(col = 0; col < MATRIX88_COLUMN_MAX; col++)
	INCF       R2+0, 1
;Teris.c,525 :: 		}
	GOTO       L_is_row_full29
L_is_row_full30:
;Teris.c,526 :: 		return 1;
	MOVLW      1
	MOVWF      R0+0
;Teris.c,527 :: 		}
L_end_is_row_full:
	RETURN
; end of _is_row_full

_delete_row:

;Teris.c,528 :: 		void delete_row(MATRIX88* matrix, unsigned short row)
;Teris.c,531 :: 		for(i = MATRIX88_ROW_MAX - 1; i >= 0; i--)
	MOVLW      7
	MOVWF      delete_row_i_L0+0
L_delete_row33:
	MOVLW      128
	XORWF      delete_row_i_L0+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 0
	GOTO       L_delete_row34
;Teris.c,533 :: 		if(i <= row)
	MOVLW      128
	MOVWF      R0+0
	MOVLW      128
	BTFSC      delete_row_i_L0+0, 7
	MOVLW      127
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L__delete_row238
	MOVF       delete_row_i_L0+0, 0
	SUBWF      FARG_delete_row_row+0, 0
L__delete_row238:
	BTFSS      STATUS+0, 0
	GOTO       L_delete_row36
;Teris.c,535 :: 		if(i > 0)
	MOVLW      128
	XORLW      0
	MOVWF      R0+0
	MOVLW      128
	XORWF      delete_row_i_L0+0, 0
	SUBWF      R0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_delete_row37
;Teris.c,543 :: 		memcpy(matrix->cell[i], matrix->cell[i - 1], len);
	MOVLW      3
	MOVWF      R1+0
	MOVF       delete_row_i_L0+0, 0
	MOVWF      R0+0
	MOVF       R1+0, 0
L__delete_row239:
	BTFSC      STATUS+0, 2
	GOTO       L__delete_row240
	RLF        R0+0, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__delete_row239
L__delete_row240:
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
L__delete_row241:
	BTFSC      STATUS+0, 2
	GOTO       L__delete_row242
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__delete_row241
L__delete_row242:
	MOVF       R0+0, 0
	ADDWF      FARG_delete_row_matrix+0, 0
	MOVWF      FARG_memcpy_s1+0
	MOVLW      8
	MOVWF      FARG_memcpy_n+0
	MOVLW      0
	MOVWF      FARG_memcpy_n+1
	CALL       _memcpy+0
;Teris.c,544 :: 		}
	GOTO       L_delete_row38
L_delete_row37:
;Teris.c,547 :: 		memset(matrix->cell[i], 0, MATRIX88_COLUMN_MAX*sizeof(unsigned short));
	MOVLW      3
	MOVWF      R1+0
	MOVF       delete_row_i_L0+0, 0
	MOVWF      R0+0
	MOVF       R1+0, 0
L__delete_row243:
	BTFSC      STATUS+0, 2
	GOTO       L__delete_row244
	RLF        R0+0, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__delete_row243
L__delete_row244:
	MOVF       R0+0, 0
	ADDWF      FARG_delete_row_matrix+0, 0
	MOVWF      FARG_memset_p1+0
	CLRF       FARG_memset_character+0
	MOVLW      8
	MOVWF      FARG_memset_n+0
	MOVLW      0
	MOVWF      FARG_memset_n+1
	CALL       _memset+0
;Teris.c,548 :: 		}
L_delete_row38:
;Teris.c,549 :: 		}
L_delete_row36:
;Teris.c,531 :: 		for(i = MATRIX88_ROW_MAX - 1; i >= 0; i--)
	DECF       delete_row_i_L0+0, 1
;Teris.c,550 :: 		}
	GOTO       L_delete_row33
L_delete_row34:
;Teris.c,551 :: 		}
L_end_delete_row:
	RETURN
; end of _delete_row

_delete_matrix:

;Teris.c,552 :: 		unsigned short delete_matrix(MATRIX88* matrix)
;Teris.c,554 :: 		unsigned short count = 0;
	CLRF       delete_matrix_count_L0+0
	MOVLW      7
	MOVWF      delete_matrix_row_L0+0
;Teris.c,556 :: 		while(row >= 0)
L_delete_matrix39:
	MOVLW      128
	XORWF      delete_matrix_row_L0+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 0
	GOTO       L_delete_matrix40
;Teris.c,558 :: 		if(is_row_full(matrix, row))
	MOVF       FARG_delete_matrix_matrix+0, 0
	MOVWF      FARG_is_row_full_matrix+0
	MOVF       delete_matrix_row_L0+0, 0
	MOVWF      FARG_is_row_full_row+0
	CALL       _is_row_full+0
	MOVF       R0+0, 0
	BTFSC      STATUS+0, 2
	GOTO       L_delete_matrix41
;Teris.c,560 :: 		delete_row(matrix, row);
	MOVF       FARG_delete_matrix_matrix+0, 0
	MOVWF      FARG_delete_row_matrix+0
	MOVF       delete_matrix_row_L0+0, 0
	MOVWF      FARG_delete_row_row+0
	CALL       _delete_row+0
;Teris.c,561 :: 		count++;
	INCF       delete_matrix_count_L0+0, 1
;Teris.c,562 :: 		}
	GOTO       L_delete_matrix42
L_delete_matrix41:
;Teris.c,565 :: 		row--;
	DECF       delete_matrix_row_L0+0, 1
;Teris.c,566 :: 		}
L_delete_matrix42:
;Teris.c,567 :: 		}
	GOTO       L_delete_matrix39
L_delete_matrix40:
;Teris.c,572 :: 		return count;
	MOVF       delete_matrix_count_L0+0, 0
	MOVWF      R0+0
;Teris.c,573 :: 		}
L_end_delete_matrix:
	RETURN
; end of _delete_matrix

_is_row_empty:

;Teris.c,574 :: 		unsigned short is_row_empty(MATRIX88* matrix, unsigned short row)
;Teris.c,577 :: 		for(col = 0; col < MATRIX88_COLUMN_MAX; col++)
	CLRF       R2+0
L_is_row_empty43:
	MOVLW      8
	SUBWF      R2+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_is_row_empty44
;Teris.c,579 :: 		if(matrix->cell[row][col] == 1)
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
	GOTO       L_is_row_empty46
;Teris.c,581 :: 		return 0;
	CLRF       R0+0
	GOTO       L_end_is_row_empty
;Teris.c,582 :: 		}
L_is_row_empty46:
;Teris.c,577 :: 		for(col = 0; col < MATRIX88_COLUMN_MAX; col++)
	INCF       R2+0, 1
;Teris.c,583 :: 		}
	GOTO       L_is_row_empty43
L_is_row_empty44:
;Teris.c,584 :: 		return 1;
	MOVLW      1
	MOVWF      R0+0
;Teris.c,585 :: 		}
L_end_is_row_empty:
	RETURN
; end of _is_row_empty

_is_col_empty:

;Teris.c,586 :: 		unsigned short is_col_empty(MATRIX88* matrix, unsigned short col)
;Teris.c,589 :: 		for(row = 0; row < MATRIX88_ROW_MAX; row++)
	CLRF       R2+0
L_is_col_empty47:
	MOVLW      8
	SUBWF      R2+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_is_col_empty48
;Teris.c,591 :: 		if(matrix->cell[row][col] == 1)
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
	GOTO       L_is_col_empty50
;Teris.c,593 :: 		return 0;
	CLRF       R0+0
	GOTO       L_end_is_col_empty
;Teris.c,594 :: 		}
L_is_col_empty50:
;Teris.c,589 :: 		for(row = 0; row < MATRIX88_ROW_MAX; row++)
	INCF       R2+0, 1
;Teris.c,595 :: 		}
	GOTO       L_is_col_empty47
L_is_col_empty48:
;Teris.c,596 :: 		return 1;
	MOVLW      1
	MOVWF      R0+0
;Teris.c,597 :: 		}
L_end_is_col_empty:
	RETURN
; end of _is_col_empty

_hit_land1:

;Teris.c,598 :: 		unsigned short hit_land1(short x, short y, const MATRIX44* matrix_44, MATRIX88* matrix_88)
;Teris.c,606 :: 		for(row = MATRIX44_ROW_MAX - 1; row >= 0; row--)
	MOVLW      3
	MOVWF      R5+0
L_hit_land151:
	MOVLW      128
	XORWF      R5+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 0
	GOTO       L_hit_land152
;Teris.c,608 :: 		for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
	CLRF       R6+0
L_hit_land154:
	MOVLW      128
	XORWF      R6+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      4
	SUBWF      R0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_hit_land155
;Teris.c,610 :: 		if(matrix_44->cell[row][col] == 1)
	MOVF       R5+0, 0
	MOVWF      R0+0
	MOVLW      0
	BTFSC      R0+0, 7
	MOVLW      255
	MOVWF      R0+1
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	MOVF       FARG_hit_land1_matrix_44+0, 0
	ADDWF      R0+0, 1
	MOVF       FARG_hit_land1_matrix_44+1, 0
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      R0+1, 1
	MOVF       R6+0, 0
	ADDWF      R0+0, 1
	BTFSC      STATUS+0, 0
	INCF       R0+1, 1
	MOVLW      0
	BTFSC      R6+0, 7
	MOVLW      255
	ADDWF      R0+1, 1
	MOVF       R0+0, 0
	MOVWF      ___DoICPAddr+0
	MOVF       R0+1, 0
	MOVWF      ___DoICPAddr+1
	CALL       _____DoICP+0
	MOVWF      R1+0
	MOVF       R1+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_hit_land157
;Teris.c,612 :: 		if((y + row) >= (MATRIX88_ROW_MAX - 1))
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
	GOTO       L__hit_land1249
	MOVLW      7
	SUBWF      R1+0, 0
L__hit_land1249:
	BTFSS      STATUS+0, 0
	GOTO       L_hit_land158
;Teris.c,618 :: 		return 1;
	MOVLW      1
	MOVWF      R0+0
	GOTO       L_end_hit_land1
;Teris.c,619 :: 		}
L_hit_land158:
;Teris.c,621 :: 		if(matrix_88->cell[y + row + 1][x + col] == 1)
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
L__hit_land1250:
	BTFSC      STATUS+0, 2
	GOTO       L__hit_land1251
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__hit_land1250
L__hit_land1251:
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
	GOTO       L_hit_land159
;Teris.c,627 :: 		return 1;
	MOVLW      1
	MOVWF      R0+0
	GOTO       L_end_hit_land1
;Teris.c,628 :: 		}
L_hit_land159:
;Teris.c,629 :: 		}
L_hit_land157:
;Teris.c,608 :: 		for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
	INCF       R6+0, 1
;Teris.c,630 :: 		}
	GOTO       L_hit_land154
L_hit_land155:
;Teris.c,606 :: 		for(row = MATRIX44_ROW_MAX - 1; row >= 0; row--)
	DECF       R5+0, 1
;Teris.c,631 :: 		}
	GOTO       L_hit_land151
L_hit_land152:
;Teris.c,636 :: 		return 0;
	CLRF       R0+0
;Teris.c,637 :: 		}
L_end_hit_land1:
	RETURN
; end of _hit_land1

_is_valid:

;Teris.c,638 :: 		unsigned short is_valid(short x, short y, const MATRIX44* matrix_44, MATRIX88* matrix_88)
;Teris.c,646 :: 		for(row = MATRIX44_ROW_MAX - 1; row >= 0; row--)
	MOVLW      3
	MOVWF      R5+0
L_is_valid60:
	MOVLW      128
	XORWF      R5+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 0
	GOTO       L_is_valid61
;Teris.c,648 :: 		for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
	CLRF       R6+0
L_is_valid63:
	MOVLW      128
	XORWF      R6+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      4
	SUBWF      R0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_is_valid64
;Teris.c,650 :: 		if(matrix_44->cell[row][col] == 1)
	MOVF       R5+0, 0
	MOVWF      R0+0
	MOVLW      0
	BTFSC      R0+0, 7
	MOVLW      255
	MOVWF      R0+1
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	MOVF       FARG_is_valid_matrix_44+0, 0
	ADDWF      R0+0, 1
	MOVF       FARG_is_valid_matrix_44+1, 0
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      R0+1, 1
	MOVF       R6+0, 0
	ADDWF      R0+0, 1
	BTFSC      STATUS+0, 0
	INCF       R0+1, 1
	MOVLW      0
	BTFSC      R6+0, 7
	MOVLW      255
	ADDWF      R0+1, 1
	MOVF       R0+0, 0
	MOVWF      ___DoICPAddr+0
	MOVF       R0+1, 0
	MOVWF      ___DoICPAddr+1
	CALL       _____DoICP+0
	MOVWF      R1+0
	MOVF       R1+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_is_valid66
;Teris.c,652 :: 		if(matrix_88->cell[y + row][x + col] == 1)
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
L__is_valid253:
	BTFSC      STATUS+0, 2
	GOTO       L__is_valid254
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__is_valid253
L__is_valid254:
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
	GOTO       L_is_valid67
;Teris.c,658 :: 		return 0;
	CLRF       R0+0
	GOTO       L_end_is_valid
;Teris.c,659 :: 		}
L_is_valid67:
;Teris.c,661 :: 		if(( x + col < 0) || (x + col >= MATRIX88_COLUMN_MAX))
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
	GOTO       L__is_valid255
	MOVLW      0
	SUBWF      R1+0, 0
L__is_valid255:
	BTFSS      STATUS+0, 0
	GOTO       L__is_valid211
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
	GOTO       L__is_valid256
	MOVLW      8
	SUBWF      R1+0, 0
L__is_valid256:
	BTFSC      STATUS+0, 0
	GOTO       L__is_valid211
	GOTO       L_is_valid70
L__is_valid211:
;Teris.c,667 :: 		return 0;
	CLRF       R0+0
	GOTO       L_end_is_valid
;Teris.c,668 :: 		}
L_is_valid70:
;Teris.c,669 :: 		if((y + row) > (MATRIX88_ROW_MAX - 1))
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
	GOTO       L__is_valid257
	MOVF       R1+0, 0
	SUBLW      7
L__is_valid257:
	BTFSC      STATUS+0, 0
	GOTO       L_is_valid71
;Teris.c,675 :: 		return 0;
	CLRF       R0+0
	GOTO       L_end_is_valid
;Teris.c,676 :: 		}
L_is_valid71:
;Teris.c,677 :: 		}
L_is_valid66:
;Teris.c,648 :: 		for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
	INCF       R6+0, 1
;Teris.c,678 :: 		}
	GOTO       L_is_valid63
L_is_valid64:
;Teris.c,646 :: 		for(row = MATRIX44_ROW_MAX - 1; row >= 0; row--)
	DECF       R5+0, 1
;Teris.c,679 :: 		}
	GOTO       L_is_valid60
L_is_valid61:
;Teris.c,684 :: 		return 1;
	MOVLW      1
	MOVWF      R0+0
;Teris.c,685 :: 		}
L_end_is_valid:
	RETURN
; end of _is_valid

_is_left_boundary:

;Teris.c,686 :: 		unsigned short is_left_boundary(short x, const MATRIX44* matrix_44, MATRIX88* matrix_88)
;Teris.c,690 :: 		for(row = MATRIX44_ROW_MAX - 1; row >= 0; row--)
	MOVLW      3
	MOVWF      R3+0
L_is_left_boundary72:
	MOVLW      128
	XORWF      R3+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 0
	GOTO       L_is_left_boundary73
;Teris.c,692 :: 		for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
	CLRF       R4+0
L_is_left_boundary75:
	MOVLW      128
	XORWF      R4+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      4
	SUBWF      R0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_is_left_boundary76
;Teris.c,694 :: 		if(matrix_44->cell[row][col] == 1)
	MOVF       R3+0, 0
	MOVWF      R0+0
	MOVLW      0
	BTFSC      R0+0, 7
	MOVLW      255
	MOVWF      R0+1
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	MOVF       FARG_is_left_boundary_matrix_44+0, 0
	ADDWF      R0+0, 1
	MOVF       FARG_is_left_boundary_matrix_44+1, 0
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      R0+1, 1
	MOVF       R4+0, 0
	ADDWF      R0+0, 1
	BTFSC      STATUS+0, 0
	INCF       R0+1, 1
	MOVLW      0
	BTFSC      R4+0, 7
	MOVLW      255
	ADDWF      R0+1, 1
	MOVF       R0+0, 0
	MOVWF      ___DoICPAddr+0
	MOVF       R0+1, 0
	MOVWF      ___DoICPAddr+1
	CALL       _____DoICP+0
	MOVWF      R1+0
	MOVF       R1+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_is_left_boundary78
;Teris.c,696 :: 		if( x + col < 0)
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
	GOTO       L__is_left_boundary259
	MOVLW      0
	SUBWF      R1+0, 0
L__is_left_boundary259:
	BTFSC      STATUS+0, 0
	GOTO       L_is_left_boundary79
;Teris.c,702 :: 		return LEFT_OVER_BOUNDARY;
	MOVLW      2
	MOVWF      R0+0
	GOTO       L_end_is_left_boundary
;Teris.c,703 :: 		}
L_is_left_boundary79:
;Teris.c,704 :: 		}
L_is_left_boundary78:
;Teris.c,692 :: 		for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
	INCF       R4+0, 1
;Teris.c,705 :: 		}
	GOTO       L_is_left_boundary75
L_is_left_boundary76:
;Teris.c,690 :: 		for(row = MATRIX44_ROW_MAX - 1; row >= 0; row--)
	DECF       R3+0, 1
;Teris.c,706 :: 		}
	GOTO       L_is_left_boundary72
L_is_left_boundary73:
;Teris.c,707 :: 		return OK;
	CLRF       R0+0
;Teris.c,708 :: 		}
L_end_is_left_boundary:
	RETURN
; end of _is_left_boundary

_is_right_boundary:

;Teris.c,709 :: 		unsigned short is_right_boundary(short x, const MATRIX44* matrix_44, MATRIX88* matrix_88)
;Teris.c,713 :: 		for(row = MATRIX44_ROW_MAX - 1; row >= 0; row--)
	MOVLW      3
	MOVWF      R3+0
L_is_right_boundary80:
	MOVLW      128
	XORWF      R3+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 0
	GOTO       L_is_right_boundary81
;Teris.c,715 :: 		for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
	CLRF       R4+0
L_is_right_boundary83:
	MOVLW      128
	XORWF      R4+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      4
	SUBWF      R0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_is_right_boundary84
;Teris.c,717 :: 		if(matrix_44->cell[row][col] == 1)
	MOVF       R3+0, 0
	MOVWF      R0+0
	MOVLW      0
	BTFSC      R0+0, 7
	MOVLW      255
	MOVWF      R0+1
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	MOVF       FARG_is_right_boundary_matrix_44+0, 0
	ADDWF      R0+0, 1
	MOVF       FARG_is_right_boundary_matrix_44+1, 0
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      R0+1, 1
	MOVF       R4+0, 0
	ADDWF      R0+0, 1
	BTFSC      STATUS+0, 0
	INCF       R0+1, 1
	MOVLW      0
	BTFSC      R4+0, 7
	MOVLW      255
	ADDWF      R0+1, 1
	MOVF       R0+0, 0
	MOVWF      ___DoICPAddr+0
	MOVF       R0+1, 0
	MOVWF      ___DoICPAddr+1
	CALL       _____DoICP+0
	MOVWF      R1+0
	MOVF       R1+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_is_right_boundary86
;Teris.c,719 :: 		if(x + col > MATRIX88_COLUMN_MAX - 1)
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
	GOTO       L__is_right_boundary261
	MOVF       R1+0, 0
	SUBLW      7
L__is_right_boundary261:
	BTFSC      STATUS+0, 0
	GOTO       L_is_right_boundary87
;Teris.c,725 :: 		return RIGHT_OVER_BOUNDARY;
	MOVLW      3
	MOVWF      R0+0
	GOTO       L_end_is_right_boundary
;Teris.c,726 :: 		}
L_is_right_boundary87:
;Teris.c,727 :: 		}
L_is_right_boundary86:
;Teris.c,715 :: 		for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
	INCF       R4+0, 1
;Teris.c,728 :: 		}
	GOTO       L_is_right_boundary83
L_is_right_boundary84:
;Teris.c,713 :: 		for(row = MATRIX44_ROW_MAX - 1; row >= 0; row--)
	DECF       R3+0, 1
;Teris.c,729 :: 		}
	GOTO       L_is_right_boundary80
L_is_right_boundary81:
;Teris.c,730 :: 		return OK;
	CLRF       R0+0
;Teris.c,731 :: 		}
L_end_is_right_boundary:
	RETURN
; end of _is_right_boundary

_fall_off:

;Teris.c,732 :: 		unsigned short fall_off(short x, short y, const MATRIX44* matrix_44, MATRIX88* matrix_88)
;Teris.c,734 :: 		while(1)
L_fall_off88:
;Teris.c,738 :: 		for(row = MATRIX44_ROW_MAX - 1; row >= 0; row--)
	MOVLW      3
	MOVWF      R5+0
L_fall_off90:
	MOVLW      128
	XORWF      R5+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 0
	GOTO       L_fall_off91
;Teris.c,740 :: 		for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
	CLRF       R6+0
L_fall_off93:
	MOVLW      128
	XORWF      R6+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      4
	SUBWF      R0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_fall_off94
;Teris.c,742 :: 		if(matrix_44->cell[row][col] == 1)
	MOVF       R5+0, 0
	MOVWF      R0+0
	MOVLW      0
	BTFSC      R0+0, 7
	MOVLW      255
	MOVWF      R0+1
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	MOVF       FARG_fall_off_matrix_44+0, 0
	ADDWF      R0+0, 1
	MOVF       FARG_fall_off_matrix_44+1, 0
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      R0+1, 1
	MOVF       R6+0, 0
	ADDWF      R0+0, 1
	BTFSC      STATUS+0, 0
	INCF       R0+1, 1
	MOVLW      0
	BTFSC      R6+0, 7
	MOVLW      255
	ADDWF      R0+1, 1
	MOVF       R0+0, 0
	MOVWF      ___DoICPAddr+0
	MOVF       R0+1, 0
	MOVWF      ___DoICPAddr+1
	CALL       _____DoICP+0
	MOVWF      R1+0
	MOVF       R1+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_fall_off96
;Teris.c,744 :: 		if(matrix_88->cell[y + row + 1][x + col] == 1)
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
L__fall_off263:
	BTFSC      STATUS+0, 2
	GOTO       L__fall_off264
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__fall_off263
L__fall_off264:
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
	GOTO       L_fall_off97
;Teris.c,750 :: 		return y;
	MOVF       FARG_fall_off_y+0, 0
	MOVWF      R0+0
	GOTO       L_end_fall_off
;Teris.c,751 :: 		}
L_fall_off97:
;Teris.c,752 :: 		if((y + row) >= (MATRIX88_ROW_MAX - 1))
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
	GOTO       L__fall_off265
	MOVLW      7
	SUBWF      R1+0, 0
L__fall_off265:
	BTFSS      STATUS+0, 0
	GOTO       L_fall_off98
;Teris.c,758 :: 		return y;
	MOVF       FARG_fall_off_y+0, 0
	MOVWF      R0+0
	GOTO       L_end_fall_off
;Teris.c,759 :: 		}
L_fall_off98:
;Teris.c,760 :: 		}
L_fall_off96:
;Teris.c,740 :: 		for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
	INCF       R6+0, 1
;Teris.c,761 :: 		}
	GOTO       L_fall_off93
L_fall_off94:
;Teris.c,738 :: 		for(row = MATRIX44_ROW_MAX - 1; row >= 0; row--)
	DECF       R5+0, 1
;Teris.c,762 :: 		}
	GOTO       L_fall_off90
L_fall_off91:
;Teris.c,763 :: 		y++;
	INCF       FARG_fall_off_y+0, 1
;Teris.c,764 :: 		}
	GOTO       L_fall_off88
;Teris.c,765 :: 		}
L_end_fall_off:
	RETURN
; end of _fall_off

_clear:

;Teris.c,766 :: 		void clear(short x, short y, const MATRIX44* matrix_44, MATRIX88* matrix_88)
;Teris.c,770 :: 		for(row = 0; row < MATRIX44_ROW_MAX; row++)
	CLRF       R5+0
L_clear99:
	MOVLW      4
	SUBWF      R5+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_clear100
;Teris.c,772 :: 		for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
	CLRF       R6+0
L_clear102:
	MOVLW      4
	SUBWF      R6+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_clear103
;Teris.c,774 :: 		if(matrix_44->cell[row][col] == 1)
	MOVF       R5+0, 0
	MOVWF      R0+0
	CLRF       R0+1
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	MOVF       FARG_clear_matrix_44+0, 0
	ADDWF      R0+0, 1
	MOVF       FARG_clear_matrix_44+1, 0
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      R0+1, 1
	MOVF       R6+0, 0
	ADDWF      R0+0, 1
	BTFSC      STATUS+0, 0
	INCF       R0+1, 1
	MOVF       R0+0, 0
	MOVWF      ___DoICPAddr+0
	MOVF       R0+1, 0
	MOVWF      ___DoICPAddr+1
	CALL       _____DoICP+0
	MOVWF      R1+0
	MOVF       R1+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_clear105
;Teris.c,776 :: 		matrix_88->cell[y + row][x + col] = 0;
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
L__clear267:
	BTFSC      STATUS+0, 2
	GOTO       L__clear268
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__clear267
L__clear268:
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
;Teris.c,777 :: 		}
L_clear105:
;Teris.c,772 :: 		for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
	INCF       R6+0, 1
;Teris.c,778 :: 		}
	GOTO       L_clear102
L_clear103:
;Teris.c,770 :: 		for(row = 0; row < MATRIX44_ROW_MAX; row++)
	INCF       R5+0, 1
;Teris.c,779 :: 		}
	GOTO       L_clear99
L_clear100:
;Teris.c,780 :: 		}
L_end_clear:
	RETURN
; end of _clear

_merge:

;Teris.c,781 :: 		void merge(short x, short y, const MATRIX44* matrix_44, MATRIX88* matrix_88)
;Teris.c,785 :: 		for(row = 0; row < MATRIX44_ROW_MAX; row++)
	CLRF       R5+0
L_merge106:
	MOVLW      4
	SUBWF      R5+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_merge107
;Teris.c,787 :: 		for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
	CLRF       R6+0
L_merge109:
	MOVLW      4
	SUBWF      R6+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_merge110
;Teris.c,789 :: 		if(matrix_44->cell[row][col] == 1)
	MOVF       R5+0, 0
	MOVWF      R0+0
	CLRF       R0+1
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	MOVF       FARG_merge_matrix_44+0, 0
	ADDWF      R0+0, 1
	MOVF       FARG_merge_matrix_44+1, 0
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      R0+1, 1
	MOVF       R6+0, 0
	ADDWF      R0+0, 1
	BTFSC      STATUS+0, 0
	INCF       R0+1, 1
	MOVF       R0+0, 0
	MOVWF      ___DoICPAddr+0
	MOVF       R0+1, 0
	MOVWF      ___DoICPAddr+1
	CALL       _____DoICP+0
	MOVWF      R1+0
	MOVF       R1+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_merge112
;Teris.c,791 :: 		matrix_88->cell[y + row][x + col] = 1;
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
L__merge270:
	BTFSC      STATUS+0, 2
	GOTO       L__merge271
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__merge270
L__merge271:
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
;Teris.c,792 :: 		}
L_merge112:
;Teris.c,787 :: 		for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
	INCF       R6+0, 1
;Teris.c,793 :: 		}
	GOTO       L_merge109
L_merge110:
;Teris.c,785 :: 		for(row = 0; row < MATRIX44_ROW_MAX; row++)
	INCF       R5+0, 1
;Teris.c,794 :: 		}
	GOTO       L_merge106
L_merge107:
;Teris.c,795 :: 		}
L_end_merge:
	RETURN
; end of _merge

_merge1:

;Teris.c,796 :: 		void merge1(short x, short y, const MATRIX44* matrix_44, MATRIX88* matrix88_in, MATRIX88* matrix88_out)
;Teris.c,807 :: 		memcpy(matrix88_out, matrix88_in, len);
	MOVF       FARG_merge1_matrix88_out+0, 0
	MOVWF      FARG_memcpy_d1+0
	MOVF       FARG_merge1_matrix88_in+0, 0
	MOVWF      FARG_memcpy_s1+0
	MOVLW      64
	MOVWF      FARG_memcpy_n+0
	MOVLW      0
	MOVWF      FARG_memcpy_n+1
	CALL       _memcpy+0
;Teris.c,809 :: 		for(row = 0; row < MATRIX44_ROW_MAX; row++)
	CLRF       merge1_row_L0+0
L_merge1113:
	MOVLW      4
	SUBWF      merge1_row_L0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_merge1114
;Teris.c,811 :: 		for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
	CLRF       merge1_col_L0+0
L_merge1116:
	MOVLW      4
	SUBWF      merge1_col_L0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_merge1117
;Teris.c,813 :: 		if(matrix_44->cell[row][col] == 1)
	MOVF       merge1_row_L0+0, 0
	MOVWF      R0+0
	CLRF       R0+1
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	MOVF       FARG_merge1_matrix_44+0, 0
	ADDWF      R0+0, 1
	MOVF       FARG_merge1_matrix_44+1, 0
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      R0+1, 1
	MOVF       merge1_col_L0+0, 0
	ADDWF      R0+0, 1
	BTFSC      STATUS+0, 0
	INCF       R0+1, 1
	MOVF       R0+0, 0
	MOVWF      ___DoICPAddr+0
	MOVF       R0+1, 0
	MOVWF      ___DoICPAddr+1
	CALL       _____DoICP+0
	MOVWF      R1+0
	MOVF       R1+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_merge1119
;Teris.c,815 :: 		matrix88_out->cell[y + row][x + col] = 1;
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
L__merge1273:
	BTFSC      STATUS+0, 2
	GOTO       L__merge1274
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__merge1273
L__merge1274:
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
;Teris.c,816 :: 		}
L_merge1119:
;Teris.c,811 :: 		for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
	INCF       merge1_col_L0+0, 1
;Teris.c,817 :: 		}
	GOTO       L_merge1116
L_merge1117:
;Teris.c,809 :: 		for(row = 0; row < MATRIX44_ROW_MAX; row++)
	INCF       merge1_row_L0+0, 1
;Teris.c,818 :: 		}
	GOTO       L_merge1113
L_merge1114:
;Teris.c,819 :: 		}
L_end_merge1:
	RETURN
; end of _merge1

_evaluate:

;Teris.c,820 :: 		unsigned int evaluate(MATRIX88* matrix)
;Teris.c,822 :: 		unsigned int risk = 0;
	CLRF       evaluate_risk_L0+0
	CLRF       evaluate_risk_L0+1
	MOVLW      255
	MOVWF      evaluate_full_L0+0
;Teris.c,826 :: 		for(col = 0; col < MATRIX88_COLUMN_MAX; col++)
	CLRF       R2+0
L_evaluate120:
	MOVLW      8
	SUBWF      R2+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_evaluate121
;Teris.c,828 :: 		full = 0xFF;
	MOVLW      255
	MOVWF      evaluate_full_L0+0
;Teris.c,829 :: 		for(row = MATRIX88_ROW_MAX - 1; row >= 0; row--)
	MOVLW      7
	MOVWF      R3+0
L_evaluate123:
	MOVLW      128
	XORWF      R3+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 0
	GOTO       L_evaluate124
;Teris.c,831 :: 		if(full == 0xFF)
	MOVF       evaluate_full_L0+0, 0
	XORLW      255
	BTFSS      STATUS+0, 2
	GOTO       L_evaluate126
;Teris.c,833 :: 		full = matrix->cell[row][col];
	MOVLW      3
	MOVWF      R1+0
	MOVF       R3+0, 0
	MOVWF      R0+0
	MOVF       R1+0, 0
L__evaluate276:
	BTFSC      STATUS+0, 2
	GOTO       L__evaluate277
	RLF        R0+0, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__evaluate276
L__evaluate277:
	MOVF       FARG_evaluate_matrix+0, 0
	ADDWF      R0+0, 1
	MOVF       R2+0, 0
	ADDWF      R0+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	MOVWF      evaluate_full_L0+0
;Teris.c,834 :: 		}
	GOTO       L_evaluate127
L_evaluate126:
;Teris.c,837 :: 		if(matrix->cell[row][col] == 1)
	MOVLW      3
	MOVWF      R1+0
	MOVF       R3+0, 0
	MOVWF      R0+0
	MOVF       R1+0, 0
L__evaluate278:
	BTFSC      STATUS+0, 2
	GOTO       L__evaluate279
	RLF        R0+0, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__evaluate278
L__evaluate279:
	MOVF       FARG_evaluate_matrix+0, 0
	ADDWF      R0+0, 1
	MOVF       R2+0, 0
	ADDWF      R0+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_evaluate128
;Teris.c,839 :: 		if(full == 0)
	MOVF       evaluate_full_L0+0, 0
	XORLW      0
	BTFSS      STATUS+0, 2
	GOTO       L_evaluate129
;Teris.c,841 :: 		risk++;
	INCF       evaluate_risk_L0+0, 1
	BTFSC      STATUS+0, 2
	INCF       evaluate_risk_L0+1, 1
;Teris.c,842 :: 		}
L_evaluate129:
;Teris.c,843 :: 		}
L_evaluate128:
;Teris.c,844 :: 		full = matrix->cell[row][col];
	MOVLW      3
	MOVWF      R1+0
	MOVF       R3+0, 0
	MOVWF      R0+0
	MOVF       R1+0, 0
L__evaluate280:
	BTFSC      STATUS+0, 2
	GOTO       L__evaluate281
	RLF        R0+0, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__evaluate280
L__evaluate281:
	MOVF       FARG_evaluate_matrix+0, 0
	ADDWF      R0+0, 1
	MOVF       R2+0, 0
	ADDWF      R0+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	MOVWF      evaluate_full_L0+0
;Teris.c,845 :: 		}
L_evaluate127:
;Teris.c,829 :: 		for(row = MATRIX88_ROW_MAX - 1; row >= 0; row--)
	DECF       R3+0, 1
;Teris.c,846 :: 		}
	GOTO       L_evaluate123
L_evaluate124:
;Teris.c,826 :: 		for(col = 0; col < MATRIX88_COLUMN_MAX; col++)
	INCF       R2+0, 1
;Teris.c,847 :: 		}
	GOTO       L_evaluate120
L_evaluate121:
;Teris.c,853 :: 		return risk;
	MOVF       evaluate_risk_L0+0, 0
	MOVWF      R0+0
	MOVF       evaluate_risk_L0+1, 0
	MOVWF      R0+1
;Teris.c,854 :: 		}
L_end_evaluate:
	RETURN
; end of _evaluate

_char_info_index_rand:

;Teris.c,855 :: 		unsigned short char_info_index_rand()
;Teris.c,857 :: 		return (unsigned short)(rand()%CHARACTER_MAX);
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
;Teris.c,858 :: 		}
L_end_char_info_index_rand:
	RETURN
; end of _char_info_index_rand

_left_most:

;Teris.c,859 :: 		short left_most(short x, const MATRIX44* matrix_44, MATRIX88* matrix_88)
;Teris.c,861 :: 		while(1)
L_left_most130:
;Teris.c,863 :: 		if(is_left_boundary(x, matrix_44, matrix_88) == LEFT_OVER_BOUNDARY)
	MOVF       FARG_left_most_x+0, 0
	MOVWF      FARG_is_left_boundary_x+0
	MOVF       FARG_left_most_matrix_44+0, 0
	MOVWF      FARG_is_left_boundary_matrix_44+0
	MOVF       FARG_left_most_matrix_44+1, 0
	MOVWF      FARG_is_left_boundary_matrix_44+1
	MOVF       FARG_left_most_matrix_88+0, 0
	MOVWF      FARG_is_left_boundary_matrix_88+0
	CALL       _is_left_boundary+0
	MOVF       R0+0, 0
	XORLW      2
	BTFSS      STATUS+0, 2
	GOTO       L_left_most132
;Teris.c,869 :: 		return x + 1;
	INCF       FARG_left_most_x+0, 0
	MOVWF      R0+0
	GOTO       L_end_left_most
;Teris.c,870 :: 		}
L_left_most132:
;Teris.c,871 :: 		x--;
	DECF       FARG_left_most_x+0, 1
;Teris.c,872 :: 		}
	GOTO       L_left_most130
;Teris.c,873 :: 		}
L_end_left_most:
	RETURN
; end of _left_most

_right_most:

;Teris.c,874 :: 		short right_most(short x, const MATRIX44* matrix_44, MATRIX88* matrix_88)
;Teris.c,876 :: 		while(1)
L_right_most133:
;Teris.c,878 :: 		if(is_right_boundary(x, matrix_44, matrix_88) == RIGHT_OVER_BOUNDARY)
	MOVF       FARG_right_most_x+0, 0
	MOVWF      FARG_is_right_boundary_x+0
	MOVF       FARG_right_most_matrix_44+0, 0
	MOVWF      FARG_is_right_boundary_matrix_44+0
	MOVF       FARG_right_most_matrix_44+1, 0
	MOVWF      FARG_is_right_boundary_matrix_44+1
	MOVF       FARG_right_most_matrix_88+0, 0
	MOVWF      FARG_is_right_boundary_matrix_88+0
	CALL       _is_right_boundary+0
	MOVF       R0+0, 0
	XORLW      3
	BTFSS      STATUS+0, 2
	GOTO       L_right_most135
;Teris.c,884 :: 		return x - 1;
	DECF       FARG_right_most_x+0, 0
	MOVWF      R0+0
	GOTO       L_end_right_most
;Teris.c,885 :: 		}
L_right_most135:
;Teris.c,886 :: 		x++;
	INCF       FARG_right_most_x+0, 1
;Teris.c,887 :: 		}
	GOTO       L_right_most133
;Teris.c,888 :: 		}
L_end_right_most:
	RETURN
; end of _right_most

_get_high:

;Teris.c,889 :: 		unsigned short get_high(MATRIX88* matrix)
;Teris.c,892 :: 		for(row = MATRIX88_ROW_MAX - 1; row >= 0; row--)
	MOVLW      7
	MOVWF      get_high_row_L0+0
L_get_high136:
	MOVLW      128
	XORWF      get_high_row_L0+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 0
	GOTO       L_get_high137
;Teris.c,894 :: 		if(is_row_empty(matrix, row) == 1)
	MOVF       FARG_get_high_matrix+0, 0
	MOVWF      FARG_is_row_empty_matrix+0
	MOVF       get_high_row_L0+0, 0
	MOVWF      FARG_is_row_empty_row+0
	CALL       _is_row_empty+0
	MOVF       R0+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_get_high139
;Teris.c,900 :: 		return (unsigned short)(MATRIX88_ROW_MAX - row - 1);
	MOVF       get_high_row_L0+0, 0
	SUBLW      8
	MOVWF      R0+0
	DECF       R0+0, 1
	GOTO       L_end_get_high
;Teris.c,901 :: 		}
L_get_high139:
;Teris.c,892 :: 		for(row = MATRIX88_ROW_MAX - 1; row >= 0; row--)
	DECF       get_high_row_L0+0, 1
;Teris.c,902 :: 		}
	GOTO       L_get_high136
L_get_high137:
;Teris.c,903 :: 		return MATRIX88_ROW_MAX;
	MOVLW      8
	MOVWF      R0+0
;Teris.c,904 :: 		}
L_end_get_high:
	RETURN
; end of _get_high

_get_high_after_merge:

;Teris.c,905 :: 		unsigned short get_high_after_merge(short y, const MATRIX44* matrix)
;Teris.c,909 :: 		for(row = 0; row < MATRIX44_ROW_MAX; row++)
	CLRF       R3+0
L_get_high_after_merge140:
	MOVLW      128
	XORWF      R3+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      4
	SUBWF      R0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_get_high_after_merge141
;Teris.c,911 :: 		for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
	CLRF       R4+0
L_get_high_after_merge143:
	MOVLW      128
	XORWF      R4+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      4
	SUBWF      R0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_get_high_after_merge144
;Teris.c,913 :: 		if(matrix->cell[row][col] == 1)
	MOVF       R3+0, 0
	MOVWF      R0+0
	MOVLW      0
	BTFSC      R0+0, 7
	MOVLW      255
	MOVWF      R0+1
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	MOVF       FARG_get_high_after_merge_matrix+0, 0
	ADDWF      R0+0, 1
	MOVF       FARG_get_high_after_merge_matrix+1, 0
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      R0+1, 1
	MOVF       R4+0, 0
	ADDWF      R0+0, 1
	BTFSC      STATUS+0, 0
	INCF       R0+1, 1
	MOVLW      0
	BTFSC      R4+0, 7
	MOVLW      255
	ADDWF      R0+1, 1
	MOVF       R0+0, 0
	MOVWF      ___DoICPAddr+0
	MOVF       R0+1, 0
	MOVWF      ___DoICPAddr+1
	CALL       _____DoICP+0
	MOVWF      R1+0
	MOVF       R1+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_get_high_after_merge146
;Teris.c,919 :: 		return (unsigned short)(MATRIX88_ROW_MAX - y - row);
	MOVF       FARG_get_high_after_merge_y+0, 0
	SUBLW      8
	MOVWF      R0+0
	MOVF       R3+0, 0
	SUBWF      R0+0, 1
	GOTO       L_end_get_high_after_merge
;Teris.c,920 :: 		}
L_get_high_after_merge146:
;Teris.c,911 :: 		for(col = 0; col < MATRIX44_COLUMN_MAX; col++)
	INCF       R4+0, 1
;Teris.c,921 :: 		}
	GOTO       L_get_high_after_merge143
L_get_high_after_merge144:
;Teris.c,909 :: 		for(row = 0; row < MATRIX44_ROW_MAX; row++)
	INCF       R3+0, 1
;Teris.c,922 :: 		}
	GOTO       L_get_high_after_merge140
L_get_high_after_merge141:
;Teris.c,923 :: 		}
L_end_get_high_after_merge:
	RETURN
; end of _get_high_after_merge

_get_holes_after_merge:

;Teris.c,924 :: 		unsigned short get_holes_after_merge(MATRIX88* matrix)
;Teris.c,926 :: 		short start = -1;
	MOVLW      255
	MOVWF      get_holes_after_merge_start_L0+0
	MOVLW      255
	MOVWF      get_holes_after_merge_stop_L0+0
	CLRF       get_holes_after_merge_num_hole_L0+0
;Teris.c,931 :: 		for(col = 0; col < MATRIX88_COLUMN_MAX; col++)
	CLRF       R5+0
L_get_holes_after_merge147:
	MOVLW      128
	XORWF      R5+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      8
	SUBWF      R0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_get_holes_after_merge148
;Teris.c,933 :: 		start = stop = -1;
	MOVLW      255
	MOVWF      get_holes_after_merge_stop_L0+0
	MOVLW      255
	MOVWF      get_holes_after_merge_start_L0+0
;Teris.c,934 :: 		for(row = 0; row < MATRIX88_ROW_MAX; row++)
	CLRF       R6+0
L_get_holes_after_merge150:
	MOVLW      128
	XORWF      R6+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      8
	SUBWF      R0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_get_holes_after_merge151
;Teris.c,936 :: 		if(col == 0)
	MOVF       R5+0, 0
	XORLW      0
	BTFSS      STATUS+0, 2
	GOTO       L_get_holes_after_merge153
;Teris.c,938 :: 		if((matrix->cell[row][col] == 0) && (matrix->cell[row][col + 1] == 1))
	MOVLW      3
	MOVWF      R1+0
	MOVF       R6+0, 0
	MOVWF      R0+0
	MOVF       R1+0, 0
L__get_holes_after_merge288:
	BTFSC      STATUS+0, 2
	GOTO       L__get_holes_after_merge289
	RLF        R0+0, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__get_holes_after_merge288
L__get_holes_after_merge289:
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
L__get_holes_after_merge290:
	BTFSC      STATUS+0, 2
	GOTO       L__get_holes_after_merge291
	RLF        R0+0, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__get_holes_after_merge290
L__get_holes_after_merge291:
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
L__get_holes_after_merge215:
;Teris.c,940 :: 		if(start == -1)
	MOVF       get_holes_after_merge_start_L0+0, 0
	XORLW      255
	BTFSS      STATUS+0, 2
	GOTO       L_get_holes_after_merge157
;Teris.c,942 :: 		start = row;
	MOVF       R6+0, 0
	MOVWF      get_holes_after_merge_start_L0+0
;Teris.c,943 :: 		}
L_get_holes_after_merge157:
;Teris.c,944 :: 		}
L_get_holes_after_merge156:
;Teris.c,945 :: 		}
	GOTO       L_get_holes_after_merge158
L_get_holes_after_merge153:
;Teris.c,946 :: 		else if(col == MATRIX88_COLUMN_MAX - 1)
	MOVF       R5+0, 0
	XORLW      7
	BTFSS      STATUS+0, 2
	GOTO       L_get_holes_after_merge159
;Teris.c,948 :: 		if((matrix->cell[row][col] == 0) && (matrix->cell[row][col - 1] == 1))
	MOVLW      3
	MOVWF      R1+0
	MOVF       R6+0, 0
	MOVWF      R0+0
	MOVF       R1+0, 0
L__get_holes_after_merge292:
	BTFSC      STATUS+0, 2
	GOTO       L__get_holes_after_merge293
	RLF        R0+0, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__get_holes_after_merge292
L__get_holes_after_merge293:
	MOVF       FARG_get_holes_after_merge_matrix+0, 0
	ADDWF      R0+0, 1
	MOVF       R5+0, 0
	ADDWF      R0+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	XORLW      0
	BTFSS      STATUS+0, 2
	GOTO       L_get_holes_after_merge162
	MOVLW      3
	MOVWF      R1+0
	MOVF       R6+0, 0
	MOVWF      R0+0
	MOVF       R1+0, 0
L__get_holes_after_merge294:
	BTFSC      STATUS+0, 2
	GOTO       L__get_holes_after_merge295
	RLF        R0+0, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__get_holes_after_merge294
L__get_holes_after_merge295:
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
	GOTO       L_get_holes_after_merge162
L__get_holes_after_merge214:
;Teris.c,950 :: 		if(start == -1)
	MOVF       get_holes_after_merge_start_L0+0, 0
	XORLW      255
	BTFSS      STATUS+0, 2
	GOTO       L_get_holes_after_merge163
;Teris.c,952 :: 		start = row;
	MOVF       R6+0, 0
	MOVWF      get_holes_after_merge_start_L0+0
;Teris.c,953 :: 		}
L_get_holes_after_merge163:
;Teris.c,954 :: 		}
L_get_holes_after_merge162:
;Teris.c,955 :: 		}
	GOTO       L_get_holes_after_merge164
L_get_holes_after_merge159:
;Teris.c,958 :: 		if((matrix->cell[row][col] == 0) && (matrix->cell[row][col - 1] == 1) && (matrix->cell[row][col + 1] == 1))
	MOVLW      3
	MOVWF      R1+0
	MOVF       R6+0, 0
	MOVWF      R0+0
	MOVF       R1+0, 0
L__get_holes_after_merge296:
	BTFSC      STATUS+0, 2
	GOTO       L__get_holes_after_merge297
	RLF        R0+0, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__get_holes_after_merge296
L__get_holes_after_merge297:
	MOVF       FARG_get_holes_after_merge_matrix+0, 0
	ADDWF      R0+0, 1
	MOVF       R5+0, 0
	ADDWF      R0+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	XORLW      0
	BTFSS      STATUS+0, 2
	GOTO       L_get_holes_after_merge167
	MOVLW      3
	MOVWF      R1+0
	MOVF       R6+0, 0
	MOVWF      R0+0
	MOVF       R1+0, 0
L__get_holes_after_merge298:
	BTFSC      STATUS+0, 2
	GOTO       L__get_holes_after_merge299
	RLF        R0+0, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__get_holes_after_merge298
L__get_holes_after_merge299:
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
	GOTO       L_get_holes_after_merge167
	MOVLW      3
	MOVWF      R1+0
	MOVF       R6+0, 0
	MOVWF      R0+0
	MOVF       R1+0, 0
L__get_holes_after_merge300:
	BTFSC      STATUS+0, 2
	GOTO       L__get_holes_after_merge301
	RLF        R0+0, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__get_holes_after_merge300
L__get_holes_after_merge301:
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
	GOTO       L_get_holes_after_merge167
L__get_holes_after_merge213:
;Teris.c,960 :: 		if(start == -1)
	MOVF       get_holes_after_merge_start_L0+0, 0
	XORLW      255
	BTFSS      STATUS+0, 2
	GOTO       L_get_holes_after_merge168
;Teris.c,962 :: 		start = row;
	MOVF       R6+0, 0
	MOVWF      get_holes_after_merge_start_L0+0
;Teris.c,963 :: 		}
L_get_holes_after_merge168:
;Teris.c,964 :: 		}
L_get_holes_after_merge167:
;Teris.c,965 :: 		}
L_get_holes_after_merge164:
L_get_holes_after_merge158:
;Teris.c,966 :: 		if(start >= 0)
	MOVLW      128
	XORWF      get_holes_after_merge_start_L0+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 0
	GOTO       L_get_holes_after_merge169
;Teris.c,968 :: 		if(row == MATRIX88_ROW_MAX - 1)
	MOVF       R6+0, 0
	XORLW      7
	BTFSS      STATUS+0, 2
	GOTO       L_get_holes_after_merge170
;Teris.c,970 :: 		if(stop == -1)
	MOVF       get_holes_after_merge_stop_L0+0, 0
	XORLW      255
	BTFSS      STATUS+0, 2
	GOTO       L_get_holes_after_merge171
;Teris.c,972 :: 		stop = MATRIX88_ROW_MAX;
	MOVLW      8
	MOVWF      get_holes_after_merge_stop_L0+0
;Teris.c,973 :: 		}
L_get_holes_after_merge171:
;Teris.c,974 :: 		}
	GOTO       L_get_holes_after_merge172
L_get_holes_after_merge170:
;Teris.c,975 :: 		else if(matrix->cell[row + 1][col] == 1)
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
L__get_holes_after_merge302:
	BTFSC      STATUS+0, 2
	GOTO       L__get_holes_after_merge303
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__get_holes_after_merge302
L__get_holes_after_merge303:
	MOVF       FARG_get_holes_after_merge_matrix+0, 0
	ADDWF      R0+0, 1
	MOVF       R5+0, 0
	ADDWF      R0+0, 0
	MOVWF      FSR
	MOVF       INDF+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_get_holes_after_merge173
;Teris.c,977 :: 		if(stop == -1)
	MOVF       get_holes_after_merge_stop_L0+0, 0
	XORLW      255
	BTFSS      STATUS+0, 2
	GOTO       L_get_holes_after_merge174
;Teris.c,979 :: 		stop = row + 1;
	INCF       R6+0, 0
	MOVWF      get_holes_after_merge_stop_L0+0
;Teris.c,980 :: 		}
L_get_holes_after_merge174:
;Teris.c,981 :: 		}
L_get_holes_after_merge173:
L_get_holes_after_merge172:
;Teris.c,982 :: 		}
L_get_holes_after_merge169:
;Teris.c,934 :: 		for(row = 0; row < MATRIX88_ROW_MAX; row++)
	INCF       R6+0, 1
;Teris.c,984 :: 		}
	GOTO       L_get_holes_after_merge150
L_get_holes_after_merge151:
;Teris.c,985 :: 		if((start >= 0) && (stop >= 0) && (stop - start >= 3))
	MOVLW      128
	XORWF      get_holes_after_merge_start_L0+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 0
	GOTO       L_get_holes_after_merge177
	MOVLW      128
	XORWF      get_holes_after_merge_stop_L0+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORLW      0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 0
	GOTO       L_get_holes_after_merge177
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
	GOTO       L__get_holes_after_merge304
	MOVLW      3
	SUBWF      R1+0, 0
L__get_holes_after_merge304:
	BTFSS      STATUS+0, 0
	GOTO       L_get_holes_after_merge177
L__get_holes_after_merge212:
;Teris.c,991 :: 		num_hole++;
	INCF       get_holes_after_merge_num_hole_L0+0, 1
;Teris.c,992 :: 		}
L_get_holes_after_merge177:
;Teris.c,931 :: 		for(col = 0; col < MATRIX88_COLUMN_MAX; col++)
	INCF       R5+0, 1
;Teris.c,993 :: 		}
	GOTO       L_get_holes_after_merge147
L_get_holes_after_merge148:
;Teris.c,998 :: 		return num_hole;
	MOVF       get_holes_after_merge_num_hole_L0+0, 0
	MOVWF      R0+0
;Teris.c,999 :: 		}
L_end_get_holes_after_merge:
	RETURN
; end of _get_holes_after_merge

_find_best_solution:

;Teris.c,1000 :: 		unsigned short find_best_solution()
;Teris.c,1002 :: 		short temp_pre_x = 0xFF, tem_pre_sub_index = 0xFF;
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
;Teris.c,1020 :: 		printf_console_MATRIX88("8", &g_matrix88);
	MOVLW      ?lstr16_Teris+0
	MOVWF      FARG_printf_console_MATRIX88_lable+0
	MOVLW      _g_matrix88+0
	MOVWF      FARG_printf_console_MATRIX88_matrix+0
	CALL       _printf_console_MATRIX88+0
;Teris.c,1026 :: 		Cus_UART1_Write_Int("index", g_char_info_index);
	MOVLW      ?lstr17_Teris+0
	MOVWF      FARG_Cus_UART1_Write_Int_lable+0
	MOVF       _g_char_info_index+0, 0
	MOVWF      FARG_Cus_UART1_Write_Int_UART_data+0
	CLRF       FARG_Cus_UART1_Write_Int_UART_data+1
	CALL       _Cus_UART1_Write_Int+0
;Teris.c,1028 :: 		for(tem_sub_index = 0; tem_sub_index < g_char_info[g_char_info_index].num; tem_sub_index++)
	CLRF       find_best_solution_tem_sub_index_L0+0
L_find_best_solution178:
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
	GOTO       L_find_best_solution179
;Teris.c,1031 :: 		left_most_index = left_most(cur_x, GET_TEMP_MAXTRIX44, &g_matrix88);
	MOVF       _cur_x+0, 0
	MOVWF      FARG_left_most_x+0
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
L__find_best_solution306:
	BTFSC      STATUS+0, 2
	GOTO       L__find_best_solution307
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__find_best_solution306
L__find_best_solution307:
	MOVF       R0+0, 0
	ADDLW      _g_matrix44+0
	MOVWF      FARG_left_most_matrix_44+0
	MOVLW      hi_addr(_g_matrix44+0)
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      R0+1, 0
	MOVWF      FARG_left_most_matrix_44+1
	MOVLW      _g_matrix88+0
	MOVWF      FARG_left_most_matrix_88+0
	CALL       _left_most+0
	MOVF       R0+0, 0
	MOVWF      find_best_solution_left_most_index_L0+0
;Teris.c,1032 :: 		right_most_index = right_most(cur_x, GET_TEMP_MAXTRIX44, &g_matrix88);
	MOVF       _cur_x+0, 0
	MOVWF      FARG_right_most_x+0
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
L__find_best_solution308:
	BTFSC      STATUS+0, 2
	GOTO       L__find_best_solution309
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__find_best_solution308
L__find_best_solution309:
	MOVF       R0+0, 0
	ADDLW      _g_matrix44+0
	MOVWF      FARG_right_most_matrix_44+0
	MOVLW      hi_addr(_g_matrix44+0)
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      R0+1, 0
	MOVWF      FARG_right_most_matrix_44+1
	MOVLW      _g_matrix88+0
	MOVWF      FARG_right_most_matrix_88+0
	CALL       _right_most+0
	MOVF       R0+0, 0
	MOVWF      find_best_solution_right_most_index_L0+0
;Teris.c,1034 :: 		for(temp_x = left_most_index; temp_x <= right_most_index; temp_x++)
	MOVF       find_best_solution_left_most_index_L0+0, 0
	MOVWF      find_best_solution_temp_x_L1+0
L_find_best_solution181:
	MOVLW      128
	XORWF      find_best_solution_right_most_index_L0+0, 0
	MOVWF      R0+0
	MOVLW      128
	XORWF      find_best_solution_temp_x_L1+0, 0
	SUBWF      R0+0, 0
	BTFSS      STATUS+0, 0
	GOTO       L_find_best_solution182
;Teris.c,1036 :: 		temp_y = fall_off(temp_x, cur_y, GET_TEMP_MAXTRIX44, &g_matrix88);
	MOVF       find_best_solution_temp_x_L1+0, 0
	MOVWF      FARG_fall_off_x+0
	MOVF       _cur_y+0, 0
	MOVWF      FARG_fall_off_y+0
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
L__find_best_solution310:
	BTFSC      STATUS+0, 2
	GOTO       L__find_best_solution311
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__find_best_solution310
L__find_best_solution311:
	MOVF       R0+0, 0
	ADDLW      _g_matrix44+0
	MOVWF      FARG_fall_off_matrix_44+0
	MOVLW      hi_addr(_g_matrix44+0)
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      R0+1, 0
	MOVWF      FARG_fall_off_matrix_44+1
	MOVLW      _g_matrix88+0
	MOVWF      FARG_fall_off_matrix_88+0
	CALL       _fall_off+0
	MOVF       R0+0, 0
	MOVWF      find_best_solution_temp_y_L0+0
;Teris.c,1037 :: 		Cus_UART1_Write_Text_Item("2:");
	MOVLW      ?lstr18_Teris+0
	MOVWF      FARG_Cus_UART1_Write_Text_Item_UART_text+0
	CALL       _Cus_UART1_Write_Text_Item+0
;Teris.c,1038 :: 		printf_console_MATRIX44(temp_x, temp_y, GET_TEMP_MAXTRIX44);
	MOVF       find_best_solution_temp_x_L1+0, 0
	MOVWF      FARG_printf_console_MATRIX44_x+0
	MOVF       find_best_solution_temp_y_L0+0, 0
	MOVWF      FARG_printf_console_MATRIX44_y+0
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
L__find_best_solution312:
	BTFSC      STATUS+0, 2
	GOTO       L__find_best_solution313
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__find_best_solution312
L__find_best_solution313:
	MOVF       R0+0, 0
	ADDLW      _g_matrix44+0
	MOVWF      FARG_printf_console_MATRIX44_matrix+0
	MOVLW      hi_addr(_g_matrix44+0)
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      R0+1, 0
	MOVWF      FARG_printf_console_MATRIX44_matrix+1
	CALL       _printf_console_MATRIX44+0
;Teris.c,1039 :: 		printf_console_MATRIX88("2", &g_matrix88);
	MOVLW      ?lstr19_Teris+0
	MOVWF      FARG_printf_console_MATRIX88_lable+0
	MOVLW      _g_matrix88+0
	MOVWF      FARG_printf_console_MATRIX88_matrix+0
	CALL       _printf_console_MATRIX88+0
;Teris.c,1040 :: 		printf_Screen();
	CALL       _printf_Screen+0
;Teris.c,1041 :: 		if(is_valid(temp_x, temp_y, GET_TEMP_MAXTRIX44, &g_matrix88) == 0)
	MOVF       find_best_solution_temp_x_L1+0, 0
	MOVWF      FARG_is_valid_x+0
	MOVF       find_best_solution_temp_y_L0+0, 0
	MOVWF      FARG_is_valid_y+0
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
L__find_best_solution314:
	BTFSC      STATUS+0, 2
	GOTO       L__find_best_solution315
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__find_best_solution314
L__find_best_solution315:
	MOVF       R0+0, 0
	ADDLW      _g_matrix44+0
	MOVWF      FARG_is_valid_matrix_44+0
	MOVLW      hi_addr(_g_matrix44+0)
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      R0+1, 0
	MOVWF      FARG_is_valid_matrix_44+1
	MOVLW      _g_matrix88+0
	MOVWF      FARG_is_valid_matrix_88+0
	CALL       _is_valid+0
	MOVF       R0+0, 0
	XORLW      0
	BTFSS      STATUS+0, 2
	GOTO       L_find_best_solution184
;Teris.c,1043 :: 		continue;
	GOTO       L_find_best_solution183
;Teris.c,1044 :: 		}
L_find_best_solution184:
;Teris.c,1045 :: 		res = 1;
	MOVLW      1
	MOVWF      find_best_solution_res_L0+0
;Teris.c,1046 :: 		merge1(temp_x, temp_y, GET_TEMP_MAXTRIX44, &g_matrix88, &temp_matrix88);
	MOVF       find_best_solution_temp_x_L1+0, 0
	MOVWF      FARG_merge1_x+0
	MOVF       find_best_solution_temp_y_L0+0, 0
	MOVWF      FARG_merge1_y+0
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
L__find_best_solution316:
	BTFSC      STATUS+0, 2
	GOTO       L__find_best_solution317
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__find_best_solution316
L__find_best_solution317:
	MOVF       R0+0, 0
	ADDLW      _g_matrix44+0
	MOVWF      FARG_merge1_matrix_44+0
	MOVLW      hi_addr(_g_matrix44+0)
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      R0+1, 0
	MOVWF      FARG_merge1_matrix_44+1
	MOVLW      _g_matrix88+0
	MOVWF      FARG_merge1_matrix88_in+0
	MOVLW      find_best_solution_temp_matrix88_L0+0
	MOVWF      FARG_merge1_matrix88_out+0
	CALL       _merge1+0
;Teris.c,1047 :: 		temp_count = delete_matrix(&temp_matrix88);
	MOVLW      find_best_solution_temp_matrix88_L0+0
	MOVWF      FARG_delete_matrix_matrix+0
	CALL       _delete_matrix+0
	MOVF       R0+0, 0
	MOVWF      find_best_solution_temp_count_L0+0
;Teris.c,1048 :: 		temp_risk = evaluate(&temp_matrix88);
	MOVLW      find_best_solution_temp_matrix88_L0+0
	MOVWF      FARG_evaluate_matrix+0
	CALL       _evaluate+0
	MOVF       R0+0, 0
	MOVWF      find_best_solution_temp_risk_L0+0
	MOVF       R0+1, 0
	MOVWF      find_best_solution_temp_risk_L0+1
;Teris.c,1049 :: 		temp_high = get_high_after_merge(temp_y, GET_TEMP_MAXTRIX44);
	MOVF       find_best_solution_temp_y_L0+0, 0
	MOVWF      FARG_get_high_after_merge_y+0
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
L__find_best_solution318:
	BTFSC      STATUS+0, 2
	GOTO       L__find_best_solution319
	RLF        R0+0, 1
	RLF        R0+1, 1
	BCF        R0+0, 0
	ADDLW      255
	GOTO       L__find_best_solution318
L__find_best_solution319:
	MOVF       R0+0, 0
	ADDLW      _g_matrix44+0
	MOVWF      FARG_get_high_after_merge_matrix+0
	MOVLW      hi_addr(_g_matrix44+0)
	BTFSC      STATUS+0, 0
	ADDLW      1
	ADDWF      R0+1, 0
	MOVWF      FARG_get_high_after_merge_matrix+1
	CALL       _get_high_after_merge+0
	MOVF       R0+0, 0
	MOVWF      find_best_solution_temp_high_L0+0
;Teris.c,1050 :: 		temp_hole = get_holes_after_merge(&temp_matrix88);
	MOVLW      find_best_solution_temp_matrix88_L0+0
	MOVWF      FARG_get_holes_after_merge_matrix+0
	CALL       _get_holes_after_merge+0
	MOVF       R0+0, 0
	MOVWF      find_best_solution_temp_hole_L0+0
;Teris.c,1054 :: 		printf_console_MATRIX88("3", &temp_matrix88);
	MOVLW      ?lstr20_Teris+0
	MOVWF      FARG_printf_console_MATRIX88_lable+0
	MOVLW      find_best_solution_temp_matrix88_L0+0
	MOVWF      FARG_printf_console_MATRIX88_matrix+0
	CALL       _printf_console_MATRIX88+0
;Teris.c,1056 :: 		if(temp_count > temp_pre_count)
	MOVF       find_best_solution_temp_count_L0+0, 0
	SUBWF      find_best_solution_temp_pre_count_L0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_find_best_solution185
;Teris.c,1062 :: 		temp_pre_count = temp_count;
	MOVF       find_best_solution_temp_count_L0+0, 0
	MOVWF      find_best_solution_temp_pre_count_L0+0
;Teris.c,1063 :: 		temp_pre_risk = temp_risk;
	MOVF       find_best_solution_temp_risk_L0+0, 0
	MOVWF      find_best_solution_temp_pre_risk_L0+0
	MOVF       find_best_solution_temp_risk_L0+1, 0
	MOVWF      find_best_solution_temp_pre_risk_L0+1
;Teris.c,1064 :: 		temp_pre_high = temp_high;
	MOVF       find_best_solution_temp_high_L0+0, 0
	MOVWF      find_best_solution_temp_pre_high_L0+0
;Teris.c,1065 :: 		temp_pre_hole = temp_hole;
	MOVF       find_best_solution_temp_hole_L0+0, 0
	MOVWF      find_best_solution_temp_pre_hole_L0+0
;Teris.c,1066 :: 		tem_pre_sub_index = tem_sub_index;
	MOVF       find_best_solution_tem_sub_index_L0+0, 0
	MOVWF      find_best_solution_tem_pre_sub_index_L0+0
;Teris.c,1067 :: 		temp_pre_x = temp_x;
	MOVF       find_best_solution_temp_x_L1+0, 0
	MOVWF      find_best_solution_temp_pre_x_L0+0
;Teris.c,1068 :: 		}
	GOTO       L_find_best_solution186
L_find_best_solution185:
;Teris.c,1069 :: 		else if(temp_count == temp_pre_count)
	MOVF       find_best_solution_temp_count_L0+0, 0
	XORWF      find_best_solution_temp_pre_count_L0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L_find_best_solution187
;Teris.c,1071 :: 		if(get_high(&g_matrix88) <= MATRIX88_ROW_MAX/2 + 1)
	MOVLW      _g_matrix88+0
	MOVWF      FARG_get_high_matrix+0
	CALL       _get_high+0
	MOVF       R0+0, 0
	SUBLW      5
	BTFSS      STATUS+0, 0
	GOTO       L_find_best_solution188
;Teris.c,1079 :: 		if(temp_risk < temp_pre_risk)
	MOVF       find_best_solution_temp_pre_risk_L0+1, 0
	SUBWF      find_best_solution_temp_risk_L0+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__find_best_solution320
	MOVF       find_best_solution_temp_pre_risk_L0+0, 0
	SUBWF      find_best_solution_temp_risk_L0+0, 0
L__find_best_solution320:
	BTFSC      STATUS+0, 0
	GOTO       L_find_best_solution189
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
	GOTO       L_find_best_solution190
L_find_best_solution189:
;Teris.c,1092 :: 		else if(temp_risk == temp_pre_risk)
	MOVF       find_best_solution_temp_risk_L0+1, 0
	XORWF      find_best_solution_temp_pre_risk_L0+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__find_best_solution321
	MOVF       find_best_solution_temp_pre_risk_L0+0, 0
	XORWF      find_best_solution_temp_risk_L0+0, 0
L__find_best_solution321:
	BTFSS      STATUS+0, 2
	GOTO       L_find_best_solution191
;Teris.c,1098 :: 		if(temp_high < temp_pre_high)
	MOVF       find_best_solution_temp_pre_high_L0+0, 0
	SUBWF      find_best_solution_temp_high_L0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_find_best_solution192
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
	GOTO       L_find_best_solution193
L_find_best_solution192:
;Teris.c,1111 :: 		else if(temp_high == temp_pre_high)
	MOVF       find_best_solution_temp_high_L0+0, 0
	XORWF      find_best_solution_temp_pre_high_L0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L_find_best_solution194
;Teris.c,1117 :: 		if(temp_hole < temp_pre_hole)
	MOVF       find_best_solution_temp_pre_hole_L0+0, 0
	SUBWF      find_best_solution_temp_hole_L0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_find_best_solution195
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
L_find_best_solution195:
;Teris.c,1131 :: 		}
L_find_best_solution194:
L_find_best_solution193:
;Teris.c,1133 :: 		}
L_find_best_solution191:
L_find_best_solution190:
;Teris.c,1134 :: 		}
	GOTO       L_find_best_solution196
L_find_best_solution188:
;Teris.c,1142 :: 		if(temp_high < temp_pre_high)
	MOVF       find_best_solution_temp_pre_high_L0+0, 0
	SUBWF      find_best_solution_temp_high_L0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_find_best_solution197
;Teris.c,1148 :: 		temp_pre_count = temp_count;
	MOVF       find_best_solution_temp_count_L0+0, 0
	MOVWF      find_best_solution_temp_pre_count_L0+0
;Teris.c,1149 :: 		temp_pre_risk = temp_risk;
	MOVF       find_best_solution_temp_risk_L0+0, 0
	MOVWF      find_best_solution_temp_pre_risk_L0+0
	MOVF       find_best_solution_temp_risk_L0+1, 0
	MOVWF      find_best_solution_temp_pre_risk_L0+1
;Teris.c,1150 :: 		temp_pre_high = temp_high;
	MOVF       find_best_solution_temp_high_L0+0, 0
	MOVWF      find_best_solution_temp_pre_high_L0+0
;Teris.c,1151 :: 		temp_pre_hole = temp_hole;
	MOVF       find_best_solution_temp_hole_L0+0, 0
	MOVWF      find_best_solution_temp_pre_hole_L0+0
;Teris.c,1152 :: 		tem_pre_sub_index = tem_sub_index;
	MOVF       find_best_solution_tem_sub_index_L0+0, 0
	MOVWF      find_best_solution_tem_pre_sub_index_L0+0
;Teris.c,1153 :: 		temp_pre_x = temp_x;
	MOVF       find_best_solution_temp_x_L1+0, 0
	MOVWF      find_best_solution_temp_pre_x_L0+0
;Teris.c,1154 :: 		}
	GOTO       L_find_best_solution198
L_find_best_solution197:
;Teris.c,1155 :: 		else if(temp_high == temp_pre_high)
	MOVF       find_best_solution_temp_high_L0+0, 0
	XORWF      find_best_solution_temp_pre_high_L0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L_find_best_solution199
;Teris.c,1161 :: 		if(temp_hole < temp_pre_hole)
	MOVF       find_best_solution_temp_pre_hole_L0+0, 0
	SUBWF      find_best_solution_temp_hole_L0+0, 0
	BTFSC      STATUS+0, 0
	GOTO       L_find_best_solution200
;Teris.c,1167 :: 		temp_pre_count = temp_count;
	MOVF       find_best_solution_temp_count_L0+0, 0
	MOVWF      find_best_solution_temp_pre_count_L0+0
;Teris.c,1168 :: 		temp_pre_risk = temp_risk;
	MOVF       find_best_solution_temp_risk_L0+0, 0
	MOVWF      find_best_solution_temp_pre_risk_L0+0
	MOVF       find_best_solution_temp_risk_L0+1, 0
	MOVWF      find_best_solution_temp_pre_risk_L0+1
;Teris.c,1169 :: 		temp_pre_high = temp_high;
	MOVF       find_best_solution_temp_high_L0+0, 0
	MOVWF      find_best_solution_temp_pre_high_L0+0
;Teris.c,1170 :: 		temp_pre_hole = temp_hole;
	MOVF       find_best_solution_temp_hole_L0+0, 0
	MOVWF      find_best_solution_temp_pre_hole_L0+0
;Teris.c,1171 :: 		tem_pre_sub_index = tem_sub_index;
	MOVF       find_best_solution_tem_sub_index_L0+0, 0
	MOVWF      find_best_solution_tem_pre_sub_index_L0+0
;Teris.c,1172 :: 		temp_pre_x = temp_x;
	MOVF       find_best_solution_temp_x_L1+0, 0
	MOVWF      find_best_solution_temp_pre_x_L0+0
;Teris.c,1173 :: 		}
	GOTO       L_find_best_solution201
L_find_best_solution200:
;Teris.c,1174 :: 		else if(temp_hole == temp_pre_hole)
	MOVF       find_best_solution_temp_hole_L0+0, 0
	XORWF      find_best_solution_temp_pre_hole_L0+0, 0
	BTFSS      STATUS+0, 2
	GOTO       L_find_best_solution202
;Teris.c,1180 :: 		if(temp_risk < temp_pre_risk)
	MOVF       find_best_solution_temp_pre_risk_L0+1, 0
	SUBWF      find_best_solution_temp_risk_L0+1, 0
	BTFSS      STATUS+0, 2
	GOTO       L__find_best_solution322
	MOVF       find_best_solution_temp_pre_risk_L0+0, 0
	SUBWF      find_best_solution_temp_risk_L0+0, 0
L__find_best_solution322:
	BTFSC      STATUS+0, 0
	GOTO       L_find_best_solution203
;Teris.c,1186 :: 		temp_pre_count = temp_count;
	MOVF       find_best_solution_temp_count_L0+0, 0
	MOVWF      find_best_solution_temp_pre_count_L0+0
;Teris.c,1187 :: 		temp_pre_risk = temp_risk;
	MOVF       find_best_solution_temp_risk_L0+0, 0
	MOVWF      find_best_solution_temp_pre_risk_L0+0
	MOVF       find_best_solution_temp_risk_L0+1, 0
	MOVWF      find_best_solution_temp_pre_risk_L0+1
;Teris.c,1188 :: 		temp_pre_high = temp_high;
	MOVF       find_best_solution_temp_high_L0+0, 0
	MOVWF      find_best_solution_temp_pre_high_L0+0
;Teris.c,1189 :: 		temp_pre_hole = temp_hole;
	MOVF       find_best_solution_temp_hole_L0+0, 0
	MOVWF      find_best_solution_temp_pre_hole_L0+0
;Teris.c,1190 :: 		tem_pre_sub_index = tem_sub_index;
	MOVF       find_best_solution_tem_sub_index_L0+0, 0
	MOVWF      find_best_solution_tem_pre_sub_index_L0+0
;Teris.c,1191 :: 		temp_pre_x = temp_x;
	MOVF       find_best_solution_temp_x_L1+0, 0
	MOVWF      find_best_solution_temp_pre_x_L0+0
;Teris.c,1192 :: 		}
L_find_best_solution203:
;Teris.c,1193 :: 		}
L_find_best_solution202:
L_find_best_solution201:
;Teris.c,1194 :: 		}
L_find_best_solution199:
L_find_best_solution198:
;Teris.c,1195 :: 		}
L_find_best_solution196:
;Teris.c,1196 :: 		}
L_find_best_solution187:
L_find_best_solution186:
;Teris.c,1203 :: 		}
L_find_best_solution183:
;Teris.c,1034 :: 		for(temp_x = left_most_index; temp_x <= right_most_index; temp_x++)
	INCF       find_best_solution_temp_x_L1+0, 1
;Teris.c,1203 :: 		}
	GOTO       L_find_best_solution181
L_find_best_solution182:
;Teris.c,1028 :: 		for(tem_sub_index = 0; tem_sub_index < g_char_info[g_char_info_index].num; tem_sub_index++)
	INCF       find_best_solution_tem_sub_index_L0+0, 1
;Teris.c,1204 :: 		}
	GOTO       L_find_best_solution178
L_find_best_solution179:
;Teris.c,1205 :: 		if(res == 1)
	MOVF       find_best_solution_res_L0+0, 0
	XORLW      1
	BTFSS      STATUS+0, 2
	GOTO       L_find_best_solution204
;Teris.c,1207 :: 		g_char_info_sub_index = tem_pre_sub_index;
	MOVF       find_best_solution_tem_pre_sub_index_L0+0, 0
	MOVWF      _g_char_info_sub_index+0
;Teris.c,1208 :: 		cur_x = temp_pre_x;
	MOVF       find_best_solution_temp_pre_x_L0+0, 0
	MOVWF      _cur_x+0
;Teris.c,1209 :: 		Cus_UART1_Write_Text_Item("4:");
	MOVLW      ?lstr21_Teris+0
	MOVWF      FARG_Cus_UART1_Write_Text_Item_UART_text+0
	CALL       _Cus_UART1_Write_Text_Item+0
;Teris.c,1210 :: 		printf_console_cur_MATRIX44(cur_x, cur_y);
	MOVF       _cur_x+0, 0
	MOVWF      FARG_printf_console_cur_MATRIX44_x+0
	MOVF       _cur_y+0, 0
	MOVWF      FARG_printf_console_cur_MATRIX44_y+0
	CALL       _printf_console_cur_MATRIX44+0
;Teris.c,1211 :: 		printf_console_MATRIX88("4", &temp_matrix88);
	MOVLW      ?lstr22_Teris+0
	MOVWF      FARG_printf_console_MATRIX88_lable+0
	MOVLW      find_best_solution_temp_matrix88_L0+0
	MOVWF      FARG_printf_console_MATRIX88_matrix+0
	CALL       _printf_console_MATRIX88+0
;Teris.c,1218 :: 		}
	GOTO       L_find_best_solution205
L_find_best_solution204:
;Teris.c,1224 :: 		Cus_UART1_Write_Text_Item("GAME OVER!!!\r\n");
	MOVLW      ?lstr23_Teris+0
	MOVWF      FARG_Cus_UART1_Write_Text_Item_UART_text+0
	CALL       _Cus_UART1_Write_Text_Item+0
;Teris.c,1226 :: 		}
L_find_best_solution205:
;Teris.c,1227 :: 		return res;
	MOVF       find_best_solution_res_L0+0, 0
	MOVWF      R0+0
;Teris.c,1228 :: 		}
L_end_find_best_solution:
	RETURN
; end of _find_best_solution

_test:

;Teris.c,1311 :: 		void test()
;Teris.c,1313 :: 		printf_console_MATRIX88("8", &g_matrix88);
	MOVLW      ?lstr24_Teris+0
	MOVWF      FARG_printf_console_MATRIX88_lable+0
	MOVLW      _g_matrix88+0
	MOVWF      FARG_printf_console_MATRIX88_matrix+0
	CALL       _printf_console_MATRIX88+0
;Teris.c,1314 :: 		}
L_end_test:
	RETURN
; end of _test

_main:

;Teris.c,1316 :: 		int main()
;Teris.c,1343 :: 		Chip_Select_Direction = 0;    // Set RA2 pin as output.
	BCF        TRISA2_bit+0, 2
;Teris.c,1347 :: 		srand(0);
	CLRF       FARG_srand_x+0
	CLRF       FARG_srand_x+1
	CALL       _srand+0
;Teris.c,1349 :: 		UART1_Init(9600);
	MOVLW      129
	MOVWF      SPBRG+0
	BSF        TXSTA+0, 2
	CALL       _UART1_Init+0
;Teris.c,1350 :: 		Delay_ms(1000);
	MOVLW      26
	MOVWF      R11+0
	MOVLW      94
	MOVWF      R12+0
	MOVLW      110
	MOVWF      R13+0
L_main206:
	DECFSZ     R13+0, 1
	GOTO       L_main206
	DECFSZ     R12+0, 1
	GOTO       L_main206
	DECFSZ     R11+0, 1
	GOTO       L_main206
	NOP
;Teris.c,1364 :: 		g_char_info_index = 7;
	MOVLW      7
	MOVWF      _g_char_info_index+0
;Teris.c,1365 :: 		g_char_info_sub_index = 0;
	CLRF       _g_char_info_sub_index+0
;Teris.c,1381 :: 		find_best_solution();
	CALL       _find_best_solution+0
;Teris.c,1383 :: 		printf_console_MATRIX88("6", &g_matrix88);
	MOVLW      ?lstr25_Teris+0
	MOVWF      FARG_printf_console_MATRIX88_lable+0
	MOVLW      _g_matrix88+0
	MOVWF      FARG_printf_console_MATRIX88_matrix+0
	CALL       _printf_console_MATRIX88+0
;Teris.c,1384 :: 		while(1)
L_main207:
;Teris.c,1386 :: 		Delay_ms(100);
	MOVLW      3
	MOVWF      R11+0
	MOVLW      138
	MOVWF      R12+0
	MOVLW      85
	MOVWF      R13+0
L_main209:
	DECFSZ     R13+0, 1
	GOTO       L_main209
	DECFSZ     R12+0, 1
	GOTO       L_main209
	DECFSZ     R11+0, 1
	GOTO       L_main209
	NOP
	NOP
;Teris.c,1387 :: 		}
	GOTO       L_main207
;Teris.c,1468 :: 		}
L_end_main:
	GOTO       $+0
; end of _main