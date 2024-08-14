




/*
                       Description: This file prosseses images and adds filters to it with 15 different options.
*/   






#include "Image_Class.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>
using namespace std;



// Function to add a simple frame to the image
void addSimpleFrame(Image& image, int frameColor, int borderWidth) {
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            if (x < borderWidth || x >= image.width - borderWidth ||
                y < borderWidth || y >= image.height - borderWidth) {
                switch (frameColor) {
                    case 1:
                        image(x, y, 0) = 0;
                        image(x, y, 1) = 0;
                        image(x, y, 2) = 0;
                        break;
                    case 2:
                        image(x, y, 0) = 255;
                        image(x, y, 1) = 255;
                        image(x, y, 2) = 255;
                        break;
                    case 3:
                        image(x, y, 0) = 0;
                        image(x, y, 1) = 0;
                        image(x, y, 2) = 255;
                        break;
                    default:
                        cout << "Invalid please enter number of valid frame color." << endl;
                        return;
                }
            }
        }
    }
}

// Function to add a fancy frame to the image
void addFancyFrame(Image& image, int frameColor, int borderWidth, const int decorationWidth = 60) {
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            if (x < borderWidth || x >= image.width - borderWidth ||
                y < borderWidth || y >= image.height - borderWidth) {
                switch (frameColor) {
                    case 1:
                        image(x, y, 0) = 0;
                        image(x, y, 1) = 0;
                        image(x, y, 2) = 0;
                        break;
                    case 2:
                        image(x, y, 0) = 255;
                        image(x, y, 1) = 255;
                        image(x, y, 2) = 255;
                        break;
                    case 3:
                        image(x, y, 0) = 0;
                        image(x, y, 1) = 0;
                        image(x, y, 2) = 255;
                        break;
                    default:
                        cout << "Invalid please enter number of valid frame color." << endl;
                        return;
                }
            }

            if ((x >= borderWidth && x < borderWidth + decorationWidth) || (x < image.width - borderWidth && x >= image.width - borderWidth - decorationWidth) ||
                (y >= borderWidth && y < borderWidth + decorationWidth) || (y < image.height - borderWidth && y >= image.height - borderWidth - decorationWidth)) {
                switch (frameColor) {
                    case 1:
                        image(x, y, 0) = 255;
                        image(x, y, 1) = 255;
                        image(x, y, 2) = 255;
                        break;
                    case 2:
                        image(x, y, 0) = 0;
                        image(x, y, 1) = 0;
                        image(x, y, 2) = 0;
                        break;
                    case 3:
                        image(x, y, 0) = 255;
                        image(x, y, 1) = 255;
                        image(x, y, 2) = 255;
                        break;
                    default:
                        cout << "Invalid please enter number of valid frame color." << endl;
                        return;
                }
            }
        }
    }
}



// Function to resize an image to a specified width and height
void resizeImage(Image& img, int newWidth, int newHeight, Image& resizedImage) {
    // Calculate scaling factors for width and height
    float scaleX = (float)newWidth / img.width;
    float scaleY = (float)newHeight / img.height;

    // Loop through each pixel of the resized image
    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            // Calculate corresponding coordinates in the original image
            int originalX = static_cast<int>(x / scaleX);
            int originalY = static_cast<int>(y / scaleY);

            // Copy pixel value from original image to resized image
            for (int c = 0; c < 3; ++c) {
                resizedImage(x, y, c) = img(originalX, originalY, c);
            }
        }
    }
}

// Function to merge two images by resizing the smaller one to match the bigger one
Image mergeByResizing(Image& img1, Image& img2) {
    // Determine the dimensions of the resulting image
    int mergedWidth = max(img1.width, img2.width);
    int mergedHeight = max(img1.height, img2.height);

    // Create resized images
    Image resizedImg1(mergedWidth, mergedHeight);
    Image resizedImg2(mergedWidth, mergedHeight);

    // Resize images
    resizeImage(img1, mergedWidth, mergedHeight, resizedImg1);
    resizeImage(img2, mergedWidth, mergedHeight, resizedImg2);

    // Create a new image for the merged result
    Image mergedImage(mergedWidth, mergedHeight);

    // Loop through each pixel of the merged image
    for (int y = 0; y < mergedHeight; ++y) {
        for (int x = 0; x < mergedWidth; ++x) {
            //merge the colors of the two images
            for (int c = 0; c < 3; ++c) {
                mergedImage(x, y, c) = (resizedImg1(x, y, c) + resizedImg2(x, y, c)) / 2; // averaging
            }
        }
    }

    return mergedImage;
}

