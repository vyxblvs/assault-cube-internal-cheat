# COMPILING
- install nasm and add it to path environment variables (or prefix the command with nasm's directory)
- include .asm file in project
- set item type as custom build tool
- set command line to: nasm -f win32 "$(ProjectDir)asm hooks.asm" -o "$(ProjectDir)asm hooks.obj"
- set output to $(ProjectDir)asm hooks.obj
- Enable "Verify Dependencies and Outputs Exist"
- Enable "Link Objects"
