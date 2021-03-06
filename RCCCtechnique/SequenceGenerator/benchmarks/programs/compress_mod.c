
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

#ifdef DO_TRACING   /* ON PC */

#include <stdio.h>
#define TRACE(x) trace((x))
#undef TEST                   /* finished testing! */


#else               /* ON TARGET */

#define TRACE(x)
#undef TEST

#endif


#define BUFFERSIZE	50
#define IN_COUNT        BUFFERSIZE

#define HSIZE	257		/* 95% occupancy */
#define BITS 16
#define INIT_BITS 9			/* initial number of bits/code */



/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/

#define	min(a,b)	((a>b) ? b : a)



#define SACREDMEM	0


# define USERMEM 	450000	/* default user memory */

#ifdef interdata		/* (Perkin-Elmer) */
#define SIGNED_COMPARE_SLOW	/* signed compare is slower than unsigned */
#endif


#define PBITS	16
#define BITS 16
#define HSIZE	257		/* 95% occupancy was 69001 */


#if BITS > 15
typedef long int	code_int;
#else
typedef int		code_int;
#endif

#ifdef SIGNED_COMPARE_SLOW
typedef unsigned long int count_int;
typedef unsigned short int count_short;
#else
typedef long int	  count_int;
#endif

typedef	unsigned char	char_type;

/* Defines for third byte of header */
#define BIT_MASK	0x1f
#define BLOCK_MASK	0x80

int n_bits;				/* number of bits/code */
int maxbits = BITS;			/* user settable max # bits/code */
code_int maxcode;			/* maximum code, given n_bits */
#if BITS > 15
code_int maxmaxcode = 1L << BITS;	/* should NEVER generate this code */
#else
code_int maxmaxcode = 1 << BITS;	/* should NEVER generate this code */
#endif

# define MAXCODE(n_bits)	((1 << (n_bits)) - 1)


#define htabof(i)	htab[i]
#define codetabof(i)	codetab[i]

code_int hsize = HSIZE;			/* for dynamic table sizing */
count_int fsize;



#define tab_prefixof(i)	codetabof(i)
#define tab_suffixof(i)	((char_type *)(htab))[i]
#define de_stack		((char_type *)&tab_suffixof(1<<BITS))

code_int free_ent = 0;			/* first unused entry */
int exit_stat = 0;

int nomagic = 1;	/* Use a 3-byte magic number header, unless old file */
int zcat_flg = 0;	/* Write output on stdout, suppress messages */
int quiet = 1;		/* don't tell me about compression */


int block_compress = BLOCK_MASK;
int clear_flg = 0;
long int ratio = 0;
#define CHECK_GAP 10000	/* ratio check interval */
count_int checkpoint = CHECK_GAP;

#define FIRST	257	/* first free entry */
#define	CLEAR	256	/* table clear output code */

int force = 0;
char ofname [100];
int InCnt;
int apsim_InCnt;
unsigned char *InBuff;
unsigned char *OutBuff;

char orig_text_buffer[BUFFERSIZE];
char comp_text_buffer[BUFFERSIZE+5];

count_int htab [HSIZE];
unsigned short codetab [HSIZE];
char buf[BITS];



/*---------------------------------------------------- */
/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/


/*----------------------------------------- Prototypes */
void initbuffer(void);
void compress(void);
void cl_hash(count_int hsize);		/* reset code table */
unsigned int getbyte(void);
void putbyte( char c );
void cl_block (void);
void output( code_int code );
void writebytes( char *buf, int n );




void initbuffer(void)
{
   int seed = 1;
   int i;
   int tabort;

   for (i = 0 ; (i < BUFFERSIZE) ; i++) {
      /* Generates random integers between 0 and 8095 */
      tabort = i;
      seed = ((seed * 133) + 81) % 8095;

      orig_text_buffer[i] = seed % 256;
   }
}



static int offset;
long int in_count = 1;			/* length of input */
long int bytes_out;			/* length of compressed output */
long int out_count = 0;			/* # of codes output (for debugging) */


void compress(void)
{
   register long fcode;
   register code_int i = 0;
   register int c;
   register code_int ent;
   register int disp;
   register code_int hsize_reg;
   register int hshift;


   offset = 0;
   bytes_out = 3;		/* includes 3-byte header mojo */
   out_count = 0;
   clear_flg = 0;
   ratio = 0;
   in_count = 1;
   checkpoint = CHECK_GAP;
   maxcode = MAXCODE(n_bits = INIT_BITS);
   //free_ent = ((block_compress) ? (FIRST) : (256) );
      if(block_compress)
{
free_ent = FIRST;
}
else
{
free_ent = 256;
}
   ent = getbyte ();

   hshift = 0;
   for ( fcode = (long) hsize;  fcode < 65536L ; fcode *= 2L )
   {
      hshift++;
   }

   hshift = 8 - hshift;		/* set hash code range bound */

   hsize_reg = hsize;
   cl_hash( (count_int) hsize_reg);		/* clear hash table */


   while ( InCnt > 0 )           /* apsim_loop 11 0 */
   {
      int apsim_bound111 = 0;

      c = getbyte();   /* decrements InCnt */

      in_count++;
      fcode = (long) (((long) c << maxbits) + ent);
      i = ((c << hshift) ^ ent);	/* xor hashing */

      if ( htabof (i) == fcode ) {
         ent = codetabof (i);
         continue;
      } else if ( (long)htabof (i) < 0 ) { /* empty slot */
         goto nomatch;
      }


      disp = hsize_reg - i;		/* secondary hash (after G. Knott) */
      if ( i == 0 ) {
         disp = 1;
      }

probe:

      if ( (i -= disp) < 0 ) {  /* apsim_loop 111 11 */
         i += hsize_reg;
      }

      if ( htabof (i) == fcode ) {
         ent = codetabof (i);
         continue;
      }
 
if ( (long)htabof (i) > 0 && (++apsim_bound111 < in_count) )
         goto probe;
nomatch:

      out_count++;
      ent = c;
      if ( free_ent < maxmaxcode ) {
         codetabof (i) = free_ent++;	        /* apsim_unknown codetab */
         htabof (i) = fcode;			/* apsim_unknown htab */
      } else if ( ((count_int)in_count >= checkpoint) && (block_compress) ) {
         cl_block ();
      }

   }
   if(bytes_out > in_count) { /* exit(2) if no savings */
      exit_stat = 2;
   }
   return;
}


