# NCTU EE Computer Organization Final Project Spring 2017
    The project will take you to get started with RISCV and a basic concept about images processing. In this project, it’s divided into 3 parts, and each part is a bit related to the other two. The main tasks are using spike which is connected with the cache, modifying the program to get better performance, changing replacement policy in cache to implement another policy respectively.  
 
    Hope you will learn a lot and have fun!

---------------------------------------
# Introduction 
    In general, the major job of DIP(Digital image process) is using algorithms and analyzing images with computers. Mainly, spatial domain filtering is commonly used to modify or enhance an image. In other words, you can emphasize or remove certain feature by doing so.  
    
    In this program, it’s written to do images processing by above-mentioned method, and it has two filters which will blur the images and find edge of the images separately via 2D-convolution method.    
    For more information, please check the link to learn more about these techniques:
	
  [2D-convolution](http://homepages.inf.ed.ac.uk/rbf/HIPR2/convolve.htm),    [bluring](http://homepages.inf.ed.ac.uk/rbf/HIPR2/gsmooth.htm),   [edge detection(Laplacian of Gaussian)](http://homepages.inf.ed.ac.uk/rbf/HIPR2/log.htm)
	
---------------------------------------
# Set up for envirnment
    Before we begin to undertake the project, we should download what we need, that is RISCV tool. In the Part I, it will introduce RISCV tool briefly. You have to download the source code of RISCV-tools from our github’s repository, and follow these commands that can update the repository and install it.
	
First thing before we install the tools, it’s necessary to set the $RISCV environment variable:
	
	$ export RISCV=$TOP/I-love-CO
	$ export PATH=$PATH:$RISCV/bin
Alternatively, you can open your own .bashrc and add the path manually:
	
	export RISCV=$TOP/I-love-CO
	PATH=${PATH}:$TOP/I-love-CO/bin 
Download the RISCV tool repository:

	$ git clone https://github.com/proyar/riscv-tool
Once you have downloaded, you need to update it and build the tools(It will take some time.):

        $ cd riscv-tool
	$ git submodule update --init --recursive
	$ ./build.sh
After finish it, You should notice that you will get some new commands in your Linux command.
![default](https://cloud.githubusercontent.com/assets/20680945/25227703/27dbb6fe-25fc-11e7-849a-a64592e68359.PNG)
We will use scripts to compile the c code into riscv binary code:

	$ make riscv
To run the riscv binary code in spike:

	$ make riscv-run
You may want to test the program first on your host machine. Similarly, you can use these commands to do it.
	
	$ make host
    $ make host-run
To clear the compiled code:

	$ make clean
Do not use this comand:
      
    $ make
Note: You will use at least riscv-fesvr, riscv-gnu-toolchain, riscv-isa-sim(spike) and riscv-pk(pk) in the riscv-tools.

---------------------------------------
# Part I (due date:) Observe the cache behavior in spike
## Introduction
    RISCV is a new instruction set architecture (ISA) that was originally designed to support computer architecture research and education, its instruction resembles in risc’s partially.

    Spike, the RISCV ISA simulator, can simulate functional behavior of RISCV ISA. It also provides users with hardware simulation. Ex. cache simulation, multi-core simulation.

## Specifications:
    Since we mentioned that spike can simulate cache, we can do something to cache and look over what happens. You should remember how the cache operations. If not, please review the textbook as soon as possible.

    We provided the program that you will deal with it in the entire project. In the program, it makes use of two different filters (blur and LoG) on one input image through convolution respectively and generates 2 outputs which are stored under "Output" directory. You can read description on the top to understand how to use this reference code.

* Please compile this program and run the binary code in spike.

* Originally, spike doesn’t simulate cache, it provides users with commands(--ic=\<Sets>:\<Ways>:\<Block sizes>,--dc=\<Sets>:\<Ways>:\<Block sizes>) that can connect spike with cache,please simulate just only simulate D$.You are welcome to rewrite Makefile to use cache in spike.For more information for spike,type this command.

      $ spike

* Please use different sets, ways and block sizes and record the cache miss rate. The rule is that you will have to fix two parameters that you can set the number arbitrarily, and unfix the other one, adjust the unfixed one at least five times.

* Make three line charts for sets, ways and block sizes to record the cache miss rate, you should tell us what are fixed parameters and what is unfixed parameter clearly in each chart. 

* Write down the reason why the miss rate increases or decreases when the parameter changes in the report.(Hint: increasing block sizes/ways/sets fully utilize what? And so on…..)

* Grade: 20% for report.

# Part II (due date:)Find a Program-optimizing approach
## Introduction:
    To continue our final project, we should keep an eye on this program, it’s not hard to find that the program has a poor cache performance. That is, there is still room for improvement.

## Specifications:
    Your job is try to understand what things will be done in the whole programs, and try to get familiar with image blurring and edge detection. Furthermore, revise the program to get better cache performance.
 
* Improve the reference code performance and explain the reason how you do this in the report.(Hint : We suggest that you may improve "cnv.h",but you also can modify other code files.)

* To confirm that whether the performance can get better or not, please create a 4KB(64X2X64)instruction-cache and 4KB(64X2x64) data-cache (AXBXC means Sets X Ways X line size) and run your modified program in spike connects with these caches.

* Assume hit time is 1 unit time, and as for miss penalty, it takes 200- unit time to access the DRAM to retrieve the correct data. Please calculate total cache access time for I1$ and D1$, and write down your answer in your report.

      AMAT(average memory access time) = Hit_time + Miss_rate * Miss_penalty
      total_cache_access_time = access_count * AMAT
* Compare the total cache access time between the original program and modified program to make sure that it gets better performance. Warning, if your result is equal or worse than the original program, you will get zero point on this part.

* The program “inspector.c” can tell you that whether your modified program’s output is correct or not. It indicates you are forbidden from receiving the wrong result or else you will get zero point.

* Turn over only your modified program(s),and don’t modify the “inspector.c”, it’s not a good way to escape from reality.
* Grade: 20% for code. 10% for performance rank. 10% for report.

## Bonus(3%~5%)Find the best cache construction to your program
* Find out the L1$(both of D$ and I$) configuration to make your cache accessing time fastest.

* If your AMAT is less within 10% than your original result, you can get 3 points. If it’s among 10% to 20%, you can get 4 points. If it’s beyond 30%, you can get 5 points.

    Example: I get AMAT that is 2000-unit time in the part II, after I adjust the cache configuration and I get new AMAT is 800-unit time. Then I have improved 60%[(2000-800)/2000 * 100%] so I will get 5 points.

* The caches size are restricted to 4KB separately.

* Write down the cache construction and your improvement percent in your report. 
---------------------------------------
# Part III (Due date:)Find a cache-optimizing approach
## Introduction:
    In the part II, we enhance the cache performance by modifying the program directly. Now that spike can simulate the cache, we can improve the cache performance through modifying the inside the cache construction. The files related to cache simulation are “cachesim.h” and “cachesim.cc”. They lie in the repository “/path/to/riscv-tools/riscv-isa-sim/riscv”.
## Specifications:
* There are two main functions in “cachesim.cc”, access and victimize. When tracer calls trace, the cache will call access. The access will check tag and then do the write or read. the original design is that it uses LFSR to find the victim when a replacement happens.

* You are asked to focus on cache replacement policy, please redesign the other replacement policy and write down what is your design in the report.
* Only “cachesim.cc” and “cachesim.h” can be modified. Do not touch other files.

* Ignore “class fa_cache_sim_t” in both “cachesim.h” and “cachesim.cc”.

* Do not modify the part to calculate cache access count and the miss count.

* When you have modified the spike,you need to rebuild the spike.Following these steps can make this be done.

      $ cd /path/to/riscv-tools/riscv-isa-sim/build
      $ ../configure --prefix=$RISCV --with-fesvr=$RISCV
      $ make
      $ make install

* Please create a 4KB(64X2X64)instruction-cache and 4KB(64X2x64) data-cache and run the program in spike connects with these modified caches.

* Run the reference program in spike ,not the modified program which is written by you in the part II. In this time, it’s not required that you need to get better performance. In the other words, you will not get zero point due to worse performance, only get lower rank.

* Assume hit time is 1 unit time, and as for miss penalty, it takes 200- unit time to access the DRAM to retrieve the correct data. Please calculate total total cache access time for I1$ and D1$, and write down your answer in your report.

* Grade: 10% for code. 20% for performance rank. 10% for report.
---------------------------------------
# Rules
* Before start at the project, please divide into 9 groups. Each group has two people at most excluding one group can have 3 people. Select a leader who should be in charge of this team. Link on here to fill the group list before ****/**/** 23:59.

* Upload all the required files to E3 in right format before the deadline. TA will write a testing script to grade your project automatically. For the late submission in three days, you will get 70% of your grade. For who hasn't uploaded more than 3 days after the due date, you will just get zero point.

* Name your report as "Report_part#_LeaderStudentID.pdf". For example, if it's part II and the leader's ID is 9487953, then set your report as "Report_partII_9487953.pdf". Put the needed source codes under a directory called "code_LeaderStudentID". Pack your report and source code into a file named "Part#_LeaderStudentID.zip" in zip format. Then upload it to E3.

* Each group just only turns over one package, each part has one zip file .
---------------------------------------
# Grading Policy
* The grade distribution has been written in the description of each part.

* Extra 5% for report and write about what you’ve learned from this project, is it difficult? Does anything in the project should improve?......and so on. Name this report as “Report_feedback_LeaderStudentID.pdf”, and upload this report to E3 alone(Don’t put it into "Part#_LeaderStudentID.zip").

* As for performance rank in the part I, we will sort your total cache access time from high to low. The best one can get 10 points and the worst one will get 2 points.The grade decreases by 1 point gradually when the rank is lower and lower.

* As for performance rank in the part II, we will sort your total cache access time from high to low. The best one can get 20 points and the worst one will get 4 points.The grade decreases by 2 points gradually when the rank is lower and lower.
---------------------------------------
# Notes
If you get any problem when you read this document or work on the project, feel free to ask google or send an email to TA about your issue. Hope you will have a great time on this project.TA is regarded as a cheap labor. Thanks!

TA:Bo-Ya Chen

Email: mrproyar@gmail.com
