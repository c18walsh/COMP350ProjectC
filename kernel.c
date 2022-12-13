//kernel.c
//Connor Walsh working with James Evans

void printString(char*);
void printChar(char*);
void readString(char*);
void readSector(char*);
void handleInterrupt21(int,int,int,int);
void readFile(char*,char*, int);
void executeProgram(char*);
void terminate();

void main() {

	int startVidMem = 0xb800;
	int vidMemOffset = 0x0;
	int white = 0x7;
	char* letters = "Hello World\0";

	//char input[80];
	//int counter=0;



//	int ah=0xE;
//	int al='C';
//	int ax=ah*0x100+al;
//	interrupt(0x10,ax, 0,0,0);
//	interrupt(number, ax, bx, cx, dx)

	//printString("Hello World");
	//printChar('c');

	//char input[80];
	//int counter;
	//printString("Hello World\n");
	//readString();
	//counter=0;
	char buffer[13312];

/*
	//READFILE
	int sectorsRead;
	char* filename;
	filename="messag";
	makeInterrupt21();
	interrupt(0x21, 3, filename, buffer, &sectorsRead);
	if (sectorsRead>0){
		interrupt(0x21, 0, buffer, 0, 0);
	}
	else{
		interrupt(0x21, 0, "messag not found\r\n", 0, 0);
	}
	printString(buffer);*/

	//LOADFILE
	makeInterrupt21();
	interrupt(0x21,4,"shellz",0,0);
	

	//TERMINATE
/*
	makeInterrupt21();
	interrupt(0x21,4,"tstpr2",0,0);
*/
	while(1);
//	printString("Enter a line: ");
//	readString(line);
//	printString(line);


//read sector

//	readSector(buffer, 30);
//	printString(buffer);
//step 4
//	makeInterrupt21();
//	interrupt(0x21, 0, 0, 0);
//step 5
//	makeInterrupt21();
//	interrupt(0x21,1,line,0,0);
//	interrupt(0x21,0,line,0,0);


	while(1)
	{
	//char line[80];
	//printString("Enter a line: ");
	//readString(line);
	//printString(line);
	//printString("Hello World");
	//readString();
	/*	char x=interrupt(0x16,0,0,0,0);
		input[counter]=x;
		counter=counter+1;
		printChar(x);
		if(x==0xd){
			printChar('\n');
			break;
		}*/
	}
}

void printString(char* string){
	int c=0;
	int ah=0xE;
	//int al=string[c]
	while (string[c] != 0x0){
	int al=string[c];
	int ax=ah*0x100+al;
	interrupt(0x10,ax,0,0,0);
	c++;
	}
}

void printChar(char* letter){
	int ah=0xe;
	int al=letter;
	int ax=ah*0x100+al;
	interrupt(0x10,ax,0,0,0);
}

void readString(char* input){
	int counter;
	char x;
	counter=0;
	while(1){
		x=interrupt(0x16,0,0,0,0);
		if(x==0x8){
			if (counter == 0) {
				counter=0;
			}

			else{
				counter=counter-1;
				printChar('\b');
				printChar(' ');
				printChar('\b');
			}
	}
		else if(x== 0xd){
		input[counter]=0xa;
		printChar(0xa);
		counter=counter+1;
		input[counter]=0x0;
		printChar(0x0);
		printString("\n\r");
		return;
		}
		else{
		input[counter]=x;
		counter=counter+1;
		printChar(x);
		}

//		input[counter]=x;
//		counter=counter+1;
//		printChar(x);
/*		if(x==0xd)
		{
			input[counter]=0xa;
			printChar(input[counter]);
			counter=counter+1;
			input[counter]=0x0;
			printChar(input[counter]);
			counter=counter+1;
			//printChar(0xa);
			//printChar(0x0);
			break;
		}
		if(x==0x8)
		{
			if(counter>0){
			input[counter-1]=' ';
			counter=counter-1;
			//counter=counter-1;
			input[counter+1]=0x0;
			printChar(' ');
			printChar('\b');
			}
		}*/
	}
}

void readSector(char* buffer, int sector){
	int ah=2;
	int al=1;
	int bx=buffer;
	int ch=0;
	int cl=sector+1;
	int dh=0;
	int dl=0x80;

	int ax=ah*256+al;
	int cx=ch*256+cl;
	int dx=dh*256+dl;
	interrupt(0x13,ax,bx,cx,dx);
}

void handleInterrupt21(int ax, int bx, int cx, int dx){
	printString("Handle Interrupt 21 Test");

	if(ax==0){
		printString(bx);
	}
	if(ax==1){
		readString(bx);
	}
	if(ax==2){
		readSector(bx, cx);
	}
	if(ax==3){
		readFile(bx, cx, dx);
	}
	if(ax==4){
		executeProgram(bx);
	}
	if(ax==5){
		terminate();
	}
}

void readFile(char* filename,char* buffer, int* sectorsRead){
        char dir[512];
        int i;
	int j;
	int fileEntry;
	fileEntry=0;
	i=0;
	j=0;
	*sectorsRead=0;
        printString("readFile started\r\n");
	readSector(dir,2);
	//printChar(dir[32]);

	for (fileEntry=0; fileEntry<512; fileEntry+=32){
	        for (i=0; i<6; i++){
        	        if (filename[i]!=dir[fileEntry+i]){
                	        printString("file not found yet\r\n");
                        	*sectorsRead=0;
                        	break;
                	}
			if (filename[i]=='\0'&&dir[i+fileEntry]=='\0'){
				*sectorsRead= *sectorsRead+1;
				i=6;
				break;
			}
			else if(i==5){
                        	//printString("i is five but last char is not work");
                        	if(filename[i]==dir[fileEntry+i]){
                        	printString("file found\r\n");
				//if(dir[fileEntry+6]==5){printString("0");}

					while(dir[fileEntry+6+j]!=0){
						readSector(buffer, dir[fileEntry+6+j]);
						buffer=buffer+512;
						j=j+1;
						*sectorsRead=*sectorsRead+1;
					}
					return;
                        	}
                	}
        	}
	}
}

void executeProgram(char* name) {
	char buffer[13312];
	int i;
	int segment;

	segment = 0x2000;

	readFile(name, buffer, 0);
	for(i = 0; i < 13312; ++i) {
		putInMemory(segment,i,buffer[i]);
	}
	launchProgram(segment);
}

void terminate(){
	char shellName[6];
	shellName[0] = 's';
	shellName[1] = 'h';
	shellName[2] = 'e';
	shellName[3] = 'l';
	shellName[4] = 'l';
	shellName[5] = '\0';
	executeProgram(shellName);
}
