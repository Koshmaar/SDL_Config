

/* For main() wrapper and to satisfy linker */ 
#include "SDL.h"

/* You should include this file (and only this) when you want to use SDL_Config. */
#include "SDL_config_lib.h"

/*
 For autotest macros, don't include it in your code

 We're logging informations to stderr.txt
*/
#include "SDL_config_auto_tests.h"

using namespace std;


/*
 
 DON'T include SDL_config_types.h in your programs, its header to be used only by library.
 We're doing it here only because we want to access sizeofs of some types.
 
*/

#include <vector>
#include <map>

#include "SDL_config_types.h"


/*  ----------------------------------------- */

/*
 
 TEST 001
  
 Everything is thouroughly documented and explained only in this test, which functions also for educational purposes.
 Other tests aren't necessarry so documented.

 It covers basic library operations: opening file, reading and writing some values, simple operations on groups and saving file.

*/

int main(int argc, char **argv)
 {
  CFG_WRITE_HEADER(001)

  /*
   The most important structure is CFG_File, we must create it in order to do anything.
   If you need to open and work on many config files sequentially, you can reuse one CFG_File -
   open file, do sth with it, maybe save, close and once again - open another file etc.

   If you're allocating it on stack (like here) make sure you won't do anything with it when it falls off the stack.
  */
  CFG_File config;

  /*
   Open and parse file "test_001.cfg" and place results in "config" object.
   You don't need to call any library initialization functions before (there aren't any).
  */
  int result = CFG_OpenFile("test_001.cfg", &config );

  /* CFG_OpenFile returns value that allows you to check if everything went right, or do we have problems */
  if ( CFG_OK != result )
   {
    fprintf(stderr, "Error: %s", CFG_GetError());
 	return 1;
   }

  /* It dumps out nice header to stderr */
  CFG_BEGIN_AUTO_TEST

  /*
   We assume that file test_001.cfg wasn't modified by user and so we may expect
   that all entries should have certain values. That way, we can compare what should be with what
   we get, thereby achieving auto test of SDL_Config.
   Default values of every CFG_Read* should return what should NOT be returned.

   Now, we are reading integer entry and outputting its value in the next line.
   101 will be assigned if no entry called "screen_size_x" exists in currently selected group.

   Since we haven't explicitly opened any groups, global group is selected by default.
   */
  Sint32 value1 = CFG_ReadInt("screen_size_x", 100);
  CFG_AUTO_TEST_INTEGER(value1, 101);
  fprintf(stderr,"Integer value read from global group, entry *screen_size_x*: %i\n", value1 );

/*  ----------------------------------------- */

  CFG_AUTO_TEST_HEADER("Working on group")


   /* Confirm that group selection is case sensitive */
   CFG_AUTO_TEST_INTEGER( CFG_SelectGroup("vidEO", CFG_False), CFG_False );


  /*
   Now we select "Video" group.
   Passing false as second argument means: if there's no such group, don't create it.
  */
  if ( CFG_OK == CFG_SelectGroup("Video", CFG_False ) )
   {
    /* Now, read integers */
    Sint32 value2 = CFG_ReadInt("screen_size_x", 630);
    CFG_AUTO_TEST_INTEGER(value2, 640);
    fprintf(stderr,"Integer value read from [Video] group, *screen_size_x* entry: %i\n", value2 );

    Sint32 value3 = CFG_ReadInt("screen_size_y", 470);
    CFG_AUTO_TEST_INTEGER(value3, 480);
    fprintf(stderr,"Integer value read from [Video] group, entry *screen_size_y* entry: %i\n", value3 );

    Sint32 value4 = CFG_ReadInt("color_depth", 31);
    CFG_AUTO_TEST_INTEGER(value4, 32);
    fprintf(stderr,"Integer value read from [Video] group, *color_depth* entry: %i\n", value4 );

    /*
     This entry doesn't exist, so it'll be created with value passed as second argument - 101.
     OTOH, if it existed, CFG_ReadInt would just return value of that existing entry.
    */
    Sint32 value5 = CFG_ReadInt("xxxxxxxxxxxxx", 101);
    CFG_AUTO_TEST_INTEGER(value5, 101);
    fprintf(stderr,"Integer value read from [Video] group, *xxxxxxxxxxxxx* entry: %i\n", value5 );

    /*
     This entry also doesn't exist in Video group, but it exists in global group -
     so it'll get value from global group.
     Remember, first we look in selected group, then in global group, and if it doesn't exist anywhere - create entry.
    */
    Sint32 value6 = CFG_ReadInt("bad_integer", 101);
    CFG_AUTO_TEST_INTEGER(value6, 1234);
    fprintf(stderr,"Integer value read from [Video] group, *bad_integer* entry: %i\n", value6 );

    /* Read bool */
    CFG_Bool value7 = CFG_ReadBool("fullscreen", CFG_False);
    CFG_AUTO_TEST_BOOL(value7, CFG_True);
    fprintf(stderr,"Bool value read from [Video] group, *fullscreen* entry: %i\n\n", value7 );

/*  ----------------------------------------- */
    
    float value8;
    CFG_String title;

    /* Select group Game, it should exist */
    if ( CFG_OK == CFG_SelectGroup("Game", CFG_False) )
     {
      value8 = CFG_ReadFloat("version", 10.0);
      CFG_AUTO_TEST_FLOAT(value8, 0.01);
      fprintf(stderr,"Float value read from [Game] group, *version* entry: %f\n", value8 );

      title = CFG_ReadText("title", "error");
      CFG_AUTO_TEST_TEXT(title.c_str(), "Jump n' RotN");
      fprintf(stderr,"Text value read from [Game] group, *title* entry: %s\n\n", title.c_str() );

     } else CFG_LOG_OTHER_ERROR("Couldn't open group \"Game\" (without creating it).")
    
   }
    else CFG_LOG_OTHER_ERROR("Couldn't open group \"Video\" (without creating it).")

/*  ----------------------------------------- */

  CFG_AUTO_TEST_HEADER("Group operations")

  /* Remove group Game, testing returned value */
  CFG_AUTO_TEST_INTEGER(CFG_RemoveGroup("Game"), CFG_OK);

  /* Test once more" */
  CFG_AUTO_TEST_BOOL( CFG_GroupExists("Game"), CFG_False);

  /* Select group Video, testing returned value */
  CFG_AUTO_TEST_INTEGER(CFG_SelectGroup("Video", CFG_False), CFG_OK);

  /* Test once more" */
  CFG_AUTO_TEST_BOOL( CFG_GroupExists("Video"), CFG_True);

/*  ----------------------------------------- */

  /* Remove "fullscreen" entry from group Video */
  CFG_AUTO_TEST_INTEGER(CFG_RemoveBoolEntry("fullscreen"), CFG_OK);

  /* Test once more */
  CFG_AUTO_TEST_BOOL(CFG_BoolEntryExists("fullscreen"), CFG_False);

  /* Remove "fgfdgfdg" entry from group Video, which doesn't exist - so we should get CFG_ERROR */
  CFG_AUTO_TEST_INTEGER(CFG_RemoveIntEntry("fgfdgfdg"), CFG_ERROR);

  /* Try to remove "screen_size_y" entry from group Video,
  which exists but have different type - so it won't be removed */
  CFG_AUTO_TEST_INTEGER(CFG_RemoveFloatEntry("screen_size_y"), CFG_ERROR);

/*  ----------------------------------------- */

  /* Check if "fullscreen" exists */
  CFG_AUTO_TEST_BOOL( CFG_BoolEntryExists("fullscreen"), CFG_False);

  /* Check if "good_integer" exists */
  CFG_AUTO_TEST_BOOL( CFG_IntEntryExists("good_integer"), CFG_False);

  /* Check if "bad_integer" exists */
  CFG_AUTO_TEST_BOOL( CFG_TextEntryExists("bad_integer"), CFG_True);

/*  ----------------------------------------- */

  CFG_AUTO_TEST_HEADER("Integer sizes")
  CFG_SelectGroup("Integers", false);

  CFG_AUTO_TEST_INTEGER ( 2147483647, CFG_ReadInt("good_1", 0 ) ); /* 2147483647 is last good positive integer */
  CFG_AUTO_TEST_INTEGER ( -2147483648, CFG_ReadInt("good_2", 0 ) ); /* -2147483648 is last good negative integer */
  
  CFG_AUTO_TEST_INTEGER ( 0, CFG_ReadInt("bad_1", 0 ) ); /* 2147483648 will be interpreted as text */
  CFG_AUTO_TEST_INTEGER ( 0, CFG_ReadInt("bad_2", 0 ) ); /* -2147483649 will be interpreted as text */
  CFG_AUTO_TEST_INTEGER ( 0, CFG_ReadInt("bad_3", 0 ) ); /* 123456789123456789123456789123456789123456789123456 ditto */
  
  /* "2147483648" */
  CFG_AUTO_TEST_TEXT ( "2147483648", CFG_ReadText("bad_1", "0" ) );
  
  /* "-2147483649" */
  CFG_AUTO_TEST_TEXT ( "-2147483649", CFG_ReadText("bad_2", "0" ) );
  
  /* "123456789123456789123456789123456789123456789123456" */
  CFG_AUTO_TEST_TEXT ( "123456789123456789123456789123456789123456789123456", CFG_ReadText("bad_3", "0" ) );

/*  ----------------------------------------- */

  /* As a last test, save to text entry version of used SDL_Config library */

  const SDL_version * sdl_cfg_version = CFG_LinkedVersion();  
  CFG_Char buffer[20];
  sprintf(buffer, "%u.%u.%u", sdl_cfg_version->major, sdl_cfg_version->minor, sdl_cfg_version->patch);

  CFG_WriteText("SDL_Config_version", buffer);

  CFG_AUTO_TEST_TEXT( CFG_ReadText("SDL_Config_version", "error"), buffer);

/*  ----------------------------------------- */

  /* For informational purposes (mainly for the creator of this library),
   we also save sizes of some of the SDL_Config's internal types. */

  CFG_SelectGroup("Sizeofs");

  CFG_WriteInt("sizeof(CFG_Internal_ValueVectorItor)", sizeof(CFG_Internal_ValueVectorItor));  
  CFG_WriteInt("sizeof(CFG_Internal_ValueVector)", sizeof(CFG_Internal_ValueVector));  
  CFG_WriteInt("sizeof(CFG_Internal_Entry)", sizeof(CFG_Internal_Entry));  
  
  CFG_WriteInt("sizeof(CFG_Internal_EntryMap)", sizeof(CFG_Internal_EntryMap));  
  CFG_WriteInt("sizeof(CFG_Internal_Group)", sizeof(CFG_Internal_Group));  
  CFG_WriteInt("sizeof(CFG_String)", sizeof(CFG_String));  
  CFG_WriteInt("sizeof(CFG_Internal_GroupMap)", sizeof(CFG_Internal_GroupMap));  
  CFG_WriteInt("sizeof(CFG_Internal_File)", sizeof(CFG_Internal_File));    

/*  ----------------------------------------- */

  /* Save current state to file */
  CFG_SaveFile("test_001_final.cfg", CFG_SORT_ORIGINAL, CFG_SPACE_ENTRIES);  

  /* Close selected file (we would pass to it '&config' variable instead of 0, if it wasn't selected) */
  CFG_CloseFile(0);

  CFG_AUTO_SUMMARY

  return 0;
 }
 
