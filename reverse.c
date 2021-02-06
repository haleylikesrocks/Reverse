//Your code goes here..!
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	FILE *fpin;
	FILE *fpout;

	if(argc == 1){
		fpin = stdin;
		fpout = stdout;
	}
	if(argc == 2){
		fpin = fopen(argv[1], "r");
		fpout = stdout;
	}
	if(argc == 3){
		fpin = fopen(argv[1], "r");
		fpout = fopen(argv[2], "r");
		
		if(fpin == NULL){
			fprintf(stderr, "reverse: cannot open file\n");
			exit(1);
		}

		if(fpout == NULL){
			fprintf(stderr, "reverse: cannot open file\n");
			exit(1);
		}

		if(fpout == fpin){
			fprintf(stderr, "Input and out file must differ\n");
			exit(1);
		}

	}
	if(argc > 3){
		fprintf(stderr, "usage: reverse <input><output>\n");
		exit(1);
	}
	
exit(0);
}