#include "Camera.hpp"


int eur::Camera::setCameraInput() {
	camera.open(0, cv::CAP_ANY);
	if (!camera.isOpened()) {
		std::cerr << "ERROR: Could not open camera" << std::endl;
		return 1;
	}
	input = CAMERA;

	return 0;
}



int eur::Camera::setCameraInput(int cameraId) {
	camera.open(cameraId, cv::CAP_ANY);
	if (!camera.isOpened()) {
		std::cerr << "ERROR: Could not open camera" << std::endl;
	}
	input = CAMERA;

	return 0;
}


int eur::Camera::setImageInput(std::string path) {

	image = cv::imread(path);
	input = IMAGE;

	return 1;
}



cv::Mat eur::Camera::getFrame() {

	if(input == CAMERA) {
		camera >> inFrame;
	}

	if(input == IMAGE) {
		inFrame = image;
	}

	return inFrame;
}



int eur::Camera::launchDemo() {
	int cameraError = 0;
	if(input != IMAGE) {
		cameraError = setCameraInput();
	}

	if(cameraError) {
		return cameraError;
	}

	return demo();
}



int eur::Camera::launchDemo(int cameraId) {
	int cameraError = setCameraInput(cameraId);
	if(cameraError) {
		return cameraError;
	}

	return demo();
}



int eur::Camera::demo() {
	return 0;
}
