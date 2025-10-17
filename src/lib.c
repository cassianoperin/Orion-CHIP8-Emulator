#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include "lib.h"
//Native File Dialog Extended 
#include <nfd.h>
// SHA1
#include <openssl/evp.h>

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

// Get the file size and generate the SHA1 hash
RomInfo file_size_and_hash(char *filename){

	FILE *file = fopen(filename, "rb");
	if (!file) {
		fprintf(stderr, "Unable to open file '%s'!\n", filename);
		exit(1);
	}

	// Get the file size without change the reader pointer
    int prev=ftell(file);
    fseek(file, 0L, SEEK_END);
    int file_size=ftell(file);
    fseek(file,prev,SEEK_SET); //go back to where we were

	// Start of SHA1 Hash generation //
	EVP_MD_CTX *mdctx;
    unsigned char buffer[1024];
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;

    // Create the context to generate the hash
    mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL) {
        perror("Error creating SHA1 hash context!\n");
        fclose(file);
		exit(1);
    }

    // Initialize the context to generate SHA1 hash
    EVP_DigestInit_ex(mdctx, EVP_sha1(), NULL);

    // Read the file in blocks and update the hash
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        EVP_DigestUpdate(mdctx, buffer, bytesRead);
    }

    // End the hash calculation
    EVP_DigestFinal_ex(mdctx, hash, &hash_len);

    // Free the context
    EVP_MD_CTX_free(mdctx);

	// End of SHA1 Hash generation //

	// Close File
	fclose(file);

	// Memory allocation to keep hash string
    // char *hash_str = malloc(hash_len * 2 + 1);
    char *hash_str = malloc(hash_len * 2 + 1);
    if (hash_str == NULL) {
        perror("Failed to allocate memory to keep sha1 hash!");
        exit(1);
    }

    // Convert hash bytes to hexadecimal string 
    for (unsigned int i = 0; i < hash_len; i++)
        sprintf(&hash_str[i * 2], "%02x", hash[i]);

	// End the string
    hash_str[hash_len * 2] = '\0';

	// Initialize struct with defaults
	RomInfo result = {NULL, 0}; 

	// Fill the struct
    result.hash_str = hash_str;   // Hash
    result.file_len = file_size;  // File Size

    return result;
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

		// Set the selected ROM
		filename = outPath;

		// Reset CPU
		cpu_reset();

		// // Hack to force the draw on first frame to hide menu when quirk_display_wait is false
		// // Some games take some time to draw
		// if ( !quirk_display_wait ) {
		// 	cpu_draw_flag = true;
		// }

        // remember to free the memory (since NFD_OKAY is returned)
        // NFD_FreePath(outPath);

    } else if (result == NFD_CANCEL) {
        // puts("User pressed cancel.");

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
		gui_pixels_logo[ font_logo[i] ] = gui_pixel_logo_ON_color;
	}

}

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