// Function to merge two images by taking the common area of the smaller width and height
Image mergeByCommonArea(Image& img1, Image& img2) {
    // Determine the dimensions of the resulting image
    int mergedWidth = min(img1.width, img2.width);
    int mergedHeight = min(img1.height, img2.height);

    // Create a new image for the merged result
    Image mergedImage(mergedWidth, mergedHeight);

    // Loop through each pixel of the merged image
    for (int y = 0; y < mergedHeight; ++y) {
        for (int x = 0; x < mergedWidth; ++x) {
            // merge the colors of the two images
            for (int c = 0; c < 3; ++c) {
                mergedImage(x, y, c) = (img1(x, y, c) + img2(x, y, c)) / 2; // averaging
            }
        }
    }

    return mergedImage;
}

//very Important The (Blur) program takes about a minute to execute, because the blur radius = 50
// to shows blurred more clear to you, so please wait a minute and Thank you very much.
const int blurRadius = 35; // Constant blur radius

// Function to compute the Gaussian kernel weights
void computeGaussianKernel(vector<double>& kernel, int radius, double sigma) {
    double sum = 0.0;
    kernel.resize(2 * radius + 1);

    for (int x = -radius; x <= radius; ++x) {
        double weight = exp(-(x * x) / (2 * sigma * sigma));
        kernel[x + radius] = weight;
        sum += weight;
    }
    // Normalize the kernel
    for (int i = 0; i < 2 * radius + 1; ++i) {
        kernel[i] /= sum;
    }
}

// Function to apply Gaussian blur to the image
void applyGaussianBlur(Image& image) {
    int radius = blurRadius;
    double sigma = radius / 3.0;

    // Compute Gaussian kernel weights
    vector<double> kernel;
    computeGaussianKernel(kernel, radius, sigma);

    Image tempImage(image.width, image.height);

    // Apply horizontal blur

    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            for (int c = 0; c < image.channels; ++c) {
                double newValue = 0.0;
                for (int i = -radius; i <= radius; ++i) {
                    int newX = x + i;
                    if (newX >= 0 && newX < image.width) {
                        newValue += kernel[i + radius] * image(newX, y, c);
                    }
                }
                tempImage(x, y, c) = static_cast<unsigned char>(newValue);
            }
        }
    }

    // Apply vertical blur
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            for (int c = 0; c < image.channels; ++c) {
                double newValue = 0.0;
                for (int i = -radius; i <= radius; ++i) {
                    int newY = y + i;
                    if (newY >= 0 && newY < image.height) {
                        newValue += kernel[i + radius] * tempImage(x, newY, c);
                    }
                }
                image(x, y, c) = static_cast<unsigned char>(newValue);
            }
        }
    }
}


// Function to simulate old television effect
void applyOldTVEffect(Image& image) {
    // Define parameters for distortion and color degradation
    const int distortionStrength = 10; // Strength of distortion effect
    const int colorDegradation = 30;   // Strength of color degradation

    // Create random number generator and distributions for distortion and color degradation
    default_random_engine generator;
    uniform_int_distribution<int> distortionDistribution(-distortionStrength, distortionStrength);
    uniform_int_distribution<int> colorDistribution(-colorDegradation, colorDegradation);


    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            // Apply distortion effect to pixel coordinates
            int newX = x + distortionDistribution(generator);
            int newY = y + distortionDistribution(generator);

            // Ensure distorted coordinates stay within image boundaries
            newX = max(0, min(image.width - 1, newX));
            newY = max(0, min(image.height - 1, newY));

            // Get pixel color components at distorted coordinates
            unsigned char r = image(newX, newY, 0);
            unsigned char g = image(newX, newY, 1);
            unsigned char b = image(newX, newY, 2);

            // Add random noise to color channels
            r = max(0, min(255, static_cast<int>(r) + colorDistribution(generator)));
            g = max(0, min(255, static_cast<int>(g) + colorDistribution(generator)));
            b = max(0, min(255, static_cast<int>(b) + colorDistribution(generator)));

            // Set the pixel color with the distorted values
            image(x, y, 0) = r;
            image(x, y, 1) = g;
            image(x, y, 2) = b;
        }
    }
}





