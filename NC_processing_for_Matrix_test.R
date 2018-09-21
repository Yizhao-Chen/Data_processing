library(ncdf4)
data <- nc_open("C:\\Users\\dell\\Desktop\\CLM_4.0_Decomp_revision\\model_versions\\clm_4_0_beta2\\I1850CN_VRM_240pp_10yrs.clm2.h0.0010-12.nc")
soil1_beta2 <- ncvar_get(data,"SOIL1C")
soil2_beta2 <- ncvar_get(data,"SOIL2C")
soil3_beta2 <- ncvar_get(data,"SOIL3C")
#soil4_ori <- ncvar_get(data,"SOIL4C")
litr1_beta2 <- ncvar_get(data,"LITR1C")
litr2_beta2 <- ncvar_get(data,"LITR2C")
litr3_beta2 <- ncvar_get(data,"LITR3C")
hr_ori    <- ncvar_get(data,"SOILC_HR")
output <- array(data = 0, dim =6)
output[1] <- soil1_beta2
output[2] <- soil2_beta2
output[3] <- soil3_beta2
#output[4] <- soil4_ori11
output[4] <- litr1_beta2
output[5] <- litr2_beta2
output[6] <- litr3_beta2
#output[7] <- hr_mat
#write.csv(soil1_ori11,"C:\\Users\\dell\\Desktop\\CLM_4.0_Decomp_revision\\model_versions\\clm_4_0_beta2\\ori_10yrs.csv")
writeRaster(output,"C:\\Users\\dell\\Desktop\\test1.dat")
nc_close(data)

