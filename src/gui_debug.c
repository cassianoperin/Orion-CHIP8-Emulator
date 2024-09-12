#include "gui_debug.h"
// #include "../lib/nuklear/style.c"

int win_debug(struct nk_context *ctx)
{
    /* window flags */
    static nk_bool show_menu = nk_true;
    static nk_flags window_flags = NK_WINDOW_TITLE|NK_WINDOW_BORDER|NK_WINDOW_SCALABLE|NK_WINDOW_MOVABLE|NK_WINDOW_MINIMIZABLE;
    nk_flags actual_window_flags;

    /* popups */
    static enum nk_style_header_align header_align = NK_HEADER_RIGHT;
    static nk_bool show_app_about = nk_false;

    ctx->style.window.header.align = header_align;

	static nk_bool disable_widgets = nk_false;

    actual_window_flags = window_flags;
    if (!(actual_window_flags & NK_WINDOW_TITLE))
        actual_window_flags &= ~(NK_WINDOW_MINIMIZABLE|NK_WINDOW_CLOSABLE);
    if (nk_begin(ctx, "Debug", nk_rect(650, 36, 400, 600), actual_window_flags))
    {

            if (nk_tree_push(ctx, NK_TREE_NODE, "Text", NK_MINIMIZED))
                {
                    /* Text Widgets */
                    nk_layout_row_dynamic(ctx, 20, 1);
                    nk_label(ctx, "Label aligned left", NK_TEXT_LEFT);
                    nk_label(ctx, "Label aligned centered", NK_TEXT_CENTERED);
                    nk_label(ctx, "Label aligned right", NK_TEXT_RIGHT);
                    nk_label_colored(ctx, "Blue text", NK_TEXT_LEFT, nk_rgb(0,0,255));
                    nk_label_colored(ctx, "Yellow text", NK_TEXT_LEFT, nk_rgb(255,255,0));
                    nk_text(ctx, "Text without /0", 15, NK_TEXT_RIGHT);

                    nk_layout_row_static(ctx, 100, 200, 1);
                    nk_label_wrap(ctx, "This is a very long line to hopefully get this text to be wrapped into multiple lines to show line wrapping");
                    nk_layout_row_dynamic(ctx, 100, 1);
                    nk_label_wrap(ctx, "This is another long text to show dynamic window changes on multiline text");
                    nk_tree_pop(ctx);
                }



            if (nk_tree_push(ctx, NK_TREE_NODE, "Group", NK_MINIMIZED))
            {
                static nk_bool group_titlebar = nk_false;
                static nk_bool group_border = nk_true;
                static nk_bool group_no_scrollbar = nk_false;
                static int group_width = 320;
                static int group_height = 200;

                nk_flags group_flags = 0;
                if (group_border) group_flags |= NK_WINDOW_BORDER;
                if (group_no_scrollbar) group_flags |= NK_WINDOW_NO_SCROLLBAR;
                if (group_titlebar) group_flags |= NK_WINDOW_TITLE;

                nk_layout_row_dynamic(ctx, 30, 3);
                nk_checkbox_label(ctx, "Titlebar", &group_titlebar);
                nk_checkbox_label(ctx, "Border", &group_border);
                nk_checkbox_label(ctx, "No Scrollbar", &group_no_scrollbar);

                nk_layout_row_begin(ctx, NK_STATIC, 22, 3);
                nk_layout_row_push(ctx, 50);
                nk_label(ctx, "size:", NK_TEXT_LEFT);
                nk_layout_row_push(ctx, 130);
                nk_property_int(ctx, "#Width:", 100, &group_width, 500, 10, 1);
                nk_layout_row_push(ctx, 130);
                nk_property_int(ctx, "#Height:", 100, &group_height, 500, 10, 1);
                nk_layout_row_end(ctx);

                nk_layout_row_static(ctx, (float)group_height, group_width, 2);
                if (nk_group_begin(ctx, "Group", group_flags)) {
                    int i = 0;
                    static nk_bool selected[16];
                    nk_layout_row_static(ctx, 18, 100, 1);
                    for (i = 0; i < 16; ++i)
                        nk_selectable_label(ctx, (selected[i]) ? "Selected": "Unselected", NK_TEXT_CENTERED, &selected[i]);
                    nk_group_end(ctx);
                }
                nk_tree_pop(ctx);
            }
    }
    nk_end(ctx);
    return !nk_window_is_closed(ctx, "Debug");
}
