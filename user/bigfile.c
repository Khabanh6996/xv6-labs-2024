#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"
#include "kernel/fs.h"

int
main()
{
  char buf[BSIZE];
  int fd, sectors;

  fd = open("big.file", O_CREATE | O_WRONLY);
  if(fd < 0){
    printf("bigfile: cannot open big.file for writing\n");
    exit(1);
  }

  sectors = 0;
  while(1){
    // Điền dữ liệu giả vào buffer
    *(int*)buf = sectors;
    
    // Ghi 1 block (1024 bytes) vào file
    int cc = write(fd, buf, sizeof(buf));
    if(cc <= 0)
      break; // Thoát vòng lặp khi không thể ghi thêm (hết giới hạn)

    sectors++;

    // Cứ mỗi 100 blocks được ghi thành công thì in ra một dấu chấm
    if (sectors % 100 == 0)
      printf(".");
  }

  printf("\nwrote %d blocks\n", sectors);

  // Kiểm tra xem số block ghi được có đúng bằng giới hạn tối đa thiết kế không
  if(sectors != 65803) {
    printf("bigfile: file is too small\n");
    close(fd);
    exit(1);
  }

  printf("done; ok\n");
  close(fd);
  exit(0);
}
