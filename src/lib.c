#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include "lib.h"
//Native File Dialog Extended 
#include <nfd.h>


// Ticker - Use with actions that should be executed each second = 1hz
bool ticker_second(long lastTime, long currentTime)
{
	//Initialization flag
	bool success = false;

	// Check if it passed one second
	if (currentTime > lastTime + 1000000) {
		success = true;
	}
	
	return success;
}


// Ticker - Use with actions that should be executed 60 times per second = 60hz
bool ticker_fps(long lastTime, long currentTime)
{
	//Initialization flag
	bool success = false;

	// Check if it passed one second / FPS
	if (currentTime > lastTime + (1000000 / display_FPS)) {
		success = true;
	}

	return success;
}


// Ticker - Use with actions that should be executed 500 times per second = 500hz
bool ticker_cpu(long lastTime, long currentTime)
{
	//Initialization flag
	bool success = false;

	// Check if it passed one second
	if (currentTime > lastTime + (1000000 / CPU_CLOCK)) {
		success = true;
	}
	
	return success;
}


// Load rom into memory
void load_rom(char *filename, unsigned char *mem, unsigned int mem_size)
{
	int PC = 0x200;

	if ( rom_format_hex == false ) {					// Rom in binary format
		FILE *rom = fopen(filename, "rb");
		if (!rom) {
			fprintf(stderr, "Unable to open file '%s'!\n", filename);
			exit(1);
		}
		fread(&mem[PC], 1, mem_size - PC, rom);
		fclose(rom);

		// Tell CPU to start running the interpreter
		cpu_rom_loaded = true;


	} else { // Rom in hexadecimal format

		const int buffer_size = (sizeof(char) * 8192); // 8192

		// Hex roms will have the double of size in bytes of binary format
		char *hexBuffer = malloc( buffer_size ); // Pointer to a 8192 bytes array
		// Array to process and filter only valid characters from a text file
		char *hexBufferValid = malloc( buffer_size ); // Pointer to a 8192 bytes array

		// Clear buffers
		memset(hexBuffer, 0x00,  ( buffer_size / sizeof(hexBuffer[0])) );
		memset(hexBufferValid, 0x00,  ( buffer_size / sizeof(hexBufferValid[0])) );

		// Read the rom file in hexadecimal format in hexBuffer
		FILE *rom = fopen(filename, "rt");
		if (!rom) {
			fprintf(stderr, "Unable to open file '%s'!\n", filename);
			exit(1);
		}
		fread(&hexBuffer[0], 1, buffer_size, rom);
		fclose(rom);

		// Discard invalid values (like new lines (ascii 10)
		// Count rom valid bytes
		int index = 0;
		int rom_size = 0;
		for( int i = 0; i < buffer_size; i++ ) {

			// Convert ascii values into its hex correspondent
			if ( hexBuffer[i] >= 48 && hexBuffer[i] <= 57 ) {			// ASCII 0..9
				hexBufferValid[index] = hexBuffer[i] - 48;
				index++;
				rom_size++;
			} else if ( hexBuffer[i] >= 65 && hexBuffer[i] <= 70 ) { 	// ASCII A..E
				hexBufferValid[index] = hexBuffer[i] - 55;
				index++;
				rom_size++;
			} else if ( hexBuffer[i] >= 97 && hexBuffer[i] <= 102 ) {	// ASCII a..e
				hexBufferValid[index] = hexBuffer[i] - 87;
				index++;
				rom_size++;
			}
		}

		// Convert each 2 ascii bytes into one hexadecimal value
		index = 0;
		for( int i = 0 ; i < rom_size ; i+=2 ) {
			unsigned char mem_byte = hexBufferValid[i]<<4 | hexBufferValid[i+1];
			mem[PC+index] = mem_byte;
			index++;
		}

		// Convert from Big endian to Little endian
		for( int i = 0 ; i < rom_size ; i+=2 ) {
			unsigned char v1, v2;
			
			v1 = mem[PC+i];
			v2 = mem[PC+i+1];
			
			mem[PC+i] = v2;
			mem[PC+i+1] = v1;
		}

		// Tell CPU to start running the interpreter
		cpu_rom_loaded = true;

		// Enable the quirk menu
		gui_menu_quirks_inactive = false;
		

		// // Print Buffer (rom)
		// printf("Buffer (rom):\n");
		// for( int i = 0 ; i < rom_size ; i++ ) {
		// 	printf("%x", hexBufferValid[i]);
		// }
		// printf("\n\n");

		// // Print Memory
		// printf("Memory:\n");
		// for(int i = 0; i < mem_size; i++)
		// 	printf("%02X ", mem[i]);
		// printf("\n\n");

		// Free memory allocated
		free(hexBuffer);
		free(hexBufferValid);
	}

	printf("Loaded game: %s\n", filename);

}


// Get Game Signature
char *get_game_signature(char *filename) {

	// Get the first 12 elements of memory
	char *signature = (char *)malloc(26);
	sprintf(signature, "%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X", Memory[0x200], Memory[0x201], Memory[0x202],\
		 Memory[0x203], Memory[0x204], Memory[0x205], Memory[0x206], Memory[0x207], Memory[0x208], Memory[0x209]);

	// Sum all memory bytes
	unsigned int sum = 0;
	char sum_string[10] = "";
	for ( int i = 0x200 ; i < sizeof(Memory) ; i++ ) {
		sum += Memory[i];
	}
	sprintf(sum_string, "%d", sum);

	// Unify the 12 first bytes and the sum into the final signature
	sprintf(signature + strlen(signature), "+%s", sum_string);

	return signature;
}

