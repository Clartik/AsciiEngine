project "Sandbox"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "bin/%{cfg.buildcfg}"
   staticruntime "off"

   files { "src/**.h", "src/**.cpp" }

   defines 
   {
      "_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS"
   }

   includedirs
   {
      "src",
      
	  -- Include Core
	  "../AsciiEngine/src",
      "../AsciiEngine/vendor/glm"
   }

   links
   {
      "AsciiEngine"
   }

   targetdir ("../bin/" .. OutputDir .. "/%{prj.name}")
   objdir ("../bin/int/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "Off"