# Debug application with GDB

This guide describes the use of GDB to debug programs created in C on the EVK.
For more detailed information about GDB, refer to [Debugging with GDB](https://ftp.gnu.org/old-gnu/Manuals/gdb/html_chapter/gdb_toc.html).

You need to connect your PC to the EVK, and you need to install the following terminal program to run and debug the target program on the EVK.

=== "Windows PC"

	[Tera Term (terminal software)](https://github.com/TeraTermProject/teraterm/releases)

	[FTDI VCP driver](https://www.ftdichip.com/Drivers/VCP.htm)

=== "Linux PC"

	[minicom](https://help.ubuntu.com/community/Minicom)

## **Table of Contents**

  - [1. How to use GDB](#1-how-to-use-gdb)
    - [1-1. Give debugging symbols and execute compilation](#1-1-give-debugging-symbols-and-execute-compilation)
    - [1-2. Execute the created program in GDB](#1-2-execute-the-created-program-in-gdb)
    - [1-3. Stops a program running in GDB](#1-3-stops-a-program-running-in-gdb)
    - [1-4. Exit GDB](#1-4-exit-gdb)
    - [1-5. Display GDB help](#1-5-display-gdb-help)
  - [2. Monitor program execution](#2-monitor-program-execution)
    - [2-1. Interrupts the execution of the program](#2-1-interrupts-the-execution-of-the-program)
    - [2-2. Continue program execution](#2-2-continue-program-execution)
    - [2-3. Check the interruption points of the program](#2-3-check-the-interruption-points-of-the-program)
    - [2-4. Execute the program code line by line](#2-4-execute-the-program-code-line-by-line)
    - [2-5. Check the contents of program variables](#2-5-check-the-contents-of-program-variables)
    - [2-6. Change program variables](#2-6-change-program-variables)
    - [2-7. Calls a specific function linked to the program](#2-7-calls-a-specific-function-linked-to-the-program)
    - [2-8. Return from program functions](#2-8-return-from-program-functions)
  - [3. Set breakpoints](#3-set-breakpoints)
    - [3-1. Set breakpoints on specific lines](#3-1-set-breakpoints-on-specific-lines)
    - [3-2. Set a breakpoint in the function](#3-2-set-a-breakpoint-in-the-function)
    - [3-3. Obtain a list of breakpoints](#3-3-obtain-a-list-of-breakpoints)
    - [3-4. Disable breakpoints](#3-4-disable-breakpoints)
  - [4. Set watchpoints](#4-set-watchpoints)
    - [4-1. Set watchpoints for variable writes](#4-1-set-watchpoints-for-variable-writes)
    - [4-2. Set watchpoints for variable reads](#4-2-set-watchpoints-for-variable-reads)
    - [4-3. Set watchpoints for reading and writing variables](#4-3-set-watchpoints-for-reading-and-writing-variables)
    - [4-4. Obtain a list of watchpoints](#4-4-obtain-a-list-of-watchpoints)
    - [4-5. Disable watchpoints](#4-5-disable-watchpoints)
  - [5. Execute call stack](#5-execute-call-stack)
    - [5-1. Obtain a backtrace of the function](#5-1-obtain-a-backtrace-of-the-function)
    - [5-2. Change the stack frame](#5-2-change-the-stack-frame)
    - [5-3. Analyze stack frames](#5-3-analyze-stack-frames)
  - [6. Examples](#6-examples)
    - [6-1. Example 1 of infinite loop analysis](#6-1-example-1-of-infinite-loop-analysis)
    - [6-2. Example 2 of infinite loop analysis](#6-2-example-2-of-infinite-loop-analysis)
    - [6-3. Segmentation Fault Analysis Example](#6-3-segmentation-fault-analysis-example)


## 1. How to use GDB

This chapter explains how to prepare for debugging an application and how to start/stop basic GDB.  

The gdb command is not installed in the HMI SDK environment by default.
To install gdb, you need to build HMI SDK environment after changing configuration.
To build HMI SDK environment, see [How to Build HMI SDK](../../how_to_build_hmi_sdk/).
In the build procedure, modify configuration file before you run bitbake command.

1. Open the configuration file
```bash
cd ${WORK}/build
vim conf/local.conf
```
{: .dollar }

1. Add the following settings to the configuration files
```
WHITELIST_GPL-3.0 += " tools-debug gdb autoconf-native bison-native gettext-native gnu-config-native readline"
IMAGE_INSTALL_append = " gdb"
EXTRA_IMAGE_FEATURES_append = " tools-debug"
```

2. Run bitbake with gdb alone to make sure no error occurs.
```bash
MACHINE=${BOARD} bitbake gdb
```
{: .dollar }

3. Run bitbake to build images (See [How to Build HMI SDK](../../how_to_build_hmi_sdk/).)

### 1-1. Give debugging symbols and execute compilation

The -g flag must be passed to the compiler to grant debugging symbols.  
Add the -g flag to the Makefile. Add the -O0 flag to disable optimization.

```bash title="Makefile"
APP = testprog
SRC = main.c
all: $(APP)
CC = gcc
CFLAGS = -g -O0 -Wall
$(APP):
        $(CC) -o $(APP) $(SRC) $(CFLAGS)
clean:
        rm -rf $(APP)
```
The source code should be the following.
```bash title="main.c"
#include <stdio.h>

int func1(int num)
{
   static int sum = 0;
   sum += num;
   return sum;
}

int main(int argc, char** argv)
{
   int num;
   num = 1;
   while(1){
      if(num > 5000){
         break;
      }
      func1(num);
   }
   return 0;
}
```

### 1-2. Execute the created program in GDB

Execute gdb with the program compiled with the -g flag as an argument.
```
# gdb testprog
...
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from testprog...
(gdb)
```
The gdb prompt will be invoked, and the program will run when the run command is executed. When specifying arguments, enter arg1, arg2, and so on.
```
(gdb) run arg1 arg2
Starting program: /home/root/debug/testprog arg1 arg2
```

### 1-3. Stops a program running in GDB

To stop the program, use the kill command.
```
(gdb) kill
Kill the program being debugged? (y or n) y
[Inferior 1 (process 46857) killed]
(gdb)
```
To run the program again, execute the run command.
```
(gdb) run
Starting program: /home/root/debug/testprog
```

### 1-4. Exit GDB

To exit GDB, use the quit command.
```
(gdb) quit
```

### 1-5. Display GDB help

If you want to check the help for GDB commands, use the help command.
```
(gdb) help
List of classes of commands:

aliases -- Aliases of other commands.
breakpoints -- Making program stop at certain points.
data -- Examining data.
files -- Specifying and examining files.
internals -- Maintenance commands.
obscure -- Obscure features.
running -- Running the program.
stack -- Examining the stack.
status -- Status inquiries.
support -- Support facilities.
tracepoints -- Tracing of program execution without stopping the program.
user-defined -- User-defined commands.

Type "help" followed by a class name for a list of commands in that class.
Type "help all" for the list of all commands.
Type "help" followed by command name for full documentation.
Type "apropos word" to search for commands related to "word".
Type "apropos -v word" for full documentation of commands related to "word".
Command name abbreviations are allowed if unambiguous.
(gdb)
```

## 2. Monitor program execution

This chapter explains how to interrupt a program while it is running and proceed in the code to check and rewrite the contents of variables.
   

### 2-1. Interrupts the execution of the program

Start the program.
```
(gdb) run
Starting program: /home/root/debug/testprog
```
Then Ctrl+C to send a signal and stop execution.
```
^C
Program received signal SIGINT, Interrupt.
0x000055555555516e in main (argc=1, argv=0x7fffffffe3a8) at main.c:16
16          func1(num);
(gdb)
```

### 2-2. Continue program execution

To continue and resume an interrupted program, use the continue command.
```
(gdb) continue
Continuing.
```

### 2-3. Check the interruption points of the program

Use the list command to display the code around the point where the program was interrupted.
```
(gdb) list
11        int num = 1;
12        while(1){
13          if(num > 5000){
14            break;
15          }
16          func1(num);
17        }
18        return 0;
19      }
20
(gdb)
```

### 2-4. Execute the program code line by line

To execute one line of code at a time with the program suspended, use the next or step command.  
The next command advances the program one line, and if there is a function, it skips over the function call and executes the next code.
```
(gdb) next
16          func1(num);
(gdb) next
13          if(num > 5000){
```
The step command advances the program one line and moves inside the function, if any.
```
(gdb) step
16          func1(num);
(gdb) step
func1 (num=1) at main.c:4
4       {
(gdb) step
6         sum += num;
(gdb) step
7       }
(gdb) step
main (argc=1, argv=0x7fffffffe3a8) at main.c:13
13          if(num > 5000){
```

### 2-5. Check the contents of program variables

To check the contents of a variable, use the print command.
```
(gdb) print num
$1 = 1
(gdb)
```

### 2-6. Change program variables

To change the contents of a variable, use the set command.
```
(gdb) set num = 5001
(gdb)
```

### 2-7. Calls a specific function linked to the program

Use the call command to call any function.
```
(gdb) call func1(1)
(gdb) step
func1 (num=1) at main.c:4
4       {
(gdb)
```

### 2-8. Return from program functions

To terminate execution of a function in the middle of a function and return to the caller, use the finish command.  
The return value is also displayed when the command is executed.
```
(gdb) finish
Run till exit from #0  func1 (num=1) at main.c:6
main (argc=1, argv=0x7fffffffe3a8) at main.c:14
14          if(num > 5000){
Value returned is $3 = 287125699
(gdb)
```

## 3. Set breakpoints

This chapter describes breakpoints.
A breakpoint is a landmark point at which a program is interrupted at a specific line of code.  
Breakpoints can be set on arbitrary lines of code or functions, and debugging is possible after interrupting the program because of step command or print command.
   
### 3-1. Set breakpoints on specific lines

When set to line
If there is only one source file, specify only the number of lines.
```
(gdb) break 14
Breakpoint 1 at 0x1167: file main.c, line 14.
(gdb) run
Starting program: /home/root/debug/testprog

Breakpoint 1, main (argc=1, argv=0x7fffffffe3a8) at main.c:14
14          if(num > 5000){
(gdb)
```
If there are multiple source files, specify the file name and number of lines.
```
(gdb) break main.c:6
Breakpoint 1 at 0x1134: file main.c, line 6.
(gdb) run
Starting program: /home/root/debug/testprog

Breakpoint 1, func1 (num=1) at main.c:6
6         sum += num;
(gdb)
```

### 3-2. Set a breakpoint in the function

When setting to a function, specify the function name.
```
(gdb) break func1
Breakpoint 1 at 0x1129: file main.c, line 4.
(gdb) run
Starting program: /home/root/debug/testprog

Breakpoint 1, func1 (num=21845) at main.c:4
4       {
(gdb)
```

### 3-3. Obtain a list of breakpoints

Use the info breakpoints command to display a list of all currently set breakpoints.
```
(gdb) info breakpoint
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x0000555555555129 in func1 at main.c:4
        breakpoint already hit 1 time
(gdb)
```

### 3-4. Disable breakpoints

Use the disable command to disable the currently set breakpoint.  
The argument must be a breakpoint number to be obtained with info breakpoints.  
Disabled breakpoints will have an Enb of n. run execution will not stop at breakpoints.
```
(gdb) disable 1
(gdb) info breakpoints
Num     Type           Disp Enb Address            What
1       breakpoint     keep n   0x0000555555555129 in func1 at main.c:4
        breakpoint already hit 1 time
(gdb) run
Starting program: /home/root/debug/testprog

```

## 4. Set watchpoints

This chapter describes the watchpoints.  
A watchpoint is a marker point at which the program is interrupted when a variable is accessed.  
Watchpoints can be set on arbitrary variables, and debugging is possible after interrupting the program because of step command or print command.
   
### 4-1. Set watchpoints for variable writes

If you want to interrupt the program when writing to a specific variable, use the watch command.  
Since the variable to be specified must be in the current scope, it should be used in conjunction with breakpoints.

Set a breakpoint in the main function.
```
(gdb) break main
Breakpoint 1 at 0x114d: file main.c, line 11.
(gdb) run
Starting program: /home/root/debug/testprog

Breakpoint 1, main (argc=21845, argv=0x0) at main.c:11
11      {
```
Set watchpoints in the num variable.
```
(gdb) watch num
Hardware watchpoint 2: num
(gdb) continue
Continuing.
```
Stops when writing num variables.
```
Hardware watchpoint 2: num

Old value = 0
New value = 1
main (argc=1, argv=0x7fffffffe3a8) at main.c:14
14          if(num > 5000){
(gdb)
```

### 4-2. Set watchpoints for variable reads

If you want to interrupt the program when a specific variable is read, use the rwatch command.  
Usage notes are the same as for the watch command.

Set a breakpoint in the func1 function.
```
(gdb) break func1
Breakpoint 1 at 0x1129: file main.c, line 4.
(gdb) run
Starting program: /home/root/debug/testprog

Breakpoint 1, func1 (num=21845) at main.c:4
4       {
```
Stops when sum variable is read.
```
(gdb) rwatch sum
Hardware read watchpoint 2: sum
(gdb) continue
Continuing.

Hardware read watchpoint 2: sum

Value = 0
0x000055555555513a in func1 (num=1) at main.c:6
6         sum += num;
(gdb)
```

### 4-3. Set watchpoints for reading and writing variables

If you want to interrupt the program when either reading or writing a specific variable occurs, use the awatch command.  
Usage notes are the same as for the watch command.

Set a breakpoint in the func1 function.
```
(gdb) break func1
Breakpoint 1 at 0x1129: file main.c, line 4.
(gdb) run
Starting program: /home/root/debug/testprog

Breakpoint 1, func1 (num=21845) at main.c:4
warning: Source file is more recent than executable.
4       {
```
Stops when reading/writing sum variables.
```
(gdb) awatch sum
Hardware access (read/write) watchpoint 2: sum
(gdb) continue
Continuing.
```
Stop at readout.
```
Hardware access (read/write) watchpoint 2: sum

Value = 0
0x000055555555513a in func1 (num=1) at main.c:6
6         sum += num;
(gdb) continue
Continuing.
```
Stop when writing.
```
Hardware access (read/write) watchpoint 2: sum

Old value = 0
New value = 1
func1 (num=1) at main.c:7
7         return sum;
(gdb)
```

### 4-4. Obtain a list of watchpoints

Use the info breakpoints command to display a list of all currently set watchpoints.
```
(gdb) info breakpoints
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x0000555555555129 in func1 at main.c:4
        breakpoint already hit 1 time
2       acc watchpoint keep y                      sum
        breakpoint already hit 2 times
(gdb)
```

### 4-5. Disable watchpoints

Use the disable command to disable the currently set watchpoints.  
The argument must be a watchpoint number to be obtained with info breakpoints.  
Disabled watchpoints will have an Enb of n. run execution will not stop at the watchpoint.
```
(gdb) disable 2
(gdb) info breakpoints
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x0000555555555129 in func1 at main.c:4
        breakpoint already hit 1 time
2       acc watchpoint keep n                      sum
        breakpoint already hit 2 times
(gdb) continue
Continuing.

Breakpoint 1, func1 (num=1) at main.c:4
4       {
(gdb) continue
Continuing.

Breakpoint 1, func1 (num=1) at main.c:4
4       {
(gdb)
```

## 5. Execute call stack

This chapter explains how to analyze stacked frames.  
The execution status of the function can be checked by analyzing the stack frame.
   
### 5-1. Obtain a backtrace of the function

Use the backtrace command to obtain a backtrace, which is information about the caller of a function.
```
(gdb) backtrace
#0  func1 (num=1) at main.c:4
#1  0x000055555555517a in main (argc=1, argv=0x7fffffffe3a8) at main.c:17
(gdb)
```

### 5-2. Change the stack frame

To change the stack frame, use the frame command.  
Get the frame number with the backtrace command and use it as an argument.
```
(gdb) frame 1
#1  0x000055555555517a in main (argc=1, argv=0x7fffffffe3a8) at main.c:17
17          func1(num);
(gdb)
```

### 5-3. Analyze stack frames

Three commands to check the contents of the current stack frame are described.  
The info frame command outputs detailed information such as register values for the current stack frame.
```
(gdb) info frame
Stack level 1, frame at 0x7fffffffe2c0:
 rip = 0x55555555517a in main (main.c:17); saved rip = 0x7ffff7de4083
 caller of frame at 0x7fffffffe290
 source language c.
 Arglist at 0x7fffffffe288, args: argc=1, argv=0x7fffffffe3a8
 Locals at 0x7fffffffe288, Previous frame's sp is 0x7fffffffe2c0
 Saved registers:
  rbp at 0x7fffffffe2b0, rip at 0x7fffffffe2b8
(gdb)
```
The info locals command displays a list of local variables and their values for the current stack frame.
```
(gdb) info locals
num = 1
(gdb)
```
The info args command displays a list of arguments for the current stack frame.
```
(gdb) info args
argc = 1
argv = 0x7fffffffe3a8
(gdb)
```

## 6. Examples

### 6-1. Example 1 of infinite loop analysis

The source code should be the following.  
The value of num is added and the program terminates when it exceeds 5000.

```bash title="main.c"
#include <stdio.h>

int func1(int num)
{
   static int sum = 0;
   sum += num;
   return sum;
}

int main(int argc, char** argv)
{
   int num;
   num = 1;
   while(1){
      if(num > 5000){
         break;
      }
      func1(num);
   }
   return 0;
}
```
Compile the program with the -g option.  
When the program is executed, it falls into an infinite loop.
```
# ./testprog

```
Debugging with gdb.
```
# gdb testprog
...
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from testprog...
(gdb) run
Starting program: /home/root/debug/testprog

```
The program is interrupted by Ctrl+C because it falls into an infinite loop.
```
^C
Program received signal SIGINT, Interrupt.
func1 (num=1) at main.c:8
8       }
(gdb)
```
Advance the program with the next command.
```
(gdb) next
main (argc=1, argv=0x7fffffffe3a8) at main.c:15
15          if(num > 5000){
(gdb) next
18          func1(num);
(gdb) next
15          if(num > 5000){
(gdb) next
18          func1(num);
(gdb) next
15          if(num > 5000){
(gdb)
```
The same pattern is repeated, and this code does not update the value of num.  
Since the condition for exiting the loop is that num must exceed 5000, the fact that num did not change was the cause of the infinite loop.
```
      if(num > 5000){
         break;
      }
```
The func1 function adds the value of num to sum and returns it, so the expected behavior is to receive that value in the main function.
```
int func1(int num)
{
   static int sum = 0;
   sum += num;
   return sum;
}
```
```
while(1){
   if(num > 5000){
      break;
   }
   num = func1(num);
}
```

### 6-2. Example 2 of infinite loop analysis

The source code should be the following.  
This program stores 300 values calculated from a counter in an array of ints.

```bash title="main.c"
#include <stdio.h>

#define DATANUM 300

int getdata(unsigned char cnt)
{
  return (int)cnt*(cnt+cnt);
}

int main(int argc, char** argv)
{
  unsigned char cnt = 0;
  int data[DATANUM];

  for(cnt = 0;cnt < DATANUM;cnt++){
    data[cnt] = getdata(cnt);
  }

  return 0;
}
```
Compile the program with the -g option.   
When the program is executed, it falls into an infinite loop.
```
# ./testprog

```
Debugging with gdb.
```
# gdb testprog
...
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from testprog...
(gdb) run
Starting program: /home/root/debug/testprog

```
The program is interrupted by Ctrl+C because it falls into an infinite loop.
```
^C
Program received signal SIGINT, Interrupt.
getdata (cnt=106 'j') at main3.c:6
6       {
(gdb)
```
Since the loop does not end, we confirmed that if we advance the program with the step command until cnt reaches 300,  
which is the intended end condition, cnt returns to 0 in the middle of the loop.  
```
(gdb)step
getdata (cnt=255 '\377') at main3.c:6
6       {
(gdb)step
7         return (int)cnt*(cnt+cnt);
(gdb)step
8       }
(gdb)step
main (argc=1, argv=0x7fffffffe3a8) at main3.c:15
15        for(cnt = 0;cnt < DATANUM;cnt++){
(gdb)step
16          data[cnt] = getdata(cnt);
(gdb)step
getdata (cnt=0 '\000') at main3.c:6
6       {
(gdb)
```
The fact that cnt returns to 0 at 255 means that cnt cannot hold more than 256, so the counter variable may not be of the correct type.  
I checked the counter variable and found that cnt is defined as unsigned char (0-255).  
This would have resulted in an infinite loop because the loop termination condition of 300 would never be reached.
```
unsigned char cnt = 0;
```
The expected behavior is achieved by setting the type of cnt to unsigned short (0-65535).

### 6-3. Segmentation Fault Analysis Example

The source code should be the following.  
Allocates memory with malloc and initializes buffers.

```bash title="main.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
  char *buf;
  buf = malloc(1<<31);
  memset(buf,0x00,1024);
  return 0;
}
```
Compile the program with the -g option.  
Segmentation fault occurs when the program is executed.
```
# ./testprog
Segmentation fault (core dumped)
```
Debugging with gdb.
```
# gdb testprog
...
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from testprog...
(gdb) run
Starting program: /home/root/debug/testprog

Program received signal SIGSEGV, Segmentation fault.
__memset_avx2_unaligned_erms () at ../sysdeps/x86_64/multiarch/memset-vec-unaligned-erms.S:200
200     ../sysdeps/x86_64/multiarch/memset-vec-unaligned-erms.S: No such file or directory.
(gdb)
```
Check backtrace as SIGSEGV occurs.
```
(gdb) backtrace
#0  __memset_avx2_unaligned_erms () at ../sysdeps/x86_64/multiarch/memset-vec-unaligned-erms.S:200
#1  0x00005555555551a2 in main (argc=1, argv=0x7fffffffe3a8) at main.c:9
(gdb)
```
Segmentation fault occurs at line 9 of the code, so the frame is switched.
```
(gdb) frame 1
#1  0x00005555555551a2 in main (argc=1, argv=0x7fffffffe3a8) at main.c:9
9         memset(buf,0x00,1024);
(gdb)
```
Segmentation fault occurs in memset, so I check the buf contents and the buf address is NULL.
```
(gdb) print buf
$1 = 0x0
(gdb)
```
Once the program is finished, set a breakpoint in the main function and a watchpoint in buf.
```
(gdb) kill
Kill the program being debugged? (y or n) y
[Inferior 1 (process 47511) killed]
(gdb) break main
Breakpoint 1 at 0x555555555169: file main.c, line 6.
(gdb) run
Starting program: /home/pokyuser/hello_apl/testprog

Breakpoint 1, main (argc=21845, argv=0x0) at main.c:6
6       {
(gdb) awatch buf
Hardware access (read/write) watchpoint 2: buf
(gdb)
```
Checking the buf pointer change, it remains NULL even after allocating memory with malloc.
```
(gdb) continue
Continuing.

Hardware access (read/write) watchpoint 2: buf

Value = 0x0
main (argc=1, argv=0x7fffffffe3a8) at main.c:9
9         memset(buf,0x00,1024);
(gdb) continue
Continuing.

Hardware access (read/write) watchpoint 2: buf

Value = 0x0
0x0000555555555190 in main (argc=1, argv=0x7fffffffe3a8) at main.c:9
9         memset(buf,0x00,1024);
(gdb) continue
Continuing.

Program received signal SIGSEGV, Segmentation fault.
__memset_avx2_unaligned_erms () at ../sysdeps/x86_64/multiarch/memset-vec-unaligned-erms.S:200
200     ../sysdeps/x86_64/multiarch/memset-vec-unaligned-erms.S: No such file or directory.
(gdb)
```
Check the malloc function to confirm that malloc is specified to return NULL if memory cannot be allocated.
```
buf = malloc(1<<31);
```
The memory size being allocated by malloc was 4 GB, and NULL was returned because the huge size was not allocated.  
Since the size set in memset is 1024 bytes, the problem can be solved by either setting the size to be acquired by malloc  
to 1024 as well or checking the return value of malloc, and if it is NULL, do not access it, etc.
