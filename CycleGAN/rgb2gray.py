import cv2

ori_path = 'datasets/xue.jpg'
tar_paht = 'datasets/xue_gray.jpg'

img = cv2.imread(ori_path)
shape = img.shape
if len(shape)==3:
    img = img[:,:,0]
cv2.imwrite(tar_paht,img)
