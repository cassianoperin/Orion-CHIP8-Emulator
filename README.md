# CHIP-8 GUI with Nuklear

Port of chip8 emulator to use nuklear GUI.


1) Rever opc_chip8_0NNN, colocar um exit
2) CTX no final do loop
3) Ajeitar o main loop
4) Review: msg_emuinfo
5) Review: cycle_counter_cpu
6) Change it to popup
    // Show Emulator Information on screen (input)
	// case SDLK_8:
7) Ao carregar uma rom inválida, setar uma flag de erro no opcode nao existente, mostrar mensagem e talvez sair do loop do interpreter (cpu_rom_loaded = false), ou popup com erro e resetar.
8) Criar status bar na parte de baixo da tela
9) atualizar quirks
