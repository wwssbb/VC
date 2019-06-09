#pragma once

typedef unsigned char Byte;
typedef unsigned short Word;
typedef unsigned int DWord;
typedef long Long;


typedef struct  
{

	DWord BMPFileSize;
	Word BMPFileReserve1; //保留字   
	Word BMPFileReserve2; //保留字   
	DWord  ByteNumberOffset; //从文件头到实际位图数据的偏移字节数

}BMPFileHeader;


typedef struct 
{

	DWord BMPInformationHeaderSize;//信息头大小   
	Long BMPWidth;//图像宽度   
	Long BMPHeight;//图像高度   
	Word BMPPlanes;//位平面数，必须为1   
	Word BMPPixelNumber;//每像素位数   
	DWord  CompressionType; //压缩类型   
	DWord  biSizeImage; //压缩图像大小字节数   
	Long  HorizentalResolution; //水平分辨率   
	Long  VerticalResolution; //垂直分辨率   
	DWord  UsedColorNumber; //位图实际用到的色彩数   
	DWord  ImportantColorNumber; //本位图中重要的色彩数   

}BMPInformationHeader;

typedef struct  
{
	Byte RGBBlue; //该颜色的蓝色分量   
	Byte RGBGreen; //该颜色的绿色分量   
	Byte RGBRed; //该颜色的红色分量   
	Byte RGBReserved; //保留值   

}ColorComponent;

typedef struct 
{
	Byte Red;
	Byte Green;
	Byte Blue;

}ImageData;