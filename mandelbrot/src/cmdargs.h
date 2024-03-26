#ifndef CMDARGS_H
#define CMDARGS_H

#include <unistd.h>

#include "common.h"


void parse_cmd_args( int argc, char **argv, Settings *settings );

#endif /* CMDARGS_H */