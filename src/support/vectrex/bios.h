#ifndef __vectrex_bios_h__
#define __vectrex_bios_h__

#include <vectrex.h>

// Expose Vectrex music addreses
#define vx_music_1  (char*) 0xFD0D
#define vx_music_2  (char*) 0xFD1D
#define vx_music_3  (char*) 0xFD81
#define vx_music_4  (char*) 0xFDD3
#define vx_music_5  (char*) 0xFE38
#define vx_music_6  (char*) 0xFE76
#define vx_music_7  (char*) 0xFEC6
#define vx_music_8  (char*) 0xFEF8
#define vx_music_9  (char*) 0xFF26
#define vx_music_10 (char*) 0xFF44
#define vx_music_11 (char*) 0xFF62
#define vx_music_12 (char*) 0xFF7A
#define vx_music_13 (char*) 0xFF8F

#define JOY1_BTN1 0
#define JOY1_BTN2 1
#define JOY1_BTN3 2
#define JOY1_BTN4 3

#define JOY2_BTN1 4
#define JOY2_BTN2 5
#define JOY2_BTN3 6
#define JOY2_BTN4 7

#define JOY1_BTN1_MASK (1<<JOY1_BTN1)
#define JOY1_BTN2_MASK (1<<JOY1_BTN2)
#define JOY1_BTN3_MASK (1<<JOY1_BTN3)
#define JOY1_BTN4_MASK (1<<JOY1_BTN4)

#define JOY2_BTN1_MASK (1<<JOY2_BTN1)
#define JOY2_BTN2_MASK (1<<JOY2_BTN2)
#define JOY2_BTN3_MASK (1<<JOY2_BTN3)
#define JOY2_BTN4_MASK (1<<JOY2_BTN4)

#define JOY_UP    0
#define JOY_DOWN  1
#define JOY_LEFT  2
#define JOY_RIGHT 3

#define JOY_UP_MASK    (1<<JOY_UP) 
#define JOY_DOWN_MASK  (1<<JOY_DOWN)
#define JOY_LEFT_MASK  (1<<JOY_RIGHT)
#define JOY_RIGHT_MASK (1<<JOY_LEFT)

#define JOY_UP_MASK_ASM    1 
#define JOY_DOWN_MASK_ASM  2
#define JOY_LEFT_MASK_ASM  4
#define JOY_RIGHT_MASK_ASM 8

// Wrappers around the vectrex BIOS calls

// Read the joystick buttons.
// uint8_t buttons = read_buttons();
// if (buttons & JOY1_BTN1_MASK) {
//   do stuff when joystick one button one is pressed
//   ...
// }  
  uint8_t
read_buttons()
{
  uint8_t buttons;
  asm
  {
    JSR DP_to_D0
    JSR Read_Btns
    STA buttons    
  }
  return buttons;
}

// Read the joystick positions. This is an expensive call, as the Vectrex makes use of measring time over
// an RC network to do AD conversion for the joystick positions. For the moment, only digital positions are
// measured with this routine.
// You can use this routine as follows:
// uint8_t joystick = read_joystick(1);
// if ( joystick & JOY_UP_MASK) {
//   do joystick up stuff
//   ...
// } 
  uint8_t
