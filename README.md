# Chracter-Recognition
First update

in this project i used opencv library to process img in order to procces images to recognizes chracters clearly.

firstly we have a main.cpp file includes all functions which is all procces happening here.

Other files are classifications.txt ,imagesArranged.txt. These txt files includes arrays from 20x30 white and black images writed for each pixsel  
clasifications.txt includes ASCII numbers for imagesArranged.txt file it sycronized for each array contains one chracter image.
in this files I check pixsels of chracters on by one and making decisions.



in test file contain images to recognization;

![alt text](test/IMG_1957.jpeg)  ==>> this img size is 134 × 136 px we have to resize img to 20x30 and convert to wihite and black img.In main.cpp file I wrote a function which nemed "img_transport()"



![alt text](test/img_2.jpeg) after this conversation KNN algorithm can recognize this img and specify it.

But we have a troble. when converting images W&B I shold specify threshold value but this value is a variable and the optimum number can changer for every single img. then ı developed an algorithm .it can adaptive threshold for every images then I can get the perfect white and black balance 

