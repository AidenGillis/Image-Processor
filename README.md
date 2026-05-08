# Image-Processor
Code takes an image from your folder and can either grayscale, invert, or blur the image. Multithreading was implemented to see how threading speeds up the blurring process.

I first began the project by creating simpler code to grayscale or invert an image to understand how to use loops to change the RGB values of each pixel on an inputted image. Following this, it took considerably more effort to implement blurring due to my intermediacy with C++ and trying to visualize how each for loop had to run in order to blur(get an average of the surrounding RGB values) a pixel. 

However, the main focus of this project wasn't to understand loops, but to develop a low-level understanding of how multithreading works inside GPUs specifically. Once I had made the blur function and added a timer system I was able to create new function which, upon receiving an amount of threads to make, would split up the inputted image into that many parts and process the blur significantly faster. The result of this data can be found on the accompanying LinkedIn post on my profile. 

https://www.linkedin.com/in/aiden-gillis-28b660372/?skipRedirect=true