int main() {
    while(true) {

        string choice;
        cout << "Welcome to our image processing program\n";
        cout << "Please choose which filter you want to use\n";
        cout << "1: Grayscale\n2: Black and white\n3: Colour inversion\n4: Merge Images\n5: Image flip\n6: Rotate Image\n7: Image brightness\n8: Image crop\n9: Picture Frame\n10: Detect Image Edges\n11: Image resize\n12: Blur Images\n13: Sunlight\n14: Oil Painting\n15: Wano old TV\n ";
        cout<<"Note: type \"exit\" to exit the program\n";
        cin >> choice;

        if (choice == "1"){
            string filename;
            cout << "Please enter image name: ";
            cin >> filename;
            Image image(filename);

            for (int i=0 ; i < image.width;++i ) {
                for (int j = 0; j < image.height; ++j) {
                    unsigned int avg = 0;
                    for (int k = 0; k < 3; ++k) {
                        avg += image(i, j, k);
                    }
                    avg = avg /3;
                    for (int k=0 ; k < 3 ; ++k)
                        image(i,j,k)=avg;
                }
            }

            cout << "Please enter image name to store new image,\n";
            cout << "and specify extension (.jpg, .bmp, .png, .tga): ";

            cin >> filename;
            image.saveImage(filename);
            cout << "New image saved." << endl;


        }
        else if (choice == "2"){
            string filename;
            cout << "Please enter image name: ";
            cin >> filename;
            Image image(filename);

            for (int i=0 ; i < image.width;++i ) {
                for (int j = 0; j < image.height; ++j) {
                    unsigned int avg = 0;
                    for (int k = 0; k < 3; ++k) {
                        avg += image(i, j, k);
                    }
                    avg = avg /3;
                    for (int k=0 ; k < 3 ; ++k)
                        image(i,j,k)=avg;
                }
            }

            for (int i=0 ; i < image.width;++i ){
                for (int j = 0; j < image.height; ++j){
                    for (int k=0 ; k<3 ; ++k){
                        if (image(i,j,k)<=150) //let the threshold = 200
                            image(i,j,k)=0;
                        else
                            image(i,j,k)=255;
                    }
                }
            }

            cout << "Please enter image name to store new image,\n";
            cout << "and specify extension (.jpg, .bmp, .png, .tga): ";

            cin >> filename;
            image.saveImage(filename);
            cout << "New image saved." << endl;


        }
        else if (choice == "3") {
            string filename;
            cout << "Please enter image name: ";
            cin >> filename;

            Image image(filename);

            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    for (int k = 0; k < 3; ++k) {
                        unsigned int rn = image(i, j, k);
                        image(i, j, k) = 255 - rn;
                    }
                }
            }

            cout << "Please enter image name to store new image,\n";
            cout << "and specify extension (.jpg, .bmp, .png, .tga): ";

            cin >> filename;
            image.saveImage(filename);
            cout << "New image saved." << endl;


        }
        else if (choice == "5"){
            string filename;
            cout << "Please enter image name: ";
            cin >> filename;
            Image image(filename);

            char x;
            cout<<"Please choose which way to flip\na: Horizontally\nb: Vertically\n";
            cin>>x;
            if (x == 'a') {
                for (int j = 0; j < image.height; ++j) {
                    for (int i = 0; i < image.width / 2; ++i) {
                        for (int k = 0; k < 3; ++k) {
                            int temp = image(i, j, k);
                            image(i, j, k) = image(image.width - i - 1, j, k);
                            image(image.width - i - 1, j, k) = temp;
                        }
                    }
                }
            }else if (x == 'b') {
                for (int i = 0; i < image.width; ++i) {
                    for (int j = 0; j < image.height/2 ; ++j) {
                        for (int k = 0; k < 3; ++k) {
                            int temp = image(i, j, k);
                            image(i, j, k) = image(i, image.height - j - 1, k);
                            image(i, image.height - j - 1, k) = temp;
                        }
                    }
                }
            }else
                cout<<"Please enter a valid choice";

            cout << "Please enter image name to store new image,\n";
            cout << "and specify extension (.jpg, .bmp, .png, .tga): ";

            cin >> filename;
            image.saveImage(filename);
            cout << "New image saved." << endl;


        }
        else if (choice == "7" ){
            string filename;
            cout << "Please enter image name: ";
            cin >> filename;
            Image image(filename);

            char x;
            cout<<"Please choose what to do\na: Darken\nb: Brighten\n";
            cin>>x;
            if (x == 'a') {
                for (int i = 0; i < image.width; ++i) {
                    for (int j = 0; j < image.height; ++j) {
                        for (int k = 0; k < 3; ++k) {
                            float rn = image(i, j, k);
                            image(i, j, k) = rn * 0.5;
                        }
                    }
                }
            }else if (x == 'b') {
                for (int i = 0; i < image.width; ++i) {
                    for (int j = 0; j < image.height; ++j) {
                        for (int k = 0; k < 3; ++k) {
                            float rn = image(i, j, k);
                            image(i, j, k) = rn + (255- rn)*0.125;
                        }
                    }
                }
            }else
                cout<<"Please enter a valid choice";

            cout << "Please enter image name to store new image,\n";
            cout << "and specify extension (.jpg, .bmp, .png, .tga): ";

            cin >> filename;
            image.saveImage(filename);
            cout << "New image saved." << endl;



        }
        else if (choice == "8"){
            string filename;
            cout << "Please enter image name: ";
            cin >> filename;
            Image image(filename);
            int x, y, w, h;
            cout << "Please enter the starting point\n";
            cout << "Enter x: ";
            cin >> x;
            cout << endl << "Enter y: ";
            cin >> y;
            cout << "Please enter the dimensions\n";
            cout << "Enter w: ";
            cin >> w;
            cout << endl << "Enter h: ";
            cin >> h;

            // Create a new Image object for the cropped image
            Image newImage(w, h);

            // Perform cropping
            for (int i = 0; i < w; ++i) {
                for (int j = 0; j < h; ++j) {
                    for (int k = 0; k < 3; ++k) {
                        newImage(i, j, k) = image(x + i, y + j, k);
                    }
                }
            }
            cout << "Please enter image name to store new image, and specify extension (.jpg, .bmp, .png, .tga): ";
            cin >> filename;
            newImage.saveImage(filename);
            cout << "New image saved." << endl;


        }
        else if (choice == "13"){
            string filename;
            cout << "Please enter image name: ";
            cin >> filename;
            Image image(filename);

            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    for (int k = 0; k < 3; ++k) {
                        float intensity = image(i, j, k);

                        // Apply sunlight filter
                        if (k == 0) {
                            // Red channel
                            intensity *= 1.3;
                        } else if (k == 1) {
                            // Green channel
                            intensity *= 1.4;
                        }
                        // Blue channel remains unchanged

                        // Ensure intensity stays within the valid range [0, 255]
                        if (intensity < 0.0) {
                            intensity = 0.0;
                        } else if (intensity > 255.0) {
                            intensity = 255.0;
                        }

                        // Update pixel value in the image
                        image(i, j, k) = intensity;
                    }
                }
            }

            // Save the filtered image
            cout << "Please enter the name of the output image file, and specify extension (.jpg, .bmp, .png, .tga): ";
            cin >> filename;
            image.saveImage(filename);
            cout << "New image saved." << endl;


        }
        else if (choice == "11"){
            string filename;
            cout << "Please enter image name: ";
            cin >> filename;
            Image image(filename);
            int newwidth, newheight;
            cout << "please enter new width: ";
            cin >> newwidth;
            cout << "please enter new height: ";
            cin >> newheight;
            Image resizedImage(newwidth, newheight);

            for (int y = 0; y < newheight; ++y) {
                for (int x = 0; x < newwidth; ++x) {
                    for (int k = 0; k<3; k++){
                        int ox = x * image.width / newwidth;
                        int oy = y * image.height / newheight;
                        unsigned char& pixelColor = image.getPixel(ox, oy, k);
                        resizedImage.setPixel(x, y,k, pixelColor);
                    }
                }
            }

            cout << "Please enter the name of the output image file, and specify extension (.jpg, .bmp, .png, .tga): ";
            cin >> filename;
            resizedImage.saveImage(filename);
            cout << "New image saved." << endl;


        }
        else if (choice == "14"){
            const int radius = 2;
            string filename;
            cout << "Please enter the image name: ";
            cin >> filename;
            Image image(filename);
            Image result = image;

            int width = image.width;
            int height = image.height;

            for (int y = radius; y < height - radius; ++y) {
                for (int x = radius; x < width - radius; ++x) {
                    vector<int> icount(256, 0);
                    vector<int> sumR(256, 0);
                    vector<int> sumG(256, 0);
                    vector<int> sumB(256, 0);

                    for (int a = -radius; a <= radius; ++a) {
                        for (int b = -radius; b <= radius; ++b) {
                            int px = x + b;
                            int py = y + a;
                            if (px >= 0 && px < width && py >= 0 && py < height) {
                                unsigned char r, g, b;
                                r = image.getPixel(px, py, 0);
                                g = image.getPixel(px, py, 1);
                                b = image.getPixel(px, py, 2);
                                int intensity = (r + g + b) / 3 * 25;
                                intensity = min(max(intensity, 0), 255); // Clamp intensity between 0 and 255
                                icount[intensity]++;
                                sumR[intensity] += r;
                                sumG[intensity] += g;
                                sumB[intensity] += b;
                            }
                        }
                    }

                    int maxCount = 0;
                    int maxIndex = 0;
                    for (int i = 0; i < 256; ++i) {
                        if (icount[i] > maxCount) {
                            maxCount = icount[i];
                            maxIndex = i;
                        }
                    }

                    unsigned char modeR = sumR[maxIndex] / maxCount;
                    unsigned char modeG = sumG[maxIndex] / maxCount;
                    unsigned char modeB = sumB[maxIndex] / maxCount;

                    result.setPixel(x, y, 0, modeR);
                    result.setPixel(x, y, 1, modeG);
                    result.setPixel(x, y, 2, modeB);
                }
            }

            cout << "Please enter the image name to store the new image and specify extension (.jpg, .bmp, .png, .tga): ";
            cin >> filename;
            result.saveImage(filename);
            cout << "New image saved." << endl;


        }
        else if (choice == "10"){
            string filename;
            cout << "Please enter the image name: ";
            cin >> filename;

            // Load image
            Image image(filename);

            // Convert image to grayscale
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    unsigned int avg = 0;
                    for (int k = 0; k < 3; ++k) {
                        avg += image(i, j, k);
                    }
                    avg = avg / 3;
                    for (int k = 0; k < 3; ++k)
                        image(i, j, k) = avg;
                }
            }
            for (int i=0 ; i < image.width;++i ) {
                for (int j = 0; j < image.height; ++j) {
                    unsigned int avg = 0;
                    for (int k = 0; k < 3; ++k) {
                        avg += image(i, j, k);
                    }
                    avg = avg /3;
                    for (int k=0 ; k < 3 ; ++k)
                        image(i,j,k)=avg;
                }
            }

            for (int i=0 ; i < image.width;++i ){
                for (int j = 0; j < image.height; ++j){
                    for (int k=0 ; k<3 ; ++k){
                        if (image(i,j,k)<=150) //let the threshold = 150
                            image(i,j,k)=0;
                        else
                            image(i,j,k)=255;
                    }
                }
            }

            // Perform edge detection
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    for (int k = 0; k < 3; ++k) {
                        if (abs(image(i+1, j, k)- image(i , j, k)) >= 250 || abs(image(i, j+1, k) - image(i, j, k)) >= 250)
                            image(i, j, k) = 0;
                        else
                            image(i, j, k) = 255;
                    }
                }
            }

            // Save the new image
            cout << "Please enter the image name to store the new image and specify extension (.jpg, .bmp, .png, .tga): ";
            cin >> filename;
            image.saveImage(filename);
            cout << "New image saved." << endl;


        }
        else if (choice == "4"){
            string filename;
            string filename1;
            cout << "Please enter the first image name: ";
            cin >> filename1;
            Image image1(filename1);

            string filename2;
            cout << "Please enter the second image name: ";
            cin >> filename2;
            Image image2(filename2);

            //menu to choose
            cout << "Choose merging option:\n";
            cout << "1. Merge by resizing\n";
            cout << "2. Merge by common area\n";

            int option;
            // Keep asking until a valid option is chosen
            while (true) {
                cout << "Enter your choice (1 or 2): ";
                cin >> option;

                if (option == 1) {
                    // Merge by resizing
                    Image mergedImage = mergeByResizing(image1, image2);
                    cout << "Please enter the image name to store the new image and specify extension (.jpg, .bmp, .png, .tga): ";
                    cin >> filename;
                    mergedImage.saveImage(filename);
                    cout << "New image saved." << endl;
                    break;
                } else if (option == 2) {
                    // Merge by common area
                    Image mergedImage = mergeByCommonArea(image1, image2);
                    cout << "Please enter the image name to store the new image and specify extension (.jpg, .bmp, .png, .tga): ";
                    cin >> filename;
                    mergedImage.saveImage(filename);
                    cout << "New image saved." << endl;
                    break;
                } else {
                    cout << "Invalid option. Please enter 1 or 2.\n";
                }
            }


        }
        else if (choice == "6"){
            string filename;
            cout << "Please enter the image name: ";
            cin >> filename;

            // Load image
            Image image(filename);

            // Determine dimensions of the rotated image
            int rotatedWidth = image.height;
            int rotatedHeight = image.width;

            // Create a new image for rotated image
            Image rotatedImage(rotatedWidth, rotatedHeight);

            int degree;
            bool validInput = false;
            while (!validInput) {
                // Get degree of rotation from the user
                cout << "Enter degree of rotation (90, 180, or 270): ";
                cin >> degree;

                if (degree == 90 || degree == 180 || degree == 270) {
                    validInput = true;
                } else {
                    cout << "Invalid degree of rotation. Please enter 90, 180, or 270." <<  endl;
                }
            }

            // Rotate the image
            for (int y = 0; y < rotatedHeight; ++y) {
                for (int x = 0; x < rotatedWidth; ++x) {
                    // Apply rotation transformation based on user input
                    int originalX, originalY;
                    switch (degree) {
                        case 90:
                            originalX = y;
                            originalY = rotatedWidth - 1 - x;
                            break;
                        case 180:
                            originalX = rotatedWidth - 1 - x;
                            originalY = rotatedHeight - 1 - y;
                            break;
                        case 270:
                            originalX = rotatedHeight - 1 - y;
                            originalY = x;
                            break;
                    }

                    // Copy pixel value from original image to rotated image
                    for (int c = 0; c < 3; ++c) {
                        rotatedImage(x, y, c) = image(originalX, originalY, c);
                    }
                }
            }

           // Save the new image
            cout << "Please enter the image name to store the new image and specify extension (.jpg, .bmp, .png, .tga): ";
            cin >> filename;
            rotatedImage.saveImage(filename);
            cout << "New image saved." << endl;


        }
        else if (choice == "9"){
            string filename;
            cout << "Please enter the image name: ";
            cin >> filename;
            // Load image
            Image image(filename);

            int frameType;
            while (true) {
                cout << "simple frame or a fancy frame? (Enter 1 for simple, 2 for fancy): "<<endl;
                cin >> frameType;
                if (cin.fail() || (frameType != 1 && frameType != 2)) {
                    cout << "Invalid input. Please enter either 1 for simple frame or 2 for fancy frame." << endl;
                } else {
                    break;
                }
            }

            int frameColor;
            while (true) {
                cout << "frame color (Enter 1 for black, 2 for white, 3 for blue): "<<endl;
                cin >> frameColor;
                if (cin.fail() || (frameColor != 1 && frameColor != 2 && frameColor != 3)) {
                    cout << "Invalid input. Please enter either 1 for black, 2 for white, or 3 for blue." << endl;
                    cin.clear();

                } else {
                    break;
                }
            }

            int borderWidth = 150;

            if (frameType == 1) {
                addSimpleFrame(image, frameColor, borderWidth);
            } else if (frameType == 2) {
                addFancyFrame(image, frameColor, borderWidth);
            }





            // Save the new image
            cout << "Please enter the image name to store the new image and specify extension (.jpg, .bmp, .png, .tga): ";
            cin >> filename;
            image.saveImage(filename);
            cout << "New image saved." << endl;


        }
        else if (choice == "12"){
            string filename;
            cout << "Please enter the image name: ";
            cin >> filename;
            // Load image
            Image image(filename);

            // calling function
            applyGaussianBlur(image);

            cout << "Please enter the image name to store the new image and specify extension (.jpg, .bmp, .png, .tga): ";
            cin >> filename;
            image.saveImage(filename);
            cout << "New image saved." << endl;


        }
        else if (choice == "15"){
            string filename;
            cout << "Please enter the image name: ";
            cin >> filename;
            // Load image
            Image image(filename);

            // calling function
            applyOldTVEffect(image);

            // Save the new image
            cout << "Please enter the image name to store the new image and specify extension (.jpg, .bmp, .png, .tga): ";
            cin >> filename;
            image.saveImage(filename);
            cout << "New image saved." << endl;

        }
        else if (choice == "exit"){
            cout<<"Thanks for using our program, bye!\n ";
            break;

        }

    }
    return 0;
}
