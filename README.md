# Repo that reproduces the bugs that I encounter when using installed drake as external with bazel build system
* This repo is a copy of the official [`drake_bazel_installed`](https://github.com/RobotLocomotion/drake-external-examples/tree/main/drake_bazel_installed) example.
* I also add several targets from the official [`drake_bazel_external`](https://github.com/RobotLocomotion/drake-external-examples/tree/main/drake_cmake_external) to produce the bugs.
* I use an `apt` installed drake, which is located at `/opt/drake`. The bugs persists when I change to use the http_archive drake.
* I can build and run the original targets in `drake_bazel_installed` successfully with both the `apt` installed drake and the http_archive installed drake.

To reproduce the bug, run
```
bazel build //...
```

The error info that I see is:
```
DEBUG: Rule 'drake_artifacts' indicated that a canonical reproducible form can be obtained by modifying arguments sha256 = "073219cda0ee55fc302395d6dbdd8c703d4734774b1cc3a8d3c8289e5024b071"
DEBUG: Repository drake_artifacts instantiated at:
  /home/chenwang/repro_drake_bazel_external/drake_bazel_installed/WORKSPACE:63:13: in <toplevel>
Repository rule http_archive defined at:
  /home/chenwang/.cache/bazel/_bazel_chenwang/026752f2886d35384cb1076d1dc9796d/external/bazel_tools/tools/build_defs/repo/http.bzl:353:31: in <toplevel>
INFO: Analyzed 8 targets (55 packages loaded, 3114 targets configured).
INFO: Found 8 targets...
ERROR: /home/chenwang/repro_drake_bazel_external/drake_bazel_installed/apps/BUILD.bazel:98:11: Compiling apps/simple_adder.cc failed: (Exit 1): gcc failed: error executing command /usr/bin/gcc -U_FORTIFY_SOURCE -fstack-protector -Wall -Wunused-but-set-parameter -Wno-free-nonheap-object -fno-omit-frame-pointer -g0 -O2 '-D_FORTIFY_SOURCE=1' -DNDEBUG -ffunction-sections ... (remaining 27 arguments skipped)

Use --sandbox_debug to see verbose messages from the sandbox and retain the sandbox build root for debugging
In file included from bazel-out/k8-opt/bin/external/drake/_virtual_includes/.drake_headers/drake/common/default_scalars.h:3,
                 from bazel-out/k8-opt/bin/external/drake/_virtual_includes/.drake_headers/drake/systems/framework/leaf_system.h:14,
                 from apps/simple_adder.h:41,
                 from apps/simple_adder-inl.h:41,
                 from apps/simple_adder.cc:41:
bazel-out/k8-opt/bin/external/drake/_virtual_includes/.drake_headers/drake/common/autodiff.h:12:10: fatal error: Eigen/Core: No such file or directory
   12 | #include <Eigen/Core>
      |          ^~~~~~~~~~~~
compilation terminated.
INFO: Elapsed time: 38.676s, Critical Path: 0.15s
INFO: 12 processes: 12 internal.
FAILED: Build did NOT complete successfully
```