#include <stdio.h>
#include "gui_debug_sprite.h"

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
    if (!nk_begin(ctx, "Sprite", nk_rect(x, y, width, height), NK_WINDOW_MOVABLE | NK_WINDOW_NO_SCROLLBAR | NK_WINDOW_TITLE | flags))
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

void win_debug_sprite(struct nk_context *ctx)
{
        struct nk_canvas canvas;

        int x_pos, y_pos, x_length, y_height, rect_size;
        x_pos=582;
        y_pos=328;
        x_length=270;
        y_height=366;
        rect_size = x_length / 8;

            // if (nk_begin(ctx, "Registers and Flags", nk_rect(0, 328, 580, 366), actual_window_flags))


        if (canvas_begin(ctx, &canvas, NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_MINIMIZABLE,  \
                                                    x_pos, y_pos, x_length ,y_height , nk_rgb(0,0,0)))
        {
            float x = canvas.painter->clip.x, y = canvas.painter->clip.y;

            // Center the grade into canvas
            y+=17;

            // Draw the gray grade
            for (int column = 0 ; column < 8 ; column++){
                for (int line = 0 ; line < 8 ; line++){         
                        nk_stroke_rect(canvas.painter, nk_rect(x + rect_size*column, y + rect_size*line, rect_size, rect_size), 1, 1, nk_rgb(16, 16, 16));
                }
            }

            // Draw the sprite into the grade
            if ( (Opcode & 0xF000) == 0xD000 ) {

                char n = (Opcode & 0x000F);
                unsigned char byte, sprite, bit, bit_value= 0;

                for ( byte = 0 ; byte < n ; byte++ ){
                    sprite = Memory[I + byte];

                    // Always print 8 bits of the byte
                    for (bit = 0; bit < 8; bit++)
                    {
                        // Bit
                        bit_value = (sprite & 0x80) >> 7;	// MSB (Most Significant Bit), 1 will draw, 0 don't
                        
                        if ( bit_value == 1 ) {
                            nk_fill_rect(canvas.painter,   nk_rect(x + rect_size*bit, y + rect_size*byte, rect_size, rect_size), 0, nk_rgb(255, 255, 255));
                        } else {
                            nk_stroke_rect(canvas.painter, nk_rect(x + rect_size*bit, y + rect_size*byte, rect_size, rect_size), 1, 1, nk_rgb(144, 144, 144));
                        }

                        // Shift left to get the next bit on the MSB (Most Significant Bit) positon
                        sprite <<= 1;
                    }
                }
            }


        }
        canvas_end(ctx, &canvas);
        
}

