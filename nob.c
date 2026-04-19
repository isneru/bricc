#define NOB_IMPLEMENTATION
#include "nob.h"

int main(int argc, char **argv) {
  NOB_GO_REBUILD_URSELF(argc, argv);
  if (!nob_mkdir_if_not_exists("./build/"))
    return 1;

  const char *output_path = "./build/bricc";

  Nob_Cmd cmd = {0};
  nob_cmd_append(&cmd, "cc", "-Wall", "-Wextra", "-o", output_path, "bricc.c");
  if (!nob_cmd_run(&cmd))
    return 1;

  nob_cmd_append(&cmd, output_path);
  if (!nob_cmd_run(&cmd))
    return 1;

  return 0;
}
