<a href="https://github.com/FriedImage/DPCPP-Image-Blurring-with-SYCL/blob/master/icon.png">
    <img src="https://github.com/FriedImage/DPCPP-Image-Blurring-with-SYCL/blob/master/icon.png" alt="BlurFilter App Icon" title="DPC++ BlurFilter App" align="right" height="64" />
</a>

# DPC++ BlurFilter App  

## About the project  

- This project was created as a DPC++ SYCL Implementation for my Thesis project **(GPU Programming with DPC++)**. 
- The execution interface is provided as a **CLI Application**.

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

... (to be written)

## Final Thoughts

- While this implementation is part of my studying progress and possibly ***VERY UNSTABLE***, I believe it's a good start on getting to know SYCL's mission to provide an open-source portable standard in High-Performance Computing.