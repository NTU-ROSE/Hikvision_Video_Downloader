# A Tool for Downloading Video Clips from Hikvision VMS
A simple command line tool for quickly downloading video clips from Hikvision VMS. Currently only work in Linux X64 system.

### Compile
``` bash
cd Hikvision_Video_Downloader
make all
```

### Runing
__Hikvision_Video_Downloader Class: 3 inputs__
1. Device IP Address _(Use Default 8000 port)_
2. Username
3. Password
4. Camera Channel
5. Year
6. Month
7. Day
8. Start_Hour
9. Start_Minute
10. Start_Second
11. Stop_Hour
12. Stop_Minute
13. Stop_Second
14. Video Saving Path
``` bash
./Hikvision_Video_Downloader 192.0.0.64 admin 12345 1 2019 3 25 12 0 0 12 5 0 ./test.mp4
```

### TODO
- [ ] Windows Compatible
