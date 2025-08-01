# Ref the Reference Application

The purpose of this application is to demonstrate a completely assembled application for use on Linux, and macOS.  This allows the user to get
up and running quickly, test the installation, and work with the code before embedded hardware may be available. Should the user be interested in
cross-compiling, please see the [F Prime LED Tutorial](https://fprime.jpl.nasa.gov/latest/tutorials-led-blinker/docs/led-blinker/).

## Prerequisites

Understanding the reference application has a few minimal prerequisites.

**Installing F´**

Please follow the [install guide for F´](../docs/getting-started/installing-fprime.md).

## Building and Running the Ref Application

To get started with creating the Ref application we will first need to clone the nasa/fprime repository. We then can change directories into the project's
Ref directory so that we have a place to build the Ref application.

```
git clone https://github.com/nasa/fprime
cd fprime/Ref
```

With the repository cloned and the project's Ref directory entered we can now create a python virtual environment, activate that environment, and then
install the project requirements.

```
python3 -m venv fprime-venv
. fprime-venv/bin/activate
pip install -r ../requirements.txt
```

In order to build the Ref application, or any other F´ application, we need to generate a build directory.  F´ uses CMake under the hood,
which requires a directory to work in. To generate a build directory, we will use the `fprime-util` (a wrapper for CMake to streamline standard 
F´ processes). This can be done with the following commands:

```
fprime-util generate
```

Now that the build directory has been generated, the user need not run `fprime-util generate` again unless the build directory has been removed.

The next step is to build the Ref application's code. This is done for the current system that the user is running on. This is handled by CMake
and will produce a binary that can be run on the user's system. This is accomplished by using the `build` subcommand of `fprime-util`.

## Running the F´ Ground System and Code

F´ ships with a browser-based test ground system. This system is designed to help developers of F´
projects quickly test and work with F´ code without much overhead. This ground system can be run
with the following commands. Please note: the Ref application's binary will also be run
automatically. This allows for quick testing on Linux and macOS. Before running the GDS, make sure
that you have built the Ref example.

```
cd fprime/Ref
fprime-gds
```

The user may now explore the "Commanding", "Event", and "Channels" tabs to see the F´ code in action.  The "Logs" tab has logs for the running
application should an error arise.  See: Logs -> Ref.log to see standard output of the Ref app.

To run the ground system without starting the Ref app:
```
cd fprime/Ref
fprime-gds --no-app
```

The ref app may then be run independently from the created 'bin' directory.

```
cd fprime/Ref/build-artifacts/<platform>/bin/
./Ref -a 127.0.0.1 -p 50000
```

## Quick Tips

- The F´ GDS defaults to port 50000. More information can be found with `fprime-gds --help`
- The F´ utility's build command can build individual components too.
- The 'generate' command can take a toolchain argument for quickly generating a cross-compile `fprime-util generate raspberrypi` for example.

Further work with the F´ utility can be found in the [HelloWorld tutorial](../docs/tutorials/index.md) tutorial.

