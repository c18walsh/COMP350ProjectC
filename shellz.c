main(){
	char input[80];
	while(1){
		syscall(0, "SHELL> ");
		syscall(1, input);
		if(input!="pwoeriwpeori"){
			("Bad Command");
			break;
		}
	}
}
