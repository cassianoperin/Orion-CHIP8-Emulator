#include "gui_debug_opc.h"
// #include "../lib/nuklear/style.c"

int win_debug_opc(struct nk_context *ctx)
{
    /* window flags */
    static nk_flags window_flags = NK_WINDOW_TITLE|NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_NO_SCROLLBAR;
    nk_flags actual_window_flags;

    /* popups */
    static enum nk_style_header_align header_align = NK_HEADER_RIGHT;

    ctx->style.window.header.align = header_align;

    actual_window_flags = window_flags;
    if (nk_begin(ctx, "Disassembler", nk_rect(582, 36, 270, 322), actual_window_flags))
    {

        // Line with 1 columns
        static const float ratio_1column[] = {258};
        nk_layout_row(ctx, NK_STATIC, 130, 1, ratio_1column);

        // Opcode Group
        if (nk_group_begin(ctx, "OpcodesGrp", NK_WINDOW_BORDER|NK_WINDOW_NO_SCROLLBAR)) {

            static const float ratio[] = {40, 40, 140};
            nk_layout_row(ctx, NK_STATIC, 10, 3, ratio);

            char str[50];
            int opc_lines = 18;
            int opc_tmp = 0; 

            // Show previous opcodes
            for ( int i = opc_lines ; i > 0 ; i-=2 ) {
                sprintf(str, "%04X:", PC_last - i);
                strcpy(guiDebug_opc_addr_msg, str);
                sprintf(str, "%02X %02X", Memory[PC_last - i], Memory[ (PC_last - i) + 1]);
                strcpy(guiDebug_opc_data_msg, str);
                if ( PC_last - i < 0x200 ) {
                    // Print address
                    nk_label_colored(ctx, guiDebug_opc_addr_msg, NK_TEXT_LEFT, nk_rgb(104,104,104));
                    // Print data
                    nk_label_colored(ctx, guiDebug_opc_data_msg, NK_TEXT_LEFT, nk_rgb(104,104,104));
                    // Print description
                    nk_label_colored(ctx, "", NK_TEXT_LEFT, nk_rgb(104,104,104));
                } else {
                    // Print address
                    nk_label_colored(ctx, guiDebug_opc_addr_msg, NK_TEXT_LEFT, nk_rgb(0,255,255));
                    // Print data
                    nk_label_colored(ctx, guiDebug_opc_data_msg, NK_TEXT_LEFT, nk_rgb(176,176,176));
                    // Print description
                    opc_tmp = cpu_fetch_opcode(PC_last - i, false);
                    cpu_decode_opcode(opc_tmp);
                    nk_label_colored(ctx, guiDebug_opc_description_msg, NK_TEXT_LEFT, nk_rgb(176,176,176));
                }                
            }

        nk_group_end(ctx);
        }

        // Line with 1 columns
        nk_layout_row(ctx, NK_STATIC, 19, 1, ratio_1column);

        // Opcode Group Current
        if (nk_group_begin(ctx, "OpcodesGrpCurrent", NK_WINDOW_BORDER|NK_WINDOW_NO_SCROLLBAR)) {

            static const float ratio[] = {40, 40, 140};
            nk_layout_row(ctx, NK_STATIC, 10, 3, ratio);

            char str[50];
            int opc_tmp = 0; 

            // Show current opcode (in red)
            sprintf(str, "%04X:", PC_last);
            strcpy(guiDebug_opc_addr_msg, str);
            nk_label_colored(ctx, guiDebug_opc_addr_msg, NK_TEXT_LEFT, nk_rgb(0,153,255));

            sprintf(str, "%02X %02X", Memory[PC_last], Memory[PC_last+1]);
            strcpy(guiDebug_opc_data_msg, str);
            nk_label(ctx, guiDebug_opc_data_msg, NK_TEXT_LEFT);

            opc_tmp = cpu_fetch_opcode(PC_last, false);
            cpu_decode_opcode(opc_tmp);
            nk_label(ctx, guiDebug_opc_description_msg, NK_TEXT_LEFT); 

        nk_group_end(ctx);
        }

        // Line with 1 columns
        nk_layout_row(ctx, NK_STATIC, 130, 1, ratio_1column);

        // Opcode Group Next
        if (nk_group_begin(ctx, "OpcodesGrpNext", NK_WINDOW_BORDER|NK_WINDOW_NO_SCROLLBAR)) {

            if ( cpu_rom_loaded ) {
                static const float ratio[] = {40, 40, 140};
                nk_layout_row(ctx, NK_STATIC, 10, 3, ratio);

                char str[50];
                int opc_lines = 20;
                int opc_tmp = 0; 

                // Show next opcodes
                for ( int i = 2 ; i < opc_lines ; i+=2 ) {
                    sprintf(str, "%04X:", PC_last + i);
                    strcpy(guiDebug_opc_addr_msg, str);
                    sprintf(str, "%02X %02X", Memory[PC_last + i], Memory[ (PC_last + i) + 1]);
                    strcpy(guiDebug_opc_data_msg, str);

                    if ( PC_last + i > 0x1000 ) {
                        // Print address
                        nk_label_colored(ctx, guiDebug_opc_addr_msg, NK_TEXT_LEFT, nk_rgb(104,104,104));
                        // Print data
                        nk_label_colored(ctx, guiDebug_opc_data_msg, NK_TEXT_LEFT, nk_rgb(104,104,104));
                        // Print description
                        nk_label_colored(ctx, "", NK_TEXT_LEFT, nk_rgb(104,104,104));
                    } else {
                        // Print address
                        nk_label_colored(ctx, guiDebug_opc_addr_msg, NK_TEXT_LEFT, nk_rgb(0,255,255));
                        // Print data
                        nk_label_colored(ctx, guiDebug_opc_data_msg, NK_TEXT_LEFT, nk_rgb(176,176,176));
                        // Print description
                        opc_tmp = cpu_fetch_opcode(PC_last + i, false);
                        cpu_decode_opcode(opc_tmp);
                        nk_label_colored(ctx, guiDebug_opc_description_msg, NK_TEXT_LEFT, nk_rgb(176,176,176));
                    }
                }
            }      

        nk_group_end(ctx);
        }

        if ( cpu_debug_mode && cpu_rom_loaded ) {
            sprintf(gui_statusbar_msg, "Last instruction: ");
            strcat(gui_statusbar_msg, cpu_debug_message);
        }
       
    }
    nk_end(ctx);
    return !nk_window_is_closed(ctx, "Debug");
}
