#Chen: for NC post-processing & figure outputs
setwd("D:/2018work/nc")
list.files()
options(repos='http://cran.rstudio.com/')
library("raster")
library("ncdf4")

ncin<-nc_open("AddN_I1850CRUCN_ad_120pp_50year.clm2.h0.0031-01-01-00000.nc")#这个文件历史纪录

print(ncin)#头文件属性
print(head(ncin))
names(ncin$var)#查看所有变量名

#获取经纬度，dimension中的字段，begin
(lon <- ncvar_get(ncin,"lon"))#获取字段
(nlon <- dim(lon))
head(lon)
lat <- ncvar_get(ncin,"lat")
nlat <- dim(lat)
head(lat)
print(c(nlon,nlat))#720,360
#获取经纬度，end
#获取时间，dimension,begin
(time <- ncvar_get(ncin,"time"))
(tunits <- ncatt_get(ncin,"time","units"))
nt <- dim(time)
nt
#获取时间，dimension,end
#获取variable中的变量，begin
#Get a variable

dname <- "TOTLITC" #我的文件中的TOTLITC

#######################################
tmp_array <- ncvar_get(ncin,dname)#获取TOTLITC数据
dlname <- ncatt_get(ncin,dname,"long_name")#长名字
dunits <- ncatt_get(ncin,dname,"units")#单位
fillvalue <- ncatt_get(ncin,dname,"_FillValue")#缺省值
dim(tmp_array)#576,384,30，数据的维度
#获取variable中的变量，end
# get global attributes
title <- ncatt_get(ncin,0,"title")
(institution <- ncatt_get(ncin,0,"institution"))
(datasource <- ncatt_get(ncin,0,"source"))
(references <- ncatt_get(ncin,0,"references"))
(history <- ncatt_get(ncin,0,"history"))
(Conventions <- ncatt_get(ncin,0,"Conventions"))
ls()
#3 Reshaping from raster to rectangular
# load some packages
library(chron)
library(lattice)
library(RColorBrewer)

#3.1 Convert the time variable
# convert time -- split the time units string into fields
tustr <- strsplit(tunits$value, " ")
tdstr <- strsplit(unlist(tustr)[3], "-")
tmonth <- as.integer(unlist(tdstr)[2])
tday <- as.integer(unlist(tdstr)[3])
tyear <- as.integer(unlist(tdstr)[1])
chron(time,origin=c(tmonth, tday, tyear))#提取时间
#3.2 Replace netCDF fillvalues with R NAs
tmp_array[tmp_array==fillvalue$value] <- NA#将缺省值赋值为NA
length(na.omit(as.vector(tmp_array)))
#3.3 Get a single time slice of the data, create an R data frame, and write a .csv file
#3.3.1 Get a single slice of data

tmp_slice <- tmp_array[,,1]#第几个时间单位的数据
tmp_slice <- tmp_array[,,10]
tmp_slice <- tmp_array[,,20]
tmp_slice <- tmp_array[,,100]
tmp_slice <- tmp_array[,,300]
tmp_slice <- tmp_array[,,600]
write.csv(tmp_array,"tmp_array20.csv")#将数据以csv输出
# quick map
image(lon,lat,tmp_slice, col=rev(brewer.pal(10,"RdBu")))#简单出图

# levelplot of the slice
grid <- expand.grid(lon=lon, lat=lat)

cutpts <- c(-50,-40,-30,-20,-10,0,10,20,30,40,50)#设置颜色变化的数据分割点

levelplot(tmp_slice ~ lon * lat, data=grid, at=cutpts, cuts=13, pretty=T, 
          col.regions=(rev(brewer.pal(10,"RdBu"))))#出带有legend的图