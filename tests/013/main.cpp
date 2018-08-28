
#include "SDL.h"

#include "SDL_config_lib.h"
#include "SDL_config_auto_tests.h"

using namespace std;

/*

  Test 013


  Value substitution

  There should be two failures regarding float and int, since their type wasn't reevaluated after substitutions - and that's ok.
     
*/

void CheckGroupKinky( ConfigFile & config );


int main(int argc, char **argv)
 {
  CFG_WRITE_HEADER(013)
  CFG_BEGIN_AUTO_TEST

  ConfigFile config("test_013.cfg");

  config.Save("test_013_orig.cfg");

  /* don't force and don't reevaluate entry types now */
  config.PerformValueSubstitution(false);

  config.Save("test_013_subst.cfg");
      
    CFG_AUTO_TEST_TEXT( config.ReadText("bar", ""), "5+5" );
    CFG_AUTO_TEST_TEXT( config.ReadText("lots_of_cash", ""), "$$$" );


  config.SelectGroup("Game");

    CFG_AUTO_TEST_TEXT( config.ReadText("exec", ""), "C:\\Games\\MagicPencil.exe" );
    CFG_AUTO_TEST_TEXT( config.ReadText("full_exec", ""), "C:\\Games\\MagicPencil\\MagicPencil.exe" );


    CFG_SelectMultiValueEntry("game_paths", 0);
    CFG_AUTO_TEST_TEXT( config.ReadText(CFG_MULTI_VALUE_ENTRY_ITERATION, ""), "C:\\Games\\MagicPencil.exe" );

    CFG_SelectMultiValueEntry("game_paths", 1);
    CFG_AUTO_TEST_TEXT( config.ReadText(CFG_MULTI_VALUE_ENTRY_ITERATION, ""), "C:\\Games\\MagicPencil\\MagicPencil.exe" );

    /* multiple value entries after substitution remain multi values, not lumped together in one entry*/
    CFG_SelectMultiValueEntry("my_game_paths", 0);
    CFG_AUTO_TEST_TEXT( config.ReadText(CFG_MULTI_VALUE_ENTRY_ITERATION, ""), "C:\\Games\\MagicPencil.exe" );

    CFG_SelectMultiValueEntry("my_game_paths", 1);
    CFG_AUTO_TEST_TEXT( config.ReadText(CFG_MULTI_VALUE_ENTRY_ITERATION, ""), "C:\\Games\\MagicPencil\\MagicPencil.exe" );

    CFG_SelectMultiValueEntry("my_game_paths", 2);
    CFG_AUTO_TEST_TEXT( config.ReadText(CFG_MULTI_VALUE_ENTRY_ITERATION, ""), "C:\\Games\\MagicPencil.exe" );

    CFG_SelectMultiValueEntry("my_game_paths", 3); // gdy bylo 4 to sie wywalalo
    CFG_AUTO_TEST_TEXT( config.ReadText(CFG_MULTI_VALUE_ENTRY_ITERATION, ""), "C:\\Games\\MagicPencil\\MagicPencil.exe" );


    /* should fail in few places */
    CheckGroupKinky(config); 

  /* now reevaluate entry types  */
  config.PerformValueSubstitution(true);

    /* should succeed */
    CheckGroupKinky(config);



/*
    CFG_Settings settings;
    CFG_GetDefaultSettings(&settings);

    settings.substitution_start[0] = '%';

    config.Open("test_013.cfg", &settings);    

*/

  
  CFG_AUTO_SUMMARY
  return 0;
 }

void CheckGroupKinky( ConfigFile & config )
  {
  config.SelectGroup("Kinky");


    CFG_AUTO_TEST_INTEGER( config.ReadInt("five", 0), 5 );
    CFG_AUTO_TEST_INTEGER( config.ReadInt("two", 0), 2 );

    CFG_AUTO_TEST_INTEGER( config.ReadInt("fifty-two", 0), 52 );

    CFG_AUTO_TEST_FLOAT( config.ReadFloat("five-point-two", 0.0f), 5.2f );


    CFG_AUTO_TEST_TEXT( config.ReadText("a", ""), "$(" );
    CFG_AUTO_TEST_TEXT( config.ReadText("b", ""), ")" );
    CFG_AUTO_TEST_TEXT( config.ReadText("middle", ""), "dupa" );
    CFG_AUTO_TEST_TEXT( config.ReadText("dupa", ""), "britney" );
    CFG_AUTO_TEST_TEXT( config.ReadText("trio", ""), "britney" );

  }