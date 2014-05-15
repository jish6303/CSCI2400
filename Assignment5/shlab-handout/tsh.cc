// 
// tsh - A tiny shell program with job control
// 
// <Put your name and login ID here>
//

using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string>

#include "globals.h"
#include "jobs.h"
#include "helper-routines.h"

//
// Needed global variable definitions
//

static char prompt[] = "tsh> ";
int verbose = 0;

//
// You need to implement the functions eval, builtin_cmd, do_bgfg,
// waitfg, sigchld_handler, sigstp_handler, sigint_handler
//
// The code below provides the "prototypes" for those functions
// so that earlier code can refer to them. You need to fill in the
// function bodies below.
// 

void eval(char *cmdline);
int builtin_cmd(char **argv);
void do_bgfg(char **argv);
void waitfg(pid_t pid);

void sigchld_handler(int sig);
void sigtstp_handler(int sig);
void sigint_handler(int sig);

//
// main - The shell's main routine 
//
int main(int argc, char **argv) 
{
  int emit_prompt = 1; // emit prompt (default)

  //
  // Redirect stderr to stdout (so that driver will get all output
  // on the pipe connected to stdout)
  //
  dup2(1, 2);

  /* Parse the command line */
  char c;
  while ((c = getopt(argc, argv, "hvp")) != EOF) {
    switch (c) {
    case 'h':             // print help message
      usage();
      break;
    case 'v':             // emit additional diagnostic info
      verbose = 1;
      break;
    case 'p':             // don't print a prompt
      emit_prompt = 0;  // handy for automatic testing
      break;
    default:
      usage();
    }
  }

  //
  // Install the signal handlers
  //

  //
  // These are the ones you will need to implement
  //
  Signal(SIGINT,  sigint_handler);   // ctrl-c
  Signal(SIGTSTP, sigtstp_handler);  // ctrl-z
  Signal(SIGCHLD, sigchld_handler);  // Terminated or stopped child

  //
  // This one provides a clean way to kill the shell
  //
  Signal(SIGQUIT, sigquit_handler); 

  //
  // Initialize the job list
  //
  initjobs(jobs);

  //
  // Execute the shell's read/eval loop
  //
  for(;;) {
    //
    // Read command line
    //
    if (emit_prompt) {
      printf("%s", prompt);
      fflush(stdout);
    }

    char cmdline[MAXLINE];

    if ((fgets(cmdline, MAXLINE, stdin) == NULL) && ferror(stdin)) {
      app_error("fgets error");
    }
    //
    // End of file? (did user type ctrl-d?)
    //
    if (feof(stdin)) {
      fflush(stdout);
      exit(0);
    }

    //
    // Evaluate command line
    //
    eval(cmdline);
    fflush(stdout);
    fflush(stdout);
  } 

  exit(0); //control never reaches here
}
  
/////////////////////////////////////////////////////////////////////////////
//
// eval - Evaluate the command line that the user has just typed in
// 
// If the user has requested a built-in command (quit, jobs, bg or fg)
// then execute it immediately. Otherwise, fork a child process and
// run the job in the context of the child. If the job is running in
// the foreground, wait for it to terminate and then return.  Note:
// each child process must have a unique process group ID so that our
// background children don't receive SIGINT (SIGTSTP) from the kernel
// when we type ctrl-c (ctrl-z) at the keyboard.
//
void eval(char *cmdline) {
  /* Parse command line */
  //
  // The 'argv' vector is filled in by the parseline
  // routine below. It provides the arguments needed
  // for the execve() routine, which you'll need to
  // use below to launch a process.
  //
	char *argv[MAXARGS];
	pid_t pid;															// local variable called "pid" to store process id in.
	
  //
  // The 'bg' variable is TRUE if the job should run
  // in background mode or FALSE if it should run in FG
  //
	int bg = parseline(cmdline, argv); 
	
	if(argv[0] == NULL)  
		return;   /* ignore empty lines */
		
	// call builtin_cmd function: "builtin_cmd(argv);", will return a 0 
	// if the command is not built in, so put in an if statement so that 
	// if it is a built in command it will run otherwise it will enter 
	// the if statement and get executed properly.
	if(!builtin_cmd(argv)) {											// builtin_cmd will return 0 if the command is not built in, so use an if statement to get it to either run the built in command, or do the right thing 
	                                                                    //run the built in command, or do the right thing if it's not built in, and that's to run the program as a command and execute 
		//pid = fork();													// call fork once and it returns twice. It clones the current shell, copies to a different thread, and then both execute in parallel 
		                                                                //(really one at a time, but you can think of it as in parallel. Child thread (new) always returns 0. The old fork returns the process id of the child
																		// if in the child, run the program
		if((pid = fork()) == 0) {										// will only be executed if we're in the "new" child thread. if it's not a built in command then run the command as a program and execute..
			// This will only do two things - either execute the child or if error, print message and exit.
			// arguments: execve(argv[0] = execve runs the program, the program you want to run. 
			// Fork created a clone of the running thread. Execve takes 
			// the thread and runs it as a fresh call. 
			// argv = the arguments for that program. 
			// environ = the environmental variables.
			if(execve(argv[0], argv, environ) < 0) {					// if we're in the child we want to run the program. If there's an error it will return something less than 0, so you'll want to print the most common error.
				printf("%s: Command not found.\n", argv[0]);			// if a problem then print out the error message and exit.
				exit(0);												// exit(0) and child thread goes away. We don't need an else statement because that code will never be reached by the child any way.
			} 															// the child thread will never get past this line, so we don't need an else statement.
		}																// if it's a foreground (fg) job, the parent will wait for the code to finish executing.
		//
		//code from this point on will be executed by the parent, not the child
		//
		
																		// if its a fg job, then the parent needs to sit and wait for it to finish.
																		// Parent waits for foreground job to finish.
																		// (waitpid(pid, &status, 0), can do lots of things!
																		// "waitpid": it'll wait, pause the thread that calls it until the 
																		// process specified that its process id either stopped or 
																		// terminated. The "0" is the place where lots of options can be 
																		// passed to the function waitpid."&status" is the way information 
																		// can be reported what happened while it was waiting. When int status 
																		// is called it writes the info to &status (it's a way for functions 
																		// to return 2 things). "pid" is a number, can be looked up.
																		// Process ids are always positive. waitpid uses negative values to 
																		// encode special meaning. If pid > 0, then it waits for the specific process to stop or terminate and then it'll resume.
																		// if pid = 0, then it will wait for any child that's in the same group as the calling process to stop or terminate. 
																		// if -1 then waits for any child process of the process 
																		// to stop or terminate. If pid < -1, then it will wait for any process in that 
																		// group id to stop or terminate
																		// if you want it to wait until any process in group 5 to stop or terminate, 
																		// you'd put in a -5 in place of pid. Think of the (-) sign to be a marker, not a negative.
																		// if (waitpid(pid, &status, 0) < 0) 
																		// Where the "0" is, you'll want to look in the header file for the different
																		// things you can implement here. For instance, you'll want to change it to
																		// (waitpid(pid, &status, OPTION_1 | OPTION_TWO), combine them with a series
																		// of bitwise "or"s.
		if(!bg) {
			int status;
			//if (waitpid(pid, &status, OPTION_1 | OPTION_TWO) < 0) { 	//standard error checking code)
			if (waitpid(pid, &status, 0) < 0) {
				unix_error("waitfg: waitpid error");
			}
		}else {   														// if it's not a background job
			printf("%d %s", pid, cmdline); 								// print out the pid and the command line used to generate it.
		}	
		
	 
	}	
	// from here you will implement fg, bg, jobs
  return;
}


