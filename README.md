# CHIP-8 GUI with Nuklear

Port of chip8 emulator to use nuklear GUI.

1) Rever opc_chip8_0NNN, colocar um exit
2) Review: msg_emuinfo
3) Review: cycle_counter_cpu
4) Change it to popup
    // Show Emulator Information on screen (input)
	// case SDLK_8:
5) Ao carregar uma rom inválida, setar uma flag de erro no opcode nao existente, mostrar mensagem e talvez sair do loop do interpreter (cpu_rom_loaded = false), ou popup com erro e resetar.
6) Criar status bar na parte de baixo da tela
7) atualizar quirks

8) Atualizar o nuklear a framework pra ver se para de sumir o mouse quando aumenta o clock
9) Quando aperta a primeira tecla está travando