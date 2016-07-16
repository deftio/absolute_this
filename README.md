# Absolute..This   A few thought  bitwiddling absolute values
	
(c) 2000  M. A. Chatterjee,   < deftio [at] deftio [dot] com >  

release notes:  
* cleaned up comments 2012
* changed to markdown 2016  



## About this code and what it does

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

I'm publishing this as a way to preserve some thought experiments rather than as a 
true open-source "library" of any kind.  Many times I've run accross some
little brainbender of code someone wrote and thought "hmmm cute" and soe here
is a small contribution to such thinking. 

Cheers-
MC 


## Building the Code

See C language code "absolute_this.c"
command line compile via gcc or equivalent.
e.g. in gcc
```
#build it
gcc absolute_this.c -lm -o abs_this

#run it
./abs_this

Note the code uses stdio.h so your platform will need to support printf like 
statements.


```


## License

Copyright (c) 2001-2016, M. A. Chatterjee < deftio at deftio dot com >
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.