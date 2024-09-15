#include "gui_debug_opc.h"

int win_debug_opc(struct nk_context *ctx)
{
    /* window flags */
    static nk_flags window_flags = NK_WINDOW_TITLE|NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_CLOSABLE;
    nk_flags actual_window_flags;

    /* popups */
    static enum nk_style_header_align header_align = NK_HEADER_RIGHT;

    ctx->style.window.header.align = header_align;

    actual_window_flags = window_flags;
    if (nk_begin(ctx, "Opcode Viewer", nk_rect(650, 36, 200, 658), actual_window_flags))
    {

        // Line with 1 columns
        static const float ratio_1column[] = {150};
        nk_layout_row(ctx, NK_STATIC, 500, 1, ratio_1column);

        // Opcode Group LEFT
        if (nk_group_begin(ctx, "RegGroupLeft", NK_WINDOW_BORDER|NK_WINDOW_NO_SCROLLBAR)) {

                static nk_bool selected[4] = {nk_false, nk_false, nk_true, nk_false};
                nk_layout_row_static(ctx, 18, 100, 1);
                nk_selectable_label(ctx, "Selectable", NK_TEXT_LEFT, &selected[0]);
                nk_selectable_label(ctx, "Selectable", NK_TEXT_LEFT, &selected[1]);
                nk_label(ctx, "Not Selectable", NK_TEXT_LEFT);
                nk_selectable_label(ctx, "Selectable", NK_TEXT_LEFT, &selected[2]);
                nk_selectable_label(ctx, "Selectable", NK_TEXT_LEFT, &selected[3]);

            // PC

        nk_group_end(ctx);
        }


       
    }
    nk_end(ctx);
    return !nk_window_is_closed(ctx, "Debug");
}
