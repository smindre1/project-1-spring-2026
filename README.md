# Assignment 1
By Shane Mindreau - 2/24/2026

## Assignment Completion

Test 1: Testing the big five (13/14)
Test 1: Testing overloading operators (8/9)
Test 2: Testing the big five (12/14)
Test 2: Testing overloading operators (4/9)
Test 3: Testing the big five (8/14)

The assignment was completed, however, because of some unknown formatting issues with << and >> operators, and other function formatting, I was not able to get 100% from gradescope. These issues were due to not being properly informed on how the assignment should be formatted, because even though I matched what the tests were looking for in outputs I still had points deducted.

## Bugs I encountered

I encountered some bugs of mismatching data types of the array carrying integers, doubles, and being a pointer making it unable to transform into another data type. This was a relatively easy fix.

I also encountered a few stringstream bugs where manipulating the stringstream needed to be corrected.

The biggest bug is gradescope not explaining why points were deducted when my output matched exactly what they were looking for, which is very upsetting.


## Running the assignment

You will use `Makefile` to compile on the terminal. To do this type in the terminal:

```bash
make clean
make all
```

To delete executables and object files, type:

```bash
make clean
```

To run, type:

```bash
./test_points2d
```

## Providing Input from Standard Input

To run with a given file that is redirected to standard input:

```bash
./test_points2d < test_input_file.txt
```
