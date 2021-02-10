//Your code goes here..!
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int same_file(int fd1, int fd2) {
    struct stat stat1, stat2;
    if(fstat(fd1, &stat1) < 0) return -1;
    if(fstat(fd2, &stat2) < 0) return -1;
    return (stat1.st_dev == stat2.st_dev) && (stat1.st_ino == stat2.st_ino);
}

int main(int argc, char **argv)
{
	FILE *fpin;
	FILE *fpout;
	size_t len = 0;
	ssize_t read;
	char *line = NULL;
	int linecount = 0;
	int max_line = 0;
	int i, a;

	if(argc == 1){
		fpin = stdin;
		fpout = stdout;

		// printf("%s", stat(fpin).st_ino);
	}
	if(argc == 2){
		fpin = fopen(argv[1], "r");
		if(fpin == NULL){
			fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
			exit(1);
		}

		fpout = stdout;
	}
	if(argc == 3){
		fpin = fopen(argv[1], "r");
		fpout = fopen(argv[2], "w");
		
		if(fpin == NULL){
			fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
			exit(1);
		}

		if(fpout == NULL){
			fprintf(stderr, "reverse: cannot open file '%s'\n", argv[2]);
			exit(1);
		}

		int fd1 = fileno(fpin);
		int fd2 = fileno(fpout);

		if(same_file(fd1, fd2)){
			fprintf(stderr, "reverse: input and output file must differ\n");
			exit(1);
		}
	}

	if(argc > 3){
		fprintf(stderr, "usage: reverse <input> <output>\n");
		exit(1);
	}
	

	while((read = getline(&line, &len, fpin)) != -1){
		linecount++;
		if(read > max_line){
			max_line = read;
		}

	}

	char **file_lines = (char**) malloc(linecount * sizeof(char*));
  for (int i = 0; i < max_line; i++) {
	  file_lines[i] = (char*) malloc(max_line * sizeof(char));
  }

	rewind(fpin);

	for(i = 0; i < linecount; i++){
		getline(&line, &len, fpin);
		strcpy(file_lines[i], line);
	}

	for(a = linecount - 1; a >= 0; a--){
		fprintf(fpout, "%s", file_lines[a]);
	}

exit(0);
}