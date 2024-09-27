#include "gui.h"
#include "../lib/nuklear/style.c"

int menu(struct nk_context *ctx)
{
    static nk_flags window_flags = NK_WINDOW_BORDER;
    nk_flags actual_window_flags;

    /* popups */
    static enum nk_style_header_align header_align = NK_HEADER_RIGHT;
    static int show_app_about = nk_false;
    static int show_app_quirk_help = nk_false;

    ctx->style.window.header.align = header_align;

    int windows_x_size = 0;
    int windows_y_size = 0;

    // Get the window size to add the status bar correctly on the botton
	SDL_GetWindowSize(window,&windows_x_size,&windows_y_size);

    actual_window_flags = window_flags;
    if (!(actual_window_flags & NK_WINDOW_TITLE))
        actual_window_flags &= ~(NK_WINDOW_MINIMIZABLE|NK_WINDOW_CLOSABLE);
    if (nk_begin(ctx, "MainMenu", nk_rect(0, 0, windows_x_size, 35), actual_window_flags))
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

            if (nk_menu_item_label(ctx, "Close ROM", NK_TEXT_LEFT)) {
                cpu_initialize();

                // Update StatusBar message
		        strcpy(gui_statusbar_msg, "No ROM loaded");
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
                static int option = 6;

                //THEME_BLACK, THEME_WHITE, THEME_RED, THEME_BLUE, THEME_DARK, THEME_DRACULA
                nk_layout_row_static(ctx, 20, 160, 1);
                option = nk_option_label(ctx, "1: Black",   option == 0) ? 0 : option;
                option = nk_option_label(ctx, "2: White",   option == 1) ? 1 : option;
                // option = nk_option_label(ctx, "3: Red",     option == 2) ? 2 : option;
                // option = nk_option_label(ctx, "4: Blue",    option == 3) ? 3 : option;
                // option = nk_option_label(ctx, "5: Dark",    option == 4) ? 4 : option;
                option = nk_option_label(ctx, "3: Dracula", option == 5) ? 5 : option;

                switch( option )
                {
                    // Black
                    case 0:
                        set_style(ctx, THEME_BLACK);
                        break;

                    // White
                    case 1: {
                       	set_style(ctx, THEME_WHITE);
                        break;
                    }

                    // Red
                    case 2:
                        set_style(ctx, THEME_RED);
                        break;

                    // Blue
                    case 3: {
                       	set_style(ctx, THEME_BLUE);
                        break;
                    }
                    
                    // Dark
                    case 4:
                        set_style(ctx, THEME_DARK);
                        break;

                    // Dracula
                    case 5: {
                       	set_style(ctx, THEME_DRACULA);
                        break;
                    }
                    

                }

                nk_tree_pop(ctx);
            }

            // Update the main window resolution
            if (nk_tree_push(ctx, NK_TREE_NODE, "Resolution", NK_MINIMIZED))
            {
                static int option;

                nk_layout_row_static(ctx, 20, 180, 1);
                option = nk_option_label(ctx, "1:  720p (1280 x  720)",  option == 0) ? 0 : option;
                option = nk_option_label(ctx, "2: 1080p (1920 x 1080)",  option == 1) ? 1 : option;
                option = nk_option_label(ctx, "3: 1440p (2560 x 1440)",  option == 2) ? 2 : option;
                option = nk_option_label(ctx, "4: 2160p (3840 x 2160)",  option == 3) ? 3 : option;

                switch( option )
                {
                    // 720p (1280 x  720)
                    case 0:
                    	display_WINDOW_WIDTH_X		= 1280;
	                    display_WINDOW_HEIGHT_Y 	=  720;
                        SDL_SetWindowSize (window, display_WINDOW_WIDTH_X, display_WINDOW_HEIGHT_Y);
                        SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

                        break;

                    // 1080p (1920 x 1080)
                    case 1: {
                    	display_WINDOW_WIDTH_X		= 1920;
	                    display_WINDOW_HEIGHT_Y 	= 1080;
                        SDL_SetWindowSize (window, display_WINDOW_WIDTH_X, display_WINDOW_HEIGHT_Y);
                        SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

                        break;
                    }

                    // 1440p (2560 x 1440)
                    case 2: {
                        display_WINDOW_WIDTH_X		= 2560;
                        display_WINDOW_HEIGHT_Y 	= 1440;
                        SDL_SetWindowSize (window, display_WINDOW_WIDTH_X, display_WINDOW_HEIGHT_Y);
                        SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

                        break;
                    }

                    // 2160p (3840 x 2160)
                    case 3: {
                        display_WINDOW_WIDTH_X		= 3840;
                        display_WINDOW_HEIGHT_Y 	= 2160;
                        SDL_SetWindowSize (window, display_WINDOW_WIDTH_X, display_WINDOW_HEIGHT_Y);
                        SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

                        break;
                    }

                }

                nk_tree_pop(ctx);
            }


            // Disable Pixel Scale menu before rom loading
            if ( display_fullscreen ) {
                nk_widget_disable_begin(ctx);
            }


            nk_widget_disable_end(ctx);

            if ( nk_checkbox_label(ctx, "Fullscreen", &display_fullscreen) ) {

                if ( display_fullscreen ) {
                    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);       
                    display_EMULATOR_RES_SCALE = 20; // To ensure that will fill entire screen
                    display_updateWindowSize(display_EMULATOR_RES_SCALE);
                } else {
                    SDL_SetWindowFullscreen(window, 0);
                    display_EMULATOR_RES_SCALE = 10;
                    display_updateWindowSize(display_EMULATOR_RES_SCALE);
                    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
                }

            }

            nk_menu_end(ctx);
        }

        // ----------------------------------- Menu EMULATION ----------------------------------- //
        nk_layout_row_push(ctx, 80);
        if (nk_menu_begin_label(ctx, "Emulation", NK_TEXT_LEFT, nk_vec2(220, 200)))
        {

            if (nk_tree_push(ctx, NK_TREE_NODE, "Emulator Theme", NK_MINIMIZED))
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
                        // display_pixel_ON_color_alt	= 0xFFFFFFFF;
                        // display_pixel_OFF_color_alt	= 0xFF000000;

                        // display_update_theme();
                        break;

                    // White and Black
                    case 1: {
                        // // New colors
                        // display_pixel_ON_color_alt	= 0xFF000000;
                        // display_pixel_OFF_color_alt	= 0xFFFFFFFF;
                        // // Update the colors after Pause if theme has changed
                        // display_pixel_ON_color_tmp = display_pixel_ON_color_alt;
                        // display_pixel_OFF_color_tmp = display_pixel_OFF_color_alt;
                        // // Update Theme
                        // display_update_theme();
                        break;
                    }

                    // Grey Wolfand and Crystal Blue
                    case 2: {
                        // // New colors
                        // display_pixel_ON_color_alt	= 0xFF5CB3FF;
                        // display_pixel_OFF_color_alt	= 0xFF504A4B;
                        // // Update the colors after Pause if theme has changed
                        // display_pixel_ON_color_tmp = display_pixel_ON_color_alt;
                        // display_pixel_OFF_color_tmp = display_pixel_OFF_color_alt;
                        // // Update Theme
                        // display_update_theme();
                        break;
                    }

                    // Cloudy Gray and Emerald Green
                    case 3: {
                        // // New colors
                        // display_pixel_ON_color_alt	= 0xFF50C878;
                        // display_pixel_OFF_color_alt	= 0xFF6D6968;
                        // // Update the colors after Pause if theme has changed
                        // display_pixel_ON_color_tmp = display_pixel_ON_color_alt;
                        // display_pixel_OFF_color_tmp = display_pixel_OFF_color_alt;
                        // // Update Theme
                        // display_update_theme();
                        break;
                    }

                    // Night Black and Pastel Yellow
                    case 4: {
                        // // New colors
                        // display_pixel_ON_color_alt	= 0xFFFAF884;
                        // display_pixel_OFF_color_alt	= 0xFF0C090A;
                        // // Update the colors after Pause if theme has changed
                        // display_pixel_ON_color_tmp = display_pixel_ON_color_alt;
                        // display_pixel_OFF_color_tmp = display_pixel_OFF_color_alt;
                        // // Update Theme
                        // display_update_theme();
                        break;
                    }

                    // Grey and LightCoral Pink
                    case 5: {
                        // // New colors
                        // display_pixel_ON_color_alt	= 0xFFF08080;
                        // display_pixel_OFF_color_alt	= 0xFF1C1C1C;
                        // // Update the colors after Pause if theme has changed
                        // display_pixel_ON_color_tmp = display_pixel_ON_color_alt;
                        // display_pixel_OFF_color_tmp = display_pixel_OFF_color_alt;
                        // // Update Theme
                        // display_update_theme();
                        break;
                    }

                }

                nk_tree_pop(ctx);
            }

            if ( nk_checkbox_label(ctx, "HEX ROM mode", &rom_format_hex) ) {}

            if ( nk_checkbox_label(ctx, "Debug", &cpu_debug_mode) ) {}

            if ( nk_checkbox_label(ctx, "Pause", &cpu_pause) ) {}

            if ( nk_checkbox_label(ctx, "Sound", &sound_enabled) ) {}

            // --- Split Menu --- //
            nk_layout_row_dynamic(ctx, 1, 1);
            nk_rule_horizontal(ctx, nk_gray, nk_true);

            // Emulator Scale
            int initial_scale_value = display_EMULATOR_RES_SCALE;
            static const float ratio[] = {80, 120};
            nk_layout_row(ctx, NK_STATIC, 20, 2, ratio);
            nk_label(ctx, "Pixel Scale:", NK_TEXT_LEFT);
            nk_property_int(ctx, "", 10, (int *)&display_EMULATOR_RES_SCALE, 30, 5, 1);
            // Check if the scale was changed and update the window size
            if ( initial_scale_value != display_EMULATOR_RES_SCALE) {
                // Resize Emulator Window
                nk_window_set_bounds(ctx, "Emulator", nk_rect(0, 36, (display_EMULATOR_RES_X * display_EMULATOR_RES_SCALE) + 4, (display_EMULATOR_RES_Y * display_EMULATOR_RES_SCALE) + 34 ) );
            }

            // Clock
            nk_layout_row(ctx, NK_STATIC, 20, 2, ratio);
            nk_label(ctx, "CPU CLOCK:", NK_TEXT_LEFT);
            nk_property_int(ctx, "Clock:", 60, (int *)&CPU_CLOCK, 2000, 10, 1);
            
            // --- Split Menu --- //
            nk_layout_row_dynamic(ctx, 1, 1);
            nk_rule_horizontal(ctx, nk_gray, nk_true);

            // Reset
            nk_layout_row_dynamic(ctx, 20, 1);
            if (nk_menu_item_label(ctx, "Reset", NK_TEXT_LEFT)) {
                if ( cpu_rom_loaded ) {
                    cpu_reset();
                }
            }


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
                if (nk_checkbox_label(ctx, "Display Wait", &quirk_display_wait)){


                    if ( quirk_display_wait ) {
                        SDL_RenderSetVSync(renderer, 1);
                    } else {
                        SDL_RenderSetVSync(renderer, 0);
                    }

                };
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
        const int popup_initial_x_pos = display_EMULATOR_RES_X * display_EMULATOR_RES_SCALE / 2 - popup_size_x / 2;
        const int popup_initial_y_pos = display_EMULATOR_RES_Y * display_EMULATOR_RES_SCALE / 2 - popup_size_y / 2 - popup_size_header;

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
        const int popup_initial_x_pos = display_EMULATOR_RES_X * display_EMULATOR_RES_SCALE  / 2 - popup_size_x / 2;
        const int popup_initial_y_pos = display_EMULATOR_RES_Y * display_EMULATOR_RES_SCALE / 2 - popup_size_y / 2 - popup_size_header;

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
    // Variables
    gui_pixel_logo_ON_color  = 0xFFFFFFFF; // White
	gui_pixel_logo_OFF_color = 0xFF00FFAA; // Green

    // Disable Quirks Menu until a rom is loaded
    gui_menu_quirks_inactive = true;

    // Initialize msg string
    strcpy(gui_statusbar_msg, "No ROM loaded");

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

    // Initialization - Clean logo pixels array
	for ( int i = 0 ; i < (int)( sizeof(gui_pixels_logo) / sizeof(gui_pixels_logo[0])) ; i++ ) {
			gui_pixels_logo[i] = gui_pixel_logo_OFF_color;
	}

    // Load the emulator Logo
    showLogo();
}
