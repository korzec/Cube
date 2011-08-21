/* 
 * File:   cube_encode.cpp
 * Author: korzec
 *
 * Created on August 19, 2011, 8:43 PM
 */

#include "../cubecodec/types.h"
#include "../cubecodec/Encoder.h"
#include "../cubecodec/PictureIO.h"

int cube_encode(Parameters params, std::string input, std::string output)
{
    Encoder encoder;
    params.codecParams.subcubeSize.width = 60;
    params.codecParams.subcubeSize.height = 32;
    params.codecParams.subcubeSize.depth = 4;
    
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

    std::cout << "w " << encoder.GetParams().codecParams.cubeSize.width << " h " << encoder.GetParams().codecParams.cubeSize.height << std::endl;

    //open file for writing
    std::string codedFileName = output + ".wcb";
    std::ofstream* codedFile = new std::ofstream(codedFileName.c_str(), std::ios::out | std::ios::binary);
    
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
    
    //skip frames
    for (int i=0; i<params.start_pos; ++i)
    {
        PictureIO::ReadPicture(inputPicture,
                           encoder.GetParams().codecParams.cubeSize.width, 
                           encoder.GetParams().codecParams.cubeSize.height);
    }
    
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
             frameNumber++;
             std::cout << "frame: " << frameNumber << std::endl; 
             
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
    return 0;
}
