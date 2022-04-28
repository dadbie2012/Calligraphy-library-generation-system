#coding:gbk
#!/usr/bin/python3
import time

import argparse
import sys
import os
import torchvision.transforms as transforms
from PIL  import Image
from torchvision.utils import save_image
from torch.utils.data import DataLoader
import torch
from models import Generator
from datasets import ImageDataset

import os

#ɾ������
#file = open("D:\�鷨������\outtext.txt", 'w').close()
#fd1=open("D:\�鷨������\ganorder.txt").read()
#print(fd1[0])
#f = open("D:\�鷨������\ganorder.txt")  # ����һ���ļ�����
ganorder = []

fd = open("D:\�鷨������\outtext.txt", encoding="UTF-8").read()
fd1 = open("D:\�鷨������\ganorder.txt", encoding="UTF-8").read()
print(fd1)
a=fd1.split(',',-1)




import PIL.Image as Image
import os



for i in range(len(a)-1):
    print(fd[int(a[i])-1])



for i in range(len(a)-1):

    pathin=str(fd[int(a[i])-1])
    pathout=str(a[i])+str(fd[int(a[i])-1])
    parser = argparse.ArgumentParser()
    parser.add_argument('--batchSize', type=int, default=1, help='size of the batches')
    parser.add_argument('--dataroot', type=str, default='datasets/lantingkai/', help='root directory of the dataset')
    parser.add_argument('--input_nc', type=int, default=1, help='number of channels of input data')
    parser.add_argument('--output_nc', type=int, default=1, help='number of channels of output data')
    parser.add_argument('--size', type=int, default=128, help='size of the data (squared assumed)')
    parser.add_argument('--cuda', action='store_true', help='use GPU computation')
    parser.add_argument('--n_cpu', type=int, default=0, help='number of cpu threads to use during batch generation')
    parser.add_argument('--generator_A2B', type=str, default='output/TEXT4/20_netG_A2B.pth', help='A2B generator checkpoint file')
    parser.add_argument('--generator_B2A', type=str, default='output/20_netG_B2A.pth', help='B2A generator checkpoint file')
    parser.add_argument('--demo_path', type=str, default='datasets/'+pathin+'.jpg', help='B2A generator checkpoint file')
    opt = parser.parse_args()

    parser.parse_known_args()
    print(opt)
    #default='datasets/baotakai/test/A/0010.jpg'
    ###### Definition of variables ######
        # Networks
    netG_A2B = Generator(opt.input_nc, opt.output_nc)
    netG_B2A = Generator(opt.output_nc, opt.input_nc)

    if opt.cuda:
        netG_A2B.cuda() #netG_A2B.to(torch.device('cuda')) new
        netG_B2A.cuda() #netG_B2A.to(torch.device('cuda'))


    #print(torch.load(opt.generator_A2B))

    # Load state dicts
    if opt.cuda:
        netG_A2B.load_state_dict({k.replace('module.',''):v for k,v in torch.load(opt.generator_A2B).items()})
        netG_B2A.load_state_dict({k.replace('module.',''):v for k,v in torch.load(opt.generator_B2A).items()})
    else:
        netG_A2B.load_state_dict({k.replace('module.', ''): v for k, v in torch.load(opt.generator_A2B, map_location=torch.device('cpu')).items()})
        netG_B2A.load_state_dict({k.replace('module.', ''): v for k, v in torch.load(opt.generator_B2A, map_location=torch.device('cpu')).items()})

    # Set model's test mode e.x.  set dropout and batch normalization layers to evaluation mode
    netG_A2B.eval()
    netG_B2A.eval()

    # Inputs & targets memory allocation
    Tensor = torch.cuda.FloatTensor if opt.cuda else torch.Tensor
    input_A = Tensor(opt.batchSize, opt.input_nc, opt.size, opt.size)

    # Dataset loader
    transforms_ = [ transforms.ToTensor(),transforms.Normalize((0.5,), (0.5,)) ]

    inputs = Image.open(opt.demo_path)
    transform = transforms.Compose(transforms_)
    data = transform(inputs)[None]

    # Create output dirs if they don't exist
    if not os.path.exists('demo'):
        os.makedirs('demo')
    real_A = input_A.copy_(data)

    # Generate output
    fake_B = 0.5*(netG_A2B(real_A).data + 1.0)
    real = 0.5*(real_A.data + 1.0)

    # Save image files

    t=transforms.Compose([
    transforms.Resize((100, 100)),])
    image = t(fake_B)

    save_image(image,'D:/�鷨������/����ɹ�/'+pathout+'.jpg')
    save_image(real, 'demo/demo_real_A.png')
    print('generated succeed !')
