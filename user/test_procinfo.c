#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/procinfo.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  struct procinfo info;
  
  // Lấy PID của chính chương trình đang chạy này
  int my_pid = getpid(); 

  // Truyền PID và địa chỉ bộ nhớ của biến info vào system call procinfo
  if(procinfo(my_pid, &info) == 0){
    printf("Process: %s\n", info.name);
    printf("PID: %d, PPID: %d\n", info.pid, info.ppid);
    printf("State: %d\n", info.state); 
    
    // Ép kiểu info.sz về int để khớp với %d
    printf("Memory: %d bytes\n", (int)info.sz); 
  } else {
    printf("Error: procinfo failed to retrieve data.\n");
  }

  exit(0);
}