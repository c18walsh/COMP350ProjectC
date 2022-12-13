//Connor Walsh/James Evans
main(){
	char input[80];
	char buffer[13312];
	char filename[6];
	char command[5];

	while(1){
		syscall(0, "SHELL> ");
		syscall(1, input);

		command[0] = input[0];
		command[1] = input[1];
		command[2] = input[2];
		command[3] = input[3];

		filename[0] = input[5];
		filename[1] = input[6];
		filename[2] = input[7];
		filename[3] = input[8];
		filename[4] = input[9];
		filename[5] = input[10];



		if(command[0] == 't' && command[1] == 'y' && command[2] == 'p' && command[3] == 'e') {
			// 'TYPE' COMMAND
			syscall(3, filename, buffer, 0);
			syscall(0, buffer);
		}else {
                        syscall(0, "Command not recognized...");
                }



		if(command[0] == 'e' && command[1] == 'x' && command[2] == 'e' && command[3] == 'c') {
			// 'EXEC' COMMAND
			syscall(3, filename, buffer, 0);
			syscall(4, filename);
		}else {
			syscall(0, "Command not recognized...");
		}
	}
}