int lib_gui_loadrom(void) {
    // initialize NFD
    // either call NFD_Init at the start of your program and NFD_Quit at the end of your program,
    // or before/after every time you want to show a file dialog.
    NFD_Init();

    nfdchar_t* outPath;

    // prepare filters for the dialog
    nfdfilteritem_t filterItem[2] = {{"Chip8 Binary ROMs", "CH8,ch8"}, {"Chip8 Hexadecimal ROMs", "hex,HEX"}};

    // show the dialog
    nfdresult_t result = NFD_OpenDialog(&outPath, filterItem, 2, NULL);
    if (result == NFD_OKAY) {
        // puts("Success!");
        // puts(outPath);

		// Hide Menu
		gui_show_menu = false;

		// Return the original Theme (before Pause)
		if ( cpu_rom_loaded ) {
			display_pixel_ON_color_alt	= display_pixel_ON_color_tmp;
			display_pixel_OFF_color_alt	= display_pixel_OFF_color_tmp;
			display_update_theme();
		}

		// Set the selected ROM
		filename = outPath;
		// Reset CPU
		cpu_reset();

		// Update StatusBar message
		char str[100];
		sprintf(str, "ROM loaded.");
		strcpy(gui_statusbar_msg, str);

		// Hack to force the draw on first frame to hide menu when quirk_display_wait is false
		// Some games take some time to draw
		if ( !quirk_display_wait ) {
			cpu_draw_flag = true;
		}

        // remember to free the memory (since NFD_OKAY is returned)
        // NFD_FreePath(outPath);

    } else if (result == NFD_CANCEL) {
        // puts("User pressed cancel.");
		gui_show_menu = true;

    } else {
        printf("NFD Error: %s\n", NFD_GetError());
		exit(2);
    }

	// Bring main window to front after choosing the rom
	SDL_RaiseWindow(window);

	// Quit NFD
    NFD_Quit();

    return 0;
}

// Show logo on initial screen (no rom loaded)
void showLogo(void) {
	for ( int i = 0; i < sizeof(font_logo) / sizeof(font_logo[0]); i++ ) {
		display_pixels[ font_logo[i] ] = display_pixel_ON_color;
	}
}


// // Show Emulator Cycles Per Second
// void showCPS(long long unsigned int number) 
// {
// 	// Variables
//     char nstring[50];
// 	int str_size, ptr, i , j = 0;

// 	// Convert the integer into a string
//     sprintf(nstring, "%llu", number);
// 	// Size of string
// 	str_size = strlen(nstring);

// 	// Label
// 	strcpy(string_msg1, "Emulator Cycles per second: ");

// 	// Work with First 3 digits
// 	ptr = str_size % 3;
// 	if (ptr) {
// 		 // Print first digits before point
// 		for ( i = 0 ; i < ptr ; i++ ) {      
// 			// printf("%c", nstring[i]); 
// 			strncat(string_msg1, &nstring[i], 1);
// 		}

// 		// Just print the point if number is bigguer than 3
// 		if ( str_size > 3) {
// 			// printf(".");
// 			strcat(string_msg1, ".");
// 		}
// 	}
//
// 	for ( i = ptr ; i < str_size ; i++ ) {      // print the rest inserting points
// 		// printf("%c", nstring[i]);
// 		strncat(string_msg1, &nstring[i], 1);
// 		j++;
// 		if ( j % 3 == 0 ) {
// 			if( i < (str_size-1) ) {
// 				strcat(string_msg1, ".");
// 				// printf(".");
// 			} 
// 		}
// 	}

// 	// printf("\n");
// }

// // Show Frames Per Second
// void showFPS(int number) 
// {
// 	int length = snprintf( NULL, 0, "%d", number );

// 	char temp[20];
// 	char fps_count[10];
// 	char fps_text[6] = "FPS: ";
// 	snprintf( fps_count, length + 1, "%d", number );

// 	memcpy(temp,fps_count,sizeof(fps_count));
// 	memcpy(fps_count,fps_text,strlen(fps_text));
// 	memcpy(fps_count+strlen(fps_text),temp,strlen(temp)+1);

// 	// strcpy(string_msg3, fps_count);
// }

// // Show CPU Cycles Per Second (Clock)
// void showCPU_CPS(int number) 
// {
// 	int length = snprintf( NULL, 0, "%d", number );

// 	char temp[30];
// 	char cps_count[30];
// 	char cps_text[30] = "CPU Clock: ";
// 	snprintf( cps_count, length + 1, "%d", number );

// 	memcpy(temp,cps_count,sizeof(cps_count));
// 	memcpy(cps_count,cps_text,strlen(cps_text));
// 	memcpy(cps_count+strlen(cps_text),temp,strlen(temp)+1);

// 	strcat(cps_count, " Hz");

// 	// strcpy(string_msg2, cps_count);
// }

// Time measurement in Microseconds (1 Sec = 1.000.000 Microsecs.)
long getMicrotime(void){
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

// Check if a string contains in another
uint8_t strContains(char* string, char* toFind)
{
    uint8_t slen = strlen(string);
    uint8_t tFlen = strlen(toFind);
    uint8_t found = 0;

    if( slen >= tFlen )
    {
        for(uint8_t s=0, t=0; s<slen; s++)
        {
            do{
                if( string[s] == toFind[t] )
                {
                    if( ++found == tFlen ) return 1;
                    s++;
                    t++;
                }
                else { s -= found; found=0; t=0; }

              }while(found);
        }
        return 0;
    }
    else return -1;
}

// Print the binary representation of a byte
void print_bin(unsigned char value)
{
	for (int i = sizeof(char) * 7; i >= 0; i--) {
		unsigned char tmp = (value & (1 << i)) >> i;

		if ( tmp == 1 ) {
       	 printf("###");
		} else {
			printf("___");
		}

	}
	printf("  %02X\n", value);
}
