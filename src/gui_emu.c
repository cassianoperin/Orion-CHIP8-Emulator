#include <stdio.h>
#include "gui_emu.h"

struct nk_canvas {
    struct nk_command_buffer *painter;
    struct nk_vec2 item_spacing;
    struct nk_vec2 panel_padding;
    struct nk_style_item window_background;
};

static nk_bool
canvas_begin(struct nk_context *ctx, struct nk_canvas *canvas, nk_flags flags,
    int x, int y, int width, int height, struct nk_color background_color)
{
    /* save style properties which will be overwritten */
    canvas->panel_padding = ctx->style.window.padding;
    canvas->item_spacing = ctx->style.window.spacing;
    canvas->window_background = ctx->style.window.fixed_background;

    /* use the complete window space and set background */
    ctx->style.window.spacing = nk_vec2(0,0);
    ctx->style.window.padding = nk_vec2(0,0);
    ctx->style.window.fixed_background = nk_style_item_color(background_color);

    /* create/update window and set position + size */
    if (!nk_begin(ctx, "Emulator", nk_rect(x, y, width, height), flags))
        return nk_false;

    /* allocate the complete window space for drawing */
    {
        struct nk_rect total_space;
        total_space = nk_window_get_content_region(ctx);
        nk_layout_row_dynamic(ctx, total_space.h, 1);
        nk_widget(&total_space, ctx);
        canvas->painter = nk_window_get_canvas(ctx);
    }

    return nk_true;
}

static void
canvas_end(struct nk_context *ctx, struct nk_canvas *canvas)
{
    nk_end(ctx);
    ctx->style.window.spacing = canvas->panel_padding;
    ctx->style.window.padding = canvas->item_spacing;
    ctx->style.window.fixed_background = canvas->window_background;
}

void win_emulator(struct nk_context *ctx)
{
        struct nk_canvas canvas;
        static nk_flags window_flags;
        unsigned int win_height, win_width;

        if ( cpu_debug_mode ) {
            window_flags = NK_WINDOW_TITLE|NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_NO_SCROLLBAR;
            win_height = (display_EMULATOR_RES_Y * (display_EMULATOR_RES_SCALE)) + 34;
            win_width  = display_EMULATOR_RES_X * (display_EMULATOR_RES_SCALE) + 4;
        } else {
            window_flags = NK_WINDOW_NO_SCROLLBAR;
            win_height = display_EMULATOR_RES_Y * display_EMULATOR_RES_SCALE;
            win_width  = display_EMULATOR_RES_X * display_EMULATOR_RES_SCALE;
        }
        
        if (canvas_begin(ctx, &canvas, window_flags, 0, 36, win_width , win_height , nk_rgb(bg_R,bg_G,bg_B))) {
            float x = canvas.painter->clip.x, y = canvas.painter->clip.y;

            int rect_size = display_EMULATOR_RES_SCALE;

            // // Screen calibration
            // nk_fill_rect(canvas.painter,   nk_rect(x + rect_size*0, y + 0, rect_size, rect_size), 0, nk_rgb(255,255,255));
            // nk_fill_rect(canvas.painter,   nk_rect(x + rect_size*1, y + 0, rect_size, rect_size), 0, nk_rgb(255,255,255));
            // nk_fill_rect(canvas.painter,   nk_rect(x + rect_size*2, y + 0, rect_size, rect_size), 0, nk_rgb(255,255,255));
            // nk_fill_rect(canvas.painter,   nk_rect(x + rect_size*3, y + 0, rect_size, rect_size), 0, nk_rgb(255,255,255));
            // nk_fill_rect(canvas.painter,   nk_rect(x + rect_size*4, y + 0, rect_size, rect_size), 0, nk_rgb(255,255,255));
            // nk_fill_rect(canvas.painter,   nk_rect(x + rect_size*5, y + 0, rect_size, rect_size), 0, nk_rgb(255,255,255));
            // nk_fill_rect(canvas.painter,   nk_rect(x + rect_size*6, y + 0, rect_size, rect_size), 0, nk_rgb(255,255,255));
            // printf("0: %f %f\n", x + rect_size*0, x + rect_size*0 + rect_size);
            // printf("1: %f %f\n", x + rect_size*1, x + rect_size*1 + rect_size);
            // printf("2: %f %f\n", x + rect_size*2, x + rect_size*2 + rect_size);
            // printf("3: %f %f\n", x + rect_size*3, x + rect_size*3 + rect_size);
            // printf("4: %f %f\n", x + rect_size*4, x + rect_size*4 + rect_size);
            // printf("5: %f %f\n", x + rect_size*5, x + rect_size*5 + rect_size);

            // // nk_stroke_rect(canvas.painter, nk_rect(x + rect_size*3, y + 0, rect_size, rect_size), 1, 1, nk_rgb(255, 0, 0));
            // nk_fill_rect(canvas.painter,   nk_rect(x + rect_size*63, y + 0, rect_size, rect_size), 0, nk_rgb(255, 0, 0));
            // nk_fill_rect(canvas.painter,   nk_rect(x + rect_size*0,  y + rect_size*31, rect_size, rect_size), 0, nk_rgb(255, 0, 0));
            // nk_fill_rect(canvas.painter,   nk_rect(x + rect_size*63, y + rect_size*31, rect_size, rect_size), 0, nk_rgb(255, 0, 0));

            // Fill canvas with pixel array
            int line, column, index = 0;

            // while ( index < 8192 )
            while ( index < (display_EMULATOR_RES_X * display_EMULATOR_RES_Y) )
            {
                // Lines
                for ( line = 0 ; line < display_EMULATOR_RES_Y ; line ++ ) {
                    // 00 ..  63
                    // 64 .. 127

                    // Columns
                    for ( column = 0 ; column < display_EMULATOR_RES_X ; column ++ ) {
                        if ( display_pixels[index+(int)column] == display_pixel_ON_color ) {
                            nk_fill_rect(canvas.painter, nk_rect(x + rect_size*(float)column, y + rect_size*(float)line, rect_size, rect_size), 0, nk_rgb(px_R, px_G, px_B));
                        }
                    }

                    // Increment the index
                    index += display_EMULATOR_RES_X;
                }
            }

        }
        canvas_end(ctx, &canvas);
        
}

