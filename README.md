# CMP-SWHE
Confused Module Projection based Somewhat Homomorphic Encryption BestiVictory/CMP-SWHE algorithm is based on the modulo projection theorem, the equivalence properties of congruences and the Chinese Remainder Theorem (CRT). This algorithm belongs to somewhat homomorphic encryption algorithm. On the client side, the original data is encrypted by amplification, randomization, and setting confusing redundancy. Operating on the ciphertext on the server side is equivalent to operating on the original data. As an extension, we designed and implemented a blind computing scheme of accelerated version based on batch processing technology to improve efficiency. We did a lot of experiments to test our scheme and applied it to blind foreground extraction, blind optical flow tracking and blind face detection. We also extend the algorithm to applications of deep learning. Experimental results show that although our algorithm has some tiny errors (10−6 )it is very efficient and practical, especially suitable for image and video processing, which does not require high accuracy.

We give an example to describe the whole process of blind adding two pixels in detail. Consider thesetwo pixels with value *x = 68* and *y = 78*. Let the amplification
factor a be *33*, the number of modulo bases *N* be *3*, the modulo base *B = {b1, b2, b3}*, where *b1 = 19, b2 = 29,b3 =31* and the number of redundancies *M* be *2*. The parameters set here are just for the convenience of display. In the actual process, the parameters will be different.

<div align="center">
  <img src="https://i.loli.net/2021/08/25/k9eTdLZ4tPR8qan.png",height='500',width='500'><br><br>
</div>

## Function
Our blind computing library implements common operations such as addition, subtraction, multiplication, division and power operation。***blind frame difference.cpp*** is a demo,The background difference method is suitable for the foreground extraction of video with relatively static background and no great change. The default background of the background difference method is unchanged, and the foreground is extracted after the fixed background frame is set. In this method, when extracting the foreground of a frame, the difference operation is performed between the frame and the pre stored background frame to obtain the differential gray image, and then the threshold judgment is carried out to extract the moving target.
## Environment
The project code needs to run on ***OpenCV, cryptopp565*** and ***miracl*** libraries，you can get them by clicking [here](https://pan.baidu.com/s/1zEkdfzsscyeBIaiGealjCw)
,password：bu7c.
We also compiled our core code into libraries，you can see them in ***include*** and ***lib*** .
## our paper
[pdf](https://pan.baidu.com/s/1iqWqrvlYxMfI__OZmL-Iew),password:F2G2 



