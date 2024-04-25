# Dependencies
GNU Make - required to run any Makefile commands

CMake - required to run GoogleTest tests using `make test`

# Run Instructions
`make run` - Creates `/bin` directory if it does not already exist, then compiles the executable to `/bin`, then runs it.
NOTE: if `/bin` does not exist, running only `make` will fail, but `make run` will not.

`make test` - Runs the test suite defined within `/testing`.

`make docs` - Creates the doxygen documentation in `/documentation` according to the instructions within `Doxyfile`

# Other Notes
 - Unit test code is located in /testing
 - The csv files we used for system and unit testing are located in /testing/test_data
 - To view documentation - run `make docs`, navigate to /documentation/html, and open index.html in your browser
