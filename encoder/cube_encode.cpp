/* 
 * File:   cube_encode.cpp
 * Author: korzec
 *
 * Created on August 19, 2011, 8:43 PM
 */

#include "../cubecodec/types.h"
#include "../cubecodec/Encoder.h"
#include "../cubecodec/PictureIO.h"
#include "../cubecodec/general.h"

std::streampos fileSize( const char* filePath ){

    std::streampos fsize = 0;
    std::ifstream file( filePath, std::ios::binary );

    fsize = file.tellg();
    file.seekg( 0, std::ios::end );
    fsize = file.tellg() - fsize;
    file.close();

    return fsize;
}

int cube_encode(Parameters params, std::string input, std::string output)
{
    Encoder encoder;
    
    //load params and check if they were correct
    if( ! encoder.SetParams(params))
    {
        std::cout << "some parameters were wrong" << std::endl;
        return EXIT_FAILURE;
    }

    std::ifstream
    inputPicture(input.c_str(), std::ios::in | std::ios::binary);
    if (inputPicture.fail())
    {
        std::cerr << std::endl <<
                "Can't open input data file: " << input << std::endl;
        return EXIT_FAILURE;
    }
    else
        std::cout << "opened file " << input << std::endl;

    std::cout << encoder.GetParams().toString();

    //open file for writing
    std::string codedFileName = output + ".wcb";
    std::ofstream* codedFile = NULL;
    if(!params.nofile)
        codedFile = new std::ofstream(codedFileName.c_str(), std::ios::out | std::ios::binary);
    
    /// open the decoded output file
    std::ofstream *outputPicture = NULL;

    if (encoder.GetParams().nolocal == false)
    {
        std::string outputPictureName = output + ".localdec.yuv";
        outputPicture = new std::ofstream(outputPictureName.c_str(), std::ios::out | std::ios::binary);

    }

    //std::cout << "result: " << WritePicture(*outputPicture, picture) << std::endl;
   
    Picture picture;
    int frameNumber = 0;
    bool go = true;
    BufferState state;
    
    //write a file header
    encoder.WriteSequenceHeader(codedFile);
    
    std::vector<double> psnr;
    std::vector<double> newPsnr;
    
    psnr.push_back(0);//y
    psnr.push_back(0);//u
    psnr.push_back(0);//v
    psnr.push_back(0);//yuv

    //how many psnr values we have accumulated
    int psnrTimes = 0;
    
    //skip frames
    std::cout << "skipping frames: ";
    for (int i=0; i<params.start_pos; ++i)
    {
        PictureIO::ReadPicture(inputPicture,
                           encoder.GetParams().codecParams.cubeSize.width, 
                           encoder.GetParams().codecParams.cubeSize.height);
        std::cout << frameNumber << ","; 
        std::cout.flush();
        frameNumber++;
    }
    std::cout << std::endl << "encoding frames: ";
    do
    {
         picture = PictureIO::ReadPicture(inputPicture,
                           encoder.GetParams().codecParams.cubeSize.width, 
                           encoder.GetParams().codecParams.cubeSize.height);
         //handle a new picture read
         if( frameNumber <= (params.end_pos - params.start_pos) &&
                 picture.isValid())
         {
             picture.pictureNumber = frameNumber;
             bool ret = encoder.LoadNextPicture(picture);
             if(ret == false)
             {
                 std::cout << "failed to load picture to the encoder" << std::endl;
                 return EXIT_FAILURE;
             }
             std::cout << frameNumber << ","; 
             std::cout.flush();
             frameNumber++;
         }
         else
         {
             std::cout << "no more pictures to read" << std::endl;
             encoder.EndOfSequence();
             break;
         }
         
         do
         {
             state  = encoder.Encode();
             PictureVectorPtr gop;
             switch (state)
             {
             case OUTPUT_AVAILABLE:
                 ///if encoded data is available
                 ///write out the buffer and continue
                 encoder.WriteCubeData(codedFile);            
                 
                 gop = encoder.GetDecodedGOP();
                 
                 if(params.analysis)
                 {
                     //get PSNR of the GOP
                     PictureVectorPtr originalGOP = encoder.GetOriginalGOP();
                     assert(originalGOP->size() == gop->size());
                     for(size_t i=0; i < originalGOP->size(); i++)
                     {
                         newPsnr = PSNR(originalGOP->at(i), gop->at(i));
                         psnr[Ych] += newPsnr[Ych];
                         psnr[Uch] += newPsnr[Uch];
                         psnr[Vch] += newPsnr[Vch];
                         psnr[3] += newPsnr[3];
                         psnrTimes++;
                     }
                 }
                 
                 
                 if(!params.nolocal)
                     for(size_t i=0; i<gop->size(); i++ )
                     {
                         PictureIO::WritePicture(*outputPicture, gop->at(i));
                     }
                 encoder.DeleteOldOutputGOP();
                 break;
             case NEED_BUFFER:
                 ///if need more pictures to continue encoding
                 break;
             case END_OF_SEQUENCE:
                 //TODO: handle EOS
                 ///if encoder finished coding a sequence
                 //write out the rest of the buffer and stop the loop
                 go = false;
                 break;
             case INVALID:
                 ///if encoder stopped with an exception
                 //return EXIT_FAILURE;
                 go = false;
                 break;
             default:
                 std::cout << "Unknown state reported by encoder" << std::endl;
                 break;
                 
             }
         }while(state == PICTURE_AVAILABLE);
         
    } while(go);
    
    
    inputPicture.close();
    if(codedFile)
        codedFile->close();
    if(outputPicture)
            outputPicture->close();
    
    std::streampos out = fileSize(codedFileName.c_str());
    std::streampos in = fileSize(input.c_str());
    std::cout << "Compression ratio: " 
                << (float)out/(float)in << std::endl;
    
    
    if(params.analysis | params.analysis2)
    {
        std::string filename;
        
        size_t pos = input.find_last_of("/");
        if(pos != std::string::npos)
            filename.assign(input.begin() + pos + 1, input.end());
        else
            filename = input;
 
        std::ofstream psnrFile("psnr_results.csv", std::ios::app );
        std::stringstream stringStream;
        
        psnr[Ych] /= psnrTimes;
        psnr[Uch] /= psnrTimes;
        psnr[Vch] /= psnrTimes;
        psnr[3] /= psnrTimes;
        //print psnr values
 
        stringStream << "cubeSize.depth" << ", "
         << "levels" << ", "
         << "sub.depth" << ", "
         << "sub.height" << ", "
         << "sub.width" << ", "
         << "skipRatio" << ", "
         << "psnr Y" << ", "
         << "psnr U" << ", "
         << "psnr V" << ", "
         << "psnr YUV" << ", " 
         << "filename" << ", " 
         << "frames" << ", " 
         << "PSNRDATA" << ", " 
         << "CR" << ", "
         << std::endl;
        std::cout << stringStream.str();
        
        if(psnrFile.tellp() == 0)
        {
            psnrFile << stringStream.str();
        }
        stringStream.str("");
        
        stringStream << params.codecParams.cubeSize.depth << ", "
         << params.codecParams.levels << ", "
         << params.codecParams.subcubeSize.depth << ", "
         << params.codecParams.subcubeSize.height << ", "
         << params.codecParams.subcubeSize.width << ", "
         << params.skipRatio << ", "
         << psnr[0] << ", "
         << psnr[1] << ", "
         << psnr[2] << ", "
         << psnr[3] << ", "
         << input << ", "
         << frameNumber << ", "
         << "PSNRDATACODE" << ", " 
         << (float)out/(float)in << ", " 
         <<std::endl;
        
        psnrFile << stringStream.str();
        std::cout << stringStream.str();
    }

    //output compression ratio:
//    if(codedFile != NULL)
//        std::cout << "Compression ratio: " 
//                << (float)codedFile->tellp()/(float)inputPicture.tellg() << std::endl;

    return 0;
}
