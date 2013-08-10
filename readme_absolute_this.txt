Read Me file for bitwiddling absolute value musings.
	
@file readme_absolute_this.txt - musings on absolute values
@copy Copyright (C) <2000>  <M. A. Chatterjee>, cleaned up comments 2012
@author M A Chatterjee <deftio [at] deftio [dot] com>
 

This software is provided 'as-is', without any express or implied
 *	warranty. In no event will the authors be held liable for any damages
 *	arising from the use of this software.
 *
 *	Permission is granted to anyone to use this software for any purpose,
 *	including commercial applications, and to alter it and redistribute it
 *	freely, subject to the following restrictions:
 *
 *	1. The origin of this software must not be misrepresented; you must not
 *	claim that you wrote the original software. If you use this software
 *	in a product, an acknowledgment in the product documentation would be
 *	appreciated but is not required.
 *
 *	2. Altered source versions must be plainly marked as such, and must not be
 *	misrepresented as being the original software.
 *
 *	3. This notice may not be removed or altered from any source
 *	distribution.

#=========================================================================
About this code and what it does

Actually this code does .. virtually nothing and is more of a historical
exploration of different compiler/processor issues I was investigating in the
mid 1990s.  Both embedded (e.g. ARM, mcore, 68xxx) and desktop (PowerPC, 
80x86) compilers were being target for work I was doing in speech and 
handwriting recognition.  Many of the embedded platforms were running in
the low single digit to low 10s of MHz.  

These musings on bit shifting and absolute values come from the mid 1990s
when processors could have pipeline stalls and I was experimenting with 
ways to avoid cache/pipeline misses on branch predictors.

This started a subset line of thinking on measuring branch penalties 
vs statements.  Some processors then didn't have hardware absolute 
value (ABS) instructions so with a little fun the macros below were created.
I make no statements that they were *useful* and I looked at these and 
other statement constructs to study	effects of branch-miss, cache fill 
issues for a specific problem I was dealing with at the time which
which I've since forgotten.  

Those of you coming from a Java background, bear in mind the difference in 
Java between >> and >>> as here in C >> means arithmetic shift (e.g. 
if there is a 1 in the high order bit then the register 1 fills
not zero-fills).

I'm publishing this as a way to preserve some experiments rather than as a 
true opensource "library" of any kind.  Many times I've run accross some
little brainbender of code someone wrote and thought "hmmm cute" and soe here
is a small contribution to such thinking. 

Cheers-
MC 
#=========================================================================
#Building the code:

See C language code "absolute_this.c"
command line compile via gcc or equivalent.
e.g. in gcc

#build it
gcc absolute_this.c -lm -o abs_this

#run it
./abs_this

Note the code uses stdio.h so your platform will need to support printf like 
statements.

