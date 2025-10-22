#define OLC_GFX_OPENGL33
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include <opencv2/videoio.hpp>
#include <iostream>
#include <cmath> 

class LinuxPGEWebcam : public olc::PixelGameEngine
{
public:
	LinuxPGEWebcam()
	{
		sAppName = "LinuxPGEWebcam";
	}

	//Camera utils:
	// OpenCV video capture object.
	olc::Sprite* pCameraFrame = nullptr;
	olc::Decal* pCameraDecal = nullptr;
	cv::VideoCapture cap;
	int nCamWidth = 640;
	int nCamHeight = 480;


public:

	bool setup_cam() {
		cap.open(0);
		if (!cap.isOpened())
		{
			std::cerr << "ERROR: Could not open camera device." << std::endl;
			return false;
		}

		cap.set(cv::CAP_PROP_FRAME_WIDTH, nCamWidth);
		cap.set(cv::CAP_PROP_FRAME_HEIGHT, nCamHeight);
		
		pCameraFrame = new olc::Sprite(nCamWidth, nCamHeight);
		pCameraDecal = new olc::Decal(pCameraFrame);
		return true;
	};

	bool RenderCameraFrame(){
		cv::Mat frame;
		cap.read(frame); 

		if (frame.empty())
		{
			return 1;
		}
		
		// --- Update the Sprite with the new frame data ---
		for (int y = 0; y < frame.rows; y++)
		{
			for (int x = 0; x < frame.cols; x++)
			{
				cv::Vec3b color = frame.at<cv::Vec3b>(y, x);
				pCameraFrame->SetPixel(x, y, olc::Pixel(color[2], color[1], color[0])); // R, G, B
			}
		}

		return 0;
	};


	bool OnUserCreate() override
	{
		if (!setup_cam()) return false;
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{

		Clear(olc::BLANK);	

		bool render;
		render = RenderCameraFrame();
		
		if (render){
			return 1;
		}

		//DrawSprite({0, 0}, pCameraFrame);  // Default is flipped unlike a mirror
		DrawSprite({0, 0}, pCameraFrame, 1, olc::Sprite::HORIZ); // Flipped like a mirror.

	 	return true;
	}

	bool OnUserDestroy() override
	{
		delete pCameraDecal;
		delete pCameraFrame;

		if(cap.isOpened())
		{
			cap.release();
		}
		return true;
	}
};

int main()
{
	LinuxPGEWebcam demo;
	if (demo.Construct(demo.nCamWidth, demo.nCamHeight, 1, 1))
		demo.Start();
	return 0;
}
