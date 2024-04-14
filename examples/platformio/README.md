# platformio

This is a minimal example of using [`byte_order`](https://github.com/ardnew/byte_order) with PlatformIO.

The [native](https://github.com/platformio/platform-native) platform is used by default and can be executed on your local host with the following commands:

```
# Clone this repository
git clone https://github.com/ardnew/byte_order.git
cd byte_order/examples/platformio

# Use debug env to build against the locally-cloned repo
pio run -e debug -t exec
```

The final command above should produce output similar to:

```none
$ pio run -e debug -t exec
Processing debug (platform: native)
--------------------------------------------------------------------------
Verbose mode can be enabled via `-v, --verbose` option
LDF: Library Dependency Finder -> https://bit.ly/configure-pio-ldf
LDF Modes: Finder ~ chain, Compatibility ~ soft
Found 1 compatible libraries
Scanning dependencies...
Dependency Graph
|-- byte_order @ 0.2.0
Building in debug mode
Executing .pio/build/debug/program
word = 3412
swap = 1234
orig = 3412
====================== [SUCCESS] Took 0.41 seconds ======================

Environment    Status    Duration
-------------  --------  ------------
debug          SUCCESS   00:00:00.414
====================== 1 succeeded in 00:00:00.414 ======================
```
