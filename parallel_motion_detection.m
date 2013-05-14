close all;
clc
I1 = imread('frame1.jpg');
I1_Gray = rgb2gray(I1);
[F1 C1] = size(I1_Gray);
% Umbral = 128;
% for i=1:F1
%     for j=1:C1
%         if (I1_Gray(i,j) > Umbral)
%             I1_Gray(i,j) = 255;
%         else
%             I1_Gray(i,j)= 0;
%         end
%     end
% end
figure,imshow(I1_Gray);
I2 = imread('frame2.jpg');
I2_Gray = rgb2gray(I2);
[F2 C2] = size(I2_Gray);
% for i=1:F2
%     for j=1:C2
%         if (I2_Gray(i,j) > Umbral)
%             I2_Gray(i,j) = 255;
%         else
%             I2_Gray(i,j)= 0;
%         end
%     end
% end
figure,imshow(I2_Gray);

I3 = I2_Gray;
for a=-2:2
    for b=-2:2
        if(5*a+b~=0)
            for i=1:F2
                for j=1:C2
                    I3(i,j) = I2_Gray(mod(i+a+1079,1080)+1,mod(j+b+1919,1920)+1);
                end
            end
%             figure,imshow(I3);
        end
    end
end
