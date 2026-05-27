PowerPC test suite for emulators (starting, wip)
===

    make

Produces

    gen/arith_test.{linux, 601}
    gen/crbit_test.{linux, 601}

Results from a real mac g4 running linux are in results

There are currently linux wrappers, which result in programs that runs on linux, as well as wrappers which produce the simple flat image executable used by personal
power firmware and outputs to the rs/6000's serial port.

Both wrap the same test code, and the outputs are supposed to be the same.
