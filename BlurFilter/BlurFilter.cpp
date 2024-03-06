// Library includes
#include <CL/sycl.hpp>
#include <opencv2/opencv.hpp>
#include <filesystem>

// Namespace shortcuts
using namespace cv;
using namespace std;

// Box/Averaging filter kernel for colored image data
/* 
    Parameters consist of the below:
    1. One dimensional 3-byte Vector Accessor (named: image_accessor) of data-type Vec3b that reads and writes the targeted global buffer (with defaults: 1, read_write, global_buffer/target)
    2. Width of the image of data-type int
    3. Height of the image of data-type int
    4. image_accessor's index inside the buffer that starts from the beginning (1) (named: idx)
    5. The radius of the affected neighborhood for averaging
*/
void blur_kernel(sycl::accessor<Vec3b, 1, sycl::access::mode::read_write, sycl::access::target::device> image_accessor, int width, int height, sycl::id<1> idx, int blur_radius) {
    int index = idx[0]; // Extracts the index from the global ID

    // As long as the index hasn't reached at the last pixel of the image this part of the code executes
    if (index < width * height) {
        // row major form
        int x = index % width; // col number x is found by pixel % total width
        int y = index / width; // row number y is found by pixel / total width

        // Apply box blur filter for each color channel (c: RGB)
        for (int c = 0; c < 3; ++c) {
            int sum = 0;
            int count = 0;

            // y-coordinate for-loop
            for (int dy = -blur_radius; dy <= blur_radius; ++dy) {
                // x-coordinate for-loop
                for (int dx = -blur_radius; dx <= blur_radius; ++dx) {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                        sum += image_accessor[nx + ny * width][c]; // Access the c-th color channel
                        count++;
                    }
                }
            }

            // Apply average to each color channel
            image_accessor[index][c] = sum / count;
        }
    }
}

// Program execution
int main() {
    cout << "AUTHOR: George Ntolias" << endl;

    // Load colored image using OpenCV
    /* 
        1. Instantiate and enter filename from user input
        2. Determine if user added a file extension
        3. Create image array of the input file
        4. Determine whether user added a supported image file extension
        5. Determine whether user's complete filename exists or not
        6. Read input_image from user
    */
    string file_name;
    cout << "Please insert the name (with file extension) of the image file you want to blur --> ";
    cin >> file_name;

    // Instantiate extension and check whether there is one from user-input
    string extension;
    size_t extension_dot_pos = file_name.find_last_of('.');
    if (extension_dot_pos != string::npos && extension_dot_pos < file_name.length()) {
        extension = file_name.substr(extension_dot_pos);
    }
    else {
        cerr << "ERROR: File extension not found!" << endl;
        return 1;
    }

    // Instantiate image array of user file
    Mat input_image;

    // Create vector with some supported image extensions
    vector<string> supported_extensions = { ".jpg", ".png", ".bmp", ".jpeg", ".tiff" };
    
    // Convert user extension to lower-case (case-insensitive user-input)
    transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

    // Iterate over each extension to check if file extension of user-input is supported
    if (file_name.length() >= 4 && file_name.length() < 256) {
        bool is_supported = false;
        for (const string& user_ext : supported_extensions) {
            if (user_ext == extension) {
                is_supported = true;
                break;
            }
        }
        if (is_supported) {
            // Check whether the filename (including the supported extension) exists at all, based on user-input
            if (std::filesystem::exists(file_name)) {
                input_image = imread(file_name);
            }
            else {
                cerr << "ERROR: Filename with supported extension not found!" << endl;
                return 2;
            }
        }
        else {
            cerr << "ERROR: Unsupported image file format! (Supported formats: .jpg, .png, .bmp, .jpeg, .tiff)" << endl;
            return 3;
        }
    }
    else {
        cerr << "ERROR: Full filename length invalid! (filename must be between 4-255 chars)" << endl;
        return 4;
    }
    cout << "Input Image (input_image) read successfully!" << endl;

    // Initialize column and row number based on image's height and width
    int width = input_image.cols;
    int height = input_image.rows;
    cout << "Image width: " << width << "px, " << "Image height: " << height << "px" << endl;

    // Get neighborhood blur radius from user
    int blur_radius;
    cout << "Enter blur radius --> ";
    cin >> blur_radius;

    // Accept input as long as its above 0
    if (blur_radius <= 0) {
        cerr << "ERROR: Blur radius must be greater than 0, input image will stay the same." << endl;
        return 5;
    }

    // Convert the input image to the BGR format (required by OpenCV)
    cvtColor(input_image, input_image, COLOR_RGB2BGR);

    // Initialize queue and Device Selector(s) to run kernel on device (GPU kernel works on Linux)
    sycl::queue q;
    if (sycl::device::get_devices(sycl::info::device_type::gpu).empty()) {
        // No GPU device available, fall back to default selector
        q = sycl::queue(sycl::default_selector_v);
    }
    else {
        // Use GPU selector
        q = sycl::queue(sycl::gpu_selector_v);
    }

    // Allocate buffer for input image
    sycl::buffer<Vec3b, 1> image_buffer(reinterpret_cast<Vec3b*>(input_image.data), sycl::range<1>(width * height));

    // Execute blur kernel through queue and selected device, repeat process in-parallel
    q.submit([&](sycl::handler& h) {
        auto image_accessor = image_buffer.get_access<sycl::access::mode::read_write>(h);
        h.parallel_for(sycl::range<1>(width * height), [=](sycl::id<1> idx) {
            blur_kernel(image_accessor, width, height, idx, blur_radius); // Blur radius required from user input
            });
        });

    // Copy data back to host
    q.wait();
    cout << "Blur of radius " << blur_radius << " done!" << endl;

    // Convert the processed image back to the RGB format from BGR to the original
    cvtColor(input_image, input_image, COLOR_BGR2RGB);

    // Save blurred image with user input for image name
    string result;
    cout << "Please name the result blurred image --> ";
    cin >> result;
    if (result.empty() || result.length() > 255) {
        cout << "Invalid name, using default filename 'blurred_image' instead" << endl;
        result = "blurred_image";
    }
    else {
        result += extension;
    }
    imwrite(result, input_image); // Move temporary blurred input_image to a new file (example: [result].jpg)

    // Display the result
    cout << "Press any key in image window to close it" << endl;
    imshow("Blurred Image", input_image);
    waitKey(0);

    return 0;
}
