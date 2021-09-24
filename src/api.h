#pragma once

#if defined _WIN32 || defined __CYGWIN__
#  define MultiRobot_DLLIMPORT __declspec(dllimport)
#  define MultiRobot_DLLEXPORT __declspec(dllexport)
#  define MultiRobot_DLLLOCAL
#else
// On Linux, for GCC >= 4, tag symbols using GCC extension.
#  if __GNUC__ >= 4
#    define MultiRobot_DLLIMPORT __attribute__((visibility("default")))
#    define MultiRobot_DLLEXPORT __attribute__((visibility("default")))
#    define MultiRobot_DLLLOCAL __attribute__((visibility("hidden")))
#  else
// Otherwise (GCC < 4 or another compiler is used), export everything.
#    define MultiRobot_DLLIMPORT
#    define MultiRobot_DLLEXPORT
#    define MultiRobot_DLLLOCAL
#  endif // __GNUC__ >= 4
#endif // defined _WIN32 || defined __CYGWIN__

#ifdef MultiRobot_STATIC
// If one is using the library statically, get rid of
// extra information.
#  define MultiRobot_DLLAPI
#  define MultiRobot_LOCAL
#else
// Depending on whether one is building or using the
// library define DLLAPI to import or export.
#  ifdef MultiRobot_EXPORTS
#    define MultiRobot_DLLAPI MultiRobot_DLLEXPORT
#  else
#    define MultiRobot_DLLAPI MultiRobot_DLLIMPORT
#  endif // MultiRobot_EXPORTS
#  define MultiRobot_LOCAL MultiRobot_DLLLOCAL
#endif // MultiRobot_STATIC