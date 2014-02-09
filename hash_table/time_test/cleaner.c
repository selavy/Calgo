#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
  if( argc < 3 )
    {
      fputs("./cleaner <in_file> <out_file>\n", stderr);
      exit(1);
    }

  FILE *in, *out;
  char line[256];
  char input[256];
  char * end;
  char delimiter = (argc == 4) ? argv[3][0] : '|';

  in = fopen( argv[1], "r" );
  out = fopen( argv[2], "w" );

  if( !(in && out) )
    {
      fputs("Unable to open file!\n", stderr);
      exit(1);
    }

  while( fgets( input, 256, in ) )
   {
     sscanf( input, "%s\n", line );
     end = strchr( line, delimiter );
     if( end )
       {
	 *end = '\0';
	 fprintf( out, "%s\n", line );
       }
   }

  fclose( in );
  fclose( out );
  return 0;
}