read_joystick(uint8_t joystick)
{
  uint8_t result;
  asm
  {
    PSHS    X, DP
    JSR     DP_to_D0
    LDA     joystick                ; Which joystick?
    CMPA    #$02          
    BEQ     read_joystick_2

read_joystick_1:
    LDA     #1                      ; Joystick 1 set up
    STA     Vec_Joy_Mux_1_X
    LDA     #3
    STA     Vec_Joy_Mux_1_Y
    LDA     #0                      ; No Joystick 2 - saves a lot of cycles
    STA     Vec_Joy_Mux_2_X
    STA     Vec_Joy_Mux_2_Y

    JSR     Joy_Digital             ; Read joystick

    LDB     #$00                    ; Clear direction mask

    LDA     Vec_Joy_1_X             ; Check X direction
    BSR     read_joystick_check_x
    LDA     Vec_Joy_1_Y             ; Check Y direction
    BSR     read_joystick_check_y

    BRA     read_joystick_end

read_joystick_2:
    LDA     #0                      ; No Joystick 1 - saves a lot of cycles
    STA     Vec_Joy_Mux_1_X
    STA     Vec_Joy_Mux_1_Y
    LDA     #5                      ; Joystick 2 set up
    STA     Vec_Joy_Mux_2_X
    LDA     #7
    STA     Vec_Joy_Mux_2_Y

    JSR     Joy_Digital             ; Read joystick

    LDB     #$00                    ; Clear direction mask

    LDA     Vec_Joy_2_X             ; Check X direction
    BSR     read_joystick_check_x
    LDA     Vec_Joy_2_Y             ; Check Y direction
    BSR     read_joystick_check_y

    BRA     read_joystick_end

read_joystick_check_x:
    CMPA    #0
    BEQ     read_joystick_x_done
    BMI     read_joystick_left
    ORB     #JOY_RIGHT_MASK_ASM
    BRA     read_joystick_x_done
read_joystick_left:
    ORB     #JOY_LEFT_MASK_ASM
read_joystick_x_done:
    RTS

read_joystick_check_y:
    CMPA    #0    
    BEQ     read_joystick_y_done
    BMI     read_joystick_down
    ORB     #JOY_UP_MASK_ASM
    BRA     read_joystick_y_done
read_joystick_down:
    ORB     #JOY_DOWN_MASK_ASM
read_joystick_y_done:
    RTS
      
read_joystick_end:
    STB     result
    PULS    X, DP
  }
  return result;
}

// This call waits for timer two to timeout and restarts it, it then recalibrates the vector generators to
// coordinate (0, 0) it also calls the BIOS routine behind reset_beam in the process.
  void asm
wait_retrace()
{
  asm
  {
    JSR Wait_Recal
  }
}

// Set the beam intensity. The value 0x7f is often used and is rather bright.
  void 
intensity(uint8_t i)
{
  asm
  {
    LDA i
    JSR Intensity_a
  }
}

// Reset the beam to the middle of the screen.
// This is necassary from time to time as there is drift on the Vectrex integrators.
// Caling this makes coordinate (0,0) the middle of the screen.
  void
reset_beam()
{
  asm
  {
    JSR Reset0Ref
  }  
}


// Set the text width and height. Negative values are needed for the y coordinate. Otherwise text will be upside down.
  void
set_text_size(int8_t height, int8_t width)
{
  asm
  {
    LDA     width
    STA     Vec_Text_Width
    LDA     height
    STA     Vec_Text_Height
  }
}

// Print a string to the screen. The string must end with 0x80
  void
print_str(int8_t y, int8_t x, char* string)
{
  asm
  {
    JSR     DP_to_D0
    LDA     y 
    LDB     x 
    PSHS    U
    LDU     string
    JSR     Print_Str_d
    PULS    U
  }
}

// Print a C string (ends with 0).
  void
