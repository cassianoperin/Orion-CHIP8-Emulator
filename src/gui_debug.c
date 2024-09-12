#include "gui_debug.h"
// #include "../lib/nuklear/style.c"

int win_debug(struct nk_context *ctx)
{
    /* window flags */
    static nk_flags window_flags = NK_WINDOW_TITLE|NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_MINIMIZABLE;
    nk_flags actual_window_flags;

    /* popups */
    static enum nk_style_header_align header_align = NK_HEADER_RIGHT;

    ctx->style.window.header.align = header_align;

    actual_window_flags = window_flags;
    // if (!(actual_window_flags & NK_WINDOW_TITLE))
    //     actual_window_flags &= ~(NK_WINDOW_MINIMIZABLE|NK_WINDOW_CLOSABLE);
    if (nk_begin(ctx, "Memory Viewer", nk_rect(854, 36, 426, 658), actual_window_flags))
    {

        // Memory selector combo box
        static int current_mem_debug = 0;
        static const char *memory_list[] = {"Display","RAM: 0x0000 -> 0x0199 (Interpreter)", "RAM: 0x0200 -> 0x1000 (Program)"};
        nk_layout_row_static(ctx, 25, 270, 1);
        current_mem_debug = nk_combo(ctx, memory_list, NK_LEN(memory_list), current_mem_debug, 25, nk_vec2(270,200));

        // Memory Group (Address label)
        nk_layout_row_static(ctx, (float)20, 404, 2);
        if (nk_group_begin(ctx, "MemLabel", NK_WINDOW_NO_SCROLLBAR)) {

            static const float ratio[] = {40, 340};
            nk_layout_row(ctx, NK_STATIC, 20, 2, ratio);

            strcpy(guiDebug_mem_addr, "");
            strcpy(guiDebug_emuinfo_msg, "00 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F");
            nk_label_colored(ctx, guiDebug_mem_addr, NK_TEXT_LEFT, nk_rgb(0,255,255));
            nk_label_colored(ctx, guiDebug_emuinfo_msg, NK_TEXT_LEFT, nk_rgb(0,255,255));
            nk_group_end(ctx);
        }

        // Memory Group (data)
        nk_layout_row_static(ctx, (float)550, 404, 2);
        if (nk_group_begin(ctx, "Memory", NK_WINDOW_BORDER)) {

            static const float ratio[] = {40, 340};
            nk_layout_row(ctx, NK_STATIC, 10, 2, ratio);

            switch( current_mem_debug )
            {
                char str[50];

                // Display Memory Viewer
                case 0: {

                    for ( int i = 0 ; i < display_EMULATOR_RES_X * display_EMULATOR_RES_Y ; i+=16 ) {
                        sprintf(str, "%04X:", i);
                        strcpy(guiDebug_mem_addr, str);

                        sprintf(str, "%02X %02X %02X %02X %02X %02X %02X %02X  %02X %02X %02X %02X %02X %02X %02X %02X",    \
                                    display_pixels[i+0],  display_pixels[i+1],  display_pixels[i+2],  display_pixels[i+3],  \
                                    display_pixels[i+4],  display_pixels[i+5],  display_pixels[i+6],  display_pixels[i+7],  \
                                    display_pixels[i+8],  display_pixels[i+9],  display_pixels[i+10], display_pixels[i+11], \
                                    display_pixels[i+12], display_pixels[i+13], display_pixels[i+14], display_pixels[i+15]
                        );
                        strcpy(guiDebug_emuinfo_msg, str);

                        nk_label_colored(ctx, guiDebug_mem_addr, NK_TEXT_LEFT, nk_rgb(0,255,255));
                        nk_label(ctx, guiDebug_emuinfo_msg, NK_TEXT_LEFT);
                    }

                    break;
                }

                // RAM Memory Viewer 0x0000 -> 0x0199 (Interpreter)
                case 1: {

                     for ( int i = 0 ; i < 0x200 ; i+=16 ) {
                        sprintf(str, "%04X:", i);
                        strcpy(guiDebug_mem_addr, str);

                        sprintf(str, "%02X %02X %02X %02X %02X %02X %02X %02X  %02X %02X %02X %02X %02X %02X %02X %02X",    \
                                                                    Memory[i+0],  Memory[i+1],  Memory[i+2],  Memory[i+3],  \
                                                                    Memory[i+4],  Memory[i+5],  Memory[i+6],  Memory[i+7],  \
                                                                    Memory[i+8],  Memory[i+9],  Memory[i+10], Memory[i+11], \
                                                                    Memory[i+12], Memory[i+13], Memory[i+14], Memory[i+15]
                        );
                        strcpy(guiDebug_emuinfo_msg, str);

                        nk_label_colored(ctx, guiDebug_mem_addr, NK_TEXT_LEFT, nk_rgb(0,255,255));
                        nk_label(ctx, guiDebug_emuinfo_msg, NK_TEXT_LEFT);
                    }

                    break;
                }

                // RAM Memory Viewer 0x0200 -> 0x1000 (Program)
                case 2: {

                    for ( int i = 0x200 ; i < sizeof(Memory) ; i+=16 ) {
                        sprintf(str, "%04X:", i);
                        strcpy(guiDebug_mem_addr, str);

                        sprintf(str, "%02X %02X %02X %02X %02X %02X %02X %02X  %02X %02X %02X %02X %02X %02X %02X %02X",    \
                                                                    Memory[i+0],  Memory[i+1],  Memory[i+2],  Memory[i+3],  \
                                                                    Memory[i+4],  Memory[i+5],  Memory[i+6],  Memory[i+7],  \
                                                                    Memory[i+8],  Memory[i+9],  Memory[i+10], Memory[i+11], \
                                                                    Memory[i+12], Memory[i+13], Memory[i+14], Memory[i+15]
                        );
                        strcpy(guiDebug_emuinfo_msg, str);

                        nk_label_colored(ctx, guiDebug_mem_addr, NK_TEXT_LEFT, nk_rgb(0,255,255));
                        nk_label(ctx, guiDebug_emuinfo_msg, NK_TEXT_LEFT);
                    }

                    break;
                }

            }

            nk_group_end(ctx);
        }





                // /* Text Widgets */
                // nk_layout_row_dynamic(ctx, 20, 1);
                // nk_label(ctx, "Label aligned left", NK_TEXT_LEFT);
                // nk_label(ctx, "Label aligned centered", NK_TEXT_CENTERED);
                // nk_label(ctx, "Label aligned right", NK_TEXT_RIGHT);
                // nk_label_colored(ctx, "Blue text", NK_TEXT_LEFT, nk_rgb(0,0,255));
                // nk_label_colored(ctx, "Yellow text", NK_TEXT_LEFT, nk_rgb(255,255,0));
                // nk_text(ctx, "Text without /0", 15, NK_TEXT_RIGHT);

                // nk_layout_row_static(ctx, 100, 200, 1);
                // nk_label_wrap(ctx, "This is a very long line to hopefully get this text to be wrapped into multiple lines to show line wrapping");
                // nk_layout_row_dynamic(ctx, 100, 1);
                // nk_label_wrap(ctx, "This is another long text to show dynamic window changes on multiline text");
            




    }
    nk_end(ctx);
    return !nk_window_is_closed(ctx, "Debug");
}
