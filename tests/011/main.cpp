
#include "SDL.h"

#include "SDL_config_lib.h"
#include "SDL_config_auto_tests.h"

using namespace std;

/*

  Test 011

  Operations on comments 


  \r is the Carriage Return, used here since that's the way it works...
  Tests works without \r when test_011.cfg has line endings in Unix format.
  Curiously, you don't need to use \r when returned comment is C-like... strange :-/ I'll try to fix this test in next version
     
*/


int main(int argc, char **argv)
 {
  CFG_WRITE_HEADER(011)
   
  CFG_File config;
     
  if ( CFG_OK != CFG_OpenFile("test_011.cfg", &config ) )
   {
    fprintf(stderr, "Error: %s", CFG_GetError());
 	return 1;
   }

  /*  ----------------------------------------- */

  CFG_BEGIN_AUTO_TEST

  CFG_AUTO_TEST_HEADER("Reading comments")

  CFG_AUTO_TEST_TEXT( CFG_GetEntryComment("Axl", CFG_TEXT, CFG_COMMENT_PRE), "// Guns\r" );
  CFG_AUTO_TEST_TEXT( CFG_GetEntryComment("Axl", CFG_TEXT, CFG_COMMENT_POST), "// n Roses\r" );
  
  CFG_AUTO_TEST_TEXT( CFG_GetEntryComment("Ozzy", CFG_TEXT, CFG_COMMENT_PRE), "# Black\r" );
  CFG_AUTO_TEST_TEXT( CFG_GetEntryComment("Ozzy", CFG_TEXT, CFG_COMMENT_POST), "# Sabbath\r" );

  /* Shows how neighbouring comments get stuffed together */
  CFG_AUTO_TEST_TEXT( CFG_GetEntryComment("Angry", CFG_TEXT, CFG_COMMENT_PRE), "; Alice\r\n; in\r\n; Chains\r" );   

  /*  ----------------------------------------- */

  CFG_AUTO_TEST_HEADER("Writing comments")

  CFG_SetEntryComment("Axl", CFG_TEXT, CFG_COMMENT_PRE, "# he is");
  CFG_SetEntryComment("Axl", CFG_TEXT, CFG_COMMENT_POST, "/* the vocalist */");

  CFG_AUTO_TEST_TEXT( CFG_GetEntryComment("Axl", CFG_TEXT, CFG_COMMENT_PRE), "# he is" );
  CFG_AUTO_TEST_TEXT( CFG_GetEntryComment("Axl", CFG_TEXT, CFG_COMMENT_POST), "/* the vocalist */" );

  CFG_SetEntryComment("Ozzy", CFG_TEXT, CFG_COMMENT_PRE, "// this guy");
  /* You must always remember to add comment sign, or else you risk of changing the value - see generated file */
  CFG_SetEntryComment("Ozzy", CFG_TEXT, CFG_COMMENT_POST, " likes biting off bat's heads ");

  /*  ----------------------------------------- */

  CFG_AUTO_TEST_HEADER("Group comments")

  CFG_AUTO_TEST_TEXT( CFG_GetGroupComment("Closterkeller", CFG_COMMENT_PRE),  "// Leader is\r" );
  CFG_AUTO_TEST_TEXT( CFG_GetGroupComment("Closterkeller", CFG_COMMENT_POST),  "// Anja Orthodox\r" );

  CFG_SelectGroup("Closterkeller");

  CFG_AUTO_TEST_TEXT( CFG_GetGroupComment(0, CFG_COMMENT_PRE),  "// Leader is\r" );
  CFG_AUTO_TEST_TEXT( CFG_GetGroupComment(0, CFG_COMMENT_POST),  "// Anja Orthodox\r" );


  /* This shows how can you 'comment out' a group. In fact, you can do this with entries too. */
  CFG_SetGroupComment("Closterkeller", CFG_COMMENT_PRE, "/* We want");
  CFG_SetGroupComment("Closterkeller", CFG_COMMENT_POST, " more concerts! */");

  CFG_AUTO_TEST_TEXT( CFG_GetGroupComment(0, CFG_COMMENT_PRE),  "/* We want" );
  CFG_AUTO_TEST_TEXT( CFG_GetGroupComment(0, CFG_COMMENT_POST),  " more concerts! */" );

  /*  ----------------------------------------- */

  CFG_AUTO_TEST_HEADER("Entry iteration")
   CFG_SelectGroup("Blind_Guardian");
   
  CFG_StartEntryIteration();

  CFG_AUTO_TEST_TEXT( CFG_GetSelectedEntryName(), "At" );  
  CFG_AUTO_TEST_TEXT( CFG_ReadText(CFG_ENTRY_ITERATION, "error"), "The" );
  CFG_AUTO_TEST_TEXT( CFG_GetEntryComment(0, CFG_TEXT, CFG_COMMENT_PRE), "// A Night\r" );
  CFG_AUTO_TEST_TEXT( CFG_GetEntryComment(0, CFG_TEXT, CFG_COMMENT_POST), "// Opera\r" );
  CFG_SelectNextEntry();

  CFG_AUTO_TEST_TEXT( CFG_GetSelectedEntryName(), "Far" );  
  CFG_AUTO_TEST_TEXT( CFG_ReadText(CFG_ENTRY_ITERATION, "error"), "" );
  CFG_AUTO_TEST_TEXT( CFG_GetEntryComment(0, CFG_TEXT, CFG_COMMENT_PRE), "/* Somewhere */" );
  CFG_AUTO_TEST_TEXT( CFG_GetEntryComment(0, CFG_TEXT, CFG_COMMENT_POST), "/* Beyond */" );
  CFG_SelectNextEntry();

  CFG_AUTO_TEST_TEXT( CFG_GetSelectedEntryName(), "In" );  
  CFG_AUTO_TEST_TEXT( CFG_ReadText(CFG_ENTRY_ITERATION, "error"), "Middle" );
  CFG_AUTO_TEST_TEXT( CFG_GetEntryComment(0, CFG_TEXT, CFG_COMMENT_PRE), "# Nightfall\r" );
  CFG_AUTO_TEST_TEXT( CFG_GetEntryComment(0, CFG_TEXT, CFG_COMMENT_POST), "# Earth\r" );
  CFG_SelectNextEntry();

  /*  ----------------------------------------- */

  CFG_SaveFile("test_011_generated.cfg");
  CFG_CloseFile(0);

  CFG_AUTO_SUMMARY

  return 0;
 }
