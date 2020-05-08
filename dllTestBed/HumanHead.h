#ifndef _HUMANHRAD_DETECTION_H_
#define _HUMANHRAD_DETECTION_H_
#include <afx.h>
#include <Windows.h>
#include "GeoFR_InfoDef.h"

#ifdef HUMANHRADDETECTIONDLL_EXPORTS
#define FACEDETECTIONDLL_API __declspec(dllimport) 
#else
#define HUMANHRADDETECTIONDLL_API __declspec(dllexport) 
#endif

//#define	 _is_Gender_Reg 0

enum
{
	CASCADE_DO_CANNY_PRUNING = 1,
	CASCADE_SCALE_IMAGE = 2,
	CASCADE_FIND_BIGGEST_OBJECT = 4,
	CASCADE_DO_ROUGH_SEARCH = 8
};

typedef struct FR_Debug_info {
	float theta;
	float phi;
	float theta_thres;
	float phi_thres;
	int angle_pass;
	float img_q;
	float img_q_thres;
	int img_q_pass;
	int nTop;
	char** Top_name;
	float* Top_score;
	float conf_gap;
	float conf_gap_thres;
	int gap_pass;
	float brightMean;
	float bright_thres_up;
	float bright_thres_low;
	int bright_pass;
	float conf_thres;
	float unconf_thres;
	int unconf_pass;
	int conf_pass;
	int SVM_pass;
	char pred_name[128];
	int pred_label;
	float pred_score;
	int counting;

	FR_Debug_info() {
		nTop = 0;
		Top_name = NULL;
		Top_score = NULL;
		Reset();
	}

	~FR_Debug_info() {
		Delete_Top_n_Space();
	}

	void Create_Top_n_Space(int _nTop) {
		Delete_Top_n_Space();
		nTop = _nTop;
		if (nTop) {
			Top_name = new char*[nTop];
			Top_score = new float[nTop];
			for (int i = 0; i < nTop; i++) {
				Top_name[i] = new char[512];
				sprintf_s(Top_name[i], 512, "");
				Top_score[i] = -1;
			}
		}
	}

	void Delete_Top_n_Space() {
		if (Top_name) {
			for (int i = 0; i < nTop; i++) {
				delete[] Top_name[i];
				Top_name[i] = NULL;
			}
			delete[] Top_name;
			Top_name = NULL;
		}
		if (Top_score) {
			delete[] Top_score;
			Top_score = NULL;
		}
	}

	void Reset() {
		theta = phi = theta_thres = phi_thres = -1;
		angle_pass = -1;
		img_q = img_q_thres = img_q_pass = -1;
		Create_Top_n_Space(nTop);
		conf_gap = conf_gap_thres = -1;
		gap_pass = -1;
		brightMean = bright_thres_up = bright_thres_low = -1;
		bright_pass = -1;
		conf_thres = unconf_thres = SVM_pass = -1;
		unconf_pass = conf_pass = -1;
		sprintf_s(pred_name, "");
		pred_label = -1;
		pred_score = -1;
		counting = 0;
	}
};
HUMANHRADDETECTIONDLL_API void* CreateHumanDetection();
HUMANHRADDETECTIONDLL_API void ReleaseHumanDetection(void *obj);

class IHumanHeadDetection
{
public:
	virtual bool CreateLM(int width, int height, char* file1, char* file2) = 0;
	virtual void ReleaseLM() = 0;
	virtual int CreateFR(int nCam, int width, int height, char* file01, char* file02, char* file03, char* file04,
		int &fr_alarm, int &fps_known, int &fps_unknown, int* nCamDB, int countDB, int &age_diff, int &face_min, int &face_dwell_time,
		int &auto_enroll_time, bool &auto_enroll_on, bool &auto_enroll_findmaxface_on, int *Retail_DetecTime, int &confidenceGap,
		int *unknown_time = NULL) = 0;
	virtual void CNN_face_recog(unsigned char *src, int width, int height, RECT &face, char *facerecog, char *uuid, int &facelabel, bool &bUnknown,
		float &frscore, float* gender_score, float* age_score, unsigned char *chipsrc, bool bRetail, bool &bPose_front, unsigned char *chipretail, 
		int &group_id, float *features, double &theta, double &phi, double &roll, bool &bUseServerDB, bool bUseOpenVinoAttributes, void* debug_info = NULL) = 0;
	virtual void CNN_face_recog(unsigned char *src, int width, int height, RECT &face, float* gender_score, float* age_score, bool bRetail, 
		double &theta, double &phi, bool &bPoseFront, bool bUseOpenVinoAttributes, void* debug_info = NULL) = 0;
	virtual void ReleaseFR() = 0;
	virtual bool CreateFR(int nCam, int width, int height, char* file01, char* file02, char* file03, char* file04) = 0;
	virtual bool Auto_EnrollFR(unsigned char *src, int width, int height, float* gender_score, float* age_score, int &enroll_id,
		unsigned char *chipsrc, char *UUID, float *feature) = 0;
	virtual bool EraseRetail(int nCam, int label_num, char *uuid) = 0;
	virtual bool ClearALL(int nCam) = 0;
	virtual void EnrollRefresh() = 0;
	virtual bool SetFaceInfo(int nCam, int iCmd, int value, void *pData) = 0;
	virtual int EnrollFeatures(int nCam, unsigned char *src, int width, int height, char *UUID, int &group_id, float *features, char *enroll_name) = 0;
	virtual void EraseRefresh() = 0;
	virtual int FaceInput(unsigned char *src, int width, int height, bool bAutoEnroll,
		char *name, float& gender, float& age, RECT &rect, float &frscore, int &facelabel, float *features, char *uuid, int &group_id) = 0; //for Joe
	virtual void SaveFRDebugInfo(FR_Debug_info& pData) = 0;
	virtual int FaceInput_Playback(int nCam, unsigned char *pIn, int nWidth, int nHeight, float *features, bool bFlip, bool bDoFaceDetect, float& gender, float& age) = 0; //for Jordan *features size see FR_FEATURES_DIM
	virtual int FeatureCmp(int nCam, float *featureInf, float *featureCmp, float &score) = 0; //for Jordan
	virtual bool checkCpuAVX() = 0;
	//===AICentral===//
	virtual int CreateFR_AICentral(int nCam) = 0;
	virtual int FaceInput_AICentral(int nCam, tagGVGETFACEFEATURE& faceFeature) = 0;
	virtual void ReleaseFR_AICentral(int nCam) = 0;
	//===============//
protected:
	IHumanHeadDetection() {};
	~IHumanHeadDetection() {};
};

#endif