void cl_block (void)		/* table clear for block compress */
{
   register long int rat;

   checkpoint = in_count + CHECK_GAP;

   if(in_count > 0x007fffff) {	/* shift will overflow */

      rat = bytes_out >> 8;
      if(rat == 0) {		/* Don't divide by zero */
         rat = 0x7fffffff;
      } else {
         rat = in_count / rat;
      }
   } else {
      rat = (in_count << 8) / bytes_out;	/* 8 fractional bits */
   }
   if ( rat > ratio ) {
      ratio = rat;
   } else {
      ratio = 0;
      cl_hash ( (count_int) hsize );


      free_ent = FIRST;
      clear_flg = 1;
      output ( (code_int) CLEAR );
   }
}

void cl_hash(count_int hsize)		/* reset code table */
{
   register count_int *htab_p = htab+hsize;
   register long i;
   register long m1 = -1;

   i = hsize - 16;
   do {				/* might use Sys V memset(3) here */

      *(htab_p-16) = m1;
      *(htab_p-15) = m1;
      *(htab_p-14) = m1;
      *(htab_p-13) = m1;
      *(htab_p-12) = m1;
      *(htab_p-11) = m1;
      *(htab_p-10) = m1;
      *(htab_p-9) = m1;
      *(htab_p-8) = m1;
      *(htab_p-7) = m1;
      *(htab_p-6) = m1;
      *(htab_p-5) = m1;
      *(htab_p-4) = m1;
      *(htab_p-3) = m1;
      *(htab_p-2) = m1;
      *(htab_p-1) = m1;
      htab_p -= 16;
   } while ((i -= 16) >= 0);
   for ( i += 16; i > 0; i-- ) {
      *--htab_p = m1;
   }
}



unsigned int getbyte(void)
{
   if( InCnt > 0 && (apsim_InCnt-- > 0)) {
      InCnt--;
      return( (unsigned int)*InBuff++ );
   } else {
      return( -1 );
   }
}

void putbyte( char c )
{
   *OutBuff++ = c;       		 /* apsim_unknown comp_text_buffer */
}


void writebytes( char *buf, int n )
{
   int i;
   for( i=0; (i<n) && (i < BITS) ; i++ ) {
      *OutBuff++ = buf[i];       		 /* apsim_unknown comp_text_buffer */
   }
}

char_type lmask[9] = {0xff, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 0x80, 0x00};
char_type rmask[9] = {0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff};

void output(code_int code)
{
  
   register int r_off = offset, bits= n_bits;
   register char * bp = buf;

   if (code >= 0) {
     
      bp += (r_off >> 3);
      r_off &= 7;
     
      *bp = ((*bp & rmask[r_off]) | (code << r_off)) & lmask[r_off];  /* apsim_unknown buf */
      bp++;
      bits -= (8 - r_off);
      code >>= 8 - r_off;
  
      if ( bits >= 8 ) {

         *bp++ = code;  /* apsim_unknown buf */
         code >>= 8;
         bits -= 8;
      }

      /* Last bits. */
      if(bits) {
         *bp = code;			 /* apsim_unknown buf */
      }

      offset += n_bits;
      if ( offset == (n_bits << 3) ) {
         bp = buf;
         bits = n_bits;
         bytes_out += bits;
         do {
            putbyte(*bp++);
              
         } while((( --bits) && ((bp - buf) < BITS)));
         offset = 0;
      }
    
      if (((free_ent > maxcode) || (clear_flg > 0))) {
     
         if ( offset > 0 ) {
            writebytes( buf, n_bits );
            bytes_out += n_bits;
         }
         offset = 0;
         if ( clear_flg ) 
         {
            maxcode = MAXCODE (n_bits = INIT_BITS);
            clear_flg = 0;
         } else {
            n_bits++;
            if ( n_bits == maxbits )
            {
               maxcode = maxmaxcode;
            }
            else
            {
               maxcode = MAXCODE(n_bits);
            }
         }
      }
   } else {
   
      if ( offset > 0 )
      {
         writebytes( buf, ((offset + 7) / 8) );
      }
      bytes_out += (offset + 7) / 8;
      offset = 0;
   }
}

int main(void)
{
   int count = IN_COUNT;


   initbuffer();

#ifdef LLBMC
  for (int i = 0; i < BUFFERSIZE; ++i) 
{
    orig_text_buffer[i] = __llbmc_nondef_char();
  }
#else
   klee_make_symbolic(orig_text_buffer, BUFFERSIZE * sizeof(char), "orig_text_buffer");
#endif
 
   maxbits = BITS;
   maxmaxcode = 1 << maxbits;

   InCnt = count;
   apsim_InCnt = IN_COUNT + 3;
   InBuff = (unsigned char *)orig_text_buffer;
   OutBuff = (unsigned char *)comp_text_buffer;

   compress();
   
   return (0);

}

