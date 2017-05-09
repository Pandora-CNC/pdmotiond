# pdmotiond
Motion deamon for the DDCSV1.1

This utility serves two purposes.
First, it runs in the background as a deamon and uses Unix socket IPC to communicate with the client application
and controls the CNC functionality through the motiondev driver.
Second, it allows CLI access to the deamon by connecting to the IPC socket (instead of the GUI application) and controlling
the deamon in this way.