numpicture= len(fd)
IMAGES_PATH = 'D:/�鷨������/'  # ͼƬ����ַ
IMAGES_FORMAT = ['.jpg', '.JPG', '.png']  # ͼƬ��ʽ
IMAGE_SIZE = 100 # ÿ��СͼƬ�Ĵ�С
IMAGE_ROW =3# ͼƬ�����Ҳ���Ǻϲ���һ��ͼ��һ���м���

IMAGE_COLUMN = 7 # ͼƬ�����Ҳ���Ǻϲ���һ��ͼ��һ���м���
IMAGE_SAVE_PATH = 'D:/�鷨������/����ͼƬ/finall.jpg'  # ͼƬת����ĵ�ַ

# ��ȡͼƬ����ַ�µ�����ͼƬ����
image_names = []
for i in range(len(fd)):
    path2='����ɹ�/'+str(i+1)+str(fd[i])+'.jpg'
    image_names.append(path2)
image_names.append('�հ�ͼƬ/'+str(1000)+'.jpg')
image_names.append('�հ�ͼƬ/'+str(1001)+'.jpg')
image_names.append('�հ�ͼƬ/'+str(1002)+'.jpg')
image_names.append('�հ�ͼƬ/'+str(1003)+'.jpg')
image_names.append('�հ�ͼƬ/'+str(1004)+'.jpg')
image_names.append('�հ�ͼƬ/'+str(1005)+'.jpg')
image_names.append('�հ�ͼƬ/'+str(1006)+'.jpg')
image_names.append('�հ�ͼƬ/'+str(1007)+'.jpg')
image_names.append('�հ�ͼƬ/'+str(1008)+'.jpg')
image_names.append('�հ�ͼƬ/'+str(1009)+'.jpg')
image_names.append('�հ�ͼƬ/'+str(1010)+'.jpg')
image_names.append('�հ�ͼƬ/'+str(1011)+'.jpg')
image_names.append('�հ�ͼƬ/'+str(1012)+'.jpg')
image_names.append('�հ�ͼƬ/'+str(1013)+'.jpg')
image_names.append('�հ�ͼƬ/'+str(1014)+'.jpg')
image_names.append('�հ�ͼƬ/'+str(1015)+'.jpg')
image_names.append('�հ�ͼƬ/'+str(1016)+'.jpg')
image_names.append('�հ�ͼƬ/'+str(1017)+'.jpg')
image_names.append('�հ�ͼƬ/'+str(1018)+'.jpg')
image_names.append('�հ�ͼƬ/'+str(1019)+'.jpg')





# image_names = [name for name in os.listdir(IMAGES_PATH) for item in IMAGES_FORMAT if
#               os.path.splitext(name)[1] == item]


# �򵥵Ķ��ڲ������趨��ʵ��ͼƬ���Ĵ�С���������ж�
#if len(image_names) != IMAGE_ROW * IMAGE_COLUMN:
 #   raise ValueError("�ϳ�ͼƬ�Ĳ�����Ҫ�����������ƥ�䣡")



# ����ͼ��ƴ�Ӻ���
def image_compose():
    to_image = Image.new('RGB', (IMAGE_COLUMN * IMAGE_SIZE, IMAGE_ROW * IMAGE_SIZE))  # ����һ����ͼ
    # ѭ����������ÿ��ͼƬ��˳��ճ������Ӧλ����
    for y in range(1, IMAGE_ROW + 1):
        for x in range(1, IMAGE_COLUMN + 1):
            from_image = Image.open(IMAGES_PATH + image_names[IMAGE_COLUMN * (y - 1) + x - 1]).resize(
                (IMAGE_SIZE, IMAGE_SIZE), Image.ANTIALIAS)
            to_image.paste(from_image, ((x - 1) * IMAGE_SIZE, (y - 1) * IMAGE_SIZE))
    return to_image.save(IMAGE_SAVE_PATH)  # ������ͼ


image_compose()  # ���ú���

file2 = open("D:\�鷨������\outtext.txt", 'w').close()
file3 = open("D:\�鷨������\ganorder.txt", 'w').close()
file4 = open("D:\�鷨������\outstyle.txt", 'w').close()
file4 = open("D:\�鷨������\outstyle.txt", 'w').close()
file_name = "D:\\�鷨������\\����ɹ�"
for root, dirs, files in os.walk(file_name):
    for name in files:
        if name.endswith(".jpg"): # ��д����
            os.remove(os.path.join(root, name))
            print("Delete File: " + os.path.join(root, name))
