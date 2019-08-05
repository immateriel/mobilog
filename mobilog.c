#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>
/* include libmobi header */
#include <mobi.h>

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Usage: mobilog filename.mobi\n");
		exit(1);
	}
	char *filename = argv[1];

	MOBI_RET mobi_ret;

	unsigned char *data = NULL;
	size_t size = 0;

	/* Initialize main MOBIData structure */
	MOBIData *m = mobi_init();
	if (m == NULL) {
		printf("Memory allocation failed\n");
		exit(1);
	}

	errno = 0;
	FILE *file = fopen(filename, "rb");
	if (file == NULL) {
		int errsv = errno;
		printf("Error opening file: %s (%s)\n", filename, strerror(errsv));
		mobi_free(m);
		exit(1);
	}
	/* MOBIData structure will be filled with loaded document data and metadata */
	mobi_ret = mobi_load_file(m, file);
	fclose(file);

	MOBIPdbRecord *rec = m->rec;
	while(rec != NULL) {
		if(rec->data[0] == 'C' && rec->data[1] == 'M' && rec->data[2] == 'E' && rec->data[3] == 'T')
		{
			char *out;
			out = rec->data+12;
			printf("%s\n",out);
			mobi_free(m);
			exit(0);
		}
		rec = rec->next;
	}
	mobi_free(m);
	exit(1);
}