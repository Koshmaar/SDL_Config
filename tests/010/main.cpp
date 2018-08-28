

#include "SDL.h"

#include "SDL_config_lib.h"
#include "SDL_config_auto_tests.h"

using namespace std;

/*

  Test 010

  We're creating alternate config file format, which differs only in keywords.
     
*/


int main(int argc, char **argv)
 {
  CFG_WRITE_HEADER(010)

  CFG_Settings settings;
  CFG_GetDefaultSettings(&settings);

  settings.remove_group_spaces = false;
  settings.syntax_group_start = '<';
  settings.syntax_group_end = '>';
  settings.syntax_double_quote = '^';
  settings.syntax_multiple_value_separator = '|';
  settings.syntax_entry_equals = ':';
  settings.syntax_comment_2 = '!';
  /*settings.keyword_bool_true_1 = "this_is_truth"; // uncomment if CFG_REDEFINE_BOOL_KEYWORDS
  settings.keyword_bool_false_1 = "dupa";*/

  CFG_File config;
     
  if ( CFG_OK != CFG_OpenFile("test_010.cfg", &config, &settings ) )
   {
    fprintf(stderr, "Error: %s", CFG_GetError());
 	return 1;
   }

  CFG_BEGIN_AUTO_TEST


  CFG_AUTO_TEST_INTEGER( CFG_SelectGroup(" Type O Negative ", false), CFG_OK);
  CFG_AUTO_TEST_TEXT( CFG_ReadText("Bloody_Kisses", "error"), "Machine Screw");

  CFG_AUTO_TEST_BOOL( CFG_ReadBool("TON_is_great", false), true);
   

  /*
  Now wer'e saving with default syntax settings.
  Though most of the syntax got converted, as you can see in the generated file,
  you can't rely on the comments in this matter - TOFIX in next revision?

  */

  CFG_SaveFile("test_010_generated.cfg");
  CFG_SaveFile("test_010_kinky.cfg", CFG_SORT_ORIGINAL, CFG_SPACE_ENTRIES, &settings);
  CFG_CloseFile(0);

  CFG_AUTO_SUMMARY

  return 0;
 }
