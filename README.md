## Code Charlie
## Code Charlie
-This project is build for some kind of SBC Management. 

-Project is Linux exclusive because there is most likely no SBCs running other than linux.

-And it's probably not compatible with distributions other than debian based ones.

-C standard for this projects is 23.

# Project Structure
-Every single file, rather its .h or .c, will include the header "BaseGlobal.h".
--This file includes:
---Most basic headers for direct use like stdbool, stddef, limits etc.
---Necessary headers for debugging like assert, stdio.
---Debugging macros for debug usage.
--And shouldn't include any custom build files.
-For debugging, there is info, warning and error debugs for debug build.--Debug build configuration can be made from global header.

## The App
-First of all, I don't know what I'm doing in this project honestly. Just trying out some hardware and software ideas that I can't do in windows and regular pcs. The process will show us whats going to happen. I hope you good days, evenings and nights.
-The app must be run with sudo to make gpio interface work.