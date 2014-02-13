/*
Copyright (c) 2014 Aleksandar Panic

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

   3. This notice may not be removed or altered from any source
   distribution.
*/

#define RAGE_RB_PROC_ERROR "You can only pass instances of Proc object as an argument."
#define RAGE_RB_INCOMPATIBLE "This game may be incompatible with this version of RAGE.\n\n"
#define RAGE_RB_FILE_MISSING_ERROR "File '%s' not found."
#define RAGE_RB_PATH_MISSING_ERROR "Path '%s' not found."
#define RAGE_EVENT_ERROR "Cannot call methods from abstract RAGE::Event class."
#define RAGE_BITMAP_ERROR "Width and Height values need to be Fixnum."
#define RAGE_BITMAP_PARENT_ERROR "Parent argument must be an instance of RAGE::Bitmap."
#define RAGE_BITMAP_NOT_CREATED_ERROR "Cannot set nil bitmap as drawing target. Create or load a bitmap first."
#define RAGE_ERROR_CANNOT_SET_DISPOSED_OBJECTS "Cannot set disposed objects."
#define RAGE_COLOR_ERROR "Argument must be an instance of RAGE::Color class."
#define RAGE_FONT_ERROR "Argument must be an instance of RAGE::Font class."
#define RAGE_ERROR_DISPOSED_OBJECT "Cannot call methods or properties of disposed objects."
#define RAGE_ERROR_MUSIC_LOAD_FAIL "Music file '%s' failed to load."
#define RAGE_ERROR_SFX_LOAD_FAIL "Sfx file '%s' failed to load."
#define RAGE_ERROR_EVENT_QUEUE_FAIL "Failed to initialize event queue."
#define RAGE_ERROR_TIMER_FAIL "Failed to initialize timer."
#define RAGE_ERROR_INI_CREATE_FAIL "IniFile creation failed."
#define RAGE_ERROR_INI_LOAD_FAIL "IniFile failed load file '%s'."
#define RAGE_ERROR_BITMAP_CREATE_FAIL "Bitmap creation failed."
#define RAGE_ERROR_SUBBITMAP_CREATE_FAIL "Sub-Bitmap creation failed."
#define RAGE_ERROR_BITMAP_LOAD_FAIL "Bitmap failed to load file '%s'."
#define RAGE_ERROR_FONT_LOAD_FAIL "Font failed to load file '%s'."
#define RAGE_ERROR_MOUSE_CURSOR_CREATE_FAIL "Failed to create bitmap mouse cursor."
#define RAGE_ERROR_SHADER_CODE_NOT_ADDED "Shader code is not added, cannot set it as active."
#define RAGE_SHADER_COMPILE_LINK_ERROR "Shader Error:\n"
#define RAGE_ERROR_NO_EXT_FRAGMENT_SHADERS "Your OpenGL implementation does not support fragment shaders."
#define RAGE_ERROR_NO_EXT_VERTEX_SHADERS "Your OpenGL implementation does not support vertex shaders."
#define RAGE_JOYSTICK_NOT_FOUND_ERROR "Joystick with index %d is not available."
#define RAGE_VAR_FUNCTION_TOO_MANY_ARGS "Too many arguments passed."
#define RAGE_VAR_FUNCTION_INCOMP_ARGS "Too many or not enough arguments passed. Minimum %d or maximum %d arguments need to be passed."
#define RAGE_ERROR_INDICES_NOT_ARRAY "You must pass an indices must be passed as an array."
#define RAGE_ERROR_DL_EXT_RB_DATA_FAILED "DL/Win32API extension RB class data failed to parse."
#define RAGE_ERROR_CANNOT_CREATE_VOICE "RAGE Error: Failed to allocate audio voice. Audio functions will not work.\n"
#define RAGE_ERROR_CANNOT_CREATE_MIXER "RAGE Error: Failed to allocate audio mixer. Audio functions will not work.\n"
#define RAGE_RB_TIMER_ERROR "You can only pass instances of RAGE::Timer object as an argument."
#define RAGE_RB_EVENT_REG_ERR "You can register only instances of RAGE::Event objects."
#define RAGE_ERROR_CANNOT_DISPOSE_DRAWING_TARGET "Cannot dispose current drawing target bitmap."
#define RAGE_ERROR_CANNOT_DISPOSE_LOCKED_BITMAP "Cannot dispose locked bitmap. Unlock this bitmap first."
#define RAGE_ERROR_FS_BASE_FILE_ERROR "Cannot call methods from abstract RAGE::BaseFile class."
#define RAGE_ERROR_FS_CANNOT_LOAD "File '%s' cannot be loaded."
#define RAGE_ERROR_FS_CANNOT_OPEN "Cannot open '%s' for writing."
#define RAGE_ERROR_FS_FILE_NOT_LOADED "No file loaded or created."
#define RAGE_ERROR_FS_RAGE_FILE_NOT_LOADED "No file loaded or created in RAGE::BaseFile."
#define RAGE_ERROR_FS_MEMFILE_CANNOT_OPEN "Failed to open memory as file."
#define RAGE_ERROR_FS_DISPOSED_RAGE_FILE "Cannot load from disposed RAGE::BaseFile"
#define RAGE_ERROR_FS_DISPOSED_RAGE_FILE_READ "Cannot read from disposed RAGE::BaseFile"
#define RAGE_ERROR_FS_DISPOSED_RAGE_FILE_WRITE "Cannot write to disposed RAGE::BaseFile"
#define RAGE_ERROR_FS_PASSED_ARGUMENT_NOT_STRING "Passed first argument is not a string."
#define RAGE_ERROR_SHADER_ARG_NOT_ARY "Passed variable must be an array."
#define RAGE_FATAL_ERROR_SIGSEGV "Fatal error: Segmentation fault.\nPress any key to exit."
#define RAGE_FATAL_ERROR_SIGSEGV_DEBUG "Fatal error: Segmentation fault!"
#define RAGE_ERROR_FONT_GLYPH_RANGE_ERROR "Passed range array must have an even size."
#define RAGE_ERROR_FONT_ARG_NOT_ARY "Passed variable must be an array."
#define RAGE_ERROR_SOCKET_CANNOT_RESOLVE_HOST "Socket Error: Cannot resolve host name."
#define RAGE_ERROR_SOCKET_CANNOT_CREATE "Socket Error: Cannot create socket."
#define RAGE_ERROR_SOCKET_CANNOT_CONNECT_HOST "Socket Error: Cannot connect to host."
#define RAGE_ERROR_SOCKET_CANNOT_SEND_DATA "Socket Error: Failed to send header data."
#define RAGE_ERROR_SOCKET_CANNOT_RECV_DATA "Socket Error: Failed to receive data."
#define RAGE_ERROR_SOCKET_WSA_INIT "Socket Error: WSA Initialization failed."
#define RAGE_ERROR_SOCKET_WSA_CLEANUP "Socket Error: WSA cleanup failed."
#define RAGE_ERROR_SOCKET_CONFIG "Socket Error: Failed to set socket configuration."
#define RAGE_ERROR_SOCKET_BLOCK_MODE "Socket Error: Could not set blocking mode."
#define RAGE_ERROR_SOCKET_BIND_ERROR "Socket Error: Could not bind server to ip."
#define RAGE_ERROR_SERVER_NOT_CONNECTED "Server was not created. Cannot use this method."
#define RAGE_ERROR_CLIENT_NOT_CONNECTED "Cannot use this method. Not connected to host."
#define RAGE_ERROR_SERVER_CANNOT_DISCONNECT_SELF "Cannot disconnect self."
#define RAGE_ERROR_SOCKET_CANNOT_CLOSE_SERVER "Socket Error: Could not close server socket."
#define RAGE_ERROR_SOCKET_TIMEOUT_CANNOT_SET "Socket Error: Could not set timeout."
