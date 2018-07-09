#include "ps4.h"
#include "patch.h"
#include "ApplicationCache.h"

void writeCacheDB()
{
    size_t len = 0;
    unsigned char* fbuf = base64_decode(ApcStr, sizeof(ApcStr), &len);
	if (len != 0)
	{
    int fid = open("/user/system/webkit/webbrowser/appcache/ApplicationCache.db", O_WRONLY | O_CREAT | O_TRUNC, 0777);
    write(fid, fbuf, len);
    close(fid);
	free(fbuf);
	sceKernelSleep(3);
	systemMessage("Cache install Complete\n\nBookmark:\nhttp://cache/index.html");
	sceKernelSleep(1);
	openBrowser("http://cache/index.html");
	}
	else
	{
		systemMessage("ERROR:\nNo internal cache found");
	}
}

int _main(struct thread *td) {
	initKernel();
	initLibc();
	syscall(11,patcher,td);
	initSysUtil();
	if (!dir_exists("/user/system/webkit/webbrowser/appcache"))
	{
	    mkdir ("/user/system/webkit/webbrowser/appcache", 0777);
	}
	int usbdir = open("/mnt/usb0/.dirtest", O_WRONLY | O_CREAT | O_TRUNC, 0777);
         if (usbdir == -1)
            {
                usbdir = open("/mnt/usb1/.dirtest", O_WRONLY | O_CREAT | O_TRUNC, 0777);
                if (usbdir == -1)
                {
                    systemMessage("No usb found\nUsing Internal Cache");
                    writeCacheDB();
                    return 0;
                }
                else
                {
                    close(usbdir);    
                    if (file_exists("/mnt/usb1/ApplicationCache.db")) 
                    { 
                    systemMessage("Cache file found on USB1");
                    copy_File("/mnt/usb1/ApplicationCache.db","/user/system/webkit/webbrowser/appcache/ApplicationCache.db");
                    systemMessage("Cache restore Complete.");
                    }
					else
					{
						systemMessage("No cache file found on USB1\nUsing Internal Cache");
						writeCacheDB();
					}
                }
            }
            else
            {
                close(usbdir);
                if (file_exists("/mnt/usb0/ApplicationCache.db")) 
                {
                    systemMessage("Cache file found on USB0");
                    copy_File("/mnt/usb0/ApplicationCache.db","/user/system/webkit/webbrowser/appcache/ApplicationCache.db");
                    systemMessage("Cache restore Complete.");
                }
                else
                {
                    systemMessage("No cache file found on USB0\nUsing Internal Cache");
                    writeCacheDB();
                }
            }
	return 0;
}
