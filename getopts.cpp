/**
 * Example program demonstrating the usage of getopt_long.
 */

#include <getopt.h>
#include <iostream>
#include <cstdlib>

using namespace std;


int main (int argc, char** argv) {
  // Flag set by --verbose and --quiet.
  int verbosity = 0;

  // An array of long-form options.
  static struct option long_options[] = {
    // Because the third argument for these two flags is non-NULL, getopt_long
    // will set the indicated variable (verbosity) to the given value (42 or
    // 10) if the flag is present.
    {"verbose", no_argument,       &verbosity, 42},
    {"quiet",   no_argument,       &verbosity, 10},

    // Because the third argument is NULL for these flags, getopt_long will
    // return the fourth argument when these are encountered. If the long-form
    // flag corresponds to a short-form flag, use the short-form character and
    // you can handle both cases (long and short) the same way.
    {"add",     no_argument,       NULL, 'a'},
    {"append",  no_argument,       NULL, 'b'},
    {"delete",  required_argument, NULL, 'd'},
    {"create",  required_argument, NULL, 'c'},
    {"file",    required_argument, NULL, 'f'},

    // Terminate the long_options array with an object containing all zeroes.
    {0, 0, 0, 0}
  };

  // getopt_long parses one argument at a time. Loop until it tells us that it's
  // all done (returns -1).
  while (true) {
    // getopt_long stores the latest option index here,you can get the flag's
    // long-form name by using something like long_options[option_index].name
    int option_index = 0;

    // Process the next command-line flag. the return value here is the
    // character or integer specified by the short / long options.
    int flag_char = getopt_long(
        argc,           // The total number of arguments passed to the binary
        argv,           // The arguments passed to the binary
        "abc:d:f:",     // Short-form flag options
        long_options,   // Long-form flag options
        &option_index); // The index of the latest long-form flag

    // Detect the end of the options.
    if (flag_char == -1) {
      break;
    }

    switch (flag_char) {
    case 0:
      // flag_char will be 0 for long-form options like --verbose and --quiet,
      // where the third argument is not NULL. This would also get hit if you
      // set the fourth argument for the other arguments to 0.
      cout << "Saw --" << long_options[option_index].name << " flag" << endl;
      break;

    case 'a':
      cout << "option -a" << endl;
      break;

    case 'b':
      cout << "option -b" << endl;
      break;

    case 'c':
      cout << "option -c with value " << optarg << endl;
      break;

    case 'd':
      cout << "option -d with value " << optarg << endl;
      break;

    case 'f':
      cout << "option -f with value " << optarg << endl;
      break;

    case '?':
      // This represents an error case, but getopt_long already printed an error
      // message for us.
      break;

    default:
      // This would only happen if a flag hasn't been handled, or if you're not
      // detecting -1 (no more flags) correctly.
      exit(EXIT_FAILURE);
    }
  }

  if (verbosity == 42) {
    cout << "--verbose flag is set" << endl;
  }

  if (verbosity == 10) {
    cout << "--quiet flag is set" << endl;
  }

  // Print any other command line arguments that were not recognized as flags.
  if (optind < argc) {
    cout << "Non-option ARGV-elements: ";

    for (int i = optind; i < argc; i++) {
      cout << argv[i] << " ";
    }

    cout << endl;
  }

  return EXIT_SUCCESS;
}

