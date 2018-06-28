# Cache-Install

payload to (re)install <b>ApplicationCache.db</b> to the ps4.

the payload will look for a file called <b>ApplicationCache.db</b> on the root of a usb drive and install it to the console.

if no file is found on the usb drive or if there is no usb drive found the payload will create and install a basic <b>ApplicationCache.db</b> to the console.

using the basic install you can access the landing page through the ps4 <b>user guide</b> or the webbrowser by going to http://cache/index.html

if you already have another offline cache installed you can back that up using the DB_SG_Backup payload and place the <b>ApplicationCache.db</b> from that backup on the root of a usb drive and use this payload to reinstall it if you have to delete the browser data or lose it for any reason.


 