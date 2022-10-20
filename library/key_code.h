/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_code.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmongell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 19:30:16 by tmongell          #+#    #+#             */
/*   Updated: 2022/03/26 14:24:37 by tmongell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//this library is used to call a key via a macro rather than it's num code:

#ifndef KEY_CODE_H
# define KEY_CODE_H

//ascii key
# define KEY_A 0
# define KEY_B 11
# define KEY_C 8
# define KEY_D 2
# define KEY_E 14
# define KEY_F 3
# define KEY_G 5
# define KEY_H 4
# define KEY_I 34
# define KEY_J 38
# define KEY_K 40
# define KEY_L 37
# define KEY_M 46
# define KEY_N 45
# define KEY_O 31
# define KEY_P 35
# define KEY_Q 12
# define KEY_R 15
# define KEY_S 1
# define KEY_T 17
# define KEY_U 32
# define KEY_V 9
# define KEY_W 13
# define KEY_X 7
# define KEY_Y 16
# define KEY_Z 6
# define KEY_1 18
# define KEY_2 19
# define KEY_3 20
# define KEY_4 21
# define KEY_5 23
# define KEY_6 22
# define KEY_7 26
# define KEY_8 28
# define KEY_9 25
# define KEY_0 29
# define KEY_MINUS 27
# define KEY_PLUS 24
# define KEY_TILD 50
# define KEY_BRAKET_OP 33
# define KEY_BRACKET_CL 30
# define KEY_PIPE 42
# define KEY_SEMICOLON 41
# define KEY_QUOTE 39
# define KEY_COMMA 43
# define KEY_PERIOD 47
# define KEY_SLASH 44
# define KEY_SPACE 49

//modiffier key

# define KEY_CTRL 256
# define KEY_FN -1
# define KEY_CMD 259
# define KEY_ALT 261
# define KEY_SHIFT 257
# define KEY_CAPS_LOCK 272 //send code only on unlock according to my tests
# define KEY_L_CTRL 269
# define KEY_L_ALT 262
# define KEY_L_SHIFT 258

//numpad

# define NUMKEY_0 82
# define NUMKEY_1 83
# define NUMKEY_2 84
# define NUMKEY_3 85
# define NUMKEY_4 86
# define NUMKEY_5 87
# define NUMKEY_6 88
# define NUMKEY_7 89
# define NUMKEY_8 91
# define NUMKEY_9 92
# define NUMKEY_PLUS 69
# define NUMKEY_MINUS 78
# define NUMKEY_DIV 75
# define NUMKEY_MULT 67
# define NUMKEY_PERIOD 65
# define NUMKEY_ENTER 76
# define NUMKEY_LOCK 71

//movepad

# define KEY_ARROW_UP 126
# define KEY_ARROW_DOWN 125
# define KEY_ARROW_LEFT 123
# define KEY_ARROW_RIGHT 124
# define KEY_INSERT 114
# define KEY_HOME 115
# define KEY_PG_UP 116
# define KEY_DEL 117
# define KEY_END 119
# define KEY_PG_DOWN 121

//special

# define KEY_F1 122
# define KEY_F2 120
# define KEY_F3 99
# define KEY_F4 118
# define KEY_F5 96
# define KEY_F6 97
# define KEY_F7 98
# define KEY_F8 100
# define KEY_F9 101
# define KEY_F10 109
# define KEY_F11 -1
# define KEY_F12 111
# define KEY_PRT_SC 105
# define KEY_SCR_LOCK -1
# define KEY_PAUSE -1
# define KEY_ESC 53
# define KEY_MENU 110
# define KEY_ENTER 36
# define KEY_BACKSPACE 51
# define KEY_TAB 48

//mouse

# define MOUSE_LMB
# define MOUSE_RMB
# define MOUSE_MMB
# define MOUSE_MB4
# define MOUSE_MB5
# define MOUSE_SCRL_UP
# define MOUSE_SCRL_DWN

#endif
