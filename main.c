#pragma comment(linker, "/RELEASE")
#pragma comment(linker, "/OPT:NOWIN98")
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

static char buf[128 * 1024];

int main(int argc, const char **argv)
{
	const char *p;
	STARTUPINFO startupinfo;
	PROCESS_INFORMATION processinfo;

	// "C:\Program Files (x86)\Steam\steamapps\common\VRChat\launch.exe" --url=create?roomId=4376424507&hidden=true&name=BuildAndRun&url=file:///C%3a%2fUsers%2fmina%2fAppData%2fLocal%2fTemp%2fDefaultCompany%2fW_Dance%2fcustomscene.vrcw

	p = GetCommandLine();
	if (p == NULL) {
		return -1;
	}

	printf("%s\n", p);

	if (*p != '"' ||
		(p = strchr(&p[1], '"')) == NULL) {
		return -1;
	}

	strcpy(buf, "\"VRChat.exe\" ");

	printf("launch as VR (Y/N)? ");
	if ((getch() & 223) != 'Y') {
		strcat(buf, "--no-vr ");
	}

	strcat(buf, "--enable-debug-gui --enable-sdk-log-level ");
	strcat(buf, &p[2]);

	memset(&startupinfo, 0, sizeof(startupinfo));
	startupinfo.cb = sizeof(startupinfo);

	if (CreateProcess(NULL, buf, NULL, NULL, FALSE, 0, NULL, NULL, &startupinfo, &processinfo) == FALSE) {
		return -1;
	}

	fputc('\n', stdout);
	WaitForSingleObject(processinfo.hProcess, INFINITE);
	CloseHandle(processinfo.hProcess);
	CloseHandle(processinfo.hThread);
	return 0;
}
