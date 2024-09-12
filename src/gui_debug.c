#include "gui_debug.h"
// #include "../lib/nuklear/style.c"

int win_debug(struct nk_context *ctx)
{
    char str[1000];
    /* window flags */
    static nk_flags window_flags = NK_WINDOW_TITLE|NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_MINIMIZABLE;
    nk_flags actual_window_flags;

    /* popups */
    static enum nk_style_header_align header_align = NK_HEADER_RIGHT;

    ctx->style.window.header.align = header_align;

    actual_window_flags = window_flags;
    // if (!(actual_window_flags & NK_WINDOW_TITLE))
    //     actual_window_flags &= ~(NK_WINDOW_MINIMIZABLE|NK_WINDOW_CLOSABLE);
    if (nk_begin(ctx, "Debug", nk_rect(650, 36, 416, 600), actual_window_flags))
    {

                // Memory Viewer
                nk_layout_row_static(ctx, (float)320, 394, 2);
                if (nk_group_begin(ctx, "Group", NK_WINDOW_BORDER)) {

                    static const float ratio[] = {40, 330};
                    nk_layout_row(ctx, NK_STATIC, 10, 2, ratio);

                    for ( int i = 0 ; i < 2028 ; i+=16 ) {
                        sprintf(str, "%04X:", i);
                        strcpy(guiDebug_mem_addr, str);

                        sprintf(str, "00 00 00 00 00 00 00 66 66 66 66 66 66 66 77 77");
                        strcpy(guiDebug_emuinfo_msg, str);

                        nk_label_colored(ctx, guiDebug_mem_addr, NK_TEXT_LEFT, nk_rgb(0,255,255));
                        nk_label(ctx, guiDebug_emuinfo_msg, NK_TEXT_LEFT);
                    }

                    // for (int i = 0; i < 100; ++i) {
                    //     nk_label_colored(ctx, guiDebug_mem_addr, NK_TEXT_LEFT, nk_rgb(0,255,255));
                    //     nk_label(ctx, guiDebug_emuinfo_msg, NK_TEXT_LEFT);
                    // }

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
