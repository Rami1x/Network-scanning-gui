all: WinNetScan.exe

WinNetScan.exe: gui.c networking.c netinput.h
	gcc -o WinNetScan.exe gui.c networking.c -lws2_32 -lgdi32 -mwindows
	
clean:
	del WinNetScan.exe