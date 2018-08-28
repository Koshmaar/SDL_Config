

#include "SDL.h"

#include "SDL_config_lib.h"
#include "SDL_config_auto_tests.h"

using namespace std;

/*

  Test 012

  C++ wrapper interface to SDL_Config
     
*/


int main(int argc, char **argv)
 {
  CFG_WRITE_HEADER(012)
  CFG_BEGIN_AUTO_TEST

  ConfigFile config("test_001.cfg");

  CFG_AUTO_TEST_BOOL( config.IsOpen(), true );
  CFG_AUTO_TEST_INTEGER( config.ReadInt("screen_size_x", 0), 101 );
  CFG_AUTO_TEST_INTEGER( config.WriteInt("screen_size_x", 55), CFG_OK );
  CFG_AUTO_TEST_INTEGER( config.ReadInt("screen_size_x", 0), 55 );

  config.SelectGroup("Video");

  CFG_AUTO_TEST_BOOL( config.FloatEntryExists("dupa"), false);

  config.SelectGroup("Floats");

  /* won't work when CFG_Float == floats 
#if CFG_Float == double ifdefs don't want to work */
  CFG_AUTO_TEST_BOOL( config.Read("double", 0.0f) == 333640273517170720000.0, true );  /* there's sth weird around here: you can use 333640273517170720001.0 and it'll also work */
/* #endif */
  CFG_AUTO_TEST_BOOL( config.Read("float", 0.0f) == 160320.0, true );  

  config.Save("test_012_gen.cfg");


  config.Open("test_002.cfg");

  CFG_AUTO_TEST_TEXT( config.ReadText("text", "error"), "LedZep uber alles!" )     

  CFG_AUTO_SUMMARY
  return 0;
 }
