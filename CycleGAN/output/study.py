import torch
import os
import glob
import glob
import random
import os

from torch.utils.data import Dataset
from PIL import Image
import torchvision.transforms as transforms
files_A=[]
images = glob.glob(os.path.join('datasets/lantingkai/train', 'A', '*.jpg'))
files_A = sorted(glob.glob(os.path.join('datasets/lantingkai/', '%s/A' % 'train') + '/*.*'))
print(len(files_A))


