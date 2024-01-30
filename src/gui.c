#include "gui.h"

int menu(struct nk_context *ctx)
{
    static nk_flags window_flags = NK_WINDOW_BORDER;
    nk_flags actual_window_flags;

    /* popups */
    static enum nk_style_header_align header_align = NK_HEADER_RIGHT;
    static int show_app_about = nk_false;
    static int show_app_quirk_help = nk_false;


    ctx->style.window.header.align = header_align;

    actual_window_flags = window_flags;
    if (!(actual_window_flags & NK_WINDOW_TITLE))
        actual_window_flags &= ~(NK_WINDOW_MINIMIZABLE|NK_WINDOW_CLOSABLE);
    if (nk_begin(ctx, "Overview", nk_rect(0, 0, display_SCREEN_WIDTH_X * display_SCALE, 35), actual_window_flags))
    {
        nk_menubar_begin(ctx);

        // ------------------------------------- Menu FILE -------------------------------------- //
        
        // Start Menu Row
        nk_layout_row_begin(ctx, NK_STATIC, 25, 5);
        
        nk_layout_row_push(ctx, 45);
        if (nk_menu_begin_label(ctx, "File", NK_TEXT_LEFT, nk_vec2(120, 200)))
        {
            nk_layout_row_dynamic(ctx, 25, 1);
            if (nk_menu_item_label(ctx, "Load ROM", NK_TEXT_LEFT)) {
                lib_gui_loadrom();
            }

            if (nk_menu_item_label(ctx, "Exit", NK_TEXT_LEFT)) {
                printf("Exiting (from GUI)\n");
                quit = true;
            }

            nk_menu_end(ctx);
        }


        // ------------------------------------- Menu VIEW -------------------------------------- //
        nk_layout_row_push(ctx, 45);
        if (nk_menu_begin_label(ctx, "View", NK_TEXT_LEFT, nk_vec2(190, 220)))
        {

            if (nk_tree_push(ctx, NK_TREE_NODE, "Theme", NK_MINIMIZED))
            {
                static int option;

                nk_layout_row_static(ctx, 20, 160, 1);
                option = nk_option_label(ctx, "1: Black and White",  option == 0) ? 0 : option;
                option = nk_option_label(ctx, "2: White and Black",  option == 1) ? 1 : option;
                option = nk_option_label(ctx, "3: Gray and Blue",    option == 2) ? 2 : option;
                option = nk_option_label(ctx, "4: Gray and Green",   option == 3) ? 3 : option;
                option = nk_option_label(ctx, "5: Black and Yellow", option == 4) ? 4 : option;
                option = nk_option_label(ctx, "6: Gray and Pink",    option == 5) ? 5 : option;

                switch( option )
                {
                    // Black and White
                    case 0:
                        display_pixel_ON_color_alt	= 0xFFFFFFFF;
                        display_pixel_OFF_color_alt	= 0xFF000000;

                        display_update_theme();
                        break;

                    // White and Black
                    case 1: {
                        // New colors
                        display_pixel_ON_color_alt	= 0xFF000000;
                        display_pixel_OFF_color_alt	= 0xFFFFFFFF;
                        // Update the colors after Pause if theme has changed
                        display_pixel_ON_color_tmp = display_pixel_ON_color_alt;
                        display_pixel_OFF_color_tmp = display_pixel_OFF_color_alt;
                        // Update Theme
                        display_update_theme();
                        break;
                    }

                    // Grey Wolfand and Crystal Blue
                    case 2: {
                        // New colors
                        display_pixel_ON_color_alt	= 0xFF5CB3FF;
                        display_pixel_OFF_color_alt	= 0xFF504A4B;
                        // Update the colors after Pause if theme has changed
                        display_pixel_ON_color_tmp = display_pixel_ON_color_alt;
                        display_pixel_OFF_color_tmp = display_pixel_OFF_color_alt;
                        // Update Theme
                        display_update_theme();
                        break;
                    }

                    // Cloudy Gray and Emerald Green
                    case 3: {
                        // New colors
                        display_pixel_ON_color_alt	= 0xFF50C878;
                        display_pixel_OFF_color_alt	= 0xFF6D6968;
                        // Update the colors after Pause if theme has changed
                        display_pixel_ON_color_tmp = display_pixel_ON_color_alt;
                        display_pixel_OFF_color_tmp = display_pixel_OFF_color_alt;
                        // Update Theme
                        display_update_theme();
                        break;
                    }

                    // Night Black and Pastel Yellow
                    case 4: {
                        // New colors
                        display_pixel_ON_color_alt	= 0xFFFAF884;
                        display_pixel_OFF_color_alt	= 0xFF0C090A;
                        // Update the colors after Pause if theme has changed
                        display_pixel_ON_color_tmp = display_pixel_ON_color_alt;
                        display_pixel_OFF_color_tmp = display_pixel_OFF_color_alt;
                        // Update Theme
                        display_update_theme();
                        break;
                    }

                    // Grey and LightCoral Pink
                    case 5: {
                        // New colors
                        display_pixel_ON_color_alt	= 0xFFF08080;
                        display_pixel_OFF_color_alt	= 0xFF1C1C1C;
                        // Update the colors after Pause if theme has changed
                        display_pixel_ON_color_tmp = display_pixel_ON_color_alt;
                        display_pixel_OFF_color_tmp = display_pixel_OFF_color_alt;
                        // Update Theme
                        display_update_theme();
                        break;
                    }

                }

                nk_tree_pop(ctx);
            }


            // Disable Pixel Scale menu before rom loading
            if ( display_fullscreen ) {
                nk_widget_disable_begin(ctx);
            }

            static const float ratio[] = {100, 80};
            int initial_scale_value = display_SCALE;
            nk_layout_row(ctx, NK_STATIC, 20, 2, ratio);
            nk_label(ctx, "Pixel Scale:", NK_TEXT_LEFT);
            nk_property_int(ctx, "", 10, (int *)&display_SCALE, 40, 5, 1);
            // Check if the scale was changed and update the window size
            if ( initial_scale_value != display_SCALE) {
                display_updateWindowSize(display_SCALE);
                SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
            }

            nk_widget_disable_end(ctx);

            if ( nk_checkbox_label(ctx, "Fullscreen", &display_fullscreen) ) {

                if ( display_fullscreen ) {
                    display_SCALE = 20; // To ensure that will fill entire screen
                    display_updateWindowSize(display_SCALE);
                    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
                    
                } else {
                    display_SCALE = 10; // To ensure that will fill entire screen
                    display_updateWindowSize(display_SCALE);
                    SDL_SetWindowFullscreen(window, 0);
                    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
                }

            }

            nk_menu_end(ctx);
        }

        // ----------------------------------- Menu EMULATION ----------------------------------- //
        nk_layout_row_push(ctx, 80);
        if (nk_menu_begin_label(ctx, "Emulation", NK_TEXT_LEFT, nk_vec2(220, 200)))
        {
            nk_layout_row_dynamic(ctx, 20, 1);
            if ( nk_checkbox_label(ctx, "HEX ROM mode", &rom_format_hex) ) {}

            if ( nk_checkbox_label(ctx, "Debug", &cpu_debug_mode) ) {}

            if ( nk_checkbox_label(ctx, "Sound", &sound_enabled) ) {}

            // Split
            nk_layout_row_dynamic(ctx, 1, 1);
            nk_rule_horizontal(ctx, nk_gray, nk_true);

            nk_layout_row_dynamic(ctx, 20, 1);
            if (nk_menu_item_label(ctx, "Reset", NK_TEXT_LEFT)) {
                cpu_reset();

                gui_show_menu = false;

                // Return the original Theme (before Pause)
                if ( cpu_rom_loaded ) {
                    display_pixel_ON_color_alt	= display_pixel_ON_color_tmp;
                    display_pixel_OFF_color_alt	= display_pixel_OFF_color_tmp;
                    display_update_theme();
                }
            }

            static const float ratio[] = {80, 120};
            nk_layout_row(ctx, NK_STATIC, 20, 2, ratio);
            nk_label(ctx, "CPU CLOCK:", NK_TEXT_LEFT);
            nk_property_int(ctx, "Clock:", 60, (int *)&CPU_CLOCK, 2000, 10, 1);
            
            nk_menu_end(ctx);
        }

        // ------------------------------------ Menu QUIRKS ------------------------------------- //
                                 
        nk_layout_row_push(ctx, 55);
        if (nk_menu_begin_label(ctx, "Quirks", NK_TEXT_LEFT, nk_vec2(320, 200)))
        {
            // Disable Quirks menu before rom loading
            if ( gui_menu_quirks_inactive ) {
                nk_widget_disable_begin(ctx);
            }

            /* CHIP-8 Quirks */
            if (nk_tree_push(ctx, NK_TREE_TAB, "CHIP-8", NK_MINIMIZED)) { 
                nk_layout_row_dynamic(ctx, 20, 2);
                nk_checkbox_label(ctx, "VF Reset", &quirk_VF_Reset_8xy1_8xy2_8xy3);
                nk_checkbox_label(ctx, "Memory legacy", &quirk_Memory_legacy_Fx55_Fx65);
                nk_checkbox_label(ctx, "Display Wait", &quirk_display_wait);
                nk_checkbox_label(ctx, "Clipping", &quirk_Clipping_Dxyn);
                nk_checkbox_label(ctx, "Shifting", &quirk_Shifting_legacy_8xy6_8xyE);
                nk_checkbox_label(ctx, "Jump with offset", &quirk_Jump_with_offset_Bnnn);
                nk_tree_pop(ctx);
            }

            nk_widget_disable_end(ctx);

            nk_menu_end(ctx);
        }

        // ------------------------------------- Menu HELP -------------------------------------- //
        
        nk_layout_row_push(ctx, 105);
        if (nk_menu_begin_label(ctx, "Help", NK_TEXT_LEFT, nk_vec2(200, 100)))
        {

            nk_layout_row_dynamic(ctx, 25, 1);
            if (nk_menu_item_label(ctx, "CHIP-8 Quirk Descriptions", NK_TEXT_LEFT)) {
                show_app_quirk_help = nk_true;
            }

            // Split
            nk_layout_row_dynamic(ctx, 1, 1);
            nk_rule_horizontal(ctx, nk_gray, nk_true);

            nk_layout_row_dynamic(ctx, 25, 1);
            if (nk_menu_item_label(ctx, "About", NK_TEXT_LEFT)) {
                show_app_about = nk_true;
            }
            
            nk_menu_end(ctx);
        }
        
        nk_menubar_end(ctx);
    }



    /* about popup */
    if (show_app_about)
    {
        // Center popup
        const int popup_size_x = 420;
        const int popup_size_y = 140;
        const int popup_size_header = 20;
        const int popup_initial_x_pos = display_SCREEN_WIDTH_X * display_SCALE  / 2 - popup_size_x / 2;
        const int popup_initial_y_pos = display_SCREEN_HEIGHT_Y * display_SCALE / 2 - popup_size_y / 2 - popup_size_header;

        struct nk_rect s = {popup_initial_x_pos, popup_initial_y_pos, popup_size_x, popup_size_y};
        if (nk_popup_begin(ctx, NK_POPUP_STATIC, "About", NK_WINDOW_BORDER | NK_WINDOW_CLOSABLE, s))
        {
            nk_layout_row_dynamic(ctx, 20, 1);
            nk_label(ctx, "Orion CHIP-8 Emulator", NK_TEXT_CENTERED);
            nk_label(ctx, "By Cassiano Perin", NK_TEXT_CENTERED);
            nk_label(ctx, "Orion CHIP8 is licensed under the public domain License.",  NK_TEXT_CENTERED);
            nk_popup_end(ctx);
        } else show_app_about = nk_false;
    }

    /* about popup */
    if (show_app_quirk_help)
    {
        
        // Center popup
        const int popup_size_x = 500;
        const int popup_size_y = 200;
        const int popup_size_header = 20;
        const int popup_initial_x_pos = display_SCREEN_WIDTH_X * display_SCALE  / 2 - popup_size_x / 2;
        const int popup_initial_y_pos = display_SCREEN_HEIGHT_Y * display_SCALE / 2 - popup_size_y / 2 - popup_size_header;

        struct nk_rect s = {popup_initial_x_pos, popup_initial_y_pos, popup_size_x, popup_size_y};
        if (nk_popup_begin(ctx, NK_POPUP_STATIC, "CHIP-8 Quirk Help", NK_WINDOW_BORDER | NK_WINDOW_CLOSABLE, s))
        {
            nk_layout_row_dynamic(ctx, 20, 1);
            nk_label_colored(ctx, "1. vF reset", NK_TEXT_LEFT, nk_blue);
            nk_layout_row_static(ctx, 40, popup_size_x - 20, 1);
            nk_label_wrap(ctx, "The AND, OR and XOR opcodes (8xy1, 8xy2 and 8xy3) reset the register flag to zero.");
            nk_layout_row_dynamic(ctx, 20, 1);
            nk_label_colored(ctx, "2. Memory", NK_TEXT_LEFT, nk_blue);
            nk_layout_row_static(ctx, 40, popup_size_x - 20, 1);
            nk_label_wrap(ctx, "The save and load opcodes (Fx55 and Fx65) increment the index register.");
            nk_layout_row_dynamic(ctx, 20, 1);
            nk_label_colored(ctx, "3. Display wait", NK_TEXT_LEFT, nk_blue);
            nk_layout_row_static(ctx, 40, popup_size_x - 20, 1);
            nk_label_wrap(ctx, "Drawing sprites to the display waits for the vertical blank, limiting to max 60 FPS.");
            nk_layout_row_dynamic(ctx, 20, 1);
            nk_label_colored(ctx, "4. Clipping", NK_TEXT_LEFT, nk_blue);
            nk_layout_row_static(ctx, 40, popup_size_x - 20, 1);
            nk_label_wrap(ctx, "Sprites drawn at the bottom edge of the screen get clipped instead of wrapping around to the top of the screen.");
            nk_layout_row_dynamic(ctx, 20, 1);
            nk_label_colored(ctx, "5. Shifting", NK_TEXT_LEFT, nk_blue);
            nk_layout_row_static(ctx, 40, popup_size_x - 20, 1);
            nk_label_wrap(ctx, "The shift opcodes (8xy6 and 8xyE) only operate on vX instead of storing the shifted version of vY in vX.");
            nk_layout_row_dynamic(ctx, 20, 1);
            nk_label_colored(ctx, "6. Jumping", NK_TEXT_LEFT, nk_blue);
            nk_layout_row_static(ctx, 40, popup_size_x - 20, 1);
            nk_label_wrap(ctx, "The \"jump to some address plus v0\" instruction (Bnnn) doesn't use v0, but vX instead where X is the highest nibble of nnn.");
            nk_popup_end(ctx);
        } else show_app_quirk_help = nk_false;
    }

    nk_end(ctx);
    return !nk_window_is_closed(ctx, "Overview");
}

