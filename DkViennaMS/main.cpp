/**************************************************
 * 	main.cpp
 *
 *	Created on:	16.08.2011
 * 	    Author:	Markus Diem
 *     Company:	Vienna University of Technology
 **************************************************/

#include "DkMSModule.h"		// MSTEx (ICDAR 2015)
#include "DkRgbModule.h"	// RGB images
#include "DkMvModule.h"		// MegaVision

// definition
std::string helpText();

int main(int argc, char *argv[]) {

	if (argc < 3 || argc > 4) {
		std::cout << "Wrong number of input arguments: " << argc-1 << " (2-3 expected)" << std::endl;
		std::cout << helpText();
		return 1;
	}

	// commented for debugging - uncomment!
	try {

		if (argc == 3) {
			std::cout << "MSI mode is active..." << std::endl;
			std::string folderName(argv[1]);
			std::replace(folderName.begin(), folderName.end(), '\\', '/');
			std::wstring folderNameW(folderName.begin(), folderName.end());
			std::string imageName(argv[2]);

			DkMSModule module(folderNameW);
			if (!module.load())
				return 1;

			module.compute();
			module.saveImage(imageName);
		}
		else if (argc == 4 && std::string(argv[1]) == "-rgb") {
			std::cout << "RGB mode is active..." << std::endl;
			std::string fileName(argv[2]);
			std::replace(fileName.begin(), fileName.end(), '\\', '/');
			std::wstring folderNameW(fileName.begin(), fileName.end());
			std::string imageName(argv[3]);

			DkRgbModule module(folderNameW);
			module.load();
			module.compute();
			module.saveImage(imageName);
		}
		else if (argc == 4 && std::string(argv[1]) == "-mv") {
			std::cout << "MegaVision mode is active..." << std::endl;
			std::string fileName(argv[2]);
			std::replace(fileName.begin(), fileName.end(), '\\', '/');
			std::wstring folderNameW(fileName.begin(), fileName.end());
			std::string imageName(argv[3]);

			DkMVModule module(folderNameW);

			if (!module.load())
				return 1;

			module.compute();
			
			if (module.saveImage(imageName)) {
				std::string in(imageName.begin(), imageName.end());
				std::cout << "pseudo color image written to " << in << std::endl;
			}
		}
		else {
			std::cout << "error: unknown command" << std::endl;
			std::cout << "argc = " << argc << std::endl;
			std::cout << helpText();
		}
	}
	catch(cv::Exception cvex) {
		printf("Error in function %s, in file %s: msg %s\n", cvex.func.c_str(), cvex.file.c_str(), cvex.err.c_str());
		std::cout << helpText() << std::endl;
		return 2;
	}

	return 0;

}

std::string helpText() {

	std::string ht;
	ht += "Welcome to ViennaMS.\n\n";
	ht += "ViennaMS.exe <folder_name> <output_img_name>\n";
	ht += "  <folder_name> path to the MS folder.\n       The folder should contain 8 image files (FXXs.png) where XX is the channel number.\n";
	ht += "  <output_img_name> the output image name.\n\n";
	ht += "RGB mode: ViennaMS.exe -rgb <file_path> <output_img_name>\n";
	ht += "  <file_path> path to an RGB image.\n";
	ht += "  <output_img_name> the output image name.\n\n";
	ht += "  Enjoy your day!\n";

	return ht;
}