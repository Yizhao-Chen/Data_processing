library(ncdf4)
setwd("E:\\SPEI")
data <- nc_open("spei01.nc")
data <- ncvar_get(data)
for(i in 960:1380){
  filename <- sprintf("mm01%d.raw",i)
  zz <- file(filename,'wb')
  data1 <- data[1:720,1:360,i]
  for(j in 1:360){
    line = 360 - j + 1
    data2 <- data1[1:720,line]
    writeBin(data2,zz)
  }
  close(zz)
}









