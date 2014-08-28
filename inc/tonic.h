#ifndef TONIC_H
#define TONIC_H
#include <math.h>
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif
// cures your ills, fixing programming stupidity everywhere

double rtod(double radians);

#define json_check(obj, e) if (!obj) { fprintf(stderr, "%s:%d:%d %s\n", e.source, e.line, e.column, e.text); exit(1);}
#endif
