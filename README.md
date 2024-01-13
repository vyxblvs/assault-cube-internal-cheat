# acmenu2.0
This is a relatively basic cheat, but it was my introduction to game hacking, i didnt add esp or noclip or things like that because this was made mainly to improve at RE, c++, and assembly, and i really really dont like graphics related stuff so i didnt wanna learn to draw esp yet, and i didn't really care to learn much about game development in order to make more advanced features.
i also feel that i should mention the fact that i did not use any tutorials or repos relating assault cube or game hacking, if i didnt say that this would probably instantly be wrote off as just another one of the trillion cheats for this game that were pasted

# COMPILING
- install nasm and add it to path environment variables (or prefix the command with nasm's directory)
- include .asm file in project
- set item type as custom build tool
- set command line to: nasm -f win32 "$(ProjectDir)asm hooks.asm" -o "$(ProjectDir)asm hooks.obj"
- set output to $(ProjectDir)asm hooks.obj
- Enable "Verify Dependencies and Outputs Exist"
- Enable "Link Objects"
