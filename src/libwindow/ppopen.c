

/******************************************************************************
Copyright 1990 by the Massachusetts Institute of Technology.  All 
rights reserved.

Developed by the Visible Language Workshop at the Media Laboratory, MIT, 
Cambridge, Massachusetts, with support from Hewlett Packard, DARPA, and Nynex.

For use by Suguru Ishizaki.  
This distribution is approved by Nicholas Negroponte, Director of 
the Media Laboratory, MIT.

Permission to use, copy, or modify these programs and their 
documentation for educational and research purposes only and 
without fee is hereby granted, provided that this copyright notice 
appears on all copies and supporting documentation.  For any other 
uses of this software, in original or modified form, including but not 
limited to distribution in whole or in part, specific prior permission 
must be obtained from MIT.  These programs shall not be used, 
rewritten, or adapted as the basis of a commercial software or 
hardware product without first obtaining appropriate licenses from 
MIT.  MIT makes no representations about the suitability of this 
software for any purpose.  It is provided "as is" without express or 
implied warranty."
******************************************************************************/






/* ppopen.c
*	utilities for reading and writing processes
*
*	Steve Pieper	
*	pieper@media-lab.media.mit.edu
*/
#include <stdio.h>

extern FILE	*fdopen();

#define READ	0
#define WRITE	1

#define VFORK
#ifdef VFORK
# define fork vfork
#endif 

fppopen(fps, argc, argv)
	FILE	**fps;
	int	argc;
	char	**argv;
{
	int	fds[2];
	int	childpid;

	if ( (childpid = ppopen (fds, argc, argv)) == -1 )
	{	perror ("fppopen: ppopen failed");
		return (-1);
	} else
	{	fps[READ] = fdopen (fds[READ], "r");
		fps[WRITE] = fdopen (fds[WRITE], "w");
		if ( !fps[READ] || !fps[WRITE] ) 
		{	perror ("fppopen: fdopen failed");
			return (-1);
		}
	}
	return (childpid);
}

ppopen(fds, argc, argv)
	int	*fds;
	int	argc;
	char	**argv;
{
	int pid;
	int	ptoc[2], ctop[2];

	 /* create two pipes */
	if (pipe (ptoc) == -1)
	{	perror ("pipe failed");
		return (-1);
	}
	if (pipe (ctop) == -1)
	{	perror ("pipe failed");
		return (-1);
	}
	switch (pid = fork())
	{	case (0): /* child */
		{	close(0); /* close stdin  */
			dup (ptoc[READ]);
			close(1);	/* close stdout	*/
			dup (ctop[WRITE]);
			argv[argc] = NULL; /* for execv */
			if (execv (*argv, argv+1) == -1)
			{	perror ("ppopen child: exec failed");
				exit (-1);
			}
			break;
		}
		case (-1): /* error */
		{	perror ("ppopen: fork failed");
			return (-1);
		}
		default: /* parent */
		{	fds[READ] = ctop[READ];
			fds[WRITE] = ptoc[WRITE];
			return (pid);
		}
	}
}


csh_fppopen(fps, command)
	FILE	**fps;
	char	*command;
{
	int	fds[2];
	int	childpid;

	if ( (childpid = csh_ppopen (fds, command)) == -1 )
	{	perror ("csh_fppopen: ppopen failed");
		return (-1);
	} else
	{	fps[READ] = fdopen (fds[READ], "r");
		fps[WRITE] = fdopen (fds[WRITE], "w");
		if ( !fps[READ] || !fps[WRITE] ) 
		{	perror ("csh_fppopen: fdopen failed");
			return (-1);
		}
	}
	return (childpid);
}



csh_ppopen(fds, command)
	int	*fds;
	char	*command;
{
	int pid;
	int	ptoc[2], ctop[2];

	 /* create two pipes */
	if (pipe (ptoc) == -1)
	{	perror ("pipe failed");
		return (-1);
	}
	if (pipe (ctop) == -1)
	{	perror ("pipe failed");
		return (-1);
	}
	switch (pid = fork())
	{	case (0): /* child */
		{	close(0); /* close stdin  */
			dup (ptoc[READ]);
			close(1);	/* close stdout	*/
			dup (ctop[WRITE]);
			if (execl ("/bin/csh", "csh", "-c", command, NULL) == -1)
			{	perror ("csh_ppopen child: exec failed");
				exit (-1);
			}
			break;
		}
		case (-1): /* error */
		{	perror ("csh_ppopen: fork failed");
			return (-1);
		}
		default: /* parent */
		{	fds[READ] = ctop[READ];
			fds[WRITE] = ptoc[WRITE];
			return (pid);
		}
	}
}

#ifdef HERES_SOME_DOCUMENTATION

Sure, it's easy.  I took the ideas of popen and exended them to two pipes.
The following code has many ways of accessing the same functionality -- which
you use really depends on which arguments are the easiest to provied and
what you want to do with the resulting pipes.

The prototype call is
	ppopen(fds, argc, argv)
		int     *fds;
		int     argc;
		char    **argv;

where fds is an array of two ints to store the file descriptors of the pipes,
and argv contains the program name and the arguments to the program
a la main().

A variation is
	fppopen(fps, argc, argv)
		FILE    **fps;
		int     argc;
		char    **argv;
which provides you with file pointers instead of file descriptors, by calling
the fdopen() system call.  It just makes things a little easier later on.


It's easier to specify the command as a csh command which means it is easier
to use the commands
	csh_ppopen(fds, command)
		int     *fds;
		char    *command;
and
	csh_fppopen(fps, command)
		FILE    **fps;
		char    *command;
which accept a string which you would otherwise type at the csh prompt
and otherwise act like their non-csh_ cousins.  These are a little less
efficient, since they have to set up a csh which reads your .cshrc and
what not.  Normally the process you open stays open for quite a while while
you talk with it, so the extra overhead at startup is negligable.

As we mentioned, the command can start with remsh in order to execute the
command on another machine.  The pipe communication is still surprisingly
fast in this mode, and I find it very handy for building distributed
applications.


Good Luck,
Stevie

#endif
