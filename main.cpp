#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <filesystem>
#include <opencv2/objdetect.hpp>
using namespace std;
#include <unistd.h>
using namespace std;
using namespace cv;
void printing_img(vector<int>&,int); //this function prints chracters on console
int classification(vector<int>,vector<int>,vector<int>);
void Loads(vector<int>&,vector<int>&);
void img_transport();//in this function I created test samples folders for each num
void img_load(Mat &,vector<int>&);//loads Train Samples from txt to vector
//void Defnenin_fonksiyonu(vector<int>&);
int adaptive_threshold(Mat &);//in this function I created smart threshold calculator it adaptive at variable bright images
int main(){
    int max_indx,fold,img_num,counter=0,counter_f=0,tmp;
    char src_add[70];
    float percentage=0;
    Mat src;
    vector<int>Train_pix,Train_chr,object;
    Loads(Train_pix,Train_chr);
    //printing_img(object,0);
    //cout<<"\n";
    //printing_img(Train_pix,max_indx);
    //cout<<"\nthe chracter is: "<<(char)Train_chr[max_indx];
    //img_process();
   // img_transport();
    object.clear();
    for(fold=0;fold<=9;fold++){
        sprintf(src_add,"/Users/blackstone/Desktop/Character_recog/test/test_wb/%d",fold);
        for (const auto & entry : std::__fs::filesystem::directory_iterator(src_add)){  // ı used to read listed img from a file
            //sprintf(src_add,"/Users/blackstone/Desktop/Character_recog/test/resized/%d/img_%d.jpeg",fold,img_num);
           //sprintf(src_add,"/Users/blackstone/Desktop/Character_recog/test/test_wb/%d/img_%d.jpg",fold,img_num);
            src=imread(entry.path(),COLOR_BGR2GRAY);
            img_load(src,object);
            if(!object.empty()){
                max_indx=classification(Train_pix,Train_chr,object);
              // printing_img(Train_pix,max_indx);
              // cout<<"the letter is :"<<(char)Train_chr.at(max_indx)<<endl;
               // sleep(2);
            }
            if((Train_chr[max_indx]==(fold+48))&&(!object.empty())){
                counter++;      //true img counter
            }else if (!object.empty()){
                counter_f++;    //false img counter
            }
            object.clear();
        }
        percentage=(float)counter/(float)(counter_f+counter)*100;
        cout<<"the accuracy is : "<<percentage<<"%"<<endl;
        percentage=0;
    }

}
void img_load(Mat &src,vector<int>&object){
    int tmp;
    int i=0,j=0;
    if(src.data){
        //cout<<"opened ";
        for(i=0;i<src.rows;i++){
            for(j=0;j<src.cols;j++){
                object.push_back(src.at<uchar>(i,j));
            }
        }
        //printing_img(object,0);
    }
    src.release();
}
int adaptive_threshold(Mat &resized){  //i wrote this function instead of create variable white_and Black
    int counter_w=0,counter_b=0,threshold=128,threshold_old=128;
    int max_i=255,min_i=0;
    float percentage=0;
    int i=0,j=0;
    uchar tmp;
    while(percentage<45||percentage>50){
        Mat img_wb=resized<threshold;
        for(i=0;i<resized.rows;i++){
            for(j=0;j<resized.cols;j++){
                tmp=img_wb.at<uchar>(i,j);
                if(tmp>128){
                    counter_w++;
                }else{
                    counter_b++;
                }
            }
        }
        percentage=((float)counter_w/(float)(counter_b+counter_w))*100;
        if(percentage<45){
            min_i=threshold_old;
            threshold=(max_i+min_i)/2;
            if(abs(threshold_old-threshold)<=2){
                break;
            }
            threshold_old=threshold;
        }else if(percentage>50){
            max_i=threshold_old;
            threshold=(max_i+min_i)/2;
            threshold_old=threshold;
        }
        counter_w=0;
        counter_b=0;
    }
    return threshold;
}
void img_transport(){     // this function process img and saves to specific directories [includes adaptive_threshold algorithm which is I developed]
    int threshold=1,src_fold=0,a=1;
    char src[70],dist[70];
    Mat resized;
    Size size(20,30);
    for(src_fold=0;src_fold<=9;src_fold++){
            sprintf(src,"/Users/blackstone/Desktop/Character_recog/test/test_rgb/%d",src_fold);
            for (const auto & entry : std::__fs::filesystem::directory_iterator(src)){
                std::cout << entry.path() << std::endl;
                sprintf(dist,"/Users/blackstone/Desktop/Character_recog/test/test_wb/%d/img_%d.jpg",src_fold,a);
                cout<<dist<<endl;
                Mat test_img=imread(entry.path(),COLOR_BGR2GRAY);
                if(test_img.data){
                    resize(test_img,resized,size,COLOR_BGR2GRAY);
                    cvtColor(resized,resized,COLOR_BGR2GRAY);
                    threshold=adaptive_threshold(resized);
                    Mat img_bw = resized<threshold;
                    if(src_fold==0||src_fold==1){
                        erode(img_bw,img_bw,Mat(),Point(-1,-1),1);

                    }

                    //Canny(test_img,resized,60,3);
                    //dilate(resized,resized,Mat(),Point(-1,-1), 1);
                   // addWeighted(resized,3.5,resized,-0.3,0,resized);
                    //imshow("resized",resized);
                    //imshow("src",test_img);
                    imwrite(dist,img_bw);
                    a++;
                }
            }
            a=1;
    }
}
int classification(vector<int>(Train_pix),vector<int>(Train_chr),vector<int>(object)){
    int i,j,counter,max,max_indx;
    vector<int>(indx);
    counter=0;
    for(i=0;i<Train_chr.size();i++){
        for(j=600*i;j<600*i+600;j++){
            if(abs(object[j-i*600]-Train_pix[j])<=21){
                counter++;
            }
        }
        indx.push_back(counter);
        counter=0;
    }
    max=indx[0];
    max_indx=0;
    for(i=1;i<indx.size();i++){
        if(max<indx[i]){
           max=indx[i];
           max_indx=i;
        }
    }

    return max_indx;
}
void Loads(vector<int>&Train_pix,vector<int>&Train_chr){

    int tmp=0;
    fstream train_chr,train_pix; //this files meant to be source of images and characters
    train_chr.open("/Users/blackstone/Desktop/Character_recog/classifications.txt");
    train_pix.open("/Users/blackstone/Desktop/Character_recog/imagesArranged.txt");
    if(!train_pix.is_open()){
        cout << "i cannot opened images file\n";
    }
    if(!train_chr.is_open()){
        cout<<"i cannot opened character files\n";
    }
    while(train_pix>>tmp){
        Train_pix.push_back(tmp);
    }
    train_pix.close();

    while(train_chr>>tmp){
        Train_chr.push_back(tmp);
    }
    train_chr.close();
}
void printing_img(vector<int>&img,int indx){

    int j=0.,row,colum;
    row=0,colum=0;
    for(j=indx*600;j<indx*600+600;j++){
        if(colum==20){
            colum=0;
            row++;
            cout<<endl;
        }
        if(row==30){
            row=0;
            cout<<endl;
        }
        if (img[j]>99){

        } else if(img[j]>=10){
            cout<<" ";
        }else if(img[j]<10){
            cout<<"  ";
        }
        cout<<img[j];
        colum++;
    }
}
/*void Defnenin_fonksiyonu(vector<int>&Train_pix){
    int i=0;
   int array[16]={4,75,10,18,20,10,74,10,75,75,10,9,487,19,487,75};
   for(i=0;i<9;i++){
       printing_img(Train_pix,array[i]);
      sleep(1);
   }


}
*/
