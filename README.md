<a href="https://github.com/FriedImage/DPCPP-Image-Blurring-with-SYCL/blob/master/icon.png">
    <img src="https://github.com/FriedImage/DPCPP-Image-Blurring-with-SYCL/blob/master/icon.png" alt="BlurFilter App Icon" title="DPC++ BlurFilter App" align="right" height="64" />
</a>

# DPC++ BlurFilter App  

## Table of Contents  

- [About the project](#about-the-project)
- [What does it do?](#what-does-it-do)
- [Purpose/Goals of implementation](#purposegoals-of-implementation)
- [Installation Steps](#installation-steps)
    - [DPC++ and SYCL Integration](#dpc-and-sycl-integration)
    - [Library Installation](#library-installation)
    - [(OPTIONAL) Create .msi setup file with dependencies](https://github.com/FriedImage/DPCPP-Image-Blurring-with-SYCL?tab=readme-ov-file#optional-create-msi-setup-file-with-dependencies)
    - [(OPTIONAL) Program execution using Intel OneAPI Command Prompt for Visual Studio 2022](#optional-program-execution-using-intel-oneapi-command-prompt-for-visual-studio-2022)
- [Limitations](#limitations)
- [Final Thoughts](#final-thoughts)

## About the project  

- This project was created as a DPC++ SYCL Implementation for my Thesis project **(GPU Programming with DPC++)**. 
- The execution interface is provided as a **CLI Application**.
- This project is made with the Standard ISO C++ 17 with DPC++ support, using the SYCL 2020 Library.

## "What does it do?"  

- In general, the processing of the image data will be that of a "**Box Filter**" approach, which computes the "average" value of the surrounding pixels based on a **blur radius**, then replaces each pixel's value with the computed average. 
- This process is repeated for all the pixels of the image.
- The resulting image ends in a **whole image blur** of the **input image**.

## Purpose/Goals of implementation  

- The need for **Data Parallelism** exists in every scenario where processing scaling amounts of any type of data is needed, ***especially*** in the field of Image Processing applications.
- Applying Image Blurring with DPC++ and SYCL, we are able to get a plethora of positive characteristics which state the usefulness of a program such as: 
    1. **Strong Scaling**. Increasing the amount of data-to-process we are also increasing the execution resources that are needed. Parallelizing this process reduces the execution time and resource processing significantly.
    2. **Parallel Data Management**. With Parallel Data Management, we achieve low latency-high throughput of the host and accelerator devices **overall**, while a classic serialized approach (eg. using pure C++), there are times of unwanted idleness.
    3. **SYCL's Ease of Use**. Finally, knowing that parallelizing a program becomes difficult in many cases, SYCL helps combat this problem by providing high-level programming structures that are equivalent to low-level ones.

## Installation Steps  

### DPC++ and SYCL Integration  

- Using the link below ("<a href="https://www.intel.com/content/www/us/en/developer/tools/oneapi/base-toolkit-download.html?operatingsystem=window&distributions=offline" target="_blank">Intel oneAPI Install</a>") and selecting the text ***"Continue without signing up"***, following the on-screen installation instructions, **being cautious** of the below specific features. 
    1. **Version**. Intel® oneAPI Base Toolkit for Windows* (64-bit) – 2024.0.1.45
    2. **Installation type**. **Recommended** should be fitting for most setups.
    3. **Visual Studio IDE Integration**. Select the checkbox with the option "Visual Studio 2022".
    4. **Visual Studio Project Template**. The DPC++ Console Application project template is used for this implementation.

### Library Installation  

- The libraries used are -> OpenCV, SYCL 2020 and other Standard C++ 17 included libraries.
- **REQUIRED: OpenCV 4.9.0**. Using the link belowUsing the link below ("<a href="https://opencv.org/releases/" target="_blank">OpenCV Install</a>") and selecting version 4.9.0, following the instructions below. 
    1. **Installation**. Running the executable file, the user is prompted to select a desired path which the files will be provided.
    2. **OpenCV project integration (for Visual studio 2022)**. Steps for Project -> Properties are shown below.
        1. DPC++ -> General -> Change Include Directory -> **Path_To_Include** (Where Path_To_Include the “include” path of the extracted “opencv” folder)
        2. Linker -> General -> Additional Library Directories -> **Path_To_Lib** (Where Path_To_Lib the path of the "build -> x64 -> vc16 -> lib" folder of the extracted "opencv" folder)
        3. Linker -> Input -> Additional Library Directories -> **opencv_world490.lib** (for debug configuration use opencv_world490d.lib)
- **REQUIRED: SYCL 2020**. SYCL is installed automatically with Intel's OneAPI DPC++ toolkit thus, no additional actions are required.
- **ALREADY INCLUDED WITH C++: iostream, thread, chrono, filesystem**.

### (OPTIONAL) Create .msi setup file with dependencies  

- In case you want to run the app with all the dependencies included, load the DPC++ BlurFilter App.vdproj and follow the steps below
    1. Right click on the already modified Setup project, then build.
    2. The setup.msi file is located at "DPC++ BlurFilter App\Release".

### (OPTIONAL) Program execution using Intel OneAPI Command Prompt for Visual Studio 2022  

- To run the application without Setup, through the Intel OneAPI terminal, the following steps are mentioned.
    1. Open Intel OneAPI Command Prompt for Visual Studio 2022.
    2. Paste following command to run .exe file. ***May vary, depending on the path of the installed Project***. (“`C:\Program Files (x86)\Intel\oneAPI>C:\Users\ntoli\source\repos\DPCPP\BlurFilter\x64\Release\BlurFilter.exe`”)

## Limitations  
- **Lack of administrator privileges in special directories**. In case the program setup is installed in a path that requires special rights to edit files, the program shows the result of blurring, but in an unsaved state. To address the above problem, it is required that administrator rights must be given when the program is run by the user. **Alternatively**, it can be installed in a different path.

## Final Thoughts  

- With the development of this and more implementations to come, I want to expand my knowledge on parallel computing. My personal objective is the continuous study of the subject of parallel computation, thereby becoming more knowledgable of the HPC science and of aspects that constitute it.
- While this implementation is part of my studying progress and possibly ***VERY UNSTABLE***, I believe it's a good start on getting to know SYCL's mission to provide an open-source portable standard in High-Performance Computing.

<a href="#dpc-blurfilter-app">
    <p align="center"><b>Back to top</b></p>
</a>