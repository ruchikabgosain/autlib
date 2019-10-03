
[![Build Status](https://travis-ci.com/gkarlos/autlib.svg?branch=master)](https://travis-ci.com/gkarlos/autlib) [![codecov](https://codecov.io/gh/gkarlos/autlib/branch/master/graph/badge.svg)](https://codecov.io/gh/gkarlos/autlib) [![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

autlib
======
autlib is a simple, open source, C library for the manipulation of `AUT` files. It takes care of a lot of boilerplate code that is otherwise required to read/write and convert `AUT` files.

<table>
  <tr>
    <td><b>Homepage</b></td>
    <td>TBA</td>
  </tr>
  <tr>
    <td><b>Online Docs</b></td>
    <td>TBA</td>
  </tr>
</table>

## The AUT file : what is it? 
An `AUT` file is a text file used to represent Labelled Transition System (LTS) ([more](https://en.wikipedia.org/wiki/Transition_system)). It consists of a descriptor line, followed by 1 or more lines, one for each transition is the LTS. 

The `AUT` descriptor (first line in file) is of the form : 

```des (<initial_state>, <number_of_transitions>, <number_of_states>)```

The transitions (each remaining line) are of the form :

```(<source_state>, <transition_action>, <target_state>)```

autlib follows the `AUT` format specification (2014 Version) as defined in [CADP](https://cadp.inria.fr/man/aut.html). Example LTS and the `AUT` file it produces:

<table border="0" style="border-style : hidden!important;">
 <tr>
    <td style="border-style : hidden!important;">
      <img class="center-block" src="https://www.researchgate.net/profile/Haiyu_Pan/publication/267047900/figure/fig2/AS:673458769903620@1537576491710/The-labelled-transition-system-A.ppm">
    </td>
    <td style="border-style : hidden!important;"> 
      <pre> <code>
    des (0, 10, 7)
    (0, "a", 1)
    (0, "b", 2)
    (1, "a", 3)
    (1, "a", 4)
    (2, "b", 5)
    (2, "c", 6)
    (3, "a", 3)
    (4, "b", 4)
    (5, "a", 5)
    (6, "c", 6)</code></pre>
    </td>
 </tr>
</table>

## Using autlib : Requirements, Builds and Tests

### Requirements

<table>
  <tr>
    <td><b>Build</b></td>
    <td>CMake</td>
    <td><b>Docs</b></td>	
    <td>Doxygen</td>
  </tr>
  <tr>
    <td><b>Compiler</b></td>
    <td>GCC (for now)</td>
    <td><b>Testing</b></td>	
    <td>Git</td>
  </tr>
  <tr>
    <td><b>Parsing</b></td>
    <td>Flex, Bison</td>
    <td><b>Coverage</b></td>
    <td>lcov</td>
  </tr>
</table>

### Build the library
Before we start deployment, make sure you have installed all the required packages in your machine. To do this, follow: 
- ```
  cd autlib
  mkdir build && cd build
  cmake ..
  make
  ```

### Run the tests
Now that you have built the library, let's try running some tests!

- Run `ctest`, or `ctest -V` for more verbose output
- Alternatively, you can change directory into the test folder with the following command : 
  ```
  cd autlib/build/test
  ```
  and run all tests as follows: 
  ```
  ./test_all
  ```
  To run a specific test, use :
  ```
  ./test_repr_descriptor
  ```
### Link autlib to your project
To compile a dummy source file `main.c` and link `autlib` run:
- <b>GCC</b>:
  ```
  gcc -Lpath/to/autlib/build/src -o main main.c -lautlib 
  ```

### Examples

Read an `AUT` file and print the transitions:
```c
#include <aut/read.h>
#include <aut/repr.h>

int main(void)
{
  Aut *lts;
  AutErr err;
  if ((err = aut_read("path/to/file.aut", &lts) != AUT_ESUCCESS) {
    fprintf(stderr, "error opening file");
    exit(1);
  }

  AutTransition *t;
  for ( size_t i = 0; i < aut_get_size(lts); ++i) {
    t = aut_get_transition(lts, i);
    printf("%ld -> %ld, %s", aut_transition_get_source(t),
                             aut_transition_get_target(t),
                             aut_transition_get_action(t));
  }

  // ... process lts

  aut_destroy(&lts);
}
```

Construct an AUT file:
```c
#include <aut/repr.h>
#include <aut/write.h>

int main(void)
{
  Aut *lts;
  AutDescriprot *d;
  AutErr err;
  if ((err = aut_descriptor_create(&d, 0, 5, 6)) != AUT_ESUCCESS) {
    fprintf(stderr, "error creating decriptor (%s)", aut_error_str(err));
    exit(1);
  }

  if ((err = aut_create(&lts, d, "t")) != AUT_ESUCCESS) {
    fprintf(stderr, "error creating aut (%s)", aut_error_str(err));
    exit(1);
  }

  AutTransition *t;
  for ( size_t i = 0; i < aut_descriptor_get_num_transitions(d); ++i) {
    if ( (err = aut_add_transition(lts, i, i + 1, "t")) != AUT_ESUCCESS)
      fprintf(stderr, "error adding transition (%s)", aut_error_str(err));
  }

  // ... process lts

  aut_destroy(&lts);
}
```
## Documentation

Documentation is automatically generated on `make`. It can be easily browsed locally by `./readthedocs.sh` from the root of the project.

## Contributing
Contributions are always welcome! Help us make this project more awesome. 

If you are interested in contributing, please head over to [`CONTRIBUTING.md`](./CONTRIBUTING.md) to get started. We're waiting! :smile

## License
`autlib` is licensed under the MIT License. You can head over to [`LICENSE.md`](./LICENSE.md) file for details.

## Credits
Offering thanks to this beautiful Doxygen Theme by https://github.com/aklapatch/doxygenTheme
