# rest4git

RESTful web service based on (header-only) Crow c++ microframework for web to support customized git commands. A client can be any application on any platform that support HTTP network protocols. One could setup this web service, implement several useful REST-routing APIs (using GET or POST request) and return expected data from local git repository instead consuming local git or github. Basically, in bigger scope, you could even implement your own repository web application using this web service / backend.
As example, an ABAP program is consuming this RESTful web service to get its kernel's code source in c/c++ e.g. to blame a source from core dump information.

## How to build and launch:
1) Clone this repo somewhere on your local disk
 ```sh
  user@localhost:~>git clone https://github.com/jwongso/rest4git.git
  ```
2) Create build folder and create and configure make file using cmake
 ```sh
  user@localhost:~>cd rest4git
  user@localhost:~>mkdir build && cd build
  # Replace Debug with Release for release build
  user@localhost:~>cmake -DCMAKE_BUILD_TYPE=Debug ..
  ```
3) Compile the sources
```sh
  # Modify -j<number of your processor cores>
  user@localhost:~>make -j4
```
4) For testing and debugging, it's fine to start it directly
```sh
  user@localhost:~>cd src
  user@localhost:~>./rest4git &
```
5) Kill it if you're done
```sh
  user@localhost:~>ps -ef | grep rest4git
  # Copy the pid (from the 2nd column)
  user@localhost:~>kill <pid>
```
5) Once you are done with testing, you can finally launch it as (--user) service.
See [this](https://nts.strzibny.name/systemd-user-services/)
for easy undestanding how to create and run a service that runs under user privilege.
Double check whether automatic start-up of systemd user instances is enabled for your username:
```sh
  user@localhost:~>loginctl enable-linger $USER
```

## Super simple example from ABAP code:

```abap
REPORT z_rs_blame_last_stack_trace

DATA L_COMMAND    TYPE STRING.
DATA CMD(500)     TYPE C.
DATA p_line       TYPE I.
DATA p_file       TYPE STRING.
TYPES:
    T_LIST TYPE STANDARD TABLE OF char16384 WITH NON-UNIQUE DEFAULT KEY.
DATA RESULT       TYPE T_LIST.

" Blame at line <pline> in a kernel source file <p_file> via curl application with proper URL.
L_COMMAND = 'http://localhost:8000/blame/' && p_line && '/' && p_line && '/' && p_file.
CMD       = |wget -qO- { L_COMMAND }|.

call 'SYSTEM' id 'COMMAND' field CMD
              id 'TAB'     field RESULT.            "#EC CI_CCALL

IF SY-SUBRC <> 0.
"    Handle error.
endif.
" If successful, RESULT should contain following data:
" 173fca33f296 (<name@email.com> 2022-08-04 12265)               //~ ?( { $key1.itabtype = $itabtype; } key1:ITAB_USING_KEY )
" Process the RESULT e.g. extract the email, date/time and code information
```

## Help
Run from web browser:
[http://localhost:8000/](http://localhost:8000/)
or from console:
```sh
  user@localhost:~>curl http//localhost:8000/
```
to see the manual and examples

## Todo
Redis c++ integration to cache/speed up git blame and log related requests
