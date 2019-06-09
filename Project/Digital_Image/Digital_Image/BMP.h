#pragma once

typedef unsigned char Byte;
typedef unsigned short Word;
typedef unsigned int DWord;
typedef long Long;


typedef struct  
{

	DWord BMPFileSize;
	Word BMPFileReserve1; //������   
	Word BMPFileReserve2; //������   
	DWord  ByteNumberOffset; //���ļ�ͷ��ʵ��λͼ���ݵ�ƫ���ֽ���

}BMPFileHeader;


typedef struct 
{

	DWord BMPInformationHeaderSize;//��Ϣͷ��С   
	Long BMPWidth;//ͼ����   
	Long BMPHeight;//ͼ��߶�   
	Word BMPPlanes;//λƽ����������Ϊ1   
	Word BMPPixelNumber;//ÿ����λ��   
	DWord  CompressionType; //ѹ������   
	DWord  biSizeImage; //ѹ��ͼ���С�ֽ���   
	Long  HorizentalResolution; //ˮƽ�ֱ���   
	Long  VerticalResolution; //��ֱ�ֱ���   
	DWord  UsedColorNumber; //λͼʵ���õ���ɫ����   
	DWord  ImportantColorNumber; //��λͼ����Ҫ��ɫ����   

}BMPInformationHeader;

typedef struct  
{
	Byte RGBBlue; //����ɫ����ɫ����   
	Byte RGBGreen; //����ɫ����ɫ����   
	Byte RGBRed; //����ɫ�ĺ�ɫ����   
	Byte RGBReserved; //����ֵ   

}ColorComponent;

typedef struct 
{
	Byte Red;
	Byte Green;
	Byte Blue;

}ImageData;