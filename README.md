# Normalization
Normalization assignment for Professor Kovalerchuk
## Installation
* Go to https://github.com/huberlw/Normalization.git
* Download ZIP then unzip
## Compiler Versions Used
* C++ Implementaion - VS 2022 Version 17.0.4
* Java Implementation - IntelliJ IDEA 2021.3.2 Version 17.0.2
## How to Run
A csv file is needed to run the normalization.  
When running the program will ask for the file path to the csv file. Enter this path.  
Then, the program will ask if the csv file's first column is for ID. Enter 'y' for yes and 'n' for no. 
Last, the program will ask if the csv file's first row is for labels. Enter 'y' for yes and 'n' for no.  
At this point the program will output a "normalized.csv" file in the project directory or give an error is the file could not be found.  
### Execution Example
1. Example Data without ID or labels and with ID and labels.
    * ![image](https://user-images.githubusercontent.com/100527741/155895630-26fed2b6-45c3-42ae-bf22-99dac23936a2.png)
    * ![image](https://user-images.githubusercontent.com/100527741/155895682-5449c304-1b8a-4032-832d-e4a817b42f37.png)
2. Running C++ implementaion without ID or labels.
    * ![image](https://user-images.githubusercontent.com/100527741/155895772-27553245-60a3-4c6e-bda9-f211d12fcc6d.png)
3. Running Java implementaion with ID and labels.
    * ![image](https://user-images.githubusercontent.com/100527741/155895839-bf93a373-e964-44a8-8085-d67f1b2ab71b.png)
5. Outputted csv files. (C++ output on left, Java output on right)
    * ![image](https://user-images.githubusercontent.com/100527741/155895919-729bc0e8-3f85-4ba6-90a4-7fd8a652e6d8.png)
## Implementation
Run VisCanvas, select normalization method
## Normalization Algorithm
1. Each data point is recalculated by subtracting the mean and dividing by the standard deviation.  
![iamge]("https://user-images.githubusercontent.com/100527741/155894497-c83e5aaf-d27e-4f24-91cb-b1f934765bc4.png")  
2. Each data point is normalized linearly from [0, 1] by subtracting the samllest data point and dividing by the largest data point minus the smallest data point.  
![image]("https://user-images.githubusercontent.com/100527741/155894526-f883c039-48a4-4d12-be28-9028186f0b45.png")
