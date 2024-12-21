-- premake5.lua
workspace "AsciiEngine"
   architecture "x64"
   configurations { "Debug", "Release" }
   startproject "Sandbox"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

include "AsciiEngine/Build-Engine.lua"
include "Sandbox/Build-Sandbox.lua"