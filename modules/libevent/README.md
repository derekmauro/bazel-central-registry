Download the version you want to release from
https://github.com/libevent/libevent/releases

Run `cmake` to generate `evconfig-private.h` and `event2/event-config.h` in
`build/include`.

```
mkdir build && cd build
cmake ..
```

CMake detects the capabilities of the host platform and writes these files
accordingly, but this workflow doesn't happen on Bazel, so we will have to edit
these files and provide our own feature detection.

I also decided to make them platform specific for better organization. So for
example, I renamed `evconfig-private.h` to `evconfig-private_linux.h` and then
made `evconfig-private.h` into a platform selector file. I did the same with
`event2/event-config.h`. When you rename these files, be sure to fix the strings
used by the `#include` guards as well. These files get overlayed onto the tree
in the Bazel Central Registry as patches.

```shell
${CC:-gcc} -dM -E - $@ < /dev/null
```

Next you will have to create the `BUILD.bazel` file. Commands like 
```
ls -1 include/*.h | sort | awk '{ print "\""$0"\","}'
```
are helpful for getting the list of files in a format that can be copy-pasted.

https://github.com/bazelbuild/bazel-central-registry/blob/main/docs/README.md has some nice hints like running

```
bazel run -- //tools:update_integrity libevent
bazel shutdown && bazel build --enable_bzlmod --registry="file:///home/dmauro/github/bazel-central-registry" --lockfile_mode=off @libevent//...
```