print_str_c(int8_t y, int8_t x, char* string)
{
  asm
  {
    JSR     DP_to_D0
    LDA     y 
    LDB     x 
    PSHS    U
    LDU     string
    
    ; -- Print_Str_d --
    JSR     >Moveto_d_7F
    JSR     Delay_1

    STU     Vec_Str_Ptr     ;Save string pointer
    LDX     #Char_Table-$20 ;Point to start of chargen bitmaps
    LDD     #$1883          ;$8x = enable RAMP?
    CLR     <VIA_port_a     ;Clear D/A output
    STA     <VIA_aux_cntl   ;Shift reg mode = 110, T1 PB7 enabled
    LDX     #Char_Table-$20 ;Point to start of chargen bitmaps
LF4A5:
    STB     <VIA_port_b     ;Update RAMP, set mux to channel 1
    DEC     <VIA_port_b     ;Enable mux
    LDD     #$8081
    NOP                     ;Wait a moment
    INC     <VIA_port_b     ;Disable mux
    STB     <VIA_port_b     ;Enable RAMP, set mux to channel 0
    STA     <VIA_port_b     ;Enable mux
    TST     $C800           ;I think this is a delay only
    INC     <VIA_port_b     ;Enable RAMP, disable mux
    LDA     Vec_Text_Width  ;Get text width
    STA     <VIA_port_a     ;Send it to the D/A
    LDD     #$0100
    LDU     Vec_Str_Ptr     ;Point to start of text string
    STA     <VIA_port_b     ;Disable RAMP, disable mux
    BRA     LF4CB

LF4C7:
    LDA     A,X             ;Get bitmap from chargen table
    STA     <VIA_shift_reg  ;Save in shift register
LF4CB:
    LDA     ,U+             ;Get next character
    ; BPL     LF4C7           ;Go back if not terminator
    BNE     LF4C7           ;Go back if not terminator
    LDA     #$81
    STA     <VIA_port_b     ;Enable RAMP, disable mux
    NEG     <VIA_port_a     ;Negate text width to D/A
    LDA     #$01
    STA     <VIA_port_b     ;Disable RAMP, disable mux
    CMPX    #Char_Table_End-$20 ;     Check for last row
    BEQ     LF50A           ;Branch if last row
    LEAX    $50,X           ;Point to next chargen row
    TFR     U,D             ;Get string length
    SUBD    Vec_Str_Ptr
    SUBB    #$02            ; -  2
    ASLB                    ; *  2
    BRN     LF4EB           ;Delay a moment
LF4EB:
    LDA     #$81
    NOP
    DECB
    BNE     LF4EB           ;Delay some more in a loop
    STA     <VIA_port_b     ;Enable RAMP, disable mux
    LDB     Vec_Text_Height ;Get text height
    STB     <VIA_port_a     ;Store text height in D/A
    DEC     <VIA_port_b     ;Enable mux
    LDD     #$8101
    NOP                     ;Wait a moment
    STA     <VIA_port_b     ;Enable RAMP, disable mux
    CLR     <VIA_port_a     ;Clear D/A
    STB     <VIA_port_b     ;Disable RAMP, disable mux
    STA     <VIA_port_b     ;Enable RAMP, disable mux
    LDB     #$03            ;$0x = disable RAMP?
    BRA     LF4A5           ;Go back for next scan line

LF50A:
    LDA     #$98
    STA     <VIA_aux_cntl   ;T1->PB7 enabled
    JSR     Reset0Ref       ;Reset the zero reference

    ; --
    PULS    U
  }
}

// Draw one dot at the relative y and x coordinate from the last beam position.
  void
dot(int8_t y, int8_t x)
{
  asm
  {
    JSR     DP_to_D0
    LDA     y
    LDB     x
    JSR     Dot_d
  }
}

// Draw a list of dots to the screen. Each dot is positioned relative to the previous one.
  void
dots(uint8_t nr_dots, int8_t* list)
{
  asm
  {
    JSR     DP_to_D0
    LDA     nr_dots
    STA     $C823
    LDX     list
    JSR     Dot_List
  }
}

// Set the scale. With this you can zoom in and out objects.
  void
set_scale(int8_t scale)
{
  asm
  {
    LDA     scale
    STA     <VIA_t1_cnt_lo 
  }
}

// Move the dot to a specific position.
  void
move(uint8_t y, uint8_t x)
{
  asm
  {
    JSR     DP_to_D0
    LDA     y
    LDB     x
    JSR     Moveto_d
  }
}

// Draw a line.
  void
line(int8_t y, int8_t x)
{
  asm
  {
    CLR     Vec_Misc_Count    ; To draw only 1 line, clear
    LDA     y
    LDB     x
    JSR     Draw_Line_d
  }
}