int status_bar(struct nk_context *ctx)
{
    static nk_flags window_flags = NK_WINDOW_NO_SCROLLBAR;

    int windows_x_size = 0;
    int windows_y_size = 0;

    // Get the window size to add the status bar correctly on the botton
	SDL_GetWindowSize(window,&windows_x_size,&windows_y_size);

    if (nk_begin(ctx, "StatusBar", nk_rect(0, windows_y_size -25, windows_x_size, 25), window_flags))
    {
        nk_menubar_begin(ctx);
        
        nk_layout_row_dynamic(ctx, 15, 1);
        nk_label_colored(ctx, gui_statusbar_msg, NK_TEXT_CENTERED, nk_gray);
        // nk_label(ctx, gui_statusbar_msg, NK_TEXT_CENTERED);
        
        nk_menubar_end(ctx);        
    }

    nk_end(ctx);
    return !nk_window_is_closed(ctx, "StatusBar");
}


void gui_init(void)
{
    // Show Menu
    gui_show_menu = true;

    // Disable Quirks Menu until a rom is loaded
    gui_menu_quirks_inactive = true;

    // Initialize msg string
    strcpy(gui_statusbar_msg, "No ROM loaded.");

    ctx = nk_sdl_init(window, renderer);
    /* Load Fonts: if none of these are loaded a default font will be used  */
    /* Load Cursor: if you uncomment cursor loading please hide the cursor */
    {
        // struct nk_font_atlas *atlas;
        struct nk_font_config config = nk_font_config(0);
        struct nk_font *font;

        /* set up the font atlas and add desired font; note that font sizes are
        * multiplied by font_scale to produce better results at higher DPIs */
        nk_sdl_font_stash_begin(&atlas);
        font = nk_font_atlas_add_default(atlas, 13 * font_scale, &config);
        /*font = nk_font_atlas_add_from_file(atlas, "../../../extra_font/DroidSans.ttf", 14 * font_scale, &config);*/
        /*font = nk_font_atlas_add_from_file(atlas, "../../../extra_font/Roboto-Regular.ttf", 16 * font_scale, &config);*/
        /*font = nk_font_atlas_add_from_file(atlas, "../../../extra_font/kenvector_future_thin.ttf", 13 * font_scale, &config);*/
        /*font = nk_font_atlas_add_from_file(atlas, "../../../extra_font/ProggyClean.ttf", 12 * font_scale, &config);*/
        /*font = nk_font_atlas_add_from_file(atlas, "../../../extra_font/ProggyTiny.ttf", 10 * font_scale, &config);*/
        /*font = nk_font_atlas_add_from_file(atlas, "../../../extra_font/Cousine-Regular.ttf", 13 * font_scale, &config);*/
        nk_sdl_font_stash_end();

        /* this hack makes the font appear to be scaled down to the desired
        * size and is only necessary when font_scale > 1 */
        font->handle.height /= font_scale;
        /*nk_style_load_all_cursors(ctx, atlas->cursors);*/
        nk_style_set_font(ctx, &font->handle);
    }

    // Load the emulator Logo
    showLogo();
}
