/**
 *	@file absolute_this.c - musings on bit manipulation, expressions, and 
 *   absolute value options
 *
 *	@copy Copyright (C) <2000>  <M. A. Chatterjee>, cleaned up comments 2012
 *  	
 *  @author M A Chatterjee <deftio [at] deftio [dot] com>
 *
 *	These musings on bit shifting and absolute values come from the mid 1990s
 *  when processors could have pipeline stalls and I was experimenting with 
 *  ways to avoid cache/pipeline misses on branch predictors.
 *  This started a subset line of thinking on measuring branch penalties 
 *  vs statements.  Some processors then didn't have hardware absolute 
 *  value (ABS) instructions so with a little fun the macros below were created.
 *  I make no statements that they were *useful* and I looked at these and 
 *  other statement constructs to study	effects of branch-miss, cache fill 
 *  issues for a specific problem I was dealing with at the time which
 *  which I've since forgotten.  
 *
 *	Those of you coming from a Java background, bear in mind the difference in 
 *  Java between >> and >>> as here in C >> means arithmetic shift (e.g. 
 *  if there is a 1 in the high order bit then the register 1 fills
 *  not zero-fills).
 *
 *	This software is provided 'as-is', without any express or implied
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
 *
 */
#include <stdio.h>
#include <stdlib.h>

/*
 * change to non-zero value to run the full test
 */
#define RUN_FULL_TEST (0)

/*
 This file heavily uses C language macros so ...
 About all those paranthesis (below)... remember that in C/C++ macros the passed 
 parameter is true string replacement so it can be a complex expression and 
 cannot be assumed to just be just a simple atomic type..
 If a complex expression is expanded then this can result in funny happenings 
 if that expression relies or order-of-precedence rules:
 eg if x = -5 then wrapping it in all the parans (x) below is unncessary 
 but if x is -3<<4+1 then the macros
 below may 'misbehave' without parenthesis forcing precedence
 */

/****************************************************************************
 The commmon way and the way we'll use for reference purposes.
 but ... in some older compilers -x is a multiply by negative 1 (to be avoided)
 For those less familiar with the "?" operater in C in this context the 
 this operator is equavalent special type if if() statement which combines a
 conditional test and an assignment.  
 
 if (x < 0) // ?(x<0)
 {	  
 	x = -x; // -(x)
 }
 else       // :
 {
 	x = x;  // (x)
 }
 
 */
#define  soft_abs0(x)  ((x)<0?-(x):(x))

/****************************************************************************
 The normal way but with 2's complement inversion (often compilers generate 
 equivalent code for integer operands). 
 This __does not__ work for float or doubles or C++ classes (unless truly 
 unusual operator overloading has been supplied)
 */
#define  soft_abs1(x) (((x)>=0)?(x):(~(x))+1)
#define  soft_abs2(x) (((x)>=0)?(x):~((x)-1))

/****************************************************************************
 but what if we could get rid of the conditional "if" or "?:" operators?  
 What if the whole thing was just statements? (for byte/short/int/long types)

 A few notes explaining the thinking below: 
 1. Now the fun part...  sizeof() returns the size in bytes 
 2. ">>" 1-fills if the number is negative 
 3. The "3"s you see below are to convert from bytes to bits so...
 
 */
 
#define  soft_abs3(x) ((((x)>>((((signed)sizeof(x))<<3)-1))^(x))+(((x)>>((((signed)sizeof(x))<<3)-1))&0x1))

/****************************************************************************
 Then theres exploiting that high bit to be come either [-1,0] which is 
 linearly scaled to be come [-1,1] the result of which can be used to 
 make (-x) to (x) and (x) to (x) giving the following but introducting 
 potentially introducing multiplies (I say "potentially" because an aggressive
 optimizing compiler may figure out that -1 vs 0 and introduce more
 efficient code but I wouldn't count on it).  But its provided here for 
 amusement of bit twiddlery rather than to abused in to actual code :)
 */
 
#define  soft_abs4(x)  (x*((((x)>>((((signed)sizeof(x))<<3)-1))*2)+1))

/****************************************************************************
 Which can become this if we '&' away the bottom bit of -1 to make it -1 2. 
 We could have accomplished the same thing with a shift e.g. <<1
 */
 
#define  soft_abs5(x)  (x*((((x)>>((((signed)sizeof(x))<<3)-1))&(~1))+1))

/****************************************************************************
 And for readbility a little less crazyiness here.  
 SN(x) produces the sign of (x) where 
 SN(negative_num) == -1 
 SN(0) 
 SN(postive_num) == 0
 */
 
#define  SN(x) ((x)>>((((signed)sizeof(x))<<3)-1))
#define  soft_abs6(x)  (x*((SN(x)*2)+1))
#define  soft_abs7(x)  (x*((SN(x)&(~1))+1))

#define NUMABS	(8)
void main (void)
{
	
	int k;
	int e[NUMABS];
	unsigned long long tot=0;
	
	printf("absolute this!\n");
	printf("a few examples ... \n");
	for (k=0; k< 6; k++)
	{
		int ii=k * (-3)*(ii+1); /* some randomish pos and neg integers */
		if (k>2)
			ii*=34543;
		printf("soft_abs0(%d)=%d\n",ii,soft_abs0(ii));
		printf("soft_abs1(%d)=%d\n",ii,soft_abs1(ii));		
		printf("soft_abs2(%d)=%d\n",ii,soft_abs2(ii));
		printf("soft_abs3(%d)=%d\n",ii,soft_abs3(ii));
		printf("soft_abs4(%d)=%d\n",ii,soft_abs4(ii));
		printf("soft_abs5(%d)=%d\n",ii,soft_abs5(ii));
		printf("soft_abs6(%d)=%d\n",ii,soft_abs6(ii));
		printf("soft_abs7(%d)=%d\n",ii,soft_abs7(ii));
		printf("\n");
	}
	

	/*
	for those who wish to exhaustively test enable the code below...
	the printfs are for a simple progress bar.
	*/
  	if (RUN_FULL_TEST)
	{
		for (k=0; k<NUMABS; k++)
			e[k]=0;
			
		for (k=-(1<<31); k<(int)((long)(1<<31)-1); k++)
		{
			tot++;
			if ((k&0x7ffffff) == 0x7ffffff) 
			{
				printf("*");
				fflush(stdout); 
			}
			e[0]+=soft_abs0(k)!=soft_abs0(k)?1:0;
			e[1]+=soft_abs0(k)!=soft_abs1(k)?1:0;
			e[2]+=soft_abs0(k)!=soft_abs2(k)?1:0;
			e[3]+=soft_abs0(k)!=soft_abs3(k)?1:0;
			e[4]+=soft_abs0(k)!=soft_abs4(k)?1:0;
			e[5]+=soft_abs0(k)!=soft_abs5(k)?1:0;
			e[6]+=soft_abs0(k)!=soft_abs6(k)?1:0;
			e[7]+=soft_abs0(k)!=soft_abs7(k)?1:0;
		}
		printf("\n");
		for (k=0; k<NUMABS; k++)
			printf("total errors for soft_abs%d():%d\n",k,e[k]);
		
		printf("total tested::%lld\n",tot);
	}
	printf("\n");
}
