#include "gui_debug_opc.h"

int win_debug_opc(struct nk_context *ctx)
{
    /* window flags */
    static nk_flags window_flags = NK_WINDOW_TITLE|NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_MINIMIZABLE;
    nk_flags actual_window_flags;

    /* popups */
    static enum nk_style_header_align header_align = NK_HEADER_RIGHT;

    ctx->style.window.header.align = header_align;

    actual_window_flags = window_flags;
    if (nk_begin(ctx, "Opcode Viewer", nk_rect(582, 36, 270, 658), actual_window_flags))
    {

        // Line with 1 columns
        static const float ratio_1column[] = {248};
        nk_layout_row(ctx, NK_STATIC, 500, 1, ratio_1column);

        // nk_style_push_style_item(ctx, &ctx->style.window.background.r, nk_style_item_color(nk_rgb(255,0,0))); 

        // Opcode Group
        if (nk_group_begin(ctx, "OpcodesGrp", NK_WINDOW_BORDER)) {

            static const float ratio[] = {40, 40, 140};
            nk_layout_row(ctx, NK_STATIC, 10, 3, ratio);

            char str[50];
            int opc_lines = 20;
            int opc_tmp = 0; 

            // Show previous opcodes
            for ( int i = opc_lines ; i > 0 ; i-=2 ) {
                sprintf(str, "%04X:", PC - i);
                strcpy(guiDebug_opc_addr_msg, str);
                sprintf(str, "%02X %02X", Memory[PC - i], Memory[ (PC - i) + 1]);
                strcpy(guiDebug_opc_data_msg, str);
                if ( PC - i < 0x200 ) {
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
                    nk_label(ctx, guiDebug_opc_data_msg, NK_TEXT_LEFT);
                    // Print description
                    opc_tmp = cpu_get_opcode(PC - i);
                    cpu_decode_opcode(opc_tmp);
                    nk_label(ctx, guiDebug_opc_description_msg, NK_TEXT_LEFT);
                }                
            }

            // Show current opcode (in red)
            sprintf(str, "%04X:", PC);
            strcpy(guiDebug_opc_addr_msg, str);
            nk_label_colored(ctx, guiDebug_opc_addr_msg, NK_TEXT_LEFT, nk_rgb(255,0,0));

            sprintf(str, "%02X %02X", Memory[PC], Memory[PC+1]);
            strcpy(guiDebug_opc_data_msg, str);
            nk_label(ctx, guiDebug_opc_data_msg, NK_TEXT_LEFT);

            opc_tmp = cpu_get_opcode(PC);
            cpu_decode_opcode(opc_tmp);
            nk_label(ctx, guiDebug_opc_description_msg, NK_TEXT_LEFT);


             // Show next opcodes
            for ( int i = 0 ; i < opc_lines ; i+=2 ) {
                sprintf(str, "%04X:", PC + 2 + i);
                strcpy(guiDebug_opc_addr_msg, str);
                sprintf(str, "%02X %02X", Memory[PC + 2 + i], Memory[ (PC + 2 + i) + 1]);
                strcpy(guiDebug_opc_data_msg, str);

                if ( PC + 2 + i > 0x1000 ) {
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
                    nk_label(ctx, guiDebug_opc_data_msg, NK_TEXT_LEFT);
                    // Print description
                    opc_tmp = cpu_get_opcode(PC + 2 + i);
                    cpu_decode_opcode(opc_tmp);
                    nk_label(ctx, guiDebug_opc_description_msg, NK_TEXT_LEFT);
                }
            }        

            if ( cpu_debug_mode ) {
                strcpy(gui_statusbar_msg, cpu_debug_message);
            }

            

            // for ( int i = 0 ; i < romsize ; i+=2 ) {
            //     sprintf(str, "%04X:", 0x200 + i);
            //     strcpy(guiDebug_opc_addr_msg, str);

            //     sprintf(str, "%02X %02X", Memory[0x200+i], Memory[0x200+i+1]);
            //     strcpy(guiDebug_opc_data_msg, str);

            //     if (PC == 0x200 + i) {
            //         nk_label_colored(ctx, guiDebug_opc_addr_msg, NK_TEXT_LEFT, nk_rgb(255,0,0));
            //         nk_label(ctx, guiDebug_opc_data_msg, NK_TEXT_LEFT);


            //         float lines = romsize / 2;
            //         float line_size = 0;

            //         if ( lines < 33) {
            //             line_size = 0;
            //         } else if ( lines >=33 && lines < 41) {
            //              line_size = 2.19512195;
            //         } else if ( lines >=41 && lines < 53) {
            //              line_size = 4.86792453;
            //         } else if ( lines >=53 && lines < 88) {
            //              line_size = 8.5;
            //         } else if ( lines >=88 && lines < 280) {
            //              line_size = 12.27142857;
            //         } else if ( lines >=280 && lines < 455) {
            //              line_size = 12.93626374;
            //         } else if ( lines >=455 && lines < 896) {
            //              line_size = 13.45982143;
            //         } else if ( lines >=896 && lines < 1791) {
            //              line_size = 13.72975991;
            //         } else {
            //             line_size = 14;
            //         }

            //         // float test = 13.58913413 * (i/2);

            //         // printf("INT LINE: %d\n", (int)line_size);

            //         nk_group_set_scroll(ctx, "OpcodesGrp", 0, line_size * (i/2) );

            //     } else {
            //         nk_label_colored(ctx, guiDebug_opc_addr_msg, NK_TEXT_LEFT, nk_rgb(0,255,255));
            //         nk_label(ctx, guiDebug_opc_data_msg, NK_TEXT_LEFT);
            //     }

            // }

            // nk_uint valy;
            // nk_group_get_scroll(ctx, "OpcodesGrp", NULL, &valy);

            // printf("%d\n", valy);

            // nk_group_set_scroll(ctx, "Memory", 0, 744);




            //16008 / 1178
            //13,58913413


        nk_group_end(ctx);
        }

	// unsigned char  rom_ptr[romsize];
	// for (int i = 0; i < romsize; ++i) { 
	// 	rom_ptr[i] = Memory[PC+i];
	// }

       
    }
    nk_end(ctx);
    return !nk_window_is_closed(ctx, "Debug");
}
