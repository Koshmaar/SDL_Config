
#include "SDL.h"

#include "SDL_config_lib.h"
#include "SDL_config_auto_tests.h"

using namespace std;

/*

  TEST 002

  Strieves to perform as much auto tests as possible
  You shouldn't modify test_002.cfg, it's frozen
     
*/

/*  ----------------------------------------- */

void PerformBasicTests()
 {
  CFG_AUTO_TEST_HEADER("Reading")

   CFG_AUTO_TEST_BOOL( CFG_ReadBool("bool", CFG_True), CFG_False );
   CFG_AUTO_TEST_INTEGER( CFG_ReadInt("int", 0), 32 );   
   CFG_AUTO_TEST_FLOAT( CFG_ReadFloat("float", 0.0f), 1.23f );  
   CFG_AUTO_TEST_TEXT( CFG_ReadText("text", "error"), "LedZep uber alles!" );
   CFG_AUTO_TEST_TEXT( CFG_ReadText("xxxnoquote", "error"), "C:\\Games\\" );
   

  CFG_AUTO_TEST_HEADER("Writing, create new entries")

   CFG_WriteBool("bool2", CFG_True);
   CFG_WriteInt("int2", -23);
   CFG_WriteFloat("float2", 77.7f);
   CFG_WriteText("text2", "Stairway To Heaven");

   CFG_AUTO_TEST_BOOL( CFG_ReadBool("bool2", CFG_False), CFG_True );
   CFG_AUTO_TEST_INTEGER( CFG_ReadInt("int2", 0), -23 );
   CFG_AUTO_TEST_FLOAT( CFG_ReadFloat("float2", 0.0f), 77.7f );  
   CFG_AUTO_TEST_TEXT( CFG_ReadText("text2", "error"), "Stairway To Heaven" );
   CFG_AUTO_TEST_INTEGER( CFG_GetEntriesInSelectedGroup(), 9 );

  CFG_AUTO_TEST_HEADER("Writing to existing entries")

   CFG_WriteBool("bool2", CFG_False);
   CFG_WriteInt("int2", 99);
   CFG_WriteFloat("float2", 66.7f);
   CFG_WriteText("text2", "ZoSo");

   CFG_AUTO_TEST_BOOL( CFG_ReadBool("bool2", CFG_True), CFG_False );
   CFG_AUTO_TEST_INTEGER( CFG_ReadInt("int2", 0), 99 );
   CFG_AUTO_TEST_FLOAT( CFG_ReadFloat("float2", 0.0f), 66.7f );  
   CFG_AUTO_TEST_TEXT( CFG_ReadText("text2", "error"), "ZoSo" );


  CFG_AUTO_TEST_HEADER("Existance checking")
   
   CFG_AUTO_TEST_BOOL( CFG_BoolEntryExists("!!!!"), CFG_False );
   CFG_AUTO_TEST_BOOL( CFG_IntEntryExists("!!!!"), CFG_False );
   CFG_AUTO_TEST_BOOL( CFG_FloatEntryExists("!!!!"), CFG_False );
   CFG_AUTO_TEST_BOOL( CFG_TextEntryExists("!!!!"), CFG_False );

   CFG_AUTO_TEST_BOOL( CFG_BoolEntryExists("bool2"), CFG_True );
   CFG_AUTO_TEST_BOOL( CFG_IntEntryExists("int2"), CFG_True );
   CFG_AUTO_TEST_BOOL( CFG_FloatEntryExists("float2"), CFG_True );
   CFG_AUTO_TEST_BOOL( CFG_TextEntryExists("text2"), CFG_True );

   /* Entry exists but with different type, should return false  */
   CFG_AUTO_TEST_BOOL( CFG_IntEntryExists("text2"), CFG_False );

   CFG_AUTO_TEST_HEADER("Removing")

   CFG_AUTO_TEST_INTEGER( CFG_RemoveBoolEntry("bool2"), CFG_OK );
   CFG_AUTO_TEST_INTEGER( CFG_RemoveIntEntry("int2"), CFG_OK );
   CFG_AUTO_TEST_INTEGER( CFG_RemoveFloatEntry("float2"), CFG_OK );
   CFG_AUTO_TEST_INTEGER( CFG_RemoveTextEntry("text2"), CFG_OK );

   CFG_AUTO_TEST_BOOL( CFG_BoolEntryExists("bool2"), CFG_False );
   CFG_AUTO_TEST_BOOL( CFG_IntEntryExists("int2"), CFG_False );
   CFG_AUTO_TEST_BOOL( CFG_FloatEntryExists("float2"), CFG_False );
   CFG_AUTO_TEST_BOOL( CFG_TextEntryExists("text2"), CFG_False );

   CFG_AUTO_TEST_INTEGER( CFG_RemoveBoolEntry("bool2"), CFG_ERROR );
   CFG_AUTO_TEST_INTEGER( CFG_RemoveIntEntry("int2"), CFG_ERROR );
   CFG_AUTO_TEST_INTEGER( CFG_RemoveFloatEntry("float2"), CFG_ERROR );
   CFG_AUTO_TEST_INTEGER( CFG_RemoveTextEntry("text2"), CFG_ERROR );

   /* Try to remove entry with matching name, but different type */
   CFG_WriteInt("int2", 99);

   CFG_AUTO_TEST_INTEGER( CFG_RemoveFloatEntry("int2"), CFG_ERROR );

   CFG_AUTO_TEST_HEADER("Type checking")

   CFG_AUTO_TEST_INTEGER( CFG_GetEntryType("bool"), CFG_BOOL );
   CFG_AUTO_TEST_INTEGER( CFG_GetEntryType("int"), CFG_INTEGER );
   CFG_AUTO_TEST_INTEGER( CFG_GetEntryType("float"), CFG_FLOAT );
   CFG_AUTO_TEST_INTEGER( CFG_GetEntryType("text"), CFG_TEXT );

   CFG_AUTO_TEST_INTEGER( CFG_GetEntryType("!!!!"), 0 );


 }