// Draw lines.
// The list of lines can live in ROM.
// You provide the list of lines as follows:
// int8_t list[n] = {
//    y1, x1,
//    y2, x2,
//    ...
//    xn, yn 
// };
// Make note that these are not absolute, but relative coordinates.
  void
lines(uint8_t nr_lines, int8_t* list)
{
  asm
  {
    JSR     DP_to_D0
    LDA     nr_lines
    DECA
    LDX     list
    JSR     Draw_VL_a
  }
}

// Draw patterned lines, where the pattern is provided as the first parameter, for the rest
// this function behaves the same as the lines fucntion.
  void
pattern_lines(uint8_t pattern, uint8_t nr_lines, int8_t *list)
{
  asm
  {
    JSR     DP_to_D0
    LDA     pattern
    STA     Vec_Pattern
    LDA     nr_lines
    DECA
    LDX     list
    JSR     Draw_Pat_VL_a 
  }
}

// Rotate a list of points. The points array can be in ROM, but the out_points need to be in RAM.
// The list of points is given as follows:
// int8_t points[n] = {
//   y1, x1,
//   y2, x2,
//   ...
//   yn, xn
// };
  void
rotate(int8_t angle, uint8_t nr_points, int8_t* points, int8_t* out_points)
{
  asm
  {
    PSHS    U,D
    LDA     angle
    LDB     nr_points
    DECB       
    LDX     points
    LDU     out_points
    JSR     Rot_VL_ab  
    PULS    U,D
  }
}  

// Set the music flag, which should be set to 1 to start playing music using the BIOS routine.
// The music flag has 3 states: 0, 1 and 0x80.
// State 0 means no music is playing. A 1 means we are about to start the music.
// And 0x80 means the music is currently playing.
  void
music_set_flag(uint8_t flag)
{
  asm
  {
    LDA     flag
    STA     Vec_Music_Flag
  }
}

// Get the music flag, which can have the states documented with the get method.
// If you want to repeat the music, you should check this flag and if it is 0 set to 1 again.
  uint8_t
music_get_flag()
{
  uint8_t flag;
  asm
  {
    LDA     Vec_Music_Flag
    STA     flag
  }  
  return flag;
}

// Point the BIOS play routine to a piece of music.
// Info about the format: http://www.playvectrex.com/designit/chrissalo/soundplaying.htm
  void
music_check(unsigned char* music)
{
  asm
  {
    PSHS    U
    JSR     DP_to_C8
    LDU     music
    JSR     Init_Music_chk
    PULS    U
  }
}

// Call this in the main loop to play the music.
  void
music_play()
{
  asm
  {
    JSR     Do_Sound
  }
}

// The Vectrex uses three bytes for the random seed.
  void
random_seed(uint8_t seed1, uint8_t seed2, uint8_t seed3)
{
  asm
  {
     LDA  seed1
     STA  Vec_Seed_Ptr+0   
     LDA  seed2
     STA  Vec_Seed_Ptr+1   
     LDA  seed3
     STA  Vec_Seed_Ptr+2   
  }
} 

// Produce a random value using the BIOS Random function.
  int8_t
random()
{
  int8_t rnd;
  asm
  {
    JSR Random
    STA rnd  
  }
  return rnd;
}

// What follows here are some low level BIOS fucntions that are not really necessary to call from your
// C program, but the are here for completeness.
  void asm
cold_start()
{
  asm
  {
    JSR   Cold_Start
  }
}

  void asm
warm_start()
{
  asm
  {
    JSR   Warm_Start
  }
}

  void asm
init_via()
{
  asm
  {
    JSR   Init_VIA
  }
}

  void asm
init_os_ram()
{
  asm
  {
    JSR   Init_OS_RAM
  }
}

  void asm
init_os()
{
  asm
  {
    JSR Init_OS
  }
}

  void 
set_refresh(uint16_t value)
{
  asm
  {
    JSR     DP_to_D0
    LDX     value
	  STX 	  0xc83e
    PSHS    D
	  JSR 	  Set_Refresh
    PULS    D
  }
}

#endif // __vectrex_bios_h__
