# Sandbox Function

## Overview
The `sandbox` function provides a secure testing environment for executing and evaluating function behavior. It acts as a safety wrapper that monitors function execution, handling potential crashes, timeouts, and abnormal terminations while preventing process leaks.

## Function Signature
```c
int sandbox(void (*f)(void), unsigned int timeout, bool verbose);
```

## Description
The sandbox function is designed to safely execute and evaluate functions by running them in an isolated environment. It determines whether a given function behaves "nicely" or exhibits "bad" behavior based on specific criteria.

### Return Values
- `1`: Function executed successfully (nice function)
- `0`: Function failed (bad function)
- `-1`: Internal sandbox error

### Parameters
- `f`: Function pointer to the target function to be tested
- `timeout`: Maximum execution time allowed (in seconds)
- `verbose`: Enable/disable detailed output messages

## Features

### Safety Mechanisms
- Process isolation using fork
- Signal handling for crash detection
- Timeout enforcement
- Zombie process prevention
- Comprehensive error handling

### Verbose Output Messages
When verbose mode is enabled, the function provides detailed feedback:
```
Nice function!
Bad function: exited with code <exit_code>
Bad function: <signal description>
Bad function: timed out after <timeout> seconds
```

### Bad Function Detection
A function is classified as "bad" if it:
- Terminates due to a signal (e.g., SIGSEGV, SIGABRT)
- Exits with a non-zero status code
- Exceeds the specified timeout duration

## Implementation Details

### Dependencies
```c
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
```

### Allowed Functions
- `fork`
- `waitpid`
- `exit`
- `alarm`
- `sigaction`
- `kill`
- `printf`
- `strsignal`
- `errno`

## Usage Examples
are in the main.c file

```

## Error Handling
The function handles various error scenarios:
- Invalid function pointers
- Process creation failures
- Signal handling setup failures
- Wait operation failures

## Technical Considerations
- Implements proper process cleanup
- Prevents zombie process formation
- Handles all potential signals
- Manages system resources efficiently
