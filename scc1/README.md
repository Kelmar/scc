Stage 1 compiling.

This occurs after the preprocessor has done it's thing.

We need to keep an eye out for "#line" directives while lexing; that will
change the file name and line number, which we'll need for error reporting.
