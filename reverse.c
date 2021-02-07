//Your code goes here..!
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	FILE *fpin;
	FILE *fpout;
	size_t len = 0;
	ssize_t read;
	char *line = NULL;
	int linecount = 0;
	int max_line = 0;
	int i;

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
	

	while((read = getline(&line, &len, fpin)) != -1){
		linecount++;
		if(read > max_line){
			max_line = read;
		}

	}

	char file_lines[linecount][max_line];

	rewind(fpin);

	for(i = 0; i < linecount; i++){
		getline(&line, &len, fpin);
		strcpy(file_lines[i], line);
		printf("the text is: %s and i = %d\n\n", file_lines[i], i);
	}

	for(i = linecount - 1; i >= 0; i--){
		printf("%s and i = %d \n\n", file_lines[i], i);
	}

exit(0);
}