#include "user_input.h"

void processUserInputs(){
    SDL_Event e;
    while( SDL_PollEvent( &e ) != 0 )
    {
        if(e.type == SDL_QUIT )
        {
            send("QUIT_APP");
        }
        if(e.type == SDL_KEYUP){

        }
        if(e.type ==  SDL_KEYDOWN)
        {
            if(SDL_GetModState() == KMOD_LSHIFT || SDL_GetModState() == KMOD_RSHIFT || SDL_GetModState() == KMOD_CAPS){
                switch(e.key.keysym.sym){
                    case SDLK_a: send("A_KEY_PRESSED"); break;
                    case SDLK_b: send("B_KEY_PRESSED"); break;
                    case SDLK_c: send("C_KEY_PRESSED"); break;
                    case SDLK_d: send("D_KEY_PRESSED"); break;
                    case SDLK_e: send("E_KEY_PRESSED"); break;
                    case SDLK_f: send("F_KEY_PRESSED"); break;
                    case SDLK_g: send("G_KEY_PRESSED"); break;
                    case SDLK_h: send("H_KEY_PRESSED"); break;
                    case SDLK_i: send("I_KEY_PRESSED"); break;
                    case SDLK_j: send("J_KEY_PRESSED"); break;
                    case SDLK_k: send("K_KEY_PRESSED"); break;
                    case SDLK_l: send("L_KEY_PRESSED"); break;
                    case SDLK_m: send("M_KEY_PRESSED"); break;
                    case SDLK_n: send("N_KEY_PRESSED"); break;
                    case SDLK_o: send("O_KEY_PRESSED"); break;
                    case SDLK_p: send("P_KEY_PRESSED"); break;
                    case SDLK_q: send("Q_KEY_PRESSED"); break;
                    case SDLK_r: send("R_KEY_PRESSED"); break;
                    case SDLK_s: send("S_KEY_PRESSED"); break;
                    case SDLK_t: send("T_KEY_PRESSED"); break;
                    case SDLK_u: send("U_KEY_PRESSED"); break;
                    case SDLK_v: send("V_KEY_PRESSED"); break;
                    case SDLK_w: send("W_KEY_PRESSED"); break;
                    case SDLK_x: send("X_KEY_PRESSED"); break;
                    case SDLK_y: send("Y_KEY_PRESSED"); break;
                    case SDLK_z: send("Z_KEY_PRESSED"); break;
                }
            }
            else{
                switch(e.key.keysym.sym){
                    case SDLK_a: send("a_KEY_PRESSED"); break;
                    case SDLK_b: send("b_KEY_PRESSED"); break;
                    case SDLK_c: send("c_KEY_PRESSED"); break;
                    case SDLK_d: send("d_KEY_PRESSED"); break;
                    case SDLK_e: send("e_KEY_PRESSED"); break;
                    case SDLK_f: send("f_KEY_PRESSED"); break;
                    case SDLK_g: send("g_KEY_PRESSED"); break;
                    case SDLK_h: send("h_KEY_PRESSED"); break;
                    case SDLK_i: send("i_KEY_PRESSED"); break;
                    case SDLK_j: send("j_KEY_PRESSED"); break;
                    case SDLK_k: send("k_KEY_PRESSED"); break;
                    case SDLK_l: send("l_KEY_PRESSED"); break;
                    case SDLK_m: send("m_KEY_PRESSED"); break;
                    case SDLK_n: send("n_KEY_PRESSED"); break;
                    case SDLK_o: send("o_KEY_PRESSED"); break;
                    case SDLK_p: send("p_KEY_PRESSED"); break;
                    case SDLK_q: send("q_KEY_PRESSED"); break;
                    case SDLK_r: send("r_KEY_PRESSED"); break;
                    case SDLK_s: send("s_KEY_PRESSED"); break;
                    case SDLK_t: send("t_KEY_PRESSED"); break;
                    case SDLK_u: send("u_KEY_PRESSED"); break;
                    case SDLK_v: send("v_KEY_PRESSED"); break;
                    case SDLK_w: send("w_KEY_PRESSED"); break;
                    case SDLK_x: send("x_KEY_PRESSED"); break;
                    case SDLK_y: send("y_KEY_PRESSED"); break;
                    case SDLK_z: send("z_KEY_PRESSED"); break;
                }
            }
            switch(e.key.keysym.sym){
                case SDLK_BACKQUOTE: send("TOGGLE_DEBUG_MODE"); break;
                
                case SDLK_RETURN: send("CONFIRM"); break;

                case SDLK_0: send("0_KEY_PRESSED"); break;
                case SDLK_1: send("1_KEY_PRESSED"); break;
                case SDLK_2: send("2_KEY_PRESSED"); break;
                case SDLK_3: send("3_KEY_PRESSED"); break;
                case SDLK_4: send("4_KEY_PRESSED"); break;
                case SDLK_5: send("5_KEY_PRESSED"); break;
                case SDLK_6: send("6_KEY_PRESSED"); break;
                case SDLK_7: send("7_KEY_PRESSED"); break;
                case SDLK_8: send("8_KEY_PRESSED"); break;
                case SDLK_9: send("9_KEY_PRESSED"); break;

                case SDLK_PERIOD: send("._KEY_PRESSED"); break;
                case SDLK_COMMA: send(",_KEY_PRESSED"); break;
                case SDLK_SLASH: send("/_KEY_PRESSED"); break;
                case SDLK_BACKSLASH: send("\\_KEY_PRESSED"); break;
                case SDLK_SPACE: send(" _KEY_PRESSED"); break;
                case SDLK_MINUS: send("__KEY_PRESSED"); break;
                case SDLK_SEMICOLON: send(";_KEY_PRESSED"); break;
            }
        }
    }

}