int main(int argc, char **argv)
 {
  CFG_WRITE_HEADER(002)

  CFG_File config;
     
  if ( CFG_OK != CFG_OpenFile("test_002.cfg", &config ) )
   {
    fprintf(stderr, "Error: %s", CFG_GetError());
 	return 1;
   }

  CFG_BEGIN_AUTO_TEST

  CFG_AUTO_TEST_HEADER("File operations")

  CFG_AUTO_TEST_TEXT( CFG_GetSelectedFileName(), "test_002.cfg");
  CFG_AUTO_TEST_INTEGER( CFG_GetSelectedFile(), &config);

  CFG_AUTO_TEST_INTEGER( CFG_GetEntriesInSelectedGroup(), 5 );
  CFG_AUTO_TEST_INTEGER( CFG_GetEntriesInSelectedGroup(CFG_BOOL), 1 );
  CFG_AUTO_TEST_INTEGER( CFG_GetEntriesInSelectedGroup(CFG_INTEGER), 1 );
  CFG_AUTO_TEST_INTEGER( CFG_GetEntriesInSelectedGroup(CFG_FLOAT), 1 );
  CFG_AUTO_TEST_INTEGER( CFG_GetEntriesInSelectedGroup(CFG_TEXT), 2 );

  /*  -----------------------------------------  Entries */

  PerformBasicTests();

  CFG_ClearGroup(CFG_GLOBAL);  
  CFG_SelectGroup("Nirvana");
  PerformBasicTests();
  
   
  /*  ----------------------------------------- Groups  */

  CFG_AUTO_TEST_HEADER("Groups creation and existance")


  CFG_AUTO_TEST_INTEGER( CFG_GetGroupCount(), 2);

  CFG_AUTO_TEST_BOOL( CFG_GroupExists("Bob_Dylan"), false);
  CFG_AUTO_TEST_BOOL( CFG_GroupExists("Nirvana"), true);

  CFG_AUTO_TEST_TEXT( CFG_GetSelectedGroupName(), "Nirvana");

  CFG_SelectGroup(0);
  CFG_AUTO_TEST_INTEGER( CFG_GetSelectedGroupName(), 0);

  CFG_AUTO_TEST_INTEGER( CFG_SelectGroup("Bob_Dylan", CFG_True), CFG_GROUP_CREATED);
  CFG_AUTO_TEST_BOOL( CFG_GroupExists("Bob_Dylan"), true);
  CFG_AUTO_TEST_TEXT( CFG_GetSelectedGroupName(), "Bob_Dylan");
  CFG_AUTO_TEST_INTEGER( CFG_GetGroupCount(), 3);


  CFG_AUTO_TEST_HEADER("Groups removal")

  CFG_AUTO_TEST_BOOL( CFG_RemoveGroup("Bob_Dylan"), CFG_OK );

  CFG_AUTO_TEST_INTEGER( CFG_GetGroupCount(), 2);
  CFG_AUTO_TEST_BOOL( CFG_GroupExists("Bob_Dylan"), false);
  CFG_AUTO_TEST_INTEGER( CFG_GetSelectedGroupName(), 0);
  CFG_AUTO_TEST_BOOL( CFG_RemoveGroup("Bob_Dylan"), CFG_ERROR );
  CFG_AUTO_TEST_INTEGER( CFG_SelectGroup("Bob_Dylan", CFG_True), CFG_GROUP_CREATED);

  
  /*  -----------------------------------------  */

  CFG_AUTO_TEST_HEADER("Group iteration")

  /* Yeaah, I always wanted to create variables with such names ;-) */
  const char * Nirvana = "Nirvana";
  const char * Black_Sabbath = "Black_Sabbath";
  const char * Bob_Dylan = "Bob_Dylan";

  const char * expected_groups_orig_forward[] = { Nirvana, Black_Sabbath, Bob_Dylan };
  const char * expected_groups_orig_reverse[] = { Bob_Dylan, Black_Sabbath, Nirvana };
  const char * expected_groups_alpha_forward[] = { Black_Sabbath, Bob_Dylan, Nirvana };
  const char * expected_groups_alpha_reverse[] = { Nirvana, Bob_Dylan, Black_Sabbath };
  int i = 0;

  for ( CFG_StartGroupIteration(CFG_SORT_ORIGINAL); !CFG_IsLastGroup(); CFG_SelectNextGroup(), ++i)
   {
    CFG_AUTO_TEST_TEXT( CFG_GetSelectedGroupName(), expected_groups_orig_forward[i] )
   }

  CFG_AUTO_TEST_INTEGER( CFG_SetGroupIterationDirection(CFG_ITERATE_REVERSE), CFG_ITERATE_NORMAL );
  i = 0;
  for ( CFG_StartGroupIteration(CFG_SORT_ORIGINAL); !CFG_IsLastGroup(); CFG_SelectNextGroup(), ++i)
   {
    CFG_AUTO_TEST_TEXT( CFG_GetSelectedGroupName(), expected_groups_orig_reverse[i] )
   }

  CFG_AUTO_TEST_INTEGER( CFG_SetGroupIterationDirection(CFG_ITERATE_NORMAL), CFG_ITERATE_REVERSE );
  i = 0;
  for ( CFG_StartGroupIteration(CFG_SORT_ALPHABET); !CFG_IsLastGroup(); CFG_SelectNextGroup(), ++i)
   {
    CFG_AUTO_TEST_TEXT( CFG_GetSelectedGroupName(), expected_groups_alpha_forward[i] )
   }

  CFG_SetGroupIterationDirection(CFG_ITERATE_REVERSE);
  i = 0;
  for ( CFG_StartGroupIteration(CFG_SORT_ALPHABET); !CFG_IsLastGroup(); CFG_SelectNextGroup(), ++i)
   {
    CFG_AUTO_TEST_TEXT( CFG_GetSelectedGroupName(), expected_groups_alpha_reverse[i] )
   }

  CFG_SetGroupIterationDirection(CFG_ITERATE_NORMAL);

  /*  -----------------------------------------  */

  CFG_AUTO_TEST_HEADER("Entry iteration")

  CFG_ClearFile(0);

  CFG_AUTO_TEST_INTEGER( CFG_OpenFile("test_002.cfg", &config ), CFG_OK )

  CFG_SelectGroup("Nirvana");
  CFG_StartEntryIteration();

  /* bool */
  CFG_AUTO_TEST_INTEGER( CFG_GetEntryType(CFG_ENTRY_ITERATION), CFG_BOOL );
  CFG_AUTO_TEST_TEXT( CFG_GetSelectedEntryName(), "bool" );
  CFG_AUTO_TEST_BOOL( CFG_ReadBool(CFG_ENTRY_ITERATION, true), false );
  CFG_SelectNextEntry();

   /* float */
  CFG_AUTO_TEST_INTEGER( CFG_GetEntryType(CFG_ENTRY_ITERATION), CFG_FLOAT );
  CFG_AUTO_TEST_TEXT( CFG_GetSelectedEntryName(), "float" );
  CFG_AUTO_TEST_FLOAT( CFG_ReadFloat(CFG_ENTRY_ITERATION, 0.0f), 1.23f );
  CFG_SelectNextEntry();

  /* int */ 
  CFG_AUTO_TEST_INTEGER( CFG_GetEntryType(CFG_ENTRY_ITERATION), CFG_INTEGER );
  CFG_AUTO_TEST_TEXT( CFG_GetSelectedEntryName(), "int" );
  CFG_AUTO_TEST_INTEGER( CFG_ReadInt(CFG_ENTRY_ITERATION, 0), 32 );
  CFG_SelectNextEntry();

  /* text */
  CFG_AUTO_TEST_INTEGER( CFG_GetEntryType(CFG_ENTRY_ITERATION), CFG_TEXT );  
  CFG_AUTO_TEST_TEXT( CFG_GetSelectedEntryName(), "text" );
  CFG_AUTO_TEST_TEXT( CFG_ReadText(CFG_ENTRY_ITERATION, "error"), "LedZep uber alles!" );
  CFG_SelectNextEntry();

  CFG_AUTO_TEST_BOOL( CFG_IsLastEntry(), false );
  CFG_SelectNextEntry();
  CFG_AUTO_TEST_BOOL( CFG_IsLastEntry(), true );

  /*  -----------------------------------------  */

  CFG_AUTO_TEST_HEADER("Multi value entry iteration")

    
  CFG_AUTO_TEST_BOOL( CFG_IsEntryMultiValue("int"), false )
  CFG_SelectGroup("Black_Sabbath");
  CFG_AUTO_TEST_BOOL( CFG_IsEntryMultiValue("albums"), true )
  CFG_AUTO_TEST_INTEGER( CFG_GetNumberOfMultiValueEntries("albums"), 3 )

  CFG_StartMultiValueEntryIteration( "albums" );    
 
  CFG_AUTO_TEST_TEXT( CFG_ReadText(CFG_MULTI_VALUE_ENTRY_ITERATION, 0), "Paranoid" );  
  CFG_SelectNextMultiValueEntry();

  CFG_AUTO_TEST_TEXT( CFG_ReadText(CFG_MULTI_VALUE_ENTRY_ITERATION, 0), "Master of reality" );  
  CFG_SelectNextMultiValueEntry();

  CFG_AUTO_TEST_TEXT( CFG_ReadText(CFG_MULTI_VALUE_ENTRY_ITERATION, 0), "Heaven and hell" );  
  CFG_SelectNextMultiValueEntry();  

  CFG_AUTO_TEST_BOOL( CFG_IsLastMultiValueEntry(), true )

  CFG_AUTO_TEST_INTEGER( CFG_SelectMultiValueEntry("albums", 2), CFG_OK )
  CFG_AUTO_TEST_TEXT( CFG_ReadText(CFG_MULTI_VALUE_ENTRY_ITERATION, 0), "Heaven and hell" );  

  CFG_AUTO_TEST_INTEGER( CFG_SelectMultiValueEntry("albums", 1), CFG_OK )
  CFG_AUTO_TEST_TEXT( CFG_ReadText(CFG_MULTI_VALUE_ENTRY_ITERATION, 0), "Master of reality" );  


  CFG_AUTO_TEST_INTEGER( CFG_WriteBool("cool_wind", true), CFG_ENTRY_CREATED )

  CFG_AUTO_TEST_INTEGER( CFG_AddMultiValueToBool("cool_wind", false), CFG_OK )
  CFG_AUTO_TEST_INTEGER( CFG_AddMultiValueToBool("cool_wind", true), CFG_OK )

  CFG_AUTO_TEST_INTEGER( CFG_SelectMultiValueEntry("cool_wind", 0), CFG_OK )
  CFG_AUTO_TEST_BOOL( CFG_ReadBool(CFG_MULTI_VALUE_ENTRY_ITERATION, 0), true );  

  CFG_AUTO_TEST_INTEGER( CFG_SelectMultiValueEntry("cool_wind", 1), CFG_OK )
  CFG_AUTO_TEST_BOOL( CFG_ReadBool(CFG_MULTI_VALUE_ENTRY_ITERATION, 0), false );

  CFG_AUTO_TEST_INTEGER( CFG_SelectMultiValueEntry("cool_wind", 2), CFG_OK )
  CFG_AUTO_TEST_BOOL( CFG_ReadBool(CFG_MULTI_VALUE_ENTRY_ITERATION, 0), true );  


  CFG_AUTO_TEST_INTEGER( CFG_AddMultiValueToBool("cool_wind", false, 0), CFG_OK )
  CFG_AUTO_TEST_INTEGER( CFG_SelectMultiValueEntry("cool_wind", 0), CFG_OK )
  CFG_AUTO_TEST_BOOL( CFG_ReadBool(CFG_MULTI_VALUE_ENTRY_ITERATION, 0), false );  

  CFG_AUTO_TEST_INTEGER( CFG_AddMultiValueToBool("cool_wind", false, 1), CFG_OK )
  CFG_AUTO_TEST_INTEGER( CFG_SelectMultiValueEntry("cool_wind", 1), CFG_OK )
  CFG_AUTO_TEST_BOOL( CFG_ReadBool(CFG_MULTI_VALUE_ENTRY_ITERATION, 0), false );  



  CFG_AUTO_TEST_INTEGER( CFG_AddMultiValueToBool("dupa", false), CFG_ERROR )


  /*  -----------------------------------------  */
   
    
  /* CFG_SaveFile("test_002_compressed.ini", CFG_SORT_ORIGINAL, CFG_COMPRESS_OUTPUT);  */

  CFG_CloseFile(0);

  CFG_AUTO_SUMMARY

  return 0;
 }
