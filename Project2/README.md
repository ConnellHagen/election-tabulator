# Dependencies
GNU Make - required to run any Makefile commands

CMake - required to run GoogleTest tests using `make test`

# Usage Instructions

## Running
`make run` - Creates `/bin` directory if it does not already exist, then compiles the executable to `/bin`, then runs it.
The running of the executable will start the process of prompting the user for files to calculate the winner for. The paths
will be relative to the executable, so `testing/test_data/file_name.csv` is a valid path, but `file_name.csv` will not be
(assuming that the user does not add in their own file in that proper location).
NOTE: if `/bin` does not exist, running only `make` will fail, but `make run` will not.

## Documentation
`make docs` - Creates the doxygen documentation in `/documentation` according to the instructions within `Doxyfile`
Inside of `/documentation/html`, find `index.html`, and open it in a web browser. This will bring you to the interactive
documentation website.

## Testing
`make test` - Runs the test suite defined within `/testing`.

# Other Notes
 - Unit test code is located in /testing
 - The csv files we used for system and unit testing are located in /testing/test_data
