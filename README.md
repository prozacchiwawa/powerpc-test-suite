PowerPC test suite for emulators (starting, wip)
===

    make

Produces

    arith_test_linux
    arith_test.601


At present this just contains the program gen_subf_test, which generates a random sequence of addition and subtraction instructions and prints the results to some medium.

There is currently a linux wrapper, which results in a program that runs on linux, as well as a wrapper which produces the simple flat image executable used by personal
power firmware and outputs to the rs/6000's serial port.

Both wrap the same test code, and the outputs are supposed to be the same.
