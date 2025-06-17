# Code Charlie
-This project is build for some kind of SBC Management. 

-Project is Linux exclusive because there is most likely no SBCs running other than linux.

-C standard for this projects is 23.

# Project Structure
-Every single file, rather its .h or .c, will include the header "CodeCharlieGlobal.h".
--This file includes:
---Most basic headers for direct use like stdbool, stddef, limits etc.
---Necessary headers for debugging like assert, stdio.
---Debugging macros for debug usage.
--And shouldn't include any custom build files.
-For debugging, there is info, warning and error debugs for debug build.--Debug build configuration can be made from global header.
-stdint types used in necessary places.
