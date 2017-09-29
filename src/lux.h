#include "arg.h"
#include "compat.h"
#include "pkg.h"

/* PKG_DIR: ROOT  PATH
 * PKG_LDB: LOCAL DATABASE
 * PKG_RDB: REPO  DATABASE
 * PKG_SRC: REPO  FILE
 * PKG_TMP: TMP   DIR
 * PKG_FMT: PKG   FORMAT
 * PKG_SIG: PKG   SIGNATURE
 */
#define PKG_DIR "/"
#define PKG_LDB "/var/pkg/ldb"
#define PKG_RDB "/var/pkg/rdb"
#define PKG_SRC "/var/pkg/source.list"
#define PKG_TMP "/tmp"
#define PKG_FMT ".tar.gz"
#define PKG_SIG ".sig"

static int add(Package *pkg, const char *);
static int del(Package *pkg, const char *);
static int fetch(Package *pkg);
static int info(Package *pkg);
