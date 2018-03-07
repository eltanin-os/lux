#include <sys/stat.h>

#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "pkg.h"

int
copy(const char *src, const char *dest)
{
	ssize_t rf;
	int sf, tf, rval;
	char buf[BUFSIZ];

	sf   = tf = -1;
	rval =  0;

	if ((sf = open(src, O_RDONLY, 0)) < 0) {
		warn("open %s", src);
		goto failure;
	}

	if ((tf = open(dest, O_WRONLY | O_CREAT | O_EXCL, 644)) < 0) {
		warn("open %s", dest);
		goto failure;
	}

	while ((rf = read(sf, buf, sizeof(buf))) > 0) {
		if (write(tf, buf, rf) != rf) {
			warn("write %s", dest);
			goto failure;
		}
	}

	if (rf < 0) {
		warn("read %s", src);
		goto failure;
	}

	goto done;
failure:
	rval = -1;
done:
	if (sf != -1)
		close(sf);
	if (tf != -1)
		close(tf);

	return rval;
}

int
move(const char *src, const char *dest)
{
	struct stat st;

	if (stat(src, &st) < 0) {
		warn("stat %s", src);
		return -1;
	}

	switch(st.st_mode & S_IFMT) {
	case S_IFDIR:
		if (mkdir(dest, st.st_mode) < 0 && errno != EEXIST) {
			warn("mkdir %s", dest);
			return -1;
		}
		break;
	default:
		if (rename(src, dest) < 0) {
			warn("rename %s %s", src, dest);
			return -1;
		}
		break;
	}

	return 0;
}

int
remove(const char *path) {
	struct stat st;
	int (*fn)(const char *);

	if (stat(path, &st) < 0) {
		warn("stat %s", path);
		return -1;
	}

	if (S_ISDIR(st.st_mode))
		fn = rmdir;
	else
		fn = unlink;

	if (fn(path) < 0) {
		warn("remove %s", path);
		return -1;
	}

	return 0;
}
