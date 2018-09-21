#Chen: for NC post-processing & figure outputs
setwd("D:/2018work/nc")
list.files()
options(repos='http://cran.rstudio.com/')
library("raster")
library("ncdf4")

ncin<-nc_open("AddN_I1850CRUCN_ad_120pp_50year.clm2.h0.0031-01-01-00000.nc")#����ļ���ʷ��¼

print(ncin)#ͷ�ļ�����
print(head(ncin))
names(ncin$var)#�鿴���б�����

#��ȡ��γ�ȣ�dimension�е��ֶΣ�begin
(lon <- ncvar_get(ncin,"lon"))#��ȡ�ֶ�
(nlon <- dim(lon))
head(lon)
lat <- ncvar_get(ncin,"lat")
nlat <- dim(lat)
head(lat)
print(c(nlon,nlat))#720,360
#��ȡ��γ�ȣ�end
#��ȡʱ�䣬dimension,begin
(time <- ncvar_get(ncin,"time"))
(tunits <- ncatt_get(ncin,"time","units"))
nt <- dim(time)
nt
#��ȡʱ�䣬dimension,end
#��ȡvariable�еı�����begin
#Get a variable

dname <- "TOTLITC" #�ҵ��ļ��е�TOTLITC

#######################################
tmp_array <- ncvar_get(ncin,dname)#��ȡTOTLITC����
dlname <- ncatt_get(ncin,dname,"long_name")#������
dunits <- ncatt_get(ncin,dname,"units")#��λ
fillvalue <- ncatt_get(ncin,dname,"_FillValue")#ȱʡֵ
dim(tmp_array)#576,384,30�����ݵ�ά��
#��ȡvariable�еı�����end
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
chron(time,origin=c(tmonth, tday, tyear))#��ȡʱ��
#3.2 Replace netCDF fillvalues with R NAs
tmp_array[tmp_array==fillvalue$value] <- NA#��ȱʡֵ��ֵΪNA
length(na.omit(as.vector(tmp_array)))
#3.3 Get a single time slice of the data, create an R data frame, and write a .csv file
#3.3.1 Get a single slice of data

tmp_slice <- tmp_array[,,1]#�ڼ���ʱ�䵥λ������
tmp_slice <- tmp_array[,,10]
tmp_slice <- tmp_array[,,20]
tmp_slice <- tmp_array[,,100]
tmp_slice <- tmp_array[,,300]
tmp_slice <- tmp_array[,,600]
write.csv(tmp_array,"tmp_array20.csv")#��������csv���
# quick map
image(lon,lat,tmp_slice, col=rev(brewer.pal(10,"RdBu")))#�򵥳�ͼ

# levelplot of the slice
grid <- expand.grid(lon=lon, lat=lat)

cutpts <- c(-50,-40,-30,-20,-10,0,10,20,30,40,50)#������ɫ�仯�����ݷָ��

levelplot(tmp_slice ~ lon * lat, data=grid, at=cutpts, cuts=13, pretty=T, 
          col.regions=(rev(brewer.pal(10,"RdBu"))))#������legend��ͼ