////////////////////////////////////////////////////////////////////////
//
// builtin_cmd - If the user has typed a built-in command then execute
// it immediately. The command name would be in argv[0] and
// is a C string. We've cast this to a C++ string type to simplify
// string comparisons; however, the do_bgfg routine will need 
// to use the argv array as well to look for a job number.
int builtin_cmd(char **argv) { 											// If cmd is quit, then exits the terminal																	// why not use argv == "quit" ?
	string cmd(argv[0]);												// because they are not the same types. argv is a
	if(cmd == "quit") {													// character pointer and "quit" is a string type.
		exit(0);														// because they are differnt types, this would 
	}																	// always return false even when "quit" is true.  
	return 0;     /* not a builtin command */							// string cmd(argv[0]) sets cmd to a string object 
}																		// which is the same type as "quit".
																		
																		

////////////////////////////////////////////////////////////////////////
//
// do_bgfg - Execute the builtin bg and fg commands
//
void do_bgfg(char **argv) 
{
  struct job_t *jobp=NULL;
    
  /* Ignore command if no argument */
  if (argv[1] == NULL) {
    printf("%s command requires PID or %%jobid argument\n", argv[0]);
    return;
  }
    
  /* Parse the required PID or %JID arg */
  if (isdigit(argv[1][0])) {
    pid_t pid = atoi(argv[1]);
    if (!(jobp = getjobpid(jobs, pid))) {
      printf("(%d): No such process\n", pid);
      return;
    }
  }
  else if (argv[1][0] == '%') {
    int jid = atoi(&argv[1][1]);
    if (!(jobp = getjobjid(jobs, jid))) {
      printf("%s: No such job\n", argv[1]);
      return;
    }
  }	    
  else {
    printf("%s: argument must be a PID or %%jobid\n", argv[0]);
    return;
  }

  //
  // You need to complete rest. At this point,
  // the variable 'jobp' is the job pointer
  // for the job ID specified as an argument.
  //
  // Your actions will depend on the specified command
  // so we've converted argv[0] to a string (cmd) for
  // your benefit.
  //
  string cmd(argv[0]);

  return;
}

/////////////////////////////////////////////////////////////////////////////
//
// waitfg - Block until process pid is no longer the foreground process
//
void waitfg(pid_t pid)
{
  return;
}

/////////////////////////////////////////////////////////////////////////////
//
// Signal handlers
//


/////////////////////////////////////////////////////////////////////////////
//
// sigchld_handler - The kernel sends a SIGCHLD to the shell whenever
//     a child job terminates (becomes a zombie), or stops because it
//     received a SIGSTOP or SIGTSTP signal. The handler reaps all
//     available zombie children, but doesn't wait for any other
//     currently running children to terminate.  
//
void sigchld_handler(int sig) 
{
  printf("SIGCHLD handler called.\n");
}

/////////////////////////////////////////////////////////////////////////////
//
// sigint_handler - The kernel sends a SIGINT to the shell whenver the
//    user types ctrl-c at the keyboard.  Catch it and send it along
//    to the foreground job.  
//
void sigint_handler(int sig) 
{
  printf("SIGINT handler called.\n");
}

/////////////////////////////////////////////////////////////////////////////
//
// sigtstp_handler - The kernel sends a SIGTSTP to the shell whenever
//     the user types ctrl-z at the keyboard. Catch it and suspend the
//     foreground job by sending it a SIGTSTP.  
//
void sigtstp_handler(int sig) 
{
  printf("SIGTSTP handler called.\n");
}

/*********************
 * End signal handlers
 *********************/



