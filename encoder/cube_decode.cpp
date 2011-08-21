/* 
 * File:   cube_decode.cpp
 * Author: korzec
 *
 * Created on August 19, 2011, 10:37 PM
 */

#include "../cubecodec/types.h"
#include "../cubecodec/Decoder.h"
#include "../cubecodec/PictureIO.h"

int cube_decode(Parameters params, std::string input, std::string output)
{
    std::ifstream inputData(input.c_str(), std::ios::in | std::ios::binary);
    if (inputData.fail())
    {
        std::cerr << std::endl <<
                "Can't open input video file: " << input << std::endl;
        return EXIT_FAILURE;
    }
    else
        std::cout << "opened file " << input << std::endl;

    /// open the decoded output file
    std::ofstream *outputPicture = NULL;
    std::string outputPictureName = output + ".yuv";
    outputPicture = new std::ofstream(outputPictureName.c_str(), std::ios::out | std::ios::binary);

    Decoder decoder;
    params.codecParams.subcubeSize.width = 60;
    params.codecParams.subcubeSize.height = 32;
    params.codecParams.subcubeSize.depth = 4;

    //read header to get params and check if they were correct
    if (!decoder.ReadSequenceHeader(&inputData))
    {
        std::cout << "file header was wrong" << std::endl;
        return EXIT_FAILURE;
    }

    //report read parameters
    std::cout << " width " << decoder.GetParams().codecParams.cubeSize.width << std::endl
            << " height " << decoder.GetParams().codecParams.cubeSize.height << std::endl
            << " depth " << decoder.GetParams().codecParams.cubeSize.depth << std::endl
            << " levels " << decoder.GetParams().codecParams.levels << std::endl
            << " sw " << decoder.GetParams().codecParams.subcubeSize.width << std::endl
            << " sh " << decoder.GetParams().codecParams.subcubeSize.height << std::endl
            << " sd " << decoder.GetParams().codecParams.subcubeSize.depth << std::endl;
            
    Picture picture;
    int frameNumber = 0;
    bool go = true;
    BufferState state;

    do
    {
        //let the decoder read data for a cube
        //if failed to read then stop
        if (!decoder.ReadCube(&inputData))
            go = false;
        do
        {
            state = decoder.Decode();
            PictureVectorPtr gop;
            switch (state)
            {
            case PICTURE_AVAILABLE:
                ///if decoded picture is available
                ///write output picture and continue
                gop = decoder.GetDecodedGOP();
                for (size_t i = 0; i < gop->size(); i++)
                {
                    PictureIO::WritePicture(*outputPicture, gop->at(i));
                    frameNumber++;
                }
                decoder.DeleteOldOutputGOP();
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
                ///if decoder stopped with an exception
                //return EXIT_FAILURE;
                go = false;
                break;
            default:
                std::cout << "Unknown state reported by encoder" << std::endl;
                break;

            }
        }
        while (state == PICTURE_AVAILABLE);

    }
    while (go);

    inputData.close();
    if (outputPicture)
        outputPicture->close();
    return true;
}
