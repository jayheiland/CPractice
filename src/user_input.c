#include "user_input.h"

void processUserInputs(){
    SDL_Event e;
    while( SDL_PollEvent( &e ) != 0 )
    {
        if( e.type == SDL_QUIT )
        {
            send("QUIT_APP");
        }
        if( e.type ==  SDL_KEYDOWN)
        {
            if(e.key.keysym.sym == SDLK_BACKQUOTE){
                send("TOGGLE_DEBUG_MODE");
            }
            if(e.key.keysym.sym == SDLK_w){
                send("UP_PRESSED");
                send("KEY_W_PRESSED");
            }
            if(e.key.keysym.sym == SDLK_s){
                send("DOWN_PRESSED");
                send("KEY_S_PRESSED");
            }
            if(e.key.keysym.sym == SDLK_a){
                send("LEFT_PRESSED");
                send("KEY_A_PRESSED");
            }
            if(e.key.keysym.sym == SDLK_d){
                send("RIGHT_PRESSED");
                send("KEY_D_PRESSED");
            }
            if(e.key.keysym.sym == SDLK_RETURN){
                send("CONFIRM");
            }

            if(e.key.keysym.sym == SDLK_b){ send("KEY_B_PRESSED"); }
            if(e.key.keysym.sym == SDLK_c){ send("KEY_C_PRESSED"); }
            if(e.key.keysym.sym == SDLK_e){ send("KEY_E_PRESSED"); }
            if(e.key.keysym.sym == SDLK_f){ send("KEY_F_PRESSED"); }
            if(e.key.keysym.sym == SDLK_g){ send("KEY_G_PRESSED"); }
            if(e.key.keysym.sym == SDLK_h){ send("KEY_H_PRESSED"); }
            if(e.key.keysym.sym == SDLK_i){ send("KEY_I_PRESSED"); }
            if(e.key.keysym.sym == SDLK_j){ send("KEY_J_PRESSED"); }
            if(e.key.keysym.sym == SDLK_k){ send("KEY_K_PRESSED"); }
            if(e.key.keysym.sym == SDLK_l){ send("KEY_L_PRESSED"); }
            if(e.key.keysym.sym == SDLK_m){ send("KEY_M_PRESSED"); }
            if(e.key.keysym.sym == SDLK_n){ send("KEY_N_PRESSED"); }
            if(e.key.keysym.sym == SDLK_o){ send("KEY_O_PRESSED"); }
            if(e.key.keysym.sym == SDLK_p){ send("KEY_P_PRESSED"); }
            if(e.key.keysym.sym == SDLK_q){ send("KEY_Q_PRESSED"); }
            if(e.key.keysym.sym == SDLK_r){ send("KEY_R_PRESSED"); }
            if(e.key.keysym.sym == SDLK_t){ send("KEY_T_PRESSED"); }
            if(e.key.keysym.sym == SDLK_u){ send("KEY_U_PRESSED"); }
            if(e.key.keysym.sym == SDLK_v){ send("KEY_V_PRESSED"); }
            if(e.key.keysym.sym == SDLK_x){ send("KEY_X_PRESSED"); }
            if(e.key.keysym.sym == SDLK_y){ send("KEY_Y_PRESSED"); }
            if(e.key.keysym.sym == SDLK_z){ send("KEY_Z_PRESSED"); }

            if(e.key.keysym.sym == SDLK_0){ send("KEY_0_PRESSED"); }
            if(e.key.keysym.sym == SDLK_1){ send("KEY_1_PRESSED"); }
            if(e.key.keysym.sym == SDLK_2){ send("KEY_2_PRESSED"); }
            if(e.key.keysym.sym == SDLK_3){ send("KEY_3_PRESSED"); }
            if(e.key.keysym.sym == SDLK_4){ send("KEY_4_PRESSED"); }
            if(e.key.keysym.sym == SDLK_5){ send("KEY_5_PRESSED"); }
            if(e.key.keysym.sym == SDLK_6){ send("KEY_6_PRESSED"); }
            if(e.key.keysym.sym == SDLK_7){ send("KEY_7_PRESSED"); }
            if(e.key.keysym.sym == SDLK_8){ send("KEY_8_PRESSED"); }
            if(e.key.keysym.sym == SDLK_9){ send("KEY_9_PRESSED"); }

            if(e.key.keysym.sym == SDLK_MINUS){ send("KEY_UNDERSCORE_PRESSED"); }
            if(e.key.keysym.sym == SDLK_SEMICOLON){ send("KEY_SEMICOLON_PRESSED"); }
        }
    }
}