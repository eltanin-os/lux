#include <sys/stat.h>

#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lux.h"

int
db_eopen(const char *path, Package **pkg)
{
	if (!(*pkg = db_open(path))) {
		if (errno == ENOMEM)
			err(1, NULL);
		warn("open_db %s", path);
		return 1;
	}

	return 0;
}

void
usage(void)
{
	fprintf(stderr,
	    "usage: %s add          package ...\n"
	    "       %s del          package ...\n"
	    "       %s fetch        package ...\n"
	    "       %s info  [-dlr] package ...\n",
	    getprogname(), getprogname(), getprogname(), getprogname());
	exit(1);
}

int
main(int argc, char *argv[])
{
	int (*fn)(int, char **) = NULL;

	setprogname(argv[0]);
	argc--, argv++;

	if (!argc)
		usage();

	if (!strcmp(*argv, "add"))
		fn = add_main;
	else if (!strcmp(*argv, "del"))
		fn = del_main;
	else if (!strcmp(*argv, "fetch"))
		fn = fetch_main;
	else if (!strcmp(*argv, "info"))
		fn = info_main;
	else
		usage();

	exit(fn(argc, argv));
}
