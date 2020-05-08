#pragma once

#pragma pack(push,4)

#ifndef FR_IMAGE_HEIGHT
#define FR_IMAGE_HEIGHT 224	//Height of FR Input Image
#define FR_IMAGE_WIDTH  224 //Width of FR Input Image 
#define FR_IMAGE_SIZE 224*224*3
#define FR_FEATURES_DIM 512 //Features Dimension of FR Input Image 
#define Gender_Classes	2			
#define Age_Classes	7	
#endif

typedef enum ColorFormat {
	RGB = 30,
	YUYV,

};

typedef enum  SmartRetail {		 //see GvRetail_SetInfo()/GeoStoryLine_ExtraInfo()
	SmartRetail_SetGroupID = 100,//nCam=CamId,if (pData==NULL) Auto detect Max Face and assign Group ID;else (pData=char *UUID)
	FR_bEnableAgeGender,		 //nCam=CamId,value=1 Enable,value=0 Disable
	FR_DelFaceID,				 //nCam=CamId,Del FaceID by UUID see (pData=char *UUID)	
	FR_SetConfidenceTH,          //nCam=CamId,value = Th, default{FR=68; SmartRetail=60}
	FR_FacePosition,			 //nCam=CamId,value = 0(Front),value = 1(Side),value = 2(Any),
	FR_MiniFaceSize,			 //nCam=CamId,value = size 
	FR_bMaxFaceOnly,			 //nCam=CamId,value = {1:MaxFace;0:None}
	FR_bDBKeepEnrollFaceImg,	 //[Global params] value = {1:Keep;0:None}
	FR_FaceDwellTime,			 //value = Dwell Time 
	FR_SetFaceBrightnessTH,		 //[RD use only]
	FR_SetFaceQualityTH,		 //[RD use only]
	FR_GetDongleInfo,			 //[Global params]  pData={GvDnogleInfo()} //Louis Dongle 20190426

	FR_CallBack_DongleInfo,		 //[CallBack CMD] [Global params] pData={GvDnogleInfo()} use GeoStoryLine_ExtraInfo();

	FR_SetSolutionType,			 //[Global params][FR,Value=1][Smart Retail,Value=2]
	FR_GetMaxFaceUUID,			 //nCam=CamId,return Max UUID (pData=char *UUID)	
	FR_SetCamType,				 //nCam=CamId, value={1:In};{2:Out};{3:POS(Max Face)};{4:Signage(Max face)};{5:Use SR SDK};
	FR_CallBack_IOInfo,			 //nCam=CamId, value=Module,pData=(int) pin
	FR_Updated_UserInfo,		 //
	FR_Reload,
	FR_MaxFaceSize,				 //nCam=CamId,value = size 
	FR_SetUnConfidenceTH,        //nCam=CamId,value = Th
	FR_BeMaskUpdated,			 //nCam=CamId
	FR_Set_Unknown_time,         //nCam=CamId,value = time(sec)
	FR_SetVAType,			     //[Face Recognition,Value=1][Face Attributes,Value=2]
	FR_SetHWAcceleration,		 //[Off,Value=0][On,Value=1]
	FR_Set_LivenessDetect,		 //nCam=CamId,value = {1:LivenessDetect;0:None}
};

typedef enum EnrollMsg {	 //see EnrollFeatures 
	FR_ImageQuality = 1,	     //color quality
	FR_ImageBlur,				 //quality too blur
	FR_ImageSize,				 //face size FR_IMAGE_HEIGHTxFR_IMAGE_WIDTH up & area ratio
	FR_FaceLocation,			 //center of image
	FR_FaceTooBright,			 //mean > 192
	FR_FaceTooDark,				 //mean < 96
	FR_FaceNotFront,			 //angle < 15, phi < 10
	FR_FaceNotFound,			 //No Face detected 
	FR_AVXNotFound,				 //cpu AVX mode not detected 
	FR_LandMarkNotFound,		 //landmark model dat file not found 
};


typedef struct tagGVGETFACEFEATURE
{
	int nVersion;	//Reserved (set to 0)
					//Input
	unsigned char* pIn;
	int nWidth;
	int nHeight;
	unsigned short nReserved;
	bool bYUY2;		//Reserved, always false for now
	BYTE nCntROI;
	POINT ptROI[4];
	POINT ptLandmark[6];
	BYTE nReservedIn[16];
	//Output
	BYTE nReservedOut[18];
	BYTE nAge;
	BYTE nGender;
	int nFeatureDim;
	float fFeature[1024];

	tagGVGETFACEFEATURE() : nVersion(0), nReserved(0), bYUY2(false), nAge(0), nGender(0), nFeatureDim(0)
	{
		memset(nReservedIn, 0, sizeof(nReservedIn));
		memset(nReservedOut, 0, sizeof(nReservedOut));
		memset(fFeature, 0, sizeof(fFeature));
	}
}*PGVGETFACEFEATURE, GVGETFACEFEATURE;

#pragma pack(pop)