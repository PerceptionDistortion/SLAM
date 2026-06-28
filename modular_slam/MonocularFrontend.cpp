

//bool MonocularFrontend::process(){
    //convert the raw sensor data to slam object and preprocess it
    //Important: motion blur, and lighting of the frame must be checked at driver level to filter frame

    //detect and describe features of the current image: ORB, SuperPoint, etc.
    //detect and compute are hard coupled as algo compatibility matters
    //This has to be done before first frame init as, descriptors required to compare first init frame

    //Initize the prev frame and skip further processing
    //It has detect and compute data
    //The first frame is also set as the first keyframe in visual pipeline

    //Make a mandatory time gaurd check, new frame must have greater time than last

    //Track, match features between curr and prev frame: BF Matcher, KLT, SuperGlue

    //Descriptor filter based on distance threshold

    //Lowe's ratio test

    //Cross check filtering

    //RANSAC using E or F when no landmarks available or PnP, Homography

    //Update tentative feature tracks

    //Update active feature tracks

    //Check parallax to determine if further keyframe, pose and triangulation based processing feasible
    //Parallax check is done wrt last key frame

    //If parallax success, perform the pose recovery wrt last reference key frame

    //Determine the baseline between last keyframe and the current frame
    //Based on pixel within recover pose
    //Accept or reject recover pose as well as frame
    //Other checks: rotation, parallax, inliar ratio, chiarlty ratio

    //Motion gating: is estimated motion physically possible

    //local pose only refinnement: at least two landmarks
    //If no landmarks, skip this step and wait for more landmarks in the next frame
    
    //Active past landmarks quality monitoring: reject ouliers, visibility
    //associate observations with existing landmarks,
    //Project landmarks in current image, compute reprojection residuals and reject
    //Varies if no triangulated landmark init
    
    //local pose only refinement

    //Keyframe determination

    //If keyframe, new landmark init after geometry and age check

    //Perform triangulation

    //Check reprojection error of triangulated landmark and accept/reject landmark


//}

