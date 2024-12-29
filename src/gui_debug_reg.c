#include "gui_debug_reg.h"

int win_debug_reg(struct nk_context *ctx)
{
    /* window flags */
    static nk_flags window_flags = NK_WINDOW_TITLE|NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_NO_SCROLLBAR;
    nk_flags actual_window_flags;

    /* popups */
    static enum nk_style_header_align header_align = NK_HEADER_RIGHT;

    ctx->style.window.header.align = header_align;

    actual_window_flags = window_flags;
    if (nk_begin(ctx, "Registers and Flags", nk_rect(0, 360, 580, 334), actual_window_flags))
    {
        // Layouts
        static const float ratio_1column[] = {100};
        static const float ratio_2column[] = {70, 45};
        static const float ratio_2column_long[] = {100, 90};
        static const float ratio_3column[] = {70, 45, 45};
        static const float ratio_4column[] = {20, 50, 22, 50};
        static const float ratio_3column_maingroup[] = {180, 170, 210};
        static const float ratio_4column_Input[] = {38, 38, 38, 38};

        // Split the window in 3 horizontal groups
        nk_layout_row(ctx, NK_STATIC, 294, 3, ratio_3column_maingroup);

        // Opcode Group LEFT
        if (nk_group_begin(ctx, "RegGroupLeft", NK_WINDOW_BORDER|NK_WINDOW_NO_SCROLLBAR)) {

            // Line with 3 columns
            nk_layout_row(ctx, NK_STATIC, 14, 3, ratio_3column);

            // Register label
            nk_label_colored(ctx, "Registers:", NK_TEXT_LEFT, nk_rgb(255,255,255));
            nk_label_colored(ctx, "Hex", NK_TEXT_RIGHT, nk_rgb(120,120,120));
            nk_label_colored(ctx, "Dec", NK_TEXT_RIGHT, nk_rgb(120,120,120));

            // PC
            nk_label_colored(ctx, "PC:", NK_TEXT_LEFT, nk_rgb(0,255,255));
            sprintf(guiDebug_reg_emuinfo_msg, "#%04X", PC_last);
            nk_label(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT);
            sprintf(guiDebug_reg_emuinfo_msg, "%d", PC_last);
            nk_label(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT);

            // Line with 2 columns
            nk_layout_row(ctx, NK_STATIC, 14, 2, ratio_2column);

            // Opcode
            nk_label_colored(ctx, "Opcode:", NK_TEXT_LEFT, nk_rgb(120,120,120));
            sprintf(guiDebug_reg_emuinfo_msg, "#%04X", Opcode);
            nk_label_colored(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT, nk_rgb(120,120,120));

            // Line with 3 columns of 50
            nk_layout_row(ctx, NK_STATIC, 14, 3, ratio_3column);

            // I
            nk_label_colored(ctx, "I:", NK_TEXT_LEFT, nk_rgb(0,255,255));
            sprintf(guiDebug_reg_emuinfo_msg, "#%04X", I);
            nk_label(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT);
            sprintf(guiDebug_reg_emuinfo_msg, "%d", I);
            nk_label(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT);

            // SP
            nk_label_colored(ctx, "SP:", NK_TEXT_LEFT, nk_rgb(0,255,255));
            sprintf(guiDebug_reg_emuinfo_msg, "#%04x", SP);
            nk_label(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT);      
            sprintf(guiDebug_reg_emuinfo_msg, "%d", SP);
            nk_label(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT);

            // Delay Timer:
            nk_label_colored(ctx, "DT:", NK_TEXT_LEFT, nk_rgb(0,255,255));
            sprintf(guiDebug_reg_emuinfo_msg, "#%02X", DelayTimer);
            nk_label(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT);
            sprintf(guiDebug_reg_emuinfo_msg, "%d", DelayTimer);
            nk_label(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT);

            // Sound Timer:
            nk_label_colored(ctx, "ST:", NK_TEXT_LEFT, nk_rgb(0,255,255));
            sprintf(guiDebug_reg_emuinfo_msg, "#%02X", SoundTimer);
            nk_label(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT);
            sprintf(guiDebug_reg_emuinfo_msg, "%02d", SoundTimer);
            nk_label(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT);

            // Line with 1 columns
            nk_layout_row(ctx, NK_STATIC, 18, 1, ratio_1column);

            // Stack
            nk_label_colored(ctx, "Stack:", NK_TEXT_LEFT, nk_rgb(255,255,255));

            // Line with 4 columns
            nk_layout_row(ctx, NK_STATIC, 14, 4, ratio_4column);

            for ( int i = 0 ; i < ( (sizeof(Stack) / sizeof(Stack[0])) ) / 2; i++ ) {
                if ( i == SP ){
                    sprintf(guiDebug_reg_emuinfo_msg, " [%X]", i);
                    nk_label_colored(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT, nk_rgb(255,255,255));
                    sprintf(guiDebug_reg_emuinfo_msg, "#%04X", Stack[i]);
                    nk_label(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT);
                } else {
                    sprintf(guiDebug_reg_emuinfo_msg, " [%X]", i);
                    nk_label_colored(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT, nk_rgb(0,255,255));
                    sprintf(guiDebug_reg_emuinfo_msg, "#%04X", Stack[i]);
                    nk_label(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT);
                }

                if ( i+8 == SP ){
                    sprintf(guiDebug_reg_emuinfo_msg, " [%X]", i+8);
                    nk_label_colored(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_LEFT, nk_rgb(255,255,255));
                    sprintf(guiDebug_reg_emuinfo_msg, "#%04X", Stack[i+8]);
                    nk_label(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT);
                } else {
                    sprintf(guiDebug_reg_emuinfo_msg, " [%X]", i+8);
                    nk_label_colored(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_LEFT, nk_rgb(0,255,255));
                    sprintf(guiDebug_reg_emuinfo_msg, "#%04X", Stack[i+8]);
                    nk_label(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT);    
                } 
            }

        nk_group_end(ctx);
        }

        // Opcode Group CENTER
        if (nk_group_begin(ctx, "RegGroupCenter", NK_WINDOW_BORDER|NK_WINDOW_NO_SCROLLBAR)) {
         
            // //  Line with 1 columns
            // nk_layout_row(ctx, NK_STATIC, 12, 1, ratio_1column);

            // // Empty line
            // nk_label_colored(ctx, "", NK_TEXT_LEFT, nk_rgb(0,255,255));

            // Line with 1 columns
            nk_layout_row(ctx, NK_STATIC, 18, 1, ratio_1column);

            // Stack
            nk_label_colored(ctx, "V:", NK_TEXT_LEFT, nk_rgb(255,255,255));

            // Line with 4 columns
            nk_layout_row(ctx, NK_STATIC, 12, 4, ratio_4column);

            for ( int i = 0 ; i < ( (sizeof(V) / sizeof(V[0])) ) / 2; i++ ) {
                sprintf(guiDebug_reg_emuinfo_msg, "   [%X]", i);
                nk_label_colored(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT, nk_rgb(0,255,255));
                sprintf(guiDebug_reg_emuinfo_msg, "#%02X", V[i]);
                nk_label(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT);
   
                if ( i+8 == 15 ) {
                    sprintf(guiDebug_reg_emuinfo_msg, "  [%X] ", i+8);
                    nk_label_colored(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT, nk_rgb(255,255,255));
                    sprintf(guiDebug_reg_emuinfo_msg, "#%02X", V[i+8]);
                    nk_label_colored(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT, nk_rgb(245,255,255));

                    // nk_label(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT); 
                } else {
                    sprintf(guiDebug_reg_emuinfo_msg, "  [%X] ", i+8);
                    nk_label_colored(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT, nk_rgb(0,255,255));
                    sprintf(guiDebug_reg_emuinfo_msg, "#%02X", V[i+8]);
                    nk_label(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT); 
                }
           
            }

            //  Line with 1 columns
            nk_layout_row(ctx, NK_STATIC, 4, 1, ratio_1column);

            // Empty line
            nk_label_colored(ctx, "", NK_TEXT_LEFT, nk_rgb(0,255,255));

            // Horizontal Ruler
            nk_layout_row_dynamic(ctx, 1, 1);
            nk_rule_horizontal(ctx, nk_gray, nk_true);

           //  Line with 1 columns
            nk_layout_row(ctx, NK_STATIC, 4, 1, ratio_1column);

            // Empty line
            nk_label_colored(ctx, "", NK_TEXT_LEFT, nk_rgb(0,255,255));

            // Line with 1 columns
            nk_layout_row(ctx, NK_STATIC, 10, 1, ratio_1column);

            //  Inputs:
            nk_label_colored(ctx, "Inputs:", NK_TEXT_LEFT, nk_rgb(255,255,255));

            // Line with 4 columns
            nk_layout_row(ctx, NK_STATIC, 20, 4, ratio_4column_Input);

            if ( Key[1] ) 
                nk_label_colored(ctx, "1", NK_TEXT_CENTERED, nk_rgb(255,255,0));
            else
                nk_label_colored(ctx, "1", NK_TEXT_CENTERED, nk_rgb(120,120,120));

            if ( Key[2] ) 
                nk_label_colored(ctx, "2", NK_TEXT_CENTERED, nk_rgb(255,255,0));
            else
                nk_label_colored(ctx, "2", NK_TEXT_CENTERED, nk_rgb(120,120,120));

            if ( Key[3] ) 
                nk_label_colored(ctx, "3", NK_TEXT_CENTERED, nk_rgb(255,255,0));
            else               
                nk_label_colored(ctx, "3", NK_TEXT_CENTERED, nk_rgb(120,120,120));

            if ( Key[12] ) 
                nk_label_colored(ctx, "C", NK_TEXT_CENTERED, nk_rgb(255,255,0));
            else
                nk_label_colored(ctx, "C", NK_TEXT_CENTERED, nk_rgb(120,120,120));

            if ( Key[4] ) 
                nk_label_colored(ctx, "4", NK_TEXT_CENTERED, nk_rgb(255,255,0));
            else
                nk_label_colored(ctx, "4", NK_TEXT_CENTERED, nk_rgb(120,120,120));

            if ( Key[5] ) 
                nk_label_colored(ctx, "5", NK_TEXT_CENTERED, nk_rgb(255,255,0));
            else
                nk_label_colored(ctx, "5", NK_TEXT_CENTERED, nk_rgb(120,120,120));

            if ( Key[6] ) 
                nk_label_colored(ctx, "6", NK_TEXT_CENTERED, nk_rgb(255,255,0));
            else
                nk_label_colored(ctx, "6", NK_TEXT_CENTERED, nk_rgb(120,120,120));

            if ( Key[13] ) 
                nk_label_colored(ctx, "D", NK_TEXT_CENTERED, nk_rgb(255,255,0));
            else
                nk_label_colored(ctx, "D", NK_TEXT_CENTERED, nk_rgb(120,120,120));

            if ( Key[7] ) 
                nk_label_colored(ctx, "7", NK_TEXT_CENTERED, nk_rgb(255,255,0));
            else
                nk_label_colored(ctx, "7", NK_TEXT_CENTERED, nk_rgb(120,120,120));

            if ( Key[8] ) 
                nk_label_colored(ctx, "8", NK_TEXT_CENTERED, nk_rgb(255,255,0));
            else
                nk_label_colored(ctx, "8", NK_TEXT_CENTERED, nk_rgb(120,120,120));

            if ( Key[9] ) 
                nk_label_colored(ctx, "9", NK_TEXT_CENTERED, nk_rgb(255,255,0));
            else
                nk_label_colored(ctx, "9", NK_TEXT_CENTERED, nk_rgb(120,120,120));

            if ( Key[14] ) 
                nk_label_colored(ctx, "E", NK_TEXT_CENTERED, nk_rgb(255,255,0));
            else
                nk_label_colored(ctx, "E", NK_TEXT_CENTERED, nk_rgb(120,120,120));

            if ( Key[10] ) 
                nk_label_colored(ctx, "A", NK_TEXT_CENTERED, nk_rgb(255,255,0));
            else
                nk_label_colored(ctx, "A", NK_TEXT_CENTERED, nk_rgb(120,120,120));

            if ( Key[0] ) 
                nk_label_colored(ctx, "0", NK_TEXT_CENTERED, nk_rgb(255,255,0));
            else
                nk_label_colored(ctx, "0", NK_TEXT_CENTERED, nk_rgb(120,120,120));
            
            if ( Key[11] ) 
                nk_label_colored(ctx, "B", NK_TEXT_CENTERED, nk_rgb(255,255,0));
            else
                nk_label_colored(ctx, "B", NK_TEXT_CENTERED, nk_rgb(120,120,120));

            if ( Key[15] ) 
                nk_label_colored(ctx, "F", NK_TEXT_CENTERED, nk_rgb(255,255,0));
            else
                nk_label_colored(ctx, "F", NK_TEXT_CENTERED, nk_rgb(120,120,120));

        nk_group_end(ctx);
        }

        // Opcode Group Right
        if (nk_group_begin(ctx, "RegGroupRight", NK_WINDOW_BORDER|NK_WINDOW_NO_SCROLLBAR)) {
         
           // Line with 1 columns
            nk_layout_row(ctx, NK_STATIC, 15, 1, ratio_1column);

            //  Inputs:
            nk_label_colored(ctx, "Information:", NK_TEXT_LEFT, nk_rgb(255,255,255));

            // Line with 2 columns
            nk_layout_row(ctx, NK_STATIC, 15, 2, ratio_2column_long);

            // CPU Clock
            nk_label_colored(ctx, "CPU Clock:", NK_TEXT_LEFT, nk_rgb(0,255,255));
            sprintf(guiDebug_reg_emuinfo_msg, "%d hz", CPU_CLOCK);
            nk_label(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT);

            // CPU Cycle
            nk_label_colored(ctx, "CPU Cycle:", NK_TEXT_LEFT, nk_rgb(0,255,255));
            sprintf(guiDebug_reg_emuinfo_msg, "%d", cycle_cpu);
            nk_label(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT);

            // Emulator Cycles per second
            nk_label_colored(ctx, "Emu cycle p/s:", NK_TEXT_LEFT, nk_rgb(0,255,255));
            sprintf(guiDebug_reg_emuinfo_msg, "%d", counter_second_cycles);
            nk_label(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT);

            // Frame Counter
            nk_label_colored(ctx, "Frames per sec.:", NK_TEXT_LEFT, nk_rgb(0,255,255));
            sprintf(guiDebug_reg_emuinfo_msg, "%d", counter_second_frames);
            nk_label(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT);
            
            // Frequency
            nk_label_colored(ctx, "Video system:", NK_TEXT_LEFT, nk_rgb(0,255,255));
            if (video_system_freq == 60) {
                sprintf(guiDebug_reg_emuinfo_msg, "NTSC (60hz)");
            } else {
                sprintf(guiDebug_reg_emuinfo_msg, "PAL (50hz)");
            }
            nk_label(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT);

            // Second duration
            nk_label_colored(ctx, "Second dur.:", NK_TEXT_LEFT, nk_rgb(0,255,255));
            sprintf(guiDebug_reg_emuinfo_msg, "%llu ms", counter_second_ms_duration);
            nk_label(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT);

           //  Line with 1 columns
            nk_layout_row(ctx, NK_STATIC, 4, 1, ratio_1column);

            // Empty line
            nk_label_colored(ctx, "", NK_TEXT_LEFT, nk_rgb(0,255,255));

            // Horizontal Ruler
            nk_layout_row_dynamic(ctx, 1, 1);
            nk_rule_horizontal(ctx, nk_gray, nk_true);

           //  Line with 1 columns
            nk_layout_row(ctx, NK_STATIC, 4, 1, ratio_1column);

            // Empty line

           // Line with 1 columns
            nk_layout_row(ctx, NK_STATIC, 15, 1, ratio_1column);

            //  Inputs:
            nk_label_colored(ctx, "Flags:", NK_TEXT_LEFT, nk_rgb(255,255,255));

            //  Line with 1 columns
            nk_layout_row(ctx, NK_STATIC, 4, 1, ratio_1column);

            // Empty line
            nk_label_colored(ctx, "", NK_TEXT_LEFT, nk_rgb(0,255,255));

            // // Quirk VF Reset
            // nk_label_colored(ctx, "VF Reset:", NK_TEXT_LEFT, nk_rgb(0,255,255));
            // sprintf(guiDebug_reg_emuinfo_msg, "%d", quirk_VF_Reset_8xy1_8xy2_8xy3);
            // nk_label(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT);

            // // Quirk Memory
            // nk_label_colored(ctx, "Mem. Legacy:", NK_TEXT_LEFT, nk_rgb(0,255,255));
            // sprintf(guiDebug_reg_emuinfo_msg, "%d", quirk_Memory_legacy_Fx55_Fx65);
            // nk_label(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT);
            
            // // Quirk Draw Flag
            // nk_label_colored(ctx, "Display Wait:", NK_TEXT_LEFT, nk_rgb(0,255,255));
            // sprintf(guiDebug_reg_emuinfo_msg, "%d", quirk_display_wait);
            // nk_label(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT);

            // // Quirk Clipping
            // nk_label_colored(ctx, "Clipping:", NK_TEXT_LEFT, nk_rgb(0,255,255));
            // sprintf(guiDebug_reg_emuinfo_msg, "%d", quirk_Clipping_Dxyn);
            // nk_label(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT);

            // // Quirk Shifting
            // nk_label_colored(ctx, "Shifting:", NK_TEXT_LEFT, nk_rgb(0,255,255));
            // sprintf(guiDebug_reg_emuinfo_msg, "%d", quirk_Shifting_legacy_8xy6_8xyE);
            // nk_label(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT);

            // // Quirk Jump
            // nk_label_colored(ctx, "Jump:", NK_TEXT_LEFT, nk_rgb(0,255,255));
            // sprintf(guiDebug_reg_emuinfo_msg, "%d", quirk_Jump_with_offset_Bnnn);
            // nk_label(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT);

            // Line with 2 columns
            nk_layout_row(ctx, NK_STATIC, 15, 2, ratio_2column_long);

            // Draw Flag
            nk_label_colored(ctx, "Draw Flag:", NK_TEXT_LEFT, nk_rgb(0,255,255));
            sprintf(guiDebug_reg_emuinfo_msg, "%d", cpu_draw_flag);
            nk_label(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT);

            // CPU Pause
            nk_label_colored(ctx, "CPU Pause:", NK_TEXT_LEFT, nk_rgb(0,255,255));
            sprintf(guiDebug_reg_emuinfo_msg, "%d", cpu_pause);
            nk_label(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT);     

            // CPU Debug
            nk_label_colored(ctx, "CPU Debug:", NK_TEXT_LEFT, nk_rgb(0,255,255));
            sprintf(guiDebug_reg_emuinfo_msg, "%d", cpu_debug_mode);
            nk_label(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT);

            // Rom Hex Format
            nk_label_colored(ctx, "Rom Hex.:", NK_TEXT_LEFT, nk_rgb(0,255,255));
            sprintf(guiDebug_reg_emuinfo_msg, "%d", rom_format_hex);
            nk_label(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT);

            // Sound
            nk_label_colored(ctx, "Sound:", NK_TEXT_LEFT, nk_rgb(0,255,255));
            sprintf(guiDebug_reg_emuinfo_msg, "%d", sound_enabled);
            nk_label(ctx, guiDebug_reg_emuinfo_msg, NK_TEXT_RIGHT);

        
        nk_group_end(ctx);
        }  

    }

    nk_end(ctx);
    return !nk_window_is_closed(ctx, "Registers and Flags");
}
